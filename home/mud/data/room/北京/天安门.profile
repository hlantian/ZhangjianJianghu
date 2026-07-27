#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=天安门
描述=@LONG
    天安门是皇宫的正门，高墙巍峨，长梁雕龙，飞檐画凤，充分地显示了皇权至高无上的地位。一般的百姓到此就截然止步，不敢再向前擅自逾越皇家禁地。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>、<a href='javascript:sendmsg("n")'>北</a>。
LONG
南=天安门广场
北=皇宫大门
NPC列表=皇宫侍卫1 皇宫侍卫2
老板名字=皇宫侍卫1
领取条件=朝廷声望
换取条件=朝廷声望
物品1=勋爵勋章
销毁物品=宋老夫子_领取物品
换取列表=丈八蛇矛 密银指环 惊神锤 烈炎刀 盘龙棍 青龙鞭 鱼肠剑 诸葛弩
long values:
换取数目=100000
物品数目=1
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/皇宫侍卫1
object=npc/皇宫侍卫2
end of YObjectGroup