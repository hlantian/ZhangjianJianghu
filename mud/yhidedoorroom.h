#ifndef __YHIDEDOORROOM_H__
#define __YHIDEDOORROOM_H__
#include "yroom.h"

class YHideDoorRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YHideDoorRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YHideDoorRoom(YString initFileName="");  //构造函数
    virtual ~YHideDoorRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    //事件onAfterLeave的默认处理函数
    virtual int onAfterLeave(YMUDObject* sender, YAbstractActor* actor);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

    //各种命令处理
    virtual int readly(YAbstractActor* executor,YString command); //要走前的准备
    virtual int next(YAbstractActor* executor,YString command); //要走的命令
};

#endif //__YHIDEDOORROOM_H__
