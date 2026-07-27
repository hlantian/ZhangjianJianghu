//---------------------------------------------------------------------------
//
// yplayer.h    2000年6月12日
//
// 类YPlayer：玩家
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YPLAYER_H__
#define __YPLAYER_H__

#include "yactor.h"
#include "yuser.h"
#include "ysession.h"

class YRoom;

class YPlayer : public YActor, public YUser{
  	//属性：Beg(叫化绝活)
	private:
		long m_Beg; //属性Beg(叫化绝活)的成员变量
	public:
		long getBeg(void) {return m_Beg;} //读属性Beg(叫化绝活)
		void setBeg(long newBeg) {m_Beg=newBeg;} //设置Beg(叫化绝活)
        //属性：m_playerip(ip地址)
	private:
		YString m_playerip; //属性ip的成员变量
	public:
		YString getplayerip(void) {return m_playerip;} //读属性属性ip的成员变量
		void setplayerip(YString newplayerip) {m_playerip=newplayerip;} //设置属性ip的成员变量
        //属性：FightMiaoshu(较量描述)
	private:
		long m_FightMiaoshu; //属性FightMiaoshu(较量描述)的成员变量
	public:
		long getFightMiaoshu(void) {return m_FightMiaoshu;} //读属性FightMiaoshu(较量描述)
		void setFightMiaoshu(long newFightMiaoshu) {m_FightMiaoshu=newFightMiaoshu;} //设置FightMiaoshu(较量描述)
        //属性：BingArm(先天臂力)
	private:
		long m_BeginArm; //属性BingArm(先天臂力)的成员变量
	public:
		long getBeginArm(void) {return m_BeginArm;} //读属性BingArm(先天臂力)
		void setBeginArm(long newBingArm) {m_BeginArm=newBingArm;} //设置BingArm(先天臂力)
	//属性：BeginLearn(先天悟性)
	private:
		long m_BeginLearn; //属性BeginLearn(先天悟性)的成员变量
	public:
		long getBeginLearn(void) {return m_BeginLearn;} //读属性BeginLearn(先天悟性)
		void setBeginLearn(long newBeginLearn) {m_BeginLearn=newBeginLearn;} //设置BeginLearn(先天悟性)
        //属性：beginDodge(先天身法)
	private:
		long m_beginDodge; //属性beginDodge(先天身法)的成员变量
	public:
		long getbeginDodge(void) {return m_beginDodge;} //读属性beginDodge(先天身法)
		void setbeginDodge(long newbeginDodge) {m_beginDodge=newbeginDodge;} //设置beginDodge(先天身法)
	//属性：BeginForce(先天根骨)
	private:
		long m_BeginForce; //属性BeginForce(先天根骨)的成员变量

	public:
		long getBeginForce(void) {return m_BeginForce;} //读属性BeginForce(先天根骨)
		void setBeginForce(long newBeginForce) {m_BeginForce=newBeginForce;} //设置BeginForce(先天根骨)
	//属性：Weight(负重)
	private:
		long m_Weight; //属性Weight(负重)的成员变量

	public:
		long getWeight(void) {return m_Weight;} //读属性Weight(负重)
		void setWeight(long newWeight) {m_Weight=newWeight;} //设置Weight(负重)
	//属性：MaxWeight(最大负重)
	private:
		long m_MaxWeight; //属性MaxWeight(最大负重)的成员变量

	public:
		long getMaxWeight(void) {return m_MaxWeight;} //读属性MaxWeight(最大负重)
		void setMaxWeight(long newMaxWeight) {m_MaxWeight=newMaxWeight;} //设置MaxWeight(最大负重)
	//属性：Food(食物)
	private:
		long m_Food; //属性Food(食物)的成员变量

	public:
		long getFood(void) {return m_Food;} //读属性Food(食物)
		void setFood(long newFood) {m_Food=newFood;refreshHP();} //设置Food(食物)
	//属性：Drink(饮水)
	private:
		long m_Drink; //属性Drink(饮水)的成员变量

	public:
		long getDrink(void) {return m_Drink;} //读属性Drink(饮水)
		void setDrink(long newDrink) {m_Drink=newDrink;refreshHP();} //设置Drink(饮水)
	//属性：MaxFood(最大食物)
	private:
		long m_MaxFood; //属性MaxFood(最大食物)的成员变量

