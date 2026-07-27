#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=乐器店
描述=@LONG
        这是一家古香古色的乐器店。四面的墙上挂满了各种奇怪的乐器，除了常见的琴瑟笛箫外，还有许多是叫不出名字的。店老板站在柜台后面，正拿着一支竹箫在比划着。<br>
    这里明显的出口是 <a href='javascript:sendmsg("nw")'>西北</a>
LONG
西北=中央广场
NPC列表=乐师
老板名字=乐师
物品=琵琶 古筝 瑶琴 长箫 竹笛 唢呐 冬不拉 马头琴 勋
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/乐师
end of YObjectGroup


