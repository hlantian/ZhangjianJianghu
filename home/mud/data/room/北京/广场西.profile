#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=广场西
描述=@LONG
    这里是天安门广场东半部，喧闹的长安街到了这里一下子安静了许多。北面透过高大的华表，可以看到重重叠嶂的宫殿屋脊。广场把长安街一分为二，再向西是西长安街，向东越过广场中心便是东长安街了。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
西=西长安街1
东=天安门广场
南=校军场
NPC列表=行人1 巡逻武将
禁止方向列表=南
老板名字=巡逻武将
通过条件=经验
long values:
没有守卫=1
经验=100000
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/行人1
object=npc/巡逻武将
end of YObjectGroup