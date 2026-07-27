#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=南大街
描述=@LONG
    这里是长安城的南大街，就像四四方方的长安城一样，城里纵横分明的道路，是这座古老皇城的印记，记忆着这里曾经的繁华和荣耀。东边是太白楼的总号，西边是城里很有名气的吉祥客栈。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=南大街1
西=吉祥客栈
东=太白楼
南=南门
NPC列表=巡捕1
禁止方向列表=东 南 北
老板名字=巡捕1
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕1
end of YObjectGroup