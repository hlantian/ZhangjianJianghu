//---------------------------------------------------------------------------
//
// yactor.h    2000年6月12日
//
// 类YActor：人物
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YACTOR_H__
#define __YACTOR_H__
#include "yabstractactor.h"
#include "yxiluuser.h"

class YActor : public YAbstractActor{
  //属性：DestroyList(销毁列表)
	private:
		YString m_DestroyList; //属性DestroyList(销毁列表)的成员变量
	public:
		YString getDestroyList(void) {return m_DestroyList;} //读属性DestroyList(销毁列表)
		void setDestroyList(YString newDestroyList) {m_DestroyList=newDestroyList;} //设置DestroyList(销毁列表)
  //属性：Status(状态)
	private:
		YString m_Status; //属性Status(状态)的成员变量
	public:
		YString getStatus(void) {return m_Status;} //读属性Status(状态)
		void setStatus(YString newStatus) {m_Status=newStatus;} //设置Status(状态)
  //属性：FightInterval(战斗间隔)
	private:
		long m_FightInterval; //属性FightInterval(战斗间隔)的成员变量
	public:
		long getFightInterval(void) {return m_FightInterval;} //读属性FightInterval(战斗间隔)
		void setFightInterval(long newFightInterval) {m_FightInterval=newFightInterval;} //设置FightInterval(战斗间隔)
  //属性：FaintTime(晕倒时间)
	private:
		long m_FaintTime; //属性FaintTime(晕倒时间)的成员变量
	public:
		long getFaintTime(void) {return m_FaintTime;} //读属性FaintTime(晕倒时间)
		void setFaintTime(long newFaintTime) {m_FaintTime=newFaintTime;} //设置FaintTime(晕倒时间)
  //属性：Adversary(对手)
	private:
		YString m_Adversary; //属性Adversary(对手)的成员变量
	public:
		YString getAdversary(void) {return m_Adversary;} //读属性Adversary(对手)
		void setAdversary(YString newAdversary) {m_Adversary=newAdversary;} //设置Adversary(对手)
  //属性：ActorName(名字)
	private:
		//YString m_ActorName; //属性ActorName(名字)的成员变量
	public:
		YString getActorName(void) {return getObjectName();} //读属性ActorName(名字)
		void setActorName(YString newActorName) {setObjectName(newActorName);} //设置ActorName(名字)
  //属性：ActorShow(描述)
	private:
		YString m_ActorShow; //属性ActorName(名字)的成员变量
	public:
		YString getActorShow(void) {return m_ActorShow;} //读属性ActorShow(描述)
		void setActorShow(YString newActorName) {m_ActorShow=newActorName;} //设置ActorShow(描述)
  //属性：Body(气血)
	private:
		long m_Body; //属性Body(气血)的成员变量
	public:
		long getBody(void) {return m_Body;} //读属性Body(气血)
		void setBody(long newBody) {m_Body=newBody;refreshHP();} //设置Body(气血)
  //属性：MaxBody(最大气血)
	private:
		long m_MaxBody; //属性MaxBody(最大气血)的成员变量
	public:
		long getMaxBody(void) {return m_MaxBody;} //读属性MaxBody(最大气血)
		void setMaxBody(long newMaxBody) {m_MaxBody=newMaxBody;refreshHP();} //设置MaxBody(最大气血)
  //属性：Energy(精力)
	private:
		long m_Energy; //属性Energy(精力)的成员变量
	public:
		long getEnergy(void) {return m_Energy;} //读属性Energy(精力)
		void setEnergy(long newEnergy) {m_Energy=newEnergy;refreshHP();} //设置Energy(精力)
  //属性：MaxEnergy(最大精力)
	private:
		long m_MaxEnergy; //属性MaxEnergy(最大精力)的成员变量
	public:
		long getMaxEnergy(void) {return m_MaxEnergy;} //读属性MaxEnergy(最大精力)
		void setMaxEnergy(long newMaxEnergy) {m_MaxEnergy=newMaxEnergy;refreshHP();} //设置MaxEnergy(最大精力)
  //属性：AddMaxEnergy(附加最大精力)
	private:
		long m_AddMaxEnergy; //属性AddMaxEnergy(附加最大精力)的成员变量
	public:
		long getAddMaxEnergy(void) {return m_AddMaxEnergy;} //读属性AddMaxEnergy(附加最大精力)
		void setAddMaxEnergy(long newAddMaxEnergy) {m_AddMaxEnergy=newAddMaxEnergy;refreshHP();} //设置AddMaxEnergy(附加最大精力)

