<?
session_start();
session_register("qx");
?>
<?
if ($submit != ""){
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$sql="select count(*) from mytest where name='".$name."' and passwd=password('".$passwd."')";
$rst = mysql_query($sql,$server);
$row = mysql_fetch_row($rst); 
if ($row[0] > 0){
$fd = fopen("/home/mud/data/player/".$name.".profile", "r");
while ($buffer = fgets($fd, 4096)) {
$tok = strtok($buffer," ");
$i=strspn('玩家级别',$tok);
if($i == 8){
$aa = strlen($tok);
$cc = substr($tok,9,$aa - 8);
if ($cc > 0 ){
$qx = $cc;
Header("Location:lb.php");
}
else{
$sql = "insert into playerbug values('".$name."',now())";
mysql_query($sql,$server) or die($sql.'出错');
echo "注意这是巫师登陆程序，你的ID已经被记录，请等待巫师处罚！";
}
}
}
fclose($fd);
}
else{
echo "用户名或密码错误！";
}
}
mysql_close($server);
?>
