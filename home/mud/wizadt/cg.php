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
<title>玩家命令记录程序</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
</head>
<body>
<p align=center>玩家命令记录程序</p>
<form name="form1" action="userjl.php" method="post">
<table border=1 align="center">
<tr>
<td align="right">用户名</td><td><input name="name" type="text"></td>
</tr>
<tr>
<td align="center" colspan="2"><input type="submit" name="submit" value="确认"></td>
</tr>
</table>
</form>
</body>
</html>
<?
}
?>