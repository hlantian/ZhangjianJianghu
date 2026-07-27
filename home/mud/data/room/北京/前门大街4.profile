#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=前门大街
描述=@LONG
    这里就是前门大街，街道两边店铺林立，生意好不兴隆。北边是去天安门广场去的路，南边便是热闹杂乱的天桥了。西边是间当铺，东边是京城很出名的平安客栈。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=天安门广场
西=当铺
东=平安客栈
南=前门大街3
NPC列表=巡捕2
禁止方向列表=西 南 北
老板名字=巡捕2
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕2
end of YObjectGroup