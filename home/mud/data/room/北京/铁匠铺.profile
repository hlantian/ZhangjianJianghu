#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=铁匠铺
描述=@LONG
    里面几件摆设十分简单，靠门的炉子里的火烧得正旺，地下散放着几件打好的铁器。你一进门就感到一股热气扑面而来。里面的铁匠挥汗如雨，正在卖力地砸炼着一块烧红的铁块。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=东长安街5
NPC列表=李铁匠
老板名字=李铁匠
物品=铁锤 铁棍 铁剑 铁枪
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/李铁匠
end of YObjectGroup