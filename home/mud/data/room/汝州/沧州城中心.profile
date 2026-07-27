#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=沧州城中心 
描述=@LONG
    这里是沧州城的中心，东边是远近闻名的饮马客栈，多住着一些江湖客人。西边比这里更要热闹，北边出了城，就是上京的大驿道了。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=沧州北门
西=沧州西街
东=饮马客栈
南=沧州南门
NPC列表=巡捕3
禁止方向列表=西 南 北
老板名字=巡捕3
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕3
end of YObjectGroup