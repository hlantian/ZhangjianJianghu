//---------------------------------------------------------------------------
//
// ynpc.h    2000年6月12日
//
// 类YNPC：NPC
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YNPC_H__
#define __YNPC_H__

#include "yactor.h"

class YNPC : public YActor{
  
  //属性：AllowPrentice(收徒)
	private:
		long m_AllowPrentice; //属性AllowPrentice(收徒)的成员变量
	public:
		long getAllowPrentice(void) {return m_AllowPrentice;} //读属性AllowPrentice(收徒)
		void setAllowPrentice(long newAllowPrentice) {m_AllowPrentice=newAllowPrentice;} //设置AllowPrentice(收徒)
  //属性：AnswerForAgreePrentice(同意拜师的回答)
	private:
		YString m_AnswerForAgreePrentice; //属性AnswerForAgreePrentice(同意拜师的回答)的成员变量
	public:
		YString getAnswerForAgreePrentice(void) {return m_AnswerForAgreePrentice;} //读属性AnswerForAgreePrentice(同意拜师的回答)
		void setAnswerForAgreePrentice(YString newAnswerForAgreePrentice) {m_AnswerForAgreePrentice=newAnswerForAgreePrentice;} //设置AnswerForAgreePrentice(同意拜师的回答)
  //属性：ProvideQuest(是否发任务)
	private:
		long m_ProvideQuest; //属性ProvideQuest(是否发任务)的成员变量
	public:
		long getProvideQuest(void) {return m_ProvideQuest;} //读属性ProvideQuest(是否发任务)
		void setProvideQuest(long newProvideQuest) {m_ProvideQuest=newProvideQuest;} //设置ProvideQuest(是否发任务)
  //属性：NeedPate(需要首级)
	private:
		long m_NeedPate; //属性NeedPate(需要首级)的成员变量
	public:
		long getNeedPate(void) {return m_NeedPate;} //读属性NeedPate(需要首级)
		void setNeedPate(long newNeedPate) {m_NeedPate=newNeedPate;} //设置NeedPate(需要首级)
  //属性：NeedKillBySelf(需亲自杀)
	private:
		long m_NeedKillBySelf; //属性NeedKillBySelf(需亲自杀)的成员变量
	public:
		long getNeedKillBySelf(void) {return m_NeedKillBySelf;} //读属性NeedKillBySelf(需亲自杀)
		void setNeedKillBySelf(long newNeedKillBySelf) {m_NeedKillBySelf=newNeedKillBySelf;} //设置NeedKillBySelf(需亲自杀)
  //属性：NeedGeBySelf(需亲自割)
	private:
		long m_NeedGeBySelf; //属性NeedGeBySelf(需亲自割)的成员变量
	public:
		long getNeedGeBySelf(void) {return m_NeedGeBySelf;} //读属性NeedGeBySelf(需亲自割)
		void setNeedGeBySelf(long newNeedGeBySelf) {m_NeedGeBySelf=newNeedGeBySelf;} //设置NeedGeBySelf(需亲自割)
  //属性：PlayerSayWhenGiveup(玩家放弃时说话)
	private:
		YString m_PlayerSayWhenGiveup; //属性PlayerSayWhenGiveup(玩家放弃时说话)的成员变量
	public:
		YString getPlayerSayWhenGiveup(void) {return m_PlayerSayWhenGiveup;} //读属性PlayerSayWhenGiveup(玩家放弃时说话)
		void setPlayerSayWhenGiveup(YString newPlayerSayWhenGiveup) {m_PlayerSayWhenGiveup=newPlayerSayWhenGiveup;} //设置PlayerSayWhenGiveup(玩家放弃时说话)
  //属性：NPCSayWhenNoQuest(无任务说话)
	private:
		YString m_NPCSayWhenNoQuest; //属性NPCSayWhenNoQuest(无任务说话)的成员变量
	public:
		YString getNPCSayWhenNoQuest(void) {return m_NPCSayWhenNoQuest;} //读属性NPCSayWhenNoQuest(无任务说话)
		void setNPCSayWhenNoQuest(YString newNPCSayWhenNoQuest) {m_NPCSayWhenNoQuest=newNPCSayWhenNoQuest;} //设置NPCSayWhenNoQuest(无任务说话)
  //属性：NPCSayWhenGiveup(被放弃任务说话)
	private:
		YString m_NPCSayWhenGiveup; //属性NPCSayWhenGiveup(被放弃任务说话)的成员变量
	public:
		YString getNPCSayWhenGiveup(void) {return m_NPCSayWhenGiveup;} //读属性NPCSayWhenGiveup(被放弃任务说话)
		void setNPCSayWhenGiveup(YString newNPCSayWhenGiveup) {m_NPCSayWhenGiveup=newNPCSayWhenGiveup;} //设置NPCSayWhenGiveup(被放弃任务说话)
  //属性：AppraiseName(评价名)
	private:
		YString m_AppraiseName; //属性AppraiseName(评价名)的成员变量
	public:
		YString getAppraiseName(void) {return m_AppraiseName;} //读属性AppraiseName(评价名)
		void setAppraiseName(YString newAppraiseName) {m_AppraiseName=newAppraiseName;} //设置AppraiseName(评价名)
  //属性：NPCSayWhenBeGive(被给时说话)
	private:
		YString m_NPCSayWhenBeGive; //属性NPCSayWhenBeGive(被给时说话)的成员变量
	public:
		YString getNPCSayWhenBeGive(void) {return m_NPCSayWhenBeGive;} //读属性NPCSayWhenBeGive(被给时说话)
		void setNPCSayWhenBeGive(YString newNPCSayWhenBeGive) {m_NPCSayWhenBeGive=newNPCSayWhenBeGive;} //设置NPCSayWhenBeGive(被给时说话)
  //属性：NPCSayWhenEndQuest(被完成任务说话)
	private:
		YString m_NPCSayWhenEndQuest; //属性NPCSayWhenEndQuest(被完成任务说话)的成员变量
	public:
		YString getNPCSayWhenEndQuest(void) {return m_NPCSayWhenEndQuest;} //读属性NPCSayWhenEndQuest(被完成任务说话)
		void setNPCSayWhenEndQuest(YString newNPCSayWhenEndQuest) {m_NPCSayWhenEndQuest=newNPCSayWhenEndQuest;} //设置NPCSayWhenEndQuest(被完成任务说话)
  //属性：UniteKill(联合协防)
	private:
		long m_UniteKill; //属性UniteKill(联合协防)的成员变量
	public:
		long getUniteKill(void) {return m_UniteKill;} //读属性UniteKill(联合协防)
		void setUniteKill(long newUniteKill) {m_UniteKill=newUniteKill;} //设置UniteKill(联合协防)
  
  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);
    virtual YString getNickName(void);

  public:
    YNPC(YString initFileName=""); //构造函数
    virtual ~YNPC(); //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YNPC");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    //被动执行命令
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);

    virtual int beGive(YAbstractActor* executor,YString command);//别人给东西
    virtual int beAsk(YAbstractActor* executor,YString command);//被别人询问
    virtual int beBai(YAbstractActor* executor,YString command);//被拜师
    virtual int beXue(YAbstractActor* executor,YString command);//被学习
    virtual int becunquit(YAbstractActor* executor,YString command);//被存任务
    virtual int beQuest(YAbstractActor* executor);//被领取任务
    virtual int beGiveup(YAbstractActor* executor);//被放弃任务

    //条件判断函数(拜师,任务...)
    virtual int conditionEstimation(YAbstractActor* executor,YString conditionName);

    virtual int fnUniteKill(YAbstractActor* executor,YString command);//联合协防

    virtual int NPCKill(YString name); //NPC主动杀人
};

#endif //__YNPC_H__
