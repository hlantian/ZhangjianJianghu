#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=街道
描述=@LONG
    这是衡山城，衡山城依山而建。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=衡山城北门
南=街道1
NPC列表=何三七
老板名字=何三七
物品=鲜肉馄饨 馄饨汤
long values:
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/何三七
end of YObjectGroup