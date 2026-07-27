<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta name="GENERATOR" content="Microsoft FrontPage 4.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<title>仗剑江湖</title>
</head>

<script LANGUAGE="JavaScript"><!--
step = 0;
obj = new Image();
function anim(xp,xk,smer) //smer = direction
{
obj.style.left = x;
x += step*smer;
if (x>=(xk+xp)/2) {
if (smer == 1) step--;
else step++;
}
else {
if (smer == 1) step++;
else step--;
}
if (x >= xk) {
x = xk;
smer = -1;
}
if (x <= xp) {
x = xp;
smer = 1;
}
// if (smer > 2) smer = 3;
setTimeout('anim('+xp+','+xk+','+smer+')', 50);
}
function moveLR(objID,movingarea_width,c)
{
if (navigator.appName=="Netscape") window_width = window.innerWidth;
else window_width = document.body.offsetWidth;
obj = document.images[objID]; 
image_width = obj.width;
x1 = obj.style.left;
x = Number(x1.substring(0,x1.length-2));
if (c == 0) {
if (movingarea_width == 0) {
right_margin = window_width - image_width;
anim(x,right_margin,1);
}
else {
right_margin = x + movingarea_width - image_width; 
if (movingarea_width < x + image_width) window.alert("No space for moving!");
else anim(x,right_margin,1);
}
}
else {
if (movingarea_width == 0) right_margin = window_width - image_width;
else {
x = Math.round((window_width-movingarea_width)/2);
right_margin = Math.round((window_width+movingarea_width)/2)-image_width;
}
anim(x,right_margin,1);
} 
} 
//-->
</script>

<bgsound loop=-1 src="cg-s01.mid">
<SCRIPT LANGUAGE="JavaScript">
var isNS = ((navigator.appName == "Netscape") && (parseInt(navigator.appVersion) >= 4));
var _all = '';
var _style = '';
var wwidth, wheight;
var ydir = '++';
var xdir = '++';
var id1, id2, id3;
var x = 1;
var y = 1;
var x1, y1;
if(!isNS) {
_all='all.';
_style='.style';
}
function getwindowsize() {
clearTimeout(id1);
clearTimeout(id2);
clearTimeout(id3);
if (isNS) {
wwidth = window.innerWidth - 55;
wheight = window.innerHeight - 50;
} else {
wwidth = document.body.clientWidth - 55;
wheight = document.body.clientHeight - 50;
}
id3 = setTimeout('randomdir()', 20000);
animate();
}
function randomdir() {
if (Math.floor(Math.random()*2)) {
(Math.floor(Math.random()*2)) ? xdir='--': xdir='++';
} else {
(Math.floor(Math.random()*2)) ? ydir='--': ydir='++';
}
id2 = setTimeout('randomdir()', 20000);
}
function animate() {
eval('x'+xdir);
eval('y'+ydir);
if (isNS) {
pic1.moveTo((x+pageXOffset),(y+pageYOffset))
} else {
pic1.pixelLeft = x+document.body.scrollLeft;
pic1.pixelTop = y+document.body.scrollTop;
}
if (isNS) {
if (pic1.top <= 5+pageYOffset) ydir = '++';
if (pic1.top >= wheight+pageYOffset) ydir = '--';
if (pic1.left >= wwidth+pageXOffset) xdir = '--';
if (pic1.left <= 5+pageXOffset) xdir = '++';
} else {
if (pic1.pixelTop <= 5+document.body.scrollTop) ydir = '++';
if (pic1.pixelTop >= wheight+document.body.scrollTop) ydir = '--';
if (pic1.pixelLeft >= wwidth+document.body.scrollLeft) xdir = '--';
if (pic1.pixelLeft <= 5+document.body.scrollLeft) xdir = '++';
}
id1 = setTimeout('animate()', 30);
}
</script>

<bgsound loop=-1 src="cg-s01.mid">
<body onLoad="getwindowsize()" onresize="getwindowsize()" text=#000000 vLink=#800080 aLink=#0000ff link=#0000ff bgColor=#808000 
background="">
<SCRIPT language=JavaScript1.2>
var snowsrc="4.GIF";
var no = 10;
var ns4up = (document.layers) ? 1 : 0;
var ie4up = (document.all) ? 1 : 0;
var dx, xp, yp;
var am, stx, sty;
var i, doc_width = 800, doc_height = 600;
if (ns4up) {
doc_width = self.innerWidth;
doc_height = self.innerHeight;
} else if (ie4up) {
doc_width = document.body.clientWidth;
doc_height = document.body.clientHeight;
}
dx = new Array();
xp = new Array();
yp = new Array();
am = new Array();
stx = new Array();
sty = new Array();
for (i = 0; i < no; ++ i) {  
dx[i] = 0;
xp[i] = Math.random()*(doc_width-50);
yp[i] = Math.random()*doc_height;
am[i] = Math.random()*20;
stx[i] = 0.02 + Math.random()/10;
sty[i] = 0.7 + Math.random();
if (ns4up) {
if (i == 0) {
document.write("<layer name=\"dot"+ i +"\" left=\"15\" top=\"15\" visibility=\"show\"><a href=\"http://www.sunv.com/\"><img src='"+snowsrc+"' border=\"0\"></a></layer>");
} else {
document.write("<layer name=\"dot"+ i +"\" left=\"15\" top=\"15\" visibility=\"show\"><img src='"+snowsrc+"' border=\"0\"></layer>");
}
} else if (ie4up) {
if (i == 0) {
document.write("<div id=\"dot"+ i +"\" style=\"POSITION: absolute; Z-INDEX: "+ i +"; VISIBILITY: visible; TOP: 15px; LEFT: 15px;\"><a href=\"http://dynamicdrive.com\"><img src='"+snowsrc+"' border=\"0\"></a></div>");
} else {
document.write("<div id=\"dot"+ i +"\" style=\"POSITION: absolute; Z-INDEX: "+ i +"; VISIBILITY: visible; TOP: 15px; LEFT: 15px;\"><img src='"+snowsrc+"' border=\"0\"></div>");
}
}
}
function snowNS() { 
for (i = 0; i < no; ++ i) {
yp[i] += sty[i];
if (yp[i] > doc_height-50) {
xp[i] = Math.random()*(doc_width-am[i]-30);
yp[i] = 0;
stx[i] = 0.02 + Math.random()/10;
sty[i] = 0.7 + Math.random();
doc_width = self.innerWidth;
doc_height = self.innerHeight;
}
dx[i] += stx[i];
document.layers["dot"+i].top = yp[i];
document.layers["dot"+i].left = xp[i] + am[i]*Math.sin(dx[i]);
}
setTimeout("snowNS()", 10);
}
function snowIE() {
for (i = 0; i < no; ++ i) {
yp[i] += sty[i];
if (yp[i] > doc_height-50) {
xp[i] = Math.random()*(doc_width-am[i]-30);
yp[i] = 0;
stx[i] = 0.02 + Math.random()/10;
sty[i] = 0.7 + Math.random();
doc_width = document.body.clientWidth;
doc_height = document.body.clientHeight;
}
dx[i] += stx[i];
document.all["dot"+i].style.pixelTop = yp[i];
document.all["dot"+i].style.pixelLeft = xp[i] + am[i]*Math.sin(dx[i]);
}
setTimeout("snowIE()", 10);
}
if (ns4up) {
snowNS();
} else if (ie4up) {
snowIE();
}
</SCRIPT>

