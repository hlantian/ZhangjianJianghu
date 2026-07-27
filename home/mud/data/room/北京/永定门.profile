#class=YRoom
begin of YPropertyGroup
string values:
名字=永定门
描述=@LONG
    这里是永定门，城门正上方刻着“永定门”三个大字，城墙上贴着几张官府告示(gaoshi)。每天都有许多人从这里是出入京城，正因如此官兵盘查得格外仔细。一条笔直的大道向南北两边延伸。南边的驿道上人来车往，尘土飞扬。北边通往城中心。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=永定门内大街
南=大驿道1
NPC列表=官兵1 官兵2 武将1
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/武将1
object=npc/官兵1
object=npc/官兵2
end of YObjectGroup