//---------------------------------------------------------------------------
//
// yloadroom.h    2001年6月6日
//
// 类YLoadRoom：事先Load所有物品的Room
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YLOADROOM_H__
#define __YLOADROOM_H__
#include "yroom.h"

class YLoadRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YLoadRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YLoadRoom(YString initFileName="");  //构造函数
    virtual ~YLoadRoom(){}; //析构函数

    virtual int onTimer(void); //重载room的onTimer，目的在于取消所有room中的功能。
};

#endif //__YLOADROOM_H__
