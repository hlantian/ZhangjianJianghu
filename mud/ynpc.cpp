//---------------------------------------------------------------------------
//
// ynpc.cpp    2000年6月12日
//
// 类YNPC：NPC
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YNPC::YNPC(YString initFileName):YActor(initFileName),
                                  m_AllowPrentice(0),
                                  m_AnswerForAgreePrentice(""),
                                  m_ProvideQuest(0),
                                  m_NeedPate(0),
                                  m_NeedKillBySelf(0),
                                  m_NeedGeBySelf(0),
                                  m_PlayerSayWhenGiveup(""),
                                  m_NPCSayWhenNoQuest(""),
                                  m_NPCSayWhenGiveup(""),
                                  m_AppraiseName(""),
                                  m_NPCSayWhenBeGive(""),
                                  m_NPCSayWhenEndQuest(""),
                                  m_UniteKill(0)
{
  g_PlayerManager->addNPC(this);
  setSmallTime(2000);
}
//--------------------------------------------------------
//析构函数
YNPC::~YNPC()
{
  g_PlayerManager->removeNPC(getActorName());
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YNPC::isTypeOf(YString className)
{
  if(className=="YNPC") return 1;
  else return YActor::isTypeOf(className);
}

//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YNPC::onAfterLoad(void)
{
  int retVal=YActor::onAfterLoad();
  
  setAllowPrentice(getAsLong("收徒"));
  setAnswerForAgreePrentice(getAsString("同意拜师的回答"));
  setProvideQuest(getAsLong("是否发任务"));
  setNeedPate(getAsLong("需要首级"));
  setNeedKillBySelf(getAsLong("需亲自杀"));
  setNeedGeBySelf(getAsLong("需亲自割"));
  setPlayerSayWhenGiveup(getAsString("玩家放弃时说话"));
  setNPCSayWhenNoQuest(getAsString("无任务说话"));
  setNPCSayWhenGiveup(getAsString("被放弃任务说话"));
  setAppraiseName(getAsString("评价名"));
  setNPCSayWhenBeGive(getAsString("被给"));
  setNPCSayWhenEndQuest(getAsString("被完成任务说话"));
  setUniteKill(getAsLong("联合协防"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YNPC::onBeforeSave(void)
{
  int retVal=YActor::onBeforeSave();
  
  set("收徒",getAllowPrentice());
  set("同意拜师的回答",getAnswerForAgreePrentice());
  set("是否发任务",getProvideQuest());
  set("需要首级",getNeedPate());
  set("需亲自杀",getNeedKillBySelf());
  set("需亲自割",getNeedGeBySelf());
  set("玩家放弃时说话",getPlayerSayWhenGiveup());
  set("无任务说话",getNPCSayWhenNoQuest());
  set("被放弃任务说话",getNPCSayWhenGiveup());
  set("评价名",getAppraiseName());
  set("被给",getNPCSayWhenBeGive());
  set("被完成任务说话",getNPCSayWhenEndQuest());
  set("联合协防",getUniteKill());
  
  return retVal;
}

//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YNPC::getDisplayName(void)
{
  YString name=getActorName(); //名字
  //return "sa(\'"+name+"\');";
  return "<font color="+g_Settings->getNPCNameColor()
          +"><span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+name+"\")>"+name+"</span></font>";
}
//-------------------------------------------------------------
//属性： NickName (显示人物得绰号和名字)
YString YNPC::getNickName(void)
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
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="ask") retVal=beAsk(executor,cmd);//被别人询问
  else if(commandVerb=="bai") retVal=beBai(executor,cmd);//被拜师
  else if(commandVerb=="give") retVal=beGive(executor,cmd);//别人给东西
  else if(commandVerb=="giveup") retVal=beGiveup(executor);//被放弃任务
  else if(commandVerb=="quest") retVal=beQuest(executor);//被领取任务
  else if(commandVerb=="xue") retVal=beXue(executor,cmd);//被学习
  else if(commandVerb=="cunquit") retVal=becunquit(executor,cmd);//被存任务
  else if(commandVerb=="kill") retVal=fnUniteKill(executor,cmd);//联合协防

  if(!retVal) return YActor::executeCommandAsTarget(executor,command);
  else return retVal;
}

int YNPC::becunquit(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord(); //所学的对象
  YString commandCount=cmd.getWord(); //学习的次数
  long count=commandCount.toLong();
  player->display(commandTarget);
  return 1;
}


//--------------------------------------------------------
//被学习
int YNPC::beXue(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord(); //所学的对象
  YString commandSkills=cmd.getWord(); //所学的武功名
  YString commandCount=cmd.getWord(); //学习的次数
  long count=commandCount.toLong();
  if(count<1) count=1; //最少一次
  if(count>1000) count=1000; //最大一千
  YString msg;
  long GradeExp;//武功经验
  long Savvy;//悟性
  YString Zhaoshu;//武功招数
  YString MyName=getActorName(); //本NPC的名字
  if(commandTarget!=MyName) return 1;
  YString Teacher=player->getTeacherName(); //player的师父
  if(Teacher!=MyName){
     player->display(MyName+"不是你的师父!");
     return 1;
  }
  YString allSkills=getAllSkillsList(); //本NPC的所有技能
  int i=allSkills.find(commandSkills,0); //查找本NPC是否会player要学的技能
  if(i==YString::npos){
     player->display("你的师父不懂这种技能。");
     return 1;
  }
  if(getAsLong(commandSkills)==0){
     player->display("你的师父不懂这种技能。");
     return 1;
  }
  long Potential=player->getPotential(); //player目前的潜能
  long Energy=player->getEnergy(); //player目前的精力
  //学这种武功每次消耗的潜能
  long PotentialUsed=g_Wugong->wugong_qianneng_used(commandSkills);
  if(PotentialUsed<=0) PotentialUsed=1; //默认值为1
  //学这种武功每次消耗的精力
  long EnergyUsed=g_Wugong->wugong_jingli_used(commandSkills);
  if(EnergyUsed<=0) EnergyUsed=1; //默认值为1
  if(Potential<PotentialUsed){
     player->display("你的潜能不足!");
     return 1;
  }
  if(Energy<EnergyUsed){
     player->display("你的精力不足!");
     return 1;
  }
  long Grade=player->getSkillLevel(commandSkills); //player的武功等级
  long teacherGrade=getAsLong(commandSkills); //本NPC的武功等级
  if(Grade>=teacherGrade){
     player->display("你的["+commandSkills+"]已经不低于你的师父了。");
     return 1;
  }
  YString isnotEspecialWugong=g_Wugong->wugong_isnot_especialWugong(commandSkills);
  if(isnotEspecialWugong=="是"){
     long numCondition=getAsLong(commandSkills+"_条件个数");
     for(int i=0;i<numCondition;i++){
        //例:华山剑法_条件一
        YString strCondition=getAsString(commandSkills+"_条件"+LongToChinese(i+1));
        YString itemConnection=strCondition.getWord(); //项目关系(大于,等于...)
        YString itemName=strCondition.getWord(); //项目名字(紫霞功...)
        YString itemAnswer=strCondition.getWord(); //项目回答
        if((itemConnection!="大于")&&(itemConnection!="等于")&&(itemConnection!="小于"))
        {
          msg=MyName+"对&s说:今天我生病了,不能教你武功。";
          OutputMsg(player,msg);
          g_err.show("[YNPC::beXue]"+MyName+"_学习条件_项目关系_出错");
          return 1;
        }
        long itemNameGrade=player->getAsLong(itemName); //项目名字的等级
        if(((itemConnection=="大于")&&(Grade<=itemNameGrade))|| //条件不满足则拒绝
           ((itemConnection=="等于")&&(Grade!=itemNameGrade))||
           ((itemConnection=="小于")&&(Grade>=itemNameGrade)))
        {
          OutputMsg(player,itemAnswer); //给player的回答,拒绝教武功
          return 1;
        }
     }
     YString basicWugong=g_Wugong->wugong_corresponding_basicWugong(commandSkills);
     long basicWugongGrade=player->getSkillLevel(basicWugong);//getAsLong(basicWugong); //基本武功等级
     if(Grade>=basicWugongGrade){
        player->display(MyName+"说道:你的基本功还没练熟,再去练练!");
        return 1;
     }
  }
  YString Motion=g_Wugong->CurrentLearningZhaoshu(commandSkills,Grade);
  if(Motion==""){
     player->display(MyName+"指导了你一些["+commandSkills+"]的要点。");
     player->display("你似乎有些心得,在心里细细体会。");
  }
  else{
     player->display(MyName+"指导了你一招["+Motion+"]");
     player->display("你似乎有些心得,在心里细细体会.");
  }
  long poCount=Potential/PotentialUsed; //潜能支持的最大次数
  long enCount=Energy/EnergyUsed; //精力支持的最大次数
  if(count>poCount) count=poCount;
  if(count>enCount) count=enCount;
  Potential-=count*PotentialUsed;
  Energy-=count*EnergyUsed;
  if(Potential<0) Potential=0;
  if(Energy<0) Energy=0;
  player->setPotential(Potential); //潜能
  player->setEnergy(Energy); //精力
  if(count>1){
    player->display("你学习了"+(YString)count+"次....");
  }
  YString playerAllSkills=player->getAllSkillsList(); //所会技能
  if(playerAllSkills.find(commandSkills,0)==YString::npos){
    if(playerAllSkills=="")
      playerAllSkills=commandSkills;
    else
      playerAllSkills+=" "+commandSkills;
    player->setAllSkillsList(playerAllSkills); //所会技能
  }
  GradeExp=player->getAsLong(commandSkills+"_经验"); //player当前的武功经验
  Savvy=player->getLastLearn();   //后天悟性
  if(Savvy < 20) Savvy=20;          //最小是20
  else if(Savvy > 100) Savvy=100; //最大是100
  //long step=(Savvy-20)*2+20; //以前的方法
  //-------------新方法
  long step=0;
  if(count < 500){
    step=rand()%Savvy;              //0-->Savvy随机
  }
  else{     // >= 500
    step=rand()%(Savvy/2)+Savvy/2;  //Savvy/2-->Savvy随机
  }
  step+=Savvy;                    //再加上Savvy
  //-------------新方法
  GradeExp+=step*count;    //学习count次所能学到的武功经验值
  if(GradeExp>=(Grade+1)*(Grade+1)*10){
    GradeExp=0; //武功经验清0
    player->playerlevelup(commandSkills); //player武功等级提升
  }
  player->set(commandSkills+"_经验",GradeExp);
  return 1;
}

//--------------------------------------------------------
//被别人询问
int YNPC::beAsk(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString answer = getAsString(command);
  if (answer == "")
  {
    player->display(getActorName()+"摇了摇头,对你说:我不知道。");
  }
  else display (answer);
  return 1;
}

//--------------------------------------------------------
//被拜师
int YNPC::beBai(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString msg;
  YString cmd=command;
  YString commandTarget=cmd.getWord();
  YString MyName=getActorName(); //本NPC的名字
  if(commandTarget!=MyName) return 1;
  if(getAllowPrentice()!=1){ //是否允许收徒弟
     player->display(MyName+"目前不能收徒!");
     return 1;
  }
  player->onBeforeSave();
  //player的门派,师父,辈分
  YString School=player->getSchool();
  if(School=="") player->setSchool("无"); //门派
  YString Teacher=player->getTeacherName(); //师父
  long schoolPlace=player->getSchoolPlace(); //辈分
  YString MySchool=getSchool(); //师父的门派
  long MySchoolPlace=getSchoolPlace(); //师父的辈分
  if(School==MySchool){
    if(Teacher==MyName){
      msg="&s恭恭敬敬地向"+MyName+"磕头请安,叫道:「师父!」";
      OutputMsg(player,msg);
      player->setMeipaichat();
      return 1;
    }
    else if(schoolPlace <= MySchoolPlace){  //玩家的辈分大于等于NPC的辈分
      msg=MyName+"对你说道:你在本门中辈分太高，我不能收你为徒。";
      player->display(msg);
      return 1;
    }
  }
  if(conditionEstimation(player,"拜师") != 0) return 1; //拜师条件判断
  //1-表示处理完成,拒绝拜师   0-表示继续处理,同意拜师  -1-表示出错
  
  // 那么收他为徒
  msg=getAnswerForAgreePrentice(); //同意拜师的回答
  OutputMsg(player,msg);
  msg=MyName+"决定收&s为弟子。";
  OutputMsg(player,msg);
  msg="&s跪了下来向"+MyName+"恭恭敬敬地磕了四个响头,叫道:「师父!」";
  OutputMsg(player,msg);
  //schoolPlace=你在门派中的位置=辈分
  schoolPlace=MySchoolPlace+1; //player的辈分等于师父的辈分加1
  player->display("恭喜您成为"+MySchool+"的第"+LongToChinese(schoolPlace)+"代弟子。");
  if(MySchool!="丐帮")
    player->setTitle(MySchool+"第"+LongToChinese(schoolPlace)+"代弟子"); //设置头衔
  else{
    long pocket=27-schoolPlace;
    if(pocket>9) pocket=9;
    if(pocket<5) pocket=5;
    if(pocket==9)
      player->setTitle("丐帮<font color=#ff8000>"+LongToChinese(pocket)+"袋长老</font>");
    else if(pocket==8)
      player->setTitle("丐帮<font color=#00aaaa>"+LongToChinese(pocket)+"袋护法</font>");
    else
      player->setTitle("丐帮"+LongToChinese(pocket)+"袋弟子");
  }
  player->setSchool(MySchool); //门派
  player->setTeacherName(MyName); //师父
  player->setSchoolPlace(schoolPlace); //辈分
  return 1;
}

//--------------------------------------------------------
//被领取任务
int YNPC::beQuest(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  long provideQuest=getProvideQuest(); //是否发任务
  if(provideQuest!=1){
     player->display("我目前不发放任务!");
     return 1;
  }
  YString MyName=getActorName(); //名字
  YString msg;
  if(player->getAsLong(MyName+"_任务间隔") != 0)
  {
    player->display(MyName+"对你说到：你这么不努力，我很生气，等会再给你任务！");
    return 1;
  }
  if(player->getAsString(MyName+"_任务目标")!=""){
     msg="<font color="+g_Settings->getQuestColor()+">"+MyName+"对&s说:你先把手头的任务完成了再说。</font>";
     player->displayEx(msg);
     return 1;
  }
  //YString Name=player->getAsString("名字");
  if(conditionEstimation(player,"任务") != 0){
    player->set("信息屏蔽",1); //禁止使用OutputMsg
    return 1;
  }

  //同意发任务
  YQuest *objQuest;
  objQuest=(YQuest*)g_Quest->findChild(MyName,"YQuest");
  if(!objQuest){
     player->display("我目前不发放任务!");
     return 1;
  }
  long questNumber=objQuest->randomReturnQuestNumber();//随机返回一个任务的序号
  YString questType=objQuest->specifyNumberQuestType(questNumber);
  YString questTarget=objQuest->specifyNumberQuestTarget(questNumber);
  YString questList=player->getQuestList(); //任务列表
  long pos=questList.find(MyName,0);
  if(pos==YString::npos){
     if(questList=="") questList=MyName;
     else questList=questList+" "+MyName;
  }
  player->setQuestList(questList); //任务列表
  player->set(MyName+"_任务号",questNumber);
  player->set(MyName+"_任务类型",questType);
  player->set(MyName+"_任务目标",questTarget);
  player->set(MyName+"_评价名",getAppraiseName()); //评价名
  if(questType=="找"){
     player->display("<font color="+g_Settings->getQuestColor()+">" +MyName+"想了想,说道:你去找回"+questTarget+"吧。</font>");
     player->set(MyName+"_任务描述","找回"+questTarget);
  }
  else if(questType=="找人"){
     player->display("<font color="+g_Settings->getQuestColor()+">" +MyName+"想了想,说道:你帮我把"+questTarget+"找过来，我想和他谈谈。</font>");
     player->set(MyName+"_任务描述","找到"+questTarget+"并把他带回来。");
  }
  else if(questType=="找东西"){
     player->display("<font color="+g_Settings->getQuestColor()+">" +MyName+"想了想,说道:你帮我把"+questTarget+"买过来吧。</font>");
     player->set(MyName+"_任务描述","把"+questTarget+"买回来。");
  }
  else if(questType=="杀"){
     if(getNeedPate()==1){ //需要首级
        player->set(MyName+"_需要首级",1); //必须拿回首级才奖励
        if(getNeedKillBySelf()==1){ //需要亲自杀
           player->display("<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:你去杀了"+questTarget+",提首级回来见我。</font>");
           player->set(MyName+"_任务描述","杀了"+questTarget+",取其首级。");
        }
        else{
           player->display("<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:你去提"+questTarget+"的首级回来。</font>");
           player->set(MyName+"_任务描述","取"+questTarget+"的首级。");
        }
     }
     else{
        player->set(MyName+"_需要首级",0); //杀了后立刻奖励
        player->display("<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:你去杀了"+questTarget+"。</font>");
        player->set(MyName+"_任务描述","杀了"+questTarget);
     }
  }
  else if(questType=="送"){
     //要送的物品和所需的时间
     YString questThing=objQuest->specifyNumberQuestThing(questNumber);//任务物品
     long questTime=objQuest->specifyNumberQuestTime(questNumber);//任务时间
     player->set(MyName+"_任务物品",questThing);
     player->set(MyName+"_任务时间",questTime);
     player->set(MyName+"_任务超时",0);
     long minute=(questTime/1000)/60; //分钟
     long second=(questTime/1000)-minute*60; //秒
     YString chineseMinute=LongToChinese(minute);
     YString chineseSecond=LongToChinese(second);
     YString msg="<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:给你"+chineseMinute+"分"+chineseSecond+"秒 \
                   的时间,把"+questThing+"送到"+questTarget+"那里,快去吧。</font>";
     player->display(msg);
     player->set(MyName+"_任务描述","送"+questThing+"给"+questTarget);
     //送东西需要onTimer支持,所以设置此属性,用来判断
     player->setGiveThing(player->getGiveThing()+1);//set("送东西数",player->getAsLong("送东西数")+1); //使用次数加一
     player->resumWeight();
     if((player->getWeight()) >= (player->getMaxWeight())){
       player->display(MyName+"一皱眉：你拿的东西太多了，自己想办法吧。");
       return 1;
     }
     YAbstractThing *objThing; //要送的物品
     objThing=(YAbstractThing*)loadObject("thing/"+questThing);
     if(!objThing){
        g_err.show("[YNPC::beQuest]loadObject"+questThing+" is NULL");
        return 1;
     }
     objThing->setCount(1);
     player->addChild(objThing);
     player->resumWeight(); //计算重量
  }
  else if(questType=="找送"){
     //要找送的物品和所需的时间
     YString questThing=objQuest->specifyNumberQuestThing(questNumber);//任务物品
     long questTime=objQuest->specifyNumberQuestTime(questNumber);//任务时间
     player->set(MyName+"_任务物品",questThing);
     player->set(MyName+"_任务时间",questTime);
     player->set(MyName+"_任务超时",0);
     long minute=(questTime/1000)/60; //分钟
     long second=(questTime/1000)-minute*60; //秒
     YString chineseMinute=LongToChinese(minute);
     YString chineseSecond=LongToChinese(second);
     YString msg="<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:给你"+chineseMinute+"分"+chineseSecond+"秒 \
                   的时间,找到"+questThing+",把它送到"+questTarget+"那里,快去吧。</font>";
     player->display(msg);
     player->set(MyName+"_任务描述","找到"+questThing+"送给"+questTarget);
     //送东西需要onTimer支持,所以设置此属性,用来判断
     player->setGiveThing(player->getGiveThing()+1);//set("送东西数",player->getAsLong("送东西数")+1); //使用次数加一,处理和送东西相同
  }
  else if(questType=="屠城"){
     YString questTargetType=objQuest->specifyNumberQuestTargetType(questNumber);//任务目标类型
     long questTime=objQuest->specifyNumberQuestTime(questNumber);//任务时间
     player->set(MyName+"_任务目标类型",questTargetType);
     player->set(MyName+"_任务时间",questTime);
     player->set(MyName+"_任务超时",0);
     long minute=(questTime/1000)/60; //分钟
     long second=(questTime/1000)-minute*60; //秒
     YString chineseMinute=LongToChinese(minute);
     YString chineseSecond=LongToChinese(second);
     YString msg;
     if(questTargetType=="性别"){
        msg="<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:给你"+chineseMinute+"分"+chineseSecond+"秒 \
                   的时间,去杀几个"+questTarget+"人,越多越好。</font>";
        player->set(MyName+"_任务描述","杀几个"+questTarget+"人");
     }
     else if(questTargetType=="位置"){
        msg="<font color="+g_Settings->getQuestColor()+">"+MyName+"想了想,说道:给你"+chineseMinute+"分"+chineseSecond+"秒 \
                   的时间,杀几个"+questTarget+"弟子,越多越好。</font>";
        player->set(MyName+"_任务描述","屠"+questTarget);
     }
     player->display(msg);
     player->setCityKill(player->getCityKill()+1);//set("屠城数",player->getAsLong("屠城数")+1); //使用次数加一
  }
  return 1;
}

//--------------------------------------------------------
//被放弃任务
int YNPC::beGiveup(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  long provideQuest=getProvideQuest(); //是否发任务
  if(provideQuest!=1){
     player->display("我目前不管任务的事!");
     return 1;
  }
  YString MyName=getActorName(); //名字
  YQuest *objQuest;
  objQuest=(YQuest*)g_Quest->findChild(MyName,"YQuest");
  if(!objQuest){
     player->display("我目前不管任务的事!");
     return 1;
  }
  YString msg;
  //
  if(player->getAsString(MyName+"_任务目标")=="")
  {
     msg=getNPCSayWhenNoQuest(); //player无任务时npc说话
     player->displayEx(msg); //屏蔽
     return 1;
  }
  else{
        long bOut=player->getAsLong("信息屏蔽"); //是否允许OutputMsg
        msg=getPlayerSayWhenGiveup(); //player放弃任务时说的话
        if(bOut == 1)
        { //屏蔽!
          player->displayEx(msg);
        }
        else
        {
          OutputMsg(player,msg);
          player->set("信息屏蔽",1); //禁止使用OutputMsg
        }
     //2004.06.19改好之后,意随宣布后遭到众人反对,所以下面的语句又注释掉了
     //player->set(MyName+"_任务间隔",1);
     msg=getNPCSayWhenGiveup(); //被放弃任务说话
     if(bOut == 1) player->displayEx(msg); //屏蔽
     else OutputMsg(player,msg); //不屏蔽
     long questTimes=player->getAsLong(MyName+"_连续次数");
     long questNumber=player->getAsLong(MyName+"_任务号");
     YString appraiseName=getAppraiseName(); //评价名
     if(appraiseName!=""){
        long rewardAppraise=objQuest->questRewardAppraise(questNumber,questTimes);//奖励评价
        long reduceAppraise=(long)(0.5*rewardAppraise); //降低的数值为应奖励评价的0.5倍
        player->display("你的"+appraiseName+"降低了"+LongToChinese(reduceAppraise)+"点。");
        if(appraiseName == "门派评价") player->setPartyValue(player->getPartyValue()-reduceAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
        else if(appraiseName == "朝廷声望") player->setCourtValue(player->getCourtValue()-reduceAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
        else if(appraiseName == "江湖声望") player->setSocietyValue(player->getSocietyValue()-reduceAppraise);//set(appraiseName,getAsLong(appraiseName)+rewardAppraise);
        //player->set(appraiseName,player->getAsLong(appraiseName)-reduceAppraise);
     }
     YString questType=player->getAsString(MyName+"_任务类型"); //任务类型
     if((questType=="送")||(questType=="找送")){
        player->set(MyName+"_任务物品","");
        player->set(MyName+"_任务时间",0);
        player->set(MyName+"_任务超时",0);
        player->setGiveThing(player->getGiveThing()-1);//set("送东西数",player->getAsLong("送东西数")-1);
     }
     else if(questType=="屠城"){
        player->set(MyName+"_任务目标类型","");
        player->set(MyName+"_任务时间",0);
        player->set(MyName+"_任务超时",0);
        player->setCityKill(player->getCityKill()-1);//set("屠城数",player->getAsLong("屠城数")-1);
     }
     player->set(MyName+"_连续次数",0);
     player->set(MyName+"_任务号",0);
     player->set(MyName+"_任务类型","");
     player->set(MyName+"_任务目标","");
     player->set(MyName+"_任务描述","");
     YString questList=player->getQuestList(); //任务列表
     if(questList==MyName) questList="";
     else{
       questList.removeWord(MyName);
     }
     player->setQuestList(questList); //任务列表
  }
  return 1;
}

//--------------------------------------------------------
//别人给东西
int YNPC::beGive(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString MyName=getActorName(); //名字
  YString msg;
  YString cmd=command;
  YString commandThing=cmd.getWord(); //要给的东西名
  YString command_To=cmd.getWord();//单词to
  YString commandTarget=cmd.getWord(); //给谁
  if((command_To!="to")||(commandTarget!=MyName)){
     player->display("命令格式错误。");
     player->display("正确的格式是:give sth. to sb.");
     return 1;
  }
  YAbstractThing* objThing=player->findChildThing(commandThing);
  if(!objThing){
     g_err.show("[YNPC::beGive]findChildThing_"+commandThing+" is NULL");
     player->display("你没有这种东西。");
     return 1;
  }
  //接受别人送来的东西
  YString questList=player->getQuestList(); //任务列表
  YString hisName;
  while((hisName=questList.getWord())!=""){
     if((player->getAsString(hisName+"_任务目标")==MyName)&&
        (player->getAsString(hisName+"_任务物品")==commandThing)){
       if((player->getAsString(hisName+"_任务类型")=="送")||
          (player->getAsString(hisName+"_任务类型")=="找送")){
          //player->giveChildTo(objThing,this);
          long count=objThing->getCount();
          if(count<1){
            player->display("你没有这种东西。");
            return 1;
          }
          else if(count==1){
            if(player->removeChild(objThing)) delete objThing;
          }
          else{
            objThing->setCount(count-1);
          }
          player->resumWeight(); //重新计算负重
//          player->ActorAddFeatureChange();
          player->ActorAddRecoveryChange();
          if(player->getAsLong(hisName+"_任务超时")==1){
            player->display(MyName+"惋惜地说:你来晚了,下次再努力。");
            player->set(hisName+"_任务号",0);
            player->set(hisName+"_任务类型","");
            player->set(hisName+"_任务目标","");
            player->set(hisName+"_任务描述","");
            player->delQuestpercent(hisName+"_连续次数",10);  //连续次数10%
          }
          else{
            player->display(MyName+"赞许地说:你辛苦了。");
            player->setGiveThing(player->getGiveThing()-1);//set("送东西数",player->getAsLong("送东西数")-1);
            player->getReward(hisName);
          }
          return 1;
       }
     }
  }
  //任务物品的递交
  long provideQuest=getProvideQuest(); //是否发任务
  YString questType=player->getAsString(MyName+"_任务类型");
  if((provideQuest!=1)||(questType=="")){
     YString msg=getNPCSayWhenBeGive(); //被给，被给东西时说话
     if(msg=="") player->display(MyName+"不接受你的东西。");
     else player->displayEx(msg);
     return 1;
  }
  YQuest *objQuest;
  objQuest=(YQuest*)g_Quest->findChild(MyName,"YQuest");
  if(!objQuest){
     player->display("我目前不管任务的事!");
     return 1;
  }
  YString questTarget=player->getAsString(MyName+"_任务目标");
  int wrong=0;
  if(questType=="找"){
    if(commandThing!=questTarget){
      player->display(MyName+"摇摇头说:我要的不是这个东西。");
      //return 1;
      wrong=1;
    }
  }
  else if(questType=="找人")
  {
    if(commandThing!=questTarget)
    {
      player->display(MyName+"说道，他不是我要找的人！");
      return 1;
    }
    else if  (commandThing == questTarget)
    {
       YActor* givenpc = (YActor*) player->findChildActor(questTarget);
       if (givenpc)
       {
         if(givenpc->isTypeOf("YNPC"))
         {
            YRoom* useRoom =(YRoom*) g_Map->getRoom(g_Settings->getNPCDeadRoom(),getRoom());
            if (useRoom)
            {
              player->giveChildTo(givenpc,useRoom);
              msg="&s把"+commandThing+"递给"+MyName+"。";
              OutputMsg(player,msg);
              msg=getNPCSayWhenEndQuest(); //被完成任务说话
              OutputMsg(player,msg);
              player->getReward(MyName);
              return 1;
            }
            else
            {
              player->display("任务系统中的房间没有找到请联系巫师.");
            }
            //givenpc->gotoRoom(g_Settings->getNPCDeadRoom());//getAsString("NPC死亡房间"));
         }
         else if(givenpc->isTypeOf("YPlayer")) //玩家的被给
         {
            player->giveChildTo(givenpc,getRoom());
            player->display("你的任务不是找到"+questTarget+"并把他交给"+MyName);
         }
         else g_applog->write("[YNPC系统中给人程序出错。");
       }
    }
    return 1;
  }
  else if(questType=="买东西")
  {
    if(commandThing!=questTarget)
    {
      player->display(MyName+"说道，这个不是我让你买的东西！");
      return 1;
    }
    else if  (commandThing == questTarget)
    {
       YThing* givething = (YThing*) player->findChildThing(questTarget);
       if (givething)
       {
         if(givething->isTypeOf("YThing"))
         {
              long howmuch=givething->getThingprice();
              //给的加乘
              if (howmuch == 0)//没有价格但是任务里有的物品
              {
                 howmuch = getAsLong(questTarget);
                 if (howmuch == 0)
                 {
                   player->display("任务交付"+questTarget+"出错，请联系巫师!");
                 }
              }
              howmuch = howmuch * 2;
              long lThingCount=givething->getCount();  //得到物品重量
              YString unit=givething->getQuantifier();//getAsString("量词");
              if(unit=="") unit="个";
              player->giveChildTo(givething,this);
              if(lThingCount==1){
                player->ActorAddFeatureChange();
                player->ActorAddRecoveryChange();
              }
              long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
              YString priceString=""; //例:一两金子二十两银子五十文铜板
              if((goldnum=howmuch/10000)!=0) priceString=LongToChinese(goldnum)+"两金子";
              if((silvernum=(howmuch-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两银子";
              if((coinnum=howmuch%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
              YThing *objMoney;
              if(goldnum!=0)
              {
                objMoney=(YThing*)player->findChildThing("金子");
                if(!objMoney)
                {
                  objMoney=(YThing*)loadObject("thing/金子");
                  if(!objMoney)
                  {
                        g_err.show("[YPawnRoom::sell]loadObject thing/金子 is NULL");
                        return 1;
                  }
                  player->addChild(objMoney);
                  objMoney->setCount(0);
                }
                objMoney->setCount(objMoney->getCount()+goldnum);
              }
              if(silvernum!=0)
              {
                objMoney=(YThing*)player->findChildThing("银子");
                if(!objMoney)
                {
                  objMoney=(YThing*)loadObject("thing/银子");
                  if(!objMoney)
                  {
                    g_err.show("[YPawnRoom::sell]loadObject thing/银子 is NULL");
                    return 1;
                  }
                  player->addChild(objMoney);
                  objMoney->setCount(0);
                }
                objMoney->setCount(objMoney->getCount()+silvernum);
              }
              if(coinnum!=0)
              {
                objMoney=(YThing*)player->findChildThing("铜板");
                if(!objMoney)
                {
                  objMoney=(YThing*)loadObject("thing/铜板");
                  if(!objMoney)
                  {
                    g_err.show("[YPawnRoom::sell]loadObject thing/铜板 is NULL");
                    return 1;
                  }
                  player->addChild(objMoney);
                  objMoney->setCount(0);
                }
                objMoney->setCount(objMoney->getCount()+coinnum);
              }
              player->display("你得到了"+priceString+"的奖赏。");
         }
         else if(givething->isTypeOf("YPlayer")) //玩家的被给
         {
            player->giveChildTo(givething,getRoom());
            player->display("你的任务不是找到"+questTarget+"并把他交给"+MyName);
         }
         else g_applog->write("[YNPC系统中给物品程序出错。");
       }
       else player->display("你没有这样东西。");
    }
    return 1;
  }
  else if(questType=="杀"){
      long needPate=getNeedPate(); //需要首级
      long needKillInBody=getNeedKillBySelf(); //需亲自杀
      long needShearInBody=getNeedGeBySelf(); //需亲自割
      YString killerName=objThing->getAsString("杀人者");
      YString ShearName=objThing->getAsString("割首级者");
      YString ownerType=objThing->getAsString("拥有者类型");
      if(needPate==0){ //不要首级
        player->display(MyName+"摇摇头说:我不要这个东西。");
        //return 1;
        wrong=1;
      }
      else if((needKillInBody==1)&&(killerName!=player->getActorName())){
        player->display(MyName+"摇摇头说:这不是你杀的。");
        //return 1;
        wrong=1;
      }
      else if((needShearInBody==1)&&(ShearName!=player->getActorName())){
        player->display(MyName+"对你斥道:你从哪里捡来的首级,还想蒙混过关!");
        //return 1;
        wrong=1;
      }
      else if(commandThing!=questTarget+"的首级"){
        player->display(MyName+"摇摇头说:我要的不是这个东西。");
        //return 1;
        wrong=1;
      }
      else if(ownerType!="NPC"){
        player->display(MyName+"对你斥道:这个首级是假的!");
        //return 1;
        wrong=1;
      }
  }
  else{
      player->display(MyName+"疑惑的说：你给我这个干什么？");
      //return 1;
      wrong=1;
  }
  //player->giveChildTo(objThing,this);
  long count=objThing->getCount();
  if(count<1){
    player->display("你没有这种东西。");
    return 1;
  }
  else if(count==1){
    if(player->removeChild(objThing)) delete objThing;
  }
  else{
    objThing->setCount(count-1);
  }
  player->resumWeight();
  player-> ActorAddFeatureChange();
  player-> ActorAddRecoveryChange();
  msg="&s把"+commandThing+"递给"+MyName+"。";
  if(wrong == 1) return 1;
  OutputMsg(player,msg);
  msg=getNPCSayWhenEndQuest(); //被完成任务说话
  OutputMsg(player,msg);
  player->getReward(MyName);
  return 1;
}

//------------------------------------------------------------
//XX条件判断
//0   ----  表示成功，条件满足，通过
//1   ----  表示失败，条件不满足，被拒绝
//-1  ----  表示出错
int YNPC::conditionEstimation(YAbstractActor* executor,YString conditionName)
{
  YActor *pActor;
  if(executor->isTypeOf("YActor")) pActor=(YActor*)executor;
  else return -1;   //出错
  
  YString msg;
  YString MyName=getActorName(); //本NPC的名字
  long numCondition=getAsLong(conditionName+"_条件个数");
  for(int i=0;i<numCondition;i++){
     YString strCondition=getAsString(conditionName+"_条件"+LongToChinese(i+1)); //XX_条件N字符串
     YString itemName=strCondition.getWord(); //项目名字(正气值,性别...)
     YString itemType=strCondition.getWord(); //项目类型(数值,字符串...)
     YString itemConnection=strCondition.getWord(); //项目关系(大于,等于...)
     YString itemValue=strCondition.getWord(); //项目值(-100,男...)
     YString itemAnswer=strCondition.getWord(); //项目回答
     if((itemType!="数值")&&(itemType!="字符串"))
     {
        msg=MyName+"对&s说:今天我生病了,你回去吧。";
        OutputMsg(pActor,msg);
        g_err.show("[YNPC::conditionEstimation]"+MyName+"_"+conditionName+"条件_项目类型_出错");
        return -1;    //出错
     }
     long bOut=pActor->getAsLong("信息屏蔽"); //是否允许OutputMsg
     if(itemType=="数值"){
        if((itemConnection!="大于")&&(itemConnection!="等于")&&(itemConnection!="小于"))
        {
          msg=MyName+"对&s说:今天我生病了,你回去吧。";
          OutputMsg(pActor,msg);
          g_err.show("[YNPC::conditionEstimation]"+MyName+"_"+conditionName+"条件_项目关系_出错");
          return -1;   //出错
        }
        long itemLongValue;
        if (itemName == "经验")
        {
          itemLongValue=pActor->getExperience(); //项目长整型值
        }
        else if (itemName == "正气值")
        {
          itemLongValue=pActor->getGoodnessCount(); //项目长整型值
        }
        else
        {
          pActor->onBeforeSave();
          itemLongValue=pActor->getAsLong(itemName); //项目长整型值
        }
        if(((itemConnection=="大于")&&(itemLongValue<=itemValue.toLong()))|| //条件不满足,则拒绝
           ((itemConnection=="等于")&&(itemLongValue!=itemValue.toLong()))||
           ((itemConnection=="小于")&&(itemLongValue>=itemValue.toLong())))
        {
          if(bOut == 1) pActor->displayEx(itemAnswer);
          else OutputMsg(pActor,itemAnswer); //给pActor的回答,拒绝
          return 1;   //条件不满足
        }
     }
     else if(itemType=="字符串"){
        if((itemConnection!="等于")&&(itemConnection!="不等于"))
        {
          msg=MyName+"对&s说:今天我生病了,你回去吧。";
          OutputMsg(pActor,msg);
          g_err.show("[YNPC::conditionEstimation]"+MyName+"_"+conditionName+"条件_项目关系_出错");
          return -1;   //出错
        }
        YString itemStringValue;
        if (itemName == "门派")
        {
          itemStringValue=pActor->getSchool(); //项目字符串值
        }
        else if (itemName == "性别")
        {
          itemStringValue=pActor->getSexString(); //项目字符串值
        }
        else
        {
           pActor->onBeforeSave();
           itemStringValue=pActor->getAsString(itemName); //项目字符串值
        }
        if(((itemConnection=="不等于")&&(itemStringValue==itemValue))|| //条件不满足,则拒绝
           ((itemConnection=="等于")&&(itemStringValue!=itemValue)))
        {
          if(bOut == 1) pActor->displayEx(itemAnswer);
          else OutputMsg(pActor,itemAnswer); //给pActor的回答,拒绝
          return 1;   //条件不满足
        }
     }
  }
  return 0;   //条件满足
}
//----------------------------------------------------------------
//联合协防
int YNPC::fnUniteKill(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  if(getUniteKill() != 1){  //getAsLong("联合协防")
    g_err.show("[YNPC::fnUniteKill]"+getActorName()+"_联合协防_出错_错误号=0001");
    return 1;   //本NPC并没有联合协防的属性，却错误的传递给了他kill命令。
  }

  YString sNPCName=command.getWord(); //player要杀的NPC名字
  YAbstractActor *pAbstractActor=getRoom()->findChildActor(sNPCName);
  if(!pAbstractActor){
    g_err.show("[YNPC::fnUniteKill]"+sNPCName+"_不在当前房间_出错_错误号=0002");
    return 1;   //要杀的人不在当前房间，却通过了YActor的kill函数的检测。
  }
  YNPC *pNPC;
  if(pAbstractActor->isTypeOf("YNPC")){ //暂时只作NPC的处理
    pNPC=(YNPC*)pAbstractActor;
  }
  else{
    g_err.show("[YNPC::fnUniteKill]"+sNPCName+"_不是NPC_出错_错误号=0003");
    return 1;   //要杀的人不是NPC，却错误的触发了联合协防。
  }

  if(getStatus() == "晕倒中"){ //状态不为空，说明本NPC有事
    return 1;
  }
  if(conditionEstimation(pNPC,"联合协防") == 1){ //条件不满足，已说话。将杀人。
    //YString sMessage=getAsString("联合协防对象_"+sNPCName);
    //if(sMessage == "") sMessage=getActorName()+"对你喝道：我杀了你！";
    //player->display("<font color=red>"+sMessage+"</font>");  //显示红色的本NPC说话
    YString sPlayerName=player->getActorName();   //player的名字
    NPCKill(sPlayerName);    //杀人
  }
  return 1;
}
//----------------------------------
//NPC主动杀人(赋值"杀死人物列表")
int YNPC::NPCKill(YString name)
{
  YAbstractActor* obj=getRoom()->findChildActor(name);
  if(!obj) return 1; //当前房间没有找到，返回不处理
  YActor* objActor;
  if(obj->isTypeOf("YActor")){
    objActor=(YActor*)obj;
  }
  else return 1; //类型不符，返回不处理
  
  YString sMyName=getActorName(); //本NPC的名字

  //设置"房间内敌人列表"和"杀死人物列表"
  
  YString sMyAllEnemyList;   //杀死人物列表
  
  sMyAllEnemyList=getAllEnemyList(); //自己的"杀死人物列表"

  if(!findStringInStr(sMyAllEnemyList,name)){     //如果在"杀死人物列表"里面没有找到对方的名字
      setSameRoomEnemyList(name+" "+getSameRoomEnemyList());
      setAllEnemyList(name+" "+getAllEnemyList());                  		//自己
      objActor->setSameRoomEnemyList(sMyName+" "+objActor->getSameRoomEnemyList());
      objActor->setAllEnemyList(sMyName+" "+objActor->getAllEnemyList());   	//对方
  }
  objActor->setStatus("战斗中");
  setStatus("战斗中");
  return 1;
}
