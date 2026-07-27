#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=说书场
描述=@LONG
    里面黑压压地坐了很多的人，上面有一个说书先生正在眉飞色舞地说到精彩之处，大家伙都聚精会神地听着。几个小贩在场里来加走动，兜售着一些小食品。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>。
LONG
西=天桥
NPC列表=小贩1 书客1 书客2
老板名字=小贩1
物品=冰糖葫芦 拨浪鼓
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/书客1
object=npc/书客2
object=npc/小贩1
end of YObjectGroup