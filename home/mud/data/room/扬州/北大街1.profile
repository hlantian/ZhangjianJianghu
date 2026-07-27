#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=北大街
描述=@LONG
     是一条宽阔的青石街道，向南北两头延伸。北边是北城门通向城外。。东边是一家酒楼，阵阵酒肉香酒香传出，让你垂涎欲滴。西边是一座古朴的庙宇，香火缭绕，是一座岳王庙。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>和<a href='javascript:sendmsg("s")'>南</a>。
LONG
东=酒楼
西=武庙
北=北门
南=北大街
NPC列表=阿宝
物品列表=熔炉 铁砧
打造列表=铁鞭 长鞭 牧马鞭 金丝马鞭 鳄尾鞭 银索金铃 黑索 金龙鞭 赤龙金索 黑龙鞭 青龙鞭 乌龙鞭 九龙鞭
制作_铁鞭=铁块 1
制作_长鞭=铁块 2 铁鞭 1
制作_牧马鞭=铁块 2 长鞭 1
制作_金丝马鞭=铜块 2 牧马鞭 1
制作_鳄尾鞭=银块 1 金丝马鞭 1
制作_银索金铃=银块 2 鳄尾鞭 1
制作_黑索=黄金块 1 银索金铃 1
制作_金龙鞭=黄金块 1 黑索 1
制作_赤龙金索=黄金块 2 金龙鞭 1
制作_黑龙鞭=花岗石块 2 赤龙金索 1
制作_青龙鞭=花岗石块 2 黑龙鞭 1
制作_乌龙鞭=白金块 1 青龙鞭 1
制作_九龙鞭=白金块 2 乌龙鞭 1 玄铁 1
long values:
最大成功率=100
最小成功率=30
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/阿宝
object=thing/熔炉
object=thing/铁砧
end of YObjectGroup


