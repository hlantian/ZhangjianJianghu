#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=皇宫大门
描述=@LONG
    这里是皇宫大门，地上打扫的干干净净，几名侍卫在附近巡视。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>
LONG
南=天安门
NPC列表=大内总管
老板名字=大内总管
物品1=伯爵勋章3
物品2=伯爵勋章2
物品3=伯爵勋章1
销毁物品=蔡进忠_领取物品
领取条件=朝廷声望
换取条件=朝廷声望
换取列表=沉香剑 魔音刀 乌龙鞭 佛指 天机棍 玄铁枪 震天锤 梨花暴雨针
long values:
换取数目=1000000
物品数目=3
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/大内总管
end of YObjectGroup