//---------------------------------------------------------------------------
//
// yofferrewardnpc.h    2001年1月12日
//
// 类YOfferRewardNPC：主管悬赏杀人的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YOFFERREWARDNPC_H__
#define __YOFFERREWARDNPC_H__

#define MAXNUMBER 20

#include "ynpc.h"

class YOfferRewardNPC:public YNPC{
  //属性：IsNotOfferReward(是否悬赏)
	private:
		long m_IsNotOfferReward; //属性IsNotOfferReward(是否悬赏)的成员变量
	public:
		long getIsNotOfferReward(void) {return m_IsNotOfferReward;} //读属性IsNotOfferReward(是否悬赏)
		void setIsNotOfferReward(long newIsNotOfferReward) {m_IsNotOfferReward=newIsNotOfferReward;} //设置IsNotOfferReward(是否悬赏)
  
  public:
    YOfferRewardNPC(YString initFileName=""); //构造函数
    virtual ~YOfferRewardNPC(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YOfferRewardNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
    //-------------------------------------------------
    //各种处理函数
    virtual int beXuanshang(YAbstractActor* executor,YString command);//悬赏杀某人
    virtual int beList(YAbstractActor* executor,YString command);//察看目前的悬赏情况
    virtual int beGive(YAbstractActor* executor,YString command);//递交首级并领取赏金
  public:
    YString offerreward[MAXNUMBER];
};

#endif //__YOFFERREWARDNPC_H__


