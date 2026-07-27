#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=皮货店
描述=@LONG
    这里是皮货店，出售各种皮衣，店中有一股兽皮散发出来的气味。这里卖出去的皮衣，很少会有什么问题，而且价格公道，北京城附近的猎户常到他这里卖皮。堂中挂了一排的各色皮毛。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>。
LONG
东=前门大街2
NPC列表=老刘头
老板名字=老刘头
物品=皮袄 皮大衣 皮帽
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/老刘头
end of YObjectGroup