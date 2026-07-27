<?
$fd = fopen("/home/mud/data/playercount.dat", "r");
echo fread($fd, 512);
fclose($fd);
?>