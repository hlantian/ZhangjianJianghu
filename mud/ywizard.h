//---------------------------------------------------------------------------
//
// ywizard.h    2001年5月21日
//
// 类YWizard：巫师
//
// 作者：刘鹏，张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YWIZARD_H__
#define __YWIZARD_H__

#include "yplayer.h"
#include "ylogfile.h"

class YWizard : public YPlayer{
public:
    YWizard(YUser* user, YString initFileName="");  //构造函数
    virtual ~YWizard(); //析构函数

    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YWizard");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YString command);

    virtual int cmd_goto(YString command);        //goto 命令---------去room
    virtual int wizgoto(YString sentence);        //wizgoto 命令------去player/npc的房间
    virtual int wizclose(YString sentence);       //wizclose 命令-----关闭频道
    virtual int wizopen(YString sentence);        //wizopen 命令------开启频道
    virtual int wizlook(YString sentence);        //wizlook 命令------查看player/npc属性
    virtual int wizlookroom(YString sentence);    //wizlook 命令------查看room属性
    virtual int wizset(YString sentence);         //wizset 命令-------设置long型属性
    virtual int wizsets(YString sentence);        //wizsets 命令------设置YString型属性
    virtual int wizsetadd(YString sentence);      //wizsetadd 命令----设置文字添加????
    virtual int wizsetaddsb(YString sentence);    //wizsetaddsb 命令--设置他人文字添加????
    virtual int wizsetsb(YString sentence);       //wizsetsb 命令-----设置他人long型属性
    virtual int wizsetssb(YString sentence);      //wizsetssb 命令----设置他人YString属性
    virtual int wizkick(YString sentence);        //wizkick 命令------使人物晕倒
    virtual int wizkickout(YString sentence);     //wizkickout 命令---强制他人退出游戏
    virtual int wizget(YString sentence);         //wizget 命令-------把人物抓到自己这里
    virtual int wizjianyu(YString sentence);         //wizjianyu 命令-------把人物抓到监狱
    virtual int wizfree(YString sentence);         //wizjianyu 命令-------把人物抓到监狱
    virtual int wizgetthing(YString sentence);         //wizgetthing 命令-------从别人人上拿东西
    virtual int wizchat(YString sentence);        //wizchat 命令------巫师专用公共频道
    virtual int timeuse(void);                    //timeuse 命令------查看系统参数
    virtual int cmd_reload(YString command);      //reload 命令-------重新装载object的属性
    virtual int wizcreate(YString command);       //wizcreate 命令----创造物品
    virtual int shutdown(YString sentence);       //shutdown 命令-----保存所有玩家数据
    virtual int uselevel(YString sentence);       //setuselevel 命令--设置"玩家级别"
    virtual int lookrumor(YString command);       //lookrumor 命令---- 察看谣言
    virtual int blackip(YString command);       //blackip 封锁ip命令
    virtual int unblackip(YString command);       //unblackip 去处封锁ip命令
    virtual int wizdisband(YString command);       //wizdisbandfaction 命令---- 巫师强制解散帮会
    
    virtual bool fnAllowSet(YString string);      //这个字符串是否允许set

public:
    YLogFile wizardlog;                           //纪录巫师命令的Log文件
};

#endif //__YWIZARD_H__
