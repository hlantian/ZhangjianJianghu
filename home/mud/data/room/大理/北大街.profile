#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=北大街
描述=@LONG
    这里是大理城的街道，地上扫的一尘不染。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>,<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("e")'>东</a>。
LONG
南=城中心
北=北大街1
东=大理客栈
NPC列表=巡捕6
禁止方向列表=南 北
老板名字=巡捕6
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕6
end of YObjectGroup