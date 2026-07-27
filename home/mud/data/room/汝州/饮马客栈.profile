#class=YPawnRoom
begin of YPropertyGroup
string values:
名字=饮马客栈
描述=@LONG
    饮马客栈位于沧州城东，远近闻名，生意非常兴隆。南来北往的侠客、江湖汉子都选择在这里落脚，这里可以打听到各地的风土人情。店小二里里外外忙得团团转，接待着南腔北调的客人。南边有一扇门，里面是客栈的里院，上面挂着一块布帘子。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
西=沧州城中心
南=饮马客栈里院
NPC列表=店小二3
老板名字=店小二3
物品=鸡腿 牛皮酒袋
long values:
禁止战斗=1
销售物品不变=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/店小二3
end of YObjectGroup