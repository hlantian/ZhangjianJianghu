#class=YRoom
begin of YPropertyGroup
string values:
名字=钟楼
描述=@LONG
    这里是长安城的中心，眼前是一座青砖造起的高大阁楼，上面建有铜钟，有专人看守。多少年来，晨钟暮鼓是这个城市和谐安宁的象征，伴随着一下下的撞击，熟悉的钟声悠悠地飘到城市的每个角落。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>,<a href='javascript:sendmsg("s")'>南</a>,<a href='javascript:sendmsg("in")'>里面</a>。
LONG
北=北大街
西=西大街1
东=东大街
南=南大街1
里面=仓库中心
NPC列表=游客2 游客3 黑衣人 巡捕9
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/游客2
object=npc/游客3
object=npc/黑衣人
object=npc/巡捕9
end of YObjectGroup