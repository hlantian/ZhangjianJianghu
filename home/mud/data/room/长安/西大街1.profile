#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=西大街
描述=@LONG
    这里是长安城的西大街，就像四四方方的长安城一样，城里纵横分明的道路，是这座古老皇城的印记，记忆着这里曾经的繁华和荣耀。北边是鼓楼，南边是棋艺馆。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>,<a href='javascript:sendmsg("w")'>西</a>,<a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
北=鼓楼
西=西大街2
东=钟楼
南=棋艺馆
物品列表=熔炉 铁砧
打造列表=铁剑 长剑 钢剑 清风剑 白剑 黑剑 玄铁匕首 淑女剑 君子剑 真武剑 玄铁剑 玉萧 相思剑 乌木剑 鱼肠剑 沉香剑 倚天剑
制作_铁剑=铁块 1
制作_长剑=铁块 2 铁剑 1
制作_钢剑=铁块 2 长剑 1
制作_清风剑=铜块 1 钢剑 1
制作_白剑=铜块 2 清风剑 1
制作_黑剑=铜块 2 清风剑 1
制作_玄铁匕首=银块 1 白剑 1 黑剑 1
制作_淑女剑=银块 2 玄铁匕首 1
制作_君子剑=银块 2 玄铁匕首 1
制作_真武剑=黄金块 1 玄铁匕首 1
制作_玄铁剑=黄金块 2 真武剑 1
制作_玉萧=黄金块 1 玄铁剑 1
制作_相思剑=花岗石块 1 玉萧 1
制作_乌木剑=花岗石块 2 相思剑 1
制作_鱼肠剑=花岗石块 2 乌木剑 1
制作_沉香剑=白金块 1 鱼肠剑 1
制作_倚天剑=白金块 2 沉香剑 1 玄铁 1
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