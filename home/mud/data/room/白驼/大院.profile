#class=YRoom
begin of YPropertyGroup
string values:
名字=大院
描述=@LONG
    这儿就是山庄的中心大院。地面上十分地平整。向北走可以到后院了。除了山庄里的人，一般是不能再向后走了。东面是一个偏门，通向另一个院落。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=长廊
东=偏门
南=大厅
NPC列表=丫环1 丫环2
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/丫环1
object=npc/丫环2
end of YObjectGroup