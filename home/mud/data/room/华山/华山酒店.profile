#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=华山酒店
描述=@LONG
    这是一华山脚下的一间小酒馆，店面虽小，生意倒还不错。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("w")'>西</a> 。
LONG
NPC列表=店小二
老板名字=店小二
西=华山脚下
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/店小二
end of YObjectGroup


