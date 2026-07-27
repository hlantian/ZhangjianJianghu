<?
session_start();
session_register("qx");
if ($qx==''){
Header("Location:index.php");
}
else{
if ($name==''){
echo "必须填写用户名";
}
else{
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$sql="select backpass,email from mytest where name='".$name."'";
$rst = mysql_query($sql,$server);
$row = mysql_fetch_row($rst);
if ($email==''){$email=$row[1]; }
mail($email,$name."你的江湖密码",$row[0],"from:gongliwei@163.com");
echo "密码找回成功！";
}
}
?>