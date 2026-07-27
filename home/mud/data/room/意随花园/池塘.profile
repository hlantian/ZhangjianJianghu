#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=池塘
描述=@LONG
    你来到这里你就觉的一阵清凉，四周全是高大的垂柳，池塘里鱼儿欢快的游着，几张休闲时尚的长椅放在岸边。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("e")'>东</a> 。
LONG
老板名字=服务员1
劳动种类=钓鱼
劳动开始=&s把鱼饵装上鱼钩，挥动鱼杆，鱼钩在空中画了一条弧线，落在水中。
劳动结束=浮标动了一下，&s猛地一提钓鱼杆。
劳动结果1=&s钓起来好大一条鱼！
劳动结果2=&s钓起来一条小白条，随手又把它扔回了水里。
东=花园1
NPC列表=服务员1
long values:
是否劳动=1
劳动结果个数=2
增加经验下限=500
增加经验上限=600
增加潜能下限=450
增加潜能上限=500
劳动结果个数=2
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/服务员1
end of YObjectGroup