//---------------------------------------------------------------------------
//
// YTailPlayer.h    2001年7月10日
//
// 类YTailPlayer
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YTAILPLAYER_H__
#define __YTAILPLAYER_H__

#include "yplayer.h"
#include "ylogfile.h"

class YTailPlayer : public YPlayer{
public:
    YTailPlayer(YUser* user, YString initFileName="");  //构造函数
    virtual ~YTailPlayer(); //析构函数

    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YTailPlayer");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YString command);

public:
    YLogFile tailplayerlog;                           //纪录巫师命令的Log文件
};

#endif //__YTAILPLAYER_H__
