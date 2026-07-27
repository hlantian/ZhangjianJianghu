//---------------------------------------------------------------------------
//
// YJollityRoom.h    2000年9月16日
//
// 类YJollityRoom：结婚开酒席的房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YJOLLITYROOM_H__
#define __YJOLLITYROOM_H__
#include "yroom.h"

class YJollityRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YJollityRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YJollityRoom(YString initFileName=""):YRoom(initFileName) {};  //构造函数
    virtual ~YJollityRoom(){}; //析构函数

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

    //实现开席后的时间处理
    virtual int onTimer(void); //10分钟的开席时间

    //各种命令处理
    virtual int eat(YAbstractActor* executor,YString command); //吃东西
    virtual int drink(YAbstractActor* executor,YString command); //吃东西
    virtual int kill(YAbstractActor* executor,YString command); //杀
    virtual int dazuo(YAbstractActor* executor,YString command); //打坐
    virtual int tuna(YAbstractActor* executor,YString command); //吐纳
   // virtual int look(YAbstractActor* executor,YString command); //两个人的对拜
};

#endif //__YJOLLITYROOM_H__
