//---------------------------------------------------------------------------
//
// yactor.cpp    2000年6月12日
//
// 类YActor：人物
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
YActor::YActor(YString initFileName): YAbstractActor(initFileName),m_DestroyList(""),
                                                                    m_Status(""),
                                                                    m_FightInterval(0),
                                                                    m_FaintTime(0),
                                                                    m_Adversary(""),
                                                                   // m_ActorName(""),
                                                                    m_ActorShow(""),
                                                                    m_Body(0),
                                                                    m_MaxBody(0),
                                                                    m_AddMaxBody(0),
                                                                    m_Energy(0),
                                                                    m_MaxEnergy(0),
                                                                    m_AddMaxEnergy(0),
                                                                    m_Wimpy(0),
                                                                    m_FreeTime(0),
                                                                    m_Busy(0),
                                                                    m_WeaponType(""),
                                                                    m_SexString(""),
                                                                    m_InhereAttack(0),
                                                                    m_PowerUpAttack(0),
                                                                    m_InternalForce(0),
                                                                    m_MaxInternalForce(0),
                                                                    m_AddMaxInternalForce(0),
                                                                    m_ForceAttack(0),
                                                                    m_WeaponAttack(0),
                                                                    m_InhereDefense(0),
                                                                    m_AppendAttack(0),
                                                                    m_AppendDefense(0),
                                                                    m_PowerUpDefense(0),
                                                                    m_WeaponName(""),
                                                                    m_ClothName(""),
                                                                    //m_BehindCelerity(0),
                                                                    m_DodgeUsing(""),
                                                                    m_AllckList(""),
                                                                    m_AllSkillsList(""),
        							    m_workskills(""),
                                                                    m_Experience(0),
                                                                    m_SameRoomEnemyList(""),
                                                                    m_KillerName(""),
                                                                    m_BeKillTimes(0),
                                                                    m_Potential(0),
                                                                    m_GoodnessCount(0),
                                                                    m_KillTimes(0),
                                                                    m_PKTimes(0),
                                                                    m_BePKTimes(0),
                                                                    m_QuestList(""),
                                                                    m_Place(""),
                                                                    m_School(""),
                                                                    m_DeathMode(""),
                                                                    m_AllEnemyList(""),
                                                                    m_TeacherName(""),
                                                                    m_Title(""),
                                                                    m_Nick(""),
                                                                    m_Describe(""),
                                                                    m_SchoolPlace(0),
                                                                    m_IconNo(""),
                                                                    m_FollowYou(""),
                                                                    m_GoDirection(""),
                                                                    m_YouFollow(""),
                                                                    m_ActorWeight(0),
                                                                    m_ActorAge(0),
                                                                    m_Kill(0),
                                                                    m_Zdpk(0),
                                                                    m_KillAndGet(0),
                                                                    m_Battle(0),
                                                                    m_Armor(""),
                                                                    m_Arming(""),
                                                                    m_Cloke(""),
                                                                    m_Gird(""),
                                                                    m_Finger(""),
                                                                    m_Dangler(""),
                                                                    m_Domino(""),
                                                                    m_Hat(""),
                                                                    m_Shoe(""),
                                                                    m_Flower(""),
                                                                    m_Ring(""),
                                                                    m_Necklace(""),
                                                                    m_Bangle(""),
                                                                    m_Feature(0),
                                                                    m_AddFeature(0),
                                                                    m_Luck(0),
                                                                    m_AddLuck(0),
                                                                    m_Death(0),
                                                                    m_wichpho(0),//特殊图像
        m_BeginArm(0),
	m_LastArm(0),//描述的变量为：后天臂力
	m_LastLearn(0),//描述的变量为：后天悟性
	m_LastDodge(0),//描述的变量为：后天身法
	m_LastForce(0),//描述的变量为：后天根骨
	m_AddArm(0),//描述的变量为：附加臂力
	m_AddLearn(0),//描述的变量为：附加悟性
	m_AddDodge(0),//描述的变量为：附加身法
	m_AddForce(0),//描述的变量为：附加根骨
        m_NotDead(0)    //不死的属性
{
  setSmallTime(2000);
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YActor::isTypeOf(YString className)
{
  if(className=="YActor") return 1;
  else return YAbstractActor::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YActor::onAfterLoad(void)
{
  int retVal=YAbstractActor::onAfterLoad();

  setDestroyList(getAsString("销毁列表"));
  setStatus(getAsString("状态"));
  setFightInterval(getAsLong("战斗间隔"));
  setFaintTime(getAsLong("晕倒时间"));
  setAdversary(getAsString("对手"));
//  setActorName(getAsString("名字"));
  setActorShow(getAsString("描述"));
  setBody(getAsLong("气血"));
  setMaxBody(getAsLong("最大气血"));
  setAddMaxBody(getAsLong("附加最大气血"));
  setWimpy(getAsLong("逃跑系数"));
  setFreeTime(getAsLong("空闲时间"));
  setBusy(getAsLong("繁忙"));
  setWeaponType(getAsString("武器类型"));
  setSexString(getAsString("性别"));
  setInhereAttack(getAsLong("固定攻击力"));
  setPowerUpAttack(getAsLong("powerup攻击力"));
  setInternalForce(getAsLong("内力"));
  setMaxInternalForce(getAsLong("最大内力"));
  setAddMaxInternalForce(getAsLong("附加最大内力"));
  setForceAttack(getAsLong("加力"));
  setWeaponAttack(getAsLong("武器攻击力"));
  setInhereDefense(getAsLong("固定防御力"));
  setAppendAttack(getAsLong("附加攻击力"));
  setAppendDefense(getAsLong("附加防御力"));
  setPowerUpDefense(getAsLong("powerup防御力"));
  setWeaponName(getAsString("武器"));
  setClothName(getAsString("衣服"));
  //setBehindCelerity(getAsLong("后天身法"));
  setDodgeUsing(getAsString("轻功_使用"));
  setParryUsing(getAsString("招架_武功"));
  setForceUsing(getAsString("使用内功"));
  setAllckList(getAsString("仓库物品列表"));
  setAllSkillsList(getAsString("所会技能"));
  setworkskills(getAsString("劳动技能"));    //劳动技能
  setExperience(getAsLong("经验"));
  setSameRoomEnemyList(getAsString("房间内敌人列表"));
  setMaxEnergy(getAsLong("最大精力"));
  setAddMaxEnergy(getAsLong("附加最大精力"));
  setKillerName(getAsString("杀死自己"));
  setBeKillTimes(getAsLong("被杀次数"));
  setPotential(getAsLong("潜能"));
  setGoodnessCount(getAsLong("正气值"));
  setKillTimes(getAsLong("杀人次数"));
  setPKTimes(getAsLong("pk数"));
  setBePKTimes(getAsLong("被pk数"));
  setQuestList(getAsString("任务列表"));
  setPlace(getAsString("位置"));
  setSchool(getAsString("门派"));
  setDeathMode(getAsString("死亡方式"));
  setAllEnemyList(getAsString("杀死人物列表"));
  setTeacherName(getAsString("师父"));
  setTitle(getAsString("头衔"));
  setNick(getAsString("绰号"));
  setDescribe(getAsString("个人描述"));
  setEnergy(getAsLong("精力"));
  setSchoolPlace(getAsLong("辈分"));
  setIconNo(getAsString("头像"));
  setFollowYou(getAsString("跟随的人"));
  setGoDirection(getAsString("前进方向"));
  setYouFollow(getAsString("跟随"));
  setActorWeight(getAsLong("重量"));
  setActorAge(getAsLong("年龄"));
  setKill(getAsLong("对杀"));
  setZdpk(getAsLong("主动pk"));
  setKillAndGet(getAsLong("对杀拣物品"));
  setKillAndGe(getAsLong("对杀割头"));
  setBattle(getAsLong("战斗"));
  setArmor(getAsString("盔甲"));
  setArming(getAsString("徽章"));
  setCloke(getAsString("斗篷"));
  setGird(getAsString("玉佩"));
  setFinger(getAsString("扳指"));
  setDangler(getAsString("耳环"));
  setDomino(getAsString("面具"));
  setHat(getAsString("帽子"));
  setShoe(getAsString("鞋"));
  setFlower(getAsString("花"));
  setRing(getAsString("戒指"));
  setNecklace(getAsString("项链"));
  setBangle(getAsString("手镯"));
  setFeature(getAsLong("容貌"));
  setAddFeature(getAsLong("附加容貌值"));
  setLuck(getAsLong("福缘"));
  setAddLuck(getAsLong("附加福缘"));
  setDeath(getAsLong("死亡"));
  setBeginArm(getAsLong("先天臂力")) ; 
  setLastArm(getAsLong("后天臂力")) ; 
  setLastLearn(getAsLong("后天悟性")) ;
  setLastDodge(getAsLong("后天身法")) ;
  setLastForce(getAsLong("后天根骨")) ;
  setAddArm(getAsLong("附加臂力")) ; 
  setAddLearn(getAsLong("附加悟性")) ;
  setAddDodge(getAsLong("附加身法")) ;
  setAddForce(getAsLong("附加根骨")) ;
  setNotDead(getAsLong("不死"));
  setwichpho(getAsLong("特殊图像"));
  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YActor::onBeforeSave(void)
{
  int retVal=YAbstractActor::onBeforeSave();

  set("销毁列表",getDestroyList());
  set("状态",getStatus());
  set("战斗间隔",getFightInterval());
  set("晕倒时间",getFaintTime());
  set("对手",getAdversary());
//  set("名字",getActorName());
  set("描述",getActorShow());
  set("气血",getBody());
  set("最大气血",getMaxBody());
  set("附加最大气血",getAddMaxBody());
  set("精力",getEnergy());
  set("最大精力",getMaxEnergy());
  set("附加最大精力",getAddMaxEnergy());
  set("逃跑系数",getWimpy());
  set("空闲时间",getFreeTime());
  set("繁忙",getBusy());
  set("武器类型",getWeaponType());
  set("性别",getSexString());
  set("固定攻击力",getInhereAttack());
  set("powerup攻击力",getPowerUpAttack());
  set("内力",getInternalForce());
  set("最大内力",getMaxInternalForce());
  set("附加最大内力",getAddMaxInternalForce());
  set("加力",getForceAttack());
  set("武器攻击力",getWeaponAttack());
  set("固定防御力",getInhereDefense());
  set("附加攻击力",getAppendAttack());
  set("附加防御力",getAppendDefense());
  set("powerup防御力",getPowerUpDefense());
  set("武器",getWeaponName());
  set("衣服",getClothName());
  //set("后天身法",getBehindCelerity());
  set("轻功_使用",getDodgeUsing());
  set("招架_武功",getParryUsing());
  set("使用内功",getForceUsing());
  set("仓库物品列表",getAllckList());
  set("所会技能",getAllSkillsList());
  set("劳动技能",getworkskills());  	//劳动技能
  set("经验",getExperience());
  set("房间内敌人列表",getSameRoomEnemyList());
  set("杀死自己",getKillerName());
  set("被杀次数",getBeKillTimes());
  set("潜能",getPotential());
  set("正气值",getGoodnessCount());
  set("杀人次数",getKillTimes());
  set("pk数",getPKTimes());
  set("被pk数",getBePKTimes());
  set("任务列表",getQuestList());
  set("位置",getPlace());
  set("门派",getSchool());
  set("死亡方式",getDeathMode());
  set("杀死人物列表",getAllEnemyList());
  set("师父",getTeacherName());
  set("头衔",getTitle());
  set("绰号",getNick());
  set("个人描述",getDescribe());
  set("辈分",getSchoolPlace());
  set("头像",getIconNo());
  set("跟随的人",getFollowYou());
  set("前进方向",getGoDirection());
  set("跟随",getYouFollow());
  set("重量",getActorWeight());
  set("年龄",getActorAge());
  set("对杀",getKill());
  set("主动pk",getZdpk());
  set("对杀拣物品",getKillAndGet());
  set("对杀割头",getKillAndGe());
  set("战斗",getBattle());
  set("盔甲",getArmor());
  set("徽章",getArming());
  set("斗篷",getCloke());
  set("玉佩",getGird());
  set("扳指",getFinger());
  set("耳环",getDangler());
  set("面具",getDomino());
  set("帽子",getHat());
  set("鞋",getShoe());
  set("花",getFlower());
  set("戒指",getRing());
  set("项链",getNecklace());
  set("手镯",getBangle());
  set("容貌",getFeature());
  set("附加容貌值",getAddFeature());
  set("福缘",getLuck());
  set("附加福缘",getAddLuck());
  set("死亡",getDeath());
  set("先天臂力",getBeginArm()); 
  set("后天臂力",getLastArm());//结束后 后天臂力 变量的处理
  set("后天悟性",getLastLearn());//结束后 后天悟性 变量的处理
  set("后天身法",getLastDodge());//结束后 后天身法 变量的处理
  set("后天根骨",getLastForce());//结束后 后天根骨 变量的处理
  set("附加臂力",getAddArm());//结束后 附加臂力 变量的处理
  set("附加悟性",getAddLearn());//结束后 附加悟性 变量的处理
  set("附加身法",getAddDodge());//结束后 附加身法 变量的处理
  set("附加根骨",getAddForce());//结束后 附加根骨 变量的处理
  set("不死",getNotDead());//不死的属性
  set("特殊图像",getwichpho());//特殊图像
  return retVal;
}
//-------------------------------------------------------------
//属性： NickName (显示人物得绰号和名字)
YString YActor::getNickName(void)
{
    YString name=getActorName(); //名字
    YString hand = getTitle(); //头衔
    YString nick = getNick(); //绰号
    if (hand != "") hand = "["+hand+"]";
    YString atThisTime = getStatus(); //状态
    if  (atThisTime !="")  atThisTime ="("+atThisTime+")";
    return hand+nick+"<font color="+g_Settings->getNPCNameColor()
          +"><span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+name+"\")>"+name+atThisTime+"</span></font>";
}
//--------------------------------------------------------
sex_type YActor::getSex(void) //读属性Sex
{
  YString sex=getSexString(); //性别
  if(sex=="男") return MALE;
  else if(sex=="女") return FEMALE;
  else return SEX_UNKNOWN;
}
//--------------------------------------------------------
//读属性Icon(头像)
YString YActor::getIcon(void)
{
  YString iconNo=getIconNo(); //头像
  if(iconNo!="") return iconNo;
  else if(getSex()==FEMALE || getwichpho() == 1 ) iconNo="4";
  else iconNo="0";
  YString zhuangtai = getStatus(); //状态
  if (zhuangtai == "昏倒中" || zhuangtai == "躺" ||zhuangtai == "睡眠中")
  //判断人物是昏到还是睡眠还是躺
  {
    if (iconNo == "4") iconNo = "5";
    else  iconNo="1";
  }
  if (zhuangtai == "打坐" || zhuangtai == "吐纳" || zhuangtai == "坐")
  //坐的姿态
  {
    if (iconNo == "4") iconNo = "6";
    else  iconNo="2";
  }
  iconNo = selePhoto(iconNo);
  return iconNo;
}
//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YActor::executeCommand(YString command)
{
    //处理晕倒
  if(getFaintTime()>0)  //还在晕倒，晕倒时间 > 0
  {
    display("你现在什么也做不了！");
    return 1;
  }
  return 0;
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YActor::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  return 0;
}
//--------------------------------------------------------
//事件Message的默认处理函数
int YActor::onMessage(YAbstractActor* speaker, YString message)
{
  return 1;
}
//---------------------------------------------------------
//事件AfterChildAdd的默认处理函数
int YActor::onAfterChildAdd(YMUDObject* sender, YMUDObject* child)
{
  YMUDObject::onAfterChildAdd(sender, child);
  return 1;
}
//--------------------------------------------------------
//事件AfterChildRemove的默认处理函数
int YActor::onAfterChildRemove(YMUDObject* sender, YMUDObject* child)
{
  YMUDObject::onAfterChildRemove(sender, child);
  return 1;
}

//----------------------------------------------------------
//事件ckSave的默认处理函数
bool YActor::ckSave(YMUDObject* child,long No)
{
  if (YMUDObject::ckSave(child,No))
  {
    if (child == NULL) return false;
//    resumWeight();
    return true ;
  }
  return false;
}


//----------------------------------------------------------
//事件giveChildTo的默认处理函数
bool YActor::giveChildTo(YMUDObject* child, YMUDObject* another, long count, long No)
{
  if (YMUDObject::giveChildTo(child,another, count, No))
  {
    if ( (another == NULL) || (child == NULL)) return false;
    if (another->isTypeOf("YActor"))
    {            //引用时判断(another == NULL)
     ((YActor*)another)->resumWeight();
    }
    resumWeight();
    return true ;
  }
  return false;
}
//--------------------------------------------------------
//重新计算负重
void YActor::resumWeight(void)
{
  YString allthing=enumChildrenThing();
  YString onething ;
  long allweight = 0;
  //物品重量
  while ((onething= allthing.getWord()) != "")
  {
    YAbstractThing* AbsThing = findChildThing(onething);
    if ( !AbsThing ) continue;   //判断是否为空
    YThing* sth ;
    if(AbsThing->isTypeOf("YThing"))
    {
      sth = (YThing*)AbsThing;
    }
    else continue;

    long count = sth->getCount();
    long weight = sth->getThingWeight(); //"重量"
    if (weight == 0)
    {
      sth->setThingWeight(5); //重量
      weight = 5;
    }
    if ( onething == "金子" || onething == "银子" || onething == "铜板")
    {
      count = 1 ;
      weight = 10 ;
    }
    allweight = allweight + (weight *  count) ;
  }
  //人物的重量
  allthing = enumChildrenActor();
  while ((onething= allthing.getWord()) != "")
  {
    YAbstractActor* AbsActor = findChildActor(onething);
    if ( !AbsActor ) continue;   //判断是否为空
    YActor* sth ;
    if(AbsActor->isTypeOf("YActor"))
    {
        sth = (YActor*)AbsActor;
    }
    else continue;

    long weight = sth->getActorWeight(); //"重量"
    if (weight == 0)
    {
      sth->setActorWeight(300); //"重量"
      weight = 300;
    }
    allweight = allweight + weight ;
  }
  if(isTypeOf("YPlayer")){
    ((YPlayer*)this)->setWeight(allweight); //"负重"
  }
}
//--------------------------------------------------------
//事件AfterPropertyChange的默认处理函数
int YActor::onAfterPropertyChange(YMUDObject* sender, YString Property,
                                        long oldValue, long newValue)
{
  //调用上级处理函数
  YAbstractActor::onAfterPropertyChange(sender,Property,oldValue, newValue);
  return 1;
}
//--------------------------------------------------------
//接收一条消息
void YActor::message(YAbstractActor* speaker, YString msg, bool newline,
                 msg_type messagetype, const YString& name)
{
  onMessage(speaker, msg);
}
//--------------------------------------------------------
//定时触发事件
int YActor::onTimer(void)
{
  YAbstractActor::onTimer(); //首先调用父类的处理函数
  if(getDestroyList()!="") letsDestroy(); //销毁列表
  //long fighting=getAsLong("战斗");
  YString faint = getStatus(); //状态
  long inthistime =  getSmallTime() ;
  //战斗的的处理函数  //对杀的处理函数
  if (getFightInterval() <= 0) //"战斗间隔"
  {
      setFightInterval(g_Settings->getsitFightSkipTime());  //时间的控制，战斗间隔复位
      if (faint == "战斗中") //在发呆，晕倒等的时候不用执行
      {
        if (dokill() == 0)  dofight();
      }
      else if (faint == "") //人物如果是空闲的话，人物恢复
      {
        if (isTypeOf("YNPC"))
        {
          long npcqixue = getBody(); //气血
          long npamaxqixue = getMaxBody(); //最大气血
          if (npcqixue < npamaxqixue )
          {
            setBody(npcqixue + npamaxqixue/100); //气血
          }
        }
      }
  }
  else setFightInterval(getFightInterval()- inthistime); //战斗间隔

  // 晕倒地处理
  long fainttime =getFaintTime() ; //晕倒时间
  if ( fainttime < 0 )
  {
      wakeup();
  }
  else setFaintTime(fainttime-inthistime); //晕倒时间
  return 1;
}
//--------------------------------------------------------
//事件RoommateEnter的默认处理函数
int YActor::onRoommateEnter(YMUDObject* sender, YAbstractActor* actor)
{
  return 1;
}
//--------------------------------------------------------
int YActor::go(YString direction)
{
//  if ( getAsLong ("战斗") == 1 || getAsLong ("对杀") == 1 )
  if (getStatus()=="战斗中") //状态
  {
      long randsize = rand() % 100;
      if (randsize < g_Settings->getsitFleeChance())//getAsLong("逃跑机会") )
      {
        display ("你被对手一把拦住了。");
        return 1;
      }
  }
  //跟随处理
  YString followsb=getFollowYou(); //跟随的人
  YRoom* oldroom;
  setGoDirection(direction); //前进方向
  //处理人物出房间时的方向
  movetodirection(direction);
  if(getRoom()->isTypeOf("YRoom")) oldroom = (YRoom*)getRoom();
  else
  {
    oldroom = NULL;
    return 1;
  }
  //处理原房间的对手问题
  YString fingername = getAdversary(); //对手
  YActor* finger=NULL ;
  setStatus(""); //状态清空
  setAdversary(""); //对手清空
  showPhoto("0","4");
  finger = (YActor*)(oldroom->findChildActor(fingername)) ;
  if (finger)
  {
    display("你停止了和"+fingername+"的较量向"+direction+"离开了这里，");
    finger->display (getDisplayName() + "停止了和你的较量，向"+direction+"离开了");
    finger->setStatus(""); //对手的状态清空
    finger->setAdversary(""); //对手的对手清空
    finger->showPhoto("0","4");
  }
  int retVal=oldroom->sendActorTo(this,direction);
  if(retVal==0) {
     if (oldroom == getRoom())return 1;
     oldroom->getRoomChat()->talk(NULL, this->getDisplayName()+"向"+direction+"离开了这里。");
     YString todirection ;
     //来到的方向
     if (direction == "东" ) todirection = "西" ;
     else if (direction == "东北" ) todirection = "西南" ;
     else if (direction == "北" ) todirection = "南" ;
     else if (direction == "西北" ) todirection = "东南" ;
     else if (direction == "西" ) todirection = "东" ;
     else if (direction == "西南" ) todirection = "东北" ;
     else if (direction == "南") todirection = "北" ;
     else if (direction == "东南" ) todirection = "西北" ;
     else todirection = "别的地方";
     //movetodirection(todirection);
     getRoom()->getRoomChat()->talk(NULL, this->getDisplayName()+"从"+todirection+"来到了这里。",this);
     move((YString)(getX()-80+(rand()%160))+" "+(YString)(getY()-80+(rand()%160)));
     //if(isTypeOf("YPlayer")) ((YPlayer*)this)->look();
     /*
     //如果人物有重叠现象出现的解决方法
     YString actorList=getRoom()->enumChildrenActor();
     YString haveplayer="" ;
     int xuenhuan = 100;
     while(xuenhuan--)//处理人前有人的情况
     {
       int flag = 1;
       while ((haveplayer =actorList.getWord())!= "" )
       {
           YActor* isActor ;
           if ((getRoom()->findChildActor(haveplayer))->isTypeOf("YActor"))
           {
             isActor = (YActor*)getRoom()->findChildActor(haveplayer);
             if (isActor && (isActor != this))//有人物
             {
               if ((isActor->getX()== getX()) && (isActor->getY() ==getY())) //人物的坐标相同
               {
                 //随机移动一定的个单位
                 move((YString)(getX()-80+(rand()%160))+" "+(YString)(getY()-80+(rand()%160)));
                 flag = 0;
               }
             }
             else continue ;
           }
       }
       if (flag == 1) break ;//没有人物时的处理
     }
     */
  }
  else if(retVal==1) display("这个方向没有出路");
  else if(retVal==2) display("目的地不存在");
  else display("无法到达目的地");
  if (retVal !=0 ) return 1;
  //处理原房间的跟随问题
  YString tempfollowsb = "";
  if( followsb != "" )
  {
        YString name; //"sb."
        YActor* sb;
        while ((name=followsb.getWord()) != "")
        {
                sb=(YActor*)oldroom->findChildActor(name);
                if (sb && sb->isTypeOf("YActor"))
                {
                  if(sb->getYouFollow() == getActorName()) //名字，跟随
                  {
                       if ((oldroom->executeCommand(sb,"go "+direction)) == 0)
                       {
                           sb->go(direction);
                       }
                       //成功跟随的时候加入
                       if  ( tempfollowsb == "" ) tempfollowsb =name;
                       else tempfollowsb =name+" "+tempfollowsb;
                   }
                }
        }
  }
  //清除人物的杀人检物品的属性
  setKillAndGet(0);
  setKillAndGe(0);
  //从新设置跟随人物
  setFollowYou(tempfollowsb);
  return 1;
}
//--------------------------------------------------------
//beg sb sth.
int YActor::beg(YString sentence)
{
  /*YString s=sentence.getWord(); //"sb."
  YMUDObject* sb=getRoom()->findChildActor(s);
  if ( getSchool() != "丐帮" )//this不用判断，门派
  {
    display ("你不是丐帮弟子。不能乞讨。");
    return 1;
  }
  if((!sb)||(!sb->isTypeOf("YActor"))) //(!s)判断为空
  {
    display("你要向谁乞讨？");
    return 1;
  }
  YString s1=sentence.getWord(); //"sth."
  YAbstractThing* sth=sb->findChildThing(s1);
  if(!sth)  //判断物品
   {
    display("他没有这件物品。");
    return 1;
   }
  YActor::executeCommandAsTarget(this,"beg "+s+" "+s1);
  #ifdef __WIN32__
  randomize();
  #else //UNIX
  srand(time(0));
  #endif //__WIN32__
  long chance = getAsLong ("叫化绝活");  //成功的机会
   if((rand() % 100)< chance)  //成功机会
   {
        sb->giveChildTo(sth,this);
        if (sb->isTypeOf("YActor") && sth->isTypeOf("YThing"))
        {
          YString msg="由于乞讨"+((YActor*)sb)->getActorName()+"把"+((YThing*)sth)->getThingName()+"送给了"+getActorName()+"。";
          getRoom()->getRoomChat()->talk(NULL, msg);
        }
        else display("乞讨时物品或人物出错请联系巫师。");
        return 1;
   }
   else
   {
       if(sb->isTypeOf("YActor"))
       {
         YString msg=((YActor*)sb)->getActorName()+"对你喊道，穷鬼一边去。";
         getRoom()->getRoomChat()->talk(NULL, msg);
       }
       else display ("乞讨时人物出错清联系巫师。");
       return 1;
   } */
   return 1;
}
//lp-----------------------------
//killget 杀拣
int YActor::killget(YString sentence)
{
    if ( kill(sentence) == 1)
    {
      setKillAndGet(1);
    }
    return 1;
}
//lp-----------------------------
//killge 杀ge
int YActor::killge(YString sentence)
{
    if ( kill(sentence) == 1)
    {
      setKillAndGe(1);
    }
    return 1;
}
//lp-----------------------------
//kill 杀
int YActor::kill(YString sentence)
{
        if (!(getRoom()->isTypeOf("YRoom")))
        {
          display ("对杀中房间出错清联系巫师。") ;
          return 2;
        }
        if (((YRoom*)getRoom())->getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
        {
          display ("这里不允许战斗。");
          return 2;
        }
        YString s=sentence.getWord();//sb.
        YAbstractActor* sb=getRoom()->findChildActor(s);
        if((!sb)||(!(sb->isTypeOf("YActor"))))  //判断人物
        {
                display("没有你要攻击的人");
                return 2;
        }
        else
        {
                if ( sb->isTypeOf("YPlayer"))
                {
                  if (((YActor*)sb)->isnewbie() == 1)
                  {
                    display ("行行好放过孩子吧。");
                    return 2;
                  }
                  else if (sb->isTypeOf("YWizard"))
                  {
                    display ("你怎么可以攻击巫师呢？");
                    return 2;
                  }
                  else if (((YActor*)this)->isnewbie() == 1)
                  {
                    display ("这么小的年纪就学人玩pk！");
                    return 2;
                  }
                 setZdpk(1); //设置主动pk 
                }
                if ( !(sb->isTypeOf("YActor")) ) return 1;
                if (sb == this )
                {
                  display ("你不会是想自杀吧!!!");
                }
                else
                {
                  YString mekill=getAllEnemyList(); //"杀死人物列表"
                  //查找人物
                  long flag = playerfindname(mekill,s);
                  if (flag == 1)
                  {
                    display ("杀！杀！杀！");
                    return 1;
                  }
                  setKill(1); //对杀
                  setFightInterval(2000); //时间的控制，战斗间隔
                  setStatus("战斗中"); //状态
                  YActor* tempsb = (YActor*) sb; //转换到Actor中的函数处理
                  tempsb->setStatus("战斗中"); //对手的状态
                  tempsb->setBattle(1); //战斗
                  YString othkill=tempsb->getAllEnemyList(); //"杀死人物列表"
                  if (!(playerfindname(othkill,getActorName()))) othkill = getActorName()+" "+othkill;
                  tempsb->setKill(1);
                  setAllEnemyList(s+" "+mekill); //"杀死人物列表"
                  tempsb->setAllEnemyList(othkill); //对手的"杀死人物列表"
                  setSameRoomEnemyList(s+" "+getSameRoomEnemyList()); //"房间内敌人列表"
                  tempsb->setSameRoomEnemyList(getActorName()+" "+tempsb->getSameRoomEnemyList()); //对手的"房间内敌人列表"
                  display("你向"+sb->getDisplayName()+"发起了攻击，他看起来想杀你。");
                  sb->display(getDisplayName()+"冲着你大叫一声，发起攻击");
                  getRoom()->getRoomChat()->talk(NULL,getActorName()+"冲着"+sb->getDisplayName()+"大叫一声，扑了上来。",this,sb);
                  //同房间的npc的协防
                  if (sb->isTypeOf("YNPC"))
                  {
                    YString allNpc = getRoom()->enumChildren("","","YNPC");
                    YString NPCName  ="";
                    YAbstractActor* tempnpc;
                    while ((NPCName = allNpc.getWord())!="")
                    {
                      tempnpc =getRoom()->findChildActor(NPCName);
                      if (tempnpc)
                      {
                        if ( ((YNPC*)tempnpc)->getUniteKill()) //联合协防
                        {
                          tempnpc->executeCommandAsTarget(this,"kill "+s);
                        }
                      }
                    }
                  }
                }
         }
         return 1;
}
//------------------------------
//lp-----------------------------------------------------------
//fight 讨教
int YActor::fight(YString sentence)
{
        if (!(getRoom()->isTypeOf("YRoom")))
        {
          display ("讨教中房间出错清联系巫师。");
          return 1;
        }
        if ( ((YRoom*)getRoom())->getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
        {
          display ("这里不允许战斗。");
          return 1;
        }
        YString sMan=sentence.getWord();//sb.
        YAbstractActor* sb=getRoom()->findChildActor(sMan);
        if(!sb)   //判断人物
        {
          display("没有你要讨教的人");
          return 1;
        }
        else
        {      
                if(!(sb->isTypeOf("YActor")))
                {
                  display("没有你要讨教的人");
                  return 1;
                }
               /* if ((((YActor*)sb)->getLevel()) > 50)  //处理巫师
                {
                  display ("你不能攻击巫师。");
                  sb -> display(getAsString("名字")+"准备向你讨教");
                  return 1;
                }  */
                if (sb == this )
                {
                        display ("你不会和自己战斗吧。");
                        return 1;
                }
                else
                {
                  YActor* tempsb = (YActor*) sb;
                  if ( tempsb->getStatus()== "晕倒中") //状态
                  {
                    setBattle (0); //战斗
                    setAdversary(""); //对手清空
                    display (sMan+"已经这样了，不要再打了吧。");
                    return 1;
                  }
                  else if ( tempsb->getStatus()== "睡眠中") //状态
                  {
                        setBattle (0); //战斗
                        setAdversary(""); //对手清空
                        display (sMan+"在睡觉，不要打扰.");
                        return 1;
                  }
                  YString sAdversaryName=getAdversary(); //对手名
                  if(sAdversaryName!="")//只能和一个人对练，对手
                  {
                    if(sAdversaryName==sMan) //如果对手名等于当前要打的人，则加油
                    {
                      display ("加油。加油！！！！！");
                      return 1;
                    }
                    else
                    {
                      display ("每次只能和一个人练习武功,所以你放弃了和"+sAdversaryName+"较量武功的打算.");
                      YAbstractActor* oldsb=getRoom()->findChildActor(sAdversaryName);
                      if ( oldsb )
                      {
                        oldsb->display (getDisplayName()+"放弃了和你较量武功的打算.");
                        halt();
                      }
                      else return 1;
                    }
                  }
                  YString myname = getActorName() ; //名字
                  YString fightname = tempsb->getAdversary(); //对手的对手
                  if ( fightname!= "" && (fightname!= myname))
                  {
                    display ("他正在和别人在战斗。");
                    return 1;
                  }
                  long fightdisplay = (rand() % 8)+1; //1-8的随机数
                  if (sb-> isTypeOf("YPlayer") )
                  {
                    //YString myname =  getAsString("名字");
                    //YString fightname = sb->getAsString("对手");
                    if ( fightname == myname )//被动fight
                    {
                      YString miaoshu = sb->getAsString ("较量描述");
                      if (miaoshu == "主动fight1") miaoshu = "被动fight1";
                      else if (miaoshu == "主动fight2") miaoshu = "被动fight2";
                      else if (miaoshu == "主动fight3") miaoshu = "被动fight3";
                      else if (miaoshu == "主动fight4") miaoshu = "被动fight4";
                      else if (miaoshu == "主动fight5") miaoshu = "被动fight5";
                      else if (miaoshu == "主动fight6") miaoshu = "被动fight6";
                      else if (miaoshu == "主动fight7") miaoshu = "被动fight7";
                      else if (miaoshu == "主动fight8") miaoshu = "被动fight8";
                      setAdversary(sMan);  //对手名字设置为当前要打的人
                      YString zhudong = g_Wugong->fight_translate(miaoshu,this,sb,YWugong::OTHER) ;
                      getRoom()->getRoomChat()->talk(NULL,zhudong,NULL, NULL);
                      display ("你同意了"+sb->getDisplayName()+"较量武功的要求.");
                      sb->display (getDisplayName()+"同意了你的要求.");
                      dofight();
                      return 1;
                    }
                    //fight 开始的描述
                    //主动fight
                    YString word = "";
                    if (fightdisplay == 1 ) word = "主动fight1" ;
                    else if (fightdisplay == 2 ) word = "主动fight2" ;
                    else if (fightdisplay == 3 ) word = "主动fight3" ;
                    else if (fightdisplay == 4 ) word = "主动fight4" ;
                    else if (fightdisplay == 5 ) word = "主动fight5" ;
                    else if (fightdisplay == 6 ) word = "主动fight6" ;
                    else if (fightdisplay == 7 ) word = "主动fight7" ;
                    else if (fightdisplay == 8 ) word = "主动fight8" ;
                    YString zhudong = g_Wugong->fight_translate(word,this,sb,YWugong::OTHER) ;
                    getRoom()->getRoomChat()->talk(NULL,zhudong,NULL, NULL);
                    setAdversary(sMan); //对手名字设置为当前要打的人
                    set("较量描述",word);
                    return 1;
                  }
                  //对NPC的处理
                  //fight 开始的描述
                  //主动fight
                  YString word = "";
                  if (fightdisplay == 1 ) word = "主动fight1" ;
                  else if (fightdisplay == 2 ) word = "主动fight2" ;
                  else if (fightdisplay == 3 ) word = "主动fight3" ;
                  else if (fightdisplay == 4 ) word = "主动fight4" ;
                  else if (fightdisplay == 5 ) word = "主动fight5" ;
                  else if (fightdisplay == 6 ) word = "主动fight6" ;
                  else if (fightdisplay == 7 ) word = "主动fight7" ;
                  else if (fightdisplay == 8 ) word = "主动fight8" ;
                  YString zhudong = g_Wugong->fight_translate(word,this,sb,YWugong::OTHER) ;
                  getRoom()->getRoomChat()->talk(NULL,zhudong,NULL, NULL);
                  if (word == "主动fight1") word = "被动fight1";
                  else if (word == "主动fight2") word = "被动fight2";
                  else if (word == "主动fight3") word = "被动fight3";
                  else if (word == "主动fight4") word = "被动fight4";
                  else if (word == "主动fight5") word = "被动fight5";
                  else if (word == "主动fight6") word = "被动fight6";
                  else if (word == "主动fight7") word = "被动fight7";
                  else if (word == "主动fight8") word = "被动fight8";
                  zhudong = g_Wugong->fight_translate(word,sb,this,YWugong::OTHER) ;
                  getRoom()->getRoomChat()->talk(NULL,zhudong,NULL, NULL);
                  setBattle(1); //战斗
                  setAdversary(sMan); //对手名字设置为当前要打的人
                  setStatus("战斗中");//设置状态
                  setFightInterval(2000); //战斗间隔
                  tempsb->setStatus("战斗中"); //时间的控制，状态
                  tempsb->setBattle(1); //战斗
                  tempsb->setAdversary(myname);
                  display("你向"+sb->getDisplayName()+"开始了讨教");
                  getRoom()->getRoomChat()->talk(NULL,myname+"向着"+sb->getDisplayName()+"开始讨教",this, sb);
                }
                return 1;
         }
}
//lp----------------------------------------
//hit 攻击
int YActor::hit(YString sentence)
{
        if (!(getRoom()->isTypeOf("YRoom")))
        {
          display ("攻击中房间出错清联系巫师。");
          return 1;
        }
        if ( ((YRoom*)getRoom())->getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
        {
          display ("这里不允许战斗。");
          return 1;
        }
        YString sMan=sentence.getWord();//sb.
        YAbstractActor* sb=getRoom()->findChildActor(sMan);
         if(!sb) //判断人物
        {
                display("没有你要讨教的人");
                return 1;
         }
         else
         {
                if(!(sb->isTypeOf("YActor")))
                {
                  display("没有你要讨教的人");
                  return 1;
                }
                /*  if ((((YActor*)sb)->getLevel()) > 50)  //处理巫师
                {
                  display ("你不能攻击巫师。");
                  sb -> display(getAsString("名字")+"准备向你讨教");
                  return 1;
                }   */
                if (sb == this )
                {
                        display ("你不会和自己战斗吧。");
                        return 1;
                }
                else
                {
                  YActor* tempsb = (YActor*) sb;
                  if ( tempsb->getStatus()== "晕倒中") //状态
                  {
                    setBattle(0); //战斗
                    setAdversary(""); //对手清空
                    display (sMan+"已经这样了，不要再打了吧。");
                    return 1;
                  }
                  else if ( tempsb->getStatus()== "睡眠中") //状态
                  {
                        setBattle(0); //战斗
                        setAdversary(""); //对手清空
                        display (sMan+"在睡觉，不要打扰.");
                        return 1;
                  }
                  if ( sb->isTypeOf("YPlayer"))
                  {
                    if (((YActor*)sb)->isnewbie())
                    {
                      display ("不会吧，这么小的孩子你还要打啊！！");
                      return 1;
                    }
                  else if (((YActor*)this)->isnewbie() == 1)
                  {
                    display ("这么小的年纪就学人玩pk！");
                    return 1;
                  }
                  }
                  setBattle(1); //战斗
                  setAdversary(sMan); //对手设为要打的人
                  setFightInterval(2000); //战斗间隔
                  setStatus("战斗中"); //状态
                  tempsb->setStatus("战斗中"); //时间的控制，对手的状态
                  tempsb->setBattle(1); //战斗
                  YString name = getActorName() ; //名字
                  tempsb->setAdversary(name); //对手的对手设为自己的名字
                  display("你向"+sb->getDisplayName()+"开始了讨教");
                  tempsb->display(getDisplayName()+"向你讨教武功。");
                  getRoom()->getRoomChat()->talk(NULL,name+"向着"+sb->getDisplayName()+"开始讨教",this, sb);
                }
                return 1;
         }
}
//----------------------------------------
//touxi 偷袭
int YActor::touxi(YString sentence)
{
        if (!(getRoom()->isTypeOf("YRoom")))
        {
          display ("偷袭中房间出错清联系巫师。");
          return 1;
        }
        if ( ((YRoom*)getRoom())->getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
        {
          display ("这里不允许战斗。");
          return 0;
        }
        YString sMan=sentence.getWord();//sb.
        YAbstractActor* sb=getRoom()->findChildActor(sMan);
        
        if(!sb)  //判断人物
        {
                display("没有你要攻击的人");
                return 1;
        }
        else
        {
                if(!(sb->isTypeOf("YActor")))
                {
                  display("没有你要讨教的人");
                  return 1;
                }
                if ( sb->isTypeOf("YPlayer"))
                {
                  if (((YActor*)sb)->isnewbie() == 1)
                  {
                    display ("行行好放过孩子吧。");
                    return 1;
                  }
                  else if (sb->isTypeOf("YWizard"))
                  {
                    display ("你怎么可以攻击巫师呢？");
                    return 1;
                  }
                  else if (((YActor*)this)->isnewbie() == 1)
                  {
                    display ("这么小的年纪就学人玩pk！");
                    return 1;
                  }
                 setZdpk(1); //设置主动pk                   
                }
                if (sb == this )
                {
                  display ("你不会是想自杀吧!!!");
                }
                else
                {
                  YString mekill=getAllEnemyList(); //"杀死人物列表"
                  //查找人物
                  long flag = playerfindname(mekill,sMan);
                  if (flag == 1)
                  {
                    display ("杀！杀！杀！");
                    return 1;
                  }
                  setKill(1); //对杀
                  setFightInterval(2000); //时间的控制，战斗间隔
                  setStatus("战斗中"); //状态
                  YActor* tempsb = (YActor*) sb;
                  tempsb->setStatus("战斗中");
                  //sb->set("战斗",1);
                  YString othkill=tempsb->getAllEnemyList(); //杀死人物列表
                  YString myname = getActorName(); //自己的名字
                  if (playerfindname(othkill,myname) != 1) //没有找到
                  {
                    othkill = myname+" "+othkill;
                    tempsb->setAllEnemyList(othkill); //对手的杀死人物列表
                  }
                  tempsb->setKill(1); //对杀
                  setAllEnemyList(sMan+" "+mekill); //杀死人物列表
                  setSameRoomEnemyList(sMan+" "+getSameRoomEnemyList()); //"房间内敌人列表"
                  tempsb->setSameRoomEnemyList(myname+" "+tempsb->getSameRoomEnemyList());
                  display("你冲着"+sb->getDisplayName()+"大叫一声冲了上去，他看起来想杀你。");
                  tempsb->display(getDisplayName()+"冲着你大叫一声，冲了上来，他看起来想杀你");
                  getRoom()->getRoomChat()->talk(NULL,myname+"冲着"+tempsb->getDisplayName()+"大叫一声，扑了上去。看起来想杀了他。",this,sb);
                }
         }
         return 1;
}
//--------------------------------------------------------------------------
//lp
//杀人的程序
int YActor::dokill(void)
{
        //每次战斗开始繁忙减1
        if (getBusy() > 0) setBusy(getBusy() - 1);

        if (!(getRoom()->isTypeOf("YRoom")))
        {
          display ("对杀房间出错清联系巫师。");
          return 0;
        }
        if ( ((YRoom*)getRoom()) -> getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
        {
          setStatus(""); //状态清空
          return 0;
        }
        if (getStatus() == "晕倒中") return 1; //昏到的处理，状态
        YString s=getSameRoomEnemyList(); //房间内敌人列表
        if (s == "" )  return 0;
        long flag = 0;
        YString name; //"sb."
        setKill(0); //对杀

        YString myname=getActorName(); //自己的名字
        setSameRoomEnemyList("");//房间内敌人列表清空
        while ((name=s.getWord() )!= "")
        {
                //set ("状态","");
                YAbstractActor* sb=getRoom()->findChildActor(name);
                if (sb)   //人物判断
                {
                        setSameRoomEnemyList(name+" "+getSameRoomEnemyList()) ; //房间内敌人列表
                        if ( !(sb->isTypeOf("YActor")) ) return 1;  //类别判断
                        zhandou(name);
                        ((YActor*)sb)->zhandou(myname);
                        YActor* tempsb = (YActor*) sb;
                        tempsb->setKill(1); //对杀
                        // tempsb->setStatus("战斗中"); //状态
                        flag = 1 ;
                        if (tempsb->getBody() <= 0)  //他人的死亡 ，气血 <= 0
                        {
                            tempsb->setKillerName(myname);
                            if (tempsb->dead () != 0)
                            {
                            }
                        }
                        if (getBody() <=0 )  //自己的死亡，气血
                        {
                            setKillerName(name); //凶手是当前这个人
                            if ( dead() != 0 )
                            {
                              return 1;
                            }
                        }
                }
        }
        if (flag == 1)
        {
          setKill(1); //对杀
          // setStatus("战斗中"); //状态
        }
        return 1;
}
//--------------------------------------------------------------------------
//lp
//两人的对练程序
int YActor::dofight(void)
{
  if (!(getRoom()->isTypeOf("YRoom")))
  {
    display ("对练房间出错清联系巫师。");
    return 0;
  }
  if ( ((YRoom*)getRoom())->getForbidFight() == 1) //处理房间的战斗，禁止战斗 == 1
  {
    setStatus(""); //状态清空
    return 1;
  }
  if (getStatus() == "晕倒中") return 1; //昏到的处理，状态
  YString s=getAdversary(); //对手的名字
  //程序内部进行调用时使用  YActor* sb=(YActor*)(getRoom()->findChildActor(s));
  if ( getRoom()->findChildActor(s) == NULL )
  {
    setStatus(""); //状态清空
    setAdversary(""); //对手
    //display ("fight人名出错");
    return 0;
  }
  if ((getRoom()->findChildActor(s))->isTypeOf("YActor")) ;
  else return 0;
  YActor* sb=(YActor*)getRoom()->findChildActor(s); //房间的人物判断为下一句引用做判断
  if(!sb)      //判断人物指针
  {
        setStatus(""); //状态清空
        setBattle(0); //战斗
        return 0;
  }
  else
  {
        if (sb->getStatus()== "晕倒中" )
        {
          display ("他已经昏倒了。");
          setBattle(0); //战斗
          setAdversary(""); //对手
          setStatus(""); //状态清空
          return 1 ;
        }
        YString myname = getActorName() ; //名字
        if ((sb->getAdversary() != myname) )
        {
         /* set ("战斗",0);
          set ("对手","");
          set ("状态",""); */
          //YString testname = sb->getAdversary();
          setStatus(""); //状态清空
          return 1 ;
        }
        long heal=getBody(); //气血
        long maxheal=getMaxBody(); //最大气血
        long flee = getWimpy(); //逃跑系数
        if (flee == 0) flee = 50 ;
        zhandou(s);
        sb->zhandou(myname);
        //sb->setStatus("战斗中"); //状态
        //setStatus("战斗中");
        if ( heal < ((maxheal * flee) / 100 ) )
        {
           halt();
           heal=getBody(); //气血
           if (heal < 0 )
           {
             faint();
             if (sb-> getBody() > 0) sb->setStatus(""); //对手状态清空
           }
        }
        long otherfell = sb->getWimpy(); //对手逃跑系数
        if (otherfell == 0 ) otherfell = 50 ;
        if ( sb->getBody()< ((sb->getMaxBody()*otherfell)/100) )   //昏迷的处理
        {
          sb->halt();
          if (sb->isTypeOf("YNPC"))  //NPC的失败后自杀的处理
          {
              long randsize = rand() % 100;
              if ( randsize < 1 )
              {
                getRoom()->getRoomChat()->talk(NULL,getAsString("自杀语言"),NULL,NULL);
              }
          }
          if (sb-> getBody()<0)
          {
               sb->faint ();
               if (getBody()>0) setStatus(""); //状态清空
          }
        }
  // 在程序内部进行调用        sb->dofight();
  }
  return 1;
}
//-------------------------------------------------------
//lp
//perform 绝招
int YActor::perform(YString sentence) //稍后移出显示内容
{
   return 1;
}
//lp
//zhandou 战斗
int YActor::zhandou(YString sentence) //稍后移出显示内容
{
        setFreeTime(0); //空闲时间
        //判断人物是否在繁忙状态
        long isbusy = getBusy(); //是否繁忙
        if (isbusy > 0)//繁忙的话返回
        {
          //setBusy(isbusy-1); //繁忙时间 - 1
          return 1;
        }
        else
        {
          setBusy(1);//每次战斗的时候只能攻击其中一个人
        }
        YString name=sentence.getWord(); //"sb."
        YAbstractActor* sb=getRoom()->findChildActor(name);
        if (!sb) //判断人物的指针
        {
                display ("没有这个人物");
                setStatus("");
                return 1;
        }
        else
        {
                if ( !(sb->isTypeOf("YActor")) ) return 1 ; //判断类别
                //新加入的图形显示
                YString icon1="3";
                YString icon2="8";
                if ( getSexString() == "女")
                {
                  icon1 = selePhoto("7");
                  icon2 = selePhoto("9");
                }
                else
                {
                  if (getwichpho() == 1)
                  {
                    icon1 = selePhoto("7");
                    icon2 = selePhoto("9");
                  }
                  else
                  {
                    icon1 = selePhoto("3");
                    icon2 = selePhoto("8");
                  }
                }
                YString s="hit(\""+getActorName()+"\",\""+name+"\",\""+icon1+"\",\""+icon2+"\")";
                getRoom()->getRoomChat()->talk(NULL,s,NULL,NULL,JAVASCRIPT_MSG);
                //图显结束
                setStatus("战斗中");
                YActor* tempsb = (YActor*) sb;
                tempsb->setStatus("战斗中");
                long mebody=getBody(); //气血
                long other=tempsb->getBody();
                long maxheal=getMaxBody(); //最大气血
                long maxother=tempsb->getMaxBody();
                long mearm = getBeginArm();//getAsLong ("后天臂力");
                long otherarm = tempsb-> getBeginArm();//getAsLong ("后天臂力");
                //简单没臂力的npc处理
                if ( otherarm == 0) otherarm = 30 ;
                if ( mearm == 0) mearm = 30 ;
                //处理简单的npc的气血受攻击
                long NpcBody =g_Settings->getsitNpcBody();//getAsLong("NPC气血");
                if (( maxother == 0) && (other == 0)&& (sb->isTypeOf("YNPC")))
                {
                        tempsb->setBody(NpcBody);
                        tempsb->setMaxBody(NpcBody);
                        other= NpcBody;
                }
                //先行对杀时的处理 气血
                if (( maxheal == 0)&& (mebody == 0) && (isTypeOf("YNPC")))
                {
                        setBody(NpcBody);
                        setMaxBody(NpcBody);
                        mebody= NpcBody;
                }
                //使用的招数描述
                YString wuqi=getWeaponType(); //武器类型
                YString wugong ="";
                if (wuqi == "" )  wuqi = "空手";
                wugong=wuqi+"_攻击武功";
                YString usewugong=getAsString(wugong);
                long uselevel ;
                if ( usewugong == "") //使用的默认武功
                {
                  if (wuqi == "空手" )  usewugong="基本拳法";
                  else usewugong = "基本"+wuqi+"法";
                  if (getSexString() == "动物") //性别
                  {
                    wuqi = "咬";
                    usewugong = "基本撕咬";
                  }
                }
                if ( isTypeOf("YPlayer") ) //是玩家的时候取玩家的基本武功
                {
                     uselevel = ((YPlayer*)this)->getSkillLevel(usewugong);
                }
                else uselevel=getAsLong(usewugong);
                if ((isTypeOf("YNPC"))&& uselevel== 0 )
                {
                  uselevel = g_Settings->getsitNpcLevel();//getAsLong("NPC武功级别")  ;
                  set (usewugong,uselevel);
                 /* hit = hit+poweruphit+( uselevel*g_Settings->getAsLong("攻击力比例"))/2
                         + getAsLong("经验")/g_Settings->getAsLong("防御经验转换");*/
                }
                // if (uselevel== 0) uselevel = 30;//NPC的武功是默认的30级                //
                //
                //
                //处理简单的npc没有武功级别的问题
                float hit=getInhereAttack(); //固定攻击力
                //powerup攻击力
                long poweruphit = getPowerUpAttack(); //powerup攻击力
                // npc 的攻击武功级别
                if (uselevel == 0) uselevel = 1;
                //内力的因素
                long body=getInternalForce(); //内力
                long add=getForceAttack(); //加力，内力攻击力
                if (body < add) add = 0 ;
                //招数的描述
                YString zhao_shi=g_Wugong->randomAttack(usewugong, uselevel);
                YString zhaoshu_miaoshum=g_Wugong->zhaoshu_miaoshu(zhao_shi, "你", tempsb->getActorName()); //自己的描述
                YString zhaoshu_miaoshus=g_Wugong->zhaoshu_miaoshu(zhao_shi, getActorName(), "你"); //对方的描述
                YString zhaoshu_miaoshuo=g_Wugong->zhaoshu_miaoshu(zhao_shi, getActorName(), tempsb->getActorName()); //其余人的描述
                YString zhaoshu_miaoshuadd ;
                YString zhaoshu_miaoshuaddm ;
                YString zhaoshu_miaoshuadds ;
                YString zhaoshu_miaoshuaddo ;
                YString wuqimiaoshu="";
                //攻击力的计算
                long armhit=getWeaponAttack(); //武器攻击力
                long odeff=tempsb->getInhereDefense(); //固定防御力
                long othhit = tempsb->getInhereAttack(); //固定攻击力
                long oadddeff=tempsb->getAppendDefense(); //附加防御力
                long powerupdeff = tempsb->getPowerUpDefense(); //powerup防御力
                if (hit == 0) hit = g_Settings->getsitNpcHit();//getAsLong("NPC默认攻击"); //npc的固定攻击力的默认
                if (odeff == 0) odeff = g_Settings->getsitNpcDef();//getAsLong("NPC默认防御"); //npc的固定防御力的默认
                if ((isTypeOf("YNPC"))) // npc的攻击力级别
                {
                  if (getWeaponName() != "" && (armhit == 0)) armhit = 30;  //武器
                }
                if ((sb->isTypeOf("YNPC"))) // npc的防御力级别
                {
                  if (tempsb->getClothName() != "" && (oadddeff ==0))  oadddeff = 30; //衣服
                  /*odeff = odeff+powerupdeff+(uselevel*g_Settings->getAsLong("防御力比例"))/2 ; */
                }
                /* 原先的程序，要修改一定的变化，
                hit = hit + armhit + add + poweruphit + g_Wugong->zhaoshu_gongjili(zhao_shi);  // 招式的附加 经验的处理
                odeff = odeff + powerupdeff + oadddeff ;  //防御力加乘
                //攻击力加乘
                if (odeff <=0 ) odeff = 1;
                if ( hit <= 0 ) hit = 1;
                if (othhit <= 0) othhit = 1;
                //公式变为平方的关系
                long turehit = (hit/(odeff+odeff+othhit))*(hit/(odeff+odeff+othhit))* maxother;
                */
                long maxneili = getMaxInternalForce(); //最大内力
                  //处理NPC没有写内力的情况
                if  (maxneili == 0 ) maxneili = 2*maxheal;
                if ((armhit ==  0) && (getWeaponName()==""))
                {
                  armhit = maxneili /50;//没有武器所以是空手（少公式）
                  if ( armhit >60 ) armhit = 60;
                }
                //处理防御的衣服的附加防御力
                long tempdeff ;
                if (oadddeff <=0 ) oadddeff = 1;
                tempdeff = rand() % (2*oadddeff);
                if (tempdeff < oadddeff ) oadddeff =  oadddeff /2;
                else  oadddeff = 0;
                double turehit = g_Wugong->zhaoshu_gongjili(zhao_shi)  ;
                //加入的新的武功相克制程序部分
                YString sbusewuqi = tempsb->getWeaponType(); //武器类型
                long  forbear = g_Settings->getAsLong("武功相克比例");
                if (forbear == 0 ) forbear =20;
                if (wuqi == "剑" || wuqi == "刀")
                {
                   if (sbusewuqi == "棍" || sbusewuqi == "枪")
                   {
                     turehit = turehit - turehit * forbear /100 ;
                   }
                   else if (sbusewuqi == "" || sbusewuqi == "空手")
                   {
                     turehit = turehit + turehit * forbear /100 ;
                   }
                }
                else if (wuqi == "棍" || wuqi == "枪")
                {
                   if (sbusewuqi == "剑" || sbusewuqi == "刀")
                   {
                     turehit = turehit + turehit * forbear /100 ;
                   }
                   else if (sbusewuqi == "" || sbusewuqi == "空手")
                   {
                     turehit = turehit - turehit * forbear /100 ;
                   }
                }
                else  //空手及其他
                {
                   if (sbusewuqi == "棍" || sbusewuqi == "枪")
                   {
                     turehit = turehit + turehit * forbear /100 ;
                   }
                   else if (sbusewuqi == "剑" || sbusewuqi == "刀")
                   {
                     turehit = turehit - turehit * forbear /100 ;
                   }
                }
                //*/                        
                turehit = mearm + armhit  + turehit + add   ;
                turehit = (long)(((float)(((float)hit)/(float)(odeff))) * turehit );
                turehit = turehit - (long)(((float)(((float)hit)/(float)(odeff))) * oadddeff );
                if (turehit > (5*maxother)) turehit = 2*maxother ;//大于5倍在两倍气血内随机
                else if (turehit > 2*(maxother) )  turehit = 0.8 * maxother ;//5倍以内最大80%气血
                else if (turehit > 0.6*(maxother) )  turehit = 0.6* maxother ;//2倍以内最大60%气血
                if (turehit <= 0)turehit =1;
                hit = turehit;
                hit = rand() % (long)hit ;
                if ( hit < 5 ) hit=5;
                else ;
                //处理闪躲的变化
                //闪躲=2*身法/3 + skill附加值
                long shenfa = tempsb->getLastDodge() + tempsb->getAddDodge(); //后天身法
                long shenfa1 = getLastDodge() + getAddDodge();
                long sf = shenfa - shenfa1;
                if (sf < 20) sf = 20;
                YString useqinggong = tempsb->getDodgeUsing(); //轻功_使用，正在使用的轻功名称
                if (useqinggong == "")  useqinggong = "基本轻功" ;
                long dodge = g_Wugong->wugong_add_dodge( useqinggong ); //轻功的附加闪躲机会
               long hap=((sf*2)/3);//+((othexp/expuse)*dodge);
                long randsize = rand() % 100;
                if( randsize > hap)  //成功闪躲机会
                {
                        setInternalForce(body - add); //内力
                        if ((rand() % 100)< getLastLearn() + getAddLearn()) //任务在进行战斗经验变化时地几率（任务悟性），后天悟性
                        {
                                if(isTypeOf("YPlayer"))
                                {
                                  YString basic ="" ;
                                  if ((wuqi != "空手" ) && (wuqi != ""))
                                  {
                                    basic = "基本"+wuqi+"法";
                                  }
                                  else
                                  {
                                    basic = g_Wugong->wugong_leixing(getAsString("空手_攻击武功"));//(getHandAttackSkill()); //空手攻击武功
                                    if (basic != "") basic = "基本"+ basic ;
                                    else basic = "基本拳法";
                                  }
                                  long useup = g_Settings->getsitFightUp();//getAsLong("战斗成长");
                                  long basiclevel = ((YPlayer*)this)->getSkillLevel(basic);
                                  //
                                  //
                                  //
                                  YString playerwugong = getAllSkillsList(); //所会技能，所有技能列表
                                  if ( playerwugong.size() == 0 ) //判断是否有这种基本武功
                                  {
                                    setAllSkillsList(basic);
                                  }
                                  else
                                  {
                                    if (playerfindname(playerwugong,basic)== 0)
                                    {
                                      playerwugong = playerwugong +" "+ basic;
                                      setAllSkillsList(playerwugong);
                                     }
                                  }
                                  YString basicexp = basic + "_经验";
                                  set ( basicexp ,getAsLong(basicexp)+useup );
                                  display ("你的"+basic+"有所增长");
     				  if (getAsLong (basicexp) >((basiclevel+1) * (basiclevel+1) * 10))
    				  {
   				     ((YPlayer*)this)->playerlevelup(basic);
  				     set(basicexp,0);
       				     getRoom()->getRoomChat()->talk(NULL,"<font color=red>"+getActorName()+"的"+basic+"升级了！！！</font>",this, sb);
   				  }
                                  setExperience(getExperience()+useup); //经验增加
                                } // if(isTypeOf("YPlayer"))
                        }
                        if (wuqi == "剑" || wuqi == "枪" || wuqi == "暗器")
                        {
                          if (hit < 10 ) wuqimiaoshu = g_Settings->getciDisplay10();//"觉得只是轻轻地被刺破皮肉。";
                          else if (hit < 20 ) wuqimiaoshu = g_Settings->getciDisplay20();//"被刺出一个创口。";
                          else if (hit < 40 ) wuqimiaoshu = getWeaponName()+g_Settings->getciDisplay40();//"「噗」地一声刺入了寸许.";
                          else if (hit < 80 ) wuqimiaoshu = getWeaponName()+g_Settings->getciDisplay80();//"「噗」地一声刺进去！";
                          else if (hit < 120 ) wuqimiaoshu = getWeaponName()+g_Settings->getciDisplay120();//"「噗嗤」地一声刺出一个血肉□糊的血窟窿！";
                          else  wuqimiaoshu = g_Settings->getciDisplay160u()//"一声惨嚎，"
                                                             +getWeaponName()+g_Settings->getciDisplay160d();//"已对穿而出，鲜血溅得满地！！";
                        }
                        if (wuqi == "空手" || wuqi == "")
                        {
                          if (hit < 10 ) wuqimiaoshu =g_Settings->getkongDisplay10();// "觉得只是轻轻地碰到，比拍苍蝇稍微重了点。";
                          else if (hit < 20 ) wuqimiaoshu = g_Settings->getkongDisplay20();//"没有躲开，造成一处瘀青。";
                          else if (hit < 40 ) wuqimiaoshu = g_Settings->getkongDisplay40();//"身上登时肿了一块老高！";
                          else if (hit < 80 ) wuqimiaoshu =g_Settings->getkongDisplay80();// "闷哼了一声显然吃了不小的亏！";
                          else if (hit < 120 ) wuqimiaoshu =g_Settings->getkongDisplay120();// "只听见「砰」地一声，退了两步！";
                          else if (hit < 160 ) wuqimiaoshu = g_Settings->getkongDisplay160();//"这一下「砰」地一声,连退了好几步，差一点摔倒！";
                          else  wuqimiaoshu =g_Settings->getkongDisplay200();// "被重重地击中，「哇」地一声吐出一口鲜血。";
                        }
                        if (wuqi == "刀")
                        {
                          if (hit < 10 ) wuqimiaoshu = g_Settings->getkanDisplay10();//"觉得只是轻轻地划破了皮肉。";
                          else if (hit < 20 ) wuqimiaoshu = g_Settings->getkanDisplay20();//"感到划出一道细长的血痕。";
                          else if (hit < 40 ) wuqimiaoshu ="看见"+getWeaponName()+ g_Settings->getkanDisplay40();//"「嗤」地一声划出一道伤口！";
                          else if (hit < 80 ) wuqimiaoshu ="觉得"+getWeaponName()+g_Settings->getkanDisplay80();// "「嗤」地一声划出一道血淋淋的伤口！";
                          else if (hit < 120 ) wuqimiaoshu ="「嗤」地一声被"+getWeaponName()+g_Settings->getkanDisplay120();// "划出一道又长又深的伤口，鲜血四溅。";
                          else  wuqimiaoshu = g_Settings->getkanDisplay160()//"一声惨嚎，"
                                               +getWeaponName()+ g_Settings->getkanDisplay160();//"划出一道深及见骨的可怕伤口！！";
                        }
                        if (wuqi == "咬")
                        {
                          if (hit < 10 ) wuqimiaoshu =g_Settings->getyaoDisplay10();//getAsString ("咬伤10");// "只是轻轻的留下了咬痕。";
                          else if (hit < 20 ) wuqimiaoshu = g_Settings->getyaoDisplay20();//getAsString ("咬伤20");//"感到被咬了一口，留下了一道血印。";
                          else if (hit < 40 ) wuqimiaoshu = g_Settings->getyaoDisplay40();//getAsString ("咬伤40");//"被重重的咬住，出现了几个小洞。";
                          else if (hit < 80 ) wuqimiaoshu = g_Settings->getyaoDisplay80();//getAsString ("咬伤80");//"只听「嗤」地一声,一块肉已经被咬了下来";
                          else wuqimiaoshu = g_Settings->getyaoDisplay120();//getAsString ("咬伤120");//"一声惨嚎，被咬中的地方开始「泊泊」的流起了鲜血";
                        }
                        if (wuqi == "毒")
                        {
                          if (hit < 10 ) wuqimiaoshu =g_Settings->getduDisplay10();//getAsString ("毒伤10");
                          else if (hit < 20 ) wuqimiaoshu = g_Settings->getduDisplay20();//getAsString ("毒伤20");
                          else if (hit < 40 ) wuqimiaoshu = g_Settings->getduDisplay40();//getAsString ("毒伤40");
                          else if (hit < 80 ) wuqimiaoshu = g_Settings->getduDisplay80();//getAsString ("毒伤80");
                          else wuqimiaoshu = g_Settings->getduDisplay120();//getAsString ("毒伤120");
                        }
                        if (wuqi == "空手") wuqi = "拳";
                        if ( hit < 5 ) zhaoshu_miaoshuadd = g_Settings->getshanghai5();//getAsString ("伤害描述5");//"结果只是勉强造成一处轻微"+wuqi+"伤。";
                        else if (hit <10 ) zhaoshu_miaoshuadd =g_Settings->getshanghai10();//getAsString ("伤害描述10");// "结果造成轻微的"+wuqi+"伤。";
                        else if (hit <20 ) zhaoshu_miaoshuadd = g_Settings->getshanghai20();//getAsString ("伤害描述20");//"结果造成一处"+wuqi+"伤。";
                        else if (hit <30 ) zhaoshu_miaoshuadd = g_Settings->getshanghai30();//getAsString ("伤害描述30");//"结果造成一处严重"+wuqi+"伤。";
                        else if (hit <50 ) zhaoshu_miaoshuadd = g_Settings->getshanghai50();//getAsString ("伤害描述50");//"结果造成颇为严重的"+wuqi+"伤。";
                        else if (hit <80 ) zhaoshu_miaoshuadd = g_Settings->getshanghai80();//getAsString ("伤害描述80");//"结果造成相当严重的"+wuqi+"伤。";
                        else if (hit <100 ) zhaoshu_miaoshuadd =g_Settings->getshanghai100();//getAsString ("伤害描述100");// "结果造成十分严重的"+wuqi+"伤。";
                        else if (hit <160 ) zhaoshu_miaoshuadd = g_Settings->getshanghai160();//getAsString ("伤害描述160");//"结果造成极其严重的"+wuqi+"伤。";
                        else zhaoshu_miaoshuadd =g_Settings->getshanghai200();//getAsString ("伤害描述200");// "结果造成非常可怕的严重"+wuqi+"伤。";
                        zhaoshu_miaoshuaddm  = zhaoshu_miaoshuadd +wuqi+"伤";
                        zhaoshu_miaoshuadds  = zhaoshu_miaoshuadd +wuqi+"伤";
                        zhaoshu_miaoshuaddo  = zhaoshu_miaoshuadd +wuqi+"伤";
                }
                else
                {
                        //zhaoshu_miaoshuadd = "微微一笑闪开了攻击。";
                        //轻功招数的描述
                        YString qinggong_zhao_shi=g_Wugong->randomAttack(useqinggong, sb->getAsLong(useqinggong));
                        zhaoshu_miaoshuaddm=g_Wugong->zhaoshu_miaoshu(qinggong_zhao_shi, tempsb->getActorName(),"你" ); //自己的描述
                        zhaoshu_miaoshuadds=g_Wugong->zhaoshu_miaoshu(qinggong_zhao_shi, "你",getActorName() ); //对方的描述
                        zhaoshu_miaoshuaddo=g_Wugong->zhaoshu_miaoshu(qinggong_zhao_shi,  tempsb->getActorName(),getActorName()); //其余人的描述
                }
                //在个人的屏幕上显示的东西
                if (wuqimiaoshu != "")
                {
                  zhaoshu_miaoshum = zhaoshu_miaoshum +tempsb->getActorName()+wuqimiaoshu+zhaoshu_miaoshuaddm ;
                  zhaoshu_miaoshus = zhaoshu_miaoshus +"你"+wuqimiaoshu+zhaoshu_miaoshuadds ;
                  zhaoshu_miaoshuo = zhaoshu_miaoshuo +tempsb->getActorName()+wuqimiaoshu+zhaoshu_miaoshuaddo ;
                }
                else
                {
                  zhaoshu_miaoshum = zhaoshu_miaoshum +zhaoshu_miaoshuaddm ;
                  zhaoshu_miaoshus = zhaoshu_miaoshus +zhaoshu_miaoshuadds ;
                  zhaoshu_miaoshuo = zhaoshu_miaoshuo +zhaoshu_miaoshuaddo ;
                }
                display(zhaoshu_miaoshum);
                if((sb!=NULL)&&(sb!=this)) sb->display(zhaoshu_miaoshus);
                getRoom()->getRoomChat()->talk(NULL, zhaoshu_miaoshuo,this, sb);
                //受攻击后人物的身体状态
                other = other-hit  ;//  剩余的气血
                if ( randsize > hap && hit > 0)
                {
                        YString sex = tempsb->getSexString(); //性别
                        if (sex=="女") sex="她";
                        else if (sex == "动物") sex="它";
                        else sex="他";
                        if (other == 0 ) other = -1;
                        float otherlook = (1.0*maxother)/other ;
                        if(  other <= 0)
                        {
                                display ("<font color=00ee00>"+sex+"受伤过重，已经有如风中残烛，随时都可能断气。</font>");
                                sb->display ("<font color=ee0000>你受伤过重，已经有如风中残烛，随时都可能断气。</font>");
                        }
                        else if ( otherlook > 20 )
                        {
                                display ("<font color=00dd00>"+sex+"受伤过重，已经奄奄一息，命在旦夕了。</font>");
                                sb->display ("<font color=dd0000>你受伤过重，已经奄奄一息，命在旦夕了。</font>");
                        }
                        else if ( otherlook > 10)
                        {
                                 display ("<font color=00aa00>"+sex+"伤重之下已经难以支撑，眼看就要倒在地上。</font>");
                                 sb->display ("<font color=aa0000>你伤重之下已经难以支撑，眼看就要倒在地上。</font>");
                        }
                        else if ( otherlook > 5 )
                        {
                                 display ("<font color=008800>"+sex+"已经伤痕累累，正在勉力支撑著不倒下去。</font>");
                                 sb->display ("<font color=880000>你已经伤痕累累，正在勉力支撑著不倒下去。</font>");
                        }
                        else if(  otherlook > 3 )
                        {
                                display ("<font color=005500>"+sex+"气息粗重，动作开始散乱，看来所受的伤著实不轻。</font>");
                                sb->display ("<font color=550000>你气息粗重，动作开始散乱，看来所受的伤著实不轻。</font>");
                        }
                        else if(  otherlook > 2)
                        {
                                display ("<font color=005500>"+sex+"受伤不轻，看起来状况并不太好。</font>");
                                sb->display ("<font color=550000>你受伤不轻，看起来状况并不太好。</font>");
                        }
                        else if(  otherlook > 1.75)
                        {
                                display ("<font color=005500>"+sex+"受伤不轻，但还可以支持。</font>");
                                sb->display ("<font color=550000>你受伤不轻，但还可以支持。</font>");
                        }
                        else if( otherlook  > 1.5)
                        {
                                display ("<font color=005500>"+sex+"受了几处伤，不过似乎并不碍事。</font>");
                                sb->display ("<font color=550000>你受了几处伤，不过似乎并不碍事。</font>");
                        }
                        else if( otherlook  > 1.3)
                        {
                                display ("<font color=005500>"+sex+"受了点轻伤但没有关系</font>");
                                sb->display ("<font color=550000>你受了点轻伤但没有关系</font>");
                        }
                        else if(  otherlook  > 1.2)
                        {
                                display ("<font color=005500>"+sex+"看起来可能受了点轻伤。</font>");
                                sb->display ("<font color=550000>你看起来可能受了点轻伤。</font>");
                        }
                        else if(  otherlook > 1.1)
                        {
                                display ("<font color=005500>"+sex+"看起来可能受了点轻伤。</font>");
                                sb->display ("<font color=550000>你看起来可能受了点轻伤。</font>");
                        }
                        else if(  maxother > other )
                        {
                                display ("<font color=005500>"+sex+"似乎受了点轻伤，不过光从外表看不大出来。</font>");
                                sb->display ("<font color=550000>你似乎受了点轻伤，不过光从外表看不大出来。</font>");
                        }
                        else if(  maxother == other )
                        {
                                display ("<font color=005500>"+sex+"看起来气血充盈，并没有受伤。</font>");
                                sb->display ("<font color=550000>你看起来气血充盈，并没有受伤。</font>");
                        }
                        tempsb->setBody(other); //人物的死亡，气血
                }
        }
        return 1;
}
//-----------------------------------------------------------------
//lp
//halt 停止
int YActor::halt(void)
{
        YString s=getAdversary(); //对手
        YAbstractActor* sb=getRoom()->findChildActor(s);
        if (getStatus() == "") //没有做任何事情的时候，状态
        {
          display("你现在不忙。");
          return 1;
        }
        //处理打坐和吐纳
        if (this->isTypeOf("YPlayer"))
        {
          if (((YPlayer*)this)->getStatus() == "吐纳")
          {
            display ("你站了起来，停止了吐纳。");
            setStatus(""); //状态清空
            ((YPlayer*)this)->setTunaTime(0);//set ("吐纳时间",0);
            showPhoto("0","4");
            return 1;
          }
          else if (((YPlayer*)this)->getStatus() == "打坐")
          {
            display("你站了起来，停止了打坐。");
            setStatus(""); //状态清空
            ((YPlayer*)this)->setDazuoTime(0);//set ("打坐时间",0);
            showPhoto("0","4");
            return 1;
          }
          else if (((YPlayer*)this)->getStatus() == "坐")
          {
            display ("你从地上站了起来。");
            showPhoto("0","4");
            setStatus(""); //状态清空
            return 1;
          }
        }
        //处理看是不是在对杀状态
        YString killname=getAllEnemyList(); //杀死人物列表
        YString name; //"sb."
        while ((name=killname.getWord()) != "")
        {
                YAbstractActor* sbkill=getRoom()->findChildActor(name);
                if (sbkill)//判断对杀人物的使用
                {
                  display("你正在和"+name+"对杀,无法停止。");
                  return 1;
                }
        }
        setStatus(""); //状态清空
        setAdversary(""); //对手清空
        setBusy(0); //繁忙清0
        YString miaoshu ;
        long randsize = rand() % 101;
        if (randsize < 10) miaoshu = g_Settings->gethaltDisplay1();//getAsString ("停手描述1");//"哈哈大笑，说道：承让了！" ;
        else if (randsize <20 ) miaoshu =g_Settings->gethaltDisplay2();//getAsString ("停手描述2");//"双手一拱，笑著说道：承让！";
        else if (randsize <30 ) miaoshu =g_Settings->gethaltDisplay3();//getAsString ("停手描述3");//"胜了这招，向后跃开三尺，笑道：承让！";
        else if (randsize <40 ) miaoshu =g_Settings->gethaltDisplay4();//getAsString ("停手描述4");//"双手一拱，笑著说道：知道我的利害了吧！";
        else if (randsize <50 ) miaoshu =g_Settings->gethaltDisplay5();//getAsString ("停手描述5");//"向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！";
        else if (randsize <60 ) miaoshu =g_Settings->gethaltDisplay6();//getAsString ("停手描述6");//"向后一纵，恨恨地说道：君子报仇，十年不晚！";
        else if (randsize <70 ) miaoshu =g_Settings->gethaltDisplay7();//getAsString ("停手描述7");//"脸色一寒，说道：算了算了，就当是我让你吧！";
        else if (randsize <80 ) miaoshu =g_Settings->gethaltDisplay8();//getAsString ("停手描述8");//"纵声而笑，叫道：“你运气好！你运气好！”一面身子向后跳开。";
        else if (randsize <90 ) miaoshu =g_Settings->gethaltDisplay9();//getAsString ("停手描述9");//"脸色微变，说道：佩服，佩服！";
        else if (randsize <100 ) miaoshu =g_Settings->gethaltDisplay10();//getAsString ("停手描述10");//"向后退了几步，说道：这场比试算我输了，佩服，佩服！";
        else if (randsize == 100 )miaoshu = g_Settings->gethaltDisplay11();//getAsString ("停手描述11");//"向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！";
        if (sb == NULL) //使用前的引用
        {
          if (randsize < 40)
          {
            display("他"+miaoshu);
          }
          else display ("你"+ miaoshu);
        }
        else
        {
          if (!(sb->isTypeOf("YActor")))
          {
             display ("halt出错");
             return 1;
          }
          YActor* tempsb = (YActor*) sb;
          tempsb->setStatus(""); //对手的状态清空
          tempsb->setAdversary(""); //对手的对手清空
          if (randsize < 40)
          {
            display(tempsb->getActorName()+miaoshu);
            tempsb->display("你"+ miaoshu);
            return 1;
          }
          tempsb->display(getActorName()+miaoshu);
          display("你"+ miaoshu);
        }
        return 1;
}
//---------------------------------------------------------
//删除人物中的对杀人物
int YActor::delname()
{
  YString s=getAllEnemyList(); //"sb."，"杀死人物列表"
  YString name; //"sb."
  while ((name=s.getWord()) != "")
  {
        YAbstractActor* killer=getRoom()->findChildActor(name);
        if (killer) //指针使用前的判断
        {
                if (!(killer->isTypeOf("YActor")))
                {
                  display ("delname()1出错");
                  return 1;
                }
                YActor* tempkiller = (YActor*) killer;
                YString sbkill=tempkiller->getAllEnemyList(); //别人杀人列表的人名
                YString mekill=getAllEnemyList();  //"sb."
                YString Tempmekill = mekill;
                YString Tempsbkill = sbkill;
                mekill ="";sbkill = "";
                //自己的
                YString tempkill="";
                while ((tempkill=Tempmekill.getWord()) != "")
                {
                    if ( tempkill == tempkiller->getActorName())
                    {
                      tempkill = "";
                      continue;
                    }
                    //不是的话从新写入
                    mekill = tempkill + " " + mekill ;
                }
                //他人的
                tempkill = "";
                while ((tempkill=Tempsbkill.getWord()) != "")
                {
                    if ( tempkill == getActorName())
                    {
                      tempkill = "";
                      continue;
                    }
                    //不是的话从新写入
                    sbkill = tempkill + " " + sbkill;
                }
                tempkiller->setAllEnemyList(sbkill); //对手的杀死人物列表
                setAllEnemyList(mekill); //杀死人物列表
        }
  }
  //处理人物被杀死时（上次当机未清除的人物）
  YString killme = getKillerName(); //杀死自己
  YAbstractActor* sbkillme=getRoom()->findChildActor(killme);
  if (sbkillme)
  {
        if (!(sbkillme->isTypeOf("YActor")))
        {
          display ("delname2出错");
          return 1;
        }
        YActor* tempsbkillme = (YActor*)sbkillme ;
        YString sbkillname=tempsbkillme->getAllEnemyList(); //别人杀人列表的人名
        YString mekillname=getAllEnemyList();  //"sb."
        YString Tempmekillname = mekillname;
        YString Tempsbkillname = sbkillname;
        mekillname ="";sbkillname = "";
        //自己的
        YString tempkillname="";
        while ((tempkillname = Tempmekillname.getWord()) != "")
        {
                if ( tempkillname == killme)
                {
                      tempkillname = "";
                      continue;
                }
                //不是的话从新写入
                mekillname = tempkillname + " " + mekillname ;
        }
        //他人的
        tempkillname = "";
        while ((tempkillname = Tempsbkillname.getWord()) != "")
        {
                    if ( tempkillname == getActorName())
                    {
                      tempkillname = "";
                      continue;
                    }
                    //不是的话从新写入
                    sbkillname = tempkillname + " " + sbkillname;
        }
        tempsbkillme->setAllEnemyList(sbkillname);
        setAllEnemyList(mekillname); //"杀死人物列表",
  }
  return 1;
}
//---------------------------------------------------------
int YActor::dead()
{
  if ( getNotDead() == 1 )//不死处理
  {
    setBody(getMaxBody()); //气血恢复
    setEnergy(getMaxEnergy()); //精力恢复
    return 0;
  }
  showPhoto("1","5");
  YString killer=getKillerName(); //杀死自己
  setDeath(1); //死亡=1
  //删除人名
  delname();
  //丢掉人物
  dropplayer();
  //player 得死亡损失
  if (isTypeOf("YPlayer"))
  {
    //经验减少5%
    //setExperience((getExperience()*19)/20); //经验
    YString jineng = getAllSkillsList(); //所会技能
    YString wugong = "";
    //根据死亡次数减经验或武功级别
    if ((getBeKillTimes()%2) == 0)  //单数减经验(死亡后的)
    {
      //各种武功得经验减少为0
      while ((wugong = jineng.getWord()) != "")
      {
        wugong = wugong + "_经验";
        set (wugong , 0 );
      }
    }
    else   //双数减级别
    {
      while ((wugong = jineng.getWord()) != "")
      {
        long myskilllevel = ((YPlayer*)this)->getSkillLevel(wugong);
        if ( myskilllevel == 0) continue ;
        ((YPlayer*)this)->setSkillLevel(wugong, myskilllevel - 1);
      }
    }
    //减少50%得浅能
    setPotential((getPotential()*5)/10); //潜能
    //减少10%正气值
    setGoodnessCount((getGoodnessCount()*9)/10); //正气值
    //把人物的装备物品清空
    setWeaponName(""); //武器清空
    setClothName(""); //衣服
    setArmor(""); //盔甲
    setCloke(""); //斗篷
    setGird(""); //玉佩
    setFinger(""); //扳指
    setDangler(""); //耳环
    setDomino(""); //面具
    setHat(""); //帽子
    setShoe(""); //鞋
    setFlower(""); //花
    setRing(""); //戒指
    setNecklace(""); //项链
    setWeaponType(""); //武器类型
    setAppendAttack(0); //附加攻击力
    setAppendDefense(0); //附加防御力清空
    setAddArm(0);       //附加臂力清空
    setAddLearn(0);     //附加悟性清空
    setAddDodge(0);     //附加身法清空
    setAddForce(0);     //附加根骨清空
    setAddMaxBody(0);     //附加最大气血清空
    setAddMaxInternalForce(0);     //附加最大内力清空
    setAddMaxEnergy(0);     //附加最大精力清空
    setAddFeature(0);//set ("附加容貌值",0);
    setAddLuck(0);//set ("附加福缘",0);
    playerhpchange();
  }
  getRoom()->getRoomChat()->talk(NULL,getActorName()+"死了。");
  setBattle(0); //战斗
  setBusy(0); //繁忙
  setAdversary(""); //对手清空
  setKill(0); //对杀
  setStatus(""); //状态清空
  //杀人与被杀次数的处理
  YAbstractActor* objKiller=getRoom()->findChildActor(killer);
  if (objKiller)
  {
        if (!(objKiller->isTypeOf("YActor")))
        {
           display ("dead1出错");
           return 1;
        }
        YActor* tempobjKiller = (YActor*)objKiller ;
        setBeKillTimes(getBeKillTimes()+1); //被杀次数
        tempobjKiller->setKillTimes(tempobjKiller->getKillTimes()+1); //杀人次数
        tempobjKiller->setStatus(""); //状态
        if (isTypeOf("YPlayer"))
        {
          g_RumorChat->talk(NULL,"<font color="+g_Settings->getrumorChatColor()+">【谣言】"
          +"某人: 据江湖传言"+getActorName()+"被"+tempobjKiller->getActorName()+"杀死了。"+"</font>",NULL,NULL,CHANNEL_MSG);
          
          if ( objKiller->isTypeOf("YPlayer"))//处理pk
          {
          	if (tempobjKiller->getZdpk() == 1)
          	{
                	tempobjKiller->setPKTimes(tempobjKiller->getPKTimes()+1); //PK数
                	tempobjKiller->setZdpk(0);
                }
                if (getZdpk() == 1)
                {
                setBePKTimes(getBePKTimes()+1); //被PK数
                setZdpk(0); 
                }
          }
        }
  }
  else return 1;
  if (!(objKiller->isTypeOf("YActor")))
  {
           display ("dead2出错");
           return 1;
  }
  YActor* tempobjKiller = (YActor*)objKiller ;
  YString MyName=getActorName(); //名字
  YString Sex=getSexString(); //性别
  
  //玩家帮派
  if(isTypeOf("YPlayer") == 1){                   //如果被杀的是player
    if(tempobjKiller->isTypeOf("YPlayer") == 1){  //如果杀手还是player
      YPlayer *thisplayer=(YPlayer*)this;
      YPlayer *killplayer=(YPlayer*)tempobjKiller;
      if(thisplayer->getIsFactionOwner() == 1){             //并且是帮主 "是否帮主"
        YString sFactionName=thisplayer->getFactionName();  //"加入帮派"
        if(g_Faction->fnGetFacionOwner(sFactionName) != MyName){
          display("["+sFactionName+"]帮主纪录错误，请和巫师联系。");
        }
        else{
          g_Faction->fnRemoveFaction(sFactionName);  //删除一个帮派
          g_Faction->save();
          g_RumorChat->talk(NULL,"<font color="+thisplayer->getFactionMsgColor()
                  +">【顺风耳】<font color=red>灭门惨祸：</font>据江湖传言["+sFactionName
                  +"]被<font color=red>"+killer+"</font>所灭！["+sFactionName
                  +"]从此烟消云散！</font>",NULL,NULL,CHANNEL_MSG);
          killplayer->setKillFactionCount(killplayer->getKillFactionCount()+1);  //杀手的灭门数+1
        }
      }
    }
  }
  //玩家帮派处理结束

  //npc处理
  if(isTypeOf("YNPC"))
  {
      YString questList=tempobjKiller->getQuestList(); //任务列表
      YString hisName;
      YString questType,questTarget,questTargetType;
      long needPate;
      while((hisName=questList.getWord())!="")
      {
        if (! objKiller->isTypeOf("YPlayer")) break;
        questType=objKiller->getAsString(hisName+"_任务类型");
        questTarget=objKiller->getAsString(hisName+"_任务目标");
        questTargetType=objKiller->getAsString(hisName+"_任务目标类型");
        needPate=objKiller->getAsLong(hisName+"_需要首级");
        if((questType=="杀")&& //杀某人
          (questTarget==MyName)&&
          (needPate==0))
        {
          ((YPlayer*)objKiller)->getReward(hisName);
          break;
        }
        if(questType=="屠城"){ //屠某地
          if(questTargetType=="性别"){
            if(questTarget==Sex){
              ((YPlayer*)objKiller)->getReward(hisName);
              objKiller->set(hisName+"_屠城完成",1);
              break;
            }
          }
          if(questTargetType=="位置"){
            if((questTarget==getPlace())|| //位置
              (questTarget==getSchool()))  //门派
            {
              ((YPlayer*)objKiller)->getReward(hisName);
              objKiller->set(hisName+"_屠城完成",1); //为1表示屠城任务完成,即至少杀了一个满足条件的人
              break;
            }
          }
        }
      }
  }

  //处理其他方式死亡不生成尸体的问题
  if (getDeathMode() == "割死") //死亡方式
  {
    this->setBody(1);    //(为什么用this?)
    setKill(0); //死亡
    //showPhoto("0","4");
    YString s="setdead(\""+getActorName()+"\")";
    getRoom()->getRoomChat()->talk(NULL,s,this,NULL,JAVASCRIPT_MSG);
    if(isTypeOf("YNPC"))  gotoRoom(g_Settings->getNPCDeadRoom());//getAsString("NPC死亡房间"));
    else if(isTypeOf("YPlayer"))  gotoRoom(g_Settings->getDeadRoom());//getAsString("死亡房间"));
    else g_applog->write("[YActor::dead]死的既不是NPC也不是Player.");
    return 1;
  }
  //处理结束
  YString bodyname=getActorName(); //名字
  YAbstractThing *objBody;
  objBody=(YAbstractThing*)loadObject("thing/尸体");
  if ( objBody ) //物品在使用的时候的判断
  {
    if (objBody->isTypeOf("YThing"));
    else
    {
      display ("杀人尸体文件1出错");
      return 1;
    }
    getRoom()->addChild(objBody);
    objBody->setCount(1);
    ((YThing*)objBody)->setThingName(bodyname+"的尸体");//set("名字",bodyname+"的尸体");
    objBody->set("性别",Sex);
    objBody->set("尸体",1); //正常尸体的标志
    ((YThing*)objBody)->setDescribe("这是"+bodyname+"的尸体。");//set("描述","这是"+bodyname+"的尸体。");
    objBody->set("杀人者",killer);
    objBody->set("正气值",getGoodnessCount());
    if (isTypeOf("YNPC"))
    {
      objBody->set("拥有者类型","NPC");
    }
    else   objBody->set("拥有者类型","Player");
    //查看杀人者
    if(!objKiller){   //人物在使用的时候判断
      g_err.show("[YActor::dead]findChildActor"+killer+" iskiller NULL");
      return 1;
    }
    else tempobjKiller->setGoodnessCount(tempobjKiller->getGoodnessCount()-getGoodnessCount()/10);
    //---------------------------------------------------------
    //lp新添代码，作用是 查看人物是否还有同房间的对杀人物
    YString killname=tempobjKiller->getAllEnemyList(); //杀死人物列表
    YString name; //"sb."
    while ((name=killname.getWord()) != "")
    {
                YAbstractActor* sbkill=getRoom()->findChildActor(name);
                if (sbkill && (sbkill != this))//判断对杀人物的使用(不包括已死亡人物)
                {
                  tempobjKiller->setStatus("战斗中");
                }
    }
    //-------------------------------------------------------
    YString thingList=enumChildrenThing(); //对方身上的所有物品
    YString tempThing; //临时物品
    YAbstractThing *objThing;
    long diao;
    while((tempThing=thingList.getWord())!="")
    {
      objThing=findChildThing(tempThing);
      diao = objThing->getAsLong("不可掉落");
      if(!objThing) continue;
      else{
       if (diao == 1 && isTypeOf("YPlayer")) continue;
       else giveChildTo(objThing,objBody,objThing->getCount());
       }
    }
    if (tempobjKiller->isTypeOf("YPlayer"))
    {
       if (this->isTypeOf("YNPC"))
       {
         if (((YPlayer*)tempobjKiller)->getKillAndGet() == 1)
         {
            YString getallfrom ="all from "+ objBody->getObjectName();
           ((YPlayer*)tempobjKiller)->get(getallfrom);
         }
         if (((YPlayer*)tempobjKiller)->getKillAndGe() == 1)
         {
            YString getallfrom =objBody->getObjectName();
           ((YPlayer*)tempobjKiller)->ge(getallfrom);
         }
       }
     }
    //npc处理
   /* if(isTypeOf("YNPC")){
      YString questList=objKiller->getAsString("任务列表");
      YString hisName;
      YString questType,questTarget,questTargetType;
      long needPate;
      while((hisName=questList.getWord())!="")
      {
        questType=objKiller->getAsString(hisName+"_任务类型");
        questTarget=objKiller->getAsString(hisName+"_任务目标");
        questTargetType=objKiller->getAsString(hisName+"_任务目标类型");
        needPate=objKiller->getAsLong(hisName+"_需要首级");
        if((questType=="杀")&& //杀某人
          (questTarget==MyName)&&
          (needPate==0))
        {
          ((YPlayer*)objKiller)->getReward(hisName);
          break;
        }
        if(questType=="屠城"){ //屠某地
          if(questTargetType=="性别"){
            if(questTarget==Sex){
              ((YPlayer*)objKiller)->getReward(hisName);
              objKiller->set(hisName+"_屠城完成",1);
              break;
            }
          }
          if(questTargetType=="位置"){
            if((questTarget==getAsString("位置"))||
              (questTarget==getAsString("门派")))
            {
              ((YPlayer*)objKiller)->getReward(hisName);
              objKiller->set(hisName+"_屠城完成",1); //为1表示屠城任务完成,即至少杀了一个满足条件的人
              break;
            }
          }
        }
      }
    } */
  }
  this->setBody(1);    //(为什么用this?)
  setKill(0); //死亡
  //showPhoto("0","4");
  YString s="setdead(\""+getActorName()+"\")";
  getRoom()->getRoomChat()->talk(NULL,s,this,NULL,JAVASCRIPT_MSG);
  if(isTypeOf("YNPC"))  gotoRoom(g_Settings->getNPCDeadRoom());//getAsString("NPC死亡房间"));
  else if(isTypeOf("YPlayer"))  gotoRoom(g_Settings->getDeadRoom());//getAsString("死亡房间"));
  else g_applog->write("[YActor::dead]死的既不是NPC也不是Player.");
  return 1;
}
//---------------------------------------------------------
//lp
//昏到的处理
int YActor::faint(void)
{
    if ( getNotDead() == 1 )//不死处理
    {
      setBody(getMaxBody()); //气血恢复
      setEnergy(getMaxEnergy()); //精力恢复
      return 0;
    }
    setStatus("晕倒中");
    setBusy(0); //繁忙
    setBody(0); //气血
    setFaintTime(g_Settings->getsitFaintTime()); //设置晕倒时间
    setBattle(0); //战斗
    setKill(0); //对杀
    YString s=getAdversary(); //对手
    YAbstractActor* sb=getRoom()->findChildActor(s);
    setAdversary(""); //对手清空
    if(!sb)  //在使用的时候对对练的人物进行判断
    {
    }
    else
    {
      if (sb->isTypeOf("YActor"))
      {
        display("faint出错");
        return 1;
      }
      YActor* tempsb = (YActor*)sb;
      tempsb->setBattle(0); //战斗
      tempsb->setAdversary("");
      tempsb->display(getActorName()+"跳出战圈不打了");
    }
    display("你眼前一黑，昏倒了。");
    getRoom()->getRoomChat()->talk(NULL,getActorName()+"昏倒了。",this, NULL);
    showPhoto("1","5");
    return 1;
}
//---------------------------------------------------------
//lp
//人物苏醒的处理
int YActor::wakeup(void)
{
  if((getOwner() != NULL) && getOwner()->isTypeOf("YActor"))
  //对人物的拥有者 进行引用和类别的判断 sb不用判断了
  {
    YActor* sb;
    sb=(YActor*)getOwner();
    YAbstractRoom* room= sb->getRoom();
    room->getRoomChat()->talk(NULL,getActorName()+"清醒了。",this);
    sb->giveChildTo(this,room);
  }
  else if (getStatus() == "晕倒中")getRoom()->getRoomChat()->talk(NULL,getActorName()+"清醒了。",this);
  else
  {
    setFaintTime(3000000); //设置晕倒时间
    return 1;
  }
  showPhoto("0","4");
  setFreeTime(0); //空闲时间清0
  setFaintTime(0); //晕倒时间清0
  setStatus(""); //状态清空
  setBody(1); //气血设置为1
  display ("你清醒了。");
  return 1;
}
//----------------------------------------------------------------------------
//lp
//steal sb sth.     偷
int YActor::steal(YString sentence)
{
  /*YString s=sentence.getWord(); //"sb."
  YAbstractActor* sb=getRoom()->findChildActor(s);
  if ( getSchool() != "丐帮" ) //门派
  {
    display ("你不是丐帮弟子。不能偷盗。");
    return 1;
  }
  if((!sb)||(!sb->isTypeOf("YActor"))) //被偷人物的引用和类别判断
  {
    display("你要偷谁？");
    return 1;
  }
  YString s1=sentence.getWord(); //"sth."
  YAbstractThing* sth=sb->findChildThing(s1);
  if(!sth || (! sth->isTypeOf("YThing")))//物品的判断
  {
    display("他没有这件物品。");
    return 1;
  }
   //npc的处理
  if(sb->isTypeOf("YNPC"))//对NPC的判断
  {
     sb->executeCommandAsTarget(this,"steal "+s+" "+s1);
     return 1;
  }

  #ifdef __WIN32__
  randomize();
  #else //UNIX
  srand(time(0));
  #endif //__WIN32__

   long chance = getAsLong ("妙手空空");    //成功机会
   if((rand() % 100) < chance)
   {
        sb->giveChildTo(sth,this);
        YString msg=getActorName()+"偷到了"+((YActor*)sb)->getActorName()+"的"+((YThing*)sth)->getThingName()+"。";
        getRoom()->getRoomChat()->talk(NULL, msg);

   }
   else
   {
       YString msg=((YActor*)sb)->getActorName()+"对"+getActorName()+"喊道，抓贼啊！！！！";
       getRoom()->getRoomChat()->talk(NULL, msg);

   }
   sb->executeCommandAsTarget(this,"steal "+s+" "+s1);//传递命令
   return 1; */
   return 1;
}
//--------------------------------------------------------
int YActor::gotoRoom(YString roomName)
{
  int retVal=getRoom()->sendActorToRoom(this,roomName);
  if(retVal==0) /*do nothing*/; //look();
  else if(retVal==2) display("目的地不存在");
  else display("无法到达目的地.");
  return 1;
}
//----------------------------------------------------------
int YActor::playerfindname(YString allname , YString findname)
{
   YString tempname ;
   long flag = 0;
   while ((tempname = allname.getWord()) != "")
   {
     if (tempname == findname)
     {
        flag = 1;
        break;
     }
     else ;
   }
   return flag;
}
//-----------------------------------------------------------------
int YActor::dropplayer(void)   //丢掉身上的人物
{
        YString thingList=enumChildrenActor(); //身上的人物
        YString tempThing; //临时物品
        YAbstractActor* isactor;
        while((tempThing=thingList.getWord())!="")
        {
           isactor=findChildActor(tempThing);
           if(!isactor) continue;
           giveChildTo(isactor,getRoom());
        }
        return 1;
}
//-----------------------------------------------------------------
bool YActor::findStringInStr (YString theString ,YString findString) //查找字符串的字符
{
   if (theString == findString) return true;
   long longtheString = theString.size();
   long longfindString = findString.size();
   YString bigStr = theString ;
   YString smaStr = findString ;
   //开始的
   if ( ( longfindString+1 ) > longtheString ) return false;
   YString tempString =  bigStr.substr(0,longfindString);
   if (tempString == (smaStr) ) return true ;
   //中间的
   tempString = ' '+smaStr+' ';
   if((bigStr.find(tempString,longfindString)) != YString::npos) return true ;
   //结尾的
   tempString = bigStr.substr(longtheString - longfindString -1);
   smaStr = ' ' + smaStr ;
   if (tempString == smaStr ) return true ;
   //没找到返回错误
   return false;
   /*
   YString tempString ;
   while ((tempString = theString.getWord()) != "")
   {
     if (tempString == findString)
     {
        return true ;
     }
   }
   return false;
   */
}
//-----------------------------------------------------------------
//显示人物的图形变换
int YActor::showPhoto(YString man , YString woman)
{
  YString tuxing = man;//默认男
  if (getSexString() == "女") tuxing = woman;
  else if (getwichpho() == 1)
  {
        tuxing = woman;
  }
  tuxing = selePhoto(tuxing);
  YString s="chpic(\""+getActorName()+"\","+tuxing+")";
  getRoom()->getRoomChat()->talk(NULL,s,NULL,NULL,JAVASCRIPT_MSG);
  display(tuxing);
  return 1;
}
//--------------------------------------------------------
//move x y ---在房间里移动
int YActor::move(YString sentence)
{
  //从坐躺状态中恢复
  YString zhuangtai = getStatus(); //状态
  if (zhuangtai == "打坐" || zhuangtai == "吐纳" )
  {
    halt();
    showPhoto("0","4");
  }
  if (zhuangtai == "坐" || zhuangtai == "躺")
  {
    showPhoto("0","4");
    setStatus(""); //状态清空
  }
  //取得x,y
  int x=sentence.getWord().toLong();
  int y=sentence.getWord().toLong();
  //将X,Y限定在范围内
  if(x<0) x=0;
  if(y<0) y=0;
  int max_x=g_Settings->getsitMaxX();//getAsLong("max_x");
  if(x>max_x) x=max_x;
  int max_y=g_Settings->getsitMaxY();//getAsLong("max_y");
  if(y>max_y) y=max_y;
  //设置
  setX(x);
  setY(y);
  YString s="move(\""+getActorName()+"\","+(YString)x+","+(YString)y+")";
  getRoom()->getRoomChat()->talk(NULL,s,this,NULL,JAVASCRIPT_MSG);
  return 1;
}
int YActor::isnewbie(void)
{
  if ( getActorAge() > g_Settings->getsitNewbieAge())//getAsLong("新手年龄")) //年龄
  {
    return 0;
  }
  else return 1;
}
//--------------------------------------------------------
//move x y ---在房间里移动
int YActor::movetodirection(YString direction)
{
  /*//从坐躺状态中恢复
  YString zhuangtai = getAsString ("状态");
  if (zhuangtai == "打坐" || zhuangtai == "吐纳" )
  {
    halt();
    showPhoto("0","4");
  }
  if (zhuangtai == "坐" || zhuangtai == "躺")
  {
    showPhoto("0","4");
    set("状态","");
  }  */
  //判断
  int x=getX();
  int y=getY();
  int max_x=g_Settings->getsitMaxX();//getAsLong("max_x");
  int max_y=g_Settings->getsitMaxY();//getAsLong("max_y");
  int min_x=g_Settings->getsitMinX();//getAsLong("min_x");
  int min_y=g_Settings->getsitMinY();//getAsLong("min_y");
  //判断方向
  if ( direction == "东" )
  {
    x = max_x ;
    y = getY() ;
  }
  else if ( direction == "东北" )
  {
    x = max_x ;
    y = min_y;
  }
  else if ( direction == "北" )
  {
    x = getX() ;
    y = min_y ;
  }
  else if ( direction == "西北" )
  {
    x = min_x ;
    y = min_y ;
  }
  else if ( direction == "西" )
  {
    x = min_x ;
    y = getY() ;
  }
  else if ( direction == "西南" )
  {
    x = min_x ;
    y = max_y ;
  }
  else if ( direction == "南" )
  {
    x = getX() ;
    y = max_y ;
  }
  else if ( direction == "东南" )
  {
    x = max_x ;
    y = max_y ;
  }
  YString s="move(\""+getActorName()+"\","+(YString)x+","+(YString)y+")";
  //设置在另一个房间的出现位置
  if ((direction == "东") || (direction == "东上")|| (direction == "东下")) //东，西变x坐标
     {
           setX(min_x);
           setY(y);
     }
  else if ( (direction == "西" )|| (direction == "西上") || (direction == "西下") )
     {
         setX(max_x);
         setY(y);
     }
  else if ((direction == "北"  ) ||(direction == "北上"  )
            ||(direction == "北下" )||(direction == "里面" )||(direction == "上" ))  //南，北变Y坐标
      {
           setX(x);
           setY(max_y);
      }
  else if (( direction == "南" )||( direction == "南上" )
             ||( direction == "南下" )||( direction == "外面" )||( direction == "下" ))
     {
         setX(x);
         setY(min_y);
     }
  else if (direction == "西南")//其余的坐标全变
      {
           setX(max_x);
           setY(min_y);
      }
  else if (direction == "东南")//其余的坐标全变
      {
           setX(min_x);
           setY(min_y);
      }
  else if (direction == "西北")//其余的坐标全变
      {
           setX(max_x);
           setY(max_y);
      }
  else if (direction == "东北")//其余的坐标全变
      {
           setX(min_x);
           setY(max_y);
      }
  else //其余的坐标全变
      {
      }
  getRoom()->getRoomChat()->talk(NULL,s,NULL,NULL,JAVASCRIPT_MSG);
  return 1;
}
//-----------------------------------------------------------------
//zhy
//对pActor和其他人输出不同信息
int YActor::OutputMsg(YAbstractActor* executor,YString msg)
{
   YActor* pActor;
   if(executor->isTypeOf("YActor")) pActor=(YActor*)executor;
   else return 1;
   YString s=msg;
   //msgPlayer对pActor的消息,msgOthers对其他人的消息
   YString msgPlayer="",msgOthers="";
   long ssize = s.size();
   for(int i=0; i<ssize ;i++){
      if(s[i]=='&'){
        if(s[i+1]=='s'){
          i++;
          msgPlayer+="你";
          msgOthers+=pActor->getActorName();
        }
        else if(s[i+1]=='n'){
          i++;
          msgPlayer+=pActor->getActorName();
          msgOthers+=pActor->getActorName();
        }
      }
      else{
        msgPlayer+=s[i];
        msgOthers+=s[i];
      }
   }
   YAbstractRoom* objRoom;
   YChat* objChat;
   objRoom=getRoom();
   if(!objRoom) return 1;
   objChat=objRoom->getRoomChat();
   if(!objChat) return 1;
   objChat->talk(NULL,msgOthers,this,pActor);
   //getRoom()->getRoomChat()->talk(NULL,msgOthers,this,pActor);
   pActor->display(msgPlayer);
   return 1;
}
//--------------------------------------------
//销毁子物品
int YActor::letsDestroy(void)
{
  YString destroyList=getDestroyList(); //销毁列表
  YString theThing;
  YAbstractThing* tempthing;
  YDestroyThing* objThing;
  while((theThing=destroyList.getWord())!="")
  {
    tempthing = findChildThing(theThing) ;
    if(!tempthing) continue;
    if (tempthing->isTypeOf("YDestroyThing"))
    {
      objThing=(YDestroyThing*)tempthing;
    }
    else g_err.show("[YActor::letsDestroy] "+theThing+"不是YDestroyThing");
    if(removeChild(objThing)){
      delete objThing;
    }
  }
  setDestroyList(""); //销毁列表清空
  return 1;
}
//--------------------------------------------------------
//刷新hp的动态显示
void YActor::refreshHP(void)
{
}


//--------------------------------------------------------
//
int YActor::ActorAddFeatureChange(void)
{
/*  YString thingtype = "";
  long alladd=0;
  long fyadd=0;
  long fangadd=0;
  YAbstractThing* sth;
  thingtype = getFlower(); //花
  sth=findChildThing(thingtype);
  if (sth)
  {
    alladd = alladd + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fangadd = fangadd + ( sth->getAsLong("防御力") ) ;
  }
  else setFlower("");
  thingtype = getRing(); //戒指
  sth=findChildThing(thingtype);
  if (sth)
  {
    alladd = alladd + ( sth->getAsLong("容貌值") );
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fangadd = fangadd + ( sth->getAsLong("防御力") ) ;
  }
  else setRing("");
  thingtype = getNecklace();//项链
  sth=findChildThing(thingtype);
  if (sth)
  {
    alladd = alladd + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fangadd = fangadd + ( sth->getAsLong("防御力") ) ;
  }
  else setNecklace("");
  thingtype = getBangle();//手镯
  sth=findChildThing(thingtype);
  if (sth)
  {
    alladd = alladd + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fangadd = fangadd + ( sth->getAsLong("防御力") ) ;
  }
  else setBangle("");
  setAddFeature(alladd);//附加容貌的从新计算
  setAddLuck(fyadd);//附加福缘的从新计算
  setAppendDefense(fangadd);  //附加防御力的从新计算*/
  return 1;
}
//--------------------------------------------------------
//武器、衣服、其他物品的附加变化
int YActor::ActorAddRecoveryChange(void)  //攻击力、防御力、容貌值、福缘、最大气血、最大内力、最大精力、悟性、根骨、臂力、身法
{
  YString thingtype = "";
  long fyall=0;
  long fyadd=0;
  long rmall=0;
  long gjadd=0;
  long qxadd=0;
  long nladd=0;
  long jladd=0;
  long wxadd=0;
  long sfadd=0;
  long bladd=0;
  long ggadd=0;
  YAbstractThing* sth;

  thingtype = getWeaponName();//武器
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else
  {
    setWeaponName("");
    setWeaponType("");
    setAppendAttack(0);
  }
  thingtype = getClothName(); //衣服
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setClothName(""); 
  thingtype = getArmor();  //盔甲
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setArmor("");   
  thingtype = getCloke();  //斗篷
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setCloke("");
  thingtype = getHat();  //帽子
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setHat("");
  thingtype = getShoe();  //鞋
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setShoe("");
  thingtype = getGird();  //玉佩
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setGird("");
  thingtype = getArming();  //徽章
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setArming("");
  thingtype = getFinger();  //扳指
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setFinger("");
  thingtype = getDangler();  //耳环
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setDangler("");
  thingtype = getDomino();  //面具
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setDomino("");
  thingtype = getFlower(); //花
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setFlower("");
  thingtype = getRing(); //戒指
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setRing("");
  thingtype = getNecklace();//项链
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setNecklace("");
  thingtype = getBangle();//手镯
  sth=findChildThing(thingtype);
  if (sth)
  {
    gjadd = gjadd + ( sth->getAsLong("攻击力") ) ; 
    rmall = rmall + ( sth->getAsLong("容貌值") ) ;
    fyadd = fyadd + ( sth->getAsLong("福缘") ) ;
    fyall = fyall + ( sth->getAsLong("防御力") ) ;
    qxadd = qxadd + ( sth->getAsLong("附加气血") ) ;
    nladd = nladd + ( sth->getAsLong("附加内力") ) ;
    jladd = jladd + ( sth->getAsLong("附加精力") ) ;
    wxadd = wxadd + ( sth->getAsLong("悟性") ) ;
    sfadd = sfadd + ( sth->getAsLong("身法") ) ;
    bladd = bladd + ( sth->getAsLong("臂力") ) ;
    ggadd = ggadd + ( sth->getAsLong("根骨") ) ;
  }
  else setBangle("");

  setAppendAttack(gjadd);//附加攻击的从新计算
  setAppendDefense(fyall);  //附加防御力的从新计算
  setAddFeature(rmall);//附加容貌的从新计算
  setAddLuck(fyadd);//附加福缘的从新计算
  setAddMaxBody(qxadd);  //附加最大气血的从新计算
  setAddMaxInternalForce(nladd);  //附加最大内力的从新计算
  setAddMaxEnergy(jladd);  //附加最大精力的从新计算
  setAddLearn(wxadd);  //附加悟性的从新计算
  setAddDodge(sfadd);  //附加身法的从新计算
  setAddArm(bladd);  //附加臂力的从新计算
  setAddForce(ggadd);  //附加根骨的从新计算
  playerhpchange();
  return 1;
}
//--------------------------------------------------------
//清除任务百分比
int YActor::delQuestpercent(YString questname , long percent)
{
  set (questname , (getAsLong(questname)*(100-percent))/100);
  return 1;
}
//--------------------------------------------------------
//选择图片
YString YActor::selePhoto(YString basephoto)
{
  if (getSchool()=="") basephoto = "1" + basephoto ;
  else if (getSchool()=="少林派" || getSchool()=="峨嵋派") basephoto = "2" +basephoto ;
  else if (getSchool()=="武当派" || getSchool()=="全真教") basephoto = "3" +basephoto;
  else if (getSchool()=="丐帮") basephoto = "4" +basephoto;
  else if (getSchool() =="蛇" || getSchool() == "狗") basephoto = "5" + basephoto;
  else if (getSchool()=="官兵" || getSchool()=="武将") basephoto =  "6" +basephoto;
  else if (getSchool()=="韦小宝" || getSchool()=="白无常") basephoto =  "7" +basephoto;
  else if (getSchool()=="独孤求败" || getSchool()=="红娘") basephoto =  "8" +basephoto;
  else if (getSchool()=="头陀" || getSchool()=="牛蛙") basephoto =  "9" +basephoto;
  else if (getSchool()=="QQ" || getSchool()=="乔风") basephoto =  "10" +basephoto;

  return basephoto ;
}
//-----------------------------------------------------------------

//封装display，使其和OutputMsg的使用格式相同
//&s -- 你
//&n -- "名字"
int YActor::displayEx(YString msg)
{
   YString s=msg;
   YString msgPlayer="";
   long ssize = s.size();
   for(int i=0; i<ssize ;i++){
      if(s[i]=='&'){
        if(s[i+1]=='s'){
          i++;
          msgPlayer+="你";
        }
        else if(s[i+1]=='n'){
          i++;
          msgPlayer+=getActorName();
        }
      }
      else{
        msgPlayer+=s[i];
      }
   }
   display(msgPlayer);
   return 1;
}
