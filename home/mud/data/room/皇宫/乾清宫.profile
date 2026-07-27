#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=乾清宫
描述=@LONG
    这里是乾清宫，三个老太监站在那，杀气腾腾。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>、<a href='javascript:sendmsg("n")'>北</a>
LONG
南=乾清门
北=交泰殿
NPC列表=大内太监统领1 大内太监统领2 大内太监统领3
老板名字=大内太监统领1 大内太监统领2 大内太监统领3
禁止方向列表=南 北
大内太监统领警告信息=拿下乱匪，格杀不论。
long values:
禁止所有人=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/大内太监统领1
object=npc/大内太监统领2
object=npc/大内太监统领3
end of YObjectGroup