#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=沧州西街
描述=@LONG
    这里沧州城西街，北面是一家武馆，里面不时地传出“嘿嘿”的练功声，惹得年轻人听到声音就不由自主地向里面看。南面是一家小的杂货铺，卖一些零碎的日常用品。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=沧州武馆
西=沧州西门
东=沧州城中心
南=杂货铺
物品列表=熔炉 铁砧
打造列表=铁棍 铁杖 钢杖 禅杖 斑竹棍 熟铜棍 执法杖 蛇杖 鹿杖 玄铁拐 青龙棍 盘龙棍 天机棍 鸡毛掸子
制作_铁棍=铁块 1
制作_铁杖=铁块 2 铁棍 1
制作_钢杖=铁块 2 铁杖 1
制作_禅杖=铜块 1 钢杖 1
制作_斑竹棍=铜块 2 禅杖 1
制作_熟铜棍=铜块 2 斑竹棍 1
制作_执法杖=银块 1 熟铜棍 1
制作_蛇杖=黄金块 1 执法杖 1
制作_鹿杖=黄金块 2 蛇杖 1
制作_玄铁拐=花岗石块 1 鹿杖 1
制作_青龙棍=花岗石块 2 玄铁拐 1
制作_盘龙棍=花岗石块 2 青龙棍 1
制作_天机棍=白金块 1 盘龙棍 1
制作_鸡毛掸子=白金块 2 天机棍 1 玄铁 1
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