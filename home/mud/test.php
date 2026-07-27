<?
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$dir_name = "/home/mud/data/player/";
$dir = opendir($dir_name);
$i = 1;
while ($file_name = readdir($dir)) {
if (($file_name != ".") && ($file_name != "..")) {
clearstatcache();
if (date("Y-m-d H:i:s", filectime($dir_name.$file_name)) < date("Y-m-d H:i:s",mktime(0,0,0,1,1,2007))){

//开始读文件内容
$fd = fopen($dir_name.$file_name, "r");
while ($buffer = fgets($fd, 4096)) {
$tok = strtok($buffer," ");
$n=strspn('经验',$tok);
if($n == 4){
$len = strlen($file_name) - 8;
$bb = substr($file_name,0,$len);
$aa = strchr($tok,"=");
$aa = substr($aa, 1, -1); 
$cc = substr($tok,4,1);
if ($aa < 1000 and $cc == "="){
echo $bb." ".date("Y-m-d H:i:s", filectime($dir_name.$file_name))." ";
echo $aa."<br>";
$sql = "delete from mytest where name = '".$bb."'";
mysql_query($sql,$server) or die($sql.'出错');
unlink($dir_name.$file_name);
$i++;
}
}
}
fclose($fd);
//结束
}
}
}
echo $i."<br>";
echo date("Y-m-d H:i:s",mktime(0,0,0,1,1,2007));
mysql_close($server);
?>