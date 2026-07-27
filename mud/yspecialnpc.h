//---------------------------------------------------------------------------
//
// yspecialnpc.h    2001年3月19日
//
// 类YSpecialNPC：特殊功能NPC(主动杀人，进入说话，主动行走，循环说话)
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YSPECIALNPC_H__
#define __YSPECIALNPC_H__

#include "ynpc.h"

class YSpecialNPC:public YNPC{

  //属性：WalkTimeInterval(行走时间间隔)
	private:
		long m_WalkTimeInterval; //属性WalkTimeInterval(行走时间间隔)的成员变量
	public:
		long getWalkTimeInterval(void) {return m_WalkTimeInterval;} //读属性WalkTimeInterval(行走时间间隔)
		void setWalkTimeInterval(long newWalkTimeInterval) {m_WalkTimeInterval=newWalkTimeInterval;} //设置WalkTimeInterval(行走时间间隔)
  //属性：WalkTime(行走时间)
	private:
		long m_WalkTime; //属性WalkTime(行走时间)的成员变量
	public:
		long getWalkTime(void) {return m_WalkTime;} //读属性WalkTime(行走时间)
		void setWalkTime(long newWalkTime) {m_WalkTime=newWalkTime;} //设置WalkTime(行走时间)
  //属性：LoopSpeak(循环说话)
	private:
		long m_LoopSpeak; //属性LoopSpeak(循环说话)的成员变量
	public:
		long getLoopSpeak(void) {return m_LoopSpeak;} //读属性LoopSpeak(循环说话)
		void setLoopSpeak(long newLoopSpeak) {m_LoopSpeak=newLoopSpeak;} //设置LoopSpeak(循环说话)
  //属性：KillTimeInterval(杀人时间间隔)
	private:
		long m_KillTimeInterval; //属性KillTimeInterval(杀人时间间隔)的成员变量
	public:
		long getKillTimeInterval(void) {return m_KillTimeInterval;} //读属性KillTimeInterval(杀人时间间隔)
  	void setKillTimeInterval(long newKillTimeInterval) {m_KillTimeInterval=newKillTimeInterval;} //设置KillTimeInterval(杀人时间间隔)
  //属性：KillTime(杀人时间)
	private:
		long m_KillTime; //属性KillTime(杀人时间)的成员变量
	public:
		long getKillTime(void) {return m_KillTime;} //读属性KillTime(杀人时间)
		void setKillTime(long newKillTime) {m_KillTime=newKillTime;} //设置KillTime(杀人时间)
  //属性：SpeakTime(说话时间)
	private:
		long m_SpeakTime; //属性SpeakTime(说话时间)的成员变量
	public:
		long getSpeakTime(void) {return m_SpeakTime;} //读属性SpeakTime(说话时间)
		void setSpeakTime(long newSpeakTime) {m_SpeakTime=newSpeakTime;} //设置SpeakTime(说话时间)
  //属性：WordCount(话的个数)
	private:
		long m_WordCount; //属性WordCount(话的个数)的成员变量
	public:
		long getWordCount(void) {return m_WordCount;} //读属性WordCount(话的个数)
		void setWordCount(long newWordCount) {m_WordCount=newWordCount;} //设置WordCount(话的个数)
  //属性：SpeakTimeInterval(说话时间间隔)
	private:
		long m_SpeakTimeInterval; //属性SpeakTimeInterval(说话时间间隔)的成员变量
	public:
		long getSpeakTimeInterval(void) {return m_SpeakTimeInterval;} //读属性SpeakTimeInterval(说话时间间隔)
		void setSpeakTimeInterval(long newSpeakTimeInterval) {m_SpeakTimeInterval=newSpeakTimeInterval;} //设置SpeakTimeInterval(说话时间间隔)
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
  //属性：EnterKill(进入时杀人)
	private:
		long m_EnterKill; //属性EnterKill(进入时杀人)的成员变量
	public:
		long getEnterKill(void) {return m_EnterKill;} //读属性EnterKill(进入时杀人)
		void setEnterKill(long newEnterKill) {m_EnterKill=newEnterKill;} //设置EnterKill(进入时杀人)
  //属性：BeLook(被看)
	private:
		YString m_BeLook; //属性BeLook(被看)的成员变量
	public:
		YString getBeLook(void) {return m_BeLook;} //读属性BeLook(被看)
		void setBeLook(YString newBeLook) {m_BeLook=newBeLook;} //设置BeLook(被看)
  //属性：KillWhenBeLook(被看时杀人)
	private:
		long m_KillWhenBeLook; //属性KillWhenBeLook(被看时杀人)的成员变量
	public:
		long getKillWhenBeLook(void) {return m_KillWhenBeLook;} //读属性KillWhenBeLook(被看时杀人)
		void setKillWhenBeLook(long newKillWhenBeLook) {m_KillWhenBeLook=newKillWhenBeLook;} //设置KillWhenBeLook(被看时杀人)
  
  public:
    YSpecialNPC(YString initFileName=""); //构造函数
    virtual ~YSpecialNPC(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YSpecialNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //作为动作的承受者处理命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);

    //各种处理函数
    virtual int beLook(YAbstractActor* executor,YString command);//被别人看
    virtual int beAsk(YAbstractActor* executor,YString command);//被别人询问

    //事件Timer的默认处理函数
    virtual int onTimer(void);
    //事件RoommateEnter的默认处理函数
    virtual int onRoommateEnter(YMUDObject* sender, YAbstractActor* actor);

    //其他函数
    virtual int loopSpeak(void); //循环说话
    virtual int letsAutoWalk(void); //自动行走
    virtual int letsInitiativeKill(void); //主动杀人
};

#endif //__YSPECIALNPC_H__
