//---------------------------------------------------------------------------
//
// yabstractroom.h    2000年6月12日
//
// 类YAbstractRoom：提供抽象的Room(Player活动场所的基本单位)特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YABSTRACTROOM_H__
#define __YABSTRACTROOM_H__

#include "ymudobject.h"
#include "ychat.h"

class YAbstractActor;
class YAbstractThing;

class YAbstractRoom : public YMUDObject{

	//属性：RoomChat
	private:
		YChat* m_RoomChat; //属性RoomChat的成员变量
	public:
		YChat* getRoomChat(void) {return m_RoomChat;} //读属性RoomChat
  //属性：RoomDescribe(描述)
	private:
		YString m_RoomDescribe; //属性RoomDescribe(描述)的成员变量
	public:
		YString getRoomDescribe(void) {return m_RoomDescribe;} //读属性RoomDescribe(描述)
		void setRoomDescribe(YString newRoomDescribe) {m_RoomDescribe=newRoomDescribe;} //设置RoomDescribe(描述)

  public:
		//事件onBeforeEnter的默认处理函数
		virtual int onBeforeEnter(YMUDObject* sender, YAbstractActor* actor);
		//事件onAfterEnter的默认处理函数
		virtual int onAfterEnter(YMUDObject* sender, YAbstractActor* actor);
		//事件onBeforeLeave的默认处理函数
		virtual int onBeforeLeave(YMUDObject* sender, YAbstractActor* actor);
		//事件onAfterLeave的默认处理函数
		virtual int onAfterLeave(YMUDObject* sender, YAbstractActor* actor);
		//事件BeforeChildAdd的默认处理函数
		virtual int onBeforeChildAdd(YMUDObject* sender, YMUDObject* child);
		//事件AfterChildAdd的默认处理函数
		virtual int onAfterChildAdd(YMUDObject* sender, YMUDObject* child);
		//事件BeforeChildRemove的默认处理函数
		virtual int onBeforeChildRemove(YMUDObject* sender, YMUDObject* child);
		//事件AfterChildRemove的默认处理函数
		virtual int onAfterChildRemove(YMUDObject* sender, YMUDObject* child);
		//事件Init的默认处理函数
		virtual int onInit(void);

  public:
	  YAbstractRoom(YString initFileName="");  //构造函数
	  virtual ~YAbstractRoom(){delete m_RoomChat;}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YAbstractRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command){return 1;}; //作为场所
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command)=0;
    //将一角色移动到另一房间(0-成功，2-该场所无法装载，3-房间不允许出/入)
    virtual int sendActorToRoom(YAbstractActor* actor, YString roomName);

};

#endif //__YABSTRACTROOM_H__