  //属性：Wimpy(逃跑系数)
	private:
		long m_Wimpy; //属性Wimpy(逃跑系数)的成员变量
	public:
		long getWimpy(void) {return m_Wimpy;} //读属性Wimpy(逃跑系数)
		void setWimpy(long newWimpy) {m_Wimpy=newWimpy;} //设置Wimpy(逃跑系数)
  //属性：FreeTime(空闲时间)
	private:
		long m_FreeTime; //属性FreeTime(空闲时间)的成员变量
	public:
		long getFreeTime(void) {return m_FreeTime;} //读属性FreeTime(空闲时间)
		void setFreeTime(long newFreeTime) {m_FreeTime=newFreeTime;} //设置FreeTime(空闲时间)
  //属性：Busy(繁忙)
	private:
		long m_Busy; //属性Busy(繁忙)的成员变量
	public:
		long getBusy(void) {return m_Busy;} //读属性Busy(繁忙)
		void setBusy(long newBusy) {m_Busy=newBusy;} //设置Busy(繁忙)
  //属性：WeaponType(武器类型)
	private:
		YString m_WeaponType; //属性WeaponType(武器类型)的成员变量
	public:
		YString getWeaponType(void) {return m_WeaponType;} //读属性WeaponType(武器类型)
		void setWeaponType(YString newWeaponType) {m_WeaponType=newWeaponType;playerarmchange();} //设置WeaponType(武器类型)
  //属性：SexString(性别)
	private:
		YString m_SexString; //属性SexString(性别)的成员变量
	public:
		YString getSexString(void) {return m_SexString;} //读属性SexString(性别)
		void setSexString(YString newSexString) {m_SexString=newSexString;} //设置SexString(性别)
  //属性：InhereAttack(固定攻击力)
	private:
		long m_InhereAttack; //属性InhereAttack(固定攻击力)的成员变量
	public:
		long getInhereAttack(void) {return m_InhereAttack;} //读属性InhereAttack(固定攻击力)
		void setInhereAttack(long newInhereAttack) {m_InhereAttack=newInhereAttack;} //设置InhereAttack(固定攻击力)
  //属性：PowerUpAttack(powerup攻击力)
	private:
		long m_PowerUpAttack; //属性PowerUpAttack(powerup攻击力)的成员变量
	public:
		long getPowerUpAttack(void) {return m_PowerUpAttack;} //读属性PowerUpAttack(powerup攻击力)
		void setPowerUpAttack(long newPowerUpAttack) {m_PowerUpAttack=newPowerUpAttack;} //设置PowerUpAttack(powerup攻击力)
  //属性：InternalForce(内力)
	private:
		long m_InternalForce; //属性InternalForce(内力)的成员变量
	public:
		long getInternalForce(void) {return m_InternalForce;} //读属性InternalForce(内力)
		void setInternalForce(long newInternalForce) {m_InternalForce=newInternalForce;refreshHP();} //设置InternalForce(内力)
  //属性：MaxInternalForce(最大内力)
	private:
		long m_MaxInternalForce; //属性MaxInternalForce(最大内力)的成员变量
	public:
		long getMaxInternalForce(void) {return m_MaxInternalForce;} //读属性MaxInternalForce(最大内力)
		void setMaxInternalForce(long newMaxInternalForce) {m_MaxInternalForce=newMaxInternalForce;refreshHP();} //设置MaxInternalForce(最大内力)
  //属性：AddMaxInternalForce(附加最大内力)
	private:
		long m_AddMaxInternalForce; //属性AddMaxInternalForce(附加最大内力)的成员变量
	public:
		long getAddMaxInternalForce(void) {return m_AddMaxInternalForce;} //读属性AddMaxInternalForce(附加最大内力)
		void setAddMaxInternalForce(long newAddMaxInternalForce) {m_AddMaxInternalForce=newAddMaxInternalForce;refreshHP();} //设置AddMaxInternalForce(附加最大内力)
  //属性：ForceAttack(加力)
	private:
		long m_ForceAttack; //属性ForceAttack(加力)的成员变量
	public:
		long getForceAttack(void) {return m_ForceAttack;} //读属性ForceAttack(加力)
		void setForceAttack(long newForceAttack) {m_ForceAttack=newForceAttack;} //设置ForceAttack(加力)
  //属性：WeaponAttack(武器攻击力)
	private:
		long m_WeaponAttack; //属性WeaponAttack(武器攻击力)的成员变量
	public:
		long getWeaponAttack(void) {return m_WeaponAttack;} //读属性WeaponAttack(武器攻击力)
		void setWeaponAttack(long newWeaponAttack) {m_WeaponAttack=newWeaponAttack;} //设置WeaponAttack(武器攻击力)
  //属性：InhereDefense(固定防御力)
	private:
		long m_InhereDefense; //属性InhereDefense(固定防御力)的成员变量
	public:
		long getInhereDefense(void) {return m_InhereDefense;} //读属性InhereDefense(固定防御力)
		void setInhereDefense(long newInhereDefense) {m_InhereDefense=newInhereDefense;} //设置InhereDefense(固定防御力)
  //属性：AppendAttack(附加攻击力)
	private:
		long m_AppendAttack; //属性AppendAttack(附加攻击力)的成员变量
	public:
		long getAppendAttack(void) {return m_AppendAttack;} //读属性AppendAttack(附加攻击力)
		void setAppendAttack(long newAppendAttack) {m_AppendAttack=newAppendAttack;} //设置AppendAttack(附加攻击力)
  //属性：AppendDefense(附加防御力)
	private:
		long m_AppendDefense; //属性AppendDefense(附加防御力)的成员变量
	public:
		long getAppendDefense(void) {return m_AppendDefense;} //读属性AppendDefense(附加防御力)
		void setAppendDefense(long newAppendDefense) {m_AppendDefense=newAppendDefense;} //设置AppendDefense(附加防御力)
  //属性：PowerUpDefense(powerup防御力)
	private:
		long m_PowerUpDefense; //属性PowerUpDefense(powerup防御力)的成员变量
	public:
		long getPowerUpDefense(void) {return m_PowerUpDefense;} //读属性PowerUpDefense(powerup防御力)
		void setPowerUpDefense(long newPowerUpDefense) {m_PowerUpDefense=newPowerUpDefense;} //设置PowerUpDefense(powerup防御力)
  //属性：DodgeUsing(轻功使用)
	private:
		YString m_DodgeUsing; //属性DodgeUsing(轻功使用)的成员变量
	public:
		YString getDodgeUsing(void) {return m_DodgeUsing;} //读属性DodgeUsing(轻功使用)
		void setDodgeUsing(YString newDodgeUsing) {m_DodgeUsing=newDodgeUsing;} //设置DodgeUsing(轻功使用)
  //属性：ParryUsing(招架_武功)
	private:
		YString m_ParryUsing; //属性ParryUsing(招架_武功)的成员变量
	public:
		YString getParryUsing(void) {return m_ParryUsing;} //读属性ParryUsing(招架_武功)
		void setParryUsing(YString newParryUsing) {m_ParryUsing=newParryUsing;} //设置ParryUsing(招架_武功)
  //属性：ForceUsing(使用内功)
	private:
		YString m_ForceUsing; //属性ForceUsing(使用内功)的成员变量
	public:
		YString getForceUsing(void) {return m_ForceUsing;} //读属性ForceUsing(使用内功)
		void setForceUsing(YString newForceUsing) {m_ForceUsing=newForceUsing;} //设置ForceUsing(使用内功)

