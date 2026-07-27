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
$LBCGI::POST_MAX=20000;
$LBCGI::DISABLE_UPLOADS = 1;
$LBCGI::HEADERS_ONCE = 1;
require "data/boardinfo.cgi";
require "data/styles.cgi";
require "bbs.lib.pl";

$|++;

$thisprog = "lookemotes.cgi";
eval ('$complevel = 9 if ($complevel eq ""); use WebGzip($complevel);') if ($usegzip eq "yes");

    $query = new LBCGI;

	@params = $query->param;
	foreach $param(@params) {
		$theparam = $query->param($param);
        $theparam = &cleaninput("$theparam");
		$PARAM{$param} = $theparam;
	    }



$action      =  $PARAM{'action'};
$inforum     =  $PARAM{'forum'};
&error("打开文件&老大，别乱黑我的程序呀！") if (($inforum) && ($inforum !~ /^[0-9]+$/));

$inmember            = $query -> param('member');
$inmembername        = $query -> param("membername");
$inpassword          = $query -> param("password");
$action              = &cleaninput("$action");
$inmember            = &cleaninput("$inmember");
$inmembername        = &cleaninput("$inmembername");
$inpassword          = &cleaninput("$inpassword");
if ($inpassword ne "") {
    eval {$inpassword = md5_hex($inpassword);};
    if ($@) {eval('use Digest::MD5 qw(md5_hex);$inpassword = md5_hex($inpassword);');}
    unless ($@) {$inpassword = "lEO$inpassword";}
}

    if (! $inmembername) { $inmembername = $query->cookie("amembernamecookie"); }
    if (! $inpassword)   { $inpassword   = $query->cookie("apasswordcookie"); }
$inmembername =~ s/[\a\f\n\e\0\r\t\`\~\!\@\#\$\%\^\&\*\(\)\+\=\\\{\}\;\'\:\"\,\.\/\<\>\?]//isg;
$inpassword =~ s/[\a\f\n\e\0\r\t\|\@\;\#\{\}\$]//isg;

if ($inmembername eq "" || $inmembername eq "客人" ) { $inmembername = "客人"; }
    else {
#    &getmember("$inmembername");
    &getmember("$inmembername","no");
    &error("普通错误&此用户根本不存在！") if ($userregistered eq "no");
        }   

&mischeader("论坛EMOTE列表");

print header(-charset=>gb2312 , -expires=>"$EXP_MODE" , -cache=>"$CACHE_MODES");

$output .= qq~
    <html>
    <head>
    <title>$forumname配色列表</title>
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312">
    <style type="text/css">
		A:visited {	TEXT-DECORATION: none	}
		A:active  {	TEXT-DECORATION: none	}
		A:hover   {	TEXT-DECORATION: underline overline	}
		A:link 	  {	text-decoration: none;}
		
	        A:visited {	text-decoration: none;}
	        A:active  {	TEXT-DECORATION: none;}
	        A:hover   {	TEXT-DECORATION: underline overline}
	        
		.t     {	LINE-HEIGHT: 1.4			}
		BODY   {	FONT-FAMILY: 宋体; FONT-SIZE: 9pt;
			SCROLLBAR-HIGHLIGHT-COLOR: buttonface;
 			SCROLLBAR-SHADOW-COLOR: buttonface;
 			SCROLLBAR-3DLIGHT-COLOR: buttonhighlight;
 			SCROLLBAR-TRACK-COLOR: #eeeeee;
 			SCROLLBAR-DARKSHADOW-COLOR: buttonshadow	}
		TD	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		DIV	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		FORM	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		OPTION	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		P	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		TD	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
		BR	{	FONT-FAMILY: 宋体; FONT-SIZE: 9pt	}
input {border-width: 1; border-color: #000000; font-family: 宋体; font-size: 9pt; font-style: bold;}
textarea {border-width: 1; border-color: #000000; background-color: #efefef; font-family: 宋体; font-size: 9pt; font-style: bold;}
select {border-width: 1; border-color: #000000; background-color: #efefef; font-family: 宋体; font-size: 9pt; font-style: bold;}
    </style></head>
    <body $lbbody>
    ~;
        
        

            
            my %Mode = (             
            'style'               =>    \&styleform,                                
                       
            );


            if($Mode{$action}) { 
               $Mode{$action}->();
               }
                
        


##################################################################################
sub styleform {
&mischeader("查看论坛 EMOTE 列表");
$filetoopen = "$lbdir" . "data/emote.cgi";
open (FILE, "$filetoopen");
flock (FILE, 1) if ($OS_USED eq "Unix");
$emote = <FILE>;
close (FILE);

$output .= qq~
<BR>
<table width=$tablewidth bordercolor=$tablebordercolor align=center cellpadding=0 cellspacing=0><tr><td>注意:</td><td>下列所有的"对象"将被替换成发贴人的用户名.</td></tr></table>
        <table width=$tablewidth border=1 bordercolor=$tablebordercolor align=center cellpadding=3 cellspacing=3><br>
       ~;  
       @pairs1 = split(/\&/,$emote);
	    foreach (@pairs1) {
		($toemote, $beemote) = split(/=/,$_);
		chomp $beemote;
	$output .= qq~
	<tr><td bgcolor=$forumcolorone>$toemote</td><td  bgcolor=$forumcolortwo>$beemote</td>	           
~;
}
}

$output .= qq~</tr></table><br><br></body></html>~;
&output("$boardname - 查看论坛 EMOTE 列表",\$output);
exit;

