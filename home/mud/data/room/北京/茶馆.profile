#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=茶馆
描述=@LONG
    你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙桌一字排开，坐满了客人，或高声谈笑，或交头接耳。你要想打听江湖掌故和谣言，这里是个好所在。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=前门大街1
NPC列表=韩老板
老板名字=韩老板
物品=龙井茶
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/韩老板
end of YObjectGroup