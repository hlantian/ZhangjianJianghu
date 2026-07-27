#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=大厅
描述=@LONG
    你从大门来到了这里，只见大厅的墙上挂着一副有点发黄的画，画中有位十分美丽动人的女人，原来这位就是桃花谷的女主人，她是黄药师生平最爱的女人，自从她去世后黄药师依然对她念念不忘。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>，<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("e")'>东</a>。
LONG
南=大门
西=小院
北=后厅
东=别院
NPC列表=黄药师
老板名字=黄药师
换取条件=江湖声望
换取列表=屠龙刀
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/黄药师
end of YObjectGroup
