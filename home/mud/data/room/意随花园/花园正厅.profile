#class=YRoom
begin of YPropertyGroup
string values:
名字=花园正厅
描述=@LONG
    这里是花园入口大厅，四周随意的布置了几盆鲜花。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=花园1
南=大门口
NPC列表=服务员
禁止方向列表=北
老板名字=服务员
long values:
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/服务员
end of YObjectGroup