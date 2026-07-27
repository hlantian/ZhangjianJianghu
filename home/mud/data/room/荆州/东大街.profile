#class=YYelianRoom
begin of YPropertyGroup
string values:
名字=东大街
描述=@LONG
    这是一条宽阔的青石板街道，向东西两头延伸。西边人声嘈杂，是荆州城的城中心广场。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>和<a href='javascript:sendmsg("w")'>西</a>、<a href='javascript:sendmsg("s")'>南</a>
LONG
西=东大街1
东=东门
南=废宅
物品列表=熔炉 铁砧
打造列表=铁锄 钢锄 鹤嘴锄 玄铁锄 打铁锤 钢锤 擂天锤 玄铁锤
制作_铁锄=铁块 10
制作_钢锄=铜块 10 铁锄 1
制作_鹤嘴锄=银块 10 钢锄 1
制作_玄铁锄=黄金块 10 鹤嘴锄 1
制作_打铁锤=铁块 10 大锤 1
制作_钢锤=铜块 10 打铁锤 1
制作_擂天锤=银块 10 钢锤 1
制作_玄铁锤=黄金块 10 擂天锤 1
制作_修罗刀=白金块 10 雷神锤 1 九龙鞭 1 鸡毛掸子 1 玄金指环 1 倚天剑 1 屠龙刀 1 焚天枪 1
long values:
最大成功率=80
最小成功率=30
禁止战斗=1
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/熔炉
object=thing/铁砧
end of YObjectGroup