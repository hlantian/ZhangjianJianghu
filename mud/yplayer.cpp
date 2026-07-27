//---------------------------------------------------------------------------
//
// yplayer.cpp    2000年6月12日
//
// 类YPlayer：玩家
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

const long EXP=3000000;     //3M      经验
const long MONEY=2000000;     //200金   存款
const long ATTACK=20000;       //2万     固定攻击力
const long DEFENSE=10000;       //1万     固定防御力
const long GOODNESS=300000;      //30万    正气值
const long EVILNESS=-300000;     //-30万   负的正气值
const long CREDIT=10000;       //1万     江湖声望 

//--------------------------------------------------------
//构造函数
YPlayer::YPlayer(YUser* user, YString initFileName): YActor(initFileName),
        m_playerip(""),
        m_Beg(0),//描述的变量为：叫化绝活
	m_FightMiaoshu(0),//描述的变量为：较量描述
	m_BeginArm(0),//描述的变量为：先天臂力
	m_BeginLearn(0),//描述的变量为：先天悟性
	m_beginDodge(0),//描述的变量为：先天身法
	m_BeginForce(0),//描述的变量为：先天根骨
	m_Weight(0),//描述的变量为：负重
	m_MaxWeight(0),//描述的变量为：最大负重
	m_Food(0),//描述的变量为：食物
	m_Drink(0),//描述的变量为：饮水
	m_MaxFood(0),//描述的变量为：最大食物
	m_MaxDrink(0),//描述的变量为：最大饮水
	m_TunaTime(0),//描述的变量为：吐纳时间
	m_DazuoTime(0),//描述的变量为：打坐时间
	m_Steal(0),//描述的变量为：妙手空空
	m_BaseHand(0),//描述的变量为：基本拳法
	m_BaseFinger(0),//描述的变量为：基本指法
	m_baseSole(0),//描述的变量为：基本掌法
	m_BaseLeg(0),//描述的变量为：基本腿法
	m_BasePub(0),//描述的变量为：基本手法
	m_BaseClow(0),//描述的变量为：基本爪法
	m_BaseDodge(0),//描述的变量为：基本轻功
	m_BaseForce(0),//描述的变量为：基本内功
	m_Learn(0),//描述的变量为：读书写字
	m_BaseParry(0),//描述的变量为：基本招架
	m_FreeTime(0),//描述的变量为：空闲时间
	//m_PowUPHit(0),//描述的变量为：powerup攻击力
	//m_PowUPDeff(0),//描述的变量为：powerup防御力
 	//m_BeKill(0),//描述的变量为：被杀次数
	//m_KillOther(0),//描述的变量为：杀人次数
	//m_PKHow(0),//描述的变量为：pk数
	//m_BePKHow(0),//描述的变量为：被pk数
	m_GiveThing(0),//描述的变量为：送东西数
	m_CityKill(0),//描述的变量为：屠城数
	m_SleepTime(0),//描述的变量为：睡眠
	m_Deposit(0),//描述的变量为：存款
	m_CloseChat(0),//描述的变量为：关闭共用频道
	m_CloseRum(0),//描述的变量为：关闭谣言频道
	m_CloseNewbie(0),//描述的变量为：关闭新手频道
        m_CloseParty(0),//门派频道
	m_ComeIn(0),//描述的变量为：新人登录步骤
	m_PlayerLevel(0),//玩家级别
        m_WizCloseChat(0), //巫师关闭频道
	m_PlayCloseChat(0), //玩家关闭频道
        m_playSaySpeed(0), //玩家说话频率
        m_PartyValue(0),// (门派评价)
        m_CourtValue(0),// (朝廷声望)
        m_SocietyValue(0),//(江湖声望)
	m_OnlineTime(0), //属性：OnlineTime(在线时间)的成员变量
	m_LaseOnlineTime(0), //属性LaseOnlineTime(上次在线时间)的成员变量
        m_PlayerSleepSkip(0),
        m_PlayerRenew(0),
        m_NowWork(0),//正在劳动
        m_noaccept(0),//接受物品
        m_Session(0),
        m_IsFactionOwner(0),    //是否帮主
        m_FactionName(""),      //加入帮派
        m_FactionTitle(""),     //帮派头衔 
        m_OldPower(0),          //上次势力
        m_KillFactionCount(0),  //灭门数
        m_CloseFactionParty(0)  //关闭帮派频道
{
 
  this->setXiluUserManager(user->getXiluUserManager());
  this->setName(user->getName());
  this->set("名字",getName());
  this->setObjectName(getName());
  this->setPassword(user->getPassword());
  this->setEncryptedPassword(user->getEncryptedPassword());
  YString mysex = this-> getAsString("性别");
  if ( mysex == "" ) this->setSex(user->getSex());
  else  this->setSexString(mysex) ;
  this->setAge(user->getAge());
  this->setProvence(user->getProvence());
  this->setEmail(user->getEmail());
  this->setHomepage(user->getHomepage());

  //this->setLevel(user->getLevel());
  this->setLevelString(user->getLevelString());

  g_SystemChat->subscribe(this);
  g_NormalChat->subscribe(this);
  g_NewUserChat->subscribe(this);
  g_RumorChat->subscribe(this);
  //g_InfoChat->subscribe(this);
  //订阅门派频道
  YString menpai = this->getAsString("门派");
  if (menpai == "华山派") {g_HuaShanChat->subscribe(this);   m_menpaichat = g_HuaShanChat;}
  else if (menpai == "武当派") { g_WuDangChat->subscribe(this); m_menpaichat = g_WuDangChat;}
  else if (menpai == "古墓派") { g_GuMuChat->subscribe(this);   m_menpaichat = g_GuMuChat;}
  else if (menpai == "少林派")  { g_ShaoLinChat->subscribe(this);  m_menpaichat = g_ShaoLinChat;}
  else if (menpai == "峨嵋派")  { g_EMeiChat->subscribe(this);  m_menpaichat = g_EMeiChat;}
  else if (menpai == "丐帮")  { g_GaiBangChat->subscribe(this);  m_menpaichat = g_GaiBangChat;}
  else if (menpai == "白驼山庄")  { g_BaiTuoChat->subscribe(this); m_menpaichat =g_BaiTuoChat ;}
  else if (menpai == "明教") {g_MingJiaoChat->subscribe(this); m_menpaichat = g_MingJiaoChat ;}
  else if (menpai == "血刀门") {g_XueDaoChat->subscribe(this); m_menpaichat = g_XueDaoChat ;}
  else if (menpai == "侠客岛") {g_XiaKeChat->subscribe(this); m_menpaichat = g_XiaKeChat ;}
  else if (menpai == "日月神教") {g_RiYueChat->subscribe(this); m_menpaichat = g_RiYueChat ;}
  else if (menpai == "大理") {g_DaLiChat->subscribe(this); m_menpaichat = g_DaLiChat ;}
  else if (menpai == "桃花岛") {g_TaoHuaChat->subscribe(this); m_menpaichat = g_TaoHuaChat ;}
  else if (menpai == "红花会") {g_HongHuaChat->subscribe(this); m_menpaichat = g_HongHuaChat ;}
  else if (menpai == "灵鹫宫") {g_LingJiuChat->subscribe(this); m_menpaichat = g_LingJiuChat ;}
  else if (menpai == "神龙教") {g_ShenLongChat->subscribe(this); m_menpaichat = g_ShenLongChat ;}
  else { m_menpaichat = NULL ;}
  //进入的时候停止对杀
  this->set ("杀死人物列表","");
  this->set ("房间内敌人列表","");
  this->set ("状态","");
  this->setSmallTime(2000);
  onAfterLoad();
  m_pFactionChat=NULL;  //帮派频道指针初始化为NULL
  fnProcessFaction(); //玩家帮派
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YPlayer::onAfterLoad(void)
{
     int retVal=YActor::onAfterLoad();
     setplayerip(getAsString("IP"));
     setBeg(getAsLong("叫化绝活")) ;
     setFightMiaoshu(getAsLong("较量描述")) ;
     setBeginArm(getAsLong("先天臂力")) ;
     setBeginLearn(getAsLong("先天悟性")) ;
     setbeginDodge(getAsLong("先天身法")) ;
     setBeginForce(getAsLong("先天根骨")) ;
     setWeight(getAsLong("负重")) ;
     setMaxWeight(getAsLong("最大负重")) ;
     setFood(getAsLong("食物")) ;
     setDrink(getAsLong("饮水")) ;
     setMaxFood(getAsLong("最大食物")) ;
     setMaxDrink(getAsLong("最大饮水")) ;
     setTunaTime(getAsLong("吐纳时间")) ;
     setDazuoTime(getAsLong("打坐时间")) ;
     setSteal(getAsLong("妙手空空")) ;
     setBaseHand(getAsLong("基本拳法")) ;
     setBaseFinger(getAsLong("基本指法")) ;
     setbaseSole(getAsLong("基本掌法")) ;
     setBaseLeg(getAsLong("基本腿法")) ;
     setBasePub(getAsLong("基本手法")) ;
     setBaseClow(getAsLong("基本爪法")) ;
     setBaseDodge(getAsLong("基本轻功")) ;
     setBaseForce(getAsLong("基本内功")) ;
     setLearn(getAsLong("读书写字")) ;
     setBaseParry(getAsLong("基本招架")) ;
     setFreeTime(getAsLong("空闲时间")) ;
     //setPowUPHit(getAsLong("powerup攻击力")) ;
     //setPowUPDeff(getAsLong("powerup防御力")) ;
     //setBeKill(getAsLong("被杀次数")) ;
     //setKillOther(getAsLong("杀人次数")) ;
     //setPKHow(getAsLong("pk数")) ;
     //setBePKHow(getAsLong("被pk数")) ;
     setGiveThing(getAsLong("送东西数")) ;
     setCityKill(getAsLong("屠城数")) ;
     setSleepTime(getAsLong("睡眠")) ;
     setDeposit(getAsLong("存款")) ;
     setCloseChat(getAsLong("关闭共用频道")) ;
     setCloseRum(getAsLong("关闭谣言频道")) ;
     setCloseNewbie(getAsLong("关闭新手频道")) ;
     setCloseParty(getAsLong("关闭门派频道")) ;
     setComeIn(getAsLong("新人登录步骤")) ;
     setPlayerLevel(getAsLong("玩家级别"));
     setWizCloseChat(getAsLong("巫师关闭频道"));
     setPlayCloseChat(getAsLong("玩家关闭频道"));
     setplaySaySpeed(getAsLong("玩家说话频率"));
     setPartyValue(getAsLong("门派评价")); //设置PartyValue(门派评价)
     setCourtValue(getAsLong("朝廷声望")); //设置CourtValue(朝廷声望)
     setSocietyValue(getAsLong("江湖声望"));//设置SocietyValue(江湖声望)
     setLaseOnlineTime(getAsLong("在线时间")); //设置属性：LaseOnlineTime(上次在线时间)
     setOnlineTime(getAsLong("上次在线时间"));//设置属性：OnlineTime(在线时间)
     setPlayerSleepSkip(getAsLong("睡觉间隔"));//设置玩家休息的间隔
     setPlayerRenew(getAsLong("身体恢复速度"));//玩家身体恢复速度
     setNowWork(getAsLong("正在劳动"));//正在劳动
     //
     setIsFactionOwner(getAsLong("是否帮主"));        //是否帮主
     setFactionName(getAsString("加入帮派"));         //加入帮派
     setFactionTitle(getAsString("帮派头衔"));        //帮派头衔
     setOldPower(getAsLong("上次势力"));              //上次势力
     setKillFactionCount(getAsLong("灭门数"));        //灭门数
     setCloseFactionParty(getAsLong("关闭帮派频道")); //关闭帮派频道
     playerarmchange();
     return retVal;
}

//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YPlayer::onBeforeSave(void)
{
     int retVal=YActor::onBeforeSave();
     set("IP",getplayerip());
     set("叫化绝活",getBeg());//结束后 叫化绝活 变量的处理
     set("较量描述",getFightMiaoshu());//结束后 较量描述 变量的处理
     set("先天臂力",getBeginArm());//结束后 先天臂力 变量的处理
     set("先天悟性",getBeginLearn());//结束后 先天悟性 变量的处理
     set("先天身法",getbeginDodge());//结束后 先天身法 变量的处理
     set("先天根骨",getBeginForce());//结束后 先天根骨 变量的处理
     set("负重",getWeight());//结束后 负重 变量的处理
     set("最大负重",getMaxWeight());//结束后 最大负重 变量的处理
     set("食物",getFood());//结束后 食物 变量的处理
     set("饮水",getDrink());//结束后 饮水 变量的处理
     set("最大食物",getMaxFood());//结束后 最大食物 变量的处理
     set("最大饮水",getMaxDrink());//结束后 最大饮水 变量的处理
     set("吐纳时间",getTunaTime());//结束后 吐纳时间 变量的处理
     set("打坐时间",getDazuoTime());//结束后 打坐时间 变量的处理
     set("妙手空空",getSteal());//结束后 妙手空空 变量的处理
     set("基本拳法",getBaseHand());//结束后 基本拳法 变量的处理
     set("基本指法",getBaseFinger());//结束后 基本指法 变量的处理
     set("基本掌法",getbaseSole());//结束后 基本掌法 变量的处理
     set("基本腿法",getBaseLeg());//结束后 基本腿法 变量的处理
     set("基本手法",getBasePub());//结束后 基本手法 变量的处理
     set("基本爪法",getBaseClow());//结束后 基本爪法 变量的处理
     set("基本轻功",getBaseDodge());//结束后 基本轻功 变量的处理
     set("基本内功",getBaseForce());//结束后 基本内功 变量的处理
     set("读书写字",getLearn());//结束后 读书写字 变量的处理
     set("基本招架",getBaseParry());//结束后 基本招架 变量的处理
     set("空闲时间",0);//结束后 空闲时间 变量的处理
     //set("powerup攻击力",getPowUPHit());//结束后 powerup攻击力 变量的处理
     //set("powerup防御力",getPowUPDeff());//结束后 powerup防御力 变量的处理
     //set("被杀次数",getBeKill());//结束后 被杀次数 变量的处理
     //set("杀人次数",getKillOther());//结束后 杀人次数 变量的处理
     //set("pk数",getPKHow());//结束后 pk数 变量的处理
     //set("被pk数",getBePKHow());//结束后 被pk数 变量的处理
     set("送东西数",getGiveThing());//结束后 送东西数 变量的处理
     set("屠城数",getCityKill());//结束后 屠城数 变量的处理
     set("睡眠",getSleepTime());//结束后 睡眠 变量的处理
     set("存款",getDeposit());//结束后 存款 变量的处理
     set("关闭共用频道",getCloseChat());//结束后 关闭共用频道 变量的处理
     set("关闭谣言频道",getCloseRum());//结束后 关闭谣言频道 变量的处理
     set("关闭新手频道",getCloseNewbie());//结束后 关闭新手频道 变量的处理
     set("关闭门派频道",getCloseParty());//结束后 关闭门派频道 变量的处理
     set("新人登录步骤",getComeIn());//结束后 新人登录步骤 变量的处理
     set("玩家级别",getPlayerLevel());//结束后 玩家级别 变量的处理
     set("巫师关闭频道",getWizCloseChat());//结束后 巫师关闭频道 变量的处理
     set("玩家关闭频道",getPlayCloseChat());//结束后 玩家关闭频道 变量的处理
     set("玩家说话频率",getplaySaySpeed());
     set("门派评价",getPartyValue()); //设置PartyValue(门派评价)
     set("朝廷声望",getCourtValue()); //设置CourtValue(朝廷声望)
     set("江湖声望",getSocietyValue());//设置SocietyValue(江湖声望)
     set("在线时间",getOnlineTime());// 在线时间
     set("上次在线时间",getLaseOnlineTime());//  上次在线时间
     set("睡觉间隔",getPlayerSleepSkip());//睡觉间隔
     set("身体恢复速度",getPlayerRenew()); // 身体恢复速度
     set("正在劳动",getNowWork());//正在劳动
     set("是否帮主",getIsFactionOwner());         //是否帮主 
     set("加入帮派",getFactionName());            //加入帮派 
     set("帮派头衔",getFactionTitle());           //帮派头衔 
     set("上次势力",getOldPower());               //上次势力 
     set("灭门数",getKillFactionCount());         //灭门数 
     set("关闭帮派频道",getCloseFactionParty());  //关闭帮派频道
     return retVal;

}

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YPlayer::isTypeOf(YString className)
{
  if(className=="YPlayer") return 1;
  else return YActor::isTypeOf(className);
}
//--------------------------------------------------------
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YPlayer::getDisplayName(void)
{
  YString name=getActorName();//getAsString("名字");
  //return "<script>sa(\'"+name+"\');</script>";
  return "<font color="+g_Settings->getPlayerNameColor()
          +"><span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+name+"\")>"+name+"</span></font>";
}
//-------------------------------------------------------------
//属性： NickName (显示人物得绰号和名字)
YString YPlayer::getNickName(void)
{
    YString name=getActorName();//getAsString("名字");
    YString hand = getTitle();//getAsString("头衔");
    YString nick = getNick();
    if (hand != "") hand = "["+hand+"]";
    YString atThisTime = getStatus();//getAsString("状态");
    if  (atThisTime !="")  atThisTime ="("+atThisTime+")";
    //玩家帮派
    YString sFactionName=getFactionName();    //"加入帮派"
    YString msg="";
    if(sFactionName != ""){
      YString color=g_Faction->fnGetFacionColor(sFactionName);
      YString sFactionColorName="<font color="+color+">["+sFactionName+"]</font>";//带颜色的帮派名字
      YString sFactionTitle=getFactionTitle();  //"帮派头衔"
      msg+=sFactionColorName+"<font color="+color+">["+sFactionTitle+"]</font>";
    }
    //玩家帮派结束
    return msg+hand+nick+"<font color="+g_Settings->getNPCNameColor()
          +"><span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+name+"\")>"+name+atThisTime+"</span></font>";
}
//----------------------------------------------------------------
//事件Init的默认处理函数
int YPlayer::onInit(void)
{
  int retVal=YActor::onInit();
  //清除装备
  setWeaponName("");//set("武器","");
  setArmor("");//set("盔甲","");
  setClothName("");//set("衣服","");
  setShoe("");//set("鞋","");
  setHat("");//set("帽子","");
  setNecklace("");//set("项链","");
  setRing("");//set("戒指","");
  setFlower("");//set("花","");
  setWeaponAttack(0);//set("武器攻击力",0);
  setWeaponType("");//set("武器类型","");
  playerarmchange();
  return retVal; //必须返回1，表示处理结束
}
//--------------------------------------------------------
//事件Message的默认处理函数
int YPlayer::onMessage(YAbstractActor* speaker, YString message)
{
  return 1;
}
//--------------------------------------------------------
//接收一条消息
void YPlayer::message(YAbstractActor* speaker, YString msg, bool newline,
                msg_type messagetype, const YString& name)
{
  YString speakername;
  if((speaker)&&(messagetype==CHANNEL_MSG)) speakername=speaker->getObjectName();//getAsString("名字");
  else speakername=name;
  YActor::message(speaker, msg, newline, messagetype, name);

  if(m_Session) m_Session->message(msg, newline, messagetype, speakername);
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YPlayer::onTimer(void)
{

  YActor::onTimer(); //首先调用父类的处理函数
  if(getNowWork()==1){
    YString sWorkType=getAsString("劳动");
    if(sWorkType=="采矿"){
      letsCaikuang();
    }
    else if(sWorkType=="打铁"){
      letsDazao();
    }
    else{
      letsWork();
    }
  }
  if(getGiveThing()>0){
    letsSendThing(); //计算送东西的时间
  }
  if(getCityKill() >0){
    letsKillAll(); //计算屠城的时间
  }

  //防止浏览器超时
  if(m_Session) {
    //if((YDateTime::now()-m_Session->getLastMessageTime())>g_Settings->getAsLong("浏览器超时")) {
    if((YDateTime::now()-m_Session->getLastMessageTime())>g_Settings->getsitIEOvertime()) {
      m_Session->message("  ", false, JAVASCRIPT_MSG);
    }
  }
  long spendTime=getSmallTime();

  //关于玩家的发呆，掉线的处理

  //处理过程
  setFreeTime( getFreeTime() + spendTime );
  if ( getBeginArm() != 0) //老人物的退出
  {
    YString atzhuangtai = getStatus();//getAsString("状态");
    if (((atzhuangtai=="")||(atzhuangtai=="坐") ||(atzhuangtai=="躺"))
        &&(getFreeTime() > g_Settings->getsitDazeTime()))//getAsLong("发呆时间")))
         {
            setStatus("发呆中");
            display("您已经闲置了"+(YString)(getFreeTime()/1000)+"秒。");
         };
  }   //新人登陆未完成时没有臂力的属性
  if (getFreeTime() > g_Settings->getsitLoseTime())//getAsLong("掉线时间"))//等待新人的处理
  {
        if (getFreeTime() < (2*g_Settings->getsitLoseTime()))
        {
          display ("你已经空闲了太长时间了。");
          setStatus("掉线中");
          getRoom()->setPlayListQuit(getActorName()+" "+getRoom()->getPlayListQuit());
        }
        else return 1;
  }

  //lp
	//睡觉的处理函数
  long sleeptime=getSleepTime();
  //long busy=getAsLong("繁忙");
  long restore = getPlayerRenew();//getAsLong ("身体恢复速度");
  long expend = getAsLong("食品消耗时间");

  if(sleeptime >= 0) //睡眠的处理
  {
    sleeptime-=spendTime;
    if(sleeptime<0 && (getStatus()=="睡眠中" ))
    {
      setStatus("");
      display("你醒来了。你的气血精力恢复了。");
      if (getBody() < getMaxBody())  setBody(getMaxBody());
      if (getEnergy() < getMaxEnergy())  setEnergy(getMaxEnergy());
      showPhoto ("0","4");
    }
    else  setSleepTime(sleeptime);
  }
  //------------------------------------------------------
  //身体恢复
  //  if(busy != 1 && restore <= 0 ) //加判断的恢复
  YString playerState =getStatus();// getAsString("状态");
  if ( restore <= 0  && (playerState !="晕倒中") && (playerState !="战斗中"))//身体恢复的因素 && ( playerState ==""))//不加判断的恢复
  {
     //身体恢复
     dorenew() ;
     long restime = g_Settings->getsitbodyRenewSpeed();//getAsLong("身体恢复速度") ;
     setPlayerRenew(restime);//
     //set ("身体恢复速度",restime);
     //年龄的增长和变化     注不需要很精确所以和恢复合并
     long onlinetime = getOnlineTime();//getAsLong ("在线时间");
     long lasttime = getLaseOnlineTime();//getAsLong ("上次在线时间");
     if (onlinetime - lasttime  >= 300000 ) //5分钟一次存储
     {
     cmd_save();
      setLaseOnlineTime(onlinetime);// set ("上次在线时间", onlinetime );
       //睡觉间隔
       setPlayerSleepSkip(0);
       //set ("睡觉间隔",0);
     }
     //时间的增长
     float ageuptime = 1;
     if (getActorAge() > 20 ) ageuptime = ( getActorAge() - 20 ) /24 +1;
     if  ((onlinetime+restime) >( g_Settings->getsitAgeUpTime()*ageuptime))//getAsLong("年龄增长速度") )
     {
       ageup();
     }
     else  setOnlineTime(onlinetime+restime);//set ("在线时间",onlinetime+restime);
  }
  else setPlayerRenew(restore -  spendTime);//set ("身体恢复速度" , restore -  spendTime);
  //------------------------------------------------------
  //食品消耗
  if ( expend <=0 )
  {
     long food= getFood() -g_Settings->getsitFoodSpend();//getAsLong("食品消耗");
     long drink= getDrink() -g_Settings->getsitFoodSpend();//getAsLong("食品消耗");
     if (food <= 0) food = 0;
     setFood(food);
     if (drink <= 0) drink = 0;
     setDrink(drink);
     set ("食品消耗时间",g_Settings->getsitFoodSpendTime());//getAsLong("食品消耗时间"));
  }
  else  set ("食品消耗时间",expend-spendTime);
  //-------------------------
  //打坐吐纳处理

  if (  playerState == "打坐"||playerState == "吐纳"  )
  {//打坐处理
    long dazuotime = getDazuoTime();
    if ( dazuotime > 0)
    {
      long gongli = spendTime;
      if (dazuotime < spendTime) gongli=dazuotime;
      setInternalForce((getInternalForce()+(getBaseForce()*gongli)/500));
      setBody((getBody()-(getBaseForce()*gongli)/500));
      setDazuoTime((dazuotime- spendTime));
    }
    else if (playerState == "打坐" )
    {
      setStatus("");
      display ("你打坐完毕站了起来。");
      showPhoto("0","4");
    }
    //-------------------------
    //吐纳处理
    long tunatime = getTunaTime();
    if (tunatime > 0)
    {
      long gongli = spendTime;
      if (tunatime < spendTime) gongli=tunatime;
      setEnergy((getEnergy()+(getBaseForce()*gongli)/500));
      setBody((getBody()-(getBaseForce()*gongli)/500));
      setTunaTime((tunatime - spendTime));
    }
    else if ( playerState == "吐纳" )
    {
      setStatus("");
      display ("你吐纳完毕站了起来。");
      showPhoto("0","4");
    }
  }
  //-------------------------
  //powerup的处理
  /*
  if (getAsLong("powerup时间") <= 0 && (getAsLong("powerup攻击力")!=0))
  {
    set("powerup攻击力",0);
    set("powerup防御力",0);
    display ("运功结束把你的内功收了起来。");
  }
  else
  {
    if (getAsLong("powerup时间")>0)
    set("powerup时间",getAsLong("powerup时间")-spendTime);
  } */
  //玩家说话的频率的显示
  setplaySaySpeed(0);
  return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------


//----------------------------------------------------------------
//事件AfterPropertyChange的默认处理函数
int YPlayer::onAfterPropertyChange(YMUDObject* sender, YString Property,
                                        long oldValue, long newValue)
{
  //调用上级处理函数
  YActor::onAfterPropertyChange(sender,Property,oldValue, newValue);
  //处理人物的攻击力；防御力
  //由于改为m型变量所以人物的属性onAfterPropertyChange没有什么用处所以暂时屏蔽掉
  /*  if (Property == "武器类型" ) playerarmchange();
    else if (Property == "武器") playerarmchange();

    //有关动态显示hp的内容
    if(((Property == "气血")||(Property == "最大气血")||
       (Property == "精力")||(Property == "最大精力")||
       (Property == "内力")||(Property == "最大内力")||
       (Property == "食物")||(Property == "饮水")||
       (Property == "经验")||(Property == "潜能")) &&
       (oldValue!=newValue)) {
       refreshHP();
    } */

    return 1; //必须返回1，表示处理结束
}
//--------------------------------------------------------
//刷新hp的动态显示
void YPlayer::refreshHP(void)
{
  //气血
  long life = getBody();
  if (life <= 0) life = 0;
  if (life > getMaxBody()) life = getMaxBody() ;
  //精力
  long jingli =getEnergy();
  if (jingli > getMaxEnergy()) jingli =getMaxEnergy();
  //内力
  long neili = getInternalForce();
  if (neili > getMaxInternalForce()) neili = getMaxInternalForce();
  display("changeall("+
            (YString) life +","+
            (YString)getMaxBody()+","+
            (YString) jingli +","+
            (YString)getMaxEnergy()+","+
            (YString) neili +","+
            (YString)getMaxInternalForce()+","+
            (YString)getFood()+","+
            (YString)getDrink()+","+
            (YString)getExperience()+","+
            (YString)getPotential()+
            ")", false, JAVASCRIPT_MSG);
}

//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YPlayer::executeCommand(YString command)
{
  //setFreeTime(0);
  YString myip = getplayerip();
  if (g_Settings->getblackip().findStr(myip))
  {
     display ("你的ip被禁止使用了。如果有什么问题请到webmud.xilubbs.com发贴说明");
     return 1;
  }
  YString playerState =getStatus();// getAsString("状态");
  if( playerState == "晕倒中")         //昏迷中
  {
    display("?????????");
    return 1;
  }
  if (getStatus()=="发呆中") setStatus("");  //是否是发呆中
  long wizlevel = getLevel() ; //巫师级别
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="look") retVal=look(cmd);
  else if(commandVerb=="say") retVal=say(cmd);
  else if(commandVerb=="i") retVal=i();
  else if(commandVerb=="ask") retVal=ask(cmd);
  else if(commandVerb=="xuanshang") retVal=xuanshang(cmd);
  else if(commandVerb=="list") retVal=list(cmd);
  else if(commandVerb=="answer") retVal=answer(cmd);
  else if(commandVerb=="tell") retVal=tell(cmd);
  else if(commandVerb=="halt") retVal=halt();
  else if(commandVerb=="turn") retVal=turnoff(cmd);
  else if(commandVerb=="info") retVal=turninfo(cmd);
  else if(commandVerb=="errorchat") retVal=errorChat(cmd);
  else if(commandVerb=="nick") retVal=nick(cmd);
  else if(commandVerb=="describe") retVal=describe(cmd);
  else if (commandVerb=="say*") retVal=sayphiz(cmd);
  else if(commandVerb=="hp") retVal=hp();
  else if(commandVerb=="skills") retVal=skills(cmd);
  else if(commandVerb=="bskills") retVal=bskills(cmd);
  else if(commandVerb=="score") retVal=score();
  else if(commandVerb=="look_b") retVal=look_b(cmd);
  else if(commandVerb=="hp_b") retVal=hp_b();
  else if(commandVerb=="skills_b") retVal=skills_b();
  else if(commandVerb=="score_b") retVal=score_b();
  else if(commandVerb=="i_b") retVal=i_b();
  else if(commandVerb=="fangqi") retVal=fangqi(cmd);
  else if(commandVerb=="save")
       {
          if (getExperience()< 100000 )
          {
            retVal=1;
          }
         else retVal=cmd_save();
       }
  else if(commandVerb=="who") 
       {
         if (getEnergy() < 50)
         {
            display("你的精力还没有恢复，等一下再使用这个命令");
            return 1;
         }
         setEnergy(getEnergy()-50);
         retVal=who(cmd);
       }
  else if(commandVerb=="vote") retVal=vote(cmd); 
// 公用频道
  else if(commandVerb=="chat") retVal=chat(cmd);
  else if(commandVerb=="newbie") retVal=newbie(cmd);
  else if(commandVerb=="rumor") retVal=rumor(cmd);
  else if(commandVerb=="chat*") retVal=chatphiz(cmd);
  else if(commandVerb=="newbie*") retVal=newbiephiz(cmd);
  else if(commandVerb=="rumor*") retVal=rumorphiz(cmd);
  else if(commandVerb=="party") retVal=party(cmd);
  else if(commandVerb=="black") retVal=black(cmd);
  else if(commandVerb=="unblack") retVal=unblack(cmd);
  //忙时不可使用的命令
  else   if ( playerState == "打坐"||playerState == "吐纳"  )
  {
    display ("你正在练功无法使用命令。");
    return 1;
  }
  else if(commandVerb=="go") retVal=go(cmd.getWord());
  else if(commandVerb=="give") retVal=give(cmd);
  else if(commandVerb=="jiaohuan") retVal=exchange(cmd);
  else if(commandVerb=="tongyi") retVal=acceptchange(cmd);
  else if(commandVerb=="get")
       {
         if (getEnergy() < 20)
         {
            display("你的精力还没有恢复，等一下再使用这个命令");
            return 1;
         }
         setEnergy(getEnergy()-20);
         retVal=get(cmd);
       }
  else if(commandVerb=="sleep") retVal=goSleep();
  else if(commandVerb=="beg") retVal=beg(cmd);
  else if(commandVerb=="drop") retVal=drop(cmd);
  else if(commandVerb=="wear") retVal=wear(cmd);
  else if(commandVerb=="unwear") retVal=unwear(cmd);
  else if(commandVerb=="wield") retVal=wield(cmd);
  else if(commandVerb=="unwield") retVal=unwield(cmd);
  else if(commandVerb=="buy") retVal=buy(cmd);
  else if(commandVerb=="eat") retVal=eat(cmd);
  else if(commandVerb=="drink") retVal=drink(cmd);
  else if(commandVerb=="check") retVal=check(cmd);
  else if(commandVerb=="enforce") retVal=enforce(cmd);
  else if(commandVerb=="exert") retVal=exert(cmd);
  else if(commandVerb=="fight") retVal=fight(cmd);
  else if(commandVerb=="touxi") retVal=touxi(cmd);
  else if(commandVerb=="fill") retVal=fill(cmd);
  else if(commandVerb=="follow") retVal=follow(cmd);
  else if(commandVerb=="hit") retVal=hit(cmd);
  else if(commandVerb=="kill") retVal=kill(cmd);
  else if(commandVerb=="killget") retVal=killget(cmd);
  else if(commandVerb=="killge") retVal=killge(cmd);
  else if(commandVerb=="perform") retVal=perform(cmd);
  else if(commandVerb=="knock") retVal=knock(cmd);
  else if(commandVerb=="open") retVal=open(cmd);
  else if(commandVerb=="sit") retVal=sit(cmd);
  else if(commandVerb=="steal") retVal=steal(cmd);
  else if(commandVerb=="qu") retVal=withdraw(cmd);
  else if(commandVerb=="cun") retVal=deposite(cmd);
  else if(commandVerb=="bai") retVal=bai(cmd);
//  else if(commandVerb=="dokill") retVal=dokill();
//  else if(commandVerb=="dofight") retVal=dofight();
//  else if(commandVerb=="dorenew") retVal=dorenew();
  else if(commandVerb=="quit") retVal=quit();
  else if(commandVerb=="cquit") retVal=cquit(cmd);
//  else if(commandVerb=="xue") retVal=xue(cmd);
  else if(commandVerb=="wimpy") retVal=wimpy(cmd);
  else if(commandVerb=="lian") retVal=lian(cmd);
  else if(commandVerb=="enable") retVal=enable(cmd);
  else if(commandVerb=="dazuo") retVal=dazuo(cmd);
  else if(commandVerb=="tuna") retVal=tuna(cmd);
  else if(commandVerb=="我闪！") retVal=playerhelproom(cmd);
  else if(commandVerb=="叫车")retVal=playertaxi(cmd);

  //zhy
  else if(commandVerb=="xue") retVal=xue(cmd); //向师傅学习
  else if(commandVerb=="cunquit") retVal=cunquit(cmd); //向师傅学习
  else if(commandVerb=="quest") retVal=quest(); //申请任务
  else if(commandVerb=="giveup") retVal=giveup(); //放弃任务
  else if(commandVerb=="ge") retVal=ge(cmd); //割首级
  else if(commandVerb=="read") retVal=readBook(cmd); //读书
  else if(commandVerb=="create") retVal=fnCreateFaction(cmd); //创建帮派
  else if(commandVerb=="faction") retVal=fnCmdFaction(cmd);   //查询帮派
  else if(commandVerb=="disband") retVal=fnDisband(cmd);      //解散帮派
  else if(commandVerb=="join") retVal=fnJoinFaction(cmd);     //申请加入帮派
  else if(commandVerb=="agreejoin") retVal=fnAgreeJoin(cmd);  //同意申请
  else if(commandVerb=="fireout") retVal=fnFireOut(cmd);      //开除帮会成员
  else if(commandVerb=="unjoin") retVal=fnUnJoin(cmd);        //退出一个帮派
  else if(commandVerb=="exalt") retVal=fnExalt(cmd);          //设定某人的头衔
  else if(commandVerb=="myfaction") retVal=fnMyFaction(cmd);  //查询本帮信息
  else if(commandVerb=="demise") retVal=fnDemise(cmd);        //任命别人接替帮主
  else if(commandVerb=="factioncolor") retVal=fnSetFactionColor(cmd);   //设置帮派颜色
  else if(commandVerb=="factionbanner") retVal=fnSetFactionBanner(cmd); //设置帮派口号
  else if(commandVerb=="salute") retVal=fnSalute(cmd);        //向帮主致敬
  else if(commandVerb=="invite") retVal=fnInvite(cmd);        //邀请别人参观总舵
  else if(commandVerb=="party2") retVal=fnFactionParty(cmd);  //用帮派频道发言
  else if(commandVerb=="noaccept") retVal=nogive(cmd);  //用帮派频道发言
  //yl
  else if(commandVerb=="move") retVal=move(cmd);
  //lp
  else {
        display ("你说什么？");
        return retVal ;
  }
  if(!retVal) return YActor::executeCommand(command);
  else return retVal;
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YPlayer::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;

  if(!retVal) return YActor::executeCommandAsTarget(executor,command);
  else return retVal;
}
//--------------------------------------------------------
int YPlayer::look(YString sentence)
{
  YString sb=sentence.getWord(); //"sb."
  if (sb == "")
  {
        display(getRoom()->getDisplayName());
        display(getRoom()->getRoomDescribe());//getAsString("描述"));
        getRoom()->showNickActors(this);
        getRoom()->showThings(this);
        return 1;
  }
  else
  {
    YMUDObject* s=getRoom()->findChildActor(sb);         //  房间人物
    YMUDObject* sth=getRoom()->findChildThing(sb);       //   房间物品
    if ( sth == NULL ) sth = findChildThing(sb);         //   身上物品
    if ( s == NULL) s= findChildActor(sb);               //   身上人物
    if(!s && !sth)  //没有东西和人物时的判断
    {
      YString lookroomname;
      if (sb == "e"  || sb == "东" || sb == "east")
      {
        lookroomname = getRoom()->getAsString("东");
      }
      else if (sb == "s" || sb == "南" || sb == "south")
      {
        lookroomname = getRoom()->getAsString("南");
      }
      else if (sb == "w" || sb == "西" || sb == "west")
      {
        lookroomname = getRoom()->getAsString("西");
      }
      else if (sb == "n" || sb == "北" || sb == "north")
      {
        lookroomname = getRoom()->getAsString("北");
      }
      else if (sb == "u" || sb == "上")
      {
        lookroomname = getRoom()->getAsString("上");
      }
      else if (sb == "d" || sb == "下" )
      {
        lookroomname = getRoom()->getAsString("下");
      }
      YRoom* lookroom = (YRoom*) g_Map->getRoom(lookroomname,getRoom());
      if ((lookroomname!= "") && (lookroom != NULL) )
      {
          YString roommiaoshu = lookroom->getRoomDescribe();//getAsString("描述");
          display (roommiaoshu);
          return 1;
      }
      display("你要看什么？");
      return 1;
    }
    else if ( s ) //人物的处理
    {
      YActor* temps = (YActor*)s ; //后边多次用到，所以用temps转换
      YString xianshi = "";
      if(temps->getTitle() != "") xianshi= "【"+temps->getTitle()+"】";
      xianshi = xianshi+temps->getActorName();//getAsString("名字") ;
      if(temps->getNick() != "") xianshi =xianshi + "<br>人称【"+temps->getNick()+"】";
      display (xianshi);
      //
      YString sex = ""; //性别的判断
      //暂时使用sex的描述
      if (temps->getSexString() == "女") sex = "她";
      else if (temps->getSexString() == "动物") sex = "它";
      else sex = "他";
      if ( s == this ) sex = "你";
      //
      if(temps->isTypeOf("YPlayer") == 1){
        YPlayer *tempsplayer=(YPlayer*)temps;
        YString sFactionName=tempsplayer->getFactionName();  //加入帮派
        if(sFactionName != ""){
          display(sex+"是["+sFactionName+"]的["+tempsplayer->getFactionTitle()+"]");
        }
      }
      //
      if(temps->getActorShow() != "") display(""+temps->getActorShow());
      //容貌
      long rongmao=temps->getFeature();
      long addrongmao = temps->getAddFeature();
      long per =rongmao + addrongmao;
      if (per == 0 ) per = 40;
      //物品
      YString armor = temps->getArmor();//getAsString("盔甲");
      YString arm = temps->getWeaponName();//getAsString("武器");
      YString cap = temps->getHat();//getAsString("帽");
      YString cloth = temps->getClothName();//getAsString("衣服");
      YString shoe = temps->getShoe();//getAsString("鞋");
      YString flower = temps->getFlower();//getAsString("花");
      YString nicklace = temps->getNecklace();//getAsString("项链");
      YString ring = temps ->getRing();//>getAsString("戒指");
      YString bangle = temps ->getBangle();//>getAsString("手镯");
      YString jiehuenxiwu = temps->getAsString("结婚信物");

      YString qixuedisplay ;
      if ((temps->getMaxBody())== (temps->getBody()))
      {
        qixuedisplay = sex+"看上去气血充盈，没有受一点伤。";
      }
      long lookqixue = temps->getBody();
      long maxqixue = temps->getMaxBody();
      if ( maxqixue == 0 ) maxqixue = 1;
      long  peoplemaxqixue = temps->getMaxBody();
      if ( peoplemaxqixue  <=0 )   peoplemaxqixue = 150  ;
      float qixue = (lookqixue / (peoplemaxqixue*1.0));
      if (qixue <= 0.2) qixuedisplay = sex+g_Settings->getBodyDisplay5();//getAsString("平时气血形容5"); // "有如风中之烛，随时都有可能倒下。";
      else if (qixue <= 0.4) qixuedisplay = sex+ g_Settings->getBodyDisplay4();//getAsString("平时气血形容4"); //"的伤势很严重了，再不休息会死的啊。";
      else if (qixue <= 0.6) qixuedisplay = sex+ g_Settings->getBodyDisplay3();//getAsString("平时气血形容3") ;//"的伤势有些严重了，要好好休息了。";
      else if (qixue <= 0.8 ) qixuedisplay = sex+ g_Settings->getBodyDisplay2();//getAsString("平时气血形容2"); //"受了一点轻伤，没有什么关系。";
      else if (qixue <= 0.9 ) qixuedisplay = sex+ g_Settings->getBodyDisplay1();//getAsString("平时气血形容1"); //"看上去气血充盈，受了一点小伤。";
      else qixuedisplay = sex+ g_Settings->getBodyDisplay0();//getAsString("平时气血形容0") ;//"看上去气血充盈，没有受一点伤。";
      //回复正常的使用sex
      if (temps->getSexString() == "女") sex = "女";
      else if (temps->getSexString() == "动物") sex = "动物";
      else sex = "男";
      long old = temps->getActorAge();  //年龄的判断
      if (old == 0 && isTypeOf("YNPC")) old = 30;
      if (this != s )
      {
        temps->display(getDisplayName()+"正在偷偷的看你。");
        old = (old /10)* 10;
        if (sex == "男")
        {
          display("他大约"+LongToChinese(old)+"多岁。");
          if (per >= 80) display("他"+g_Settings->getmenFeature80());
          //"长得长得宛如玉树临风，风流倜傥，顾盼之间，神采飞扬。真正是人中龙凤！\n");
          else if ((per >= 70) && (per < 80))display("他"+g_Settings->getmenFeature70());
          //"长得英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。");
          else if ((per >= 60) && (per < 70))display("他"+g_Settings->getmenFeature60());
          //"长得相貌英俊，仪表堂堂。骨格清奇，丰姿非俗。");
          else if ((per >= 50) && (per < 60))display("他"+g_Settings->getmenFeature50());
          //"长得五官端正。");
          else if ((per >= 40) && (per < 50))display ("他"+g_Settings->getmenFeature40());
          //"长得相貌平平。没什么好看的。");
          else if (per < 40)display ("他"+g_Settings->getmenFeature30());
          //"长的...有点对不住别人。");
          display (qixuedisplay);
          if((armor != "") || (arm!="") ||(cap !="") || (shoe !=""))
          {
            display("他装备着");
          }
        }
        else if (sex == "女")
        {
          display("她大约"+LongToChinese(old)+"多岁。");
          if (per >= 80) display("她"+g_Settings->getwemenFeature80());
          //"有倾国倾城之貌，容色丽都，娇艳绝伦，堪称人间仙子！长发如云，肌肤胜雪，风华绝代，不知倾倒了多少英雄豪杰。");
          else if ((per >= 70) && (per < 80))display("她"+g_Settings->getwemenFeature70());
          //"长得清丽绝俗，风姿动人。有沉鱼落雁之容，避月羞花之貌！俏脸生春，妙目含情，顾盼神飞，轻轻一笑，不觉让人怦然心动。");
          else if ((per >= 60) && (per < 70))display("她"+g_Settings->getwemenFeature60());
          //"长得肤如凝脂，眉目如画，风情万种，楚楚动人。当真是我见犹怜！");
          else if ((per >= 55) && (per < 60))display("她"+g_Settings->getwemenFeature55());
          //"长得容色秀丽，面带晕红，眼含秋波。举手投足之间，确有一番风韵。");// 玉面娇容花含露，纤足细腰柳带烟。
          else if ((per >= 50) && (per < 55))display("她"+g_Settings->getwemenFeature50());
          //"长得气质高雅，面目姣好，虽算不上绝世佳人，也颇有几份姿色。");
          else if ((per >= 45) && (per < 50))display("她"+g_Settings->getwemenFeature45());
          //"长得相貌平平，还看得过去。");
          else if ((per >= 40) && (per <45))display("她"+g_Settings->getwemenFeature40());
          //"长得的相貌嘛...马马虎虎吧。");
          else if (per < 40)display( "咦，她"+g_Settings->getwemenFeature30());
          //"长得和无盐有点相似耶。");
          display (qixuedisplay);
          if((armor != "") || (arm!="") ||(cap !="") || (shoe !=""))
          {
            display ("她装备着");
          }
         }
         else {}//动物
         if (armor != "") display ("<font blue>囗"+armor+"</font>");
         if (cloth != "") display ("<font blue>囗"+cloth+"</font>");
         if (arm!="")     display ("<font blue>囗"+arm+"</font>");
         if (cap !="")    display ("<font blue>囗"+cap+"</font>");
         if (shoe !="")   display ("<font blue>囗"+shoe+"</font>");
         if (armor =="" && cloth =="" && (sex == "男")) display ("他什么也没有穿。");
         else if (armor =="" && cloth =="" && (sex == "女")) display ("她什么也没有穿。");
         else ;
         if (sex == "男" )
         {
          if ((flower != "")||(nicklace!="")||( ring !="")|| (jiehuenxiwu != "") || (bangle != ""))
          {
            display("他戴着");
          }
          sex = "他";
         }
         else if (sex == "女")
         {
          if ((flower != "")||(nicklace!="")||( ring !="")|| (jiehuenxiwu != "") || (bangle != ""))
          {
            display ("她戴着");
          }
          sex = "她";
         }
         else {}//动物的处理
         if(flower != "") display(flower);
         if(nicklace!="") display(nicklace);
         if(( ring !="")) display( ring );
         if(( bangle !="")) display( bangle );
         if (jiehuenxiwu != "") display (jiehuenxiwu) ;
         //个人描述的显示
         if (getDescribe() != "" ) display ( getDescribe() ) ;
         s->executeCommandAsTarget(this,"look "+sb);
      }
      else
      {
        display("你是一位"+LongToChinese(old)+"岁的"+sex+"性。");
        if (temps->getSexString() != "女") sex = "男";
        else sex = "女";
        if (sex == "女")
        {
          if (per >= 80) display("你"+g_Settings->getwemenFeature80());
          //"有倾国倾城之貌，容色丽都，娇艳绝伦，堪称人间仙子！<br>长发如云，肌肤胜雪，风华绝代，不知倾倒了多少英雄豪杰。");
          else if ((per >= 70) && (per < 80))display("你"+g_Settings->getwemenFeature70());
          //"长的清丽绝俗，风姿动人。有沉鱼落雁之容，避月羞花之貌！\n俏脸生春，妙目含情，顾盼神飞，轻轻一笑，不觉让人怦然心动。");
          else if ((per >= 60) && (per < 70))display("你"+g_Settings->getwemenFeature60());
          //"长的肤如凝脂，眉目如画，风情万种，楚楚动人。当真是我见犹怜！");
          else if ((per >= 55) && (per < 60))display("你"+g_Settings->getwemenFeature55());
          //"长的容色秀丽，面带晕红，眼含秋波。举手投足之间，确有一番风韵。");// 玉面娇容花含露，纤足细腰柳带烟。
          else if ((per >= 50) && (per < 55))display("你"+g_Settings->getwemenFeature50());
          //"长的气质高雅，面目姣好，虽算不上绝世佳人，也颇有几份姿色。");
          else if ((per >= 45) && (per < 50))display("你"+g_Settings->getwemenFeature45());
          //"长的相貌平平，还看得过去。");
          else if ((per >= 40) && (per <45))display("你"+g_Settings->getwemenFeature40());
          //"长的相貌嘛...马马虎虎吧。");
          else if (per < 40)display( "咦，你"+g_Settings->getwemenFeature30());
          //"长的长得和无盐有点相似耶。");
        }
        else
        {
          if (per >= 80) display("你"+g_Settings->getmenFeature80());
          //"长得宛如玉树临风，风流倜傥，顾盼之间，神采飞扬。真正是人中龙凤！\n");
          else if ((per >= 70) && (per < 80))display("你"+g_Settings->getmenFeature70());
          //"长的英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。");
          else if ((per >= 60) && (per < 70))display("你"+g_Settings->getmenFeature60());
          //"长的相貌英俊，仪表堂堂。骨格清奇，丰姿非俗。");
          else if ((per >= 50) && (per < 60))display("你"+g_Settings->getmenFeature50());
          //"长的五官端正。");;
          else if ((per >= 40) && (per < 50))display ("你"+g_Settings->getmenFeature40());
          //"长的相貌平平。没什么好看的。");
          else if (per < 40)display ("你"+g_Settings->getmenFeature30());
          //"长的...有点对不住别人。");
        }
        display (qixuedisplay);
        if((armor != "") || (arm!="") ||(cap !="") || (shoe !="") || (cloth != ""))
        {
          display("你装备着");
        if (armor != "") display ("<font blue>囗"+armor+"</font>");
        if (cloth != "") display ("<font blue>囗"+cloth+"</font>");
        if (arm!="")     display ("<font blue>囗"+arm+"</font>");
        if (cap !="")    display ("<font blue>囗"+cap+"</font>");
        if (shoe !="")   display ("<font blue>囗"+shoe+"</font>");
        }
        else display ("你什么也没有装备。");
        YString jiehuenxiwu = getAsString("结婚信物");
        if ((flower != "")||(nicklace!="")||( ring !="")||( bangle !="")|| (jiehuenxiwu!=""))
        {
          display("你戴着");
          if(flower != "") display(flower);
          if(nicklace!="") display(nicklace);
          if(( ring !="")) display( ring );
          if(( bangle !="")) display( bangle );
          if (jiehuenxiwu != "") display (jiehuenxiwu);
         //个人描述的显示
         if (getDescribe() != "" ) display ( getDescribe() ) ;
        }
      }
    }
    else if (sth)  //物品的处理
    {
      YString miaoshu= ((YThing*)sth)->getDescribe();//getAsString("描述") ;
      YString thingname = ((YThing*)sth)->getThingFontName();//getAsString("显示名字");
      if ( thingname != "")
       display("这是"+thingname);
      else if (miaoshu != "") display (miaoshu);
      else  display("这是"+sb);
    }
    else display ("你要看什么啊？");
    return 1;
  }
}
//--------------------------------------------------------
//显示房间标题和描述(Javascript)
int YPlayer::look_b(YString sentence)
{
  display("showroom(\""+
          getRoom()->getRoomName().toInnerString()+"\",\""+
          getRoom()->getRoomDescribe().toInnerString()+"\")",
          false,JAVASCRIPT_MSG);
  getRoom()->showNickActors(this);
  getRoom()->showThings(this);
  return 1;
}
//--------------------------------------------------------
//give (count) sth. to sb.
int YPlayer::give(YString sentence)
{
  YString cmd=sentence;
  YString s=sentence.getWord(); //"sth. or count"
  YAbstractThing* sth=findChildThing(s);
  YAbstractActor* begive=findChildActor(s);
  resumWeight();
  if(!sth && !begive ) {
    display("你没有这件物品。");
    return 1;
  }
  YString s2=sentence.getWord(); //"to"or"数量"
  long count=1;
  if(s2!="to") //带数量的物品判断
  {
    //处理人物给的数量
    if ( begive )
    {
      display ("你不可能有那么多同样的人物把，，");
      return 1;
    }
    if((count=s2.toLong())>0 );//count
    else count=1;
    YString  IsTo = sentence.getWord();
    if (IsTo != "to")
    {
      display("格式错误。(give 物品名 (数量) to 人名)");
      return 1;
    }
  }
  YString s1=sentence.getWord(); //"sb."
  YAbstractActor* sb=getRoom()->findChildActor(s1);
  if((!sb)||(!sb->isTypeOf("YActor"))) //对被给的人物和类别的判断
  {
    display("你要把东西给谁？");
    return 1;
  }
  else if (sb == this)
  {
    display ("自己的东西再怎么给都是自己的啊！");
    return 1;
  }
  //npc的处理
  if(sb->isTypeOf("YNPC"))
  {
     sb->executeCommandAsTarget(this,"give "+cmd);
     return 1;
  }
  else if (sb->isTypeOf("YPlayer"))
  {
    if (((YPlayer*)sb)->getNoAccept() != 0)
    {
       display("对方不打算接受你的东西！");
       return 1;
    }
   ((YPlayer*)sb)->resumWeight();
  }
//传递物品 对物体的重量和是人物的传递
  if (begive)     //人物的处理
  {
     if (((YActor*)sb)->getStatus() !="晕倒中" )
     {
       if ( ((YActor*)begive)->getActorWeight() == 0 ) ((YActor*)begive) -> setActorWeight(100);
       if (((YPlayer*)sb)->getWeight()+begive->getAsLong("重量") <= ((YPlayer*)sb)->getMaxWeight())
       {
         getRoom()->giveChildTo(begive,sb);
         YString msg=getDisplayName()+"把"+begive->getDisplayName()+"递给"+sb->getDisplayName();
         display("你把"+begive->getDisplayName()+"递给了"+sb->getDisplayName());
         getRoom()->getRoomChat()->talk(NULL, msg,this,sb);
       }   //重量的处理
       else display (s1+"身上的东西太多了，不能收下"+s);
     }   //接受的人物是否清醒
     else display ("你先要把"+s1+"弄醒才行。");
  }
  else if (sth)     //物体的处理
  {
    YString msg;
    if (count > sth->getCount() )
    {
      count = sth->getCount();
    }
    if (count <= 0) count = 1;
    if ( ((YThing*)sth)->getThingWeight() == 0 ) ((YThing*)sth)->setThingWeight(5);
    if (((YPlayer*)sb)->getWeight()+((((YThing*)sth)->getThingWeight())*count) <= ((YPlayer*)sb)->getMaxWeight())
    {
       YString liangci = ((YThing*)sth)->getQuantifier();//getAsString("量词");
       if ( liangci == "" ) liangci ="把";
       YString thingDisplayName =  sth->getDisplayName();
       if(giveChildTo(sth, sb, count))
       {
         msg=getDisplayName()+"送给"+sb->getDisplayName()
         +" "+YString(count)+" "+liangci
         +thingDisplayName+"。";
         getRoom()->getRoomChat()->talk(NULL, msg, this, sb);
         msg="你送给"+sb->getDisplayName()
         +" "+YString(count)+" "+liangci
         +thingDisplayName+"。";
         display(msg);
         msg=getDisplayName()+"送给你 "+YString(count)+" "+
         liangci +thingDisplayName+"。";
         sb->display(msg);
         //判断是不是所使用的物品和数量是否全部给出
         //附加容貌物品的递交
//         ActorAddFeatureChange();     //人物附加容貌变化
         ActorAddRecoveryChange();     //人物附加防御力力变化
       }
       YActor::executeCommandAsTarget(this,"give "+s+" to "+s1);
    }
    else
    {
       display(s1+"身上带的东西太多了，不能收下你的东西");
       sb->display("你身上带的东西太多了，不能收下"+getActorName()+"给你的东西");
    }
  }
  else display("递交没有成功。");
  return 1;
}
//--------------------------------------------------------
//exchange sth. count to sb. sth count
int YPlayer::exchange(YString sentence)
{
  //用于两个玩家交换的程序，现在没有用处注释
  /*
   YString mething = sentence.getWord();
   long mecount = 0 ;
   YString isto = sentence.getWord();  //判断to
   if (isto == "to") //判断数量
   {
   }
   else
   {
       mecount = isto.toLong();
       if (mecount < 0 ) mecount =1;
       isto = sentence.getWord();  //判断to
   }
   YString othname =  sentence.getWord();//人名
   YAbstractActor* begive=findChildActor(othname);
   if (begive)
   {
        YString  sbthing = sentence.getWord();//物品名称
        YString  temp = sentence.getWord();// 物品数量
        long  sbcount = temp.toLong();
        if (sbcount <= 0) sbcount =1;
        set ("交换对象",othname); //对方写交换者
        set ("交出物品",mething);
        set ("交出物品数量",mecount);
        set ("换回物品",sbthing);
        set ("换回物品数量",sbcount);
        display ("你准备用"+(YString)mecount+mething+"去换"+othname+"的"+(YString)sbcount+sbthing);
        begive->display (getActorName()+"准备用"+(YString)mecount+mething+"去换你的"+(YString)sbcount+sbthing);
   }
   else display("你要和谁交换物品？");
   */
   return 1;
}
//--------------------------------------------------------
//同意兑换
int YPlayer::acceptchange(YString sentence)
{
  //交换物品的程序，现在无用注释
  /*
  YString name = sentence.getWord();
  YAbstractActor* begive=findChildActor(name);
  if (begive)
  {
     if (begive->getAsString("交换对象") == getActorName())//getAsString("名字"))
     {
        YString mething,sbthing;
        long mecount,sbcount;
        mething = begive->getAsString("交出物品");
        mecount = begive->getAsLong("交出物品数量");
        sbthing = begive->getAsString("换回物品");
        sbcount = begive->getAsLong("换回物品数量");
        YAbstractThing* sth = begive->findChildThing(mething);
        if (sth)
        {
          if (sth->getCount() > mecount)
          {
            if ( mecount == sth->getCount() && (mething == begive->getAsString("武器")
                 || mething == begive->getAsString("盔甲") || mething == begive->getAsString("衣服")
                 || mething == begive->getAsString("鞋") || mething == begive->getAsString("帽子")
                 || mething == begive->getAsString("花") || mething == begive->getAsString("戒指")
                 || mething == begive->getAsString("项链")) )
            {
              display ("他身上装备着这件物品。");
              begive->display("你身上装备的物品不能给人");
              return 1;
            }
            YAbstractThing* mysth = begive->findChildThing(sbthing);
            if (mysth)
            {
               if (mysth->getCount() > sbcount)
               {

                 if ( mecount == mysth->getCount() && (mething == getAsString("武器")
                    || mething == getAsString("盔甲") || mething == getAsString("衣服")
                    || mething == getAsString("鞋") || mething == getAsString("帽子")
                    || mething == getAsString("花") || mething == getAsString("戒指")
                    || mething == getAsString("项链")) )
                 {
                    display ("你身上装正备着这件物品。");
                    return 1;
                 }
                 //给物品
                 if(giveChildTo(mysth, begive, sbcount) &&
                    begive->giveChildTo(sth , this , mecount))
                 {
                   display ("交换成功。");
                   begive-> display ("交换成功。");
                 }
               }
               else display ("你没有这么多的物品。");
            }
            else display ("你没有这件物品。");
          }
          else display ("他没有这么多的物品。");
        }
        else display ("他没有这件物品。");
     }
     else display (name+"并没有同意和你交换东西啊！");
  }
  else display ("你要同意谁的要求啊？");
  */
  return 1;
}
//订阅新得门派频道
int YPlayer::setMeipaichat(void)
{
      YString menpai = getSchool();//getAsString("门派");
      if (menpai == "华山派") {g_HuaShanChat->subscribe(this);   m_menpaichat = g_HuaShanChat;}
      else if (menpai == "武当派") { g_WuDangChat->subscribe(this);m_menpaichat = g_WuDangChat;}
      else if (menpai == "古墓派") { g_GuMuChat->subscribe(this);   m_menpaichat = g_GuMuChat;}
      else if (menpai == "少林派")  { g_ShaoLinChat->subscribe(this);  m_menpaichat = g_ShaoLinChat;}
      else if (menpai == "峨嵋派")  { g_EMeiChat->subscribe(this); m_menpaichat = g_EMeiChat;}
      else if (menpai == "丐帮")  { g_GaiBangChat->subscribe(this);  m_menpaichat = g_GaiBangChat;}
      else if (menpai == "白驼山庄")  { g_BaiTuoChat->subscribe(this); m_menpaichat =g_BaiTuoChat ;}
      else if (menpai == "明教") {g_MingJiaoChat->subscribe(this); m_menpaichat = g_MingJiaoChat ;}
      else if (menpai == "血刀门") {g_XueDaoChat->subscribe(this); m_menpaichat = g_XueDaoChat ;}
      else if (menpai == "侠客岛") {g_XiaKeChat->subscribe(this); m_menpaichat = g_XiaKeChat ;}
      else if (menpai == "日月神教") {g_RiYueChat->subscribe(this); m_menpaichat = g_RiYueChat ;}
      else if (menpai == "大理") {g_DaLiChat->subscribe(this); m_menpaichat = g_DaLiChat ;}
      else if (menpai == "桃花岛") {g_TaoHuaChat->subscribe(this); m_menpaichat = g_TaoHuaChat ;}
      else if (menpai == "红花会") {g_HongHuaChat->subscribe(this); m_menpaichat = g_HongHuaChat ;}
      else if (menpai == "灵鹫宫") {g_LingJiuChat->subscribe(this); m_menpaichat = g_LingJiuChat ;}
      else if (menpai == "神龙教") {g_ShenLongChat->subscribe(this); m_menpaichat = g_ShenLongChat ;}
      else { m_menpaichat = NULL ;}
      return 1;
}
//-------------------------------------------------
//say word   说话
int YPlayer::say(YString word)
{
  //说话时间限制
  if (getplaySaySpeed() == 1 )
  {
    display("你说话的速度太快了，先歇一歇吧。。");
    return 3;
  }
  setplaySaySpeed(1);
  //处理表情系统
  if(word[0]=='*') { //emote
    word.erase(0,1);
    YString emote=word.getWord();
    YString targetName=word.getWord();
    YAbstractActor* sb;
    if(targetName!="") {
      sb=getRoom()->findChildActor(targetName);
      if(!sb) {
        display("你要使用什么命令？");
        return 1;
      }
    }
    else sb=NULL;

    display(g_Emote->translate(emote,this,sb,YEmote::SELF));
    if((sb!=NULL)&&(sb!=this)) sb->display(g_Emote->translate(emote,this,sb,YEmote::TARGET));
    getRoom()->getRoomChat()->talk(this, g_Emote->translate(emote,this,sb,YEmote::OTHER),this, sb);
    if(g_Emote->translate(emote,this,sb,YEmote::SELF) == "") display("你说什么？");
    return 1;
  }
  if ( repeat( "上次发言" , word) == 1 ) return 1;
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  if (word.size() > 100)
  {
    display ("你的话太多了，少说点字。");
    return 1;
  }
  getRoom()->getRoomChat()->talk(this,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
//-------------------------------------------------
//wizchat 巫师频道
int YPlayer::wizchat(YString word)
{
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  word ="<font color=" + g_Settings->getwizChatColor() + ">【系统消息】" +
        getActorName()+":"+word+"</font>" ;
  g_SystemChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
//------------------------------------------------
//查看频道是否被关闭
int YPlayer::checkclose(void) //查看频道是否被关闭
{
  if (getplaySaySpeed() == 1 )
  {
    display("你说话的速度太快了，先歇一歇吧。。");
    return 3;
  }
  //巫师关闭频道
  if (getWizCloseChat() == 1)
  {
    display("你的公共频道已被巫师关闭。");
    return 1 ;
  }
  //玩家关闭频道
  if (getPlayCloseChat() == 1)
  {
    display("你的公共频道已被玩家关闭。");
    return 2 ;
  }
  if (getEnergy() < 20)
  {
     display("你已经没有精力说话了。");
     return 3;
  }
  setEnergy(getEnergy()-20);
  setplaySaySpeed(1);
  return 0;
}
//chat 公用频道
int YPlayer::chat(YString word)
{
  if ( checkclose() != 0 ) return 1;
  //自己关闭频道
  if ( getCloseChat()==1)
  {
    g_NormalChat->subscribe(this);
    setCloseChat(0);
  }
  //重复发言
  if ( repeat( "上次发言" , word) == 1 ) return 1;
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  if (word.size() > 100)
  {
    display ("你的话也太长了点吧。");
    return 1;
  }
  if (isTypeOf("YWizard")) word ="<font color=#9932cc>【闲聊】" + getActorName()+":"+word+"</font>" ;
  else word="<font color = #009acd>【闲聊】</font><font color=" + g_Settings->getchatColor() + ">" +
        getActorName()+":"+word+"</font>" ;
  g_NormalChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
//-------------------------------------------------
//menpai 门派频道
int YPlayer::party(YString word)
{
  if  ( getMeipaichat()==NULL) display ("你还没有门派！！");
  else
  {
    if ( checkclose() != 0 ) return 1;
    //自己关闭频道
    if ( getCloseParty()==1)
    {
      if(getMeipaichat()) getMeipaichat()->subscribe(this);
      setCloseParty(0);
    }
    //重复发言
    if ( repeat( "上次发言" , word) == 1 ) return 1;
    //查找替换< >   注：由于>在页面没反映所以不与处理
    word = changeword (word);
    if (word.size() > 100)
    {
      display ("你的话也太长了点吧。");
      return 1;
    }
    word="<font color=#00688b >【门派】</font><font color=" + g_Settings->getpartychatColor() + ">" +
        getActorName()+":"+word+"</font>" ;
    getMeipaichat()->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  }
  return 1;
}
//-------------------------------------------------
//newbie 新手频道
int YPlayer::newbie(YString word)
{
  if ( checkclose() != 0 ) return 1;
  //自己关闭频道
  if ( getCloseNewbie()==1 )
  {
    g_NewUserChat->subscribe(this);
    setCloseNewbie(0);
  }
  //判断新手的年龄
  if (isnewbie() == 0)
  {
      display ("你的年龄已经不再是新手了。");
      return 1;
  }
  //说话重复
  if ( repeat( "上次发言" , word) == 1 ) return 1;
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  if (word.size() > 100)
  {
    display ("你的话也太长了点吧。");
    return 1;
  }
  g_NewUserChat->talk(NULL,"<font color=#C9C9C9>【新手】</font><font color="+g_Settings->getnewbieChatColor()
  +">"+getActorName()+":"+word+"</font>",NULL,NULL,CHANNEL_MSG);
  return 1;
}
//-------------------------------------------------
//rumor 谣言频道
int YPlayer::rumor(YString word)
{
  if ( checkclose() != 0 ) return 1;
  //自己关闭频道
  if ( getCloseRum()==1 )
  {
    g_RumorChat->subscribe(this);
    setCloseRum(0);
  }
  //重复发言
  if ( repeat( "上次发言" , word) == 1 ) return 1;
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  if (word.size() > 100)
  {
    display ("你的话也太长了点吧。");
    return 1;
  }
  if ((rand() % 100) > 10 )
  {
    g_RumorChat->talk(NULL,"<font color=#daa520 >【谣言】</font><font color="+g_Settings->getrumorChatColor()+">"
    +"某人: "+word+"</font>",NULL,NULL,CHANNEL_MSG);
    YRoom* useRoom =(YRoom*) g_Map->getRoom("/room/鬼门关",getRoom());
    if (useRoom)
    {
        YActor* finger = (YActor*)useRoom->findChildActor("白无常");
        if (finger)
        {
          long zhaoyao = finger ->getAsLong ("造谣次数");
          zhaoyao = zhaoyao % 10;
          if ( zhaoyao == 1 ) finger ->set ("造谣1",getActorName()+"造谣："+word);
          else if ( zhaoyao == 2 ) finger ->set ("造谣2",getActorName()+"造谣："+word);
          else if ( zhaoyao == 3 ) finger ->set ("造谣3",getActorName()+"造谣："+word);
          else if ( zhaoyao == 4 ) finger ->set ("造谣4",getActorName()+"造谣："+word);
          else if ( zhaoyao == 5 ) finger ->set ("造谣5",getActorName()+"造谣："+word);
          else if ( zhaoyao == 6 ) finger ->set ("造谣6",getActorName()+"造谣："+word);
          else if ( zhaoyao == 7 ) finger ->set ("造谣7",getActorName()+"造谣："+word);
          else if ( zhaoyao == 8 ) finger ->set ("造谣8",getActorName()+"造谣："+word);
          else if ( zhaoyao == 9 ) finger ->set ("造谣9",getActorName()+"造谣："+word);
          else if ( zhaoyao == 0 ) finger ->set ("造谣10",getActorName()+"造谣："+word);
          finger -> set ("造谣次数", zhaoyao+1);
        }
        else g_applog->write("[YPlayer:谣言]房间鬼门关人物白无常不能掉入。");
    }
    else g_applog->write("[YPlayer:谣言]房间鬼门关不能掉入。");
  }
  else
  g_RumorChat->talk(NULL,"<font color=#daa520 >【谣言】</font><font color="+g_Settings->getrumorChatColor()+">"
  +getActorName()+":"+word+"</font>",NULL,NULL,CHANNEL_MSG);
  return 1;
}
//-------------------------------------------------
//chat* 公用频道
int YPlayer::chatphiz(YString word)
{
    if ( checkclose() != 0 ) return 1;
    if ( getCloseChat()==1 ) g_NormalChat->subscribe(this);
    YString emote=word.getWord();
    YString targetName=word.getWord();
    YAbstractActor* sb;
    if(targetName!="")
    {
      sb=g_PlayerManager->getActor(targetName);
      if(!sb) {
        display("你说什么啊？");
        return 1;
      }
    }
    else sb=NULL;
    word = g_Emote->translate(emote,this,sb,YEmote::OTHER) ;
    if(word == "")
    {
      if (emote != "")
      {
        int jos = 0;
        while (emote.find('&',jos)!=YString::npos)
        {
          jos = emote.find('&',jos)+1;
          if (emote[jos] == 'm' )
          {
            emote.erase(jos-1,2);            //替换
            emote.insert(jos-1,getActorName());//getAsString("名字"));     //插入
          }
          else if (emote[jos] =='o')
          {
            emote.erase(jos-1,2);            //替换
            emote.insert(jos-1,targetName);     //插入
          }
        }
        word =getActorName()+emote ;
      }
      else
      {
        display("你要表示什么啊？");
        return 1;
      }
    }
    //重复发言
    if ( repeat( "上次表情" , word) == 1 ) return 1;
    g_NormalChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
    return 1;
}
//-------------------------------------------------
//newbie* 新手频道
int YPlayer::newbiephiz(YString word)
{
    if ( checkclose() != 0 ) return 1;
    if ( getCloseNewbie()==1 ) g_NormalChat->subscribe(this);
    if (isnewbie() == 0)
    {
      display ("你的年龄已经不再是新手了。");
      return 1;
    }
    YString emote=word.getWord();
    YString targetName=word.getWord();
    YAbstractActor* sb;
    if(targetName!="")
    {
      sb=g_PlayerManager->getActor(targetName);
      if(!sb) {
        display("没找准对象别乱发表情！");
        return 1;
      }
    }
    else sb=NULL;
    word = g_Emote->translate(emote,this,sb,YEmote::OTHER) ;
    if(word == "")
    {
      display("你要表示什么啊？");
      return 1;
    }
    //重复发言
    if ( repeat( "上次表情" , word) == 1 ) return 1;
    word = "<font color="+g_Settings->getnewbieChatColor()
  +">【新手】"+getActorName()+":"+word+"</font>";
    g_NewUserChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
    return 1;
}
//-------------------------------------------------
//rumor* 谣言频道
int YPlayer::rumorphiz(YString word)
{
    if ( checkclose() != 0 ) return 1;
    if ( getCloseRum()==1 ) g_NormalChat->subscribe(this);
    YString emote=word.getWord();
    YString targetName=word.getWord();
    YAbstractActor* sb;
    if(targetName!="")
    {
      sb=g_PlayerManager->getActor(targetName);
      if(!sb) {
        display("没找准对象别乱发表情！");
        return 1;
      }
    }
    else sb=NULL;
    if ((rand() % 100) >25)
    word = g_Emote->Strtranslate(emote,"某人",sb,YEmote::OTHER);
    else
    word = g_Emote->translate(emote,this,sb,YEmote::OTHER);
    if(word == "")
    {
      display("你要表示什么啊？");
      return 1;
    }
  //重复发言
  if ( repeat( "上次表情" , word) == 1 ) return 1;
  word = "<font color="+g_Settings->getrumorChatColor()+">【谣言】" + word + "</font>";
  g_RumorChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
//-------------------------------------------------
//屋内表情
int YPlayer::sayphiz(YString word)
{
    YString emote=word.getWord();
    YString targetName=word.getWord();
    YAbstractActor* sb;
    if(targetName!="") {
      sb=getRoom()->findChildActor(targetName);
      if(!sb) {
        display("你要使用什么命令？");
        return 1;
      }
    }
    else sb=NULL;
    display(g_Emote->translate(emote,this,sb,YEmote::SELF));
    if((sb!=NULL)&&(sb!=this)) sb->display(g_Emote->translate(emote,this,sb,YEmote::TARGET));
    getRoom()->getRoomChat()->talk(this, g_Emote->translate(emote,this,sb,YEmote::OTHER),this, sb);
    if(g_Emote->translate(emote,this,sb,YEmote::SELF) == "") display("你说什么？");
    return 1;

}
//-------------------------------------------------
//关闭频道
int YPlayer::turnoff(YString sentence)
{
        if( sentence == "chat" || sentence == "chat*" )
        {
                g_NormalChat->unsubscribe(this);
                setCloseChat(1);
                display ("你关闭了闲聊频道。");
        }
        else if  ( sentence == "newbie" || sentence == "newbie*" )
        {
                g_NewUserChat->unsubscribe(this);
                setCloseNewbie(1);
                display ("你关闭了新手频道。");
        }
        else if  ( sentence == "rumor" || sentence == "rumor*" )
        {
                g_RumorChat->unsubscribe(this);
                setCloseRum(1);
                display ("你关闭了谣言频道。");
        }
        else if  ( sentence == "info" )
        {
                g_InfoChat->unsubscribe(this);
                set("关闭信息频道",1);
                display ("你关闭了信息频道。");
        }
        else if  ( sentence == "menpai" )
        {
                if (getMeipaichat() == NULL) {display ("你没有门派！"); return 1;}
                getMeipaichat()->unsubscribe(this);
                setCloseParty(1);
                display ("你关闭了门派频道。");
        }
        //玩家帮派
        else if(sentence == "faction"){
          if(!getFactionChat()){
            display("你没有加入玩家帮派！");
            return 1;
          }
          getFactionChat()->unsubscribe(this); //退订
          setCloseFactionParty(1);
          display ("你关闭了帮会频道。");
        }
        //玩家帮派结束
        else if  ( sentence == "all")
        {
                g_NormalChat->unsubscribe(this);
                setCloseChat(1);
                g_RumorChat->unsubscribe(this);
                setCloseRum(1);
                g_NewUserChat->unsubscribe(this);
                setCloseNewbie(1);
                g_InfoChat->unsubscribe(this);
                set("关闭信息频道",1);
                if (getMeipaichat() == NULL) ;
                else getMeipaichat()->unsubscribe(this);
                setCloseParty(1);
                //玩家帮派
                if(getFactionChat()){
                  getFactionChat()->unsubscribe(this);
                  setCloseFactionParty(1);
                }
                //玩家帮派结束
                display ("你关闭了所有频道。");
        }
        else display("你要关闭什么频道啊？") ;
        return 1;
}
//-------------------------------------------------
//关闭开启信息频道
int YPlayer::turninfo(YString sentence)
{
    YString about = sentence.getWord();
    if (about == "on")
    {
                g_InfoChat->subscribe(this);
                display ("你开启了信息频道。");
    }
    else if (about == "off")
    {
                g_InfoChat->unsubscribe(this);
                display ("你关闭了信息频道。");
    }
    else display ("正确格式为info on 或 info off.");
    return 1;
}

//提升玩家所会技能的等级
int YPlayer::playerworkup(YString sentence)
{
  YString basic=sentence.getWord(); //"劳动技能"
  setSkillLevel(basic,getSkillLevel(basic)+1);
  display ("<font color=red>你的劳动技能"+basic+"等级上升了。</font>");
//  playerhpchange();
  return 1;
}

//-------------------------------------------------
//----------------------------------------------------------------------------
//lp
//提升玩家所会技能的等级
int YPlayer::playerlevelup(YString sentence)
{
  YString basic=sentence.getWord(); //"武功"
  setSkillLevel(basic,getSkillLevel(basic)+1);
  display ("<font color=red>你的"+basic+"等级上升了。</font>");
  playerhpchange();
  return 1;
}
//--------------------------------------------------------------
//lp
//攻击力，防御力的变化
int YPlayer::playerarmchange(void)
{
        long arm=getWeaponAttack(); //武器攻击力
        YString wuqi=getWeaponType(); //武器类型
        YString wugong ="";
        if (wuqi == "" )  wuqi = "空手";
        wugong=wuqi+"_攻击武功";
        YString usewugong=getAsString(wugong);
        long uselevel=getAsLong(usewugong);    //使用的特殊武功
        long musclelevel =0;
        YString basic = "";
       /* if (wuqi == "空手" )
        {
        }
        else basic = "基本"+wuqi+"法";  */
        if (usewugong == "") usewugong = "基本拳法" ;
        musclelevel = getBaseHand();//getAsLong ("基本拳法"); // 基本拳法地等级对臂力地影响
        if (musclelevel < getBaseFinger())
        {
          musclelevel = getBaseFinger(); // 基本拳法地等级对臂力地影响
          if (usewugong == "") usewugong = "基本指法" ;
        }
        if (musclelevel < getbaseSole())
        {
          musclelevel = getbaseSole(); // 基本拳法地等级对臂力地影响
          if (usewugong == "") usewugong = "基本掌法" ;
        }
        if (musclelevel < getBaseLeg())
        {
           musclelevel = getBaseLeg(); // 基本拳法地等级对臂力地影响
          if (usewugong == "") usewugong = "基本腿法" ;
        }
        if (musclelevel < getBasePub())
        {
          musclelevel = getBasePub(); // 基本拳法地等级对臂力地影响
          if (usewugong == "") usewugong = "基本手法" ;
        }
        if (musclelevel < getBaseClow())
        {
          musclelevel = getBaseClow(); // 基本拳法地等级对臂力地影响
          if (usewugong == "") usewugong = "基本爪法" ;
        }
        setLastArm(getBeginArm()+(musclelevel/10)) ;
        setMaxWeight((getBeginArm()+(musclelevel/10))*15);
        long   muscleleveltemp;
        // 基本轻功等级对身法地影响
        muscleleveltemp = getBaseDodge();//getAsLong ("基本轻功");
        setlaseDodge(getbeginDodge()+(muscleleveltemp/10)) ;
        //根骨的变化
        muscleleveltemp = getBaseForce();// getAsLong ("基本内功");
        setLastForce(getBeginForce()+(muscleleveltemp/10)) ;
        //悟性变化
        muscleleveltemp = getLearn();//getAsLong ("读书写字");
        setLastLearn(getBeginLearn()+(muscleleveltemp/10));
        //setBehindSavvy(getBeginLearn()+(muscleleveltemp/10)) ;
        long hand = getLastArm();//getAsLong ("后天臂力");
        //返回使用的基本武功
        YString leixing=g_Wugong-> wugong_leixing(usewugong);
        leixing =  "基本" +  leixing ;
        long basiclevel = getSkillLevel(leixing);//getAsLong(leixing);
        /*if (basic != "" )basiclevel = getAsLong (basic);    //使用的基本武功
        else  basiclevel = musclelevel  ;  */
        long expuse = getExperience(); //经验
        if(expuse==0) expuse=1;
        // 处理人物的攻击力的变化
        long proportion = g_Settings->getsitHitScale();//getAsLong("攻击力比例");
        long hitexpchange = g_Settings->getsitHitExpChange();//getAsLong("攻击经验转换");
        if (hitexpchange == 0)hitexpchange = 1000;
        if(proportion==0) proportion=1;
        long turehit =  hand + arm + ((uselevel+(basiclevel/2))*(uselevel+(basiclevel/2)))/proportion + expuse/hitexpchange;
        setInhereAttack(turehit); //固定攻击力
        //  处理人物的防御力的变化
        long parry = getAsLong ("基本招架");  //基本招架
//       long shenfa = getAsLong ("后天身法");
        musclelevel = ((YPlayer*)this)->getBaseDodge();//getAsLong ("基本轻功");
        long deffexpchange = g_Settings->getsitDefExpChange();//getAsLong("防御经验转换");
        if  (deffexpchange == 0)  deffexpchange = 1000;
        YString useparry = getParryUsing (); //招架_武功
        long  useparryleve = getAsLong ( useparry );
        if (parry == 0 ) parry = 1;
        YString qinggong = getDodgeUsing(); //轻功使用
        long useqinggong = getAsLong (qinggong);
        long defend =  g_Settings->getsitDefScale();//getAsLong("防御力比例");
        if(defend==0) defend=1;
        long mydeff = hand  + ((parry/2 + useparryleve/4 + useqinggong/2 + musclelevel/4)*
                      (parry/2 + useparryleve/4 + useqinggong/2 + musclelevel/4)/defend) + expuse/deffexpchange;
        setInhereDefense(mydeff); //固定防御力
        if ((mydeff <0 )|| (mydeff >1000000))
        {
          g_applog->write((YString)hand+","+(YString)parry+","+(YString)useqinggong+","+(YString)musclelevel+","
                                +(YString)defend+",");
        }
        //人物的气血处理
/*        long qixue = getAsLong("基本内功");
        YString neigong = getAsString("使用内功");
        long useneigong = getAsLong(neigong);
        set("最大气血",100 + (qixue + 2*useneigong)* g_Settings->getAsLong("每级气血增长"));
        set("最大内功",100 + (qixue + 2*useneigong)* g_Settings->getAsLong("每级内力增长"));
*/
        return 1;
}
//----------------------------------------------------------
int YPlayer::playerhpchange() //人物的气血精力的增加
{
  YString neigong = getForceUsing(); //使用内功
  long base = getBaseForce();//getAsLong ("基本内功");
  long playeruse = getAsLong(neigong);
  long playerage = getActorAge();
  long playerforce =  getBeginForce ();
  long beginage = g_Settings->getsitNewbieBeginAge();//getAsLong("新手开始年龄");
  long allageadd = playerforce * (playerage - beginage);
  setMaxInternalForce(100+((base+2*playeruse)*g_Settings->getsitLelForceUp())+allageadd+getAddMaxInternalForce());
  setMaxBody(100+((base+(playeruse*2))*g_Settings->getsitLelBodyUp())+allageadd);
  long learn = getLearn();//getAsLong("读书写字");
  setMaxEnergy(100+(learn*g_Settings->getsitLelBookUp())+allageadd+getAddMaxEnergy());
  //set ("后天根骨",getAsLong("先天根骨")+(base/10)) ;
  playerarmchange();//攻击力变化
  return 1;
}
//-------------------------------------------------------------------
//get sth.
int YPlayer::get(YString sentence)
{
  YString thing_name=sentence.getWord();
  YString isFrom = sentence.getWord();
  YAbstractThing* sth=getRoom()->findChildThing(thing_name);
  YAbstractActor* sb=getRoom()->findChildActor(thing_name);
  resumWeight();
  if (isFrom != "from") //是不是从别的地方取得
  {
    // get 物品处理
    if (sth) //物品的判断
    {
      YString howmuch = isFrom ;
      if (howmuch == "" )  howmuch="1";
      long muchsth = howmuch.toLong();
      if (muchsth <= 0) muchsth=1;
      if ( sth->getCount() < muchsth ) muchsth = sth->getCount();
      if (((YThing*)sth)->getThingWeight() == 0) ((YThing*)sth)->setThingWeight(10);
      if (getWeight()+((((YThing*)sth)->getThingWeight())*muchsth )<= getMaxWeight() )
      {
        //销毁撤消
        sth->set("销毁时间间隔",0)  ;
        YString liangci = ((YThing*)sth)->getQuantifier();//getAsString("量词");
        if ( liangci == "" )liangci ="把";
        YString msg=getDisplayName()+"得到了"+(YString)muchsth+liangci+sth->getDisplayName();
        display("你捡起了"+(YString)muchsth+liangci+sth->getDisplayName());
        getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);
        getRoom()->giveChildTo(sth, this ,muchsth);
       }
       else display ("它太重了，你已经拿的东西太多了。");
    }
    // get 人物处理
    else if (sb) //人物的指定判断
    {
       if (((YActor*)sb)->getStatus() =="晕倒中" )
       {
         if (((YActor*)sb)->getActorWeight()== 0 ) ((YActor*)sb)->setActorWeight(100);
         if (getWeight()+((YActor*)sb)->getActorWeight() < getMaxWeight())
         {
           //身上的人物转移
           ((YActor*)sb)->dropplayer();
           //人物的转移
           YString msg=getDisplayName()+"扶起"+sb->getDisplayName()+"把他背到背上";
           display("你扶起"+sb->getDisplayName()+"把他背到背上");
           getRoom()->getRoomChat()->talk(NULL, msg,this,sb);
           getRoom()->giveChildTo(sb, this);
         }
         else display ("他对于你来说太重了。");

       }
       else display ("他还在清醒着呢！");
    }
    //get all 处理
    else if (thing_name == "all" )
    {
       YString allthing=getRoom()->enumChildrenThing(); //房间的所有物品
       if (allthing == "" )//没有物品时的显示
       {
         display ("这里没有什么东西可以拿起来。");
         return 1;
       }
       YString tempThing; //临时物品
       YAbstractThing *onething;
       while((tempThing=allthing.getWord()) !="" )
       {
         onething=getRoom()->findChildThing(tempThing);
         if(!onething) //是否有物品的判断
         {
            continue;
         }
         long thingwield = ((YThing*)onething)->getThingWeight() ;
         if ( thingwield == 0) thingwield = 1;
         long count = (getMaxWeight() - getWeight())/ thingwield;
         if (count > onething->getCount()) count=onething->getCount();
         if (((YThing*)onething)->getQuantifier()=="") ((YThing*)onething)->setQuantifier("把");
         if (count > 0)
         {
            //撤消销毁
            onething->set("销毁时间间隔",0);
            YString msg=getDisplayName()+"得到了"+(YString)count+((YThing*)onething)->getQuantifier()+((YThing*)onething)->getDisplayName();
            display("你捡起了"+(YString)count+((YThing*)onething)->getQuantifier()+onething->getDisplayName());
            getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);
            getRoom()->giveChildTo(onething,this,count);
//            set ("负重",getAsLong("负重")+onething->getAsLong("重量")*count);
          }
          else
          {
            display (tempThing+"对于你来说太重了。");
          }
       }
    }
    else display ("get 物品名(all) 或是 get 物品名(all) from  人物名");
  }
  else if ( isFrom== "from")
  {
     YString getFrom = sentence.getWord();
     YAbstractThing* dead = getRoom()->findChildThing(getFrom);
     sb = getRoom()->findChildActor(getFrom);
     if (sb) //人物的判断
     {
        sth = sb->findChildThing(thing_name);
        YActor* tempsb = (YActor*)sb;
        if (tempsb->getStatus() == "晕倒中")
        {
          if (sth && thing_name != "all")  //物品是否有的判断
          {
             long muchsth;
             long thingwield = ((YThing*)sth) ->getThingWeight();
             if (thingwield == 0) thingwield = 1;
             muchsth =  (getMaxWeight() - getWeight())/ thingwield;
             if (muchsth <= 0) muchsth=1;
             if ( muchsth > sth->getCount())  muchsth = sth->getCount();
             if (((YThing*)sth)->getQuantifier()=="") ((YThing*)sth)->setQuantifier("把");
             if (getWeight()+(((YThing*)sth)->getThingWeight()*muchsth )<= getMaxWeight())
             {
                YString thingDisplayName =  ((YThing*)sth)->getDisplayName();
                YString thingQuantifier =  ((YThing*)sth)->getQuantifier() ;
                if (sb->giveChildTo(sth,this,muchsth))
                {
                  display("你从"+sb->getDisplayName()+"身上取到了"+(YString)muchsth+thingQuantifier+thingDisplayName+".");
                  getRoom()->getRoomChat()->talk(NULL,getDisplayName()+"从"+sb->getDisplayName()+"身上取到了"+(YString)muchsth + thingQuantifier + thingDisplayName+".",this,sb);
                  //调用函数处理人物的物品问题
//                  tempsb->ActorAddFeatureChange();
                  tempsb->ActorAddRecoveryChange();
                }
                else display ("你没有得到"+thing_name+".");
             }
             else display ("它对于你来说太重了。");
          }
          else if (thing_name == "all" )
          {
            YString allthing=sb->enumChildrenThing(); //房间的所有物品
            YString tempThing; //临时物品
            YAbstractThing *onething;
            if (allthing == "" ) display("里边没有任何东西");
            while((tempThing=allthing.getWord())!="")
            {
              onething=sb->findChildThing(tempThing);
              if(!onething) //这件物品的判断
              {
                  continue ;
              }
              if (((YThing*)onething)->getQuantifier()=="") ((YThing*)onething)->setQuantifier("把");
              long thingweild =  ((YThing*)onething)->getThingWeight() ;
              if ( thingweild == 0) thingweild = 1 ;
              long count = ((getMaxWeight() - getWeight() )/ thingweild);
              if (count > onething->getCount()) count=onething->getCount();
              if (count > 0 )
              {
                  YString thingQuantifier= ((YThing*)onething)->getQuantifier() ;
                  YString thingDisplayName = ((YThing*)onething)->getDisplayName() ;
                  if(sb->giveChildTo(onething,this,count))
                  {
                    YString msg=getDisplayName()+"得到了"+(YString)count+thingQuantifier+thingDisplayName;
                    display("你捡起了"+(YString)count+thingQuantifier+thingDisplayName);
                    getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);
                    //调用函数处理人物的物品问题
//                    tempsb->ActorAddFeatureChange();
                    tempsb->ActorAddRecoveryChange();
                  }
                  else display ("你没有取到"+tempThing+".");
              }
              else
              {
                display (tempThing+"对于你来说太重了。");
              }
            }
          }
          else display("他身上没有这件物品。");
        }
        else display ("他还清醒着呢啊。");
     }
     else if (dead)
     {
        sth = dead->findChildThing(thing_name);
        if (sth)  //物品的判断
        {
          YString howmuch = sentence.getWord();
          if (howmuch == "" )  howmuch="1";
          long muchsth = howmuch.toLong();
          if (muchsth <= 0) muchsth=1;
          if ( sth->getCount() < muchsth ) muchsth = sth->getCount();
          if ( ((YThing*)sth)->getThingWeight()==0 ) ((YThing*)sth) ->setThingWeight(10);
          if (getWeight()+(((YThing*)sth)->getThingWeight()*muchsth )<= getMaxWeight())
          {
             if (dead->giveChildTo(sth,this,muchsth))
             {
                display("你取到了"+thing_name+".");
                getRoom()->getRoomChat()->talk(NULL,getActorName()+"取到了"+thing_name+".",this);
             }
             else display ("你没有得到"+thing_name+".");
           }
           else display ("它对于你来说是太重了。");
        }
        else if (thing_name == "all" )
        {
          YString allthing=dead->enumChildrenThing(); //房间的所有物品
          YString tempThing; //临时物品
          YAbstractThing *onething;
          if (allthing == "" ) display("里边没有任何东西");
          while((tempThing=allthing.getWord())!="")
          {
             onething=dead->findChildThing(tempThing);
             if(!onething)  //物品的指定
             {
                continue;
             }
             if (((YThing*)onething) ->getQuantifier()=="") ((YThing*)onething)->setQuantifier("把");
             long thingweild =  ((YThing*)onething)->getThingWeight();
             if (thingweild == 0 ) thingweild = 1;
             long count = ((getMaxWeight() - getWeight() )/thingweild );
             if (count>onething->getCount()) count = onething->getCount();
             YString onethingDisplayName =  ((YThing*)onething)->getDisplayName() ;
             if (count > 0 )
             {
               dead->giveChildTo(onething,this,count);
               YString msg=getDisplayName()+"从"+((YThing*)dead)->getThingName()+"中得到了"+onethingDisplayName;
               display("你从"+((YThing*)dead)->getThingName()+"中捡起了"+onethingDisplayName);
               getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);
//               set ("负重",getAsLong("负重")+(onething->getAsLong("重量")*count));
             }
             else
             {
                display (tempThing+"对于你来说太重了。");
             }
          }
        }
        else display ("里面没有任何东西。");
     }
     else display("你要从哪里取东西啊？");
  }
  else display ("get 物品名(all) 或是 get 物品名(all) from  人物名（尸体的名字）");
  return 1;
}
//--------------------------------------------------------
//睡觉
int YPlayer::goSleep(void)
{
  //房间内的可以休息
  if ((getRoom()->isTypeOf("YRetiringRoom"))  || getRoom()->getAsLong("允许睡觉")  == 1 )
  {
  }
  else
  {
    display ("请不要随地睡觉啊！！");
    return 1;
  }
  //食物饮水是否充足
  if ((getFood()*getDrink()) == 0 )
  {
    display ("你总不能空着肚子睡觉吧！！");
    return 1;
  }
  //是否有在做别的事情
  if (getStatus() != "")
  {
    display ("你还有时间做别的吗？");
    return 1;
  }
  //是否频繁的睡觉
  if (getPlayerSleepSkip() != 0)//开始的时候因为没有这个属性所以为0
  {
   display ("你今天已经睡过觉了。");
   return 1;
  }
  setStatus("睡眠中");
  setPlayerSleepSkip(1);
  //set ("睡觉间隔",1);
  setSleepTime(15000);
  //set("睡眠",15000);
  display("你躺了下来，很快进入了梦乡.......");
  showPhoto("1","5");
  return 0;
}
//--------------------------------------------------------
//列出自己身上物品
int YPlayer::i(void)
{
  YString enumThing = enumChildrenThing();
  YString enumActor = enumChildrenActor();
  if ((enumThing=="")&&(enumActor==""))
  {
   display ("你没有带着任何东西。");
   return 1;
  }
  long max_weight=getMaxWeight();
  if(max_weight==0) max_weight=1;
  long weight = (getWeight()*100)/max_weight;
  if (weight <= 0 ) weight = 1;
  display ("你的负重比例为"+(YString)(weight)+"%");
  display ("你身上的物品有:");
  if (enumThing !="") display(enumChildrenThingForDisplay());
  if (enumActor !="") display(enumChildrenActorForDisplay());
  return 1;
}
//--------------------------------------------------------
//列出自己身上物品
int YPlayer::i_b(void)
{
  YString iInfo;
  if (enumChildrenThing()!="") iInfo=enumChildrenThingForDisplay();
  if (enumChildrenActor()!="") iInfo=enumChildrenActorForDisplay()+" "+iInfo;
  if ((enumChildrenThing()=="")&&(enumChildrenActor()==""))
      iInfo="你没有带着任何东西。";
  iInfo="showinfo2(\""+iInfo.toInnerString()+"\")";
  display(iInfo,false,JAVASCRIPT_MSG);
  return 1;
}
//lp-------------------------------------------------------
//drop sth.  丢掉东西
int YPlayer::drop(YString sentence)
{
  YString thing=sentence.getWord();
  /*if (thing == "all") //all的时候处理
  {
       YString allthing=this->enumChildrenThing(); //人物的所有物品
       YString allbody = this->enumChildrenActor();// 人物身上的其他人物
       allthing= allthing+" "+allbody;
       YString tempThing ; //临时物品
       YAbstractThing *onething;
       while ((tempThing= allthing.getWord()) !="")
       {
         onething=this->findChildThing(tempThing);
         if (onething) //物品的判断
         {
           if (giveChildTo(onething,getRoom(),onething->getCount()))
           {
             onething->set("销毁时间",g_Settings->getAsLong("物品销毁时间"));
             display ("你丢掉了"+tempThing);
           }
           else display ("你没有丢掉"+tempThing);
         }
       }
       setWeaponName("");//set ("武器","");
       setArmor("");//set ("盔甲","");
       setClothName("");//set ("衣服","");
       setShoe("");//set ("鞋","");
       setFlower("");//set ("花","");
       setHat("");//set ("帽子","");
       setRing("");//set ("戒指","");
       setNecklace("");//set ("项链","");
       setWeaponType("");//set ("武器类型","");
       setAppendDefense(0);//set ("附加防御力",0);
       setAddFeature(0);//set ("附加容貌值",0);
       setAddLuck(0);//set ("附加福缘",0);
       setWeaponAttack(0);//set ("武器攻击力",0);
        return 1;
  }*/    //all的时候的物品的处理
  YAbstractThing* sth=this->findChildThing(thing);
  YActor* sb;
  sb=(YActor*)(this->findChildActor(thing));
  if(!sth && ! sb)    //没有物品时的处理
  {
    display("你要丢掉什么？");
    return 1;
  }
  if ( sb )
  {
      giveChildTo(sb,getRoom());
      display ("你放下了"+sb->getActorName());
      getRoom()->getRoomChat()->talk(NULL,getActorName()+"把"+thing+"放下了.",this,sb);
      return 1;
  }
  YString thingname = ((YThing*)sth)->getThingName();//getAsString("名字");
  YString howmuch=sentence.getWord();
  long count=howmuch.toLong();
  if ( count <= 0 )count = 1 ;
  if ( count > sth->getCount() ) count = sth->getCount() ;
  YString liangci = ((YThing*)sth)->getQuantifier();//getAsString("量词");
  if ( liangci == "" )liangci ="把";
  if (this->giveChildTo(sth,getRoom(),count))
  {
    YString msg=getActorName()+"丢掉了"+(YString)count+liangci+thingname ;
    display("你丢掉了"+(YString)count+liangci+ thingname );
    getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);
  }
  else display ("你没有丢掉"+thingname);
//  ActorAddFeatureChange();     //人物附加容貌变化
  ActorAddRecoveryChange();     //人物附加防御力力变化
  return 1;
}
//lp------------------------------------------------------
//wield sth.          装备
int YPlayer::wield(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if(!sth)
        {
          display("你要装备什么东西？");
          return 1;
        }
        else
        {
                if(sth->getAsLong("武器") == 1)
                {
                        //装备物品需要的条件
                        YString wieldneed = sth -> getAsString ("装备条件");
                        if (wieldneed != "") onBeforeSave();
                        YString tempneed = wieldneed.getWord() ;
                        while ( tempneed!= "" )
                        {
                          //如果出现问题要先进行save
                          long longneed = sth -> getAsLong (tempneed);
                          YString strneed = sth -> getAsString (tempneed);
                          if (strneed != "" )//字符的条件
                          {
                            if (getAsString(tempneed)  != strneed )
                            {
                              display ("你的"+tempneed+"不是"+strneed);
                              return 1;
                            }
                          }
                          else if (longneed != 0)
                          {
                            if (getAsLong(tempneed) < longneed)
                            {
                              display ("你的"+tempneed+"还没有到达"+(YString)longneed);
                              return 1;
                            }
                          }
                          tempneed = wieldneed.getWord() ;
                        }
                        setWeaponName(((YThing*)sth)->getThingName());
                        if (getWeaponAttack() < 0) setWeaponAttack(0);
                        setWeaponAttack(sth->getAsLong("攻击力"));
                        setWeaponType(sth->getAsString("类型"));
                        display("你装备了"+((YThing*)sth)->getThingName());
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"装备了"+((YThing*)sth)->getThingName()+"。",this, NULL);
                        playerarmchange();
                        return 1;
                }
                 else
                {
                        display("这件物品无法装备");
                        return 1;
                }
        }
}
//lp-------------------------------------------------------
//unwield         解除
int YPlayer::unwield(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YString sth=getWeaponName();//getAsString("武器") ;
        if( (sth == "") || (sth != thing)  )
        {
                display("你没有装备这件物品");
                return 1;
        }
        else
        {
                setWeaponName("");
                setWeaponAttack(0);
                setWeaponType("");
                display("你放下了"+sth);
                playerarmchange();
                getRoom()->getRoomChat()->talk(NULL,getActorName()+"放下了"+sth+"。",this, NULL);
                return 1;
        }
}
//lp------------------------------------------------------
//wear sth.       穿上
int YPlayer::wear(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if(!sth)
        {
          display("你要装备什么东西？");
          return 1;
        }
        else
        {
          if(sth->getAsLong( "穿戴") == 1 )
          {
                YString thingtype = "";
                YString thingname = "";
                if  (getAppendDefense() < 0 )   setAppendDefense(0);
                if  (getAddLuck() < 0 )   setAddLuck(0);
                if  (getAddFeature() < 0 )   setAddFeature(0);
                if (sth->getAsLong("盔甲") == 1 )  { thingtype = "盔甲";thingname=getArmor();setArmor(thing);}  //穿盔甲
                else if (sth->getAsLong("衣服") == 1 ) {thingtype ="衣服";thingname=getClothName();setClothName(thing);}
                else if (sth->getAsLong("帽子") == 1 ){ thingtype ="帽子";thingname=getHat();setHat(thing);}
                else if (sth->getAsLong("鞋") == 1 )   {thingtype = "鞋";thingname=getShoe();setShoe(thing);}
                if ((thingtype != "") )
                {
                        //原来有东西的时候的显示
                        if (thingname != "")
                        {
                          if (thingname == thing )
                          {
                            display ("你累不累啊，一件东西还要穿多少次啊！！");
                            return 1;
                          }
                          display("你脱下了"+thingname+"穿上了"+sth->getDisplayName()+".");
                          getRoom()->getRoomChat()->talk(NULL,getActorName()+"脱下了"+thingname+"穿上了"+((YThing*)sth)->getThingName()+"。",this, NULL);
                        }
                        else
                        {
                          //setAppendDefense(getAsLong("附加防御力")+sth->getAsLong("防御力"));
                          display("你穿上了"+sth->getDisplayName()+".");
                          getRoom()->getRoomChat()->talk(NULL,getActorName()+"穿上了"+((YThing*)sth)->getThingName()+"。",this, NULL);
                        }
                }
                
                if (sth->getAsLong("花")   == 1 ) {thingtype= "花" ;thingname=getFlower() ;setFlower(thing) ;}
                else if (sth->getAsLong("戒指") == 1 ) {thingtype= "戒指";thingname=getRing();setRing(thing);}
                else if (sth->getAsLong("项链") == 1 ) {thingtype ="项链";thingname=getNecklace();setNecklace(thing);}
                else if (sth->getAsLong("手镯") == 1 ) {thingtype ="手镯";thingname=getBangle();setBangle(thing);}
                if ((thingtype == "花") || (thingtype == "项链") || (thingtype == "戒指") || (thingtype == "手镯") )
                {
                        if (thingname != "")
                        {
                          if (thingname == thing )
                          {
                            display ("你要把"+thing+"戴多少次啊！！");
                            return 1;
                          }
                          display("你摘下了"+thingname+"并戴上了"+sth->getDisplayName()+".");
                          getRoom()->getRoomChat()->talk(NULL,getActorName()+"摘下了"+thingname+"并戴上了"+((YThing*)sth)->getThingName()+"。",this, NULL);
                        }
                        else
                        {
                          display("你戴上了"+sth->getDisplayName()+".");
                          getRoom()->getRoomChat()->talk(NULL,getActorName()+"戴上了"+((YThing*)sth)->getThingName()+"。",this, NULL);
                        }
                }
//                ActorAddFeatureChange();     //人物附加容貌变化
                ActorAddRecoveryChange();     //人物附加防御力力变化
                return 1;
           }
           else
           {
                  display("这件物品无法装备.");
                  return 1;
           }
        }
}
//lp-------------------------------------------------------
//unwear      脱下
int YPlayer::unwear(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if( !sth )
        {
                display("你没有这件物品");
                return 1;
        }
        else
        {
                if ( thing == getArmor() || thing == getClothName()
                    || thing ==getShoe() ||thing == getHat())
                {
                  if (thing == getArmor())
                  {

                        setArmor("");
                        display("你脱下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"脱下了"+thing+"。",this, NULL);
                  }
                  if (thing == getClothName() )
                  {
                        setClothName("");//set("衣服","");
                        display("你脱下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"脱下了"+thing+"。",this, NULL);
                  }
                  if (thing == getHat() )
                  {
                        setHat("");//set("帽子","");
                        display("你摘下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"摘下了"+thing+"。",this, NULL);
                  }
                  if (thing == getShoe() )
                  {
                        setShoe("");//set("鞋","");
                        display("你脱下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"脱下了"+thing+"。",this, NULL);
                  }
                  ActorAddRecoveryChange();     //人物附加防御力力变化
                }
                else if (thing == getFlower() ||thing == getNecklace()
                         ||thing == getRing() ||thing == getBangle())
                {
                  if (thing == getFlower() )
                  {
                        setFlower("");//set("花","");
                        display("你摘下了一朵"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"摘下了一朵"+thing+"。",this, NULL);
                  }
                  if (thing == getRing()  )
                  {
                        setRing("");//set("戒指","");
                        display("你取下了一枚"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"取下了一枚"+thing+"。",this, NULL);
                  }
                  if (thing == getNecklace() )
                  {
                        setNecklace("");//set("项链","");
                        display("你摘下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"摘下了"+thing+"。",this, NULL);
                  }
                  if (thing == getBangle() )
                  {
                        setBangle("");//set("项链","");
                        display("你摘下了"+thing);
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"摘下了"+thing+"。",this, NULL);
                  }
                  ActorAddRecoveryChange();     //人物附加防御力力变化
//                  ActorAddFeatureChange();     //人物附加容貌变化
                }
                else display("你没有穿戴这件物品。");
                return 1;
        }
}
//lp-----------------------------------------------------
//--------------------------------------------------------
//ask sb.about sth.
int YPlayer::ask(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YMUDObject* sb=getRoom()->findChildActor(s);

  if((!sb)||(!sb->isTypeOf("YNPC"))) //是否人物的判断
  {
    display("没有你要问的人");
    return 1;
  }
  s =sentence.getWord();//about
  if ( s!="about")
  {
        display(" 正确格式为: ask sb. about sth.");
        return 1;
  }
  s = sentence.getWord(); //  sth.
  YString str="ask "+((YActor*)sb)->getActorName()+" about "+s;
  sb->executeCommandAsTarget(this,str);
  return 1;
}
//lp-----------------------------------------------------
//--------------------------------------------------------
//悬赏追杀
int YPlayer::xuanshang(YString sentence)
{
  YAbstractRoom* objRoom=getRoom();
  if(!objRoom) return 1;
  YString NPCList=objRoom->enumChildren("","","YNPC");
  YString theNPC;
  YAbstractActor* objNPC;
  for(;(theNPC=NPCList.getWord())!="";){
     objNPC=objRoom->findChildActor(theNPC);
     if(!objNPC) continue;
     if(objNPC->getAsLong("是否悬赏")!=1) continue;
     else
     {
          YString str="xuanshang "+sentence;
          objNPC->executeCommandAsTarget(this,str);
          return 1;
     }
  }
  return 1;
}
//lp-----------------------------------------------------
//--------------------------------------------------------
//查看悬赏追杀
int YPlayer::list(YString sentence)
{
  YAbstractRoom* objRoom=getRoom();
  if(!objRoom) return 1;
  YString NPCList=objRoom->enumChildren("","","YNPC");
  YString theNPC;
  YAbstractActor* objNPC;
  for(;(theNPC=NPCList.getWord())!="";){
     objNPC=objRoom->findChildActor(theNPC);
     if(!objNPC) continue;
     if(objNPC->getAsLong("是否悬赏")!=1) continue;
     else
     {
          YString str="list "+sentence;
          objNPC->executeCommandAsTarget(this,str);
          return 1;
     }
  }
  return 1;
}
//lp-----------------------------------------------------
//--------------------------------------------------------
//answer sb. sth.
int YPlayer::answer(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YMUDObject* sb=getRoom()->findChildActor(s);
  if((!sb)||(!sb->isTypeOf("YNPC"))) //是否人物的判断
  {
    display("没有你要问的人");
    return 1;
  }
  s = sentence.getWord(); //  sth.
  YString str="answer "+((YActor*)sb)->getActorName()+" "+s;
  sb->executeCommandAsTarget(this,str);
  return 1;
}
//lp-----------------------------------------------------------------
//buy sth.
int YPlayer::buy(YString sentence)
{
  
   //room中处理
  /*      YString s=sentence.getWord();
        YAbstractThing* sth=getRoom()->findChildThing(s);
         if(!sth)
         {
                display("你要买什么东西？");
                return 1;
         }
         giveChildTo((YMUDObject*)sth, this);
         YString msg=getDisplayName()+"买下了"+sth->getDisplayName();
         display("你买下了"+sth->getDisplayName());
         getRoom()->getRoomChat()->talk(NULL, msg,this,NULL);  */
         return 1;
}
//lp------------------------------------------------------
//eat sth.       吃
int YPlayer::eat(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if(!sth)  //物品判断
        {
          display("你要吃什么？");
          return 1;
        }
        else
        {
          if(sth->getAsLong( "食物") == 1 )
          {
                        //-----食物添加
                     //YString much=sentence.getWord();//剩余的数量
                     long food = getFood();
                     if (food >= getMaxFood())
                     {
                       display ("你吃的已经是够饱的了，再也不能吃东西了。");
                       return 1 ;
                     }
                     //剩余量去掉
                     /*
                     if (much == "") much = "1";
                     long left = sth->getAsLong ("剩余量",much.toLong());
                     sth ->set ("剩余量",left-1 ,much.toLong());
                     */
                     display("你拿起"+thing+"咬了几口");
                     getRoom()->getRoomChat()->talk(NULL,getActorName()+"咬了"+thing+"。",this, NULL);
                     setFood(getFood()+50);//set("食物", food+50 );
                     //if ( (left-1) <= 0 )
                     //{
                       //注释由于数据文件没更新等更新使用
                       if((sth->getCount())>1) sth->setCount(sth->getCount()-1);//sth->deleteOne(much.toLong());
                       else
                       {
                          if(removeChild(sth))
                          {
                            delete sth;
                          }
                          //set ("负重",getAsLong("负重")+sth->getAsLong("重量"));
                        }
                        display("你已经把"+ thing+"吃的干干净净");
                     //}
                     return 1;
           }
           else if (sth->getAsLong( "药品") == 1 )
           {
                        YString eatneed = sth -> getAsString ("吃药条件");
                        if (eatneed != "") onBeforeSave();
                        YString tempneed = eatneed.getWord() ;
                        long i=0;
                        while ( tempneed!= "" )
                        {
                          //如果出现问题要先进行save
                          i++;
                          YString thingtempneed = tempneed + "条件" + (YString)i ;
                          long longneed = sth -> getAsLong (thingtempneed);
                          YString strneed = sth -> getAsString (thingtempneed);
                          if (strneed != "" )//字符的条件
                          {
                            if (getAsString(tempneed)  != strneed )
                            {
                              display ("你的"+tempneed+"不是"+strneed+"无法使用这种药品。");
                              return 1;
                            }
                          }
                          else if (longneed != 0)
                          {
                            if ( longneed > 0 )
                            {
                              if (getAsLong(tempneed) < longneed)
                              {
                                display ("你的"+tempneed+"还没有到达"+(YString)longneed);
                                return 1;
                              }
                            }
                            else
                            {
                              longneed = (-1) * longneed;
                              if (getAsLong(tempneed) > longneed)
                              {
                                display ("你的"+tempneed+"已经够高的了，不需要用"+thing+"来提升了。") ;
                                return 1;
                              }
                            }
                          }
                          tempneed = eatneed.getWord() ;
                        }
                        display("你拿起"+thing+"放到了嘴里。");
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"拿起"+thing+"放到了嘴里。",this, NULL);
                        YString type = sth -> getAsString("增长属性");
                        onBeforeSave();
                        YString onetype = type.getWord();
                        while (onetype != "")
                        {
                          set(onetype,getAsLong(onetype)+sth->getAsLong(onetype));
                          onetype = type.getWord();
                        }
                        onAfterLoad();
                        if((sth->getCount())>1) sth->setCount(sth->getCount()-1);//sth->deleteOne(much.toLong());
                        else
                        {
                          if(removeChild(sth))
                          {
                            delete sth;
                          }
                        }
           }
           else
           {
                  display("你拿起"+thing+"咬了几口感觉到不好吃，就又放了下来。");
                        return 1;
           }
        }
        return 1;
}
//lp------------------------------------------------------
//drink sth.       喝
int YPlayer::drink(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if(!sth)  //物品判断
        {
          display("你要喝什么？");
          return 1;
        }
        else
        {
          if(sth->getAsLong( "饮水") == 1 )
          {
        //-------添加饮水
                     YString much=sentence.getWord();//剩余的数量
                     //剩余量去掉
                     /*
                     if (much == "") much = "1";
                     long left = sth->getAsLong ("剩余量",much.toLong());
                     if ((left-1) < 0)
                     {
                        display ("你的"+thing+" 已经没有了。");
                        sth ->set ("剩余量",0,much.toLong());
                     }
                     
                    else
                     { */
                        long water = getDrink();
                        if (water >= getMaxDrink())
                        {
                          display ("你已经喝得够饱的了，不能再喝了。");
                          return 1;
                        }
                        display ("你拿起"+thing+"喝了一口。");
                        getRoom()->getRoomChat()->talk(NULL,getActorName()+"对着"+thing+"猛灌了几口。",this, NULL);
                        setDrink(water + 50);//set("饮水", water + 50 );
                       if((sth->getCount())>1) sth->setCount(sth->getCount()-1);//sth->deleteOne(much.toLong());
                       else
                       {
                          if(removeChild(sth))
                          {
                            delete sth;
                          }
                          //set ("负重",getAsLong("负重")+sth->getAsLong("重量"));
                        }
                        //sth ->set ("剩余量",left-1 ,much.toLong());
                        display (thing+"已经被喝光了。");
                     //}
           }
           else
           {
                  display("你举起"+thing+"喝了几口，可是没有一点感觉到对自己的身体有什么好处。");
           }
        }
        return 1;
}
//lp----------------------------------------------------------
//check  查帐
int YPlayer::check(YString sentence)
{
        //查帐在room中处理
        YString s=sentence.getWord();//sb.
        YAbstractActor* sb=g_PlayerManager->getActor(s);
        if (!sb) display ("你要查看什么？");//查看类别
        else
        {
                if (((YActor*)sb)->getSchool() == "丐帮")
                {
                    display ("只有巫师可以查看他人武功");
                }
                else display("只有巫师可以查看他人武功");
        }
        return 1;
}
//-------------------------------------------------------------
//lp-------------------------------------------------------
//enforce   加力
int YPlayer::enforce(YString sentence)
{
        YString how=sentence.getWord();//加力大小
        long howadd = how.toLong();
        long themax = getBaseForce();
        if (howadd <0 )
        {
          display ("你怎么可以这样加力呢？");
          return 1;
        }
        else if (howadd == 0)
        {
          display ("你取消了加力");
        }
        else if ( howadd >= themax) //加力超过最大内力
        {
            display("你没有那么高的内功。");
            return 1;
        }
        else if (howadd <=  themax )
        {
          //howadd = themax ;//加力1/10
          display("你的攻击力提升"+(YString)howadd+"。");
        }
        setForceAttack(howadd);//set ("加力", howadd);
        return 1;
}
//------------------------------------------------------------
//lp-----------------------------------------------------------
//exert todo   运内力
int YPlayer::exert(YString sentence)
{
        YString todo=sentence.getWord();// 运内力做什么
        if( todo == "powerup")
        {
          if (getAsLong("powerup时间") > 0)
          {
            display ("你正在使用你的内功啊！！");
            return 1;
          }
          YString useforce = getForceUsing() ; //使用得特殊武功
          long useforcelevel=getAsLong(useforce);  //特殊武功级别
          if ( useforcelevel <100 )
          {
            display("你的特殊武功级别还没有达到使用级别");
            return 1;
          }
          if (getInternalForce() < 300)
          {
            display("你的内力不足以使用攻防增加的招数。");
            return 1;
          }
          //现在还不实现
          /*
          long proportion=g_Wugong->wugong_powerup(useforce);//攻击的增加比例
          setPowerUpAttack(getInhereAttack*proportion);//set ("powerup攻击力",(getAsLong("固定攻击力")*proportion));
          setPowerUpDefense(getInhereDefense*(100-proportion));//set ("powerup防御力",(getAsLong("固定防御力")*(100-proportion)));
          set ("powerup时间",g_Settings->getAsLong("powerup时间"));
          setInternalForce(getInternalForce()-200); */
          display ("你两臂一伸，功力大增");
        }
        else if( (todo == "regenerate") || (todo == "jing"))   //恢复精力
        {
                long body=getInternalForce();
                if (body >0)                    //判断内力
                {
                        long mind=getEnergy();
                        long maxmind=getMaxEnergy();
                       if (mind == maxmind)
                        {
                          display ("你的精神很好啊。");
                          //set ("内力", body - 30);
                          return 1;
                        }
                        if ( body - (maxmind - mind ) / 2 < 0)
                        {
                                mind = body*2 + mind;
                                setEnergy(mind);//set ("精力", mind);
                                setInternalForce(0);//set ("内力", 0);
                        }
                         else
                        {
                                setEnergy(maxmind);//set ("精力",maxmind);
                                if  (((maxmind - mind )/2 ) > 50) setInternalForce(body - (maxmind - mind )/2 );
                                else setInternalForce(body - 50 );
                        }
                        display(g_Settings->getjingDisplay());//"你深吸一口气，精神好多了");
                }
                else display ("你没有内力了。");

        }
        else if( (todo == "recover")||(todo == "qi"))  //恢复体力
        {
                long body=getInternalForce();
                if (body >0)                    //判断内力
                {
                        long life=getBody();
                        long maxlife=getMaxBody();
                        if (life == maxlife )
                        {
                          display ("你没有受一点伤啊！！");
                          //set ("内力", body - 30);
                          return 1;
                        }
                        if ( body - (maxlife - life ) / 2 < 0)
                        {
                                life = body*2 + life;
                                setBody(life);//set ("气血", life);
                                setInternalForce(0);//set ("内力", 0);
                        }
                         else
                        {
                                setBody(maxlife);//set ("气血",maxlife);
                                if (((maxlife - life ) / 2) > 50 ) setInternalForce( body - (maxlife - life ) / 2);
                                else setInternalForce( body - 50 );
                        }
                        display(g_Settings->getQiDiaplay());//"你深吸一口气,脸色好了许多");
                }
                else display ("你没有内力了。");
        }
        else display("你用内力要作什么");
        return 1;
}
//------------------------------------------------------------

//lp-----------------------------------------------------------
//fill   装水
int YPlayer::fill(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=this->findChildThing(thing);
        if(!sth)  //物品判断
        {
          display("你用什么装水？");
          return 1;
        }
        else
        {
          if(sth->getAsLong("饮水") == 1 )
          {
        //-------添加饮水    set("饮水",sth->getAsString("名字"));
                     sth->set ("剩余量",6);
                     display("你装了一"+sth->getDisplayName()+"水");
                     return 1;
           }
           else
           {
                  display("你不能用它装水");
                  return 1;
           }
        }
}
//lp-----------------------------------------------------------
//follow 跟随
int YPlayer::follow(YString sentence)
{
        YString follow=sentence.getWord();//sb.
        YString s= follow;
        YAbstractActor* sb ;
        if ( follow == "none" )
        {
          if(getYouFollow() == "") display("你没有跟着别人");
          else
          {
            display("你决定放弃和"+getYouFollow()+"一起行动");
          }
          setYouFollow("");//set("跟随","");
          return 1;
        }
        else  sb=getRoom()->findChildActor(s);
//        display(s);
        if((!sb)||(!sb->isTypeOf("YActor"))) //跟随的人物和类别
        {
                display("没有你要跟随的人.");
        }
        else
        {
                if (sb != this)
                {
                        display("你决定和"+sb->getDisplayName()+"一起行动");
                        sb->display(this->getDisplayName()+"决定和你一起行动");
                        YString befollow = ((YActor*)sb)->getFollowYou();//sb->getAsString("跟随的人");
                        if (!( findStringInStr( befollow,getActorName()))) //查找是否已经有了
                        {
                                befollow = getActorName()+" "+ befollow ;
                                ((YActor*)sb)->setFollowYou(befollow);//sb->set ( "跟随的人" ,befollow);
                        }
                        setYouFollow(follow);//set ("跟随",follow);
                }
                else
                {
                        display("你要跟着自己吗？？？？");
                }
         }
         return 1;
}
//------------------------------------------------------------
//lp-----------------------------------------------------------
//knock 敲
int YPlayer::knock(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=getRoom()->findChildThing(thing);
        if(!sth)     //物品的查看
        {
          display("你要敲什么");
          return 1;
        }
        else
        {
                display("你敲了敲"+sth->getDisplayName());
                return 1;
        }
}
//------------------------------------------------------------
//lp-----------------------------------------------------------
//open 打开
int YPlayer::open(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=getRoom()->findChildThing(thing);
        if(!sth)     //物体的查看
        {
          display("你要打开什么");
          return 1;
        }
        else
        {
                display("你打开了"+sth->getDisplayName());
                return 1;
        }
}
//lp-----------------------------------------------------------
//sit sth. 坐
int YPlayer::sit(YString sentence)
{
        YString thing=sentence.getWord();//sth.
        YAbstractThing* sth=getRoom()->findChildThing(thing);
        if(!sth) //查看物体
        {
          display("你随便找了个地方坐了下来。");
        }
        else
        {
                if (sth->getAsLong("坐下") == 1)
                display(getDisplayName()+"坐在"+sth->getDisplayName()+"上");
                else display("你随便找了个地方坐了下来。");
        }
        setStatus("坐");
        showPhoto("2","6");
        return 1;
}
//--------------------------------------------------------------------
//lp------------------------------------------------------------------
//withdraw much 取钱
int YPlayer::withdraw(YString sentence)
{
        YString much=sentence.getWord(); //"much"
        display("你没有在钱庄里");
        return 1;
}
//--------------------------------------------------------------------
//lp------------------------------------------------------------------
//deposite much 钱
int YPlayer::deposite(YString sentence)
{
        YString much=sentence.getWord(); //"much"
        display("你没有在钱庄里");
        return 1;
}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
//tell 告诉
int YPlayer::tell(YString sentence)
{
        YString s=sentence.getWord();//sb.
        YActor* sb=g_PlayerManager->getActor(s);
        if(!sb)//查看人物是否在线
        {
                display("你找的人没有在线。") ;
                return 1;
        }
        else if(sb ==this)
        {
                display("你确定要和自己说话吗？？");
                return 1;
        }
        else
        {
                YString blackname = sb -> getAsString ("关闭对话列表");
                if (blackname == "全部人物名称" )
                {
                  if (isTypeOf("YWizard"))
                  {
                     YString msg = changeword(sentence);
                     msg = "巫师:<font color=red>"+msg+"</font>";
                     YChat::talk(this, sb, msg);
                     display("你告诉"+s+":"+msg);
                     return 1;
                  }
                  display ("对方不打算和你交谈。");
                  return 1;
                }
                YString myname = getActorName();//getAsString("名字");
                YString tempname = getActorName();//getAsString("名字");
                while ((tempname = blackname.getWord()) != "")
                {
                  if (tempname == myname)
                  {
                    display ("对方不想和你进行私人交谈。");
                    return 1;
                  }
                }
                YString msg=sentence;//word
                //查找替换< >   注：由于>在叶面没反映所以不与处理
                msg = changeword(msg);
                msg = "<font color=red>"+msg+"</font>";
                YChat::talk(this, sb, msg);
                display("你告诉"+s+":"+msg);
                return 1;
        }


}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
//wizset 设置
int YPlayer::wizset(YString sentence)
{
       YString type=sentence.getWord(); //类型
       YString much=sentence.getWord(); //数量
       if (type == "玩家级别")
       {
         display("你不能对这个属性进行设定。");
         return 1;
       }
       onBeforeSave();
       set(type,much.toLong());
       onAfterLoad();
       display("你设定你的"+type+"为"+much);
       return 1;
}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
int YPlayer::wizsets(YString sentence)
{
        YString type=sentence.getWord(); //类型
        YString much=sentence; //字符串
        onBeforeSave();
        set(type,much);
        onAfterLoad();
        display("你设定你的"+type+"为"+much);
        return 1;

}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
int YPlayer::wizsetadd(YString sentence)
{
        YString type=sentence.getWord(); //类型
        YString munch=sentence.getWord(); //添加的
        munch=munch+" "+getAsString(type);
        onBeforeSave();
        set(type,munch);
        onAfterLoad();
        display("你设定你的"+type+"为"+munch);
        return 1;
}
//lp------------------------------------------------------------------
//wizsetsb 他人设置
int YPlayer::wizsetsb(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)  //人物判别
  { display ("没有这个人物。"); }
  else
  {
        if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        YString much=sentence.getWord(); //数字
        if (type == "玩家级别")
        {
            display ("不可使用命令，");
            return 1;
        }
        sb->onBeforeSave();
        sb->set(type,much.toLong());
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+much);
  }
  return 1;

}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
//他人文字
int YPlayer::wizsetssb(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)   //人物判别
  { display ("没有这个人物。"); }
  else
  {
        if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        YString much=sentence; //字符
        sb->onBeforeSave();
        sb->set(type,much);
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+much);
  }
  return 1;
}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
int YPlayer::wizkickout(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)   //人物判别
  { display ("没有这个人物。"); }
  else
  {
        sb->setStatus("掉线中");
        display("开始把"+s+"踢出系统");
  }
  return 1;
}
//----------------------------------------------------------------
//lp--------------------------------------------------------------
//他人文字添加
int YPlayer::wizsetaddsb(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)    //人物判别
  { display ("没有这个人物。"); }
  else
  {
     if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        YString munch=sentence.getWord(); //数量
        munch= munch+" "+sb->getAsString(type);
        sb->onBeforeSave();
        sb->set(type,munch);
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+munch);
  }
  return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizget(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     if (wizcompare(sb)) return 1;
     YString roomName= sentence;
     if (roomName == "") roomName="/"+getRoom()->getDataFileName();
     if (sb->getRoom()->sendActorToRoom(sb,roomName) == 0)
     display("你已经成功的把"+s+"抓到了"+roomName);
     else display ("没有成功。");
  }
  else display("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizgoto(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     YString roomName = "";
     roomName="/"+sb->getRoom()->getDataFileName();
     if ( getRoom()->sendActorToRoom(this,roomName) == 0 )
     display("你已经成功的来到了"+s+"的房间"+roomName);
     else display ("没有成功");
  }
  else display("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
//玩家用的逃跑程序
int YPlayer::playerhelproom(YString sentence)
{
  if (getStatus() != "")
  {
    display ("你正忙着干别的呢。");
    return 1;
  }
  if (getBody() < getMaxBody())
  {
    display ("你的气血值不满，不能使用这个命令！");
    return 1;
  }
  YString gowhere =  sentence.getWord();
  if (gowhere == "北京") gotoRoom(g_Settings->getHelpRoom2());
  else if (gowhere == "长安") gotoRoom(g_Settings->getHelpRoom1());
  else if (gowhere == "成都") gotoRoom(g_Settings->getHelpRoom5());
  else if (gowhere == "沧州") gotoRoom(g_Settings->getHelpRoom4());
  else if (gowhere == "扬州") gotoRoom(g_Settings->getHelpRoom3());
  else if (gowhere == "荆州") gotoRoom(g_Settings->getHelpRoom6());
  else if (gowhere == "镇江") gotoRoom(g_Settings->getHelpRoom18());
  else if (gowhere == "平定州") gotoRoom(g_Settings->getHelpRoom17());
  else if (gowhere == "大理") gotoRoom(g_Settings->getHelpRoom20());
  else
  {
    long which;
    which = rand() % 100;
    if ( which < 12 ) gotoRoom(g_Settings->getHelpRoom1());
    else if ( which < 24 ) gotoRoom(g_Settings->getHelpRoom2());
    else if ( which < 36 ) gotoRoom(g_Settings->getHelpRoom3());
    else if ( which < 48 ) gotoRoom(g_Settings->getHelpRoom4());
    else if ( which < 60 ) gotoRoom(g_Settings->getHelpRoom6());
    else if ( which < 72 ) gotoRoom(g_Settings->getHelpRoom17());
    else if ( which < 84 ) gotoRoom(g_Settings->getHelpRoom20());
    else  gotoRoom(g_Settings->getHelpRoom5());
    return 1;
  }
  setBody(getBody()/10);
  return 1;
}
//------------------------------------------------------------------
//lp
int YPlayer::playertaxi(YString sentence)
{
  if (getplaySaySpeed() == 1 )
  {
    display("你按的那么快，我说系统怎么慢呢！。");
    return 3;
  }
  setplaySaySpeed(1);
  if (getDeposit() < g_Settings->getsitTextCost())
  {
     display ("车夫看了会你说：“没钱叫什么车啊！！”");
     return 1;
  }
  if (getStatus() != "")
  {
    display ("你正忙着干别的呢。");
    return 1;
  }
 /* if (getBody() < getMaxBody())
  {
    display ("你的气血值不满，不能使用这个命令！");
    return 1;
  }*/

  long numCash;
  YThing *objMoney;
  numCash=0;
  YPlayer* player;
  long old = getActorAge();
  
if (old >= 20){
  objMoney=(YThing*)player->findChildThing("金子");
  if(objMoney){
     numCash+=(objMoney->getCount())*10000;
  }
  objMoney=(YThing*)player->findChildThing("银子");
  if(objMoney){
     numCash+=(objMoney->getCount())*100;
  }
  objMoney=(YThing*)player->findChildThing("铜板");
  if(objMoney){
     numCash+=objMoney->getCount();
  }
  if(numCash<2000){
     display ("车夫一撇嘴:开什么玩笑,没钱做什么车?");
     return 1;
  }
  numCash-=2000; //剩下的钱
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  goldnum=numCash/10000; //剩余金
  silvernum=(numCash-goldnum*10000)/100; //剩余银
  coinnum=numCash%100; //剩余铜板
  if(goldnum!=0){
    objMoney=(YThing*)player->findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/金子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(goldnum);
  }
  else if(goldnum==0){
    objMoney=(YThing*)player->findChildThing("金子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(silvernum!=0){
    objMoney=(YThing*)player->findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/银子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(silvernum);
  }
  else if(silvernum==0){
    objMoney=(YThing*)player->findChildThing("银子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(coinnum!=0){
    objMoney=(YThing*)player->findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/铜板 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(coinnum);
  }
  else if(coinnum==0){
    objMoney=(YThing*)player->findChildThing("铜板");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
}
  YString gowhere =  sentence.getWord();
  if (old >= 20){
    display ("你拿出20银子，对车夫说，快走吧！");
  }
  else{
    display ("车夫对你说:孩子上车吧，我捎你一段路。");
  }
    display ("一阵马蹄声响，一驾马车来到你的面前，你坐上了马车。。。。。");
    getRoom()->getRoomChat()->talk(NULL,getActorName()+"随手招了一辆马车杨长而去。。。。。。",this);

  if (gowhere == "北京")
  {
    gotoRoom(g_Settings->getHelpRoom2());
  }
  else if (gowhere == "长安")
  {
   gotoRoom(g_Settings->getHelpRoom1());
  }
  else if (gowhere == "成都")
  {
   gotoRoom(g_Settings->getHelpRoom5());
  }
  else if (gowhere == "沧州")
  {
   gotoRoom(g_Settings->getHelpRoom4());
  }
  else if (gowhere == "扬州")
  {
   gotoRoom(g_Settings->getHelpRoom3());
  }
  else if (gowhere == "荆州")
  {
   gotoRoom(g_Settings->getHelpRoom6());
  }
  else if (gowhere == "少林")
  {
   gotoRoom(g_Settings->getHelpRoom7());
  }
  else if (gowhere == "武当")
  {
   gotoRoom(g_Settings->getHelpRoom9());
  }
  else if (gowhere == "明教")
  {
   gotoRoom(g_Settings->getHelpRoom8());
  }
  else if (gowhere == "古墓")
  {
   gotoRoom(g_Settings->getHelpRoom10());
  }
  else if (gowhere == "华山")
  {
   gotoRoom(g_Settings->getHelpRoom11());
  }
  else if (gowhere == "白驼")
  {
   gotoRoom(g_Settings->getHelpRoom12());
  }
  else if (gowhere == "峨嵋")
  {
   gotoRoom(g_Settings->getHelpRoom13());
  }
  else if (gowhere == "血刀")
  {
   gotoRoom(g_Settings->getHelpRoom14());
  }
  else if (gowhere == "四义")
  {
   gotoRoom(g_Settings->getHelpRoom15());
  }
  else if (gowhere == "丐帮")
  {
   gotoRoom(g_Settings->getHelpRoom16());
  }
  else if (gowhere == "嘉兴")
  {
   gotoRoom(g_Settings->getHelpRoom16());
  }
  else if (gowhere == "平定州")
  {
   gotoRoom(g_Settings->getHelpRoom17());
  }
  else if (gowhere == "日月神教")
  {
   gotoRoom(g_Settings->getHelpRoom17());
  }
  else if (gowhere == "镇江")
  {
   gotoRoom(g_Settings->getHelpRoom18());
  }
  else if (gowhere == "侠客岛")
  {
   gotoRoom(g_Settings->getHelpRoom19());
  }
  else if (gowhere == "大理")
  {
   gotoRoom(g_Settings->getHelpRoom20());
  }
  else if (gowhere == "桃花岛")
  {
   gotoRoom(g_Settings->getHelpRoom21());
  }
  else if (gowhere == "红花会")
  {
   gotoRoom(g_Settings->getHelpRoom22());
  }
  else if (gowhere == "开封")
  {
   gotoRoom(g_Settings->getHelpRoom23());
  }
  else if (gowhere == "神龙教")
  {
   gotoRoom(g_Settings->getHelpRoom24());
  }
  else if (gowhere == "灵鹫宫")
  {
   gotoRoom(g_Settings->getHelpRoom25());
  }
  else
  {
    display ("车夫打量了你两眼说道：“这位客官你到底要去那里啊？我们车行可只去有名气的大地方！”");
    return 1;
  }
  getRoom()->getRoomChat()->talk(NULL,getActorName()+"从一辆马车上面走了下来.",this);
  if (old >= 20){
	  display ("车夫后面叫到，客人慢走，欢迎下次光临！");
  }
  else{
	  display ("车夫对你说到，孩子江湖险恶，一路小心！");
  }
  setDeposit(getDeposit()-g_Settings->getsitTextCost());
  return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizkick(YString sentence)
{
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)    //人物的查看
  {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>由于你言行不当，惩罚自天而降。。。。。</font>");
     sb->faint();
     display ("你已经成功的使"+s+"昏到了");
  }
  else display ("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizclose(YString sentence)
{
   YPlayer* sb=g_PlayerManager->getPlayer(sentence);
   if (sb)     //人物查看
   {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>由于你言行不当，你的频道被封闭了。</font>");
     sb->setWizCloseChat(1);
     display ("成功关闭"+sentence+"的频道");
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizopen(YString sentence)
{
   YPlayer* sb=g_PlayerManager->getPlayer(sentence);
   if (sb)   //查看人物
   {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>你的频道被开启了。</font>");
     sb->setWizCloseChat(0);
     display ("你开启了"+sentence+"的频道。");
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::wizlook(YString sentence)
{
   YString sbname = sentence.getWord();
   YString shuxing="" ;
   long number=0;
   YString zifu ="";
   long flag = 0;
   YActor* sb=g_PlayerManager->getActor(sbname);
   if (sb)   //查看人物
   {
     if (wizcompare(sb)) return 1;
     sb->onBeforeSave();
     while ((shuxing = sentence.getWord()) != "")
     {
        if (shuxing == "allthing")
        {
          display (sbname+"携带物品："+sb->enumChildrenThing()+
                   "携带人物："+sb->enumChildrenActor());
          return 1;
        }
        number = sb->getAsLong(shuxing);
        zifu = sb->getAsString(shuxing);
        if (number != 0)display (shuxing + " : "+ (YString)number);
        else if (zifu != "") display (shuxing +" : " +zifu);
        else display ("没有属性"+shuxing + "或其值为0");
        flag = 1;
     }
     if (flag == 1 ) return 1;
     display("年龄"+(YString)sb->getActorAge());
     // 显示技能
     YString jineng = sb->getAllSkillsList();//getAsString("所会技能");
     display("所会技能"+jineng);
     YString tempjineng = jineng.getWord();
     YString exp;
     while ((tempjineng = jineng.getWord()) != "")
     {
       exp = jineng + "_经验";
       display (tempjineng+"技能级别"+(YString)sb->getAsLong(tempjineng)+"技能经验"+(YString)sb->getAsLong(exp));
     }
     display("气血"+(YString)sb->getBody()
             +"最大气血"+(YString)sb->getMaxBody());
     display("内力"+(YString)sb->getInternalForce()
             +"最大内力"+(YString)sb->getMaxInternalForce());
     display("精力"+(YString)sb->getEnergy()
             +"最大精力"+(YString)sb->getMaxEnergy());
     display("经验"+(YString)sb->getExperience()
             +"潜能"+(YString)sb->getPotential());
     display("容貌"+(YString)sb->getFeature()
             +"福缘"+(YString)sb->getLuck());
     if ( sb->isTypeOf("YPlayer"))
     {
       YPlayer* TempPlayer = (YPlayer*)sb;
       display("杀人次数"+(YString)TempPlayer->getKillTimes()
             +"被杀次数"+(YString)TempPlayer->getBeKillTimes());
       display("后天悟性"+(YString)TempPlayer->getLastLearn()
             +"后天根骨"+(YString)TempPlayer->getLastForce());
       display("后天臂力"+(YString)TempPlayer->getLastArm()
            +"后天身法"+(YString)TempPlayer->getlaseDodge());
       display("攻击力"+(YString)TempPlayer->getInhereAttack()
             +"防御力"+(YString)TempPlayer->getInhereDefense());
       display("负重"+(YString)TempPlayer->getWeight()
             +"最大负重"+(YString)TempPlayer->getMaxWeight());
     }
     display("携带物品" + sb->enumChildrenThing() +"<br>"+ "携带人物"+sb->enumChildrenActor());
     sb->onAfterLoad();
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::dazuo(YString sentence)
{
    if (getStatus() != "")
    {
      display ("你正忙着呢。");
      return 1;
    }
    if (getBaseForce() < 10 )
    {
      display ("你的基本内功等级还不够，不能打坐。");
      return 1;
    }
    long howmuch = sentence.toLong();
    if (howmuch < getBody())
    {
      if ((howmuch+ getInternalForce())>(2*getMaxInternalForce()))
      {
        display ("你的内力已经到上限了。");
        return 1;
      }
      if (howmuch < 0) howmuch =1;
      setDazuoTime((howmuch*500)/(getBaseForce()));//set ("打坐时间", ((howmuch*1000))/(getBaseForce()));
      setStatus("打坐");
      display("你盘膝坐下开始打坐。");
      showPhoto("2","6");
    }
    else display ("你的气血已经不够了.");
    return 1;
}
//----------------------------------------------------------------------
//lp--------------------------------------------------------------
int YPlayer::tuna(YString sentence)
{
    if (getStatus() != "")
    {
      display ("你正忙着呢。");
      return 1;
    }
    if (getBaseForce() < 10 )
    {
      display ("你的基本内功等级还不够，不能吐纳。");
      return 1;
    }
    long howmuch = sentence.toLong();
    if (howmuch < getBody())
    {
      if ((howmuch+ getEnergy())>(2*getMaxEnergy()))
      {
        display ("精力是不可以达到最大值两倍以上的。");
        return 1;
      }                               //< 10 判断了
      if (howmuch < 0) howmuch =1;
      setTunaTime((howmuch*500)/(getBaseForce()));//set ("吐纳时间",(howmuch*1000)/(getBaseForce()));
      setStatus("吐纳");
      display ("你闭目坐下开始吐那练精.");
      showPhoto("2","6");
    }
    else display ("你没有那么多的气血.");
    return 1;
}
//----------------------------------------------------------------------
int YPlayer::bai(YString sentence)
{
 YString s=sentence.getWord(); //"sb."
 YAbstractActor* sb=getRoom()->findChildActor(s);
 if(!sb) //查看人物
 { display ("没有这个人物。");}
 else
 {
        sb->executeCommandAsTarget(this,"bai "+s);
 }
 return 1;
}
//--------------------------------------------------------
int YPlayer::hp(void)
{
        refreshHP();
        YString life=getBody();
        YString maxlife=getMaxBody();
        YString mind=getEnergy();
        YString maxmind=getMaxEnergy();
        YString body=getInternalForce();
        YString maxbody=getMaxInternalForce();
        YString exp=getExperience();
        YString study=getPotential();
        YString food=getFood();
        YString worter=getDrink();
        YString jiali=getForceAttack();
        if (maxlife.toLong() < life.toLong()) life = maxlife ;
        if (life.toLong() < 0 ){ life = "0"; setBody(0);}//set ("气血",0);}
        if (mind.toLong() < 0 ){ mind = "0"; setEnergy(0);}// set ("精力",0);}
        if (body.toLong() < 0 ){ body = "0";  setInternalForce(0);}//set ("内力",0);}
        display ("气血"+life+"                  "+"最大气血"+maxlife);
        display ("精力"+mind+"                  "+"最大精力"+maxmind);
        display ("内力"+body+"                  "+"最大内力"+maxbody);
        display ("食物"+food+"                  "+"饮水"+worter);
        display ("经验"+exp+"                   "+"潜能"+study);
        display ("加力"+jiali);
        return 1;
}
//--------------------------------------------------------
int YPlayer::hp_b(void)
{
  refreshHP();
  return 1;
}
//--------------------------------------------------------
int YPlayer::bskills(YString sentence) //查看劳动技能
{
   YString allwork=getworkskills();  //getAsString("所会技能");
   if (allwork == "" )display ("你现在什么也不会。");
   YString tempwork;
   YString tempworkexp;
   long exp;
   while ( (tempwork = allwork.getWord()) != "")
   {
      long level=getSkillLevel(tempwork);//getAsLong(type);  //级别
      tempworkexp =  tempwork + "_经验" ;
      exp = getAsLong(tempworkexp);
      display (tempwork+"级别："+(YString)level +"经验："+(YString)exp);
   }
   return 1;
}
//--------------------------------------------------------
int YPlayer::skills(YString sentence) //查看武功
{
        YString s=sentence.getWord(); //sb
        if (s=="")
        {
                YString wugong=getAllSkillsList();//getAsString("所会技能");
                if (wugong == "" )display ("你现在什么也不会。");
                //逐个武功的显示
                YString type ;
                YString enable = "";
                //取得攻击武功的类型
                YString jian = getAsString("剑_攻击武功");
                YString dao =  getAsString("刀_攻击武功") ;
                YString gun =  getAsString("棍_攻击武功") ;
                YString kongshou =  getAsString("空手_攻击武功") ;
                YString bian =  getAsString("鞭_攻击武功") ;
                YString zhang = getAsString("杖_攻击武功") ;
                YString qiang = getAsString("枪_攻击武功") ;
                YString chui = getAsString("锤_攻击武功") ;
                YString anqi = getAsString("暗器_攻击武功") ;
                YString qinggong = getDodgeUsing() ;
                YString neigong = getForceUsing();
                YString  alldisplay ;
                while ( (type=wugong.getWord()) != "") //类型
                {
                        //判断是否是攻击武功
                        enable = "&nbsp;&nbsp;&nbsp;&nbsp;";
                        if (type == jian) enable = "<font color=red>★</font>";
                        else if (type == gun) enable = "<font color=red>★</font>";
                        else if (type == kongshou ) enable = "<font color=red>★</font>";
                        else if (type == dao ) enable = "<font color=red>★</font>";
                        else if (type == zhang ) enable = "<font color=red>★</font>";
                        else if (type == bian ) enable = "<font color=red>★</font>";
                        else if (type == qiang ) enable = "<font color=red>★</font>";
                        else if (type == chui ) enable = "<font color=red>★</font>";
                        else if (type == qinggong ) enable = "<font color=red>★</font>";
                        else if (type == neigong ) enable = "<font color=red>★</font>";
                        else if (type == anqi ) enable = "<font color=red>★</font>";

                        long leve=getSkillLevel(type);//getAsLong(type);  //武功级别
                        long Actorleve=leve;  //武功级别
                        YString typeexp=type+"_经验";   //武功经验
                        YString exp=getAsLong(typeexp);
                        YString miaoshu ="" ;
                        miaoshu = jiebiemiaoshu (Actorleve /5) ;
                        alldisplay = "<table  width=100% style=font-size:9pt><tr><td width=30% rowspan=2>"+enable+type+"</td><td width=30%>"+miaoshu+"</td><td width=40%>级别:"+(YString)leve+"</td></tr><tr><td width=80% colspan=2>经验:"+exp+"</td></tr></table>";
                        display (alldisplay,false) ;

                }
        }
        else
        {
                YAbstractActor* sb=getRoom()->findChildActor(s);
                if (!sb)  // 人物的指针
                {
                        display("没有该人物。");
                }
                else
                {
                   if ((s != getTeacherName())  && (getLevel() < 50))
                   {
                          display("你只能察看师父的武功。");
                          return 1;
                   }
                   YString wugong=((YActor*)sb)->getAllSkillsList();
                   if (wugong == "") display (s+"什么也不会");
                   YString type; //类型
                   while( (type=wugong.getWord()) != "")//类型
                   {
                        YString leve=sb->getAsLong(type);  //武功级别
                        long Actorleve=sb->getAsLong(type);  //武功级别
                        YString typeexp=type+"_经验";   //武功经验
                        YString exp=sb->getAsLong(typeexp);
                        YString miaoshu ="" ;
                        miaoshu = jiebiemiaoshu (Actorleve /5) ;
                        display (type+miaoshu+"                  武功级别:"+leve+"                  武功经验:"+exp);
                   }
                }
        }
       return 1;
}
//--------------------------------------------------------
int YPlayer::skills_b(void) //查看武功
{
  YString skillsInfo="";
  YString wugong=getAllSkillsList();//getAsString("所会技能");
  YString type; //类型
  if (wugong == "" ) skillsInfo="你现在什么也不会。";
  YString enable ="";
  //取得攻击武功的类型
  YString jian = getAsString("剑_攻击武功");
  YString dao =  getAsString("刀_攻击武功") ;
  YString gun =  getAsString("棍_攻击武功") ;
  YString kongshou =  getAsString("空手_攻击武功") ;
  YString bian =  getAsString("鞭_攻击武功") ;
  YString qiang =  getAsString("枪_攻击武功") ;
  YString chui =  getAsString("锤_攻击武功") ;
  YString zhang = getAsString("杖_攻击武功") ;
  YString anqi = getAsString("暗器_攻击武功") ;
  YString qinggong = getDodgeUsing() ;
  YString neigong = getForceUsing();
 //逐个武功的显示
  while ( (type=wugong.getWord()) != "")  //类型
  {
    //判断是否是攻击武功
    enable = "&nbsp;&nbsp;";
    if (type == jian) enable = "<font color=red>★</font>";
    else if (type == gun) enable = "<font color=red>★</font>";
    else if (type == kongshou ) enable = "<font color=red>★</font>";
    else if (type == dao ) enable = "<font color=red>★</font>";
    else if (type == zhang ) enable = "<font color=red>★</font>";
    else if (type == bian ) enable = "<font color=red>★</font>";
    else if (type == qiang ) enable = "<font color=red>★</font>";
    else if (type == chui ) enable = "<font color=red>★</font>";
    else if (type == anqi ) enable = "<font color=red>★</font>";
    else if (type == qinggong ) enable = "<font color=red>★</font>";
    else if (type == neigong ) enable = "<font color=red>★</font>";
    YString leve=getSkillLevel(type);  //武功级别
    long Actorleve=getSkillLevel(type);//getAsLong(type);  //武功级别
    YString typeexp=type+"_经验";   //武功经验
    YString exp=getAsLong(typeexp);
    YString miaoshu ="" ;
    miaoshu = jiebiemiaoshu (Actorleve /5) ;
    skillsInfo+=enable+type+miaoshu+"级别:"+leve+"经验:"+exp+"<br>";
  }
  skillsInfo="showinfo2(\""+skillsInfo.toInnerString()+"\")";
  display(skillsInfo,false,JAVASCRIPT_MSG);
  return 1;
}
//--------------------------------------------------------
int YPlayer::score(void) //查看个人状态
{
        playerarmchange();
        display ("姓名          "+getActorName()+"&nbsp;&nbsp;&nbsp;");
        long playerlevel = getLevel();
        /*if  ( playerlevel > 90 ) display ("级别：    天神" );
        else if  ( playerlevel > 50 ) display ("级别：    巫师" );
        else if  ( playerlevel >= 0 ) display ("级别：    玩家" );*/
        if (isTypeOf("YWizard"))  display ("级别：    巫师" );
        else  display ("级别：    玩家" );
        YString sex ="女" ;
        if (getSexString() != "女" ) sex = "男";
        YString nick =getNick();// getAsString ("绰号");
        if (nick != "")nick = "你的绰号是["+nick+"]";
        //
        YString sFactionName=getFactionName();  //加入帮派
        if(sFactionName != ""){
          display("你是["+sFactionName+"]的["+getFactionTitle()+"]");
        }
        //
        display ("你是一位"+(YString)getActorAge()+"岁的"+sex+"性."+nick);
        YString shifu = getTeacherName();//getAsString("师父");
        if (shifu != "") display ("你的师父是"+shifu+"。");
        YString hit=getInhereAttack();
        YString fierce=getWeaponAttack();
        YString deff=getInhereDefense();
        YString adddeff=getAppendDefense();
        YString gengu=getLastForce();
        YString shenfa=getlaseDodge();
        YString bili=getLastArm();
        YString wuxing=getLastLearn();
        if (adddeff.toLong() < 0)  //附加防御力
        {
          adddeff = "0";
          setAppendDefense(0) ;
        }
        if (fierce.toLong() < 0)   //武器攻击力
        {
           fierce = "0" ;
           setWeaponAttack(0);
        }
        display ("臂力 "+bili+"&nbsp;&nbsp;悟性"+wuxing+"&nbsp;&nbsp;根骨"+gengu+"&nbsp;&nbsp;身法"+shenfa);
        display ("攻击力"+hit+ "（"+(fierce)+"）"+"&nbsp;&nbsp;"+"防御力"+deff+"（"+(YString)adddeff+"）"+"&nbsp;&nbsp;&nbsp;");
        YString color = "blue" ;//正气值的显示颜色
        if (getGoodnessCount() < 0) color = "red";
        display ("正气值:&nbsp;&nbsp;&nbsp;&nbsp;<font color="+color+">"+(YString)getGoodnessCount()+"</font>"
                +"你杀了<font color=red>"+(YString)getKillTimes()+"</font>人,其中杀死其他玩家<font color=red>"+(YString)getPKTimes()+"</font>次");
        display ("被杀了<font color=green>"+(YString)getBeKillTimes()+"</font>次其中被其他玩家杀了<font color=blue>"+(YString)getBePKTimes()+"</font>次");
        display ("你的江湖声望："+(YString)getSocietyValue());
        display ("你的朝廷声望："+(YString)getCourtValue());
        display ("你的门派评价："+(YString)getPartyValue());
        return 1;
}
//--------------------------------------------------------
int YPlayer::score_b(void) //查看个人状态
{
        playerarmchange();
        YString scoreInfo;
        scoreInfo="姓名&nbsp;&nbsp;&nbsp;"+getActorName()+"&nbsp;&nbsp;&nbsp;";
        long playerlevel = getLevel();
        /*
        if  ( playerlevel > 90 ) scoreInfo+="级别：    天神<br>";
        else if  ( playerlevel > 50 ) scoreInfo+="级别：    巫师<br>";
        else if  ( playerlevel >= 0 ) scoreInfo+="级别：    玩家<br>";
        */
        if (isTypeOf("YWizard"))  scoreInfo+="级别：    巫师<br>";
        else   scoreInfo+="级别：    玩家<br>";
        YString sex = getSexString();
        if (sex == "") sex = "男";
        scoreInfo+="你是一位"+(YString)getActorAge()+"岁的"+sex+"性.<br>";
        YString nick = getNick();// getAsString ("绰号");
        if (nick != "" )scoreInfo+="你的绰号是"+nick+"<br>";
        YString hit=getInhereAttack();
        YString fierce=getWeaponAttack();
        YString deff=getInhereDefense();
        YString adddeff=getAppendDefense();
        YString gengu=getLastForce();
        YString shenfa=getlaseDodge();
        YString bili=getLastArm();
        YString wuxing=getLastLearn();
        if (adddeff.toLong() < 0)  //附加防御力
        {
          adddeff = "0";
          setAppendDefense(0) ;
        }
        if (fierce.toLong() < 0)   //武器攻击力
        {
           fierce = "0" ;
           setWeaponAttack(0);
        }
        scoreInfo+="臂力"+bili+"&nbsp;&nbsp;&nbsp;&nbsp;悟性"+wuxing+"<br>根骨"+gengu+"&nbsp;&nbsp;&nbsp;&nbsp;身法"+shenfa+"<br>";
        scoreInfo+="攻击力"+hit+ "（"+(fierce)+"）"+"&nbsp;&nbsp;&nbsp;"+"防御力"+deff+"（"+(YString)adddeff+"）"+"<br>";
        scoreInfo+="正气值:&nbsp;&nbsp;&nbsp;&nbsp;"+(YString)getGoodnessCount()+"<br>你杀了"+(YString)getKillTimes()+"人&nbsp;&nbsp;&nbsp;&nbsp;其中杀死其他玩家"
                   +(YString)getPKTimes()+"<br>被杀了"+(YString)getBeKillTimes()+"次&nbsp;&nbsp;&nbsp;&nbsp;其中被其他玩家杀死"+(YString)getBePKTimes();
        scoreInfo="showinfo2(\""+scoreInfo.toInnerString()+"\")";
        display(scoreInfo,false,JAVASCRIPT_MSG);
        return 1;
}
//--------------------------------------------------------
int YPlayer::dorenew(void)
{
        long merenew=getBeginForce();
        long life=getBody();
        long mind=getEnergy();
        long body=getInternalForce();
        long maxlife=getMaxBody();
        long maxmind=getMaxEnergy();
        long maxbody=getMaxInternalForce();
        long food=getFood();
        long worter=getDrink();
        //身体的恢复速度对根骨高的更有效
        merenew = merenew + getLastForce();//和任务的智力有同样的变化
        if (merenew == 0 )return 1;
//        this->display("气血"+LongToChinese(life)+"精力"+LongToChinese(mind)+"内力"+LongToChinese(body));
        if ( food > 0 && worter > 0)
        {
                if ( life + merenew >= maxlife)
                {
                        setBody(maxlife);
                 //       display ("气血"+LongToChinese(life));
                }
                else setBody(life+merenew);
                if ( mind + merenew >= maxmind)
                {
                       if (mind < maxmind) setEnergy(maxmind);
                //        display ("精力"+LongToChinese(life));
                }
                else setEnergy(mind+merenew);
                if ( body + merenew >= maxbody)
                {
                        if (body < maxbody)setInternalForce(maxbody);
                //        display ("内力"+LongToChinese(life));
                }
                else setInternalForce(body+merenew);
        }
        else {}
        //消除任务的间隔
        YString myquest = g_Quest->getAllNPCName();
        YString tempmyquest = myquest.getWord();
        while (tempmyquest != "")
        {
           tempmyquest = tempmyquest +"_任务间隔";
           set (tempmyquest , 0);
           tempmyquest = myquest.getWord();
        }
        return 1;
}
//-----------------------------------------
int YPlayer::enable(YString sentence)
{
        YString type = sentence.getWord() ;
        YString useAllwugong = getAllSkillsList();//getAsString("所会技能");
        YString wugong = sentence.getWord() ;
        //处理没有功夫的类型
        if (findStringInStr (useAllwugong , type))
        {
           YString usewugong = g_Wugong->wugong_leixing(type);
           if (type.find("基本",0) != YString::npos )
           {
             display ("你不能激发你的武功为基本武功");
             return 1;
           }
           if ( usewugong == "剑法" )
           {
              set("剑_攻击武功",type);
              display("你设置你的攻击剑法为"+type);
           }
           else if (usewugong == "掌法" )
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "指法" )
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "拳法" )
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "腿法")
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "手法")
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "爪法")
           {
              set("空手_攻击武功",type);
              display ("你设定你的攻空手击武功为"+type);
           }
           else if (usewugong == "枪法")
           {
              set("枪_攻击武功",type);
              display ("你设定你的枪法攻击武功为"+type);
           }
           else if (usewugong == "锤法")
           {
              set("锤_攻击武功",type);
              display ("你设定你的锤法攻击武功为"+type);
           }
           else if (usewugong == "棍法")
           {
              set("棍_攻击武功",type);
              display ("你设定你的棍法攻击武功为"+type);
           }
           else if (usewugong == "刀法")
           {
              set("刀_攻击武功",type);
              display ("你设定你的刀法攻击武功为"+type);
           }
           else if (usewugong == "鞭法")
           {
              set("鞭_攻击武功",type);
              display ("你设定你的鞭法攻击武功为"+type);
           }
           else if (usewugong == "暗器法")
           {
              set("暗器_攻击武功",type);
              display ("你设定你的暗器攻击武功为"+type);
           }
           else if (usewugong == "轻功")
           {
              setDodgeUsing(type);
              //set("轻功_使用",type);
              display ("你设定你的闪躲轻功为"+type);
           }
           else if (usewugong == "内功")
           {
              setForceUsing(type);
              display ("你使用的内功设为"+type);
           }
           else display("武功出错了请和巫师联系或发到mud论坛"+type+"出错");
        }
        //处理有类型的武功
        else if ( findStringInStr (useAllwugong , wugong) )
        {
          YString usewugong = g_Wugong->wugong_leixing(wugong);
          if (wugong.find("基本",0) != YString::npos )
          {
             display ("你不能激发你的武功为基本武功");
             return 1;
          }
          if (type == "剑法")
          {
            if (usewugong == "剑法")
            {
              set("剑_攻击武功",wugong);
              display("你设置你的攻击剑法为"+wugong);
            }
            else display ("这种武功不是"+type+"。");
          }
          else if (type == "空手")
          {
            if (usewugong == "掌法")
            {
              set("空手_攻击武功",wugong);
              display ("你设定你的攻空手击武功为"+wugong);
            }
            else if (usewugong == "拳法")
            {
              set("空手_攻击武功",wugong);
              display ("你设定你的空手攻击武功为"+wugong);
            }
            else if (usewugong == "指法")
            {
              set("空手_攻击武功",wugong);
              display ("你设定你的空手攻击武功为"+wugong);
            }
            else display ("这种武功不是"+usewugong+"。");
          }
          else if (type == "枪法")
          {
            if (usewugong == "枪法")
            {
              set("枪_攻击武功",wugong);
              display ("你设定你的枪法攻击武功为"+wugong);
            }

            else display ("这种武功不是"+type+"。");
          }
          else if (type == "锤法")
          {
            if (usewugong == "锤法")
            {
              set("锤_攻击武功",wugong);
              display ("你设定你的锤法攻击武功为"+wugong);
            }

            else display ("这种武功不是"+type+"。");
          }
          else if (type == "棍法")
          {
            if (usewugong == "棍法")
            {
              set("棍_攻击武功",wugong);
              display ("你设定你的棍法攻击武功为"+wugong);
            }
            else display ("这种武功不是"+type+"。");
          }
          else if (type == "刀法")
          {
            if (usewugong == "刀法")
            {
              set("刀_攻击武功",wugong);
              display ("你设定你的刀法攻击武功为"+wugong);
            }
            else display ("这种武功不是"+type+"。");
          }
          else if (type == "鞭法")
          {
            if (usewugong == "鞭法")
            {
              set("鞭_攻击武功",wugong);
              display ("你设定你的鞭法攻击武功为"+wugong);
            }
            else display ("这种武功不是"+type+"。");
          }
          else if (type == "暗器法")
          {
            if (usewugong == "暗器法")
            {
              set("暗器_攻击武功",wugong);
              display ("你设定你的暗器攻击武功为"+wugong);
            }
            else display ("这种武功不是"+type+"。");
          }
          else if (type == "轻功")
          {
            if (usewugong == "轻功")
            {
              setDodgeUsing(wugong);//set("轻功_使用",wugong);
              display ("你设定你的闪躲轻功为"+wugong);
            }
            else display ("这种武功不是轻功。");
          }
          else if (type == "招架")
          {
            if ((usewugong != "内功") && (usewugong != "轻功"))
            {
              setParryUsing(wugong);
              display("你的招架开始使用"+wugong);
            }
            else display ("这种武功不可以用做招架。");
          }
          else if (type == "内功")
          {
            if (usewugong == "内功")
            {
              setForceUsing(wugong);
              display ("你使用的内功设为"+wugong);
            }
            else display ("这种武功不是内功。");
          }
          else display ("没有这种武功类型,使用格式为 enable 剑法（招架。。） 华山剑法（你所会的武功）");
        }
        else display ("你不会这种功夫。使用格式为 enable 剑法(招架。。) 华山剑法（你所会的武功）");
        playerhpchange();
        return 1;
}
//-----------------------------------------
int YPlayer::quit(void)
{
        setBattle(0);//set ("战斗",0);
        setKill(0);//set ("对杀",0);
        setBusy(0);//set ("繁忙",0);
        setAllEnemyList("");//set ("杀死","");
        setSameRoomEnemyList("");//房间内敌人
        setAdversary("");
        setYouFollow("");//set ("跟随","");
        setFollowYou("");//set ("跟随的人","");
        setStatus("");
        setWeaponName("");//set ("武器","");
        setWeaponType("");//set ("武器类型","");
        setWeaponAttack(0);//set ("武器攻击力",0);
        setArmor("");//set ("盔甲","");
        setHat("");//set ("帽子","");
        setClothName("");//set ("衣服","");
        setShoe("");//set ("鞋","");
        setInhereDefense(0);//set ("附加防御力",0);
        setFlower("");//set ("花","");
        setRing("");//set ("项链","");
        setNecklace("");//set ("戒指","");
        setBangle("");
        setAddFeature(0);//set ("附加容貌值",0);
        setAddLuck(0);//set ("附加福缘",0);
//        set ("玩家开启频道列表","");
//        set ("玩家关闭频道列表","");
        playerarmchange();
        setFreeTime(0);//set ("空闲时间",0);
        setDazuoTime(0);//set ("打坐时间",0);
        setTunaTime(0);//set ("吐纳时间",0);
        setZdpk(0);//set ("主动pk",0);
        delname();
        delQuest();
        //丢掉人物
        dropplayer();
/*        YString thingList=enumChildrenActor(); //身上的人物
        YString tempThing; //临时物品
        YAbstractActor* isactor;
        while((tempThing=thingList.getWord())!="")
        {
           isactor=this->findChildActor(tempThing);
           if(!isactor) continue;
           giveChildTo(isactor,getRoom());
           display ("你丢下了"+tempThing);
        } */
        //退定频道
        g_SystemChat->unsubscribe(this);
        g_NormalChat->unsubscribe(this);
        g_NewUserChat->unsubscribe(this);
        g_RumorChat->unsubscribe(this);
        if (m_menpaichat) m_menpaichat->unsubscribe(this);
        //玩家帮派
        if(getFactionChat()) getFactionChat()->unsubscribe(this); //帮派频道退订
        //玩家帮派结束
        //因为析构函数中的save不能正常使用子类(YWizard)的虚函数故而将其放置于此
        save();
        return 0;
}

//-----------------------------------------
int YPlayer::cquit(YString command)
{
	YString cmd=command;
        setBattle(0);//set ("战斗",0);
        setKill(0);//set ("对杀",0);
        setBusy(0);//set ("繁忙",0);
        setAllEnemyList("");//set ("杀死","");
        setSameRoomEnemyList("");//房间内敌人
        setAdversary("");
        setYouFollow("");//set ("跟随","");
        setFollowYou("");//set ("跟随的人","");
        setStatus("");
        setWeaponName("");//set ("武器","");
        setWeaponType("");//set ("武器类型","");
        setWeaponAttack(0);//set ("武器攻击力",0);
        setArmor("");//set ("盔甲","");
        setHat("");//set ("帽子","");
        setClothName("");//set ("衣服","");
        setShoe("");//set ("鞋","");
        setInhereDefense(0);//set ("附加防御力",0);
        setFlower("");//set ("花","");
        setRing("");//set ("项链","");
        setNecklace("");//set ("戒指","");
        setBangle("");        
        setAddFeature(0);//set ("附加容貌值",0);
        setAddLuck(0);//set ("附加福缘",0);        
//        set ("玩家开启频道列表","");
//        set ("玩家关闭频道列表","");
        playerarmchange();
        setFreeTime(0);//set ("空闲时间",0);
        setDazuoTime(0);//set ("打坐时间",0);
        setTunaTime(0);//set ("吐纳时间",0);
        setZdpk(0);//set ("主动pk",0);
        delname();
        cdelQuest(cmd);
        //丢掉人物
        dropplayer();
        //退定频道
        g_SystemChat->unsubscribe(this);
        g_NormalChat->unsubscribe(this);
        g_NewUserChat->unsubscribe(this);
        g_RumorChat->unsubscribe(this);
        if (m_menpaichat) m_menpaichat->unsubscribe(this);
        //玩家帮派
        if(getFactionChat()) getFactionChat()->unsubscribe(this); //帮派频道退订
        //玩家帮派结束
        //因为析构函数中的save不能正常使用子类(YWizard)的虚函数故而将其放置于此
        save();
        return 0;
}

//-----------------------------------------
int YPlayer::xue(YString command)
{
  YString cmd=command;
  YString teacherName=cmd.getWord();
  YAbstractActor* objTeacher=getRoom()->findChildActor(teacherName);
  if(!objTeacher) display("你要向谁学习?");
  else objTeacher->executeCommandAsTarget(this,"xue "+command);
  return 1;
}

//--------------------------------------------------------------
int YPlayer::cunquit(YString command)
{
  YString cmd=command;
  YString renwuName=cmd.getWord();
  YString commandCount=cmd.getWord(); //存任务的次数
  long howmuch=commandCount.toLong();
  if (howmuch > 0) howmuch=howmuch;
  else howmuch = 0;
  long numCash;
  long questmuch;
  YAbstractThing* objMoney;
  long old = getActorAge();

  YString allquest = getQuestList();//getAsString("任务列表");
  YString givename = "";
   while ((givename = allquest.getWord()) != "")
      {
      if (givename == renwuName)
        {
	long questTimes=getAsLong(renwuName+"_连续次数");
	if (questTimes < howmuch)
	{
	  display("你没有那么多的任务！");
	  return 1;
	}
	
  numCash=0;
if (old > 16){
  objMoney=findChildThing("金子");
  if(objMoney){
     numCash+=(objMoney->getCount())*10000;
  }
  objMoney=findChildThing("银子");
  if(objMoney){
     numCash+=(objMoney->getCount())*100;
  }
  objMoney=findChildThing("铜板");
  if(objMoney){
     numCash+=objMoney->getCount();
  }
  questmuch = 500 * howmuch;
  if(numCash < questmuch){
     display ("你身上没那么多现金！");
     return 1;
  }
  numCash-= questmuch; //剩下的钱
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  goldnum=numCash/10000; //剩余金
  silvernum=(numCash-goldnum*10000)/100; //剩余银
  coinnum=numCash%100; //剩余铜板
  if(goldnum!=0){
    objMoney=findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/金子 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(goldnum);
  }
  else if(goldnum==0){
    objMoney=findChildThing("金子");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(silvernum!=0){
    objMoney=findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/银子 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(silvernum);
  }
  else if(silvernum==0){
    objMoney=findChildThing("银子");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(coinnum!=0){
    objMoney=findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/铜板 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(coinnum);
  }
  else if(coinnum==0){
    objMoney=findChildThing("铜板");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
}
//	display("保存"+(YString)howmuch+ "个" + renwuName + "任务成功，你已经退出江湖！");
     	YString tempStr="_连续次数" ;
     	tempStr = renwuName + tempStr;
	set(tempStr,howmuch);
	cquit(renwuName);
        return 0;
	}
      }
   display("你没有这个人的任务！");
   return 1;
}
//-----------------------------------------
int YPlayer::fangqi(YString command)
{

  YString fangqi = command.getWord();
  YString wugong = getAllSkillsList();//getAsString("所会技能");
  YString tempwugong = wugong;
  YString temp ;
  while((temp =tempwugong.getWord()) != "")
  {
    if (temp == fangqi)
    {
        wugong.removeWord(fangqi);
        setAllSkillsList(wugong);
        //set ("所会技能",wugong);
        display ("你放弃了"+temp+"这种武功。");
        //setSkillLevel(temp,0);
        if (temp == getAsString("剑_攻击武功")) set("剑_攻击武功","");
        else if (temp == getAsString("空手_攻击武功")) set("空手_攻击武功","");
        else if (temp == getAsString("枪_攻击武功")) set("枪_攻击武功","");
        else if (temp == getAsString("刀_攻击武功")) set("刀_攻击武功","");
        else if (temp == getAsString("鞭_攻击武功")) set("鞭_攻击武功","");
        else if (temp == getAsString("棍_攻击武功")) set("棍_攻击武功","");
        return 1;
    }
  }
  display  ("你不会这项武功。");
  return 1;
}
//---------------------------------------------
int YPlayer::black(YString command)
{
   YPlayer* sb=g_PlayerManager->getPlayer(command);
   if (sb)  //判断人物指针
   {
      YString allname = getAsString("关闭对话列表");
      YString tempname = allname;
      YString name = "";
      while ((name =tempname.getWord()) != "")
      {
        if ( name == command )
        {
          display ("你已经关闭了和"+command+"的对话了。");
          return 1;
        }
      }
      set ("关闭对话列表",command+" "+allname);
      display ("你关闭了和"+command+"的对话了。");
   }
   else if (command == "all")
   {
      set ("关闭对话列表" , "全部人物名称");
      display ("现在没有人可以和你说话了") ;
   }
   else display ("没有这个人物。");
   return 1;
}
//---------------------------------------------
int YPlayer::unblack(YString command)
{
   YPlayer* sb=g_PlayerManager->getPlayer(command);
   if (sb)  //判断人物指针
   {
      YString allname = getAsString("关闭对话列表");
      YString tempname = allname;
      long flag = 0;
      allname = "" ;
      YString name = "";
      while ((name =tempname.getWord()) != "")
      {
        if ( name == command )
        {
          display ("你已经打开了和"+command+"的对话了。");
          name="";
          flag = 1;
        }
        allname =name+" "+allname  ;
      }
      if (flag == 1)
      {
        set ("关闭对话列表",allname);
        return 1;
      }
      else display ("你并没有关闭了和"+command+"的对话。");
   }
   else if ( command == "all" )
   {
      set ("关闭对话列表" , "");
      display ("现在所有人都可以和你说话了") ;
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//lp------------------------------------------------------------------
int YPlayer::wimpy(YString sentence)
{
        YString munch=sentence.getWord(); //数量
        long longmunch=munch.toLong();
        if (longmunch == 0) display ("留得青山在，不怕没材烧。。还是给自己留点余地吧。");
        else
        {
          setWimpy(longmunch);//set("逃跑系数",longmunch);
          display("你设定你的逃跑系数为"+munch);
        }
        return 1;
}
//---------------------------------------------------------------------
//lp
int YPlayer::lian(YString sentence)
{
   long jingli = getEnergy()  ;
   long qixue = getBody()  ;
   long spendqixue = g_Settings->getsitLianSpendQi();//getAsLong("练功气血");
   long spendjingli = g_Settings->getsitLianSpendJing();//getAsLong("练功精力") ;
   long much = sentence.toLong();
   if (much <= 0) much = 1;
   else if (much > 100 ) much =100;
   if ( jingli > spendjingli)
   {
      if (much*spendjingli > jingli )much = (jingli-1) / spendjingli ; //保留精力
      jingli = jingli  -  much*spendjingli ;
      if  ( qixue > spendqixue)
      {
        if (much*spendqixue > qixue )much = (qixue-1) / spendqixue ; //保留起血
        qixue = qixue -  much*spendqixue ;
        YString type=sentence.getWord();
        YString wuqi=getWeaponType();//getAsString("武器类型");
        if (wuqi == "")wuqi = "空手"  ;
        YString wugong = wuqi+ "_攻击武功" ;
        YString usewugong = getAsString (wugong);
        if (usewugong != "")
        {
          long lianlevel = getSkillLevel(usewugong);
          //200级以上是用潜能增加的速度加快。
          if (lianlevel >= 250)
          {
              if (getPotential() > much)
              {
                 setPotential(getPotential()-much);
              }
              else
              {
                if (getPotential() == 0)
                {
                  display("没有潜能了你怎么练习"+usewugong+"？");
                  return 1;
                }
                setPotential(0);
                much = getPotential();
              }
              display ("你练习了"+(YString)much+"次"+usewugong+"."+"你的"+usewugong+"有所增加.");
              much = much * (getLastForce()+ (getBeginForce()-20)*3);
          }
          else display ("你练习了"+(YString)much+"次"+usewugong+"."+"你的"+usewugong+"有所增加.");
          YString usewugongExp = usewugong+ "_经验";
          long lianExp =  getAsLong(usewugongExp)+much*g_Settings->getsitLianUp();
          if (lianExp > ((lianlevel+1)*(lianlevel+1)*10)) //升级公式级别加1的平方*10
          {
            YString leixing = g_Wugong->wugong_leixing(usewugong);
            leixing = "基本" + leixing ;
            if ( getSkillLevel(leixing) < lianlevel+1 )
            {
              display("你的"+leixing+"还不是很扎实，所以"+usewugong+"没有办法升级。");
            }
            else
            {
              playerlevelup(usewugong);
              set (usewugongExp,0);
            }
          }
          else
          {
            set (usewugongExp , lianExp );//getAsLong("练功成长")) ;
          }
          setBody(qixue);
          setEnergy(jingli);
        }
        else display ("你没有使用特殊武功");
      }
      else display ("你的气血不足。");
    }
    else display ("你的精力不足。");
    return 1;
}
//lp-----------------------------------------
//年龄的增长
int YPlayer::ageup(void)
{
  setOnlineTime(0);//set ("在线时间",0);   //一天一年（时间）
  setLaseOnlineTime(0);//set ("上次在线时间", 0 );
  setActorAge (getActorAge()+1);
  playerhpchange();
  return 1;
}
//-----------------------------------------
//起绰号
int YPlayer::nick(YString sentence)
{
 //是否屏蔽掉javescorpt
  sentence = changeword (sentence);
  if (sentence.size() > 50)
  {
    display ("你的绰号长度太长了。");
    return 1;
  }
  YString color = sentence.getWord();
  if (color[0] == '$') color = color.erase(0,1);
  else
  {
    sentence = color ;
    color = g_Settings->getNickColor();//getAsString("绰号颜色"); //"red";
  }
  setNick("<font color="+color+">"+sentence+"</font>");
  display ("你把你的绰号起为<font color="+color+">"+sentence+"</font>"+"。");
  return 1;
}
//-----------------------------------------
//自己写描述
int YPlayer::describe(YString sentence)
{
 //是否屏蔽掉javescorpt
  sentence = changeword (sentence);
  if (sentence.size() > 50)
  {
    display ("你对自己的描述长度太长了。");
    return 1;
  }
  YString color = sentence.getWord();
  if (color[0] == '$') color = color.erase(0,1);
  else
  {
    sentence = color ;
    color = g_Settings->getDescribeColor();//getAsString("绰号颜色"); //"red";
  }
  setDescribe("<font color="+color+">"+sentence+"</font>");
  display ("你把你的绰号起为<font color="+color+">"+sentence+"</font>"+"。");
  return 1;
}
//-----------------------------------------
//设置级别
int YPlayer::uselevel(YString sentence)
{
   long melevel = getLevel();
   if (melevel < 50)         //查看是否是巫师
   {
     YString name = sentence.getWord();
     YPlayer* sb=g_PlayerManager->getPlayer(name);
     if (sb)                           //查找人物
     {
       if ( sb->getLevel() < melevel)         //查看级别权限
       {
         long level = sentence.toLong();
         if (melevel > level)                      //捡测设定等级
         {
           sb->setLevel(level);
           display ("你已经设定"+name+"的级别为"+sentence+"级。");
         }
         else display ("你设定的级别要低于自己的级别。");
       }
       else display ("你的只能设定比自己级别低的人。");
     }
     else display("没有这个玩家。");
   }
   else display ("你的级别不足以使用这个命令。");
   return 1;
}
//-----------------------------------------
//投票
int YPlayer::vote(YString sentence)
{
   YString type =  sentence.getWord();
   YString name =  sentence.getWord();
   if (type == "chblk") //关闭频道
   {
      YPlayer* sb=g_PlayerManager->getPlayer(name);
      if ( sb )
      {
         YString check = "玩家关闭频道列表";
         YString all = sb->getAsString (check);
         YString forwhat = "玩家关闭频道" ; //判断条件
         if ( sb-> getPlayCloseChat() == 1)
         {
            display (name+"的频道已经关闭了。");
            return 1;
         }
         if (findStringInStr (all,getActorName())) //有你的名字
         {
             display ("你已经投过票了。");
             return 1;
         }
         else all = getActorName()+" "+all;
         long howmuch = 0 ;
         long allplayer = 20;//g_SessionManager->getPlayerCount()*3/10 +1;
         YString tempstr = all ;
         while (tempstr.getWord() != "")
         {
           howmuch++;
         }
         g_NormalChat->talk(NULL,getActorName()+"<a style='color=#0000ff;text-decoration:underline;cursor:hand;' onclick='actor(\"vote chblk "+sb->getActorName()+"\")'>"+"投票关闭"+sb->getActorName()+"的频道</a></font>，还有"+(YString)(allplayer - howmuch)+"票。"
                            ,NULL,NULL,CHANNEL_MSG);
         if (howmuch >= allplayer) //||( howmuch > (g_SessionManager->getPlayerCount()*5/10)))   //判断关闭条件
         {
            sb -> setPlayCloseChat(1);
            sb -> display ("你的频道被关闭了。");
            sb -> set (check,"");
            g_NormalChat->talk(NULL,sb->getDisplayName()+"的频道被关闭。"
                            ,NULL,NULL,CHANNEL_MSG);
         }
         else sb->set (check , all);
      }
      else
      {
        display ("你所投票的玩家没有在线。");
      }
   }
   else if (type == "unchblk") //开启频道
   {
      YPlayer* sb=g_PlayerManager->getPlayer(name);
      if ( sb )
      {
         YString check = "玩家开启频道列表";
         YString all = sb->getAsString (check);
         YString forwhat = "玩家关闭频道" ; //判断条件
         if ( sb-> getPlayCloseChat() == 0)
         {
            display (name+"的频道已经开启了。");
            return 1;
         }
         if (findStringInStr (all , getActorName())) //有你的名字
         {
             display ("你已经投过票了。");
             return 1;
         }
         else all = getActorName()+" "+all;
         long howmuch = 0 ;
         long allplayer = 20;//g_SessionManager->getPlayerCount()*3/10 +1;
         YString tempstr = all ;
         while (tempstr.getWord() != "")
         {
           howmuch++;
         }
         g_NormalChat->talk(NULL,getActorName()+"<a style='color=#0000ff;text-decoration:underline;cursor:hand;' onclick='actor(\"vote unchblk "+sb->getActorName()+"\")'>"+"投票开启"+sb->getActorName()+"的频道</a></font>，还有"+(YString)(allplayer - howmuch)+"票。"
                            ,NULL,NULL,CHANNEL_MSG);
         if ( (howmuch >= allplayer))// ||( howmuch > (g_SessionManager->getPlayerCount()*5/10)))   //判断关闭条件
         {
            sb -> setPlayCloseChat(0);
            sb -> display ("你的频道被开启了。");
            sb -> set (check , "");
            g_NormalChat->talk(NULL,sb->getDisplayName()+"的频道被开启。"
                            ,NULL,NULL,CHANNEL_MSG);
         }
         else sb->set (check , all);
      }
      else
      {
        display ("你所投票的玩家没有在线。");
      }
   }
   else
   {
     display ("你要投票干什么？");
   }
   return 1;
}
//-----------------------------------------
//修改屏蔽javascorp
YString YPlayer::changeword(YString changeword)
{
  int jos ;
  jos=0;
  while( changeword.find ('<',jos)!=YString::npos )
  {

        jos=changeword.find ('<',jos)+1;  //查找位置变换
        changeword[jos-1]='&';            //替换
        changeword.insert(jos,"lt;");     //插入
  }
  return changeword;
}
//-----------------------------------------
//武功级别描述
YString YPlayer::jiebiemiaoshu(int level)
{
      YString jiebiemiaoshu ;
      if (level > 120 )  jiebiemiaoshu = g_Settings->getwugongDisplay35();//getAsString ("武功级别描述35");
      else if (level > 70 )  jiebiemiaoshu = g_Settings->getwugongDisplay34();//getAsString ("武功级别描述34");
      else if (level > 69 )  jiebiemiaoshu = g_Settings->getwugongDisplay33();//getAsString ("武功级别描述33");
      else if (level > 65 )  jiebiemiaoshu = g_Settings->getwugongDisplay32();//getAsString ("武功级别描述32");
      else if (level > 61 )  jiebiemiaoshu = g_Settings->getwugongDisplay31();//getAsString ("武功级别描述31");
      else if (level > 57 )  jiebiemiaoshu = g_Settings->getwugongDisplay30();//getAsString ("武功级别描述30");
      else if (level > 54 )  jiebiemiaoshu = g_Settings->getwugongDisplay29();//getAsString ("武功级别描述29");
      else if (level > 51 )  jiebiemiaoshu = g_Settings->getwugongDisplay28();//getAsString ("武功级别描述28");
      else if (level > 48 )  jiebiemiaoshu = g_Settings->getwugongDisplay27();//getAsString ("武功级别描述27");
      else if (level > 45 )  jiebiemiaoshu = g_Settings->getwugongDisplay26();//getAsString ("武功级别描述26");
      else if (level > 42 )  jiebiemiaoshu = g_Settings->getwugongDisplay25();//getAsString ("武功级别描述25");
      else if (level > 39 )  jiebiemiaoshu = g_Settings->getwugongDisplay24();//getAsString ("武功级别描述24");
      else if (level > 36 )  jiebiemiaoshu = g_Settings->getwugongDisplay23();//getAsString ("武功级别描述23");
      else if (level > 33 )  jiebiemiaoshu = g_Settings->getwugongDisplay22();//getAsString ("武功级别描述22");
      else if (level > 30 )  jiebiemiaoshu = g_Settings->getwugongDisplay21();//getAsString ("武功级别描述21");
      else if (level > 28 )  jiebiemiaoshu = g_Settings->getwugongDisplay20();//getAsString ("武功级别描述20");
      else if (level > 26 )  jiebiemiaoshu = g_Settings->getwugongDisplay19();//getAsString ("武功级别描述19");
      else if (level > 24 )  jiebiemiaoshu = g_Settings->getwugongDisplay18();//getAsString ("武功级别描述18");
      else if (level > 22 )  jiebiemiaoshu = g_Settings->getwugongDisplay17();//getAsString ("武功级别描述17");
      else if (level > 20 )  jiebiemiaoshu = g_Settings->getwugongDisplay16();//getAsString ("武功级别描述16");
      else if (level > 18 )  jiebiemiaoshu = g_Settings->getwugongDisplay15();//getAsString ("武功级别描述15");
      else if (level > 16 )  jiebiemiaoshu = g_Settings->getwugongDisplay14();//getAsString ("武功级别描述14");
      else if (level > 14 )  jiebiemiaoshu = g_Settings->getwugongDisplay13();//getAsString ("武功级别描述13");
      else if (level > 12 )  jiebiemiaoshu = g_Settings->getwugongDisplay12();//getAsString ("武功级别描述12");
      else if (level > 10 )  jiebiemiaoshu = g_Settings->getwugongDisplay11();//getAsString ("武功级别描述11");
      else if (level > 9 )  jiebiemiaoshu = g_Settings->getwugongDisplay10();//getAsString ("武功级别描述10");
      else if (level > 8 )  jiebiemiaoshu = g_Settings->getwugongDisplay9();//getAsString ("武功级别描述9");
      else if (level > 7 )  jiebiemiaoshu = g_Settings->getwugongDisplay8();//getAsString ("武功级别描述8");
      else if (level > 6 )  jiebiemiaoshu = g_Settings->getwugongDisplay7();//getAsString ("武功级别描述7");
      else if (level > 5 )  jiebiemiaoshu = g_Settings->getwugongDisplay6();//getAsString ("武功级别描述6");
      else if (level > 4 )  jiebiemiaoshu = g_Settings->getwugongDisplay5();//getAsString ("武功级别描述5");
      else if (level > 3 )  jiebiemiaoshu = g_Settings->getwugongDisplay4();//getAsString ("武功级别描述4");
      else if (level > 2 )  jiebiemiaoshu = g_Settings->getwugongDisplay3();//getAsString ("武功级别描述3");
      else if (level > 1 )  jiebiemiaoshu = g_Settings->getwugongDisplay2();//getAsString ("武功级别描述2");
      else if (level > 0 )  jiebiemiaoshu = g_Settings->getwugongDisplay1();//getAsString ("武功级别描述1");
      else jiebiemiaoshu = g_Settings->getwugongDisplay0();//getAsString ("武功级别描述0");
      return jiebiemiaoshu;
}
//-----------------------------------------
//查看是否相同
int YPlayer::repeat(YString type,YString word)
{
  long flag = 0;
  if ((getAsString(type).find(word , 0) != YString::npos)
      && word.find(getAsString(type) , 0) != YString::npos )//相同时重复不同时把&&换||就可以。
  {
    display ("请不要重复发言.");
    flag = 1;
  }
  else set (type ,word);
  return flag;
}
int YPlayer::wizcompare(YActor* other)
{
      if (other->getLevel()> getLevel())
      {
       display ("你不能对比你级别高的人物使用该命令。");
       return 1;
      }
      return 0;
}
//-----------------------------------------
//查看是否相同
int YPlayer::worklevelup(YString type,long level) //level是一个予设的参数
{
     //判断是否已经超出最大值
     long alllevel = g_Settings->getAsLong("劳动技能");
     long usealllevel = getAsLong("劳动技能");
     if (usealllevel >= alllevel)
     {
        //无返回显示
        //display ("你的技能总数已经达到最大值。");
        return 1;
     }
     YString  typeexp = type + "_经验";
     long howexp = getAsLong(typeexp);
     long worklevel = getAsLong (type);
     if (  howexp < worklevel )
     {            
       //不能升级
       return 1;
     }
     long randsize = rand() % 101;
     if ( randsize > worklevel )
     {
       //劳动技能升级
       display ("你的"+type+"升级了！！");
       set (type, worklevel +1 );
       set ("劳动技能总数",usealllevel+1);
     }
     //升级没有成功
     set ( typeexp , 0 ); //经验清0
     return 1;
}
//-----------------------------------------
//清除任务的属性
int YPlayer::delQuest(void)
{
   YString allquest = getQuestList();//getAsString("任务列表");
   YString givename = "";
   YString tempStr = "";
   while ((givename = allquest.getWord()) != "")
   {
     tempStr="_任务类型" ;
     tempStr = givename + tempStr;
     set (tempStr,"");
     tempStr="_任务描述" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务目标" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务目标类型" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务物品" ;
     tempStr = givename + tempStr;
     set (tempStr,"");
     tempStr="_连续次数" ;
     tempStr = givename + tempStr;
     set (tempStr,0);
     tempStr="_任务号" ;
     tempStr = givename + tempStr;
     set (tempStr,0) ;
     tempStr="_任务时间" ;
     tempStr = givename + tempStr;
     set (tempStr,0);
   }
   setCityKill(0);//set ("屠城数",0 );
   setGiveThing(0);//set ("送东西数",0);
   return 1;
}

//-----------------------------------------
//清除任务的属性
int YPlayer::cdelQuest(YString command)
{
   YString cmd=command;
   YString allquest = getQuestList();//getAsString("任务列表");
   YString givename = "";
   YString tempStr = "";
   while ((givename = allquest.getWord()) != "")
   {
   if (cmd != givename){
     tempStr="_任务类型" ;
     tempStr = givename + tempStr;
     set (tempStr,"");
     tempStr="_任务描述" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务目标" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务目标类型" ;
     tempStr = givename + tempStr;
     set (tempStr,"") ;
     tempStr="_任务物品" ;
     tempStr = givename + tempStr;
     set (tempStr,"");
     tempStr="_连续次数" ;
     tempStr = givename + tempStr;
     set (tempStr,0);
     tempStr="_任务号" ;
     tempStr = givename + tempStr;
     set (tempStr,0) ;
     tempStr="_任务时间" ;
     tempStr = givename + tempStr;
     set (tempStr,0);
     }
   }
   setCityKill(0);//set ("屠城数",0 );
//   setGiveThing(0);//set ("送东西数",0);
   return 1;
}



//-----------------------------------------
//申请任务
int YPlayer::quest(void)
{
  YAbstractRoom* objRoom=getRoom();
  if(!objRoom) return 1;
  YString NPCList=objRoom->enumChildren("","","YNPC");
  YString theNPC;
  YAbstractActor* objNPC;
  for(;(theNPC=NPCList.getWord())!="";){
     objNPC=objRoom->findChildActor(theNPC);
     if(!objNPC) continue;
     if(objNPC->getAsLong("是否发任务")!=1) continue;
     else {
        objNPC->executeCommandAsTarget(this,"quest");
        return 1;
     }
  }
  YString questList=getQuestList();//getAsString("任务列表");
  if(questList==""){
     display("你目前没有任务!");
     return 1;
  }
  YString hisName;
  int flag=0;
  for(;(hisName=questList.getWord())!="";){
     long questTimes=getAsLong(hisName+"_连续次数");
     if(questTimes>0) display(hisName+"给你的任务你已经完成"+(YString)questTimes+"个了。");
     YString questDescribe=getAsString(hisName+"_任务描述");
     if(questDescribe!="") display(hisName+"给你的任务是:"+questDescribe);
     YString questType=getAsString(hisName+"_任务类型");
     if(questType!="") flag=1;
     if((questType=="送")||(questType=="找送")||(questType=="屠城")){
       if(getAsLong(hisName+"_任务超时")==1){
         display("你已经超过了"+hisName+"要求的时间。");
       }
       else{
         long time=getAsLong(hisName+"_任务时间");
         long minute=(time/1000)/60;
         long second=(time/1000)-minute*60;
         YString chineseMinute=LongToChinese(minute);
         YString chineseSecond=LongToChinese(second);
         display("你还有"+chineseMinute+"分"+chineseSecond+"秒的时间。");
       }
     }
  }
  if(flag==0){ //所有的任务类型都为空
     display("你目前没有任务!");
  }
  return 1;
}

//-----------------------------------------
//放弃任务
int YPlayer::giveup(void)
{
  YAbstractRoom* objRoom=getRoom();
  if(!objRoom) return 1;
  YString NPCList=objRoom->enumChildren("","","YNPC");
  YString theNPC;
  YAbstractActor* objNPC;
  for(;(theNPC=NPCList.getWord())!="";){
     objNPC=objRoom->findChildActor(theNPC);
     if(!objNPC) continue;
     if(objNPC->getAsLong("是否发任务")!=1) continue;
     else {
        objNPC->executeCommandAsTarget(this,"giveup");
        return 1;
     }
  }
  display("你要向谁放弃任务?");
  return 1;
}
//------------------------------------------
//完成任务后的奖励
int YPlayer::getReward(YString bossName)
{
  YQuest *objQuest;
  YAbstractThing* objMoney;
  long numCash;
  objQuest=(YQuest*)g_Quest->findChild(bossName,"YQuest");
  if(!objQuest) return 0; //0表示奖励失败
  display("<font color=7CCD7C>恭喜你完成了一个任务!</font>");
  long questTimes=getAsLong(bossName+"_连续次数");
  set(bossName+"_连续次数",questTimes+1);
  long questNumber=getAsLong(bossName+"_任务号");
  long rewardExp=objQuest->questRewardExp(questNumber,questTimes);//奖励经验
  long rewardPotential=objQuest->questRewardPotential(questNumber,questTimes);//奖励潜能
  long rewardMoney=objQuest->questRewardMoney(questNumber,questTimes);//奖励钱
  display("你被奖励了"+LongToChinese(rewardExp)+"点经验。");
  display("你被奖励了"+LongToChinese(rewardPotential)+"点潜能。");
  setExperience(getExperience()+rewardExp);
  setPotential(getPotential()+rewardPotential);
  YString appraiseName=getAsString(bossName+"_评价名");
  if(appraiseName!=""){
    long rewardAppraise=objQuest->questRewardAppraise(questNumber,questTimes);//奖励评价
    display("你被奖励了"+LongToChinese(rewardAppraise)+"点"+appraiseName+"。");
    if(appraiseName == "门派评价") setPartyValue(getPartyValue()+rewardAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
    else if(appraiseName == "朝廷声望") setCourtValue(getCourtValue()+rewardAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
    else if(appraiseName == "江湖声望") setSocietyValue(getSocietyValue()+rewardAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
  }

  numCash=0;
  objMoney=findChildThing("金子");
  if(objMoney){
     numCash+=(objMoney->getCount())*10000;
  }
  objMoney=findChildThing("银子");
  if(objMoney){
     numCash+=(objMoney->getCount())*100;
  }
  objMoney=findChildThing("铜板");
  if(objMoney){
     numCash+=objMoney->getCount();
  }
  numCash+=rewardMoney;
  long goldnum,silvernum,coinnum,goldnum1,silvernum1,coinnum1;//多少金，多少银，多少铜板
  string priceString;
  goldnum=numCash/10000; //剩余金
  silvernum=(numCash-goldnum*10000)/100; //剩余银
  coinnum=numCash%100; //剩余铜板
  goldnum1=rewardMoney/10000; //剩余金
  silvernum1=(rewardMoney-goldnum1*10000)/100; //剩余银
  coinnum1=rewardMoney%100; //剩余铜板
  
  if (goldnum1!=0) priceString=LongToChinese(goldnum1)+"两黄金";
  if (silvernum1!=0) priceString=priceString+LongToChinese(silvernum1)+"两白银";
  if (coinnum1!=0) priceString=priceString+LongToChinese(coinnum1)+"文铜板";
  
  display("你被奖励了"+priceString+"。");
  if(goldnum!=0){
    objMoney=findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/金子 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(goldnum);
  }
  else if(goldnum==0){
    objMoney=findChildThing("金子");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(silvernum!=0){
    objMoney=findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/银子 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(silvernum);
  }
  else if(silvernum==0){
    objMoney=findChildThing("银子");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(coinnum!=0){
    objMoney=findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/铜板 is NULL");
        return 1;
      }
      addChild(objMoney);
    }
    objMoney->setCount(coinnum);
  }
  else if(coinnum==0){
    objMoney=findChildThing("铜板");
    if(objMoney){
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }

  if(getAsString(bossName+"_任务类型")!="屠城"){
    set(bossName+"_任务号",0);
    set(bossName+"_任务类型","");
    set(bossName+"_任务目标","");
    set(bossName+"_任务描述","");
  }
  set("信息屏蔽",0); //打开屏蔽
  return 1;
}

//-----------------------------------------
//割首级
int YPlayer::ge(YString command)
{
  YString cmd=command;
  YString commandTarget=cmd.getWord(); //要割的对象
  YString msg;
  YString MyName=getActorName();
  if(commandTarget==""){
    display("你要割谁的首级?");
    return 1;
  }
  YString weapon=getWeaponName();//getAsString("武器");
  YString weaponType=getWeaponType();//getAsString("武器类型");
  if((weaponType!="剑")&&(weaponType!="刀")){
      if (findChildThing("屠刀"))
      {
         weapon = "屠刀" ;
      }
      else
      {
        display("你手里没有刀剑之类的东西怎么割?");
        return 1;
      }
  }
  YAbstractActor *objActor=getRoom()->findChildActor(commandTarget);
  YAbstractThing *objBones;
  if(!objActor){
    objBones=getRoom()->findChildThing(commandTarget);
  }
  if((!objActor)&&(!objBones)){
    display("你要割谁的首级?");
    return 1;
  }
  if(objActor){
    YString status=((YActor*)objActor)->getStatus();//getAsString("状态");
    if(status!="晕倒中"){
      display("你偷偷地靠近"+commandTarget+",死死盯着"+commandTarget+"的脖子,一只手神经质地颤动着。");
      msg=MyName+"偷偷地靠近"+commandTarget+",死死盯着"+commandTarget+"的脖子,一只手神经质地颤动着。";
      getRoom()->getRoomChat()->talk(NULL,msg,this,objActor);
      msg=MyName+"偷偷地靠近你,死死盯着你的脖子,一只手神经质地颤动着。";
      objActor->display(msg);
      return 1;
    }
    YString targetType; //目标是player还是npc(目标类型)
    if(objActor->isTypeOf("YNPC")) targetType="NPC";
    else if(objActor->isTypeOf("YPlayer")) targetType="Player";
    else{
      display("你要割谁的首级?");
      return 1;
    }
    //添加死亡
    //新手保护
    if (objActor->isTypeOf("YPlayer")){
    if (((YActor*)objActor)->isnewbie())
    {
      display ("你不会残忍连孩子也杀把！！！");
      return 1;
    }
    else if (this->isnewbie() )
    {
      display ("你年纪这么小就学的心狠手辣！！！");
      return 1;
    }
    setZdpk(1); //设置主动pk     
    }
    ((YActor*)objActor) -> setDeathMode("割死");
    ((YActor*)objActor) -> setKillerName(getActorName());//set("杀死自己",getAsString("名字"));//设置杀死自己
    ((YActor*)objActor) -> dead();
    ((YActor*)objActor)-> setDeathMode("");//set("死亡方式","");
    //添加结束
    YAbstractThing *objPate,*objBody; //首级的指针
    objPate=(YAbstractThing*)loadObject("thing/首级");
    if(!objPate){
      g_err.show("[YPlayer::ge]loadObject首级 is NULL");
      return 1;
    }
    this->addChild(objPate);
    objPate->setCount(1);
    YString newName=commandTarget+"的首级";
    ((YThing*)objPate)->setThingName(newName);//set("名字",newName);
    ((YThing*)objPate)->setDescribe("这是"+commandTarget+"的首级");//set("描述","这是"+commandTarget+"的首级");
    objPate->set("杀人者",MyName);
    objPate->set("割首级者",MyName);
    objPate->set("拥有者类型",targetType);
    objBody=(YAbstractThing*)loadObject("thing/尸体");
    if(!objBody){
      g_err.show("[YPlayer::ge]loadObject尸体 is NULL");
      return 1;
    }
    getRoom()->addChild(objBody);
    objBody->setCount(1);
    YString targetSex=((YActor*)objActor)->getSexString();
    ((YThing*)objBody)->setThingName("无头"+targetSex+"尸");//set("名字","无头"+targetSex+"尸");
    objBody->set("性别",targetSex);
    objBody->set("尸体",2); //无头尸体的标志
    ((YThing*)objBody)->setDescribe("这是一具无头的"+targetSex+"尸。");//set("描述","这是一具无头的"+targetSex+"尸。");
    YString thingList=objActor->enumChildrenThing(); //对方身上的所有物品
    YString tempThing; //临时物品
    YAbstractThing *objThing;
    while((tempThing=thingList.getWord())!=""){
      objThing=objActor->findChildThing(tempThing);
      if(!objThing) continue;
      objActor->giveChildTo(objThing,objBody,objThing->getCount());
    }
    if(targetType=="NPC"){
      ((YActor*)objActor)->gotoRoom(g_Settings->getNPCDeadRoom());
    }
    else if(targetType=="Player"){
      ((YActor*)objActor)->gotoRoom(g_Settings->getDeadRoom());
    }
    msg="&s挥动"+weapon+",将"+commandTarget+"的首级割了下来。";
    OutputMsg(this,msg);
  }
  else if(objBones){
     if((objBones->getAsLong("尸体"))==0){
       display("你要割谁的首级?");
       return 1;
     }
     if((objBones->getAsLong("尸体"))==2){
       display("看清楚,还有头吗?");
       return 1;
     }
     if((objBones->getAsLong("尸体"))==1){
       YAbstractThing *objPate; //首级的指针
       objPate=(YAbstractThing*)loadObject("thing/首级");
       if(!objPate){
         g_err.show("[YPlayer::ge]loadObject首级 is NULL");
         return 1;
       }
       this->addChild(objPate);
       objPate->setCount(1);
       YString targetName=commandTarget;
       targetName.removeAnyWord("的尸体");
       objPate->setObjectName(targetName+"的首级");//set("名字",targetName+"的首级");
       ((YThing*)objPate)->setDescribe("这是"+targetName+"的首级");//set("描述","这是"+targetName+"的首级");
       objPate->set("杀人者",objBones->getAsString("杀人者"));
       objPate->set("割首级者",MyName);
       objPate->set("拥有者类型",objBones->getAsString("拥有者类型"));
       setGoodnessCount(getGoodnessCount()-objBones->getAsLong("正气值")/20);
       YString targetSex=objBones->getAsString("性别");
       objBones->setObjectName("无头"+targetSex+"尸");//set("名字","无头"+targetSex+"尸");
       objBones->set("尸体",2); //无头尸体的标志
       ((YThing*)objBones)->setDescribe("这是一具无头的"+targetSex+"尸。");//set("描述","这是一具无头的"+targetSex+"尸。");
       msg="&s挥动"+weapon+",将"+targetName+"的首级割了下来。";
       OutputMsg(this,msg);
     }
  }
  return 1;
}
//---------------------------------------
//劳动(钓鱼,酿蜜...)
int YPlayer::letsWork(void)
{
  long workTime=getAsLong("劳动计时");
  if(workTime>0){
    workTime-=getSmallTime();
    set("劳动计时",workTime);
  }
  else{
    set("劳动计时",0);
    setNowWork(0);//set("正在劳动",0);
    YAbstractRoom *objRoom=getRoom();
    if(!objRoom){
      return 1;
    }
    else{
      YString msg=objRoom->getAsString("劳动结束");
      OutputMsg(this,msg);
      long fruitAmount=objRoom->getAsLong("劳动结果个数");
      long randomFruit; //随机的劳动结果
      randomFruit=rand()%(fruitAmount*2)+1;
      if(randomFruit>fruitAmount) randomFruit=1;
      msg=objRoom->getAsString("劳动结果"+(YString)randomFruit);
      OutputMsg(this,msg);
      long minEx=objRoom->getAsLong("增加经验下限");
      long maxEx=objRoom->getAsLong("增加经验上限");
      long minPt=objRoom->getAsLong("增加潜能下限");
      long maxPt=objRoom->getAsLong("增加潜能上限");
      long ex=maxEx-minEx;
      if(ex<=0) ex=1;
      long pt=maxPt-minPt;
      if(pt<=0) pt=1;
      long randEx=rand()%ex+minEx;
      long randPt=rand()%pt+minPt;
      if(randomFruit==1){
        setExperience(getExperience()+randEx);
        setPotential(getPotential()+randPt);
        display("你的经验和潜能增加了！");
      }
    }
  }
  return 1;
}
//---------------------------------------
//采矿
int YPlayer::letsCaikuang(void)
{
  long workTime=getAsLong("劳动计时");
  if(workTime>0){
    workTime-=getSmallTime();
    set("劳动计时",workTime);
  }
  else{
    set("劳动计时",0);
    setNowWork(0);//set("正在劳动",0);
    set("劳动","");
    YRoom *objRoom=getRoom();
    if(objRoom->isTypeOf("YCollectRoom")){
      ((YCollectRoom*)objRoom)->caikuangEnd(this);
    }
    else{
      display("你离开了矿区。");
    }
  }
  return 1;
}
//---------------------------------------
//打铁
int YPlayer::letsDazao(void)
{
  long workTime=getAsLong("劳动计时");
  if(workTime>0){
    workTime-=getSmallTime();
    set("劳动计时",workTime);
  }
  else{
    setNowWork(0);//set("劳动计时",0);
    set("正在劳动",0);
    set("劳动","");
    YString sThing=getAsString("劳动制作");
    set("劳动制作","");
    if(sThing==""){
      display("你要打造的物品丢失了。");
    }
    YRoom *objRoom=getRoom();
    if(objRoom->isTypeOf("YYelianRoom")){
      ((YYelianRoom*)objRoom)->dazaoEnd(this,sThing);
    }
    else{
      display("你离开了打铁铺。");
    }
  }
  return 1;
}
//---------------------------------------
//计算送东西所剩的时间
int YPlayer::letsSendThing(void)
{
  YString questList=getQuestList();//getAsString("任务列表");
  YString hisName; //发任务人的名字
  while((hisName=questList.getWord())!=""){
    if(((getAsString(hisName+"_任务类型")!="送")&&
        (getAsString(hisName+"_任务类型")!="找送"))||
       (getAsLong(hisName+"_任务超时")==1))
      continue;
    long questTime=getAsLong(hisName+"_任务时间");
    if(questTime<0){
      display("你已经超过"+hisName+"要求的时间了。");
      set(hisName+"_任务超时",1);
      return 1;
    }
    else{
      questTime-=getSmallTime();
      set(hisName+"_任务时间",questTime);
    }
  }
  return 1;
}
//---------------------------------------
//计算屠城所剩的时间
int YPlayer::letsKillAll(void)
{
  YString questList= getQuestList();//getAsString("任务列表");
  YString hisName; //发任务人的名字
  while((hisName=questList.getWord())!=""){
    if((getAsString(hisName+"_任务类型")!="屠城")||
       (getAsLong(hisName+"_任务超时")==1))
      continue;
    long questTime=getAsLong(hisName+"_任务时间");
    if(questTime<0){
      display("你已经超过"+hisName+"要求的时间了。");
      long useTimes=getCityKill(); //使用次数
      useTimes-=1;  //使用次数减一
      if(useTimes<=0) useTimes=0;
      setCityKill(useTimes);
      set(hisName+"_任务超时",1);
      if(getAsLong(hisName+"_屠城完成")==1){
        getReward(hisName);
        display("这次任务完成的很好,你可以回去了。");
      }
      else{
        display("很遗憾,你没能完成任务。");
      }
      set(hisName+"_任务号",0);
      set(hisName+"_任务类型","");
      set(hisName+"_任务目标","");
      set(hisName+"_任务描述","");
    }
    else{
      questTime-=getSmallTime();
      set(hisName+"_任务时间",questTime);
    }
  }
  return 1;
}
//---------------------------------------------------------------------------
void YPlayer::setSex(YString sex)
{
  YXiluUser::setSex(sex);
  if (getSexString()!= "" ) return;
  switch(YXiluUser::getSex()) {
    case MALE:
      setSexString("男");
      break;
    case FEMALE:
      setSexString("女");
      break;
    default:   //不允许中性所以默认定义为男
      setSexString("男");
  }
}
//---------------------------------------------------------------------------
//保存玩家数据
int YPlayer::cmd_save(void)
{
  if(YMUDObject::save()==1) display("您的数据已成功保存。");
  else display("数据无法保存，请与在线巫师联系。");
  return 1;
}
//---------------------------------------------------------------------------
int YPlayer::shutdown(YString cmd)
{
  YString canshu = cmd.getWord();
  YString allname =  g_PlayerManager->enumPlayer();
  YString tempname = "";
  YPlayer* sb=NULL; //人物的指针
  while ((tempname = allname.getWord()) != "")
  {
    sb=g_PlayerManager->getPlayer(tempname);
    if (sb)
    {
      if((sb->YMUDObject::save())==1)
      display (sb->getActorName()+"保存。");
      else display(tempname+"数据无法保存");
    }
    else display (tempname+"没找到指针。");
  }
  display ("存储完毕。");
  return 1;
}
//---------------------------------------------------------------------------
int YPlayer::who(YString cmd)
{
  YString canshu = cmd.getWord();
  YString allname =  g_PlayerManager->enumPlayer();
  if (canshu == "")
  {
    display((YString)"目前在线<font color=red>"+(YString)g_SessionManager->getPlayerCount()+"</font>人");
    display( g_PlayerManager->enumPlayerForDisplay()) ;
  }
  else if (canshu == "-w")
  {
    YString wizname = "";
    YString allwizname = "";
    YActor* sb=NULL; //巫师的指针
    while ((wizname = allname.getWord()) != "")
    {
        sb=g_PlayerManager->getPlayer(wizname);
        if (sb && sb->isTypeOf("YWizard"))    // 是否是巫师
        {
           allwizname = sb->getDisplayName()+" "+allwizname;
        }
    }
    if (allwizname != "")display (allwizname);
    else display ("没有巫师在线.");
  }
  else if (canshu == "-p")
  {
    YString menpai = getSchool();//getAsString ("门派");
    YString playername = "";
    YString allplayername = "";
    YActor* sb=NULL;
    while ((playername = allname.getWord()) !="")
    {
        sb=g_PlayerManager->getPlayer(playername);
        if (sb && (sb->getAsString("门派") == menpai))    // 是否是本门
        {
           allplayername = sb->getDisplayName()+" "+allplayername;
        }
    }
    display (allplayername);
  }
  else if (canshu == "-l")
  {
    YString playername = "";
    YActor* sb=NULL;
    while ((playername = allname.getWord()) !="")
    {
        sb=g_PlayerManager->getPlayer(playername);
        if (sb)    //是否有人物
        {
           YString menpai = sb->getSchool();//getAsString("门派") ;
           YString nick = sb ->getNick();//getAsString("绰号") ;
           if ( menpai != "" ) menpai = "["+menpai+"]";
           playername =menpai+ nick +sb->getDisplayName();
           display (playername);
        }
    }
  }
  else
  {
    YString menpai = canshu.getWord();
    YString playername = "";
    YString allplayername = "";
    YActor* sb=NULL;
    while ((playername = allname.getWord()) != "")
    {
        sb=g_PlayerManager->getPlayer(playername);
        if ( sb && (sb->getAsString("门派") == menpai))    // 是否是门派弟子
        {
           //YString testmenpai= sb->getSchool() ;//
           allplayername = sb->getDisplayName()+" "+allplayername;
        }
    }
    if (allplayername != "") display (allplayername);
    else if (menpai != "" ) display ("没有这个门派，或还没有玩家拜这个门派.");
    else display ("没有这个命令参数.");
  }
  return 1;
}
//--------------------------------------------------------------------------
//读书
int YPlayer::readBook(YString command)
{
  YString cmd=command;
  YString commandBook=cmd.getWord(); //书的名字
  YString commandCount=cmd.getWord(); //读书的次数
  long count=commandCount.toLong();
  if(count<1) count=1; //最少一次
  if(count>1000) count=1000; //最大一千
  YString msg;
  if(commandBook==""){
    display("你要读什么书?");
    return 1;
  }
  YThing *objThing=(YThing*)findChildThing(commandBook);
  if(!objThing){
    display("你没有这本书。");
    return 1;
  }
  if(objThing->getAsLong("书籍")!=1){
    msg="&s拿了一"+objThing->getQuantifier()+commandBook+",左看右看,上看下看,想把它当作一本书来读。";
    OutputMsg(this,msg);
    return 1;
  }
  if(getLearn()==0){
    msg="&s拿起了一"+objThing->getQuantifier()+"《"+commandBook+"》,装模作样地读了起来,其实一个字都不认识。";
    OutputMsg(this,msg);
    return 1;
  }
  long MySavvy=getLastLearn();
  if(MySavvy<20) MySavvy=20; //后天悟性最小是20
  long bookNeedSavvy=objThing->getAsLong("书籍_需要悟性");
  if(bookNeedSavvy<20) bookNeedSavvy=20; //读书需要得悟性默认为20
  if(MySavvy<bookNeedSavvy){ //自己的悟性小于读懂这本书需要的悟性
    msg="&s拿起了一"+objThing->getQuantifier()+"《"+commandBook+"》仔细阅读,可惜悟性太差,实在读不懂。";
    OutputMsg(this,msg);
    return 1;
  }
  YString bookAddSkill=objThing->getAsString("书籍_增加技能");
  long lowerLimit=objThing->getAsLong("书籍_下限");
  long upperLimit=objThing->getAsLong("书籍_上限");
  long MySkillLevel=getSkillLevel(bookAddSkill);//getAsLong(bookAddSkill); //自己的武功等级
  if(MySkillLevel<lowerLimit){
    display("这本书对你来说太深奥了,还是先打好基础吧。");
    return 1;
  }
  if(MySkillLevel>=upperLimit){
    display("这本书对你来说太简单了,你学不到任何东西。");
    return 1;
  }
  long MyPotential=getPotential(); //player自己的潜能
  long MyEnergy=getEnergy(); //player自己的精力
  long PotentialUsed=objThing->getAsLong("书籍_消耗潜能"); //读这本书每次消耗的潜能
  if(PotentialUsed<0) PotentialUsed=0; //默认值为0
  long EnergyUsed=objThing->getAsLong("书籍_消耗精力"); //读这本书每次消耗的精力
  if(EnergyUsed<=0) EnergyUsed=1; //默认值为1
  if(MyPotential<PotentialUsed){
     display("你的潜能已经到了极限了.");
     return 1;
  }
  if(MyEnergy<EnergyUsed){
     display("你现在精力不足!");
     return 1;
  }
  if(PotentialUsed>0){
    long poCount=MyPotential/PotentialUsed; //潜能支持的最大次数
    if(count>poCount) count=poCount;
  }
  long enCount=MyEnergy/EnergyUsed; //精力支持的最大次数
  if(count>enCount) count=enCount;
  MyPotential-=count*PotentialUsed;
  MyEnergy-=count*EnergyUsed;
  if(MyPotential<0) MyPotential=0;
  if(MyEnergy<0) MyEnergy=0;
  //
  setPotential(MyPotential); //消耗潜能
  setEnergy(MyEnergy); //消耗精力
  YString playerAllSkills=getAllSkillsList();//getAsString("所会技能"); //管理技能列表
  if(playerAllSkills.find(bookAddSkill,0)==YString::npos){
    if(playerAllSkills=="")
      playerAllSkills=bookAddSkill;
    else
      playerAllSkills+=" "+bookAddSkill;
    setAllSkillsList(playerAllSkills);
    //set("所会技能",playerAllSkills);
  }
  msg="你拿起一"+objThing->getAsString("量词")+"《"+commandBook+"》,仔细地读了一会。";
  display (msg);
  display("你好像有了一些心得。");
  display("你学习了"+(YString)count+"次....");
  long MyGradeExp=getAsLong(bookAddSkill+"_经验"); //player自己的武功经验
  long step=(MySavvy-20)+objThing->getAsLong("书籍_每次增长"); //每次增长多少武功经验
  MyGradeExp+=step*count;
  if(MyGradeExp>=(MySkillLevel+1)*(MySkillLevel+1)*10){
    MyGradeExp=0; //武功经验清0
    playerlevelup(bookAddSkill); //武功等级提升
  }
  set(bookAddSkill+"_经验",MyGradeExp);
  return 1;
}
//--------------------------------------------------------------------------
//重新装载object的属性
int YPlayer::cmd_reload(YString command)
{
  YString type=command.getWord();
  if(type=="room") {
    if(getRoom()->reload()==1) display("room 已经刷新。");
    else display("room 刷新时出错。");
  }
  else if(type=="NPC") {
    YString npcname=command.getWord();
    YNPC* npc=g_PlayerManager->getNPC(npcname);
    if(!npc) {
      display("没有这个NPC。");
      return 1;
    }
    if(npc->reload()==1) display("NPC已经刷新。");
    else display("NPC刷新时出错。");
  }
  else if(type=="quest") {
    g_Quest->reload();
    display("任务已经刷新。");
  }
  else if(type=="wugong") {
    g_Wugong->reload();
    display("武功已经刷新。");
  }
  else if(type=="emote") {
    g_Emote->reload();
    display("表情已经刷新。");
  }
  else if(type=="conf") {
    g_Settings->load(0,NULL,"webmud.conf");
    display("系统设置已经刷新。");
  }
  else {
    display("目前只支持quest、wugong、emote、room、conf和NPC。");
  }
  return 1;
}
//--------------------------------------------------------------------------
//重新装载object的属性
int YPlayer::wizcreate(YString command)
{
  if(m_PlayerLevel<90) {
    display("级别不够。");
    return 1;
  }
  if(command=="") {
    display("你要制造什么东西？");
    return 1;
  }
  YString thingname = command.getWord();
  YMUDObject* obj=loadObject(thingname);
  if(!obj) {
    display("无法装载此物品。");
    return 1;
  }
  getRoom()->addChild(obj);
  if (obj->isTypeOf("YThing"))
  {
    long thingcount = command.toLong();
    if  (thingcount <= 0 ) thingcount = 1;
    ((YThing*)obj)->setCount(thingcount);
  }
  display("创造成功。");
  return 1;
}
//--------------------------------------------------------------------------
//察看耗时情况
int YPlayer::timeuse(void)
{
  if(m_PlayerLevel<90) {
    display("级别不够。");
    return 1;
  }
  g_Stopwatch->stop(0);
  display(g_Stopwatch->overview(true));
  g_Stopwatch->resetAll();
  g_Stopwatch->start(0);
  display(g_Counter->overview(true));
  return 1;
}
//----------------------------------------------------------------
//得到某种武功的等级(Player专用)
long YPlayer::getSkillLevel(YString skill)
{
  if(skill=="基本拳法") return getBaseHand();
  else if(skill=="读书写字") return getLearn();
  else if(skill=="基本内功") return getBaseForce();
  else if(skill=="基本轻功") return getBaseDodge();
  else if(skill=="基本招架") return getBaseParry();
  else if(skill=="基本掌法") return getbaseSole();
  else if(skill=="基本指法") return getBaseFinger();
  else if(skill=="基本手法") return getBasePub();
  else if(skill=="基本爪法") return getBaseClow();
  else if(skill=="基本腿法") return getBaseLeg();
  else return getAsLong(skill); //否则调用getAsLong
}
//----------------------------------------------------------------
//设置某种武功的等级(Player专用)
int YPlayer::setSkillLevel(YString skill,long level)
{
  if(skill=="基本拳法")  setBaseHand(level);
  else if(skill=="读书写字")  setLearn(level);
  else if(skill=="基本内功")  setBaseForce(level);
  else if(skill=="基本轻功")  setBaseDodge(level);
  else if(skill=="基本招架")  setBaseParry(level);
  else if(skill=="基本掌法")  setbaseSole(level);
  else if(skill=="基本指法")  setBaseFinger(level);
  else if(skill=="基本手法")  setBasePub(level);
  else if(skill=="基本爪法")  setBaseClow(level);
  else if(skill=="基本腿法")  setBaseLeg(level);
  else  set(skill,level); //否则调用set
  return 1;
}
//----------------------------------------------------------------
//给东西要不要
int YPlayer::nogive(YString sentence)
{
  int how=sentence.toLong();
  if ( how > 0 )
  {
    setNoAccept(1);
    display("你不接受别人给你的东西！");
  }
  else
  {
    if (getNoAccept() == 1)
    {
      setNoAccept(0);
      display("你可以接受别人给你的东西了.");
    }
    else
    {
      setNoAccept(1);
      display("你不接受别人给你的东西！");
    }
  }
  return 1;
}       
//----------------------------------------------------------------
//开关错误频道
int YPlayer::errorChat(YString sentence)
{
    YString about = sentence.getWord();
    if (about == "on！！")
    {
                g_ErrorChat->subscribe(this);
                display ("你开启了错误频道。");
    }
    else if (about == "off！！")
    {
                g_ErrorChat->unsubscribe(this);
                display ("你关闭了错误频道。");
    }
    else display ("啊？！");
    return 1;
}
//**********************************************************
//*****                                              *******
//*****                  玩家帮派系列                *******
//*****                                              *******
//**********************************************************
//----------------------------------------------------------
//创建玩家帮派
int YPlayer::fnCreateFaction(YString command)
{
  YString sFactionName=getFactionName();    //"加入帮派"
  if(sFactionName!=""){
    display("你已经加入了["+sFactionName+"]，不能再创建别的帮派。");
    return 1;
  }
  if(getExperience() < EXP){    //3M
    display("你的经验还不够。");
    return 1;
  }
  if(getDeposit() < MONEY){       //500金子
    display("你在钱庄的存款还不够。");
    return 1;
  }
  if(getInhereAttack() < ATTACK){    //1万
    display("你的武功还不够。");
    return 1;
  }
  if(getInhereDefense() < DEFENSE){   //1万
    display("你的武功还不够。");
    return 1;
  }
  if((getGoodnessCount() < GOODNESS) && (getGoodnessCount() > EVILNESS)){  //+-30万
    display("你的正气值还不够。");
    return 1;
  }
  if(getSocietyValue() < CREDIT){    //1万
    display("你在江湖中的声望尚浅，不能自立帮派。");
    return 1;
  }
  YAbstractThing *pObj=findChildThing("开业执照");
  if(!pObj){
    display("你创建帮派的条件已经满足，请向巫师申请执照。");
    return 1;
  }
  sFactionName=command.getWord(); //帮派名字
  //检查长度
  if(sFactionName.size() > 10){   //5 个字
    display("贵帮的名字太长了吧。");
    return 1;
  }
  YString sFactionBanner=command.getWord(); //本帮口号
  if(sFactionBanner.size() > 30){ //15 个字
    display("贵帮的口号太长了吧。");
    return 1;
  }
  //建立这个帮派
  int nError=g_Faction->fnAddFaction(sFactionName);
  if(nError == -1){                     //-1 表示名字已经有了
    display("这个名字已经有人用了。");
    return 1;
  }
  //显示公共信息
  display("恭喜！你成功创立了["+sFactionName+"]。");
  setIsFactionOwner(1);         //"是否帮主"
  setFactionName(sFactionName); //"加入帮派"
  setFactionTitle("帮主");      //"帮派头衔"
  if(sFactionBanner == "") sFactionBanner="欢迎加入";
  g_Faction->fnSetFacionBanner(sFactionName,sFactionBanner);  //设置这个帮派的口号
  YString sOwnerName=getActorName();   //玩家的名字
  g_Faction->fnSetFacionOwner(sFactionName,sOwnerName);       //设置这个帮派的帮主
  g_Faction->fnSetFacionColor(sFactionName,"60ABCD");         //设置默认的帮派颜色
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+sOwnerName+"创立了新帮派["+sFactionName+"]！他的口号是：["
          +sFactionBanner+"]</font>",NULL,NULL,CHANNEL_MSG);
  if(removeChild(pObj)) delete pObj;  //删除"开业执照"物品
  long deposit=getDeposit()-MONEY;
  if(deposit < 0) deposit=0;
  setDeposit(deposit);   //存款减去500金子
  g_Faction->fnSetPlayerAmount(sFactionName,1);   //设置这个帮派的玩家数量
  g_Faction->fnSetFactionPower(sFactionName,0,10);  //新建帮派赠送10点势力值
  g_Faction->fnSetFactionPower(sFactionName,0,1);   //由人数而增加的势力值
  g_Faction->set(sFactionName+"_成员列表",sOwnerName);
  long nOldPower,nNewPower;  //势力值
  nOldPower=0;
  nNewPower=fnReSumPower();   //玩家计算一下自己的势力值
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,nNewPower); //改变势力值
  setOldPower(nNewPower);  //保存这次计算出的势力值 "上次势力"
  g_Faction->fnSetFactionClose(sFactionName,10);   //新帮派的团结度初始为10
  g_Faction->fnSetFacionStatus(sFactionName,"新成立");  //设置帮派状态
  g_Faction->save();
  YChat* pMyFactionChat=g_ChatManager->getChat(sFactionName);
  if(!pMyFactionChat) return 1;
  pMyFactionChat->subscribe(this);    //订阅频道
  setFactionChat(pMyFactionChat);      //保存玩家频道的指针
  return 1;
}
//------------------------------------------------------------------------
//玩家计算一下自己的势力值
long YPlayer::fnReSumPower()
{
  long power=0;
  if(getIsFactionOwner() == 1){       //"是否帮主"
    power+=(getExperience()/1000000)*2; //帮主1M 等于2点势力值
  }
  else{
    power+=(getExperience()/1000000);   //普通人1M 等于1点势力值
  }
  long money=getDeposit()/10000000;     //1000金子 等于 1点
  if(money > 10) money=10;              //最多10点 
  power+=money;
  power+=getInhereAttack()/10000;
  power+=getInhereDefense()/10000;
  if((getGoodnessCount() >= GOODNESS) || (getGoodnessCount() <= EVILNESS)){
    power+=1;
  }
  if(getSocietyValue() >= CREDIT){
    power+=1;
  }
  if(power<0) power=0;
  return power;
}
//----------------------------------------------------------
//查询玩家帮派
int YPlayer::fnCmdFaction(YString command)
{
  YString sFactionName;
  YString sColor;
  YString sOwner;
  long nPower;
  if((command == "") || (command == " ")){
    long nCount=g_Faction->getFactionAmount();    //"帮派总数"
    if(nCount <=0){
      display("目前江湖中还没有任何玩家帮派！");
      return 1;
    }
    display("目前江湖中共有玩家帮派<font color=red>"+(YString)nCount+"</font>个。<br>分别是：");
    YString sFactionList=g_Faction->getFactionList();   //"帮派列表"
    for(int i=0;i<nCount;i++){
      sFactionName=sFactionList.getWord();          //帮派名
      sColor=g_Faction->fnGetFacionColor(sFactionName);   //帮派颜色
      sOwner=g_Faction->fnGetFacionOwner(sFactionName);   //帮主名字
      nPower=g_Faction->fnGetFactionPower(sFactionName);  //势力值
      display("[<font color="+sColor+">"+sFactionName+"</font>] 帮主：["+sOwner+"] 势力值：["
                +(YString)nPower+"]");
    }
  }
  else{
    sFactionName=command.getWord();
    if(g_Faction->isFacionExisting(sFactionName) == 0){
      display("江湖之中还没有这个玩家帮派。");
      return 1;
    }
    sColor=g_Faction->fnGetFacionColor(sFactionName);   //帮派颜色
    sOwner=g_Faction->fnGetFacionOwner(sFactionName);   //帮主名字
    nPower=g_Faction->fnGetFactionPower(sFactionName);    //势力值
    long nSolid=g_Faction->fnGetFactionClose(sFactionName);  //团结度
    YString sBanner=g_Faction->fnGetFacionBanner(sFactionName); //帮派口号
    display("[<font color="+sColor+">"+sFactionName+"</font>]<br>帮主：["+sOwner+"]<br>势力值：["
                +(YString)nPower+"]<br> 团结度：["+(YString)nSolid+"]<br>口号：["+sBanner+"]");
  }
  return 1;
}
//----------------------------------------------------------
//解散一个玩家帮派
int YPlayer::fnDisband(YString command)
{
  YString sFactionName=command.getWord();
  if(getIsFactionOwner() != 1){             //"是否帮主"
    display("你无权解散一个帮会。");
    return 1;
  }
  if(getFactionName() !=sFactionName){      //"加入帮派"
    display("你不是["+sFactionName+"]的帮主。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sMyName=getActorName(); //player的名字
  if(g_Faction->fnGetFacionOwner(sFactionName) != sMyName){
    display("帮主纪录不符，请和巫师联系。");
    return 1;
  }
  //解散
  g_Faction->fnRemoveFaction(sFactionName);  //删除一个帮派
  g_Faction->save();
  
  display("你决定解散["+sFactionName+"]！");
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+sMyName+"解散了["+sFactionName+"]！["+sFactionName
          +"]从此烟消云散！</font>",NULL,NULL,CHANNEL_MSG);
  return 1;
}
//----------------------------------------------------------
//玩家申请加入一个帮派
int YPlayer::fnJoinFaction(YString command)
{
  YString sMyFactionName=getFactionName();    //"加入帮派"
  if(sMyFactionName!=""){
    display("你已经加入了["+sMyFactionName+"]，不能再加入别的帮派。");
    return 1;
  }
  YString sFactionOwnerName=command.getWord(); //帮主名字
  YAbstractActor *pAbstractActor=getRoom()->findChildActor(sFactionOwnerName);
  if(!pAbstractActor){
    display("你要加入谁的帮派？");
    return 1;
  }
  YPlayer *player;
  if(pAbstractActor->isTypeOf("YPlayer") != 1){
    display("对方是NPC。");
    return 1;
  }
  else player=(YPlayer*)pAbstractActor;
  if(player->getIsFactionOwner() != 1){           //"是否帮主"
    display(sFactionOwnerName+"不是一帮之主。");
    return 1;
  }
  YString sFactionName=player->getFactionName();    //"加入帮派"
  if(sFactionName==""){
    display(sFactionOwnerName+"的帮派有问题，请联系巫师。");
    return 1;
  }
  //申请加入
  set("加入_"+sFactionName,"待批准");
  display("你单膝跪地，对"+sFactionOwnerName+"拱手说道：属下愿追随帮主，赴汤蹈火，在所不辞！");
  YString sPlayerName=getActorName(); //本玩家的名字
  player->display(sPlayerName+"单膝跪地，对你拱手说道：属下愿追随帮主，赴汤蹈火，在所不辞！");
  player->display(sPlayerName+"申请加入["+sFactionName+"]，正在等待你的批准。");
  getRoom()->getRoomChat()->talk(NULL,
        sPlayerName+"单膝跪地，对"+sFactionOwnerName+"拱手说道：属下愿追随帮主，赴汤蹈火，在所不辞！",this,player);
  return 1;
}
//----------------------------------------------------------
//同意对方的入帮申请
int YPlayer::fnAgreeJoin(YString command)
{
  if(getIsFactionOwner() != 1){         //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString sApplyName=command.getWord(); //申请人的名字
  YAbstractActor *pAbstractActor=getRoom()->findChildActor(sApplyName);
  if(!pAbstractActor){
    display("你要同意谁的申请？");
    return 1;
  }
  YPlayer *player;
  if(pAbstractActor->isTypeOf("YPlayer") != 1){
    display("对方是NPC。");
    return 1;
  }
  else player=(YPlayer*)pAbstractActor;
  YString sFactionName=getFactionName(); //我的帮派"加入帮派"
  if(sFactionName==""){
    display("你的帮派有问题，请联系巫师。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sJoinStatus=player->getAsString("加入_"+sFactionName);  //加入状态
  if(sJoinStatus == "已经加入"){
    display(sApplyName+"已经加入了["+sFactionName+"]。");
    return 1;
  }
  else if(sJoinStatus != "待批准"){
    display(sApplyName+"并没有申请加入["+sFactionName+"]。");
    return 1;
  }
  //批准
  int i=g_Faction->fnFacionAddPlayer(sFactionName,sApplyName); //添加新成员
  if(i == -1){ //表示该成员已经存在
    display(sApplyName+"已经加入了["+sFactionName+"]。");
    return 1;
  }
  else if(i == -2){ //表示该成员已经超出范围
    display("你的帮派成员已经太多了不能再加入人了。");
    return 1;
  }

  player->set("加入_"+sFactionName,"已经加入");
  player->setFactionName(sFactionName); //"加入帮派"
  player->setFactionTitle("新弟子");    //"帮派头衔"
  g_Faction->fnSetFactionPower(sFactionName,0,1); //加入一个人，势力值+1
  long nOldPower,nNewPower;  //势力值
  nOldPower=0;
  nNewPower=player->fnReSumPower();   //玩家计算一下自己的势力值
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,nNewPower); //改变势力值
  player->setOldPower(nNewPower);  //保存这次的势力值 "上次势力"
  g_Faction->save();
  //显示批准的话语
  display("你微微一笑，对"+sApplyName+"朗声说到：好，本帮又添一位栋梁之才阿！");
  display("你批准了"+sApplyName+"的申请，他加入了你们的["+sFactionName+"]。");
  YString sMyName=getActorName(); //本玩家(帮主)的名字
  player->display(sMyName+"微微一笑，对你朗声说到：好，本帮又添一位栋梁之才阿！");
  player->display("你加入了["+sFactionName+"]。");
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+sApplyName+"加入了["+sFactionName+"]！</font>",NULL,NULL,CHANNEL_MSG);
  YChat* pMyFactionChat=getFactionChat(); //得到自己身上存的频道指针
  if(!pMyFactionChat) return 1;
  pMyFactionChat->subscribe(player);    //订阅频道
  player->setFactionChat(pMyFactionChat);      //保存玩家频道的指针
  return 1;
}
//-------------------------------------------------------------------------
//得到帮派信息颜色
YString YPlayer::getFactionMsgColor()
{
  return "green";
}
//----------------------------------------------------------
//开除一位玩家
int YPlayer::fnFireOut(YString command)
{
  if(getIsFactionOwner() != 1){         //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString sFireManName=command.getWord(); //被开除人的名字
  if(sFireManName == getActorName()){
    display("你不能开除自己。");
    return 1;
  }
  YPlayer *player=g_PlayerManager->getPlayer(sFireManName);
  if(!player){
    display("对方目前不在游戏中。");
    return 1;
  }
  YString sFactionName=getFactionName(); //你的帮派"加入帮派"
  if(player->getFactionName() != sFactionName){
    display("对方和你不是同一帮派。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  //开除
  g_Faction->fnFacionSubPlayer(sFactionName,sFireManName); //减去一个成员
  player->set("加入_"+sFactionName,"");
  player->setFactionName("");     //"加入帮派"
  player->setFactionTitle("");    //"帮派头衔"
  g_Faction->fnSetFactionPower(sFactionName,1,0); //减少一个人，势力值-1
  long nOldPower=player->getOldPower(); //上次的势力值 "上次势力"
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,0); //改变势力值
  player->setOldPower(0);  //势力值清0"上次势力"
  g_Faction->save();
  //显示批准的话语
  display("<font color=red>你开除了"+sFireManName+"，他退出了["+sFactionName+"]。</font>");
  player->display("<font color=red>你被["+sFactionName+"]开除了！</font>");
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+sFireManName+"被["+sFactionName+"]开除了！</font>",NULL,NULL,CHANNEL_MSG);
  YChat* pHisFactionChat=player->getFactionChat(); //得到对方身上存的频道指针
  if(!pHisFactionChat) return 1;
  pHisFactionChat->unsubscribe(player);    //退订频道
  player->setFactionChat(NULL);            //频道指针请空
  return 1;
}
//----------------------------------------------------------
//退出一个帮派
int YPlayer::fnUnJoin(YString command)
{
  YString sFactionName=command.getWord();               //帮派名
  if(g_Faction->isFacionExisting(sFactionName) == 0){   //该帮会不存在
    display("目前江湖之中并没有这个帮派。");
    return 1;
  }
  if(sFactionName != getFactionName()){          //你的帮派"加入帮派"
    display("你没有加入过这个帮派。");
    return 1;
  }
  if(getIsFactionOwner() == 1){               //"是否帮主"
    display("你是一帮之主，不能退出帮会。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  //退出
  YString sMyName=getActorName(); //本人的名字
  g_Faction->fnFacionSubPlayer(sFactionName,sMyName); //减去一个成员
  set("加入_"+sFactionName,"");
  setFactionName("");   //"加入帮派"
  setFactionTitle("");  //"帮派头衔"
  g_Faction->fnSetFactionPower(sFactionName,1,0); //减少一个人，势力值-1
  long nOldPower=getOldPower(); //上次的势力值 "上次势力"
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,0); //改变势力值
  setOldPower(0);  //势力值清0"上次势力"
  g_Faction->save();
  //显示批准的话语
  display("<font color=red>你退出了["+sFactionName+"]！</font>");
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+sMyName+"退出了["+sFactionName+"]！</font>",NULL,NULL,CHANNEL_MSG);
  YChat* pMyFactionChat=getFactionChat(); //得到自己身上存的频道指针
  if(!pMyFactionChat) return 1;
  pMyFactionChat->unsubscribe(this);    //退订频道
  setFactionChat(NULL);                 //频道指针请空
  return 1;
}
//----------------------------------------------------------
//设定帮派成员的头衔
int YPlayer::fnExalt(YString command)
{
  if(getIsFactionOwner() != 1){     //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString name=command.getWord();
  YString title=command.getWord();
  if(title.size() >= 20){
    display("这个头衔太长了。");
    return 1;
  }
  YPlayer *player=g_PlayerManager->getPlayer(name);
  if(!player){
    display("对方目前不在游戏中。");
    return 1;
  }
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName != player->getFactionName()){
    display("对方和你不是同一个帮派。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sMyName=getActorName(); //本人的名字
  //晋升
  player->setFactionTitle(title); //"帮派头衔"
  YString color=g_Faction->fnGetFacionColor(sFactionName);  //帮派颜色
  if(sMyName == name){  //给自己封衔
    display("你设定自己的头衔为：<font color="+color+">["+title+"]</font>。");
  }
  else{
    display("你设定"+name+"的头衔为：<font color="+color+">["+title+"]</font>。");
    display("你微微一笑："+name+"，本座任命你为<font color="+color
              +">["+title+"]</font>，望你能再接再励，光大本帮！");
    player->display(sMyName+"对你微微一笑："+name+"，本座任命你为<font color="+color
              +">["+title+"]</font>，望你能再接再励，光大本帮！");
  }
  return 1;
}
//----------------------------------------------------------
//察看本帮信息
int YPlayer::fnMyFaction(YString command)
{
  YString sFactionName=getFactionName();    //"加入帮派"
  if(sFactionName == ""){
    display("你没有加入任何玩家帮派。");
    return 1;
  }
  if(g_Faction->isFacionExisting(sFactionName) == 0){   //该帮会不存在
    display("你的帮派有问题，请和巫师联系。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sFactionTitle=getFactionTitle();                  //"帮派头衔"
  YString color=g_Faction->fnGetFacionColor(sFactionName);  //帮派颜色
  YString sFactionColorName="<font color="+color+">["+sFactionName+"]</font>";  //带颜色的帮派名字
  long nPower=g_Faction->fnGetFactionPower(sFactionName);   //势力值
  long nClose=g_Faction->fnGetFactionClose(sFactionName);   //团结度
  YString sBanner=g_Faction->fnGetFacionBanner(sFactionName);   //口号
  long nMyPower=getOldPower();                      //功勋值"上次势力"
  long nAmount=g_Faction->fnGetPlayerAmount(sFactionName);  //人数
  YString sFactionPlayerList=g_Faction->getAsString(sFactionName+"_成员列表");
  display("你是"+sFactionColorName+"的<font color="+color+">["+sFactionTitle+"]</font>。");
  display(sFactionColorName+"目前的江湖势力为[&nbsp;"+(YString)nPower+"&nbsp;]。");
  display(sFactionColorName+"目前的团结度为[&nbsp;"+(YString)nClose+"&nbsp;]。");
  display(sFactionColorName+"目前的口号为[&nbsp;"+sBanner+"&nbsp;]。");
  display("你的功勋值为[&nbsp;"+(YString)nMyPower+"&nbsp;]。");
  display(sFactionColorName+"共有[&nbsp;"+(YString)nAmount+"&nbsp;]名弟子。");
  display("分别是：");
  YString playername;   //成员的名字
  YString title;        //成员的头衔
  YPlayer *player;
  for(int i=0;i<nAmount;i++){
    playername=sFactionPlayerList.getWord();
    if(playername=="") break;
    player=g_PlayerManager->getPlayer(playername);
    if(!player){  //不在线
      display(playername);
    }
    else{         //在线
      YString title=player->getFactionTitle();    //"帮派头衔"
      display("<font color="+color+">["+title+"]</font>"+playername);
    }
  }
  return 1;
}
//----------------------------------------------------------
//任命别人担任帮主
int YPlayer::fnDemise(YString command)
{
  if(getIsFactionOwner() != 1){     //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString name=command.getWord();  //继承人的名字
  YString sMyName=getActorName(); //本人的名字
  if(sMyName == name){
    display("你只能传位给别人。");
    return 1;
  }
  YPlayer *player=g_PlayerManager->getPlayer(name);
  if(!player){
    display("对方目前不在游戏中。");
    return 1;
  }
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName != player->getFactionName()){
    display("对方和你不是同一个帮派。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sex=player->getSexString(); //对方的性别
  YString sexname;
  if(sex == "男") sexname="他";
  else if(sex == "女") sexname="她";
  else sexname="它";
  if(player->getExperience() < EXP){
    display(sexname+"的经验还不够。");
    return 1;
  }
  if(player->getDeposit() < MONEY){
    display(sexname+"的存款还不够。");
    return 1;
  }
  if(player->getInhereAttack() < ATTACK){
    display(sexname+"的武功还不够。");
    return 1;
  }
  if(player->getInhereDefense() < DEFENSE){
    display(sexname+"的武功还不够。");
    return 1;
  }
  long goodness=player->getGoodnessCount(); //正气值
  if((goodness < GOODNESS) && (goodness > EVILNESS)){
    display(sexname+"的正气值还不够。");
    return 1;
  }
  if(player->getSocietyValue() < CREDIT){
    display(sexname+"在江湖中的声望尚浅，不能担任帮主。");
    return 1;
  }
  //任命
  setIsFactionOwner(0);             //"是否帮主"
  player->setIsFactionOwner(1);     //"是否帮主"
  setFactionTitle("前帮主");        //"帮派头衔"
  player->setFactionTitle("帮主");  //"帮派头衔"
  long nOldPower,nNewPower;  //势力值
  //本人的势力计算
  nOldPower=getOldPower();    //"上次势力"
  nNewPower=fnReSumPower();   //玩家计算一下自己的势力值
  setOldPower(nNewPower);     //刷新势力值"上次势力"
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,nNewPower); //改变势力值
  //对方的势力计算
  nOldPower=player->getOldPower();    //"上次势力"
  nNewPower=player->fnReSumPower();   //玩家计算一下自己的势力值
  player->setOldPower(nNewPower);     //刷新势力值"上次势力"
  g_Faction->fnSetFactionPower(sFactionName,nOldPower,nNewPower); //改变势力值
  g_Faction->save();
  //显示
  display("<font color=red>你把帮主之位传给了"+name+"。</font>");
  player->display("<font color=red>"+sMyName+"把帮主之位传给了你。</font>");
  g_RumorChat->talk(NULL,"<font color="+getFactionMsgColor()+">【顺风耳】"
          +"据江湖传言"+name+"接替"+sMyName+"出任["+sFactionName+"]的帮主！</font>",NULL,NULL,CHANNEL_MSG);
  return 1;
}
//----------------------------------------------------------
//设置帮派颜色
int YPlayer::fnSetFactionColor(YString command)
{
  if(getIsFactionOwner() != 1){           //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName == ""){
    display("你的帮派有问题，请联系巫师。");
    return 1;
  }
//  YString sMyName=getActorName(); //本人的名字
//  YString owner=g_Faction->fnGetFacionOwner(sFactionName);  //得到帮主名字
//  if(owner != sMyName){
//    display("你的帮派有问题2，请联系巫师。");
//    return 1;
//  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString color=command.getWord();
  if(color.size() > 6){
    display("你设置的颜色不能显示。");
    return 1;
  }
  g_Faction->fnSetFacionColor(sFactionName,color);  //设置帮派颜色了
  g_Faction->save();
  //显示
  display("你设置["+sFactionName+"]的帮派颜色为<font color="
            +color+">["+sFactionName+"]</font>！");
  return 1;
}
//----------------------------------------------------------
//设置帮派口号
int YPlayer::fnSetFactionBanner(YString command)
{
  if(getIsFactionOwner() != 1){           //"是否帮主"
    display("你不是一帮之主。");
    return 1;
  }
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName == ""){
    display("你的帮派有问题，请联系巫师。");
    return 1;
  }
  YString sMyName=getActorName(); //本人的名字
  YString owner=g_Faction->fnGetFacionOwner(sFactionName);  //得到帮主名字
  if(owner != sMyName){
    display("你的帮派有问题2，请联系巫师。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString banner=command.getWord();
  if(banner.size() > 20){
    display("你设置的帮派口号太长了。");
    return 1;
  }
  g_Faction->fnSetFacionBanner(sFactionName,banner);  //设置帮派口号了
  g_Faction->save();
  //显示
  display("你设置["+sFactionName+"]的口号为[&nbsp;"+banner+"&nbsp;]！");
  return 1;
}
//----------------------------------------------------------
//向帮主行礼
int YPlayer::fnSalute(YString command)
{
  YString sMyFactionName=getFactionName(); //本人的帮派名字"加入帮派"
  if(sMyFactionName == ""){
    display("你没有加入过任何玩家帮派。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sMyFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  //本人的势力计算
  long nOldPower,nNewPower;  //旧、新势力值
  YString sFactionOwner=command.getWord();  //帮主名字
  YString sMyName=getActorName(); //本人名字
  if(sFactionOwner == sMyName){   //自己向自己行礼
    if(getIsFactionOwner() != 1){ //不是帮主
      display("你不需要向自己行礼。");
      return 1;
    }
    //帮主可以自己向自己行礼，以更新势力值
    nOldPower=getOldPower();    //"上次势力"
    nNewPower=fnReSumPower();   //玩家计算一下自己的势力值
    if(nOldPower != nNewPower){
      setOldPower(nNewPower);  //刷新势力值"上次势力"
      g_Faction->fnSetFactionPower(sMyFactionName,nOldPower,nNewPower); //改变势力值
      g_Faction->save();
    }
    //显示
    display("你得意地向自己一拱手，说道：恭迎帮主！然后忍不住哈哈大笑起来。");
    getRoom()->getRoomChat()->talk(NULL,
        sMyName+"得意地向自己一拱手，说道：恭迎帮主！然后忍不住哈哈大笑起来。",this,NULL);
    return 1;
  }
  YAbstractActor *pAbstractActor=getRoom()->findChildActor(sFactionOwner);
  if(!pAbstractActor){
    display("你要向谁行礼？");
    return 1;
  }
  if(pAbstractActor->isTypeOf("YPlayer") != 1){
    display("对方是NPC。");
    return 1;
  }
  YPlayer *player=(YPlayer*)pAbstractActor;
  YString sFactionName=player->getFactionName();    //"加入帮派"
  if(sFactionName != sMyFactionName){
    display("对方和你不是同一帮派。");
    return 1;
  }
  if(player->getIsFactionOwner() != 1){     //"是否帮主"
    display("对方不是帮主。");
    return 1;
  }
  nOldPower=getOldPower();    //"上次势力"
  nNewPower=fnReSumPower();   //玩家计算一下自己的势力值
  if(nOldPower != nNewPower){
    setOldPower(nNewPower);  //刷新势力值"上次势力"
    g_Faction->fnSetFactionPower(sFactionName,nOldPower,nNewPower); //改变势力值
    g_Faction->save();
  }
  //显示
  display("你向"+sFactionOwner+"一拱手，说道：恭迎帮主！");
  player->display(sMyName+"向你一拱手，说道：恭迎帮主！");
  getRoom()->getRoomChat()->talk(NULL,
        sMyName+"向"+sFactionOwner+"一拱手，说道：恭迎帮主！",this,player);
  return 1;
}
//----------------------------------------------------------
//登陆时处理玩家帮派问题
void YPlayer::fnProcessFaction()
{
  YString sFactionName=getFactionName();    //"加入帮派"
  if(sFactionName == "") return;  //如果没有加入帮派，返回

  if(g_Faction->fnGetFacionStatus(sFactionName) == "已经解散"){
    display("<font color=red>你加入的帮派["+sFactionName+"]已经解散！</font>");
    setFactionName("");   //"加入帮派"
    setFactionTitle("");  //"帮派头衔"
    setOldPower(0);       //"上次势力"
    setIsFactionOwner(0); //"是否帮主"
    set("加入_"+sFactionName,"");
  }
  else if(g_Faction->isFacionExisting(sFactionName) == 1){     //此帮派存在
    if(g_Faction->isFacionPlayerExisting(sFactionName,getActorName()) != 1){  //说明这个帮派中没有这个人
      display("<font color=red>你加入的帮派["+sFactionName+"]已经重建！</font>");
      setFactionName("");   //"加入帮派"
      setFactionTitle("");  //"帮派头衔"
      setOldPower(0);       //"上次势力"
      setIsFactionOwner(0); //"是否帮主"
      set("加入_"+sFactionName,"");
    }
    else{     //帮派存在，人也存在
      YChat* pMyFactionChat=g_ChatManager->getChat(sFactionName);
      if(!pMyFactionChat) return;
      pMyFactionChat->subscribe(this);    //订阅频道
      setFactionChat(pMyFactionChat);     //保存玩家频道的指针
    }
  }
  else{
    display("<font color=red>你的帮派有问题，请和巫师联系解决！</font>");
    //不清空"加入帮派"等属性，保留现场
  }
  return;
}
//----------------------------------------------------------
//显示巫师关闭帮会的信息
void YPlayer::fnShowWizCloseMsg()
{
  display("你的帮派被巫师暂时关闭，请和巫师联系。");
  return;
}
//----------------------------------------------------------
//邀请某人来帮会总舵
int YPlayer::fnInvite(YString command)
{
  if(getIsFactionOwner() != 1){           //"是否帮主"
    display("你不是一帮之主，无权邀请客人。");
    return 1;
  }
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName == ""){
    display("你的帮派有问题，请联系巫师。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  YString sGuestName=command.getWord();
  YString sCount=command.getWord();
  long nCount=sCount.toLong();
  if(nCount <= 0) nCount=1;                     //最少一次
  if(nCount > 99) nCount=99;                    //最多99，表示无限
  YPlayer *player=g_PlayerManager->getPlayer(sGuestName);
  if(!player){
    display("对方目前不在游戏中。");
    return 1;
  }
  YString sMyName=getActorName(); //本人的名字
  if(isTypeOf("YWizard") != 1){
    YString blackname=player->getAsString("关闭对话列表");
    if(blackname == "全部人物名称"){
      display("对方不愿意和你交谈。");
      return 1;
    }
    YString tempname;
    while((tempname=blackname.getWord()) != ""){
      if(tempname == sMyName){
        display("对方不愿意和你交谈。");
        return 1;
      }
    }
  }
  //
  player->set("邀请参观次数_"+sFactionName,nCount); //设置参观次数
  //显示
  YString sex=player->getSexString(); //对方的性别
  YString sexname;
  if(sex == "男") sexname="他";
  else sexname="她";
  if(nCount == 99){
    display("你邀请"+sGuestName+"参观帮会总舵，"+sexname+"永远可以参观。");
  }
  else display("你邀请"+sGuestName+"参观帮会总舵，"+sexname+"可以参观"+(YString)nCount+"次。");
  player->display("<font color=red>"+sMyName+"邀请你参观["+sFactionName+"]总舵。</font>");
  return 1;
}
//-------------------------------------------------
//用玩家自建帮派频道说话(party2)
int YPlayer::fnFactionParty(YString word)
{
  YString sFactionName=getFactionName();  //你的帮派"加入帮派"
  if(sFactionName == ""){
    display("你没有加入任何一个玩家帮派。");
    return 1;
  }
  YChat* pMyFactionChat=getFactionChat();
  if(!pMyFactionChat){
    display("你的帮派有问题，频道没有打开，请联系巫师。");
    return 1;
  }
  if(g_Faction->fnGetFacionStatus(sFactionName) == "被巫师关闭"){
    fnShowWizCloseMsg();  //显示关闭信息
    return 1;
  }
  if(checkclose() != 0) return 1;
  if(getCloseFactionParty() == 1){    //关闭帮派频道
    pMyFactionChat->subscribe(this);  //订阅
    setCloseFactionParty(0);
  }
  if(repeat("上次发言",word) == 1) return 1; //重复发言
  //查找替换< >   注：由于>在页面没反映所以不与处理
  word=changeword(word);
  if(word.size() > 100){
    display ("你的话也太长了点吧。");
    return 1;
  }
  YString color=g_Faction->fnGetFacionColor(sFactionName);  //帮派颜色
  word="<font color="+color+">【"+sFactionName+"】"
        +getActorName()+":"+word+"</font>";
  pMyFactionChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
