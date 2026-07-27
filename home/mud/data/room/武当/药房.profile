#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=药房
描述=@LONG
    这是武当山脚下的一间小药房，一名武当道童正在不停拉着风箱。中间有一个丹炉，里面散发出浓
浓的药味，似乎刚有人熬过什么丹药。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("s")'>南</a>。
LONG
南=林间小径1
NPC列表=俞岱岩
老板名字=俞岱岩
劳动种类=炼丹
劳动开始=&s小心的守着炉鼎，照顾着火势大小。
劳动结果1=只见火势一变，&s急忙打开炉鼎，启出刚刚练好的丹药。
劳动结果2=&s只觉的有点困乏，不由睡了过去，起来发现炉火早已熄灭，不由万分的悔恨。
劳动结果3=&s眼看火势开始有所变化，心里不由紧张起来，匆忙之中提早启出了丹药，只好长叹一声重新开始。
long values:
是否劳动=1
劳动结果个数=3
增加经验下限=20
增加经验上限=41
增加潜能下限=10
增加潜能上限=31
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/俞岱岩
object=npc/清风
object=npc/明月
end of YObjectGroup
