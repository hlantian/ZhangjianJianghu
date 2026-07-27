#class=YDoorRoom
begin of YPropertyGroup
string values:
名字=监狱大门
描述=@LONG
    这里是牢房的大门口，大铁门前站着守牢房的狱卒。一阵阵极臭难闻的气味从铁门的另一端传过来，铁门的另一端是死囚牢，专门囚禁杀人重犯，是不容许探监的。<br>
    这里明显的出口是 <a href='javascript:sendmsg("e")'>东</a>、和<a href='javascript:sendmsg("w")'>西</a>
LONG
东=牢房
西=后院
NPC列表=狱卒
禁止方向列表=东
老板名字=狱卒
long values:
float values:
end of YPropertyGroup
begin of YObjectGroup
object=npc/狱卒
end of YObjectGroup