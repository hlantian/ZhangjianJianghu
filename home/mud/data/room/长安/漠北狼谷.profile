#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=漠北狼谷
描述=@LONG
    北面就是民间流传最神秘的狼谷，据说里面有一只铁血妖狼王，让无数武林人物丧魂。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=漠北狼谷入口
NPC列表=铁血妖狼王 狼1 狼2 狼3 狼4 狼5 狼6 狼7 狼8 狼9 狼10
禁止方向列表=南
老板名字=铁血妖狼王
铁血妖狼王警告信息=你刚想转身逃走，发现狼王正饿狠狠的盯着呢。
long values:
禁止所有人=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/铁血妖狼王
object=npc/狼1
object=npc/狼2
object=npc/狼3
object=npc/狼4
object=npc/狼5
object=npc/狼6
object=npc/狼7
object=npc/狼8
object=npc/狼9
object=npc/狼10
end of YObjectGroup