	public:
		long getMaxFood(void) {return m_MaxFood;} //读属性MaxFood(最大食物)
		void setMaxFood(long newMaxFood) {m_MaxFood=newMaxFood;} //设置MaxFood(最大食物)
	//属性：MaxDrink(最大饮水)
	private:
		long m_MaxDrink; //属性MaxDrink(最大饮水)的成员变量

	public:
		long getMaxDrink(void) {return m_MaxDrink;} //读属性MaxDrink(最大饮水)
		void setMaxDrink(long newMaxDrink) {m_MaxDrink=newMaxDrink;} //设置MaxDrink(最大饮水)
	//属性：TunaTime(吐纳时间)
	private:
		long m_TunaTime; //属性TunaTime(吐纳时间)的成员变量

	public:
		long getTunaTime(void) {return m_TunaTime;} //读属性TunaTime(吐纳时间)
		void setTunaTime(long newTunaTime) {m_TunaTime=newTunaTime;} //设置TunaTime(吐纳时间)
	//属性：DazuoTime(打坐时间)
	private:
		long m_DazuoTime; //属性DazuoTime(打坐时间)的成员变量

	public:
		long getDazuoTime(void) {return m_DazuoTime;} //读属性DazuoTime(打坐时间)
		void setDazuoTime(long newDazuoTime) {m_DazuoTime=newDazuoTime;} //设置DazuoTime(打坐时间)
	//属性：Steal(妙手空空)
	private:
		long m_Steal; //属性Steal(妙手空空)的成员变量

	public:
		long getSteal(void) {return m_Steal;} //读属性Steal(妙手空空)
		void setSteal(long newSteal) {m_Steal=newSteal;} //设置Steal(妙手空空)
	//属性：BaseHand(基本拳法)
	private:
		long m_BaseHand; //属性BaseHand(基本拳法)的成员变量

	public:
		long getBaseHand(void) {return m_BaseHand;} //读属性BaseHand(基本拳法)
		void setBaseHand(long newBaseHand) {m_BaseHand=newBaseHand;} //设置BaseHand(基本拳法)
	//属性：BaseFinger(基本指法)
	private:
		long m_BaseFinger; //属性BaseFinger(基本指法)的成员变量

	public:
		long getBaseFinger(void) {return m_BaseFinger;} //读属性BaseFinger(基本指法)
		void setBaseFinger(long newBaseFinger) {m_BaseFinger=newBaseFinger;} //设置BaseFinger(基本指法)
	//属性：baseSole(基本掌法)
	private:
		long m_baseSole; //属性baseSole(基本掌法)的成员变量

	public:
		long getbaseSole(void) {return m_baseSole;} //读属性baseSole(基本掌法)
		void setbaseSole(long newbaseSole) {m_baseSole=newbaseSole;} //设置baseSole(基本掌法)
	//属性：BaseLeg(基本腿法)
	private:
		long m_BaseLeg; //属性BaseLeg(基本腿法)的成员变量

	public:
		long getBaseLeg(void) {return m_BaseLeg;} //读属性BaseLeg(基本腿法)
		void setBaseLeg(long newBaseLeg) {m_BaseLeg=newBaseLeg;} //设置BaseLeg(基本腿法)
	//属性：BasePub(基本手法)
	private:
		long m_BasePub; //属性BasePub(基本手法)的成员变量

	public:
		long getBasePub(void) {return m_BasePub;} //读属性BasePub(基本手法)
		void setBasePub(long newBasePub) {m_BasePub=newBasePub;} //设置BasePub(基本手法)
	//属性：BaseClow(基本爪法)
	private:
		long m_BaseClow; //属性BaseClow(基本爪法)的成员变量

	public:
		long getBaseClow(void) {return m_BaseClow;} //读属性BaseClow(基本爪法)
		void setBaseClow(long newBaseClow) {m_BaseClow=newBaseClow;} //设置BaseClow(基本爪法)
	//属性：BaseDodge(基本轻功)
	private:
		long m_BaseDodge; //属性BaseDodge(基本轻功)的成员变量

	public:
		long getBaseDodge(void) {return m_BaseDodge;} //读属性BaseDodge(基本轻功)
		void setBaseDodge(long newBaseDodge) {m_BaseDodge=newBaseDodge;} //设置BaseDodge(基本轻功)
	//属性：BaseForce(基本内功)
	private:
		long m_BaseForce; //属性BaseForce(基本内功)的成员变量

