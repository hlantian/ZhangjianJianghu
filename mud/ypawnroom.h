//---------------------------------------------------------------------------
//
// ypawnroom.h    2000年8月9日
//
// 类YPawnRoom：当铺
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YPAWNROOM_H__
#define __YPAWNROOM_H__
#include "yroom.h"

class YPawnRoom : public YRoom {
  //属性：IsNotSell(是否收购)
	private:
		YString m_IsNotSell; //属性IsNotSell(是否收购)的成员变量
	public:
		YString getIsNotSell(void) {return m_IsNotSell;} //读属性IsNotSell(是否收购)
		void setIsNotSell(YString newIsNotSell) {m_IsNotSell=newIsNotSell;} //设置IsNotSell(是否收购)
  //属性：SellThingNoChange(销售物品不变)
	private:
		long m_SellThingNoChange; //属性SellThingNoChange(销售物品不变)的成员变量
	public:
		long getSellThingNoChange(void) {return m_SellThingNoChange;} //读属性SellThingNoChange(销售物品不变)
		void setSellThingNoChange(long newSellThingNoChange) {m_SellThingNoChange=newSellThingNoChange;} //设置SellThingNoChange(销售物品不变)
  //属性：ChaKanFuYuan(查看福缘)
	private:
		long m_ChaKanFuYuan; //属性ChaKanFuYuan(查看福缘)的成员变量
	public:
		long getChaKanFuYuan(void) {return m_ChaKanFuYuan;} //读属性ChaKanFuYuan(查看福缘)
		void setChaKanFuYuan(long newChaKanFuYuan) {m_ChaKanFuYuan=newChaKanFuYuan;} //设置ChaKanFuYuan(查看福缘)
  //属性：PawnPercent(典当百分比)
	private:
		long m_PawnPercent; //属性PawnPercent(典当百分比)的成员变量
	public:
		long getPawnPercent(void) {return m_PawnPercent;} //读属性PawnPercent(典当百分比)
		void setPawnPercent(long newPawnPercent) {m_PawnPercent=newPawnPercent;} //设置PawnPercent(典当百分比)
  //属性：PawnThingList(当铺老板的物品)
	private:
		YString m_PawnThingList; //属性PawnThingList(当铺老板的物品)的成员变量
	public:
		YString getPawnThingList(void) {return m_PawnThingList;} //读属性PawnThingList(当铺老板的物品)
		void setPawnThingList(YString newPawnThingList) {m_PawnThingList=newPawnThingList;} //设置PawnThingList(当铺老板的物品)
  
  public:
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YPawnRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

  public:
		YPawnRoom(YString initFileName="");  //构造函数
		virtual ~YPawnRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    

  public:
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor,YString command); //作为场所
  //各种命令处理
  public:
    virtual int sell(YAbstractActor* executor,YString command);//卖出物品
    virtual int buy(YAbstractActor* executor,YString command);//购买物品
    virtual int list(YAbstractActor* executor,YString command);//列出物品清单
    virtual int lookfy(YAbstractActor* executor);//福缘    
    //自编函数
    virtual long getPrice(YPlayer* player,YString sThing); //得到某物品价格
};

#endif //__YPAWNROOM_H__
