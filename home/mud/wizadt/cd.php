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
echo "$bb";
echo "  ";
while ($buffer = fgets($fd, 4096)) {
$tok = strtok($buffer," ");
$i=strspn('object=thing',$tok);
if($i == 12){
$aa = strlen($tok);
$cc = substr($tok,12,$aa - 12);
echo "$cc";
}
}
fclose($fd);
echo "<br>";
//结束
}
}
$file_list .= "";
closedir($dir);
}
?>