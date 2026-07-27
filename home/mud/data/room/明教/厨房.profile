#class=YCookRoom
begin of YPropertyGroup
string values:
名字=厨房
描述=@LONG
    这是明教的厨房，你一走进这里，闻得阵阵的香气，就立即产生饱餐一顿的念头。有几个厨子正在忙忙碌着，有几个小僮在旁侍侯着。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>
LONG
东=聚义厅
NPC列表=小童
老板名字=小童
提供食物=煎饼 清茶
long values:
禁止带出=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/小童
end of YObjectGroup