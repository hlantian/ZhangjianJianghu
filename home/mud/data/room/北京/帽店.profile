#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=帽店
描述=@LONG
    这是一家专门出售各种帽子的商店，北京天冷，风沙又大，买顶帽子既好看又御寒，倒是十分不错，墙上挂了几十种不同样式和品种的帽子，个个都很好看。而且任你挑选。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=东长安街4
NPC列表=季阿三
老板名字=季阿三
物品=布帽 绸帽 僧帽
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/季阿三
end of YObjectGroup