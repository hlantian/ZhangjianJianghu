#!/usr/bin/perl
#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

BEGIN {
    $startingtime=(times)[0]+(times)[1];
    foreach ($0,$ENV{'PATH_TRANSLATED'},$ENV{'SCRIPT_FILENAME'}){
    	my $LBPATH = $_;
    	next if ($LBPATH eq '');
    	$LBPATH =~ s/\\/\//g; $LBPATH =~ s/\/[^\/]+$//o;
        unshift(@INC,$LBPATH);
    }
}

use LBCGI;
$LBCGI::DISABLE_UPLOADS = 1;
$LBCGI::HEADERS_ONCE = 1;
$LBCGI::POST_MAX = 500000;
require "data/boardinfo.cgi";
require "data/styles.cgi";
require "bbs.lib.pl";

$|++;
$thisprog = "attachment.cgi";
$query = new LBCGI;

&error("盗链&请不要盗链$boardname的连接！") if ($ENV{'HTTP_REFERER'} !~ /$ENV{'HTTP_HOST'}/i && $ENV{'HTTP_REFERER'} ne '' && $ENV{'HTTP_HOST'} ne '' && $pvtdown ne "no");
$inforum = $query->param('forum');
$intopic = $query->param('topic');
$inpostno = $query->param('postno');
$fileext = $query->param('type');
$fileext =~ s/\.//sg;
$fileext = &stripMETA($fileext);
$fileext = lc($fileext);
&error('打开文件&老大，别乱黑我的程序呀！') if ($inforum !~ /^\d+$/ || $intopic !~ /^\d+$/ || $inpostno !~ /^\d+$/ || $fileext eq '');
require "data/style$inforum.cgi" if (-e "${lbdir}data/style$inforum.cgi");

