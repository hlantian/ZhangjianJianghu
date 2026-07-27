//---------------------------------------------------------------------------
//
// yteachernpc.cpp    2000年10月16日
//
// 类YTeacherNPC：教基本功的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YTeacherNPC::YTeacherNPC(YString initFileName):YNPC(initFileName),
                                                m_EnterSay(0),
                                                m_CommonSay(""),
                                                m_GiveMoneySay("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YTeacherNPC::isTypeOf(YString className)
{
  if(className=="YTeacherNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YTeacherNPC::onAfterLoad(void)
{
  int retVal=YNPC::onAfterLoad();
  
  setEnterSay(getAsLong("进入时说话"));
  setCommonSay(getAsString("普通说话"));
  setGiveMoneySay(getAsString("缴完学费说话"));
  
  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YTeacherNPC::onBeforeSave(void)
{
  int retVal=YNPC::onBeforeSave();
  
  set("进入时说话",getEnterSay());
  set("普通说话",getCommonSay());
  set("缴完学费说话",getGiveMoneySay());
  
  return retVal;
}

//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YTeacherNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="xue") retVal=beXue(executor,cmd);//被学习
  else if(commandVerb=="give") retVal=beGive(executor,cmd);//别人给东西

  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}
//---------------------------------------------------------
//事件RoommateEnter的默认处理函数
int YTeacherNPC::onRoommateEnter(YMUDObject* sender,YAbstractActor* actor)
{
  YActor::onRoommateEnter(sender,actor); //首先调用父类的处理函数
  
  YPlayer* player;
  if(actor->isTypeOf("YPlayer")) player=(YPlayer*)actor;
  else return 1;
  if(getEnterSay()!=1) return 1; //进入时说话
  YString msg=getCommonSay(); //进入时所说的话，普通说话
  if(msg!="") OutputMsg(player,msg);
  return 1;
}
//--------------------------------------------------------
//被学习
int YTeacherNPC::beXue(YAbstractActor* executor,YString command)
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

  YString allSkills=getAllSkillsList(); //本NPC的所有技能
  int i=allSkills.find(commandSkills,0); //查找本NPC是否会player要学的技能
  if(i==YString::npos){
     msg=getAsString("不会该技能");
     OutputMsg(player,msg);
     return 1;
  }
  if(getAsLong(commandSkills)==0){
     msg=getAsString("不会该技能");
     OutputMsg(player,msg);
     return 1;
  }
  //long Potential=player->getAsLong("潜能"); //player目前的潜能
  long Energy=player->getEnergy(); //player目前的精力
  //学这种武功每次消耗的潜能
  //long PotentialUsed=g_Wugong->wugong_qianneng_used(commandSkills);
  long PotentialUsed=0;//消耗潜能为0
  //学这种武功每次消耗的精力
  long EnergyUsed=g_Wugong->wugong_jingli_used(commandSkills);
  if(EnergyUsed<1) EnergyUsed=1;
  //if(Potential<=PotentialUsed){
     //player->display("你的潜能已经到了极限了.");
     //return 1;
  //}
  if(Energy<=EnergyUsed){
     player->display("你现在精力不足!");
     return 1;
  }
  long Grade=player->getSkillLevel(commandSkills);//getAsLong(commandSkills); //player的武功等级
  long teacherGrade=getAsLong(commandSkills); //本NPC的武功等级
  if(Grade>=teacherGrade){
     player->display("你的["+commandSkills+"]已经不低于"+MyName+"了。");
     return 1;
  }
  //long poCount=Potential/PotentialUsed; //潜能支持的最大次数
  long enCount=Energy/EnergyUsed; //精力支持的最大次数
  //if(count>poCount) count=poCount;
  if(count>enCount) count=enCount;
  long learnTimes=player->getAsLong(MyName+"_可学习次数");
  if(count>learnTimes) count=learnTimes; //学习次数的限制
  if(learnTimes<=0){
     player->display("你必须先缴学费。");
     return 1;
  }
  else{
     learnTimes-=count;
     player->set(MyName+"_可学习次数",learnTimes);
  }
  player->display(MyName+"指导了你一些["+commandSkills+"]的要点。");
  player->display("你似乎有些心得,在心里细细体会.");
  //Potential-=count*PotentialUsed;
  Energy-=count*EnergyUsed;
  //if(Potential<0) Potential=0;
  if(Energy<0) Energy=0;
  //player->set("潜能",Potential-PotentialUsed);
  player->setEnergy(Energy); //精力
  player->display("你学习了"+(YString)count+"次....");
  YString playerAllSkills=player->getAllSkillsList(); //所会技能
  if(playerAllSkills.find(commandSkills,0)==YString::npos){
    if(playerAllSkills=="")
      playerAllSkills=commandSkills;
    else
      playerAllSkills+=" "+commandSkills;
    player->setAllSkillsList(playerAllSkills); //所会技能
  }
  GradeExp=player->getAsLong(commandSkills+"_经验"); //player当前的武功经验
  Savvy=player->getLastLearn(); //后天悟性
  long step=(Savvy-20)*2+20;
  GradeExp+=step*count;
  if(GradeExp>=(Grade+1)*(Grade+1)*10){
    GradeExp=0; //武功经验清0
    player->playerlevelup(commandSkills); //player武功等级提升
  }
  player->set(commandSkills+"_经验",GradeExp);
  return 1;
}
//--------------------------------------------------------
//别人给东西 give (count) sth. to sb.
int YTeacherNPC::beGive(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString MyName=getActorName(); //本NPC的名字
  YString msg;
  YString cmd=command;
  long count;
  YString commandThing=cmd.getWord(); //要给的东西名
  YString commandCount=cmd.getWord(); //物品数量(缺省为1)
  YString command_To; //单词to
  if((commandCount.toLong())>0){
    count=commandCount.toLong();
    command_To=cmd.getWord();
  }
  else{
    count=1;
    command_To=commandCount;
  }
  if(count <= 0){
    player->display(MyName+"眼睛一瞪：你开什么玩笑？");
  }
  else if(count > 200){
    player->display(MyName+"呵呵一笑：我一次收不了这么多钱。");
    return 1;
  }
  YString commandTarget=cmd.getWord(); //给谁
  if((command_To!="to")||(commandTarget!=MyName)){
     player->display("命令格式错误。");
     player->display("正确的格式是:give sth. (count) to sb.");
     player->display("例如:give 金子 1 to 老夫子");
     return 1;
  }
  if(commandThing!="金子"){
     player->display("学费为一两金子。");
     return 1;
  }
  YAbstractThing* objThing=player->findChildThing("金子");
  if(!objThing){
     player->display("你身上没有金子。");
     return 1;
  }
  long yourCount=objThing->getCount(); //player的金子数量
  if(yourCount<count){
     player->display("你的金子数量不够。");
     return 1;
  }
  yourCount-=count; //减去付出的金子数
  if(yourCount==0){
    if(removeChild(objThing)){
      delete objThing;
    }
  }
  else objThing->setCount(yourCount); //设置新数量
  player->resumWeight(); //计算负重
  msg="&s把"+LongToChinese(count)+"两金子递给"+MyName+"。";
  OutputMsg(player,msg);
  msg=getGiveMoneySay(); //"缴完学费说话"
  OutputMsg(player,msg);
  long learnTimes=player->getAsLong(MyName+"_可学习次数");
  learnTimes+=count*5; //一两金子可学习5次
  player->set(MyName+"_可学习次数",learnTimes);
  return 1;
}


