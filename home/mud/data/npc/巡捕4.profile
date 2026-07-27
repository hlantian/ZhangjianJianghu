#class=YSpecialNPC
begin of YPropertyGroup
string values:
名字=巡捕4
性别=男
头衔=六扇门捕头
描述=他不象其它公门中人一样不讲理，因此虽然表情冷酷，但老百姓看着倒也不怕。
盔甲=铁甲
武器=钢剑
武器类型=剑
玩家要走_条件一=pk数 数值 小于 5 巡捕4对&s喝道：你做恶多端，今天总算被我碰见！
玩家要走_条件二=被pk数 数值 小于 5 巡捕4对&s喝道：而乃不祥之人，别在城中乱走！
进入时杀人_条件一=pk数 数值 小于 5 巡捕4对&s怒喝一声，“你做恶多端，今天总算被我碰见！”言毕挥刀砍去。
long values:
玩家要走_条件个数=2
进入时杀人=1
进入时杀人_条件个数=1
年龄=35
容貌=40
盔甲防御力=30
重量=100
气血=10000
最大气血=10000
固定攻击力=400000
固定防御力=250000
经验=50000000
武器攻击力=10
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/钢剑
object=thing/铁甲
end of YObjectGroup