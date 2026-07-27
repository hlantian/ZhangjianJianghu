<?
if ($dj==''){
echo "必须填写当前等级";
}
else{
if ($dj >= 0){
$exp = ($dj + 1)*($dj + 1)*10+1;
$dj = $dj + 1;
echo "$dj";
echo "级武功需要的升级经验点数为：";
echo "$exp";
}}
?>
<p>
<a href="javascript:history.back(-1)">返回</a></p>