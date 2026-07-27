#class=YRoom
begin of YPropertyGroup
string values:
名字=花园 
描述=@LONG
    这里是一处精心建造的花园，园内奇花异草，争奇斗艳。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>
LONG
西=后院
NPC列表=苏荃
物品列表=樱花
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/樱花
object=npc/苏荃
end of YObjectGroup