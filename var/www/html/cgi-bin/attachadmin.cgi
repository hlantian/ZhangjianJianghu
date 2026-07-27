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
use File::Copy;
$loadcopymo = 1;

$LBCGI::POST_MAX=200000;
$LBCGI::DISABLE_UPLOADS = 1;
$LBCGI::HEADERS_ONCE = 1;
require "data/boardinfo.cgi";
require "data/styles.cgi";
require "admin.lib.pl";
require "bbs.lib.pl";
$|++;

$thisprog = "attachadmin.cgi";
$query = new LBCGI;
#&ipbanned; #封杀一些 ip

$action	   = $query -> param('action');
$action	   = &unHTML("$action");
#Global
$forum		= $query -> param('forum');
$forum		= &unHTML("$forum");
$topic		= $query -> param('topic');
$topic		= &unHTML("$topic");
$reply		= $query -> param('reply');
$reply		= &unHTML("$reply");
$eachp		= $query -> param('eachp');
$eachp		= &unHTML("$eachp");
$start		= $query -> param('start');
$start		= &unHTML("$start");
#Top
$sortt		= $query -> param('sortt');
$aord		 = ($query -> param('aord') eq "a")?"a":"d";
#Move
$nforum	   = $query -> param('nforum');
$nforum	   = &unHTML("$nforum");
$ntopic	   = $query -> param('ntopic');
$ntopic	   = &unHTML("$ntopic");
$nreply	   = $query -> param('nreply');
$nreply	   = &unHTML("$nreply");
#For Mult Attachmant
$count		= $query -> param('count');
$count		= &unHTML("$count");

#v2.0
$pageaction   = ($query -> param('pageaction'))?1:0;

