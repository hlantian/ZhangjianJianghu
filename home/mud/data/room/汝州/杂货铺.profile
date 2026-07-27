#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=杂货铺
描述=@LONG
    这里沧州城的杂货铺，里面地方不大，也没有柜台，就摊了一两块木板，上面放一点货物，卖一些零碎的日常用品。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=沧州西街
NPC列表=李老板
老板名字=李老板
物品=头盔 竹篮 雨衣
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/李老板
end of YObjectGroup