//---------------------------------------------------------------------------
//
// ybankroom.h    2000年8月7日
//
// 类YBankRoom：钱庄
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YBANKROOM_H__
#define __YBANKROOM_H__
#include "yroom.h"

class YBankRoom : public YRoom {
  public:
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YBankRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

  public:
		YBankRoom(YString initFileName=""): YRoom(initFileName) {};  //构造函数
		virtual ~YBankRoom(){}; //析构函数

  public:
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

  //各种命令处理
  public:
    virtual int cun(YAbstractActor* executor, YString command); //向钱庄存钱
    virtual int qu(YAbstractActor* executor, YString command);//从钱庄取钱
    virtual int convert(YAbstractActor* executor, YString command);//兑换货币
    virtual int check(YAbstractActor* executor);//查询存款
};

#endif //__YBANKROOM_H__
