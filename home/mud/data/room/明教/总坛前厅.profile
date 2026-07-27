#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=总坛前厅
描述=@LONG
    上得山来，一座波斯风格的建筑豁然矗立在你的眼前，碧绿色的琉璃瓦和金黄色的廊柱相互辉映，这里是明教总坛的前厅，厅前有两条大石狮，大石狮之间是十余级的斜斜而上的石阶，石阶被一大岩石做成的石碑中间隔开，石碑平行于石阶镶于地上。石碑上雕着一飞腾而上的火焰，极是雄伟壮观，石碑中有一些用小楷雕刻而成的文字，记载着明教上千年的历史，由此而上就是光明顶了。<br>
    这里明显的出口是 <a href='javascript:sendmsg("ne")'>东北</a> 和 <a href='javascript:sendmsg("sw")'>西南</a> 。
LONG
东北=光明顶
西南=林间小路1
NPC列表=殷野王 明教教众 明教教众1
老板名字=殷野王
劳动种类=巡视
劳动开始=&s手提钢刀，神情肃穆，站在山门一侧，看着来往人流。
劳动结果1=&s站了一天只觉腰酸背疼，但神情却依然如故，殷野王不由对你赞许的点了点头。
劳动结果2=&s站了半天，只觉浑身难受，刚想偷懒，却被殷野王狠狠瞪了一眼，不由哆嗦了一下。
劳动结果3=&s突然大喝一声，拦住来人，却不料此人从怀中拿出令牌，你尴尬一笑，退回原处。
long values:
是否劳动=1
劳动结果个数=3
增加经验下限=20
增加经验上限=41
增加潜能下限=10
增加潜能上限=31
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/殷野王
object=npc/明教教众
object=npc/明教教众1
end of YObjectGroup
