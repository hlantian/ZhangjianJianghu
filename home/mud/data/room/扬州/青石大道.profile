#class=YHideDoorRoom
begin of YPropertyGroup
string values:
名字=青石大道
准备命令=推门
隐藏前进命令=进入
限制前进方向=阿木家
准备成功后显示=你成功推开阿木家的门
成功通过后显示=你成功的进入了阿木家
失败通过后显示=对不起，他人不在，请联系后再来！
进入条件=绰号
准备条件=花
花=龙女花
准备失败后显示=你推不开这扇大门
阿木家=/room/诸葛府/惊雁宫大门
描述=@LONG
    你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。南边就是扬州城了<br>
   这里明显的出口是 <a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("s")'>南</a>
LONG
北=青石大道1
南=北门
long values:
绰号=<font color=#3366cc>回家</font>
float values:
end of YPropertyGroup
begin of YObjectGroup
end of YObjectGroup
