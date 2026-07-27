#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=关东客栈
描述=@LONG
    这是一家客栈，生意非常兴隆。这里的老板非常豪爽好客,最大的嗜好是与人拚酒,虽然每拚必败,却越战越勇.<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("u")'>上</a>
LONG
西=南市
上=客栈二楼
NPC列表=李店主
老板名字=李店主
物品=烧刀子
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/李店主
end of YObjectGroup


