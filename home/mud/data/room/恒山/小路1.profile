#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=小路
描述=@LONG
    这里是一条小路。<br>
    这里明显的出口是 <a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("sw")'>西南</a>。
LONG
北=小路2
西南=小路
NPC列表=强盗2 强盗3
禁止方向列表=西南 北
老板名字=强盗2 强盗3
强盗警告信息=强盗2对你叫道；“此山是我开，此树是我栽，要从此路过，留下买路钱”
强盗1警告信息=强盗3拿了一把锈刀在你面前晃来晃去，不停地问你：你怕不怕？你怕不怕？
long values:
禁止所有人=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/强盗2
object=npc/强盗3
end of YObjectGroup
