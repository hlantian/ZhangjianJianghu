#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=小路
描述=@LONG
    这里是一条泥泞的小路。<br>
    这里明显的出口是<a href='javascript:sendmsg("se")'>东南</a>和<a href='javascript:sendmsg("ne")'>东北</a>
LONG
东南=小路
东北=小路2
NPC列表=强盗 强盗1
禁止方向列表=东南 东北
老板名字=强盗 强盗1
强盗警告信息=强盗对你叫道；“此山是我开，此树是我栽，要从此路过，留下买路钱”
强盗1警告信息=强盗1拿了一把锈刀在你面前晃来晃去，不停地问你：你怕不怕？你怕不怕？
long values:
禁止所有人=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/强盗
object=npc/强盗1
end of YObjectGroup
