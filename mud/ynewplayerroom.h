//---------------------------------------------------------------------------
//
// ynewplayerroom.h    2000年8月23日
//
// 类YNewPlayerRoom：新人登录的专用房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YNEWPLAYERROOM_H__
#define __YNEWPLAYERROOM_H__
#include "yroom.h"
class YNewPlayerRoom : public YRoom {
  //属性：Declare(声明)
	private:
		YString m_Declare; //属性Declare(声明)的成员变量
	public:
		YString getDeclare(void) {return m_Declare;} //读属性Declare(声明)
		void setDeclare(YString newDeclare) {m_Declare=newDeclare;} //设置Declare(声明)
  //属性：OutRoom(出口房间)
	private:
		YString m_OutRoom; //属性OutRoom(出口房间)的成员变量
	public:
		YString getOutRoom(void) {return m_OutRoom;} //读属性OutRoom(出口房间)
		void setOutRoom(YString newOutRoom) {m_OutRoom=newOutRoom;} //设置OutRoom(出口房间)
  
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YNewPlayerRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
  public:
    YNewPlayerRoom(YString initFileName="");  //构造函数
    virtual ~YNewPlayerRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
  public:
    //事件onBeforeEnter的默认处理函数
    virtual int onBeforeEnter(YMUDObject* sender, YAbstractActor* actor);
    //事件onAfterLeave的默认处理函数
    virtual int onAfterLeave(YMUDObject* sender, YAbstractActor* actor);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
};

#endif //__YNEWPLAYERROOM_H__
