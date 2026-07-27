#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=小吃店
描述=@LONG
    这里一家小吃店，专卖各色粽子。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=东街
NPC列表=莫老板
老板名字=莫老板
物品=枧水豆沙粽 火腿粽 红豆粽 蛋黄咸肉绿豆粽 鲁肉粽 鲍鱼竹筒粽
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/莫老板
end of YObjectGroup
