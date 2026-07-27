#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=珠宝店
描述=@LONG
    珠宝店中珠光宝气四射。精致的长柜中陈设着各种珠宝玉器。右边的一个雕花木架上摆着一棵三尺多高的玉树，珍贵之外又透着淡雅秀丽，显出店主的实力非同小可。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>。
LONG
东=前门大街3
NPC列表=金不换
老板名字=金不换
物品=金戒指 金项链 金手镯
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/金不换
end of YObjectGroup