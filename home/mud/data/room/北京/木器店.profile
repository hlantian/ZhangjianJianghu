#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=木器店
描述=@LONG
    这是一家专售木制兵器的小店，只有一些人常买给小孩玩玩，别的人来得不多，生意很是清淡。可是老板却一点也不着急，整日闲逛，无所事事。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>。
LONG
东=西单北大街2
NPC列表=朱老九
老板名字=朱老九
物品=木剑 木枪 木刀 木棍 木锄
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/朱老九
end of YObjectGroup