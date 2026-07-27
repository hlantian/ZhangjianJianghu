#class=YHideDoorRoom
begin of YPropertyGroup
string values:
名字=隐藏房间
准备命令=推门
隐藏前进命令=进入
限制前进方向=石洞
准备成功后显示=成功推开门
成功通过后显示=成功通过
失败通过后显示=失败，没有通过。
进入条件=年龄
准备条件=门派
门派=华山派
准备失败后显示=准备失败
石洞=领悟
描述=@LONG
    这里就是酆都城的城门,俗称[鬼门关]的所在。路两边站着很多小鬼,手里拿着五颜六色的小旗子,一边摇一边喊着:欢迎,欢迎,热烈欢迎~~~。<br>
    这里明显的出口是<a href='javascript:sendmsg("out")'>外面</a>。
LONG
外面=/room/长安/城隍庙
long values:
年龄=20
float values:
end of YPropertyGroup
begin of YObjectGroup
end of YObjectGroup