	public:
		long getBaseForce(void) {return m_BaseForce;} //读属性BaseForce(基本内功)
		void setBaseForce(long newBaseForce) {m_BaseForce=newBaseForce;} //设置BaseForce(基本内功)
	//属性：Learn(读书写字)
	private:
		long m_Learn; //属性Learn(读书写字)的成员变量

	public:
		long getLearn(void) {return m_Learn;} //读属性Learn(读书写字)
		void setLearn(long newLearn) {m_Learn=newLearn;} //设置Learn(读书写字)
	//属性：BaseParry(基本招架)
	private:
		long m_BaseParry; //属性BaseParry(基本招架)的成员变量

	public:
		long getBaseParry(void) {return m_BaseParry;} //读属性BaseParry(基本招架)
		void setBaseParry(long newBaseParry) {m_BaseParry=newBaseParry;} //设置BaseParry(基本招架)
	//属性：FreeTime(空闲时间)
	private:
		long m_FreeTime; //属性FreeTime(空闲时间)的成员变量

	public:
		long getFreeTime(void) {return m_FreeTime;} //读属性FreeTime(空闲时间)
		void setFreeTime(long newFreeTime) {m_FreeTime=newFreeTime;} //设置FreeTime(空闲时间)
	//属性：PowUPHit(powerup攻击力)
	private:
		long m_PowUPHit; //属性PowUPHit(powerup攻击力)的成员变量

	public:
		long getPowUPHit(void) {return m_PowUPHit;} //读属性PowUPHit(powerup攻击力)
		void setPowUPHit(long newPowUPHit) {m_PowUPHit=newPowUPHit;} //设置PowUPHit(powerup攻击力)
	//属性：PowUPDeff(powerup防御力)
	private:
		long m_PowUPDeff; //属性PowUPDeff(powerup防御力)的成员变量

	public:
		long getPowUPDeff(void) {return m_PowUPDeff;} //读属性PowUPDeff(powerup防御力)
		void setPowUPDeff(long newPowUPDeff) {m_PowUPDeff=newPowUPDeff;} //设置PowUPDeff(powerup防御力)
	//属性：BeKill(被杀次数)
        //和Actor冲突去掉
        /*
	private:
		long m_BeKill; //属性BeKill(被杀次数)的成员变量
	public:
		long getBeKill(void) {return m_BeKill;} //读属性BeKill(被杀次数)
		void setBeKill(long newBeKill) {m_BeKill=newBeKill;} //设置BeKill(被杀次数)
	//属性：KillOther(杀人次数)
	private:
		long m_KillOther; //属性Killother(杀人次数)的成员变量

	public:
		long getKillOther(void) {return m_KillOther;} //读属性Killother(杀人次数)
		void setKillOther(long newKillother) {m_KillOther=newKillother;} //设置Killother(杀人次数)
        */
	//属性：PKHow(pk数)
	/*private:
		long m_PKHow; //属性PKHow(pk数)的成员变量

	public:
		long getPKHow(void) {return m_PKHow;} //读属性PKHow(pk数)
		void setPKHow(long newPKHow) {m_PKHow=newPKHow;} //设置PKHow(pk数)
	//属性：BePKHow(被pk数)
	private:
		long m_BePKHow; //属性BePKHow(被pk数)的成员变量

	public:
		long getBePKHow(void) {return m_BePKHow;} //读属性BePKHow(被pk数)
		void setBePKHow(long newBePKHow) {m_BePKHow=newBePKHow;} //设置BePKHow(被pk数)
        */
	//属性：GiveThing(送东西数)
	private:
		long m_GiveThing; //属性GiveThing(送东西数)的成员变量

	public:
		long getGiveThing(void) {return m_GiveThing;} //读属性GiveThing(送东西数)
		void setGiveThing(long newGiveThing) {m_GiveThing=newGiveThing;} //设置GiveThing(送东西数)
	//属性：CityKill(屠城数)
	private:
		long m_CityKill; //属性CityKill(屠城数)的成员变量

