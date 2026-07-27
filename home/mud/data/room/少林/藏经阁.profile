#class=YWorkRoom
begin of YPropertyGroup
string values:
名字=藏经阁
描述=@LONG
    这里就是少林寺的藏经阁, 里面不但有由达摩祖师从天竺带
来的佛经典籍, 更有众多武林人士不胜向往的武功秘籍, 这里面
保存着少林历代高僧的心血, 可以说, 是少林的命脉所在。<br>
    这里明显的出口是<a href='javascript:sendmsg("e")'>东</a>。
LONG
东=竹林小道2
NPC列表=扫地僧 玄澄大师 玄生大师 澄明罗汉 澄思罗汉
物品列表=内功入门 石板 掌法诀要
老板名字=扫地僧
换取列表=舍利子
换取条件=江湖声望
long values:
换取数目=10000000
是否领取=1
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/扫地僧
object=npc/玄澄大师
object=npc/玄生大师
object=npc/澄明罗汉
object=npc/澄思罗汉
end of YObjectGroup