<html>
<head>
<title>密码修改</title>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
</head>
<body>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p align="center">
<?php
if ($submit != ""){
if ($pass1 != $pass2){
	echo "两次输入的密码不一致！";
}
else{
$passwd = trim($passwd);
$i=strspn(' ',$passwd);
if ($i > 0){
	echo "密码中带有非法字符！";
}
else{
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$sql="select count(*) from mytest where name='".$name."' and passwd=password('".$passwd."')";
$rst = mysql_query($sql,$server);
$row = mysql_fetch_row($rst); 
if ($row[0] > 0){
$ip=$REMOTE_ADDR;
$sql = "update mytest set passwd=password('".$pass1."'),backpass='".$pass1."',firstday=now(),ipdres='".$ip."' where name='".$name."' and passwd=password('".$passwd."')";
mysql_query($sql,$server) or die($sql.'出错');
echo "修改成功！";
}
else{
echo "用户名或密码错误！";
}
}
}
}
?>
</p>
<p align="center"><a href="/">返回江湖首页</a></p>
<p align="center"><a href="javascript:history.back(-1)">后退</a></p>
</body>
</html> 