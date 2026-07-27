#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=青石路
描述=@LONG
   这是青石铺成的大路，到也没什么特别，只是年代比较原久，地面显的异常的平滑。<br>
    这里明显的出口是 <a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("s")'>南</a>和<a href='javascript:sendmsg("e")'>东</a>
LONG
西=青石路
北=铁塔
南=小吃店
东=开封东门
物品列表=熔炉 铁砧
打造列表=铁甲 金甲 护心镜 青龙战甲 真丝宝甲 软猬甲 天蚕甲 雪蚕甲 镜光铠 妖狼皮
制作_铁甲=铁块 2
制作_金甲=铁块 2 铁甲 1
制作_护心镜=铜块 2 金甲 1
制作_青龙战甲=银块 2 护心镜 1
制作_真丝宝甲=黄金块 1 青龙战甲 1
制作_软猬甲=黄金块 2 真丝宝甲 1
制作_天蚕甲=花岗石块 2 软猬甲 1
制作_雪蚕甲=花岗石块 2 天蚕甲 1
制作_镜光铠=白金块 1 雪蚕甲 1
制作_妖狼皮=白金块 2 镜光铠 1 玄铁 1 狼狗皮 10
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

