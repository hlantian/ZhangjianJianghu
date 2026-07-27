#class=YRoom
begin of YPropertyGroup
string values:
名字=广场
描述=@LONG
    这里是一处宽敞的广场，地上铺着青砖。但阳光并不充足，因为四周被高山包围，因此阴阴凉凉的。正前方有一道台阶，能通往习武场，两旁分别是寝室与膳堂。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("n")'>北</a>
LONG
东=走廊3
西=走廊2
南=习武场
北=石路
NPC列表=胜谛
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/胜谛
end of YObjectGroup