	public:
		long getCityKill(void) {return m_CityKill;} //读属性CityKill(屠城数)
		void setCityKill(long newCityKill) {m_CityKill=newCityKill;} //设置CityKill(屠城数)
	//属性：SleepTime(睡眠)
	private:
		long m_SleepTime; //属性SleepTime(睡眠)的成员变量

	public:
		long getSleepTime(void) {return m_SleepTime;} //读属性SleepTime(睡眠)
		void setSleepTime(long newSleepTime) {m_SleepTime=newSleepTime;} //设置SleepTime(睡眠)
	//属性：Deposit(存款)
	private:
		long m_Deposit; //属性Deposit(存款)的成员变量

	public:
		long getDeposit(void) {return m_Deposit;} //读属性Deposit(存款)
		void setDeposit(long newDeposit) {m_Deposit=newDeposit;} //设置Deposit(存款)
	//属性：CloseChat(关闭共用频道)
	private:
		long m_CloseChat; //属性CloseChat(关闭共用频道)的成员变量

	public:
		long getCloseChat(void) {return m_CloseChat;} //读属性CloseChat(关闭共用频道)
		void setCloseChat(long newCloseChat) {m_CloseChat=newCloseChat;} //设置CloseChat(关闭共用频道)
	//属性：CloseRum(关闭谣言频道)
	private:
		long m_CloseRum; //属性CloseRum(关闭谣言频道)的成员变量

	public:
		long getCloseRum(void) {return m_CloseRum;} //读属性CloseRum(关闭谣言频道)
		void setCloseRum(long newCloseRum) {m_CloseRum=newCloseRum;} //设置CloseRum(关闭谣言频道)
	//属性：CloseNewbie(关闭新手频道)
	private:
		long m_CloseNewbie; //属性CloseNewbie(关闭新手频道)的成员变量

	public:
		long getCloseNewbie(void) {return m_CloseNewbie;} //读属性CloseNewbie(关闭新手频道)
		void setCloseNewbie(long newCloseNewbie) {m_CloseNewbie=newCloseNewbie;} //设置CloseNewbie(关闭新手频道)
	//属性：CloseParty(关闭门派频道)
	private:
		long m_CloseParty; //属性CloseParty(关闭新手频道)的成员变量

	public:
		long getCloseParty(void) {return m_CloseParty;} //读属性CloseParty(关闭门派频道)
		void setCloseParty(long newCloseParty) {m_CloseParty=newCloseParty;} //设置CloseParty(关闭门派频道)
	//属性：ComeIn(新人登录步骤)
	private:
		long m_ComeIn; //属性ComeIn(新人登录步骤)的成员变量

	public:
		long getComeIn(void) {return m_ComeIn;} //读属性ComeIn(新人登录步骤)
		void setComeIn(long newComeIn) {m_ComeIn=newComeIn;} //设置ComeIn(新人登录步骤)
	//属性：PlayerLevel
	private:
		long m_PlayerLevel; //属性PlayerLevel(玩家级别)的成员变量

	public:
		long getPlayerLevel(void) {return m_PlayerLevel;} //读属性PlayerLevel(玩家级别)
		void setPlayerLevel(long newPlayerLevel) {m_PlayerLevel=newPlayerLevel;} //设置PlayerLevel(玩家级别)

