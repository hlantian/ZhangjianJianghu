#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=太白楼一楼
描述=@LONG
    迎门是一张四尺多长的大柜台，柜台后下中悬着一块“太白遗风”的大酒幌，柜台左侧放着几坛普通的米酒，一般的客人就零沽上一两碗坐在一楼的桌上喝上几口，要是真的想尝尝这里的太白玉酿，就要上楼坐一坐了。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("u")'>上</a>。
LONG
东=王府井大街4
上=太白楼二楼
NPC列表=店小二2
老板名字=店小二2
物品=鸡腿 牛皮酒袋
long values:
销售物品不变=1
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/店小二2
end of YObjectGroup