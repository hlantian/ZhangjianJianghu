#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=当铺
描述=@LONG
    这是一家以买卖公平著称的当铺，一个五尺高的柜台挡在你的面前，柜台上摆着一个牌子(paizi)，柜台后坐着唐老板，一双精明的眼睛上上下下打量着你。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>
LONG
西=南大街
NPC列表=东家
老板名字=东家
是否收购=是
long values:
禁止战斗=1
典当百分比=50
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/东家
end of YObjectGroup


