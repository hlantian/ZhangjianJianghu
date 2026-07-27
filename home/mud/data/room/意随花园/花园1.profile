#class=YRoom
begin of YPropertyGroup
string values:
名字=花园
描述=@LONG
    这里是意随花园，四周鲜花怒放。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("s")'>南</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>。
LONG
东=花园2
西=池塘
南=大厅
北=花园3
物品列表=百合
NPC列表=花园总管
禁止方向列表=东 西 南 北
老板名字=花园总管
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/花园总管
object=thing/百合
end of YObjectGroup