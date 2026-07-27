<?
session_start();
session_register("qx");
if ($qx==''){
Header("Location:index.php");
}
else{
?>
<html>
<head>
<title>玩家金钱对比程序</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
</head>
<body>
<p align=center>玩家金钱对比程序</p>
<form name="form1" action="moneyjs.php" method="post">
<table border=1 align="center">
<tr>
<td align="right">用户名</td><td><input name="name" type="text"></td>
</tr>
<tr>
<td align="center" colspan="2"><input type="submit" name="submit" value="确认"></td>
</tr>
</table>
</form>
<p align="center">使用本程序前先查看用户存款和身上携带金子程序，本程序的数据是根据那两个程序换算出来的。</p>
</body>
</html>
<?
}
?>