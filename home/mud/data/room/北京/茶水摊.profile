#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=茶水摊
描述=@LONG
    这里卖的是京城人爱喝的大碗茶，又便宜又解渴。地下摆着几个小凳子。看起来是小本经营，摊子十分简陋。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=朝阳路
NPC列表=顾大婶
老板名字=顾大婶
物品=大碗茶
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/顾大婶
end of YObjectGroup