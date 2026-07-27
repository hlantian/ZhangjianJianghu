//---------------------------------------------------------------------------
//
// ycookroom.cpp    2000年8月4日
//
// 类YCookRoom：厨房
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YCookRoom::YCookRoom(YString initFileName):YRoom(initFileName),m_ForbidTakeOut(0),
                                                              m_OfferFoodList("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YCookRoom::isTypeOf(YString className)
{
  if(className=="YCookRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YCookRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setForbidTakeOut(getAsLong("禁止带出"));
  setOfferFoodList(getAsString("提供食物"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YCookRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("禁止带出",getForbidTakeOut());
  set("提供食物",getOfferFoodList());
  
  return retVal;
}

//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YCookRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="serve") retVal=serve(executor);
  //else if(commandVerb=="go") retVal=go(cmd.getWord());
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}

//zhy于9月15日修改
//--------------------------------------------------------
//事件onBeforeLeave的默认处理函数
int YCookRoom::onBeforeLeave(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=YRoom::onBeforeLeave(sender,actor);
  if(retVal) {
    if(getForbidTakeOut()==1){ //禁止带出
      YString bossName=getBossName(); //老板名字
      YAbstractActor *tempActor=findChildActor(bossName); //老板的指针
      if(!tempActor) return 1;
      YString foodList=getOfferFoodList(); //所提供食物的列表
      YString theFood;
      YMUDObject *objThing; //食物的指针
      while((theFood=foodList.getWord())!=""){
        objThing=actor->findChild(theFood);
        if(!objThing) continue;
        actor->display(bossName+"说道:"+theFood+"不能带出厨房。");
        return 0;
      }
    }
    return 1;
  }
  else
    return retVal;
}
//--------------------------------------------------------
//要食物和水
int YCookRoom::serve(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString bossName=getBossName(); //老板名字
  YNPC *objActor;
  YAbstractActor *tempActor=findChildActor(bossName); //老板的指针
  if(!tempActor){
     player->display("这儿没有人提供服务。");
     return 1;
  }
  if(tempActor->isTypeOf("YNPC")){
     objActor=(YNPC*)tempActor;
  }
  else{
     player->display("这儿没有人提供服务。");
     return 1;
  }
  YString msg="";
  msg="&s向"+bossName+"要一些吃的。";
  objActor->OutputMsg(player,msg);
  YString foodList=getOfferFoodList(); //提供食物
  YString theFood;
  YAbstractThing *objThing; //食物的指针
  while((theFood=foodList.getWord())!=""){
     objThing=(YAbstractThing*)loadObject("thing/"+theFood);
     player->resumWeight();
     if(!objThing){
        msg=bossName+"对&s说:今天我生病了,你回去吧。";
        objActor->OutputMsg(player,msg);
        g_err.show("[YCookRoom::serve]"+bossName+"_"+theFood+"_出错");
        return 1;
     }
     else if (player->getWeight() >= player->getMaxWeight())
     {
        player->display("你拿的东西太多了。不能再拿别的东西了.");
        return 1;
     }
     //objThing->addOne(objThing->getAsLong("剩余量"));
     objThing->setCount(1);
     objActor->addChild(objThing);
     objActor->giveChildTo(objThing,player);
     msg=bossName+"将"+theFood+"递给&s。";
     objActor->OutputMsg(player,msg);
  }
  msg=bossName+"微笑着对&s说:快吃吧,别饿坏了。";
  objActor->OutputMsg(player,msg);
  player->resumWeight();
  return 1;
}
