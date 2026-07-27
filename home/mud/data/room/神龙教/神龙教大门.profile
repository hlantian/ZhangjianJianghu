#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=神龙教大门
描述=@LONG
    这里是神龙教大门，五个穿着各色衣服的少年站在那里。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、 <a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>
LONG
东=青石路
西=小路
北=寒滩
NPC列表=青衣少年 白衣少年 赤衣少女 黑衣少年 黄衣少年
禁止方向列表=东
老板名字=青衣少年 白衣少年 赤衣少女 黑衣少年 黄衣少年
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/青衣少年
object=npc/白衣少年
object=npc/赤衣少女
object=npc/黑衣少年
object=npc/黄衣少年
end of YObjectGroup