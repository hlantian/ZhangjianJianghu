<?
session_start();
session_register("qx");
if ($qx != 100){
echo "你的权限不够，不能使用本程序！";
}
else{
?>
<html>
<head>
<title>玩家密码找回程序</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
</head>
<body>
<p align=center>玩家密码找回程序</p>
<form name="form1" action="emailqh.php" method="post">
<table border=1 align="center">
<tr>
<td align="right">用户名</td><td><input name="name" type="text"></td>
</tr>
<tr>
<td align="right">信箱：</td><td><input name="email" type="text"></td>
</tr>
<tr>
<td align="center" colspan="2"><input type="submit" name="submit" value="确认"></td>
</tr>
</table>
</form>
<p align="center">不填写邮箱就默认为玩家注册信箱！</p>
<p align="center"><font color="red">警告：所有巫师请妥善使用这些程序，如果发现利用程序造成一切负面后果，立刻开除！</red></p>
</body>
</html>
<?
}
?>