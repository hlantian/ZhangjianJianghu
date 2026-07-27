#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

$maxpoststr = "" if ($maxpoststr eq 0);
$maxpoststr = 100 if (($maxpoststr < 100)&&($maxpoststr ne ""));
if ($emoticons eq "on") { $emoticonslink = qq~<input CHECKED name=inshowemoticons type=checkbox value=yes>使用表情字符转换？~; }
if ($emailfunctions eq "on") {
    if ($innotify eq "yes") { $requestnotify = qq~<input name=notify type=checkbox value=yes checked>有回复时使用邮件通知您？<br>~; }
	               else { $requestnotify = qq~<input name=notify type=checkbox value=yes>有回复时使用邮件通知您？<br>~;}
}
if ($canchgfont ne "no") {
    $fontpost = qq~<input type=checkbox name="inshowchgfont" value="yes">使用字体转换？<br>~;
} else {
    undef $fontpost;
}
if ($idmbcodestate eq "on") {
    $idmbcodestates = qq~<input type=checkbox name="uselbcode" value="yes" checked>使用 LeoBBS 标签？<BR>~;
} else {
    $idmbcodestates = "";
}

$maxpoststr = "(帖子中最多包含 <B>$maxpoststr</B> 个字符)" if ($maxpoststr ne "");
$output .= qq~<form action=post.cgi method=post name="FORM" enctype="multipart/form-data">
<input type=hidden name=action value=addreply>
<input type=hidden name=forum value=$inforum>
<input type=hidden name=topic value=$intopic>
<table cellPadding=5 cellSpacing=1 width=$tablewidth bgcolor=$tablebordercolor align=center>
<tr><td bgcolor=$titlecolor width=220 $catbackpic><font color=$fontcolormisc><b>快速回复主题:</b></font></td><td bgcolor=$titlecolor width=500 $catbackpic> <font color=$fontcolormisc>$topictitletemp</font></td></tr>
<tr><td bgcolor=$miscbacktwo colspan=3><font color=$titlefontcolor>您目前的身份是： <font color=$fonthighlight><B><u>$inmembername</u></B></font> ，如果要使用其他用户身份，请在下面输入用户名和密码。如果不想改变用户身份，请留空。</td></tr>
<tr><td bgcolor=$miscbackone><font color=$fontcolormisc><b>输入用户名和密码:</b></font></td><td bgcolor=$miscbackone> <font color=$fontcolormisc><b>用户名</b>: <input type=text name=membername> <span onclick="javascript:location.href='register.cgi?forum=$inforum'" style=cursor:hand>没有注册？</span>　<b>密码:</b> <input type=password name=password> <a href=profile.cgi?action=lostpass style=cursor:help>忘记密码？</a></font></td></tr>
~;

if (($allowattachment ne "no")||($mymembercode eq "ad")||($mymembercode eq 'smo')||($myinmembmod eq "yes")) {
    $addtypedisp = $addtype;
    $addtypedisp =~ s/\, /\,/gi;
    $addtypedisp =~ s/ \,/\,/gi;
    $addtypedisp =~ tr/A-Z/a-z/;
    my @addtypedisp = split(/\,/, $addtypedisp);
    $addtypedisp = "<select><option value=#>支持类型：</option><option value=#>----------</option>";
    foreach (@addtypedisp) {
	chomp $_;
	next if ($_ eq "");
        $addtypedisp .= qq~<option>$_</option>~;
    }
    $addtypedisp .= qq~</select>~;
    $uploadreqire = "" if ($uploadreqire <= 0);
    $uploadreqire = "<BR>发帖数要大于 <B>$uploadreqire</B> 篇(认证用户不限)" if ($uploadreqire ne "");
    $output .= qq~<tr><td bgcolor=$miscbackone><b>上传附件或图片</b> (最大容量 <B>$maxupload</B>KB)$uploadreqire</td><td bgcolor=$miscbackone colspan=2><input type="file" size=45 name="addme">　　$addtypedisp</td></tr>~;
}
$output .= qq~
<tr><td bgcolor=$miscbacktwo valign=top><font color=$fontcolormisc><b>选项</b> $maxpoststr<br><BR>
$idmbcodestates
<input CHECKED name=inshowsignature type=checkbox value=yes>显示您的签名？<br>
$requestnotify$emoticonslink<BR>$fontpost</font></td>
<td bgcolor=$miscbacktwo width=*> <textarea cols=75 name=inpost onKeyDown=ctlent() rows=8></textarea><br>
 <INPUT name=Submit onclick="return clckcntr();" type=submit value="发 表 回 复">　<input type=button value="预 览 内 容" name=Button onclick=gopreview()>　<INPUT name=Clear type=reset value="清 除">　　[使用 Ctrl+Enter 直接提交贴子]
</td></tr></table></form>
<form name=preview action=preview.cgi method=post target=preview_page><input type=hidden name=body value=""><input type=hidden name=forum value="$inforum"></form>
<script>
function gopreview(){
document.preview.body.value=document.FORM.inpost.value;
var popupWin = window.open('preview.cgi', 'preview_page', 'scrollbars=yes,width=500,height=300');
document.preview.submit()
}
</script>
~;
1;
