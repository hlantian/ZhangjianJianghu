//---------------------------------------------------------------------------
//
// ycookroom.h    2000年8月4日
//
// 类YCookRoom：厨房
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YCOOKROOM_H__
#define __YCOOKROOM_H__
#include "yroom.h"

class YCookRoom : public YRoom {
  //属性：ForbidTakeOut(禁止带出)
	private:
		long m_ForbidTakeOut; //属性ForbidTakeOut(禁止带出)的成员变量
	public:
		long getForbidTakeOut(void) {return m_ForbidTakeOut;} //读属性ForbidTakeOut(禁止带出)
		void setForbidTakeOut(long newForbidTakeOut) {m_ForbidTakeOut=newForbidTakeOut;} //设置ForbidTakeOut(禁止带出)
  //属性：OfferFoodList(所提供食物的列表)
	private:
		YString m_OfferFoodList; //属性OfferFoodList(所提供食物的列表)的成员变量
	public:
		YString getOfferFoodList(void) {return m_OfferFoodList;} //读属性OfferFoodList(所提供食物的列表)
		void setOfferFoodList(YString newOfferFoodList) {m_OfferFoodList=newOfferFoodList;} //设置OfferFoodList(所提供食物的列表)
  
  public:
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YCookRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

  public:
		//事件onBeforeLeave的默认处理函数
		virtual int onBeforeLeave(YMUDObject* sender, YAbstractActor* actor);

  public:
		YCookRoom(YString initFileName="");  //构造函数
		virtual ~YCookRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

  public:
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

  //各种命令处理
  public:
    virtual int serve(YAbstractActor* executor); //向侍童要食物和水
};

#endif //__YCOOKROOM_H__
