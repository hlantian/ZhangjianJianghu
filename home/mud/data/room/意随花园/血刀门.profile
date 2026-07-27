#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=花园
描述=@LONG
    这里再向北走就是意随的豪宅了，两个保镖在附近巡视，不让可疑的人靠近。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("s")'>南</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>。
LONG
东=花园7
西=花园9
南=花园5
北=客厅
物品列表=果色生香
NPC列表=保镖 保镖1
禁止方向列表=东 西 南 北
老板名字=保镖 保镖1
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/保镖
object=npc/保镖1
object=thing/果色生香
end of YObjectGroup