#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=华山瀑布
描述=@LONG
    转过一个山峡，水声震耳欲聋，只见山峰间一条大白龙似的瀑布奔泻
而下，冲入一条溪流，奔胜雷鸣，湍急异常，水中挟著树枝石块，转眼便
流得不知去向。溪流(river)的中心有一块巨石(stone)。水花飞溅，四顾
水气蒙蒙，蔚为奇观。那山洪势道猛烈，令人颇有惧意，还是别乱来的好。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("nw")'>西北</a> 。
LONG
老板名字=渔翁
劳动种类=钓鱼
劳动开始=&s把鱼饵装上鱼钩，挥动鱼杆，鱼钩在空中画了一条弧线，落在水中。
劳动结束=浮标动了一下，&s猛地一提钓鱼杆。
劳动结果1=&s钓起来好大一条鱼！
劳动结果2=结果什么都没有钓着。
劳动结果3=原来是一张烂渔网。
劳动结果4=&s钓起来一条<font color=FF0000>美人鱼</font>，她微微一笑，又跳回了水中。
劳动结果5=&s钓起来一条小白条，随手又把它扔回了水里。
西北=莎萝坪
NPC列表=渔翁
long values:
是否劳动=1
劳动结果个数=5
增加经验下限=20
增加经验上限=41
增加潜能下限=10
增加潜能上限=31
劳动结果个数=5
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/渔翁
end of YObjectGroup