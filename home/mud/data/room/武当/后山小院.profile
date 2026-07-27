#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=后山小院 
描述=@LONG
    这是后山的一座小院，布置简简单单，除了一床、一桌、一椅、一蒲团，再也没有别的什物。比较引人注目的是墙上挂着一把剑。这里就是武当开山祖师张三丰的练功所在。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("n")'>北</a>。
LONG
北=林间小径
NPC列表=张三丰
物品列表=武当剑谱
老板名字=张三丰
换取列表=九龙鞭
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/张三丰
object=thing/武当剑谱
end of YObjectGroup