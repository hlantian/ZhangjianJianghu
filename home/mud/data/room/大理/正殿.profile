#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=正殿
描述=@LONG
    终于到了大理的正殿，皇座之上段正明不威自怒，使你手忙脚乱的拜倒在地。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("n")'>北</a>
LONG
南=后殿
北=大殿
NPC列表=段正明
老板名字=段正明
领取条件=朝廷声望
物品1=公爵勋章3
物品2=公爵勋章2
物品3=公爵勋章1
销毁物品=汝阳王_领取物品
long values:
物品数目=3
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup 
object=npc/段正明 
end of YObjectGroup 
