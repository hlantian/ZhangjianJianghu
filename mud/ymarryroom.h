
#ifndef __YMARRYROOM_H__
#define __YMARRYROOM_H__
#include "yroom.h"

class YMarryRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YMarryRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YMarryRoom(YString initFileName=""):YRoom(initFileName) {};  //构造函数
    virtual ~YMarryRoom(){}; //析构函数

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

    //各种命令处理
    virtual int marry(YAbstractActor* executor,YString command); //marry sb. 还要检验一下媒婆做在媒婆身上有传递的问题所以在房间中
    virtual int bai(YAbstractActor* executor,YString command); //两个人的对拜
    virtual int zeng(YAbstractActor* executor,YString command); //赠信物
    virtual int xian(YAbstractActor* executor,YString command); //掀盖头
    virtual int qing(YAbstractActor* executor,YString command); //请宾客
    virtual int unmarry(YAbstractActor* executor,YString command); //离婚
};

#endif //__YMARRYROOM_H__
 