  //属性：cklevel(仓库等级)
	private:
		long m_cklevel; //属性cklevel(仓库等级)的成员变量
	public:
		long getcklevel(void) {return m_cklevel;} //读属性cklevel(仓库等级)
		void setcklevel(long newcklevel) {m_cklevel=newcklevel;} //设置cklevel(仓库等级)

  //属性：AllckList(仓库物品列表)
	private:
		YString m_AllckList; //属性AllckList(仓库物品列表)的成员变量
	public:
		YString getAllckList(void) {return m_AllckList;} //读属性AllckList(仓库物品列表)
		void setAllckList(YString newAllckList) {m_AllckList=newAllckList;} //设置AllckList(仓库物品列表)

		
  //属性：AllSkillsList(所会技能)
	private:
		YString m_AllSkillsList; //属性AllSkillsList(所会技能)的成员变量
	public:
		YString getAllSkillsList(void) {return m_AllSkillsList;} //读属性AllSkillsList(所会技能)
		void setAllSkillsList(YString newAllSkillsList) {m_AllSkillsList=newAllSkillsList;} //设置AllSkillsList(所会技能)
//属性：workskills(劳动技能)
	private:
		YString m_workskills; //属性workskills(劳动技能)的成员变量
	public:
		YString getworkskills(void) {return m_workskills;} //读属性workskills(劳动技能)
		void setworkskills(YString newworkskills) {m_workskills=newworkskills;} //设置workskills(劳动技能)
  //属性：Experience(经验)
	private:
		long m_Experience; //属性Experience(经验)的成员变量
	public:
		long getExperience(void) {return m_Experience;} //读属性Experience(经验)
		void setExperience(long newExperience) {m_Experience=newExperience;refreshHP();} //设置Experience(经验)
  //属性：SameRoomEnemyList(房间内敌人列表)
	private:
		YString m_SameRoomEnemyList; //属性SameRoomEnemyList(房间内敌人列表)的成员变量
	public:
		YString getSameRoomEnemyList(void) {return m_SameRoomEnemyList;} //读属性SameRoomEnemyList(房间内敌人列表)
		void setSameRoomEnemyList(YString newSameRoomEnemyList) {m_SameRoomEnemyList=newSameRoomEnemyList;} //设置SameRoomEnemyList(房间内敌人列表)
  //属性：KillerName(杀死自己：凶手的名字)
	private:
		YString m_KillerName; //属性KillerName(杀死自己：凶手的名字)的成员变量
	public:
		YString getKillerName(void) {return m_KillerName;} //读属性KillerName(杀死自己：凶手的名字)
		void setKillerName(YString newKillerName) {m_KillerName=newKillerName;} //设置KillerName(杀死自己：凶手的名字)
  //属性：BeKillTimes(被杀次数)
	private:
		long m_BeKillTimes; //属性BeKillTimes(被杀次数)的成员变量
	public:
		long getBeKillTimes(void) {return m_BeKillTimes;} //读属性BeKillTimes(被杀次数)
		void setBeKillTimes(long newBeKillTimes) {m_BeKillTimes=newBeKillTimes;} //设置BeKillTimes(被杀次数)
  //属性：Potential(潜能)
	private:
		long m_Potential; //属性Potential(潜能)的成员变量
	public:
		long getPotential(void) {return m_Potential;} //读属性Potential(潜能)
		void setPotential(long newPotential) {m_Potential=newPotential;refreshHP();} //设置Potential(潜能)
  //属性：GoodnessCount(正气值)
	private:
		long m_GoodnessCount; //属性GoodnessCount(正气值)的成员变量
	public:
		long getGoodnessCount(void) {return m_GoodnessCount;} //读属性GoodnessCount(正气值)
		void setGoodnessCount(long newGoodnessCount) {m_GoodnessCount=newGoodnessCount;} //设置GoodnessCount(正气值)
  //属性：KillTimes(杀人次数)
	private:
		long m_KillTimes; //属性KillTimes(杀人次数)的成员变量
	public:
		long getKillTimes(void) {return m_KillTimes;} //读属性KillTimes(杀人次数)
		void setKillTimes(long newKillTimes) {m_KillTimes=newKillTimes;} //设置KillTimes(杀人次数)
  //属性：PKTimes(PK杀玩家次数)
	private:
		long m_PKTimes; //属性PKTimes(PK杀玩家次数)的成员变量
	public:
		long getPKTimes(void) {return m_PKTimes;} //读属性PKTimes(PK杀玩家次数)
		void setPKTimes(long newPKTimes) {m_PKTimes=newPKTimes;} //设置PKTimes(PK杀玩家次数)
  //属性：BePKTimes(被玩家PKer杀死的次数)
	private:
		long m_BePKTimes; //属性BePKTimes(被玩家PKer杀死的次数)的成员变量
	public:
		long getBePKTimes(void) {return m_BePKTimes;} //读属性BePKTimes(被玩家PKer杀死的次数)
		void setBePKTimes(long newBePKTimes) {m_BePKTimes=newBePKTimes;} //设置BePKTimes(被玩家PKer杀死的次数)
  //属性：QuestList(任务列表)
	private:
		YString m_QuestList; //属性QuestList(任务列表)的成员变量
	public:
		YString getQuestList(void) {return m_QuestList;} //读属性QuestList(任务列表)
		void setQuestList(YString newQuestList) {m_QuestList=newQuestList;} //设置QuestList(任务列表)
  //属性：Place(NPC所在位置，例如：华山派)
	private:
		YString m_Place; //属性Place(NPC所在位置，例如：华山派)的成员变量
	public:
		YString getPlace(void) {return m_Place;} //读属性Place(NPC所在位置，例如：华山派)
		void setPlace(YString newPlace) {m_Place=newPlace;} //设置Place(NPC所在位置，例如：华山派)
  //属性：School(门派，例如：华山派)
	private:
		YString m_School; //属性School(门派，例如：华山派)的成员变量
	public:
		YString getSchool(void) {return m_School;} //读属性School(门派，例如：华山派)
		void setSchool(YString newSchool) {m_School=newSchool;} //设置School(门派，例如：华山派)
  //属性：DeathMode(死亡方式)
	private:
		YString m_DeathMode; //属性DeathMode(死亡方式)的成员变量
	public:
		YString getDeathMode(void) {return m_DeathMode;} //读属性DeathMode(死亡方式)
		void setDeathMode(YString newDeathMode) {m_DeathMode=newDeathMode;} //设置DeathMode(死亡方式)
  //属性：AllEnemyList(杀死人物列表：所有敌人列表)
	private:
		YString m_AllEnemyList; //属性AllEnemyList(杀死人物列表：所有敌人列表)的成员变量
	public:
		YString getAllEnemyList(void) {return m_AllEnemyList;} //读属性AllEnemyList(杀死人物列表：所有敌人列表)
		void setAllEnemyList(YString newAllEnemyList) {m_AllEnemyList=newAllEnemyList;} //设置AllEnemyList(杀死人物列表：所有敌人列表)
  //属性：TeacherName(师父的名字)
	private:
		YString m_TeacherName; //属性TeacherName(师父的名字)的成员变量
	public:
		YString getTeacherName(void) {return m_TeacherName;} //读属性TeacherName(师父的名字)
		void setTeacherName(YString newTeacherName) {m_TeacherName=newTeacherName;} //设置TeacherName(师父的名字)
  //属性：Title(头衔)
	private:
		YString m_Title; //属性Title(头衔)的成员变量
	public:
		YString getTitle(void) {return m_Title;} //读属性Title(头衔)
		void setTitle(YString newTitle) {m_Title=newTitle;} //设置Title(头衔)
  //属性：Nick(绰号)
	private:
		YString m_Nick; //属性Nick(绰号)的成员变量
	public:
		YString getNick(void) {return m_Nick;} //读属性Nick(绰号)
		void setNick(YString newNick) {m_Nick=newNick;} //设置Nick(绰号)
  //属性：Describe(个人描述)
	private:
		YString m_Describe; //属性Describe(个人描述)的成员变量
	public:
		YString getDescribe(void) {return m_Describe;} //读属性Describe(个人描述)
		void setDescribe(YString newDescribe) {m_Describe=newDescribe;} //设置Describe(描述)
  //属性：SchoolPlace(辈分)
	private:
		long m_SchoolPlace; //属性SchoolPlace(辈分)的成员变量
	public:
		long getSchoolPlace(void) {return m_SchoolPlace;} //读属性SchoolPlace(辈分)
		void setSchoolPlace(long newSchoolPlace) {m_SchoolPlace=newSchoolPlace;} //设置SchoolPlace(辈分)
  //属性：IconNo(头像)
	private:
		YString m_IconNo; //属性IconNo(头像)的成员变量
	public:
		YString getIconNo(void) {return m_IconNo;} //读属性IconNo(头像)
		void setIconNo(YString newIconNo) {m_IconNo=newIconNo;} //设置IconNo(头像)
  //属性：FollowYou(跟随的人，跟着你的一群人)
	private:
		YString m_FollowYou; //属性FollowYou(跟随的人，跟着你的一群人)的成员变量
	public:
		YString getFollowYou(void) {return m_FollowYou;} //读属性FollowYou(跟随的人，跟着你的一群人)
		void setFollowYou(YString newFollowYou) {m_FollowYou=newFollowYou;} //设置FollowYou(跟随的人，跟着你的一群人)
  //属性：GoDirection(前进方向)
	private:
		YString m_GoDirection; //属性GoDirection(前进方向)的成员变量
	public:
		YString getGoDirection(void) {return m_GoDirection;} //读属性GoDirection(前进方向)
		void setGoDirection(YString newGoDirection) {m_GoDirection=newGoDirection;} //设置GoDirection(前进方向)
  //属性：YouFollow(跟随，你跟随的一个人)
	private:
		YString m_YouFollow; //属性YouFollow(跟随，你跟随的一个人)的成员变量
	public:
		YString getYouFollow(void) {return m_YouFollow;} //读属性YouFollow(跟随，你跟随的一个人)
		void setYouFollow(YString newYouFollow) {m_YouFollow=newYouFollow;} //设置YouFollow(跟随，你跟随的一个人)
  //属性：ActorWeight(重量)
	private:
		long m_ActorWeight; //属性Weight(重量)的成员变量
	public:
		long getActorWeight(void) {return m_ActorWeight;} //读属性Weight(重量)
		void setActorWeight(long newActorWeight) {m_ActorWeight=newActorWeight;} //设置Weight(重量)
  //属性：Age(年龄)
	private:
		long m_ActorAge; //属性Age(年龄)的成员变量
	public:
		long getActorAge(void) {return m_ActorAge;} //读属性Age(年龄)
		void setActorAge(long newAge) {m_ActorAge=newAge;} //设置Age(年龄)
  //属性：Kill(对杀)
	private:
		long m_Kill; //属性Kill(对杀)的成员变量
	public:
		long getKill(void) {return m_Kill;} //读属性Kill(对杀)
		void setKill(long newKill) {m_Kill=newKill;} //设置Kill(对杀)
  //属性：Zdpk(主动PK)
	private:
		long m_Zdpk; //属性zdpk(主动PK)的成员变量
	public:
		long getZdpk(void) {return m_Zdpk;} //读属性zdpk(主动PK)
		void setZdpk(long newZdpk) {m_Zdpk=newZdpk;} //设置zdpk(主动PK)
  //属性：KillAndGet(对杀拣物品)
	private:
		long m_KillAndGet; //属性KillAndGet(对杀)的成员变量
	public:
		long getKillAndGet(void) {return m_KillAndGet;} //读属性KillAndGet(对杀)
		void setKillAndGet(long newKillAndGet) {m_KillAndGet=newKillAndGet;} //设置KillAndGet(对杀)
  //属性：KillAndGe(对杀割头)
	private:
		long m_KillAndGe; //属性KillAndGe(对杀)的成员变量
	public:
		long getKillAndGe(void) {return m_KillAndGe;} //读属性KillAndGe(对杀)
		void setKillAndGe(long newKillAndGe) {m_KillAndGe=newKillAndGe;} //设置KillAndGe(对杀)
  //属性：Battle(战斗)
	private:
		long m_Battle; //属性Battle(战斗)的成员变量
	public:
		long getBattle(void) {return m_Battle;} //读属性Battle(战斗)
		void setBattle(long newBattle) {m_Battle=newBattle;} //设置Battle(战斗)
  //属性：WeaponName(武器的名字)
	private:
		YString m_WeaponName; //属性WeaponName(武器的名字)的成员变量
	public:
		YString getWeaponName(void) {return m_WeaponName;} //读属性WeaponName(武器的名字)
		void setWeaponName(YString newWeaponName) {m_WeaponName=newWeaponName;playerarmchange();} //设置WeaponName(武器的名字)
  //属性：ClothName(衣服的名字)
	private:
		YString m_ClothName; //属性ClothName(衣服的名字)的成员变量
	public:
		YString getClothName(void) {return m_ClothName;} //读属性ClothName(衣服的名字)
		void setClothName(YString newClothName) {m_ClothName=newClothName;} //设置ClothName(衣服的名字)
  //属性：Armor(盔甲)
	private:
		YString m_Armor; //属性Armor(盔甲)的成员变量
	public:
		YString getArmor(void) {return m_Armor;} //读属性Armor(盔甲)
		void setArmor(YString newArmor) {m_Armor=newArmor;} //设置Armor(盔甲)
  //属性：Hat(帽子)
	private:
		YString m_Hat; //属性Hat(帽子)的成员变量
	public:
		YString getHat(void) {return m_Hat;} //读属性Hat(帽子)
		void setHat(YString newHat) {m_Hat=newHat;} //设置Hat(帽子)
  //属性：Shoe(鞋)
	private:
		YString m_Shoe; //属性Shoe(鞋)的成员变量
	public:
		YString getShoe(void) {return m_Shoe;} //读属性Shoe(鞋)
		void setShoe(YString newShoe) {m_Shoe=newShoe;} //设置Shoe(鞋)
  //属性：Flower(花)
	private:
		YString m_Flower; //属性Flower(花)的成员变量
	public:
		YString getFlower(void) {return m_Flower;} //读属性Flower(花)
		void setFlower(YString newFlower) {m_Flower=newFlower;} //设置Flower(花)
  //属性：Ring(戒指)
	private:
		YString m_Ring; //属性Ring(戒指)的成员变量
	public:
		YString getRing(void) {return m_Ring;} //读属性Ring(戒指)
		void setRing(YString newRing) {m_Ring=newRing;} //设置Ring(戒指)
  //属性：Necklace(项链)
	private:
		YString m_Necklace; //属性Necklace(项链)的成员变量
	public:
		YString getNecklace(void) {return m_Necklace;} //读属性Necklace(项链)
		void setNecklace(YString newNecklace) {m_Necklace=newNecklace;} //设置Necklace(项链)
  //属性：Bangle(手镯)
	private:
		YString m_Bangle; //属性Bangle(手镯)的成员变量
	public:
		YString getBangle(void) {return m_Bangle;} //读属性Bangle(手镯)
		void setBangle(YString newBangle) {m_Bangle=newBangle;} //设置Bangle(手镯)
  //属性：Feature(容貌)
	private:
		long m_Feature; //属性Feature(容貌)的成员变量
	public:
		long getFeature(void) {return m_Feature;} //读属性Feature(容貌)
		void setFeature(long newFeature) {m_Feature=newFeature;} //设置Feature(容貌)
  //属性：Feature(附加容貌值)
	private:
		long m_AddFeature; //属性Feature(容貌)的成员变量
	public:
		long getAddFeature(void) {return m_AddFeature;} //读属性ActorFeature(附加容貌值)
		void setAddFeature(long newFeature) {m_AddFeature=newFeature;} //设置ActorFeature(附加容貌值)
  //属性：Luck(福缘)
	private:
		long m_Luck; //属性Luck(福缘)的成员变量
	public:
		long getLuck(void) {return m_Luck;} //读属性Luck(福缘)
		void setLuck(long newLuck) {m_Luck=newLuck;} //设置Luck(福缘)
  //属性：Luck(附加福缘)
	private:
		long m_AddLuck; //属性Luck(附加福缘)的成员变量
	public:
		long getAddLuck(void) {return m_AddLuck;} //读属性Luck(附加福缘)
		void setAddLuck(long newLuck) {m_AddLuck=newLuck;} //设置Luck(附加福缘)
  //属性：Death(死亡)
	private:
		long m_Death; //属性Death(死亡)的成员变量
	public:
		long getDeath(void) {return m_Death;} //读属性Death(死亡)
		void setDeath(long newDeath) {m_Death=newDeath;} //设置Death(死亡)
	//Begin
	private:
		long m_BeginArm;
	public:
		long getBeginArm(void) {return m_BeginArm;}
		void setBeginArm(long newBeginArm) {m_BeginArm=newBeginArm;}

