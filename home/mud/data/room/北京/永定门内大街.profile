#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=永定门内大街
描述=@LONG
    这里是永定门内大街，说是大街，其实很短。南城就是北京的居民居住区，有钱人都喜欢把房子修在这条大街上，或是开家店铺什么的，南面可以看到永定门了。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=天桥
西=永内西街
东=永内东街
南=永定门
物品列表=熔炉 铁砧
打造列表=缅刀 屠刀 钢刀 手术刀 金刀 紫金刀 斩妖金铙 西域弯刀 青锋宝刀 宝刀狂战 血刀 西域宝刀 金乌刀 烈炎刀 魔音刀 屠龙刀
制作_缅刀=铁块 1
制作_屠刀=铁块 2 缅刀 1
制作_钢刀=铁块 2 屠刀 1
制作_手术刀=铜块 1 钢刀 1
制作_金刀=铜块 2 手术刀 1
制作_紫金刀=铜块 2 金刀 1
制作_斩妖金铙=银块 1 紫金刀 1
制作_西域弯刀=银块 2 斩妖金铙 1
制作_青锋宝刀=银块 2 西域弯刀 1
制作_宝刀狂战=黄金块 1 青锋宝刀 1
制作_血刀=黄金块 2 宝刀狂战 1
制作_西域宝刀=花岗石块 1 血刀 1
制作_金乌刀=花岗石块 2 西域宝刀 1
制作_烈炎刀=花岗石块 2 金乌刀 1
制作_魔音刀=白金块 1 烈炎刀 1
制作_屠龙刀=白金块 2 魔音刀 1 玄铁 1
long values:
最大成功率=100
最小成功率=30
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/熔炉
object=thing/铁砧
end of YObjectGroup