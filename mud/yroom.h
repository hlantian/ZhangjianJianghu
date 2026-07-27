//---------------------------------------------------------------------------
//
// yroom.h    2000年6月12日
//
// 类YRoom：房间/地点
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YROOM_H__
#define __YROOM_H__
#include "yabstractroom.h"
class YActor;

class YRoom : public YAbstractRoom{

  //属性：UpdateTime(刷新时间)
	private:
		long m_UpdateTime; //属性UpdateTime(刷新时间)的成员变量
	public:
		long getUpdateTime(void) {return m_UpdateTime;} //读属性UpdateTime(刷新时间)
		void setUpdateTime(long newUpdateTime) {m_UpdateTime=newUpdateTime;} //设置UpdateTime(刷新时间)
  //属性：DestroyList(销毁列表)
	private:
		YString m_DestroyList; //属性DestroyList(销毁列表)的成员变量
	public:
		YString getDestroyList(void) {return m_DestroyList;} //读属性DestroyList(销毁列表)
		void setDestroyList(YString newDestroyList) {m_DestroyList=newDestroyList;} //设置DestroyList(销毁列表)
  //属性：RoomName(房间名字)
	private:
		//YString m_RoomName; //属性RoomName(房间名字)的成员变量
	public:
		YString getRoomName(void) {return getObjectName();} //读属性RoomName(房间名字)
		void setRoomName(YString newRoomName) {setObjectName(newRoomName);} //设置RoomName(房间名字)
  //属性：ThingList(物品列表)
	private:
		YString m_ThingList; //属性ThingList(物品列表)的成员变量
	public:
		YString getThingList(void) {return m_ThingList;} //读属性ThingList(物品列表)
		void setThingList(YString newThingList) {m_ThingList=newThingList;} //设置ThingList(物品列表)
  //属性：NPCList(NPC列表)
	private:
		YString m_NPCList; //属性NPCList(NPC列表)的成员变量
	public:
		YString getNPCList(void) {return m_NPCList;} //读属性NPCList(NPC列表)
		void setNPCList(YString newNPCList) {m_NPCList=newNPCList;} //设置NPCList(NPC列表)
  //属性：UpdateTimeInterval(刷新时间间隔)
	private:
		long m_UpdateTimeInterval; //属性UpdateTimeInterval(刷新时间间隔)的成员变量
	public:
		long getUpdateTimeInterval(void) {return m_UpdateTimeInterval;} //读属性UpdateTimeInterval(刷新时间间隔)
		void setUpdateTimeInterval(long newUpdateTimeInterval) {m_UpdateTimeInterval=newUpdateTimeInterval;} //设置UpdateTimeInterval(刷新时间间隔)
  //属性：ForbidFight(禁止战斗)
	private:
		long m_ForbidFight; //属性ForbidFight(禁止战斗)的成员变量
	public:
		long getForbidFight(void) {return m_ForbidFight;} //读属性ForbidFight(禁止战斗)
		void setForbidFight(long newForbidFight) {m_ForbidFight=newForbidFight;} //设置ForbidFight(禁止战斗)
  //属性：BossName(老板名字)
	private:
		YString m_BossName; //属性BossName(老板名字)的成员变量
	public:
		YString getBossName(void) {return m_BossName;} //读属性BossName(老板名字)
		void setBossName(YString newBossName) {m_BossName=newBossName;} //设置BossName(老板名字)
  //属性：FoodConsume(饮食消耗)
	private:
		long m_FoodConsume; //属性FoodConsume(饮食消耗)的成员变量
	public:
		long getFoodConsume(void) {return m_FoodConsume;} //读属性FoodConsume(饮食消耗)
		void setFoodConsume(long newFoodConsume) {m_FoodConsume=newFoodConsume;} //设置FoodConsume(饮食消耗)
  //属性：PlayListQuit(人物退出列表)
        private:
                YString m_PlayListQuit; //属性PlayListQuit(人物退出列表)
        public:
                YString getPlayListQuit(void) {return m_PlayListQuit;}//读属性PlayListQuit(人物退出列表)
                void setPlayListQuit(YString newPlayListQuit) {m_PlayListQuit=newPlayListQuit;}//设置属性PlayListQuit(人物退出列表)

  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);
    
  public:
		YRoom(YString initFileName="");  //构造函数
		virtual ~YRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);

		//事件onBeforeEnter的默认处理函数
		virtual int onBeforeEnter(YMUDObject* sender, YAbstractActor* actor);
		//事件onAfterEnter的默认处理函数
		virtual int onAfterEnter(YMUDObject* sender, YAbstractActor* actor);
		//事件onAfterLeave的默认处理函数
		virtual int onAfterLeave(YMUDObject* sender, YAbstractActor* actor);

    //将一角色移动到另一房间(0-成功，1-该方向无出口，2-该场所无法装载)
    virtual int sendActorTo(YActor* actor, YString direction);

  //各种命令处理
  public:
    virtual int showActors(YActor* receiver);//显示房间里的人员列表
    virtual int showNickActors(YActor* receiver);//显示房间里的人员列表(带绰号得)
    virtual int showThings(YActor* receiver);//显示房间里的物体列表
    virtual int quit(YAbstractActor* player); //玩家退出MUD
    virtual int cunquit(YAbstractActor* player,YString command); //保存任务退出

    //lp
    virtual int playerquit(void); //room 对玩家进行退出处理
    //将子物体传给另一物体
    virtual bool giveChildTo(YMUDObject* child, YMUDObject* another, long count=1, long No=1);

    //zhy
    virtual int onTimer(void); //15分钟刷新
    virtual int letsUpdate(void); //实现刷新
    virtual int letsDestroy(void); //销毁子物品
};

#endif //__YROOM_H__