         //属性：WizCloseChat(巫师关闭频道)
	private:
        	long m_WizCloseChat; //属性WizCloseChat(巫师关闭频道)的成员变量
	public:
		long getWizCloseChat(void) {return m_WizCloseChat;} //读属性WizCloseChat(巫师关闭频道)
		void setWizCloseChat(long newWizCloseChat) {m_WizCloseChat=newWizCloseChat;} //设置WizCloseChat(巫师关闭频道)
	//属性：PlayCloseChat(玩家关闭频道)
	private:
		long m_PlayCloseChat; //属性PlayCloseChat(玩家关闭频道)的成员变量
	public:
		long getPlayCloseChat(void) {return m_PlayCloseChat;} //读属性PlayCloseChat(玩家关闭频道)
		void setPlayCloseChat(long newPlayCloseChat) {m_PlayCloseChat=newPlayCloseChat;} //设置PlayCloseChat(玩家关闭频道)
	//属性：playSaySpeed(玩家说话频率)
	private:
		long m_playSaySpeed; //属性playSaySpeed(玩家说话频率)的成员变量
	public:
		long getplaySaySpeed(void) {return m_playSaySpeed;} //读属性playSaySpeed(玩家说话频率)
		void setplaySaySpeed(long newplaySaySpeed) {m_playSaySpeed=newplaySaySpeed;} //设置playSaySpeed(玩家说话频率)
	//属性：PartyValue(门派评价)
	private:
		long m_PartyValue; //属性PartyValue(门派评价)的成员变量
	public:
		long getPartyValue(void) {return m_PartyValue;} //读属性PartyValue(门派评价)
		void setPartyValue(long newPartyValue) {m_PartyValue=newPartyValue;} //设置PartyValue(门派评价)
	//属性：CourtValue(朝廷声望)
	private:
		long m_CourtValue; //属性CourtValue(朝廷声望)的成员变量
	public:
		long getCourtValue(void) {return m_CourtValue;} //读属性CourtValue(朝廷声望)
		void setCourtValue(long newCourtValue) {m_CourtValue=newCourtValue;} //设置CourtValue(朝廷声望)
	//属性：SocietyValue(江湖声望)
	private:
		long m_SocietyValue; //属性SocietyValue(江湖声望)的成员变量
	public:
		long getSocietyValue(void) {return m_SocietyValue;} //读属性SocietyValue(江湖声望)
		void setSocietyValue(long newSocietyValue) {m_SocietyValue=newSocietyValue;} //设置SocietyValue(江湖声望)
	//属性：OnlineTime(在线时间)
	private:
		long m_OnlineTime; //属性：OnlineTime(在线时间)的成员变量
	public:
		long getOnlineTime(void) {return m_OnlineTime;} //读属性：OnlineTime(在线时间)
		void setOnlineTime(long newOnlineTime) {m_OnlineTime=newOnlineTime;} //设置属性：OnlineTime(在线时间)
	//属性：LaseOnlineTime(上次在线时间)
	private:
		long m_LaseOnlineTime; //属性LaseOnlineTime(上次在线时间)的成员变量
	public:
		long getLaseOnlineTime(void) {return m_LaseOnlineTime;} //读属性：LaseOnlineTime(上次在线时间)
		void setLaseOnlineTime(long newLaseOnlineTime) {m_LaseOnlineTime=newLaseOnlineTime;} //设置属性：LaseOnlineTime(上次在线时间)
	//属性：playerSleepSkip(睡眠间隔)
	private:
		long m_PlayerSleepSkip; //属性playerSleepSkip(睡眠间隔)的成员变量
	public:
		long getPlayerSleepSkip(void) {return m_PlayerSleepSkip;} //读属性：playerSleepSkip(睡眠间隔)
		void setPlayerSleepSkip(long newplayerSleepSkip) {m_PlayerSleepSkip=newplayerSleepSkip;} //设置属性playerSleepSkip(睡眠间隔)
	//属性：PlayerRenew(体力恢复)
	private:
		long m_PlayerRenew; //属性PlayerRenew(体力恢复)的成员变量
	public:
		long getPlayerRenew(void) {return m_PlayerRenew;} //读属性PlayerRenew(体力恢复)
		void setPlayerRenew(long newPlayerRenew) {m_PlayerRenew=newPlayerRenew;} //设置PlayerRenew(体力恢复)
	//属性：NowWork(正在劳动)
	private:
		long m_NowWork; //属性NowWork(正在劳动)的成员变量
	public:
		long getNowWork(void) {return m_NowWork;} //读属性NowWork(正在劳动)
		void setNowWork(long newNowWork) {m_NowWork=newNowWork;} //设置NowWork(正在劳动)
	//属性：NowWork(正在劳动)
	private:
		long m_noaccept; //属性m_noaccept(接受物品)的成员变量
	public:
		long getNoAccept(void) {return m_noaccept;} //读属性m_noaccept(接受物品)
		void setNoAccept(long newnoaccept) {m_noaccept=newnoaccept;} //设置m_noaccept(接受物品)

