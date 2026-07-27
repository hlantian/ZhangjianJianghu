#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=太白楼
描述=@LONG
    这里是太白楼的总号，据说有百年的历史了，最醒目的还是那杆“太白遗风“的旗子，这里的招牌酒就是太白佳酿，天下闻名，城里的老老少少都喜欢来这里喝两盅。这两年生意越做越红火，在京城开起了分号。据说生意也不错。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("u")'>上</a>.
LONG
西=南大街2
上=喜厅
东=后院
NPC列表=店小二5
老板名字=店小二5
物品=鸡腿 牛皮酒袋
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/店小二5
end of YObjectGroup