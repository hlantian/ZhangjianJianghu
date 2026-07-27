#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=北大街
描述=@LONG
     你走在一条繁忙的街道上，看着操着南腔北调的人们行色匆匆，许多人都往南边走去，那里有一个热闹的广场。东边是一家生意兴隆的客栈。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
东=客栈
西=钱庄
北=北大街1
南=中央广场
NPC列表=苦行僧 巡捕4
禁止方向列表=西 南 北
老板名字=巡捕4
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/苦行僧
object=npc/巡捕4
end of YObjectGroup
