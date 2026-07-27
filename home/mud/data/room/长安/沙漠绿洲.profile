#class=YCookRoom
begin of YPropertyGroup
string values:
名字=沙漠绿洲
描述=@LONG
    四周是无边无际的大沙漠，当空烈日炎炎，但是这里四周绿草青青，清风和谐，一位彩衣美女正在向你望来，邀请你这里休息一会。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>，<a href='javascript:sendmsg("w")'>西</a>。
LONG
北=大沙漠8
西=/room/红花会/红花会大门
老板名字=香香公主
提供食物=水袋 干粮
NPC列表=香香公主 回族高手 回族高手1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/香香公主
object=npc/回族高手
object=npc/回族高手1
end of YObjectGroup