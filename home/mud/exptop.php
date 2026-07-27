<?
$server = mysql_connect("localhost","root","yinglei$");
mysql_select_db("lp",$server);
$sql = "delete from exp";
mysql_query($sql,$server) or die($sql.'出错');
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
$i=strspn('经验',$tok);
if($i == 4){
$len = strlen($file_name) - 8;
$bb = substr($file_name,0,$len);
$aa = strchr($tok,"=");
$aa = substr($aa, 1, -1); 
$cc = substr($tok,4,1);
if ($aa > 3000000 and $cc == "="){
$sql = "insert into exp values('".$bb."',".$aa.")";
mysql_query($sql,$server) or die($sql.'出错');
}
}
}
fclose($fd);
//结束

}
}?>

<html>
<head>
<title>江湖风云榜</title>
<META http-equiv=Content-Type content="text/html; charset=gb2312"><LINK 
href="http://www.qzmms.com/mud/images/bamboo.css" type=text/css rel=stylesheet>
</head>
<body bgcolor="#FAE6A9">
<p align=center><font color="#FF0000" style="font-size: 9pt">江湖风云榜</font></p>
<font color="#FF9933" style="font-size: 9pt">
<?
    echo '<table border="0" cellspacing="0" cellpadding="0" align="center">';
    echo '<tr><td>排名</td><td>名字</td></tr>';
    $i = 1;    
    $sql = "select name,exp from exp order by exp desc limit 10";
    $rst = mysql_query($sql);
    while($row1=mysql_fetch_array($rst)){
	echo '<tr><td>'.$i.'</td><td>'.$row1[0].'</td></tr>';
	$i++;
       }
    echo '</table>';
    mysql_free_result($rst);
?>
</font>
<p align="center"><font color="#FF9933" style="font-size: 9pt">风云榜随时更新，请时刻关注。</font></p>
</body>
</html>

<?
$file_list .= "";
mysql_close($server);

?>