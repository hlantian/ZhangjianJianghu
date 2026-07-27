#class=YSpecialNPC
begin of YPropertyGroup
string values:
名字=衙役66
性别=男
门派=
头衔=<font color=#ff4fff>诸葛府衙役</font>
描述=一个高大威猛的汉子，因为久在官府做事，脸上已经磨炼得毫无表情。
武器=钢刀
衣服=衙役服
鞋=黑靴
所会技能=基本刀法
刀_攻击武功=基本刀法
武器类型=刀
玩家要走_条件一=武器 字符串 等于 诸葛府邀请信 衙役66拦住&s：“你没有诸葛大人发的邀请信,不可以进入,如果有请装备起来,再进入!”
被看=衙役66对&s说:“这里是诸葛府，闲杂人等，一律不准进！”
long values:
玩家要走_条件个数=1
年龄=30
容貌=50
重量=100
气血=800
最大气血=800
固定攻击力=2000
固定防御力=1600
基本刀法=70
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/衙役服
object=thing/钢刀
object=thing/黑靴
end of YObjectGroup