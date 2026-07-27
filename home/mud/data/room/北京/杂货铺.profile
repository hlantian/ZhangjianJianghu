#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=杂货铺
描述=@LONG
    这是一家杂货铺，大箱小箱堆满了一地，都是一些日常用品。掌柜的懒洋洋地躺在一只躺椅上，招呼着过往行人。据说私底下他也卖一些贵重的东西。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=前门大街3
NPC列表=胡掌柜
老板名字=胡掌柜
物品=头盔 布鞋 布衣
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/胡掌柜
end of YObjectGroup