#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=北大街
描述=@LONG
    这是一条繁忙的街道上，人们行色匆匆，许多人都往南边走去，那那里有一个热闹的广场。东边是一家生意兴隆的酒楼，生意很兴隆的样子。<br>
    这里明显的出口是 <a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>
LONG
北=北大街
东=酒楼
南=城中心
NPC列表=巡捕5
禁止方向列表=南 北
老板名字=巡捕5
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/巡捕5
end of YObjectGroup