        //属性：LastArm(后天臂力)
	private:
		long m_LastArm; //属性LastArm(后天臂力)的成员变量
	public:
		long getLastArm(void) {return m_LastArm;} //读属性LastArm(后天臂力)
		void setLastArm(long newLastArm) {m_LastArm=newLastArm;} //设置LastArm(后天臂力)
        //属性：LastLearn(后天悟性)
	private:
		long m_LastLearn; //属性LastLearn(后天悟性)的成员变量
	public:
		long getLastLearn(void) {return m_LastLearn;} //读属性LastLearn(后天悟性)
		void setLastLearn(long newLastLearn) {m_LastLearn=newLastLearn;} //设置LastLearn(后天悟性)
        //属性：laseDodge(后天身法)
	private:
		long m_laseDodge; //属性laseDodge(后天身法)的成员变量
	public:
		long getlaseDodge(void) {return m_laseDodge;} //读属性laseDodge(后天身法)
		void setlaseDodge(long newlaseDodge) {m_laseDodge=newlaseDodge;} //设置laseDodge(后天身法)
	//属性：LastForce(后天根骨)
	private:
		long m_LastForce; //属性LastForce(后天根骨)的成员变量

	public:
		long getLastForce(void) {return m_LastForce;} //读属性LastForce(后天根骨)
		void setLastForce(long newLastForce) {m_LastForce=newLastForce;} //设置LastForce(后天根骨)
	//属性：NotDead(不死)
	private:
		long m_NotDead; //属性NotDead(不死)的成员变量

