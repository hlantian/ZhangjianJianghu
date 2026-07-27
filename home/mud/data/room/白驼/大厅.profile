#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=大厅
描述=@LONG
    这是『白驼山庄』的大厅，内部摆设极尽豪华，当中一张黑色檀木条案，上面陈放着精美的花瓶和一些珍贵的瓷器，四壁挂满名家的字画。西边是一间偏厅，通向主人的卧室。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("sd")'>南下</a>。
LONG
北=大院
西=偏厅
南下=练功场
NPC列表=欧阳锋
老板名字=欧阳锋
换取列表=妖狼皮
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/欧阳锋
end of YObjectGroup