#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=青竹屋
描述=@LONG
    这里是一间很大的青竹屋，屋内犹如议事大厅一般，空空荡荡的没什么人，只有一个老者，脸上都是伤疤皱纹，丑陋已极。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>
LONG
东=后院
西=青石路2
NPC列表=洪安通
老板名字=洪安通
换取列表=青凤佩
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/洪安通
end of YObjectGroup