<?
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$dir_name = "/home/mud/data/player/";
$dir = opendir($dir_name);
$file_list = "";
while ($file_name = readdir($dir)) {
if (($file_name != ".") && ($file_name != "..")) {
$file_list .= "$file_name";

//开始读文件内容
$fd = fopen("/home/mud/data/player/".$file_name, "r");
while ($buffer = fgets($fd, 4096)) {
$tok = strtok($buffer," ");
$i=strspn('读书写字',$tok);
if($i == 8){
$len = strlen($file_name) - 8;
$bb = substr($file_name,0,$len);
$aa = strchr($tok,"=");
$aa = substr($aa, 1, -1); 
$cc = substr($tok,8,1);
if ($aa > 150 and $cc == "="){
echo "$bb  ";
echo "读书写字=";
echo  "$aa";
echo "<br>";
}
}
}
fclose($fd);
//结束

}
}
$file_list .= "";
mysql_close($server);
?>