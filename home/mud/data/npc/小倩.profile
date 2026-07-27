#class=YSpecialNPC
begin of YPropertyGroup
string values:
名字=小倩
性别=女
门派=华山
头衔=<font color=#ff4fff>诸葛府秘书</font>
描述=她聪明能干,在工作上帮了诸葛不少的忙!有一空就去琴室练琴,想弹给诸葛先生听!
武器=白剑
衣服=霓霞彩衣
项链=霓霞彩巾
鞋=白靴
所会技能=基本剑法
刀_攻击武功=基本剑法
武器类型=剑
被看=小倩问&s:"你好!我是诸葛先生的秘书,有什么可以帮你的?"
被给=小倩对&s说道:你给我这个做什么，让别人看到就不好了！
诸葛仁侯_条件一=性别 字符串 等于 男 小倩对&s笑道：你好小姐！我家诸葛先生的QQ是1234458你如果有事可以加这个QQ找他。
同意诸葛仁侯的回答=小倩对&s笑道：你好先生！我家诸葛先生的QQ是1234458你如果有事可以加这个QQ找他。
long values:
诸葛仁侯_条件个数=1
年龄=19
容貌=95
重量=100

气血=80000
最大气血=80000
固定攻击力=2000
固定防御力=2000
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/霓霞彩衣
object=thing/霓霞彩巾
object=thing/白靴
object=thing/白剑
end of YObjectGroup
