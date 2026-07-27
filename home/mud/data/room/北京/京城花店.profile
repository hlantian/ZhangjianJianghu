#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=京城花店
描述=@LONG
    这是京城最大的一家花店，店内的地上有各种各样的鲜花，供您挑选。空气中总是飘荡着浓郁的花香，让人流连忘返。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=西单北大街1
NPC列表=花店伙计
老板名字=花店伙计
物品=玫瑰 牡丹 丁香 百合
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/花店伙计
end of YObjectGroup