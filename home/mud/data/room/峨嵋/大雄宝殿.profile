#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=大雄宝殿
描述=@LONG
    一间极大的佛殿，供着西天诸佛。金顶琉璃富贵中透着庄严。四季香火不断，这里已经是峨嵋重地，一般的游客并不能走到这里，这里主要是一些武林上的朋友前来拜访的时候，才能来到，由于峨嵋多是女弟子，有所不便，所以没什么重大的事情，武林同道也不来打扰。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、<a href='javascript:sendmsg("n")'>北</a>、<a href='javascript:sendmsg("w")'>西</a>和<a href='javascript:sendmsg("s")'>南</a>  。
LONG
东=斋堂
北=后殿
西=休息室
南=广场
NPC列表=静玄
老板名字=静玄
劳动种类=打扫
劳动开始=&s你拿起抹布、笤帚之类的东西，环顾四周，准备清扫清扫。
劳动结果1=&s仔细的清扫大殿，将一众佛像一一轻拭，整个大殿也变的亮堂不少。
劳动结果2=&s一时兴起，大开大阂，竟将大殿当成了演武场，结果大殿不但没打扫干净，自己也变的灰头土脸。
劳动结果3=想来&s以前并不常劳动，才不久的工夫就开始气喘吁吁，四肢无力，瘫在地上。
long values:
是否劳动=1
劳动结果个数=3
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/静玄
end of YObjectGroup

