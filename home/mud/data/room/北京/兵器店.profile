#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=兵器店
描述=@LONG
    这是京城里的兵器铺，出售一些江湖人常用的兵器，这两年生意好像不太好，老板总是发愁的样子。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=西单北大街4
NPC列表=唐九
老板名字=唐九
物品=长剑 钢剑 钢刀 长枪
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/唐九
end of YObjectGroup