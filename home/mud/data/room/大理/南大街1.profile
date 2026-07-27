#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=南大街
描述=@LONG
    这里是大理城的南大街，地上扫的一尘不染，东边就是大理的皇宫所在，看样子是戒备森严。<br>
    这里明显的出口是<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=南大街
南=南门
西=小巷
物品列表=熔炉 铁砧
打造列表=铁包拳 毒针拳套 一阳指套 白玉指环 柔丝手套 黑玉指环 钻石指环 玄铁指环 密银指环 佛指 玄金指环
制作_铁包拳=铁块 1
制作_毒针拳套=铁块 2 铁包拳 1
制作_一阳指套=铜块 1 毒针拳套 1
制作_白玉指环=铜块 2 一阳指套 1
制作_柔丝手套=银块 1 白玉指环 1
制作_黑玉指环=黄金块 1 柔丝手套 1
制作_钻石指环=黄金块 2 黑玉指环 1
制作_玄铁指环=花岗石块 2 钻石指环 1
制作_密银指环=花岗石块 2 玄铁指环 1
制作_佛指=白金块 1 密银指环 1
制作_玄金指环=白金块 2 佛指 1 玄铁 1
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