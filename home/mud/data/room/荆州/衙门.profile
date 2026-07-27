#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=衙门
描述=@LONG
    这里是衙门大门，两扇朱木大门紧紧关闭着，门上钉着碗口大的铜钉，门外两盏大灯笼，一盏写着“荆州府正堂”，另一盏写着“凌府”。“肃静”“回避”的牌子分放两头石狮子的旁边。几名衙役在门前巡逻。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、和<a href='javascript:sendmsg("w")'>西</a>
LONG
东=府衙正厅
西=南大街1
NPC列表=衙役5 衙役6
禁止方向列表=东
老板名字=衙役5 衙役6
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/衙役5
object=npc/衙役6
end of YObjectGroup