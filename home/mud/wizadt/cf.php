<?
session_start();
session_register("qx");
if ($qx==''){
Header("Location:index.php");
}
else{
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$sql = "delete from money where type='2'";
mysql_query($sql,$server) or die($sql.'出错');
$dir_name = "/home/mud/data/player/";
$dir = opendir($dir_name);
$file_list = "";
while ($file_name = readdir($dir)) {
if (($file_name != ".") && ($file_name != "..")) {
$file_list .= "$file_name";

//开始读文件内容
$fd = fopen("/home/mud/data/player/".$file_name, "r");
$len = strlen($file_name) - 8;
$bb = substr($file_name,0,$len);
while ($buffer = fgets($fd, 4096)) {
$i=strspn('object=thing/金子 ',$buffer);
if($i == 18){
$cc = substr($buffer,18,10);
if ($cc > 0){
echo "$bb";
echo "=";
echo "$cc";
$sql = "insert into money values('".$bb."',".$cc.",'2')";
mysql_query($sql,$server) or die($sql.'出错');
echo "<br>";
}
}
}
fclose($fd);
//结束
}
}
$file_list .= "";
closedir($dir);
mysql_close($server);
}
?>