<?
if ($rm==''){
echo "必须填写人名";
}
else{
$output=passthru('cat /var/log/webmud/newmud.log|grep '."$rm"); 
echo "$output"; 
?> 
<p>
<a href="javascript:history.back(-1)">返回</a></p>