#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=打铁铺
描述=@LONG
      这是一家简陋的打铁铺，中心摆着一个火炉，炉火把四周照得一片通红，你一走进去就感到浑身火热。墙角堆满了已完工和未完工的菜刀、铁锤、铁棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着铁锤，专心致志地在打铁。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>
LONG
北=东大街1
NPC列表=铁匠
老板名字=铁匠
物品=长剑 钢刀 匕首 钢杖 铁棍 铁甲 屠刀 大锤
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/铁匠
end of YObjectGroup

