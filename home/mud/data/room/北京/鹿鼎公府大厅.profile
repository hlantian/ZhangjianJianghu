#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=鹿鼎公府大厅
描述=@LONG
    大厅正中的一张红木靠椅上铺了一块虎皮，煞是威风。两边各是几张正椅，是招呼客人就坐的。两边墙上挂了一些镶金嵌玉的宝剑匕首作装饰，颇有一副武学之家的气势。<br>
    这里明显的出口是<a href='javascript:sendmsg("s")'>南</a>。
LONG
南=鹿鼎公府大院
NPC列表=韦小宝
老板名字=韦小宝
领取条件=朝廷声望
物品1=男爵勋章
销毁物品=皇宫侍卫1_领取物品
换取条件=朝廷声望
换取列表=九龙鞭 倚天剑 屠龙刀 焚天枪 玄金指环 雷神锤 鸡毛掸子 孔雀翎
long values:
换取数目=10000000
物品数目=1
禁止战斗=1
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/韦小宝
end of YObjectGroup