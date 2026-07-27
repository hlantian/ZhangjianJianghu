#class=YMarryNPC
begin of YPropertyGroup
string values:
名字=吴知远
性别=男
头衔=扬州知府
描述=他面带威严，长髯垂胸，乃是本地的知府大人。
衣服=官服
空手_攻击武功=基本拳脚
离婚=眉头一皱：“夫妻乃前世缘分，两位难道真无一点情谊了吗？”
货币种类=金子
货币种类不对时说话=只要金子，别的不要！

小于最少收费时说话=钱太少！

没钱时的说话=你没钱！

钱不够时说话=钱不够！

条件符合时说话=前世因，今世果，夫妻情绝，莫可奈何……
无配偶时说话=此乃两个人的事情，岂容你一个人在此瞎闹！

给钱成功后说话=@LONG
    你可以用 unmarry somebody 离婚了。
LONG
long values:
最小收费=50
办理离婚=1
年龄=40
容貌=80
气血=5000
最大气血=5000
固定攻击力=5000
固定防御力=5000
float values:
end of YPropertyGroup
begin of YObjectGroup
object=thing/官服
end of YObjectGroup