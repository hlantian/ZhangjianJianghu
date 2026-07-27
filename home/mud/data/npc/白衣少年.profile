#class=YNPC
begin of YPropertyGroup
string values:
名字=白衣少年
性别=男
门派=神龙教
头衔=白龙坛弟子
描述=他是神龙教白龙坛弟子。
所会技能=基本招架 基本内功 基本轻功 基本手法 读书写字 神龙心法 意形步法 神龙八式
玩家要走_条件一=门派 字符串 等于 神龙教 白衣少年对&s喝道：非本教弟子不得入内！
轻功_使用=意形步法
空手_攻击武功=神龙八式
衣服=白衣
long values:
玩家要走_条件个数=1
辈分=3
年龄=16
容貌=70
重量=100
经验=1000000
附加防御力=10
气血=1000
最大气血=1000
固定攻击力=3000
固定防御力=2000
基本内功=70
基本招架=70
基本轻功=70
基本手法=70
读书写字=70
神龙心法=70
意形步法=70
神龙八式=70
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/白衣
end of YObjectGroup