  //玩家帮派
  //属性：IsFactionOwner(是否帮主)
	private:
		long m_IsFactionOwner; //属性IsFactionOwner(是否帮主)的成员变量
	public:
		long getIsFactionOwner(void) {return m_IsFactionOwner;} //读属性IsFactionOwner(是否帮主)
		void setIsFactionOwner(long newIsFactionOwner) {m_IsFactionOwner=newIsFactionOwner;} //设置IsFactionOwner(是否帮主)
//属性：FactionName(加入帮派)
	private:
		YString m_FactionName; //属性FactionName(加入帮派)的成员变量
	public:
		YString getFactionName(void) {return m_FactionName;} //读属性FactionName(加入帮派)
		void setFactionName(YString newFactionName) {m_FactionName=newFactionName;} //设置FactionName(加入帮派)
//属性：FactionTitle(帮派头衔)
	private:
		YString m_FactionTitle; //属性FactionTitle(帮派头衔)的成员变量
	public:
		YString getFactionTitle(void) {return m_FactionTitle;} //读属性FactionTitle(帮派头衔)
		void setFactionTitle(YString newFactionTitle) {m_FactionTitle=newFactionTitle;} //设置FactionTitle(帮派头衔)
//属性：OldPower(上次势力)
	private:
		long m_OldPower; //属性OldPower(上次势力)的成员变量
	public:
		long getOldPower(void) {return m_OldPower;} //读属性OldPower(上次势力)
		void setOldPower(long newOldPower) {m_OldPower=newOldPower;} //设置OldPower(上次势力)
  //属性：KillFactionCount(灭门数)
	private:
		long m_KillFactionCount; //属性KillFactionCount(灭门数)的成员变量
	public:
		long getKillFactionCount(void) {return m_KillFactionCount;} //读属性KillFactionCount(灭门数)
		void setKillFactionCount(long newKillFactionCount) {m_KillFactionCount=newKillFactionCount;} //设置KillFactionCount(灭门数)
  //属性：CloseFactionParty(关闭帮派频道)
	private:
		long m_CloseFactionParty; //属性CloseFactionParty(关闭帮派频道)的成员变量
	public:
		long getCloseFactionParty(void) {return m_CloseFactionParty;} //读属性CloseFactionParty(关闭帮派频道)
		void setCloseFactionParty(long newCloseFactionParty) {m_CloseFactionParty=newCloseFactionParty;} //设置CloseFactionParty(关闭帮派频道)
  private:
    YChat* m_pFactionChat; //帮派频道指针
  public:
    virtual YChat* getFactionChat(void){return m_pFactionChat;}   //得到帮派频道的指针
    void setFactionChat(YChat* pnewFactionChat) {m_pFactionChat=pnewFactionChat;} //存帮派频道的指针
  //玩家帮派结束


  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);
    virtual YString getNickName(void);

	//属性：Session
	private:
		YSession* m_Session; //属性Session的成员变量
                YChat* m_menpaichat; //门派频道
	public:
		YSession* getSession(void) {return m_Session;} //读属性Session
		void setSession(YSession* newSession) {m_Session=newSession;} //设置Session
	public:
		virtual int getLevel(void) {return getAsLong("玩家级别");} //读属性Level
		virtual void setLevel(int newLevel) {set("玩家级别",newLevel);} //设置Level

	public:
                virtual YChat* getMeipaichat(void){ return m_menpaichat;}
                virtual int  setMeipaichat(void);


  public:
    YRoom* getRoom(void) {return (YRoom*)YAbstractActor::getRoom();};
  public:
		YPlayer(YUser* user, YString initFileName="");  //构造函数
		virtual ~YPlayer(){}; //析构函数

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YPlayer");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

	//属性：Sex
	public:
		sex_type getSex(void) {return YXiluUser::getSex();} //读属性Sex
		void setSex(YString sex); //设置Sex

	public:
		//事件Init的默认处理函数
		virtual int onInit(void);
  	//事件Message的默认处理函数
		virtual int onMessage(YAbstractActor* speaker, YString message);
    //接收一条消息
    virtual void message(YAbstractActor* speaker, YString msg, bool newline=true,
                    msg_type messagetype=ORIGINAL_MSG, const YString& name="");

		//事件Timer的默认处理函数
		virtual int onTimer(void);

		//事件AfterPropertyChange的默认处理函数
		virtual int onAfterPropertyChange(YMUDObject* sender, YString PropertyName,
                                        long oldValue, long newValue);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YString command);
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);


    //事件AfterLoad的默认处理函数
    virtual int onAfterLoad(void);
    //事件BeforeSave的默认处理函数
    virtual int onBeforeSave(void);



  //各种命令处理
  public:
    //lp
    virtual YString changeword(YString word);  //屏蔽javescorp
    virtual int look(YString sentence="");     //看
    virtual int give(YString sentence);        //给东西
    virtual int exchange(YString sentence);        //交换物品
    virtual int acceptchange(YString sentence);        //交换物品
    virtual int say(YString sentence);         //说话（房间内）
    virtual int sayphiz(YString sentence);     //房间内作表情
    virtual int get(YString sentence);         //取得
    virtual int goSleep(void);                 //睡觉
    virtual int i(void); //列出自己身上物品
    virtual int drop(YString sentence);     //丢掉自己的物品
    virtual int wield(YString sentence);    //装备
    virtual int unwield(YString sentence);  //卸下
    virtual int wear(YString sentence);     //穿上
    virtual int unwear(YString sentence);   //脱下
    virtual int ask(YString sentence);      //问
    virtual int xuanshang(YString sentence);      //悬赏
    virtual int list(YString sentence);      //悬赏
    virtual int answer(YString sentence);      //问
    virtual int buy(YString sentence);      //买东西
    virtual int eat(YString sentence);      //吃东西
    virtual int drink(YString sentence);    //喝东西
    virtual int check(YString sentence);    //查帐
    virtual int enforce(YString sentence);  //加力攻击
    virtual int exert(YString sentence);    //运内力取做什么
    virtual int fill(YString sentence);     //装水
    virtual int follow(YString sentence);   //跟随
    virtual int knock(YString sentence);    //敲打
    virtual int open(YString sentence);     //打开
    virtual int sit(YString sentence);      //坐下
    virtual int withdraw(YString sentence); //取钱
    virtual int deposite(YString sentence); //存钱
    virtual int tell(YString sentence);     //和某人密谈
    virtual int wizchat(YString sentence);       //聊天频道
    virtual int wizset(YString sentence);   //巫师设置数字
    virtual int wizsets(YString sentence);  //巫师设置文字
    virtual int wizkickout(YString sentence);  //巫师踢人
    virtual int wizsetadd(YString sentence); //巫师设置文字添加
    virtual int wizsetsb(YString sentence);  //巫师设置数字 （他人）
    virtual int wizsetssb(YString sentence);  //巫师设置文字  （他人）
    virtual int wizsetaddsb(YString sentence); //巫师设置文字添加  （他人）
    virtual int wizget(YString sentence);    //把人物抓到自己这里
    virtual int wizgoto(YString sentence);   //巫师去player的房间
    virtual int shutdown(YString sentence);   //让所有玩家退出
