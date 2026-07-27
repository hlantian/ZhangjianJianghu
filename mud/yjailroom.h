//---------------------------------------------------------------------------
//
// yjailroom.h    2001年2月19日
//
// 类YJailRoom：监狱
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YJAILROOM_H__
#define __YJAILROOM_H__
#include "yroom.h"

class YJailRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YJailRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    YJailRoom(YString initFileName=""):YRoom(initFileName) {};  //构造函数
    virtual ~YJailRoom(){}; //析构函数

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    //监禁中
    virtual int jail(YAbstractActor* executor); //监禁中
};

#endif //__YJAILROOM_H__