$inmembername = $query->cookie("adminname");
$inpassword   = $query->cookie("adminpass");
$inmembername =~ s/[\a\f\n\e\0\r\t\`\~\!\@\#\$\%\^\&\*\(\)\+\=\\\{\}\;\'\:\"\,\.\/\<\>\?]//isg;
$inpassword =~ s/[\a\f\n\e\0\r\t\|\@\;\#\{\}\$]//isg;

my %Mode = ('deleteattach' => \&deleteattach,'moveattach' => \&moveattach,'copyattach' => \&copyattach,
			'delete_no_topic' => \&delete_no_topic,'multdelete' => \&multdelete);#v3.5

$pageaction   = 1 if(!$Mode{$action});#v2.0
#################--- Main program ---###################
&getadmincheck;
print header(-charset=>gb2312 , -expires=>"$EXP_MODE" , -cache=>"$CACHE_MODES");
if(!$pageaction) { 
    &getmember("$inmembername","no");
	print qq~<html>
	<head>
	<title>LeoBBS - 论坛管理中心</title>
	<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<style>
A:visited{TEXT-DECORATION: none}
A:active{TEXT-DECORATION: none}
A:hover{TEXT-DECORATION: underline overline}
A:link{text-decoration: none;}
.t{LINE-HEIGHT: 1.4}
TD,DIV,form ,OPTION,P,TD,BR{FONT-FAMILY: 宋体; FONT-SIZE: 9pt} 
INPUT{BORDER-TOP-WIDTH: 1px; PADDING-RIGHT: 1px; PADDING-LEFT: 1px; BORDER-LEFT-WIDTH: 1px; FONT-SIZE: 9pt; BORDER-LEFT-COLOR: #cccccc; BORDER-BOTTOM-WIDTH: 1px; BORDER-BOTTOM-COLOR: #cccccc; PADDING-BOTTOM: 1px; BORDER-TOP-COLOR: #cccccc; PADDING-TOP: 1px; HEIGHT: 18px; BORDER-RIGHT-WIDTH: 1px; BORDER-RIGHT-COLOR: #cccccc}
textarea, select {border-width: 1; border-color: #000000; background-color: #efefef; font-family: 宋体; font-size: 9pt; font-style: bold;}
</style>
</head>
<body bgcolor="#555555" topmargin=0 leftmargin=0>
	<table width=100% cellpadding=6 cellspacing=0 height=100% style="border:1 solid #555555;">~;
	if ((($membercode eq "ad") || ($membercode eq "smo")) && ($inpassword eq $password) && (lc($inmembername) eq lc($membername))) {
			   $Mode{$action}->();
	} else {
				&erroroutsmall("请先登入管理中心！");
	}
	print qq~<tr><td bgcolor="#FFFFFF" align=right valign="bottom" height="40"><a href="http://www.LeoHacks.com" target="_blank" title="官方LeoBoard Hacks开发站点"><font color=#bbbbbb>ATTACHA for LBXP Beta 3.5</font></a><br><font color=#bbbbbb>Copyright &copy; 2002 RoyRoy All rights reserved</font></td></tr></table>~;
			} else {
&admintitle;
&getmember("$inmembername","no");
	if ((($membercode eq "ad") || ($membercode eq "smo")) && ($inpassword eq $password) && (lc($inmembername) eq lc($membername))) {
	print qq~
	<tr><td bgcolor="#2159C9"><font color="#FFFFFF">
	<b>欢迎来到论坛管理中心 / 文章附件管理器</b>
	</td></tr>~;
			if($Mode{$action}){#v2.0
			   $Mode{$action}->();
			}else{
			   &toppage;
			}
	print qq~<tr><td bgcolor="#FFFFFF" align=right valign="bottom" height="80"><a href="http://www.LeoHacks.com" target="_blank" title="官方LeoBoard Hacks开发站点"><font color=#bbbbbb>ATTACHA for LBXP Beta 3.5</font></a><br><font color=#bbbbbb>Copyright &copy; 2002 RoyRoy All rights reserved</font></td></tr></table></td></tr></table>~;
	} else {
		&adminlogin;
	}
			}
sub delete_no_topic{#v2.0
	$attachdir="${imagesdir}$usrdir/$forum";
	if($forum ne ""){
		if(!-d $attachdir){
	&errorout("管理程式出错","找不到附件目录 - $attachdir");return;
		}
	}
	print qq~
	<tr>
	<td bgcolor="#EEEEEE" align=center>
	<font color="#990000"><b>删除丢失主题的附件</b>
	</td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align=center colspan=2><table width=90% cellspacing="0" cellpadding="2">
	<tr><td align="center" bgcolor="#DDDDDD"><b style="color:blue">附件名称</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">附件容量</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">上傳日期</b></td><td align="center" width="30%" bgcolor="#DDDDDD"><b style="color:blue">已删除</b></td></tr>
	~;
	opendir(DIR,"$attachdir");
	@attachfiles=grep(/^$forum\_/,readdir(DIR));
	closedir(DIR);
	chomp @attachfiles;
	$allattachcount=@attachfiles;
	$start=0 if(!$start);
	$end=$start+$eachp;
	$end=$allattachcount if($end > $allattachcount);
	$j=$start+1;
	$k=$start;
	for($i=$start;$i<$end;$i++){
	$filefullname=$attachfiles[$i];
	next if($filefullname eq "");
		$filepath="$attachdir/".$filefullname;
		my @filename=split(/\./,$filefullname);
		my($forumid,$topicid,$relyid)=split(/\_/,$filename[0]);
		$relyid=0 if(!$relyid);
		$fileext=pop(@filename);
		$filename=join(".",@filename);
		$filecount=$filename[1];
		$filecount=0 if(!$filecount);
		$filesize=(stat("$filepath"))[7];
		$filelastmod=(stat("$filepath"))[9];
		$lastmoddate=&longdate($filelastmod);
		@checktopic=&getpl($forumid,$topicid);
		unlink($filepath) if($#checktopic == 0);
		$deleted=(!-e $filepath)?'<font color="red">TRUE</font>':'<font color="blue">FALSE</font>';
	print qq~
	<tr><td align="left">$filefullname</td><td align="right">$filesize bytes</td><td align="right">$lastmoddate</td><td align="center">$deleted</td></tr>
	~;
	$attachcount++;
	$k++;
	}
	if($end != $allattachcount){
	print qq~
	<tr><td align="center" colspan="4" bgcolor="#EEEEEE"><a href="$thisprog?action=delete_no_topic&forum=$forum&eachp=$eachp&pageaction=1&start=$end">繼續删除本论坛中主题丢失的附件</a><meta http-equiv="refresh" content="2; url=$thisprog?action=delete_no_topic&forum=$forum&eachp=$eachp&pageaction=1&start=$end"></td></tr>~;
	}else{
	print qq~
	<tr><td align="center" colspan="4" bgcolor="#EEEEEE"><a href="$thisprog?forum=$forum&eachp=$eachp">本论坛中主题丢失的附件已全部删除，按此返回</a><meta http-equiv="refresh" content="2; url=$thisprog?forum=$forum&eachp=$eachp"></td></tr>~;
	}
	print qq~
	<tr><td align="center" colspan="2" bgcolor="#EEEEEE">该分论坛共有附件 $allattachcount 个 [$j - $k]</td><td align="center" bgcolor="#EEEEEE" colspan="2"></td></tr>
	</table>
	</td>
	</tr>~;
}
sub multdelete{#v3.5
	$attachdir="${imagesdir}$usrdir/$forum";
	if($forum ne ""){
		if(!-d $attachdir){
	&errorout("管理程式出错","找不到附件目录 - $attachdir");return;
		}
	}
	print qq~
	<tr>
	<td bgcolor="#EEEEEE" align=center>
	<font color="#990000"><b>删除复数附件</b>
	</td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align=center colspan=2><form action="$thisprog" method=post name=form>
	<input type="hidden" name="forum" value="$forum">
	<input type="hidden" name="start" value="checked">
	<input type="hidden" name="pageaction" value="1">
	<input type="hidden" name="action" value="multdelete">
	<input type="hidden" name="eachp" value="$eachp">
	<table width=90% cellspacing="0" cellpadding="2">
	<tr><td align="center" bgcolor="#DDDDDD"><b style="color:blue">附件名称</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">附件容量</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">上傳日期</b></td><td align="center" width="30%" bgcolor="#DDDDDD"><b style="color:blue">相关文章</b></td><td align="center" width="5" bgcolor="#DDDDDD"><b style="color:blue">选</b></td></tr>
	~;
	$allattachcount = 0;
	$delete_array = $query -> param('delete_array');
	if($delete_array ne ""){
		@delete_array = $query -> param('delete_array');
		$allattachcount = @delete_array;
	}
	foreach(@delete_array){
		$filefullname=$_;
		next if($filefullname eq "");
		$filepath="$attachdir/".$filefullname;
		my @filename=split(/\./,$filefullname);
		$fileext=pop(@filename);
		$filename=join(".",@filename);
		$filecount=$filename[1];
		$filecount=0 if(!$filecount);
		$filesize=(stat("$filepath"))[7];
		$filelastmod=(stat("$filepath"))[9];
		$lastmoddate=&longdate($filelastmod);
		my($forumid,$topicid,$relyid)=split(/\_/,$filename[0]);
		$relyid=0 if(!$relyid);
		@checktopic=&getpl($forumid,$topicid);
		if($#checktopic == 0){
			$topiclink=qq(相关文章已经丢失);
		}else{
			($topictitle,$topisstarter,$topicposttime,$topicreply,$topicview)=@checktopic;
			$topicstart=0;$orelyid=$relyid;
			if($relyid > $maxtopics){
				my ($crelyid,undef)=split(/\./,($relyid/$maxtopics));
				$topicstart=$crelyid*$maxtopics;
			}
			$relyid="bottom" if($relyid eq $topicreply);
			$topictitle_temp=&lbhz($topictitle,30);
			$topictitle_temps="&nbsp;" x (30 - length($topictitle_temp));
			$topicpostdata=(!$topicpostdata)?"Unknown":&dateformat("$topicposttime");
		$topiclink=qq(<a href="topic.cgi?forum=$forumid&topic=$topicid&start=$topicstart#$relyid" target="_blank" TITLE="$topictitle&nbsp;\n发布时间： $topicpostdata&nbsp;\n主题作者： $topisstarter&nbsp;">$topictitle_temp</a>);
		}
		if($start eq "checked"){
			$disabled=' disabled';
			unlink($filepath);
		}
	print qq~
	<tr><td align="left"><a href="$imagesurl/$usrdir/$forum/$filefullname" title="下载附件" target="_blank">$filefullname</a></td><td align="right">$filesize bytes</td><td align="right">$lastmoddate</td><td align="left">&nbsp;&nbsp;&nbsp;$topiclink$topictitle_temps</td><td align="center" width="5"><input type="checkbox" name="delete_array" value="$filefullname" checked $disabled></td></tr>
	~;
		$attachcount++;
		$k++;
	}
	if($attachcount == 0){
		print qq~
		<tr><td align="center" colspan="5" height="30" valign="middle"><br><br>最少选择一个需要删除的附件<br><br><br></td></tr>
		~;
	}else{
		if($start ne "checked"){
		print qq~<tr><td align="center" colspan="3" bgcolor="#DDDDDD">需要删除附件 $allattachcount 个</td><td align="center" bgcolor="#DDDDDD" colspan="2"><input type="submit" name="Submit" value="确定删除"></td></tr>~;
		}else{
		print qq~<tr><td align="center" colspan="3" bgcolor="#DDDDDD">共删除附件 $allattachcount 个</td><td align="center" bgcolor="#DDDDDD" colspan="2">已上附件已被完全删除</td></tr>~;
		}
	}
	print qq~
	</table></form>
	</td>
	</tr>
	<tr><td bgcolor="#FFFFFF" align="center" valign="middle" colspan="2" height="50">--<a href="$thisprog?forum=$forum&eachp=$eachp">返回</a>--</td></tr>~;
}
sub toppage{
	$attachdir="${imagesdir}$usrdir/$forum";
	if($forum ne ""){
		if(!-d $attachdir){
	&errorout("管理程式出错","找不到附件目录 - $attachdir");return;
		}
	}
	print qq~
	<tr>
	<td bgcolor="#EEEEEE" align=center>
	<font color="#990000"><b>使用说明</b>
	</td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align=center>
	　　本程序的是为了管理文章附件而设，在这里可快速删除和检查附件。<p>
	　　请在使用前注意以下几点：<p>
	<table width=80%>
	<tr><td><ol type="1">
	<li>基本变量设置中，路径的配置是否使用绝对路径。如果不是，请改成绝对路径。<p>
	<li>检查 ${imagesdir}$usrdir 目录是否设置为可读写。如果不是，请设为可读写。<p></ol>
	</td></tr>
	</table>
	</td>
	</tr>
	<tr>
	<td bgcolor="#EEEEEE" align=center>
	<font color="#990000"><b>附件管理设置</b>
	</td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align=center colspan=2>
	~;
	$eachp=20 if(!$eachp);
my $filetoopen = "$lbdir" . "data/allforums.cgi";
open(FILE, "$filetoopen");
flock(FILE, 2) if ($OS_USED eq "Unix");
my @forums = <FILE>;
close(FILE);
chomp @forums;
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
$forumlist =~ s/option value=\"$forum\"/option value=\"$forum\" selected style='color:#990000'>>/g if($forum ne "");
$selectsort{$sortt}=" selected";
$selectaord{$aord}=" selected";
	print qq~
	<table width=100%><form action="$thisprog" method=get name=form><tr><td align="right" width="15%">选择分论坛：</td><td width="*"><select name="forum" style="width:100%">$forumlist</select></td><td align="right" width="10%">每页显示：</td><td width="15%"><input type="text" name="eachp" value="$eachp" style="width:80%"> 个</td><td width="25%"><select name="sortt" style="width:65%"><option value="name"$selectsort{name}>依主题编号</option><option value="size"$selectsort{size}>依附件容量</option><option value="lastmod"$selectsort{lastmod}>依上传日期</option></select><select name="aord" style="width:35%"><option value="d"$selectaord{d}>降序</option><option value="a"$selectaord{a}>升序</option></select></td><td width="10%" align="center"><input type="submit" value="查看附件"></td></tr></form></table>
	</td>
	</tr>
	~;
	if($forum ne ""){
	print qq~
<script language="JavaScript" type="text/javascript">
var wincount=1;
function admin(forumid,topicid,replyid,countid,action){
var Win=window.open("$thisprog?action="+action+"&forum="+forumid+"&topic="+topicid+"&reply="+replyid+"&count="+countid,"openScript"+wincount,'width=400,height=200,resizable=0,scrollbars=0,menubar=0,status=1');
wincount++;
if(wincount>9999)wincount=1;
}
</script>
	<tr>
	<td bgcolor="#FFFFFF" align=center colspan=2><form action="$thisprog" method=post name=form>
	<input type="hidden" name="forum" value="$forum">
	<input type="hidden" name="start" value="unchecked">
	<input type="hidden" name="pageaction" value="1">
	<input type="hidden" name="action" value="multdelete">
	<input type="hidden" name="sortt" value="$sortt">
	<input type="hidden" name="aord" value="$aord">
	<input type="hidden" name="eachp" value="$eachp">
	<table width=90% cellspacing="0" cellpadding="2">
	<tr><td align="center" bgcolor="#DDDDDD"><b style="color:blue">附件名称</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">附件容量</b></td><td align="center" width="20%" bgcolor="#DDDDDD"><b style="color:blue">上傳日期</b></td><td align="center" width="30%" bgcolor="#DDDDDD"><b style="color:blue">相关操作</b></td><td align="center" width="5" bgcolor="#DDDDDD"><b style="color:blue">选</b></td></tr>~;
opendir(DIR,"$attachdir");
@attachfiles=grep(/^$forum\_/,readdir(DIR));
closedir(DIR);
	chomp @attachfiles;
	if($sortt eq "lastmod"){
	@attachfiles=sort lastmod @attachfiles
	}elsif($sortt eq "size"){
	@attachfiles=sort size @attachfiles
	}else{
	@attachfiles=sort name @attachfiles
	}
	@attachfiles = reverse(@attachfiles) if ($aord eq "a");
	$allattachcount=@attachfiles;
	$start=0 if(!$start);
	$end=$start+$eachp;
	$end=$allattachcount if($end > $allattachcount);
	$attachcount=0;
	$numberofpages = $allattachcount / $eachp;
	($integer,$decimal) = split(/\./,$numberofpages);
	if ($decimal > 0) { $numberofpages = $integer + 1; }
	$mypages=$numberofpages;
	$count	 = (($start/$eachp)+1);
	$countstart= $count-4;
	$countend  = $count+4;
	if($countstart <= 0){
		$addendcount=0-$countstart;
		$countstart=1;
		$countend+=$addendcount;
		$countend++;
	}
		if($countend >= ($mypages+1)){
		$addstartcount=$countend-($mypages+1);
		$countend=($mypages+1);
		$countstart-=$addstartcount;
	}
	@page_array=("",$countstart .. $countend,"");
	$pages=join("\t\t",@page_array);
	$pages=~s/\t([-0-9]+)\t/
		my $page=$+;
		my $pagestart=($page-1)*$eachp;
		my $p_link;
		if($page eq $count){
			$p_link=qq~<font color="#990000"><B>$page<\/B><\/font> ~;
		}else{
			$p_link=qq~<a href="$thisprog?forum=$forum&start=$pagestart&sortt=$sortt&aord=$aord&eachp=$eachp" class=hb>$page<\/a> ~;
		}
		$p_link="" if(int($page) <= 0 || $pagestart >= $allattachcount);
		$p_link;
	/ge;
	if ($start > "0") { 
	$beginpage=qq~<a href="$thisprog?forum=$forum&start=0&sortt=$sortt&aord=$aord&eachp=$eachp" title="首 页" ><font face=webdings >9</font></a>~; 
	$pageup=$count-1;
	$pageup1=($pageup-1)*$eachp;
	$showup = qq~<a href="$thisprog?forum=$forum&start=$pageup1&sortt=$sortt&aord=$aord&eachp=$eachp" title="第$pageup页" ><font face=webdings >7</font></a>~;
	} else {
	$beginpage=qq~<font color="#990000"><font face=webdings >9</font></font>~;
	$showup = qq~<font color="#990000"><font face=webdings >7</font></font>~;
	}
	$showend=($mypages-1)*$eachp;
	if ($count ne $mypages) { 
	$endpage=qq~<a href="$thisprog?forum=$forum&start=$showend&sortt=$sortt&aord=$aord&eachp=$eachp" title="尾 页" ><font face=webdings >:</font></a>~; 
	$pagedown=$count+1;
	$pagedown1=$count*$eachp;
	$showdown = qq~<a href="$thisprog?forum=$forum&start=$pagedown1&sortt=$sortt&aord=$aord&eachp=$eachp" title="第$pagedown页" ><font face=webdings >8</font></a> ~; 
	} else { 
	$endpage=qq~<font color="#990000"><font face=webdings >:</font></font>~;
	$showdown = qq~<font color="#990000"><font face=webdings >8</font></font>~;
	}
	$topicpages = qq~<font color=$menufontcolor>$beginpage $showup [ $pages ] $showdown $endpage</font>~;
	$j=$start+1;
	$k=$start;
	for($i=$start;$i<$end;$i++){
		$filefullname=$attachfiles[$i];
		next if($filefullname eq "");
		$filepath="$attachdir/".$filefullname;
		my @filename=split(/\./,$filefullname);
		$fileext=pop(@filename);
		$filename=join(".",@filename);
		$filecount=$filename[1];
		$filecount=0 if(!$filecount);
		$filesize=(stat("$filepath"))[7];
		$filelastmod=(stat("$filepath"))[9];
		$lastmoddate=&longdate($filelastmod);
		my($forumid,$topicid,$relyid)=split(/\_/,$filename[0]);
		$relyid=0 if(!$relyid);
		@checktopic=&getpl($forumid,$topicid);
		if($#checktopic == 0){
			$topiclink=qq([丢失]);
		}else{
			($topictitle,$topisstarter,$topicposttime,$topicreply,$topicview)=@checktopic;
			$topicstart=0;$orelyid=$relyid;
			if($relyid > $maxtopics) {
				my ($crelyid,undef)=split(/\./,($relyid/$maxtopics));
				$topicstart=$crelyid*$maxtopics;
			}
			$relyid="bottom" if($relyid eq $topicreply);
			$topicpostdata=(!$topicpostdata)?"Unknown":&dateformat("$topicposttime");
			$topiclink=qq(<a href="topic.cgi?forum=$forumid&topic=$topicid&start=$topicstart#$relyid" target="_blank" TITLE="$topictitle&nbsp;\n发布时间： $topicpostdata&nbsp;\n主题作者： $topisstarter&nbsp;">[文章]</a>);
		}
	print qq~
	<tr><td align="left"><a href="$imagesurl/$usrdir/$forum/$filefullname" title="下载附件" target="_blank">$filefullname</a></td><td align="right">$filesize bytes</td><td align="right">$lastmoddate</td><td align="center">$topiclink <a href="javascript:admin($forumid,$topicid,$orelyid,$filecount,'moveattach')">[移动]</a> <a href="javascript:admin($forumid,$topicid,$orelyid,$filecount,'copyattach')">[复制]</a> <a href="javascript:admin($forumid,$topicid,$orelyid,$filecount,'deleteattach')">[删除]</a></td><td align="center" width="5"><input type="checkbox" name="delete_array" value="$filefullname"></td></tr>
	~;
		$attachcount++;
		$k++;
	}
	if($attachcount == 0){
	print qq~
	<tr><td align="center" colspan="5" height="30" valign="middle"><br><br><br><br>该分论坛没有任何附件</td></tr>
	~;
	}else{
	print qq~
	<tr><td align="center" colspan="4" bgcolor="#EEEEEE"><a href="$thisprog?action=delete_no_topic&forum=$forum&eachp=$eachp&pageaction=1">删除本论坛中主题丢失的附件</a></td><td align="center" width="5" bgcolor="#EEEEEE"><input type="submit" name="Submit" value="删"></td></tr>
	<tr><td align="center" colspan="3" bgcolor="#DDDDDD">该分论坛共有附件 $allattachcount 个 [$j - $k]</td><td align="center" bgcolor="#DDDDDD" colspan="2">$topicpages</td></tr>
	~;
	}
	print qq~</table></form>
	</td>
	</tr>~;
	}
}
sub moveattach{
	print qq~<tr><td bgcolor="#333333" height="20"><font color="#FFFFFF">
	<b>论坛管理中心 / 移动文章附件</b>
	</td></tr>~;
	if($forum eq "" || $topic eq ""){
	&erroroutsmall("分论坛与主题编号不能为空！");return;
	}
	$attachdir="${imagesdir}$usrdir/$forum";
	if(!-d $attachdir){
	&erroroutsmall("找不到附件目录 - $attachdir");return;
	}
opendir(DIR,"$attachdir");
	if($count == 0){
@attachfiles=grep(/^$forum\_$topic\./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\./,readdir(DIR)) if($reply > 0);
	}else{
@attachfiles=grep(/^$forum\_$topic\.$count\./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\.$count\./,readdir(DIR)) if($reply > 0);
	}
closedir(DIR);
chomp @attachfiles;
	if($#attachfiles < 0){
	&erroroutsmall("找不到该附件！");return;
	}
my $filetoopen = "$lbdir" . "data/allforums.cgi";
open(FILE, "$filetoopen");
flock(FILE, 2) if ($OS_USED eq "Unix");
my @forums = <FILE>;
close(FILE);
chomp @forums;
	if($start eq "checked"){
	if($nforum eq "" || $ntopic eq ""){
	&erroroutsmall("新分论坛与主题编号不能为空！");return;
	}
	if($forum eq $nforum && $topic eq $ntopic && $reply eq $nreply){
	&erroroutsmall("新分论坛不能和旧编号相同！");return;
	}
	@checktopic=&getpl($nforum,$ntopic);
	if($#checktopic == 0){
	&erroroutsmall("找不到该主题");return;
	}elsif($nreply > $checktopic[3]){
	&erroroutsmall("找不到该回覆");return;
	}
	$nattachdir="${imagesdir}$usrdir/$nforum";
	@oldfilename=split(/\./,$attachfiles[0]);
	$fileext=pop(@oldfilename);
	$newfilename="$nforum\_$ntopic";
	$newfilename.="\_$nreply" if($nreply > 0);
	$newfilename.=".$count" if($count > 0);
	$newfilename.=".$fileext";
	if(-e "$nattachdir/$newfilename"){
	&erroroutsmall("该文章已有附件存在！");return;
	}
	if($nforum ne $forum){
move("$attachdir/$attachfiles[0]","$nattachdir/$newfilename");
	}else{
rename("$attachdir/$attachfiles[0]","$nattachdir/$newfilename");
	}
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
if($forumlist=~/<option value="$nforum">(.+?)<\/option>/){
$forumname=$1;
}
	print qq~
	<tr><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="25%" align="right">原附件名称：</td><td colspan="3">$attachfiles[0]</td></tr>
	<tr><td width="25%" align="right">新附件名称：</td><td colspan="3">$newfilename</td></tr>
	<tr><td width="25%" align="right">現所在分论坛：</td><td colspan="3">$forumname</td></tr>
	<tr><td width="25%" align="right">主题编号：</td><td width="25%">$ntopic</td><td width="25%" align="right">回覆编号：</td><td width="25%">$nreply</td></tr>
	<tr><td width="100%" colspan="4" align="center">移动完成</td></tr>
	</table>
	</td></tr>
	<script>opener.location.reload();setTimeout("self.close()",3000);</script>
	~;
	}else{
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
if($forumlist=~/<option value="$forum">(.+?)<\/option>/){
$forumname=$1;
}
$forumlist =~ s/option value=\"$forum\"/option value=\"$forum\" selected style='color:"#990000"'>>/g;
	print qq~
<script language="JavaScript" type="text/javascript">
function CheckTopic(forumid,topicid,replyid){
creplyid=replyid;
	while(creplyid > $maxtopics){
creplyid-=$maxtopics;
	}
start=creplyid*$maxtopics;
window.open("topic.cgi?forum="+forumid+"&topic="+topicid+"&start="+start+"#"+replyid);
}
</script>
	<tr><form action="$thisprog" method=post name=form><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="25%" align="right">附件名称：</td><td colspan="3">$attachfiles[0]</td></tr>
	<tr><td width="25%" align="right">所在分论坛：</td><td colspan="3">$forumname</td></tr>
	<tr><td width="25%" align="right">目标分论坛：</td><td colspan="3"><select name="nforum" style="width:100%">$forumlist</select></td></tr>
	<tr><td width="25%" align="right">目标主题编号：</td><td width="25%"><input type="text" name="ntopic" value="$topic" style="width:100%"></td><td width="25%" align="right">回覆编号：</td><td width="25%"><input type="text" name="nreply" value="$reply" style="width:100%"></td></tr>
	<tr><td width="100%" colspan="4" align="center"><input type="hidden" name="forum" value="$forum"><input type="hidden" name="topic" value="$topic"><input type="hidden" name="reply" value="$reply"><input type="hidden" name="count" value="$count"><input type="hidden" name="action" value="moveattach"><input type="hidden" name="start" value="checked"><input type="submit" value="确定移动"> <input type="button" value="检查文章" onClick="CheckTopic(this.form.nforum.value,this.form.ntopic.value,this.form.nreply.value);"></td></tr>
	</table>
	</td></form></tr>
	~;
	}
}
sub copyattach{
	print qq~<tr><td bgcolor="#333333" height="20"><font color="#FFFFFF">
	<b>论坛管理中心 / 复制文章附件</b>
	</td></tr>~;
	if($forum eq "" || $topic eq ""){
	&erroroutsmall("分论坛与主题编号不能为空！");return;
	}
	$attachdir="${imagesdir}$usrdir/$forum";
	if(!-d $attachdir){
	&erroroutsmall("找不到附件目录 - $attachdir");return;
	}
opendir(DIR,"$attachdir");
	if($count == 0){
@attachfiles=grep(/^$forum\_$topic./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\./,readdir(DIR)) if($reply > 0);
	}else{
@attachfiles=grep(/^$forum\_$topic\.$count\./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\.$count\./,readdir(DIR)) if($reply > 0);
	}
closedir(DIR);
chomp @attachfiles;
	if($#attachfiles < 0){
	&erroroutsmall("找不到该附件！");return;
	}
my $filetoopen = "$lbdir" . "data/allforums.cgi";
open(FILE, "$filetoopen");
flock(FILE, 2) if ($OS_USED eq "Unix");
my @forums = <FILE>;
close(FILE);
chomp @forums;
	if($start eq "checked"){
	if($nforum eq "" || $ntopic eq ""){
	&erroroutsmall("新分论坛与主题编号不能为空！");return;
	}
	if($forum eq $nforum && $topic eq $ntopic && $reply eq $nreply){
	&erroroutsmall("新分论坛不能和旧编号相同！");return;
	}
	@checktopic=&getpl($nforum,$ntopic);
	if($#checktopic == 0){
	&erroroutsmall("找不到该主题");return;
	}elsif($nreply > $checktopic[3]){
	&erroroutsmall("找不到该回覆");return;
	}
	$nattachdir="${imagesdir}$usrdir/$nforum";
	@oldfilename=split(/\./,$attachfiles[0]);
	$fileext=pop(@oldfilename);
	$newfilename="$nforum\_$ntopic";
	$newfilename.="\_$nreply" if($nreply > 0);
	$newfilename.=".$count" if($count > 0);
	$newfilename.=".$fileext";
	if(-e "$nattachdir/$newfilename"){
	&erroroutsmall("该文章已有附件存在！");return;
	}
copy("$attachdir/$attachfiles[0]","$nattachdir/$newfilename");
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
if($forumlist=~/<option value="$nforum">(.+?)<\/option>/){
$forumname=$1;
}
	print qq~
	<tr><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="25%" align="right">原附件名称：</td><td colspan="3">$attachfiles[0]</td></tr>
	<tr><td width="25%" align="right">新附件名称：</td><td colspan="3">$newfilename</td></tr>
	<tr><td width="25%" align="right">所在分论坛：</td><td colspan="3">$forumname</td></tr>
	<tr><td width="25%" align="right">主题编号：</td><td width="25%">$ntopic</td><td width="25%" align="right">回覆编号：</td><td width="25%">$nreply</td></tr>
	<tr><td width="100%" colspan="4" align="center">复制完成</td></tr>
	</table>
	</td></tr>
	<script>opener.location.reload();setTimeout("self.close()",3000);</script>
	~;
	}else{
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
if($forumlist=~/<option value="$forum">(.+?)<\/option>/){
$forumname=$1;
}
$forumlist =~ s/option value=\"$forum\"/option value=\"$forum\" selected style='color:"#990000"'>>/g;
	print qq~
<script language="JavaScript" type="text/javascript">
function CheckTopic(forumid,topicid,replyid){
creplyid=replyid;
	while(creplyid > $maxtopics){
creplyid-=$maxtopics;
	}
start=creplyid*$maxtopics;
window.open("topic.cgi?forum="+forumid+"&topic="+topicid+"&start="+start+"#"+replyid);
}
</script>
	<tr><form action="$thisprog" method=post name=form><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="25%" align="right">附件名称：</td><td colspan="3">$attachfiles[0]</td></tr>
	<tr><td width="25%" align="right">所在分论坛：</td><td colspan="3">$forumname</td></tr>
	<tr><td width="25%" align="right">目标分论坛：</td><td colspan="3"><select name="nforum" style="width:100%">$forumlist</select></td></tr>
	<tr><td width="25%" align="right">目标主题编号：</td><td width="25%"><input type="text" name="ntopic" value="$topic" style="width:100%"></td><td width="25%" align="right">回覆编号：</td><td width="25%"><input type="text" name="nreply" value="$reply" style="width:100%"></td></tr>
	<tr><td width="100%" colspan="4" align="center"><input type="hidden" name="forum" value="$forum"><input type="hidden" name="topic" value="$topic"><input type="hidden" name="reply" value="$reply"><input type="hidden" name="count" value="$count"><input type="hidden" name="action" value="copyattach"><input type="hidden" name="start" value="checked"><input type="submit" value="确定复制"> <input type="button" value="检查文章" onClick="CheckTopic(this.form.nforum.value,this.form.ntopic.value,this.form.nreply.value);"></td></tr>
	</table>
	</td></form></tr>
	~;
	}
}
sub deleteattach{
	print qq~<tr><form action="$thisprog" method=post name=form><td bgcolor="#333333" height="20"><font color="#FFFFFF">
	<b>论坛管理中心 / 删除文章附件</b>
	</td></tr>~;
	if($forum eq "" || $topic eq ""){
	&erroroutsmall("分论坛与主题编号不能为空！");return;
	}
	$attachdir="${imagesdir}$usrdir/$forum";
	if(!-d $attachdir){
	&erroroutsmall("找不到附件目录 - $attachdir");return;
	}
opendir(DIR,"$attachdir");
	if($count == 0){
@attachfiles=grep(/^$forum\_$topic\./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\./,readdir(DIR)) if($reply > 0);
	}else{
@attachfiles=grep(/^$forum\_$topic\.$count\./,readdir(DIR)) if($reply == 0);
@attachfiles=grep(/^$forum\_$topic\_$reply\.$count\./,readdir(DIR)) if($reply > 0);
	}
closedir(DIR);
chomp @attachfiles;
	if($#attachfiles < 0){
	&erroroutsmall("找不到该附件！");return;
	}
my $filetoopen = "$lbdir" . "data/allforums.cgi";
open(FILE, "$filetoopen");
flock(FILE, 2) if ($OS_USED eq "Unix");
my @forums = <FILE>;
close(FILE);
chomp @forums;
	if($start eq "checked"){
	unlink("$attachdir/$attachfiles[0]");
	print qq~
	<tr><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="33%">原附件名称：</td><td>$attachfiles[0]</td></tr>
	<tr><td width="33%" colspan="2" align="center">刪除完成</td></tr>
	</table>
	</td></tr>
	<script>opener.location.reload();setTimeout("self.close()",3000);</script>
	~;
	}else{
$forumlist=(join("\n",@forums))."\n";
$forumlist=~s/(.+?)\t(.+?)\t(.+?)\t(.+?)\t(.+?)\n/<option value="$1">$4<\/option>/g;
if($forumlist=~/<option value="$forum">(.+?)<\/option>/){
$forumname=$1;
}
	print qq~
	<tr><td bgcolor="#FFFFFF" align=center valign="top" height="*">
	<table width=100% cellspacing="0" cellpadding="2">
	<tr><td width="33%">附件名称：</td><td>$attachfiles[0]</td></tr>
	<tr><td width="33%">所在分论坛：</td><td>$forumname</td></tr>
	<tr><td width="33%" colspan="2" align="center"><font color=red><b>删除後是不能够复原的，请先再三考虑！</b></font></td></tr>
	<tr><td width="33%" colspan="2" align="center"><input type="hidden" name="forum" value="$forum"><input type="hidden" name="topic" value="$topic"><input type="hidden" name="reply" value="$reply"><input type="hidden" name="count" value="$count"><input type="hidden" name="action" value="deleteattach"><input type="hidden" name="start" value="checked"><input type="submit" value="确定删除"></td></tr>
	</table>
	</td></form></tr>
	~;
	}
}
sub erroroutsmall{
	my($errormsg)=shift;
	print qq~<tr><td bgcolor="#FFFFFF" align=center valign="middle" height="*"><font color=red><b>$errormsg</b></font></td></tr>~;
}
sub errorout{
	#sub errorout v2.0
	my($errortype,$errormsg)=@_;
	print qq~
	<tr>
	<td bgcolor="#EEEEEE" align=center>
	<font color="#990000"><b>$errortype</b>
	</td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align="center"><font color=red>$errormsg</font></td>
	</tr>
	<tr>
	<td bgcolor="#FFFFFF" align="center" height="100" valign="bottom">-- <a href="$thisprog">返回</a> --</td>
	</tr>
	~;
}
sub getpl{
	my($forumid,$topicid)=@_;
	my $plfile="${lbdir}forum$forumid/$topicid.pl";
	if(-e $plfile){
	&winlock($plfile) if ($OS_USED eq "Nt");
	open (ENT, $plfile);
	flock(ENT, 2) if ($OS_USED eq "Unix");
	$in = <ENT>;
	close (ENT);
	&winunlock($plfile) if ($OS_USED eq "Nt");
	my ($ptopicid, $ptopictitle, $ptopicdescription, $pthreadstate, $pthreadposts ,$pthreadviews, $pstartedby, $pstartedpostdate, $plastposter, $plastpostdate, $pposticon,$pposttemp) = split(/\t/,$in);
	return ($ptopictitle,$pstartedby,$pstartedpostdate,$pthreadposts,$pthreadviews);
	}else{
	return ("undef");
	}
}
sub size{
	(stat("$attachdir/$b"))[7] <=> (stat("$attachdir/$a"))[7];
}
sub lastmod{
	(stat("$attachdir/$b"))[9] <=> (stat("$attachdir/$a"))[9];
}
sub name{
	my @aa=split(/\./,$a);my @an=split(/\_/,$aa[0]);
	my @ba=split(/\./,$b);my @bn=split(/\_/,$ba[0]);
	$bn[1] <=> $an[1];
}