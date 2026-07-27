#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=客栈
描述=@LONG
    这是一家价钱低廉的客栈，生意非常兴隆。外地游客多选择这里落脚，店小二里里外外忙得团团转，接待着南腔北调的客人。墙上挂着一个牌子(paizi)。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("u")'>上</a>
LONG
西=北大街
上=客栈二楼
NPC列表=店小二7
老板名字=店小二7
物品=鸡腿 牛皮酒袋
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/店小二7
end of YObjectGroup