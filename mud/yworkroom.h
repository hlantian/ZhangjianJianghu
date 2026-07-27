//---------------------------------------------------------------------------
//
// yworkroom.h    2000年9月16日
//
// 类YWorkRoom：做劳动任务的房间(钓鱼,酿蜜...)
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YWORKROOM_H__
#define __YWORKROOM_H__
#include "yroom.h"

class YWorkRoom : public YRoom{
  //属性：WorkType(劳动种类)
	private:
		YString m_WorkType; //属性WorkType(劳动种类)的成员变量
	public:
		YString getWorkType(void) {return m_WorkType;} //读属性WorkType(劳动种类)
		void setWorkType(YString newWorkType) {m_WorkType=newWorkType;} //设置WorkType(劳动种类)
  
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YWorkRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YWorkRoom(YString initFileName="");  //构造函数
    virtual ~YWorkRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    //事件onBeforeLeave的默认处理函数
    virtual int onBeforeLeave(YMUDObject* sender, YAbstractActor* actor);

    //各种命令处理
    virtual int ask(YAbstractActor* executor,YString command); //ask sb. about sth.
    virtual int work(YAbstractActor* executor); //各种劳动
};

#endif //__YWORKROOM_H__
