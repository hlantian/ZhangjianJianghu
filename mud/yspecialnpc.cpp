//---------------------------------------------------------------------------
//
// yspecialnpc.cpp    2001年3月19日
//
// 类YSpecialNPC：特殊功能NPC(主动杀人，进入说话，主动行走，循环说话)
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YSpecialNPC::YSpecialNPC(YString initFileName):YNPC(initFileName),
                                                m_WalkTimeInterval(0),
                                                m_WalkTime(0),
                                                m_LoopSpeak(0),
                                                m_KillTimeInterval(0),
                                                m_KillTime(0),
                                                m_SpeakTime(0),
                                                m_WordCount(0),
                                                m_SpeakTimeInterval(0),
                                                m_EnterSay(0),
                                                m_CommonSay(""),
                                                m_EnterKill(0),
                                                m_BeLook(""),
                                                m_KillWhenBeLook(0)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YSpecialNPC::isTypeOf(YString className)
{
  if(className=="YSpecialNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YSpecialNPC::onAfterLoad(void)
{
  int retVal=YNPC::onAfterLoad();
  
  setWalkTimeInterval(getAsLong("行走时间间隔"));
  setWalkTime(getAsLong("行走时间"));
  setLoopSpeak(getAsLong("循环说话"));
  setKillTimeInterval(getAsLong("杀人时间间隔"));
  setKillTime(getAsLong("杀人时间"));
  setSpeakTime(getAsLong("说话时间"));
  setWordCount(getAsLong("话的个数"));
  setSpeakTimeInterval(getAsLong("说话时间间隔"));
  setEnterSay(getAsLong("进入时说话"));
  setCommonSay(getAsString("普通说话"));
  setEnterKill(getAsLong("进入时杀人"));
  setBeLook(getAsString("被看"));
  setKillWhenBeLook(getAsLong("被看杀人"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YSpecialNPC::onBeforeSave(void)
{
  int retVal=YNPC::onBeforeSave();
  
  set("行走时间间隔",getWalkTimeInterval());
  set("行走时间",getWalkTime());
  set("循环说话",getLoopSpeak());
  set("杀人时间间隔",getKillTimeInterval());
  set("杀人时间",getKillTime());
  set("说话时间",getSpeakTime());
  set("话的个数",getWordCount());
  set("说话时间间隔",getSpeakTimeInterval());
  set("进入时说话",getEnterSay());
  set("普通说话",getCommonSay());
  set("进入时杀人",getEnterKill());
  set("被看",getBeLook());
  set("被看杀人",getKillWhenBeLook());
  
  return retVal;
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YSpecialNPC::onTimer(void)
{
  YNPC::onTimer(); //首先调用父类的处理函数

  //自动行走
  if(getWalkTimeInterval()>0){ //行走时间间隔
    long walkTime=getWalkTime(); //行走时间
    if(walkTime>=0){
      setWalkTime(walkTime-getSmallTime()); //set("行走时间",walkTime-getSmallTime());
    }
    else letsAutoWalk();
  }
  
  //循环说话
  if(getLoopSpeak()==1){ //是否循环说话
    loopSpeak();  //循环说话
  }

  //主动杀人
  if((getKillTimeInterval()>0)&&(getStatus()=="")){ //杀人时间间隔>0并且状态为空
    long killTime=getKillTime(); //杀人时间
    if(killTime>=0){
      setKillTime(killTime-getSmallTime()); //set("杀人时间",killTime-getSmallTime());
    }
    else letsInitiativeKill(); //主动杀人
  }
  return 1; //必须返回1，表示处理结束
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YSpecialNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="ask") retVal=beAsk(executor,cmd);//被别人询问
  else if(commandVerb=="look") retVal=beLook(executor,cmd);//被别人看
  
  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}

//---------------------------------------------------------
//事件RoommateEnter的默认处理函数
int YSpecialNPC::onRoommateEnter(YMUDObject* sender,YAbstractActor* actor)
{
  YNPC::onRoommateEnter(sender,actor); //首先调用父类的处理函数
  
  //进入说话
  YPlayer* player;
  if(actor->isTypeOf("YPlayer")) player=(YPlayer*)actor;
  else return 1;
  if(getEnterSay()==1){ //进入时说话
    if(getCommonSay()!=""){ //普通说话
      OutputMsg(player,getCommonSay());
    }
  }
  if(getEnterKill()==1){
    if(conditionEstimation(player,"进入时杀人")==1){
      NPCKill(player->getActorName());
      return 1; //条件不满足,则杀人
    }
  }
  return 1;
}

//--------------------------------------------------------
//被别人看
int YSpecialNPC::beLook(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord();
  YString MyName=getActorName(); //名字
  if(commandTarget!=MyName) return 1;
  YString beLookAnswer=getBeLook(); //被看，被看时说话
  if(beLookAnswer!="") OutputMsg(player,beLookAnswer);
  if(getKillWhenBeLook()==1){ //被看杀人
    if(conditionEstimation(player,"被看杀人")==1){
      NPCKill(player->getActorName());
      return 1; //条件不满足,则杀人
    }
  }
  //1-表示条件不满足,杀   0-表示条件满足,不杀
  return 1;
}
//--------------------------------------------------------
//被别人询问
int YSpecialNPC::beAsk(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord();//被ask的对象
  YString command_About=cmd.getWord();//单词about
  YString commandThing=cmd.getWord();//询问的内容
  //msg给player和其他人不同的消息
  YString msg;
  YString MyName=getActorName(); //名字
  if(commandTarget!=MyName) return 1;
  YString School=player->getSchool(); //player的门派
  YString MySchool=getSchool(); //本NPC的门派
  if(School==MySchool) msg=getAsString("本派弟子问关于_"+commandThing);
  else msg=getAsString("非本派弟子问关于_"+commandThing);
  if(msg=="") msg=MyName+"摇了摇头,对&s说:我不知道。";
  OutputMsg(player,msg);
  return 1;
}
//----------------------------------
//自动行走
int YSpecialNPC::letsAutoWalk(void)
{
  long direction; //行走的方向
  direction=rand()%8+1;
  YRoom* objRoom=(YRoom*)getRoom();
  switch(direction){
    case 1:{objRoom->sendActorTo(this,"东");break;}
    case 2:{objRoom->sendActorTo(this,"西");break;}
    case 3:{objRoom->sendActorTo(this,"南");break;}
    case 4:{objRoom->sendActorTo(this,"北");break;}
    case 5:{objRoom->sendActorTo(this,"东南");break;}
    case 6:{objRoom->sendActorTo(this,"东北");break;}
    case 7:{objRoom->sendActorTo(this,"西南");break;}
    case 8:{objRoom->sendActorTo(this,"西北");break;}
  }
  setWalkTime(getWalkTimeInterval()); //行走时间复位
  return 1;
}
//----------------------------------
//主动杀人
int YSpecialNPC::letsInitiativeKill(void)
{
  setKillTime(getKillTimeInterval()); //杀人时间复位
  YString playerList=getRoom()->enumChildren("","","YPlayer");
  if(playerList!=""){
    YString theMan=playerList.getWord();
    YPlayer* player;
    YAbstractActor* objMan=getRoom()->findChildActor(theMan); //本房间第一个人
    if(!objMan) return 1;
    if(objMan->isTypeOf("YPlayer")){
      player=(YPlayer*)objMan;
    }
    else return 1;
    if(conditionEstimation(player,"定时杀人")==1){
      NPCKill(theMan); //借用进入时杀人的条件
      return 1; //条件不满足,则杀人
    }
  }
  return 1;
}
//----------------------------------
//循环说话
int YSpecialNPC::loopSpeak(void)
{
   long speaktime=getSpeakTime(); //说话时间
   if(speaktime>0){
       speaktime-=getSmallTime();
       setSpeakTime(speaktime);
   }
   else{
       YString msgAll;
       YAbstractRoom* objRoom;
       YChat* objChat;
       long wordnum=getWordCount();//话的个数
       long i;
       i=(long)(rand()%wordnum+1);
       msgAll=getAsString("话"+LongToChinese(i));
       objRoom=getRoom();
       if(!objRoom) return 1;
       objChat=objRoom->getRoomChat();
       if(!objChat) return 1;
       objChat->talk(NULL,msgAll,NULL,NULL);
       setSpeakTime(getSpeakTimeInterval()); //说话时间复位
   }
   return 1;
}

