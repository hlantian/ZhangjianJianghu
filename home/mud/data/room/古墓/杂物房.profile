#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=杂物房
描述=@LONG
    一些日常所用的杂物放在一侧的墙角，另一侧整齐的摆放着一些坛子，隐约传出一些香甜之味。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>
LONG
西=走廊
物品列表=鞭法入门
NPC列表=孙婆婆
老板名字=孙婆婆
劳动种类=酿蜂浆
劳动开始=&s小心翼翼的拿出一些蜂蜜,放入坛中,加好配料,开始酿制.
劳动结束=&s擦擦汗，尝了尝蜂浆
劳动结果1=&s满意的点了点头，小心的密封好放在一边.
劳动结果2=&s皱了皱眉头，看来不是很好吃。
劳动结果3=&s觉得差不多，正想封存，却看见孙婆婆在一边看着自己，心底不由叹了口气。
劳动结果4=&s眼睛一眯，觉得很不错，正要摆放整齐，却一个不小心打碎了坛子，气的脸色发青。
long values:
是否劳动=1
劳动结果个数=4
增加经验下限=20
增加经验上限=41
增加潜能下限=10
增加潜能上限=31
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/孙婆婆
end of YObjectGroup