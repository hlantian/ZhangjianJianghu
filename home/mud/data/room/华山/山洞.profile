#class=YHideDoorRoom
begin of YPropertyGroup
string values:
名字=山洞
准备命令=刺石壁
隐藏前进命令=进入
限制前进方向=山洞
准备成功后显示=你用力一刺，居然将石壁刺穿，急忙又连刺带削，终于开了一个可用一人通过的山洞
成功通过后显示=你小心翼翼的钻了进去
失败通过后显示=你想做什么？疯了吗？
进入条件=年龄 性别 基本剑法 
准备条件=门派 武器类型 后天臂力 最大内力 内力
门派=华山派
武器=剑
性别=男
准备失败后显示=看来这里不怎么好玩。
山洞=/room/华山/秘洞
描述=@LONG
    山洞内有块光溜溜的大石，不知道曾有多少华山派的前辈在此思过面
壁，以致这块大石竟被坐得滑溜。石壁左侧刻着「风清扬」三个大
字，是以利器所刻，笔划苍劲，深有半寸。这三字刻得劲力非凡，想必其
人武功一定十分了得。<br>
    这里唯一的出口是 <a href='javascript:sendmsg("外面")'>外面</a>
LONG
外面=思过崖
里面=秘洞
NPC列表=风清扬
long values:
后天臂力=35
最大内力=2000
内力=2000
年龄=20
基本剑法=150
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/风清扬
end of YObjectGroup
