#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=肉铺
描述=@LONG
    屋檐下的一排架子上挂了十几片猪，厚厚的案板上立着几把明晃晃的屠刀，一个赤膊大汉立在后面，两三个伙计在一边忙着剔骨跺馅。店里散发着一股肉腥味。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=东长安街2
NPC列表=郑屠 肉铺伙计
老板名字=郑屠
物品=猪肉 牛肉
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/郑屠
object=npc/肉铺伙计
end of YObjectGroup