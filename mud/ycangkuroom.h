//---------------------------------------------------------------------------
//
// Ycangkuroom.h    2004年8月27日
//
// 类Ycangkuroom：仓库的房间
//
// 作者：龚丽炜
//
//---------------------------------------------------------------------------

#ifndef __Ycangkuroom_H__
#define __Ycangkuroom_H__
#include "yroom.h"

class Ycangkuroom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("Ycangkuroom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    Ycangkuroom(YString initFileName="");  //构造函数
    virtual ~Ycangkuroom(){}; //析构函数

    
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    //各种命令处理
    virtual int daxiao(YAbstractActor* executor,YString command); //存物品
    virtual int dianshu(YAbstractActor* executor,YString command); //取物品
};

#endif //__YYELIANROOM_H__
