#class=YNPC
begin of YPropertyGroup
string values:
名字=汝阳王
性别=男
描述=他就是当朝执掌兵马大权的汝阳王，由于久经沙场，不由的散发出一阵阵杀气。
所会技能=基本拳法 大力金刚拳
衣服=一品官服
盔甲=护心镜
空手_攻击武功=大力金刚拳
武器类型=空手
朝廷声望_条件一=朝廷声望 数值 大于 10000000 汝阳王对&s说道：你这么点声望也敢来我这，快点出去！
朝廷声望_条件二=朝廷声望 数值 小于 100000000 汝阳王对&s说道：您老德高望重，还是请去皇上那领取奖赏吧！
同意朝廷声望的回答=汝阳王对&s笑道:皇上给你的赏赐，你快收下吧。
long values:
朝廷声望_条件个数=2
年龄=55
容貌=50
重量=100
经验=20000000
附加防御力=5
气血=7000
最大气血=7000
固定攻击力=120000
固定防御力=100000
基本拳法=350
大力金刚拳=350
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/一品官服
object=thing/护心镜
object=thing/金子 10
end of YObjectGroup