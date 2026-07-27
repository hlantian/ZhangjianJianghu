#class=YRoom
begin of YPropertyGroup
string values:
名字=会议室
描述=@LONG
    这里是会议室，是召开重要会议的地方。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=走廊1
物品列表=哈密瓜 葡萄 荔枝 苹果
long values:
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/哈密瓜
object=thing/葡萄
object=thing/荔枝
object=thing/苹果
end of YObjectGroup