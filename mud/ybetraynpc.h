//---------------------------------------------------------------------------
//
// ybetraynpc.h    2001年1月3日
//
// 类YBetrayNPC：主管叛师的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YBETRAYNPC_H__
#define __YBETRAYNPC_H__

#include "ynpc.h"

class YBetrayNPC:public YNPC{

  public:
    YBetrayNPC(YString initFileName=""):YNPC(initFileName){}; //构造函数
    virtual ~YBetrayNPC(){}; //析构函数
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YBetrayNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
    //-------------------------------------------------
    //各种处理函数
    virtual int beAsk(YAbstractActor* executor,YString command);//别人问关于叛师
    virtual int beAnswer(YAbstractActor* executor,YString command);//别人回答叛师的问题
};

#endif //__YBETRAYNPC_H__

