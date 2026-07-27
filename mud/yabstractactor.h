//---------------------------------------------------------------------------
//
// yabstractactor.h    2000年6月12日
//
// 类YAbstractActor：提供抽象的人物特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YABSTRACTACTOR_H__
#define __YABSTRACTACTOR_H__

#include <queue>
#include "ymudobject.h"
#include "ystring.h"
#include "yfifo.h"
#include "ysession.h"

class YAbstractRoom;
class YAbstractThing;

class YAbstractActor : public YMUDObject {
  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);

  public:
  	YAbstractActor(YString initFileName="");  //构造函数
  	virtual ~YAbstractActor(){}; //析构函数

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YString command)=0;
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command)=0;
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YAbstractActor");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

	//属性：Icon(头像)
	public:
		virtual YString getIcon(void) {return "0";}; //读属性Icon(头像)
		virtual void setIcon(YString newIcon) {set("头像",newIcon);}; //设置Icon(头像)
	//属性：Room
	private:
		YAbstractRoom* m_Room; //属性Room的成员变量
	public:
		void setRoom(YAbstractRoom* newRoom);  //设置Room
		void setRoom(YString roomName);  //设置Room
		YAbstractRoom* getRoom(void) {return m_Room;} //读属性Room

	public:
  	//事件Message的默认处理函数
		virtual int onMessage(YAbstractActor* speaker, YString message);
  	//事件RoommateEnter的默认处理函数
		virtual int onRoommateEnter(YMUDObject* sender, YAbstractActor* actor);
  	//事件RoommateLeave的默认处理函数
		virtual int onRoommateLeave(YMUDObject* sender, YAbstractActor* actor);
  public:
    //接收一条消息
    virtual void message(YAbstractActor* speaker, YString msg, bool newline=true,
                      msg_type messagetype=ORIGINAL_MSG, const YString& name="");
    //给自己显示一些信息
    virtual void display(YString msg, bool newline=true,
                    msg_type messagetype=ORIGINAL_MSG, const YString& name="")
                    {message(NULL, msg, newline, messagetype, name);};

		//方法reload--重新从文件中读取属性
		virtual int reload(void);
};

#endif //__YABSTRACTACTOR_H__
