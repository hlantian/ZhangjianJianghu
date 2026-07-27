//---------------------------------------------------------------------------
//
// yteachernpc.h    2000年10月16日
//
// 类YTeacherNPC：教基本功的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YTEACHERNPC_H__
#define __YTEACHERNPC_H__

#include "ynpc.h"

class YTeacherNPC:public YNPC{
  //属性：EnterSay(进入时说话)
	private:
		long m_EnterSay; //属性EnterSay(进入时说话)的成员变量
	public:
		long getEnterSay(void) {return m_EnterSay;} //读属性EnterSay(进入时说话)
		void setEnterSay(long newEnterSay) {m_EnterSay=newEnterSay;} //设置EnterSay(进入时说话)
  //属性：CommonSay(普通说话)
	private:
		YString m_CommonSay; //属性CommonSay(普通说话)的成员变量
	public:
		YString getCommonSay(void) {return m_CommonSay;} //读属性CommonSay(普通说话)
		void setCommonSay(YString newCommonSay) {m_CommonSay=newCommonSay;} //设置CommonSay(普通说话)
  //属性：GiveMoneySay(缴完学费说话)
	private:
		YString m_GiveMoneySay; //属性GiveMoneySay(缴完学费说话)的成员变量
	public:
		YString getGiveMoneySay(void) {return m_GiveMoneySay;} //读属性GiveMoneySay(缴完学费说话)
		void setGiveMoneySay(YString newGiveMoneySay) {m_GiveMoneySay=newGiveMoneySay;} //设置GiveMoneySay(缴完学费说话)
  
  public:
    YTeacherNPC(YString initFileName=""); //构造函数
    virtual ~YTeacherNPC(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YTeacherNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
    //-------------------------------------------------
    //各种处理函数
    virtual int beGive(YAbstractActor* executor,YString command);//别人给东西
    virtual int beXue(YAbstractActor* executor,YString command);//被学习
    //事件RoommateEnter的默认处理函数
    virtual int onRoommateEnter(YMUDObject* sender, YAbstractActor* actor);
};

#endif //__YTEACHERNPC_H__
