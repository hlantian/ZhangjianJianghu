//---------------------------------------------------------------------------
//
// yliandanroom.h    2001年7月17日
//
// 类YLIAMDANROOM：生成丹药的房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YYLIANDANROOM_H__
#define __YYLIANDANROOM_H__
#include "yroom.h"

class YLianDanRoom: public YRoom{
public:

    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YLianDanRoom");}

    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    YLianDanRoom(YString initFileName="");  //构造函数
    virtual ~YLianDanRoom(){}; //析构函数
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

};

#endif //__YYLIANDANROOM_H__

