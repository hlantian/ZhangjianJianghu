#class=YMarryRoom
begin of YPropertyGroup
string values:
名字=酒宴房间
需要NPC名称=白无常1
需要条件=结婚步骤
没有NPC的情况=你要找人开始找证婚了。。

描述=@LONG
    这里是结婚的房间<br>
    这里明显的出口是<a href=out onClick='return sendmsg("out");' target=result>外面</a><br>。
LONG
外面=/room/长安/城隍庙
long values:
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/白无常1
end of YObjectGroup
