#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=平定州中心
描述=@LONG
    这里就是平定州的中心了，一直向北就可以直接到达陕甘边境，西面就是黑木崖，日月神教的地界了。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("n")'>北</a>。
LONG
西=平定州西街
北=平定州北门
物品列表=熔炉 铁砧
打造列表=铁锤 铜锤 流星锤 紫金锤 玄铁小锤 惊神锤 震天锤 震天锤 雷神锤
制作_铁锤=铁块 1
制作_铜锤=铜块 1 铁锤 1
制作_流星锤=银块 1 铜锤 1
制作_紫金锤=黄金块 1 流星锤 1
制作_玄铁小锤=花岗石块 2 紫金锤 1
制作_惊神锤=花岗石块 2 玄铁小锤 1
制作_震天锤=白金块 1 惊神锤 1
制作_雷神锤=白金块 2 震天锤 1 玄铁 1
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