<SCRIPT language=JavaScript>
var msg  = "欢迎进入仗剑江湖！！！ " ;
var interval = 100
var spacelen = 120;
var space10=" ";
var seq=0;
function Scroll() {
len = msg.length;
window.status = msg.substring(0, seq+1);
seq++;
if ( seq >= len ) { 
seq = 0; 
window.status = '';
window.setTimeout("Scroll();", interval );
}
else
window.setTimeout("Scroll();", interval );
} 
Scroll();
</SCRIPT>

<DIV id=ihomebgsound style="VISIBILITY: hidden; POSITION: absolute" loop="-1" 
src="cg-s01.mid"></DIV>
<TABLE borderColor=#ffffff width="100%" border=1>
  <TBODY>
  <TR>
    <TD width="59%" rowSpan=14>
      <P> 
<div id="pic1" style="position:absolute; visibility:visible; left:0px; top:0px; z-index:auto">
<img src="13.gif" border="0">
</div>
<script language="javascript">
var pic1=eval('document.'+_all+'pic1'+_style);
</script>
<IMG height=447 src="jh.jpg" width=564 border=0></P></TD></TR>
  <TR>
    <TD align=middle width="41%"><A href="/fzgj.rar" target=_blank>辅助工具下载</A><br>
      </TD></TR>
  <TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/j2re-1_4_2_04-windows-i586-p.exe" 
      target=_blank><B>java虚拟机</B></A><br> 
      xp用户无法登陆请先下载安装
      </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/cgi-bin/mud/register" 
      target=_blank><B>注册帐号</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/home/mud/upass.php" 
      target=_blank><B>密码修改</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/home/mud/ksxz.htm" 
      target=_blank><B>快速行走</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/home/mud/wpss.html" 
      target=_blank><B>NPC搜索</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A href="/mud/help.htm" 
      target=_blank><B>江湖攻略</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><B><A 
      href="/home/mud/exptop.php" target=_blank>风云榜</A></B> 
    </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/home/mud/moneytop.php" 
      target=_blank><B>富豪榜</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A href="/mud/qn.htm" 
      target=_blank><B>潜能计算</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="/home/mud/level.php" 
      target=_blank><B>武功与经验对比</B></A> </TD></TR>
  <TR>
    <TD align=middle width="41%"><A 
      href="http://zjjh.xihai.com/" 
      target=_blank><B>江湖论坛</B></A> </TD>
  </TR></TBODY></TABLE>
<form method="post" action="/cgi-bin/mud/login1">
<TABLE width="100%" border=1>
  <TBODY>
  <TR>
<TD borderColor=#ffffff align=middle width="53%"><B><FONT color=#000080 size=3>目前在线
<?
$fd = fopen("/home/mud/data/playercount.dat", "r");
echo fread($fd, 512);
fclose($fd);
?>
人</FONT></B> 
</td></TR>  <TR>
    <TD borderColor=#ffffff align=middle width="53%">
      <B><FONT color=#000080 size=3>用户名:</FONT><FONT 
      color=#000080 size=5> </FONT><FONT color=#000080 size=3><INPUT class=b 
      style="FONT-SIZE: 12px; WIDTH: 122px; HEIGHT: 22px" maxLength=11 size=8 
      name=name>&nbsp;&nbsp; 密码: <INPUT class=b 
      style="FONT-SIZE: 12px; WIDTH: 115px; HEIGHT: 22px" type=password 
      maxLength=11 size=8 name=password>&nbsp;&nbsp;</FONT><FONT color=#000080 
      size=5><input type="submit" name="Submit" value="登陆"></FONT></B></TD></TR>
  <TR>
    <TD borderColor=#ffffff align=middle width="53%"><B><FONT color=#993300 
      size=4>网页制作：烈焰狂龙&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;QQ:3627528</FONT></B> 
    </TD></TR></TBODY></TABLE> 
</form>
</BODY>  
  
</html>  
