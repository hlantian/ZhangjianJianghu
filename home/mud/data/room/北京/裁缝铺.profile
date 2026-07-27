#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=裁缝铺
描述=@LONG
    这是京城是做衣服做得最好的店铺了。老板被称作陈一眼，因为他量衣都不用尺，只需一眼就能看准。传的是神乎其神，也不知道是不是真的。不过这里的衣服的确是上乘手艺，远近闻名，京城的达官贵人也常常请他来做衣服。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=前门大街2
NPC列表=陈一眼
老板名字=陈一眼
物品=绸衣 布衣 缎布衫
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/陈一眼
end of YObjectGroup