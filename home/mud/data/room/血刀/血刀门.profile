#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=血刀门
描述=@LONG
    这里是西藏血刀门的根据地。在大门上写着鲜红色的“<font color=FF0000>血刀教</font>”三个楷书大字。门前有几名血刀僧人在把守。四周围一片荒凉，这里显得诡秘莫测，阴阴沉沉。<br>
    这里明显的出口是 <a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("n")'>北</a>。
LONG
南=大殿
北=黄土路
NPC列表=守门僧兵 守门僧兵1
禁止方向列表=南
老板名字=守门僧兵 守门僧兵
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/守门僧兵
object=npc/守门僧兵1
end of YObjectGroup