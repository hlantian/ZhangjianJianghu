//---------------------------------------------------------------------------
//
// YMarryNPC.cpp    2000年10月16日
//
// 类YMarryNPC：媒婆NPC
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YMarryNPC_H__
#define __YMarryNPC_H__

#include "ynpc.h"

class YMarryNPC:public YNPC{

  public:
    YMarryNPC(YString initFileName=""):YNPC(initFileName){}; //构造函数
    virtual ~YMarryNPC(){}; //析构函数
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YMarryNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
    //-------------------------------------------------
    //各种处理函数
    virtual int Give(YAbstractActor* executor,YString command);//别人给东西
    virtual int Ask(YAbstractActor* executor,YString command);//被别人问
    //事件RoommateEnter的默认处理函数
    virtual int onRoommateEnter(YMUDObject* sender, YAbstractActor* actor);
};

#endif //__YMarryNPC_H__
