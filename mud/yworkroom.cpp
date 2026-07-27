//---------------------------------------------------------------------------
//
// yworkroom.cpp    2000年9月16日
//
// 类YWorkRoom：做劳动任务的房间(钓鱼,酿蜜...)
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YWorkRoom::YWorkRoom(YString initFileName):YRoom(initFileName),
                                            m_WorkType("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YWorkRoom::isTypeOf(YString className)
{
  if(className=="YWorkRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YWorkRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setWorkType(getAsString("劳动种类"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YWorkRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("劳动种类",getWorkType());
  
  return retVal;
}

//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YWorkRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="ask") retVal=ask(executor,cmd);
  //需要将拼音转换为汉字(如:"diaoyu"转换为"钓鱼")
  if(commandVerb==getWorkType()) retVal=work(executor);
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}

//--------------------------------------------------------
//ask sb. about sth.
int YWorkRoom::ask(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString cmd=command;
  YString commandSomebody=cmd.getWord();
  YString command_about=cmd.getWord();
  YString commandSomething=cmd.getWord();
  if(command_about!="about"){
     player->display("命令格式错误,正确格式是:ask sb. about sth.");
     return 1;
  }
  YString bossName=getBossName(); //老板名字
  //如果不是问房间的主人,则由以后的player和npc程序处理
  if(commandSomebody!=bossName) return 0;
  YNPC *objActor;
  YAbstractActor *tempActor=findChildActor(bossName);
  if(!tempActor){
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if(tempActor->isTypeOf("YNPC")){
     objActor=(YNPC*)tempActor;
  }
  else{
     player->display(bossName+"不在这儿。");
     return 1;
  }
  YString workType=getWorkType(); //劳动种类，比如：钓鱼
  //如果不是关于房间特有的劳动,则由以后的player和npc程序处理
  if(commandSomething!=workType) return 0;
  YString msg;
  msg="&s向"+bossName+"打听有关["+workType+"]的事";
  objActor->OutputMsg(player,msg);
  //1表示已处理完毕,条件不满足,已经回答过了,所以直接返回
  if(objActor->conditionEstimation(player,workType) != 0) return 1; //劳动条件判断
  player->set("劳动",workType); //允许劳动
  msg=bossName+"点点头说:好吧,你就在这里<font color=red>"+workType+"</font>吧。";
  objActor->OutputMsg(player,msg);
  return 1;
}

//--------------------------------------------------------
//劳动(钓鱼,酿蜜...)
int YWorkRoom::work(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString workType=getWorkType(); //劳动种类
  if(player->getExperience()>=1000){
     player->display("按你现在的经验,已经不适合"+workType+"了。");
     return 1;
  }
  if(player->getStatus()!=""){
     player->display("你现在正忙着呢。");
     return 1;
  }
  if(player->getAsString("劳动")!=workType){
     player->display(workType+"需要得到主人的同意。");
     return 1;
  }
  if(player->getNowWork()==1){
     player->display("你不是正在"+workType+"吗?");
     return 1;
  }
  YString msg=getAsString("劳动开始");
  player->OutputMsg(player,msg);
  player->set("劳动计时",5000);
  player->setNowWork(1);//set("正在劳动",1);
  //劳动开始...
  return 1;
}

//--------------------------------------------------------
//事件onBeforeLeave的默认处理函数
int YWorkRoom::onBeforeLeave(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=YRoom::onBeforeLeave(sender,actor);
  if(retVal){
    actor->set("劳动","");
    actor->set("劳动计时",0);
    if (actor->isTypeOf("YPlayer"))
    {
      ((YPlayer*)actor)->setNowWork(0);//set("正在劳动",0);
    }
  }
  return retVal;
}

