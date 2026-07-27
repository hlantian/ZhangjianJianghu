#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=菜市场
描述=@LONG
    这里是一个很大的菜市场，闹哄哄地挤得水泄不通，场边的排水沟里堆积了一些烂菜叶之类的东西，你不由地捂起了鼻子。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=东长安街2
NPC列表=老大娘
老板名字=老大娘
物品=小白菜 大白菜
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/老大娘
end of YObjectGroup