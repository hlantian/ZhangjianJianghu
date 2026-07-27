#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=乾清门大道
描述=@LONG
    这里是乾清门大道，几个阴沉着脸的太监站在那。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>、<a href='javascript:sendmsg("n")'>北</a>
LONG
南=太和殿
北=乾清门
NPC列表=大内太监统领 大内太监高手1 大内太监高手2 大内太监高手3 大内太监高手4 大内太监高手5 大内太监高手6 大内太监高手7
老板名字=大内太监统领
禁止方向列表=南 北
大内太监统领警告信息=拿下乱匪，格杀不论。
long values:
禁止所有人=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/大内太监统领
object=npc/大内太监高手1
object=npc/大内太监高手2
object=npc/大内太监高手3
object=npc/大内太监高手4
object=npc/大内太监高手5
object=npc/大内太监高手6
object=npc/大内太监高手7
end of YObjectGroup