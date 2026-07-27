//---------------------------------------------------------------------------
//
// ydoorroom.h    2001年5月22日
//
// 类YDoorRoom：有守门NPC的Room
//
// 作者：刘鹏 张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YDOORROOM_H__
#define __YDOORROOM_H__
#include "yroom.h"

class YDoorRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YDoorRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YDoorRoom(YString initFileName="");  //构造函数
    virtual ~YDoorRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

    //各种命令处理
    virtual int fnWantGo(YAbstractActor* executor,YString command); //要走
};

#endif //__YDOORROOM_H__
