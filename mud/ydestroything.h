//---------------------------------------------------------------------------
//
// ydestroything.h    2001年2月6日
//
// 类YDestroyThing：可销毁的物品
//
// 作者：叶林 张勇 刘鹏  单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YDESTROYTHING_H__
#define __YDESTROYTHING_H__
#include "ything.h"

class YDestroyThing : public YThing {
  public:
		YDestroyThing(YString initFileName="");  //构造函数
		virtual ~YDestroyThing(){}; //析构函数

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YDestroyThing");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为中介物体
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);

    //zhy
    virtual int addToDestroyList(void); //添加到父物体的销毁列表
    virtual int onTimer(void); //事件Timer的默认处理函数
};

#endif //__YDESTROYTHING_H__
