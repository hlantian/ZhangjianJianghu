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
$sql="select * from moneytop where name='".$name."' order by inday";
$rst = mysql_query($sql,$server);
echo $name.'<br>';
while($row=mysql_fetch_array($rst)){
if ($row[0]==''){
echo "该玩家没有金钱记录！";
}
else{
echo $row[2].'   '.$row[1].'<br>';
}
}
}
}
?>
<p><a href="javascript:history.back(-1)">返回</a></p>