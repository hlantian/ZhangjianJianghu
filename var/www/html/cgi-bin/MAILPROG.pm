#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

package MAILPROG;
use strict;

use vars qw(@ISA @EXPORT);
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(sendmail);

sub sendmail {
    my ($fromaddr, $replyaddr, $to, $subject, $message) = @_;
    if ($main::emailtype eq "smtp_mail") {
	$main::SMTP_SERVER =~ s/^\s+//g;
	$main::SMTP_SERVER =~ s/\s+$//g;
	$main::SMTP_PORT = 25 if ($main::SMTP_PORT !~ /^\d+$/);
	$main::emailfunctions = "off" if ($main::SMTP_SERVER eq "");
    }
    elsif ($main::emailtype eq "esmtp_mail") {
	$main::SMTP_SERVER =~ s/^\s+//g;
	$main::SMTP_SERVER =~ s/\s+$//g;
	$main::SMTP_PORT = 25 if ($main::SMTP_PORT !~ /^\d+$/);
	$main::emailfunctions = "off" if ($main::SMTP_SERVER eq "" || $main::SMTPUSER eq "");
    }
    elsif ($main::emailtype eq "send_mail") {
	$main::emailfunctions = "off" if ($main::SEND_MAIL eq "");
    }
    $to =~ s/\\//isg;
    $to =~ s/[ \a\f\e\0\r\t]+//isg;
    $to =~ s/\,$//isg;
    $to =~ s/\,/\, /isg;

    my $sendstat = 0;
    if ($to ne "" && $main::emailfunctions eq "on") {
	$fromaddr =~ s/.*<([^\s]*?)>/$1/;
	$replyaddr =~ s/.*<([^\s]*?)>/$1/;
	$replyaddr =~ s/^([^\s]+).*/$1/;
	$message .= "<br>=====================================================<br>";
	$message .= "此邮件由雷傲极酷超级论坛（LEO SuperCool BBS）发送...  \n<br>";
	if ($main::emailtype eq "blat_mail") {
	    $sendstat = 1 if (&blat_mail($to, $fromaddr, $replyaddr, $subject, $message));
	}
	elsif ($main::emailtype eq "send_mail") {
	    $sendstat = 1 if (&send_mail($to, $fromaddr, $replyaddr, $subject, $message));
	}
	elsif ($main::emailtype eq "smtp_mail") {
	    $message =~ s/\n/\r/isg;
	    $sendstat = 1 if (&smtpmail($to, $fromaddr, $replyaddr, $subject, $message, "no"));
	}
	elsif ($main::emailtype eq "esmtp_mail") {
	    $message =~ s/\n/\r/isg;
	    $sendstat = 1 if (&smtpmail($to, $fromaddr, $replyaddr, $subject, $message, "yes"));
	}
	elsif ($main::emailtype eq "directmail") {
	    $message =~ s/\n/\r/isg;
	    $sendstat = 1 if (&directmail($to, $fromaddr, $replyaddr, $subject, $message));
	}
    }
    return $sendstat;
}

sub send_mail {
    my ($to, $fromaddr, $replyaddr, $subject, $message) = @_;
    my @to1 = split(/\, /, $to);
    foreach $to (@to1) {
	chomp $to;
	next if ($to !~ /\@/);
	return 0 unless (open(MAIL, "| $main::SEND_MAIL -t"));
	print MAIL "To: $to\n";
	print MAIL "From: $fromaddr\n";
	print MAIL "Reply-to: $replyaddr\n" if ($replyaddr ne "");
	print MAIL "X-Mailer: LeoBBS Sendmail Mail Sender\n";
	print MAIL "Content-Type: text/html; charset=gb2312\n";
	print MAIL "Subject: $subject\n\n";
	print MAIL $message;
	print MAIL "\n.";
	close(MAIL);
    }
    return 1;
}

sub blat_mail {
    my ($to, $fromaddr, $replyaddr, $subject, $message) = @_;
    my @to1 = split(/\, /, $to);
    my $tempfile = "${main::lbdir}lock/tempfile.txt";
    open(FILE, ">$tempfile");
    print FILE $message;
    close(FILE);
    foreach $to (@to1) {
	chomp $to;
	next if ($to !~ /\@/);
	return 0 unless (open(MAIL, qq~|blat $tempfile -t "$to" -i "$fromaddr" -f "$fromaddr" -s "$subject"~));
	close(MAIL);
    }
    unlink($tempfile);
    return 1;
}

