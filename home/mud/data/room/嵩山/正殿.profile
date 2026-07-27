#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=正殿
描述=@LONG
    这是嵩山峻极禅院的正殿，殿上并无佛像，大殿虽也极大，比之少林寺的大雄宝殿却有不如。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>。
LONG
东=东侧殿
西=西侧殿
南=院子
NPC列表=左冷禅
老板名字=左冷禅
换取列表=七色逍遥冠
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/左冷禅
end of YObjectGroup