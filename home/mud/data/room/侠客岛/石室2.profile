#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=石室
描述=@LONG
    你来到另外一间石室,石室壁上密密麻麻的刻满了字,但见千百文字之中有些笔划宛然便是一把长剑.<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("w")'>西</a>
LONG
南=石室1
东=石室3
西=石室4
NPC列表=龙岛主
老板名字=龙岛主
换取列表=红宝石戒指
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/龙岛主
end of YObjectGroup