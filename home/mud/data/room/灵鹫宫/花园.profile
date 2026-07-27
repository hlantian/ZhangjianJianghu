#class=YRoom
begin of YPropertyGroup
string values:
名字=花园 
描述=@LONG
    这里是飘渺峰一处精心建造的花园，园内奇花异草，争奇斗艳。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("sw")'>西南</a>
LONG
西南=独尊厅
东=憩凤阁
西=画廊
北=小道
NPC列表=黎夫人
物品列表=梅花 红景天
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/黎夫人
object=thing/梅花
object=thing/红景天
end of YObjectGroup