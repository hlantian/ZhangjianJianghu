#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=东街
描述=@LONG
    这是一条普通的街道,路上人烟稀少,行人在此大多行色匆匆<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("e")'>东</a>,<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>
LONG
北=长乐帮总舵
东=小桥
西=镇江街口
南=小院
物品列表=熔炉 铁砧
打造列表=铁枪 长枪 金枪 长柄金枪 判官笔 南海神木 乌龙矛 鹤笔 惊天枪 丈八蛇矛 玄铁枪 焚天枪
制作_铁枪=铁块 1
制作_长枪=铁块 2 铁枪 1
制作_金枪=铁块 2 长枪 1
制作_长柄金枪=铜块 2 金枪 1
制作_判官笔=铜块 2 长柄金枪 1
制作_南海神木=银块 1 判官笔 1
制作_乌龙矛=银块 2 南海神木 1
制作_鹤笔=黄金块 2 乌龙矛 1
制作_惊天枪=花岗石块 2 鹤笔 1
制作_丈八蛇矛=花岗石块 2 惊天枪 1
制作_玄铁枪=白金块 1 丈八蛇矛 1
制作_焚天枪=白金块 2 玄铁枪 1 玄铁 1
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