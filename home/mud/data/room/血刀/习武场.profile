#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=习武场
描述=@LONG
    这里是一处宽敞的广场，地上堆放着一些木人， 是供血刀门僧人练拳法而设的，有数名僧人正在努力地打着木人。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("n")'>北</a>
LONG
东=走廊5
西=走廊4
南=后殿
北=广场
NPC列表=夙兴
禁止方向列表=南
老板名字=夙兴
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/夙兴
end of YObjectGroup