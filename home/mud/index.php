<html>
<head>
<title>仗剑江湖</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<meta content="no-cache">
</head>
<body bgcolor="#FFFFFF" background="/mud/images/bg1.gif">
<p align="center"><img src='/mud/images/13.gif' border=0 width=300></p>
<form method="post" action="/cgi-bin/mud/login2">
<table border=0 align=center><tr><td>登录MUD:</td><td>目前在线(
<?
$fd = fopen("/home/mud/data/playercount.dat", "r");
echo fread($fd, 512);
fclose($fd);
?>
)
</td></tr>
<tr><td>代号： </td><td>
    <input type="text" name="name">
  </td></tr><tr><td>
 密码： </td><td>
    <input type="password" name="password">
  </td></tr><tr><td>
    <input type="submit" name="Submit" value="进入">
  </td></tr>
</table>
</form>
<p>&nbsp; </p>
<p align="center"><font color='red'>新增<a href='/home/mud/level.php'>武功与经验点数对比程序</a>。</font></p>
<p align="center"><font color='red'>江湖新增域名为<a href='http://mud.senmee.com/'>http://mud.senmee.com/</a>，由牛蛙玩家提供。</font></p>
<p align="center"><a href=/cgi-bin/mud/register>注册江湖</a></p>
<p align="center"><a href=http://zjjh.xihai.com>江湖论坛</a></p>
<p align="center"><a href=/home/mud/exptop.php>江湖风云榜</a></p>
<p align="center"><a href=/home/mud/moneytop.php>江湖富豪榜</a></p>
<p align="center"><a href=/home/mud/upass.php>密码修改</a><br></p>
<p align="center"><a href='/home/mud/ksxz.htm'>仗剑江湖快速行走</a></p>
<p align="center"><a href='/home/mud/wpss.html'>仗剑江湖NPC查找</a></p>
<p align="center"><a href='/home/mud/qn.htm '>仗剑江湖潜能计算</a></p>
</body>
</html>
