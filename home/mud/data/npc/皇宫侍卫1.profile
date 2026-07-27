#class=YNPC
begin of YPropertyGroup
string values:
名字=皇宫侍卫1
性别=男
描述=皇宫侍卫主要负责皇宫的守卫，俱是精干之士。
衣服=侍卫服
朝廷声望_条件一=朝廷声望 数值 大于 1000 皇宫侍卫1对&s说道：你这么点声望也敢来混东西！
朝廷声望_条件二=朝廷声望 数值 小于 10000 皇宫侍卫1对&s说道：大人还是请去别人那领取奖赏吧！
同意朝廷声望的回答=皇宫侍卫1对&s道:这个勋章是皇上给你的赏赐。
long values:
朝廷声望_条件个数=2
年龄=28
容貌=50
重量=100
经验=80000
附加防御力=5
气血=1100
最大气血=1100
固定攻击力=3500
固定防御力=3500
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/侍卫服
object=thing/银子 60
end of YObjectGroup