sub smtpmail {
    if ($main::loadsocketmo ne 1) { eval("use Socket;"); $main::loadsocketmo = 1; }
    my ($address, $from, $replyaddr, $subject, $body, $extra) = @_;

    my ($name, $aliases, $proto, $type, $len, $thataddr);
    my @to = split(/, /, $address);
    foreach my $i (@to) {
	#对地址进行解码
	my $AF_INET = 2;
	my $SOCK_STREAM = 1;
	my $SOCKADDR = 'S n a4 x8';

	($name, $aliases, $proto) = getprotobyname('tcp');
	($name, $aliases, $type, $len, $thataddr) = gethostbyname($main::SMTP_SERVER);
	my $this = pack($SOCKADDR, $AF_INET, 0);
	my $that = pack($SOCKADDR, $AF_INET, $main::SMTP_PORT, $thataddr);

	#打开SMTP的socket端口
	socket(S, $AF_INET, $SOCK_STREAM, $proto);
	bind(S, $this);
	connect(S, $that);

	select(S);
	$| = 1;
	select(STDOUT);
	my $a = <S>;
	if ($a !~ /^2/) {
	    close(S);
	    undef $|;
	    return $a;
	}

	if ($extra eq "no") {#与普通SMTP服务器握手连接
	    print S "HELO localhost\r\n";
	    $a = <S>;
	} else {#进行ESMTP身份验证
	    print S "EHLO localhost\r\n";
	    $a = <S>;
	    print S "AUTH LOGIN\r\n";
	    $a = <S>;
	    my $encode_smtpuser = &Base64encode($main::SMTPUSER);    #用来验证的用户名必须经过Base64编码后发往服务器
	    print S "$encode_smtpuser\r\n";
	    $a = <S>;
	    my $encode_smtppass = &Base64encode($main::SMTPPASS);    #用来验证的密码必须经过Base64编码后发往服务器
	    print S "$encode_smtppass\r\n";
	    $a = <S>;
	    return $a if ($a =~ /fail/i);
	}

	#发送邮件头部信息
	print S "MAIL FROM: <$from>\r\n";
	$a = <S>;
	print S "RCPT TO: <$i>\r\n";
	$a = <S>;

	#发送邮件正文
	print S "DATA\r\n";
	$a = <S>;
	print S "From: $from\r\n";
	print S "To: $i\r\n";
	print S "Subject: $subject\r\n";
	print S "Reply-To: $replyaddr\r\n" if ($replyaddr);
	print S "X-Mailer: LeoBBS eSmtp Mail Sender\r\n";
	print S "Content-Type: text/html; charset=gb2312\r\n\r\n";
	print S "$body\r\n";
	print S "\r\n\r\n";
	print S ".\r\n";
	$a = <S>;

	print S "QUIT\r\n";
	$a = <S>;
	close(S);
	undef $|;
    }
    return 1;
}

sub directmail {
    if ($main::loadsocketmo ne 1) { eval("use Socket;"); $main::loadsocketmo = 1; }

    my ($address, $from, $replyaddr, $subject, $body) = @_;
    my @to = split(/, /, $address);

    my ($name, $aliases, $proto, $type, $len, $thataddr, $mxrecord, @mxs);

    my $AF_INET = 2;
    my $SOCK_STREAM = 1;
    my $SOCKADDR = 'S n a4 x8';

    foreach my $i (@to) {
	my $host = lc((split(/\@/, $i))[-1]);

	#MX解析纪录缓存部分
	if (open(FILE, "${main::imagesdir}caches/mxrecord.txt")) {
	    undef $/;
	    $mxrecord = <FILE>;
	    $/ = "\n";
	    close(FILE);
	}
	while ($mxrecord =~ s/([\S\t]+)//o) {
	    my ($domain, $record) = split(/\t/, $1);
	    if ($domain eq $host) {
		@mxs = split(/\|/, $record);
		last;
	    }
	}
	unless (@mxs) {
	    if ($main::loaddnsmo ne 1) { eval("use Net::DNS;"); $main::loaddnsmo = 1; }

	    my $res = new Net::DNS::Resolver;

	    @mxs = mx($res, $host);
	    @mxs = map($_->exchange, @mxs);

	    if (@mxs) {
		my $record = join('|', @mxs);
		if (open(FILE, ">>${main::imagesdir}caches/mxrecord.txt")) {
		    print FILE "$host\t$record\n";
		}
	    }
	}
	#MX解析记录缓存结束

	foreach my $mx (@mxs) {
	    ($name, $aliases, $proto) = getprotobyname('tcp');
	    ($name, $aliases, $type, $len, $thataddr) = gethostbyname($mx);
	    my $this = pack($SOCKADDR, $AF_INET, 0);
	    my $that = pack($SOCKADDR, $AF_INET, 25, $thataddr);

	    socket(S, $AF_INET, $SOCK_STREAM, $proto);
	    bind(S, $this);
	    connect(S, $that);

	    select(S);
	    $| = 1;
	    select(STDOUT);
	    my $a = <S>;
	    next unless ($a =~ /220/);
	    print S "HELO localhost\r\n";
	    $a = <S>;

	    #发送邮件头部信息
	    print S "MAIL FROM: <$from>\r\n";
	    $a = <S>;
	    print S "RCPT TO: <$i>\r\n";
	    $a = <S>;

	    #发送邮件正文
	    print S "DATA\r\n";
	    $a = <S>;
	    print S "From: $from\r\n";
	    print S "To: $i\r\n";
	    print S "Subject: $subject\r\n";
	    print S "Reply-To: $replyaddr\r\n" if ($replyaddr);
	    print S "X-Mailer: LeoBBS eSmtp Mail Sender\r\n";
	    print S "Content-Type: text/html; charset=gb2312\r\n\r\n";
	    print S "$body\r\n";
	    print S "\r\n\r\n";
	    print S ".\r\n";
	    $a = <S>;
	    print S "QUIT\r\n";
	    $a .= <S>;
	    close(S);
	    undef $|;
	    last if ($a =~ /250/);
	}
    }
    return 1;
}

sub Base64encode {
#Base64编码函数
    my $res = pack("u", $_[0]);
    $res =~ s/^.//mg;
    $res =~ s/\n//g;
    $res =~ tr|` -_|AA-Za-z0-9+/|;
    my $padding = (3 - length($_[0]) % 3) % 3;
    $res =~ s/.{$padding}$/'=' x $padding/e if $padding;
    return $res;
}
1;