//    virtual int wizgoto(YString sentence);   //巫师去player的房间
    virtual int wizkick(YString sentence);    //把人物击倒
    virtual int wizclose(YString sentence); //关闭频道
    virtual int wizopen(YString sentence);  //开启频道
    virtual int wizlook(YString sentence);  //巫师查看他人得属性
    virtual int bai(YString sentence="");   //拜师
    virtual int hp(void);                   //气血等状态
    virtual int skills(YString sentence);   //查看武功
    virtual int bskills(YString sentence);   //查看劳动技能
    virtual int score(void);                //人物的状态
    virtual int dorenew(void);              //人物的气血的时间回复
    virtual int enable(YString sentence);   //使用武功
    virtual int worklevelup(YString type,long level); //劳动技能的升级
    virtual int quit(void);                 //退出
    virtual int cquit(YString sentence);    //退出
    virtual int wimpy(YString sentence);  //设逃跑系数
    virtual int lian(YString sentence);  //练习基本的武功
    virtual int chat(YString sentence);       //聊天频道
    virtual int rumor(YString sentence);      //谣言频道
    virtual int newbie(YString sentence);     //新手频道
    virtual int party(YString sentence);     //门派频道
    virtual int chatphiz(YString sentence);       //聊天频道
    virtual int rumorphiz(YString sentence);      //谣言频道
    virtual int newbiephiz(YString sentence);     //新手频道
    virtual int turnoff(YString sentence);     //关闭频道
    virtual int turninfo(YString sentence);     //关闭开启信息频道
    virtual int xue(YString sentence); //学武功
    virtual int cunquit(YString sentence); //存任务退出
    virtual int ageup(void); //年龄的增长
    virtual int nick(YString sentence); //起绰号
    virtual int describe(YString sentence); //自己写描述
    virtual int uselevel(YString sentence); //设置级别
    virtual int tuna(YString sentence); //吐纳
    virtual int dazuo(YString sentence); //打坐
    virtual int fangqi(YString sentence); //放弃武功
    virtual int black(YString sentence); //关闭tell人物
    virtual int unblack(YString sentence); //开启tell人物
    virtual int repeat(YString type,YString word); //比较type里边的参数和word是否相同
    virtual int wizcompare(YActor* other);//判断两个巫师的级别
    virtual YString jiebiemiaoshu(int level);  //武功级别描述
    virtual int playerhelproom(YString sentence); //跑到帮助的房间
    virtual int playertaxi(YString sentence); //跑到帮助的房间
    virtual int delQuest(void); //退出清除任务
    virtual int cdelQuest(YString sentence); //退出清除任务
    virtual int vote(YString sentence); //关闭开启频道
    virtual int checkclose(void); //查看频道是否被关闭
    virtual int playerarmchange(void);     //玩家攻击力变化
    virtual int playerlevelup(YString sentence);  //玩家升级
    virtual int playerworkup(YString sentence);  //劳动升级
    virtual int playerhpchange(void);           //气血变化
    virtual int nogive(YString sentence);           //不接受物品
    //zhy
    virtual int quest(void); //申请任务
    virtual int giveup(void); //放弃任务
    virtual int getReward(YString bossName); //得到奖励
    virtual int ge(YString command); //割首级
    virtual int readBook(YString command); //读书
    virtual int letsWork(void); //劳动(钓鱼,酿蜜...)
    virtual int letsCaikuang(void); //采矿
    virtual int letsDazao(void); //打铁
    virtual int letsSendThing(void); //送东西(任务之一)
    virtual int letsKillAll(void); //屠城(任务之一)
    virtual long getSkillLevel(YString skill);//人物的基本武功取得
    virtual int setSkillLevel(YString skill,long level);//人物的基本武功设置
    //另外,我还修改了give和onTimer的一部分

    //yl
    virtual int errorChat(YString sentence=""); //开关错误频道
    //刷新hp的动态显示
    virtual void refreshHP(void);
    virtual int cmd_save(void);              //存储
    virtual int who(YString sentence="");  //在线名单
    //显示房间标题和描述(Javascript)
    virtual int look_b(YString sentence="");   //屏幕上的看
    virtual int hp_b(void);                    //屏幕上的气血
    virtual int skills_b(void);               //屏幕上的武功
    virtual int score_b(void);                //屏幕上的状态
    virtual int i_b(void);                    //屏幕上的物品
    virtual int timeuse(void);                //察看耗时情况
    //重新装载object的属性
    virtual int cmd_reload(YString command);
    //制造物品
    virtual int wizcreate(YString command);

    //-----------------------------------------------
    //--------       玩家帮派             -----------
    //-----------------------------------------------
    virtual int fnCreateFaction(YString command); //创建帮派
    long fnReSumPower();  //重算玩家的势力值
    virtual int fnCmdFaction(YString command);    //查询帮派
    virtual int fnDisband(YString command);       //解散帮派
    virtual int fnJoinFaction(YString command);   //申请加入帮派
    virtual int fnAgreeJoin(YString command);     //同意申请
    YString getFactionMsgColor();                 //得到帮派信息颜色
    virtual int fnFireOut(YString command);       //开除一个玩家
    virtual int fnUnJoin(YString command);        //退出一个帮派
    virtual int fnExalt(YString command);         //设定某人的头衔
    virtual int fnMyFaction(YString command);     //察看本帮信息
    virtual int fnDemise(YString command);        //任命别人接替帮主
    virtual int fnSetFactionColor(YString command);        //设置帮派颜色
    virtual int fnSetFactionBanner(YString command);       //设置帮派口号
    virtual int fnSalute(YString command);        //向帮主致敬
    void fnProcessFaction();                      //登陆时处理玩家帮派问题
    void fnShowWizCloseMsg();                     //显示巫师关闭帮会的信息
    virtual int fnInvite(YString command);        //邀请某人来帮会总舵
    virtual int fnFactionParty(YString word);     //用帮派频道发言

};

#endif //__YPLAYER_H__
