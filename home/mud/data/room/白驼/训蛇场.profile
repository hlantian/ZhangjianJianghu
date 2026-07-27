#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=训蛇场
描述=@LONG
    这是白陀山庄的训蛇场，地上到处都是盘绕的各种长蛇，一个个吐着鲜红的信子，发出嘶嘶的叫声，听得人头皮发麻。<br>
    这里明显的出口是<a href='javascript:sendmsg("n")'>北</a>。
LONG
北=偏门
NPC列表=老蛇仆 毒蛇1 竹叶青蛇1
老板名字=老蛇仆
劳动种类=养蛇
劳动开始=&s胆战心惊的拿出蛇食，走进蛇场。
劳动结果1=&s好不容易给蛇儿喂完食物，走出来才发现自己流了一身的冷汗。
劳动结果2=&s你没走几步，就觉的腿软无力，迈不开步子。
劳动结果3=&s趁没人注意随便将蛇食扔进蛇场，出来正在得意，却被蛇仆一阵很骂。
long values:
是否劳动=1
劳动结果个数=3
增加经验下限=20
增加经验上限=41
增加潜能下限=10
增加潜能上限=31
禁止战斗=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/老蛇仆
object=npc/竹叶青蛇1
object=npc/毒蛇1
end of YObjectGroup