<?
if ($dj==''){
echo "必须填写当前等级";
}
if ($wx==''){
echo "wx not is null!";
}
if ($cs==''){
echo "cs not is null!";
}

if ($dj >= 0 && wx >= 0 && cs >= 0){
$exp = ($dj + 1)*($dj + 1)*10+1;
if ($cs < 500){
$amin = $wx;
}
else{
$amin = $wx + $wx/2;
}
$bmax = ceil($exp/$amin);
$amax = $wx*2;
$bmin = ceil($exp/$amax);

$dj = $dj + 1;
echo "$dj";
echo "级武功需要的升级经验点数为：max qn";
echo "$bmax";
echo ",min qn";
echo "$bmin";
}
?>
<p>
<a href="javascript:history.back(-1)">返回</a></p>
