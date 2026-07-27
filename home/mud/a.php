<?
$output=passthru('cat /var/log/webmud/newmud.log|grep chat'); 
echo "$output"; 

?> 
