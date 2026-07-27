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
$LBCGI::HEADERS_ONCE = 1;
require "data/boardinfo.cgi";
require "bbs.lib.pl";

$|++;
$query = new LBCGI;

$inforum         = $query -> param('forum');
$intopic         = $query -> param('topic');
$inreply         = $query -> param('reply');
print "Location: $boardurl/leobbs.cgi\n\n" if (($intopic !~ /^[0-9]+$/)||($inforum !~ /^[0-9]+$/)||(($inreply ne "")&&($inreply !~ /^[0-9]+$/)));
$HackDTPath="${lbdir}FileCount/$inforum/$inforum\_$intopic.cgi";
open(HACK, "$HackDTPath");
@AllHackDetail=<HACK>;
close(HACK);
chomp @AllHackDetail;
$DTDetail=join("\n",@AllHackDetail);
$AddmeName="$inforum\_$intopic\_$inreply";
@Find=grep(/^$AddmeName=/,@AllHackDetail);
$CFind=@Find;
$Find=($CFind > 0)?"yes":"no";
if ($Find eq 'yes') {
    chomp $Find[0];
    ($ThisHackName,$ThisFileName,$ThisHackDT)=split(/\=/,$Find[0]);
    $ThisHackDT++;
    $NewDTDetail="$ThisHackName\=$ThisFileName\=$ThisHackDT";
    $DTDetail=~s/$Find[0]/$NewDTDetail/s;
    open(NHACK, ">$HackDTPath");
    print NHACK "$DTDetail\n";
    close(NHACK);
    ($up_name, $up_ext) = split(/\./,$ThisFileName);
    if ($inreply eq "") {$inreply = 0;} else {$inreply++;}
    print "Location: attachment.cgi?forum=$inforum&topic=$intopic&postno=$inreply&type=.$up_ext\n\n";
} else {
    $dirtoopen2 = "$imagesdir" . "$usrdir/$inforum";
    opendir (DIR, "$dirtoopen2");
    my @dirdata2 = readdir(DIR);
    closedir (DIR);
    if ($inreply eq "") {
        @files11 = grep(/^$inforum\_$intopic\./,@dirdata2);
    } else {
	@files11= grep(/^$inforum\_$intopic\_$inreply\./,@dirdata2);
    }
    my $file2 = @files11;
    if ($file2 > 0) {
        my $files2s = $files11[0];
        chomp $files2s;
        ($up_name, $up_ext) = split(/\./,$files2s);
        $up_ext =~ tr/A-Z/a-z/;
        open(NHACK, ">>$HackDTPath");
        print NHACK "$inforum\_$intopic\_$inreply\=$up_name\.$up_ext\=1\n";
        close(NHACK);
        if ($inreply eq "") {$inreply = 0;} else {$inreply++;}
        print "Location: attachment.cgi?forum=$inforum&topic=$intopic&postno=$inreply&type=.$up_ext\n\n";
    } else {
	print "Location: $boardurl/leobbs.cgi\n\n"
    }
}
exit;