$inmembername = $query->cookie("amembernamecookie") unless ($inmembername);
$inpassword = $query->cookie("apasswordcookie") unless ($inpassword);
$inmembername =~ s/[\a\f\n\e\0\r\t\`\~\!\@\#\$\%\^\&\*\(\)\+\=\\\{\}\;\'\:\"\,\.\/\<\>\?]//isg;
$inpassword =~ s/[\a\f\n\e\0\r\t\|\@\;\#\{\}\$]//isg;

if (!$inmembername || $inmembername eq "客人")
{
	if ($regaccess eq 'on' || $privateforum eq 'yes')
	{
		print header(-charset=>gb2312 , -expires=>"$EXP_MODE" , -cache=>"$CACHE_MODES");
		print qq~<script language="JavaScript">document.location = "loginout.cgi?forum=$inforum";</script>~;
		exit;
	}
	$inmembername = '客人';
	$rating = -6;
        &error("普通错误&客人不能查看附件，请注册或登录后再试") if ($guestregistered eq "off" && $pvtdown ne "no");
}
else
{
	&getmember($inmembername, 'no');
	&error('普通错误&此用户根本不存在！') if ($userregistered eq 'no');
	&error('普通错误&密码与用户名不相符，请重新登录！') if ($inpassword ne $password);
}

&getoneforum($inforum);
$testentry = $query->cookie("forumsallowed$inforum");
$allowed = $allowedentry{$inforum} eq 'yes' || ($testentry eq $forumpass && $testentry ne '') || $membercode eq 'ad' || $membercode eq 'smo' || $inmembmod eq 'yes' ? 'yes' : 'no';
&error("进入私有论坛&对不起，您没有权限进入该私有论坛！") if ($privateforum eq 'yes' && $allowed ne 'yes' && $pvtdown ne "no");
&error("进入论坛&你一般会员不允许进入此论坛！") if ($startnewthreads eq 'cert' && (($membercode ne 'ad' && $membercode ne 'smo' && $membercode ne 'cmo' && $membercode ne 'mo' && $membercode !~ /^rz/) || $inmembername eq '客人') && $userincert eq 'no' && $pvtdown ne "no");
if ($allowusers ne ''){
    &error('进入论坛&你不允许进入该论坛！') if (",$allowusers," !~ /,$inmembername,/i && $membercode ne 'ad' && $pvtdown ne "no");
}
if ($membercode ne 'ad' && $membercode ne 'smo' && $inmembmod ne 'yes') {
    &error("进入论坛&你不允许进入该论坛，你的威望为 $rating，而本论坛只有威望大于等于 $enterminweiwang 的才能进入！") if ($enterminweiwang > 0 && $rating < $enterminweiwang);
    if ($enterminmony > 0 || $enterminml > 0 || $enterminjy > 0 ) {
	require "data/cityinfo.cgi" if ($addmoney eq "" || $replymoney eq "" || $moneyname eq "");
	$mymoney1 = $numberofposts * $addmoney + $numberofreplys * $replymoney + $visitno * $loginmoney + $mymoney - $postdel * $delmoney + $jhcount * $addjhhb;
	$meili1   = $numberofposts * $addml + $numberofreplys * $replyml + $visitno * $loginml + $meili - $postdel * $delml + $jhcount * $addjhml;
	$jingyan1 = $numberofposts * $ttojy + $numberofreplys * $rtojy + $visitno * $ltojy + $addjy - $postdel * $deljingyan + $jhcount * $addjhjy;
	&error("进入论坛&你不允许进入该论坛，你的金钱为 $mymoney1，而本论坛只有金钱大于等于 $enterminmony 的才能进入！") if ($enterminmony > 0 && $mymoney1 < $enterminmony);
	&error("进入论坛&你不允许进入该论坛，你的魅力为 $meili1，而本论坛只有魅力大于等于 $enterminml 的才能进入！") if ($enterminml > 0 && $meili1 < $enterminml);
	&error("进入论坛&你不允许进入该论坛，你的经验为 $jingyan1，而本论坛只有经验大于等于 $enterminjy 的才能进入！") if ($enterminjy > 0 && $jingyan1 < $enterminjy);
    }
}

$inpostno--;
$file = $inpostno > 0 ? "$inforum\_$intopic\_$inpostno\.$fileext" : "$inforum\_$intopic\.$fileext";
&error("打开文件&老大，别乱黑我的程序呀！") unless (-e "$imagesdir$usrdir/$inforum/$file");

if (open(FILE, "${lbdir}forum$inforum/$intopic.thd.cgi")) {
	undef $/;
	my $thread = <FILE>;
	close (FILE);
	$/ = "\n";
	@threads = split(/\n/, $thread);
}

if ($membercode eq "ad" or $membercode eq "smo" or $inmembmod eq "yes") {
    $viewhide = 1;
}
else {
    $viewhide = 0;
    if ($hidejf eq "yes" ) { 
	my @viewhide=grep(/^$inmembername\t/i,@threads);
	$viewhide=@viewhide;
	$viewhide=1 if ($viewhide >= 1);
    }
}
$StartCheck=$numberofposts+$numberofreplys;

my ($poster, undef, undef, undef, undef, undef, $post1, undef) = split(/\t/, $threads[$inpostno]);

if ($hidejf eq "yes"  && $pvtdown ne "no") {
    if ($post1 =~ /(\[hide\])(.+?)(\[\/hide\])/) {
      if ($viewhide ne "1") { 
	&error('普通错误&由于你没有回复过这个主题，所以你无权下载这个加密附件！')
      }
    }
}

if ($postjf eq "yes" && $pvtdown ne "no") {
    if ($post1 =~m/\[post=(.+?)\](.+?)\[\/post\]/isg){ 
	$viewusepost=$1; 
        unless (($StartCheck >= $viewusepost)||($membercode eq "ad")||($membercode eq "smo")||($inmembmod eq "yes")||($poster eq $inmembername)){ 
	    &error("普通错误&你无权下载这个加密附件！需要发贴达到$viewusepost，而你只有$StartCheck。")
   	}
    }
}

if ($wwjf ne "no" && $pvtdown ne "no") {
    if ($post1=~/LBHIDDEN\[(.*?)\]LBHIDDEN/sg) {
        unless (($inmembername eq $poster)||($membercode eq "ad") || ($membercode eq 'smo') || ($inmembmod eq "yes")|| ($rating >= $1) ) {
            &error("普通错误&你无权下载这个加密附件！需要威望$1，而你只有$rating。")
	}
    }
}

    if ($cansale ne "no" && $pvtdown ne "no") {
	if ($post1=~/LBSALE\[(.*?)\]LBSALE/sg) {
    	    my $postno = $inpostno;
            my $isbuyer = "";
            my $allbuyer = "";
            if (open(FILE, "${lbdir}sale/$inforum\_$intopic\_$inpostno.cgi")) {
                my $allbuyer = <FILE>;
                close(FILE);
                chomp $allbuyer;
		$allbuyer =~ s/\t\t/\t/isg;
                $allbuyer =~ s/\t$//gi;
                $allbuyer =~ s/^\t//gi;
	        $allbuyer = "\t$allbuyer\t";
		$isbuyer="yes" if ($allbuyer =~ /\t$inmembername\t/i);
            }
            unless (($inmembername eq $poster)||($membercode eq "ad")||($membercode eq 'smo')||($inmembmod eq "yes")||($isbuyer eq "yes")) {
                &error('普通错误&因为你没有购买，所以你无权下载这个加密附件！')
	    }
	}
    }


$filename = $file;
$filesize = (stat("$imagesdir$usrdir/$inforum/$file"))[7];
$fileext = 'jpeg' if ($fileext eq 'jpg');
$fileext = 'html' if ($fileext eq 'htm');
print $fileext eq 'gif' || $fileext eq 'jpeg' || $fileext eq 'png' || $fileext eq 'bmp' ? header(-type=>"image/$fileext", -attachment=>$filename, -expires=>'-1d', -content_length=>$filesize) : $fileext eq 'swf' ? header(-type=>"application/x-shockwave-flash", -attachment=>$filename, -expires=>'-1d', -content_length=>$filesize) : $fileext eq 'txt' || $fileext eq 'html' ? header(-type=>"text/$fileext", -attachment=>$filename, -expires=>'-1d', -content_length=>$filesize) : header(-type=>"attachment/$fileext", -attachment=>$filename, -expires=>'-1d', -content_length=>$filesize);
binmode(STDOUT);
undef $/;
open(FILE, "$imagesdir$usrdir/$inforum/$file");
binmode(FILE);
print <FILE>;
close(FILE);
$/ = "\n";
exit;
