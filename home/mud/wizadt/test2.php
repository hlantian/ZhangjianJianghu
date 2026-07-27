<?
session_start();
session_register("qx");
if ($qx==''){
Header("Location:index.php");
}
else{
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
$tok = strtok($buffer," ");
$i=strspn('九阴白骨爪',$tok);
if($i == 10){
$aa = strchr($tok,"=");
$aa = substr($aa, 1, -1); 
echo "$bb";
echo "=";
echo  "$tok";
echo "<br>";
//结束
}
}
}
}
$file_list .= "";
closedir($dir);
}
?>