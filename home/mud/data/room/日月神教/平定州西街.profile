#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=平定州西街
描述=@LONG
    这里就是平定州的西街，北面就是客栈了。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("n")'>北</a>。
LONG
东=平定州中心
西=平定州西门
北=客栈
NPC列表=巡捕7
禁止方向列表=东 西
老板名字=巡捕7
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕7
end of YObjectGroup