	public:
		long getNotDead(void) {return m_NotDead;} //读属性NotDead(不死)
		void setNotDead(long newNotDead) {m_NotDead=newNotDead;} //设置NotDead(不死)
	//属性：m_wichpho(特殊图像)
	private:
		long m_wichpho; //属性newwichpho(特殊图像)的成员变量

	public:
		long getwichpho(void) {return m_wichpho;} //读属性newwichpho(特殊图像)
		void setwichpho(long newwichpho) {m_wichpho=newwichpho;} //设置newwichpho(特殊图像)

  public:
		YActor(YString initFileName="") ;  //构造函数
		virtual ~YActor(){}; //析构函数

    //名字的显示
    virtual YString getNickName(void);

		//事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YActor");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YString command);
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);
		//事件AfterChildAdd的默认处理函数
		virtual int onAfterChildAdd(YMUDObject* sender, YMUDObject* child);
		//事件AfterChildRemove的默认处理函数
		virtual int onAfterChildRemove(YMUDObject* sender, YMUDObject* child);
    //事件RoommateEnter的默认处理函数
    virtual int onRoommateEnter(YMUDObject* sender, YAbstractActor* actor);

	public:
		//事件AfterPropertyChange的默认处理函数
		virtual int onAfterPropertyChange(YMUDObject* sender, YString PropertyName,
                                        long oldValue, long newValue);
  	//事件Message的默认处理函数
		virtual int onMessage(YAbstractActor* speaker, YString message);

	//属性：Level
	public:
		virtual int getLevel(void) {return 20;} //读属性Level
		virtual void setLevel(int newLevel) {} //设置Level
	//属性：Sex
	public:
		sex_type getSex(void); //读属性Sex
		void setSex(YString sex) {set("性别",sex);}//设置Sex

	//属性：Icon(头像)
	public:
		virtual YString getIcon(void); //读属性Icon(头像)

    //将子物体传给另一物体
    virtual bool giveChildTo(YMUDObject* child, YMUDObject* another, long count=1, long No=1);
    //重新计算负重
    void resumWeight(void);

    //时间处理
    virtual int onTimer(void);
    //接收一条消息
    virtual void message(YAbstractActor* speaker, YString msg, bool newline=true,
                      msg_type messagetype=ORIGINAL_MSG, const YString& name="");
    //各种命令处理
    virtual int go(YString direction);    //去其他房间的函数
    virtual int dofight(void);            //比武函数
    virtual int dokill(void);             //对杀函数
    virtual int zhandou(YString sentence); //战斗的计算
    virtual int perform(YString sentence); //战斗的计算
    virtual int hit(YString sentence);     //强行攻击
    virtual int fight(YString sentence);   //较量武功
    virtual int touxi(YString sentence);   //偷袭其他人物
    virtual int beg(YString sentence);     //乞讨
    virtual int steal(YString sentence);   //偷
    virtual int killget(YString sentence);    //杀死并拣东西
    virtual int killge(YString sentence);    //杀死并割头
    virtual int kill(YString sentence);    //杀死
    virtual int halt(void);                //停止当时的工作
    virtual int ActorAddFeatureChange(void);     //人物附加容貌变化
    virtual int ActorAddRecoveryChange(void);     //人物附加防御力力变化
    virtual int playerfindname(YString allname,YString findname); //在allname中查找findname
    virtual int delname(void); //删除名字
    virtual int dead(void); //死亡
    virtual int faint(void); //昏到
    virtual int wakeup(void);  //清醒
    virtual int gotoRoom(YString roomName);   //到其他地点的命令
    virtual int dropplayer(void);//丢掉玩家
    virtual bool findStringInStr (YString theString ,YString findString);//在字符串里查找字符串
    virtual int showPhoto(YString man , YString woman); //人物的图形显示
    virtual int move(YString sentence);   //屋内移动
    virtual int movetodirection( YString direction );   //屋内方向移动
    virtual int isnewbie(void);//是不是新手
    virtual int playerarmchange(void){return 1;};     //玩家攻击力变化
    virtual int playerhpchange(void){return 1;};        //气血变化
    virtual int delQuestpercent(YString questname , long percent); //清除任务百分比
    virtual YString selePhoto(YString basephoto); //清除任务百分比

    //zhy
    //信息输出处理函数
    virtual int OutputMsg(YAbstractActor* executor,YString msg);//对调用者和其他人输出不同信息
    virtual int letsDestroy(void); //销毁子物品
    //刷新hp的动态显示
    virtual void refreshHP(void);

    int displayEx(YString msg);
};

#endif //__YACTOR_H__
