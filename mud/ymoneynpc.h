//---------------------------------------------------------------------------
//
// ymoneynpc.h    2001年2月14日
//
// 类YMoneyNPC：收取礼金的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YMONEYNPC_H__
#define __YMONEYNPC_H__

#include "ynpc.h"

class YMoneyNPC:public YNPC{

  public:
    YMoneyNPC(YString initFileName=""):YNPC(initFileName){}; //构造函数
    virtual ~YMoneyNPC(){}; //析构函数
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YMoneyNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
    //-------------------------------------------------
    //各种处理函数
    virtual int beAsk(YAbstractActor* executor,YString command);//询问
    virtual int beGive(YAbstractActor* executor,YString command);//递交贺礼
};

#endif //__YMONEYNPC_H__
