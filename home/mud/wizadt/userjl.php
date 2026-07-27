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
$name = 'cat /var/log/webmud/newmud.log|grep '.$name;
$output=passthru($name); 
echo "$output"; 
}
}
?>
<p><a href="javascript:history.back(-1)">返回</a></p>