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
<title>巫师监视程序</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
</head>
<body>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p align="center">程序列表</p>
<p align="center"><a href="ce.php">存款监视</a></p>
<p align="center"><a href="cf.php">身上金子监视</a></p>
<p align="center"><a href="cd.php">物品监视</a></p>
<p align="center"><a href="cc.php">玩家密码找回</a></p>
<p align="center"><a href="cb.php">玩家金钱对比程序</a></p>

<p align="center"><font color="red">警告：所有巫师请妥善使用这些程序，如果发现利用程序造成一切负面后果，立刻开除！</red></p>
<?
}
?>