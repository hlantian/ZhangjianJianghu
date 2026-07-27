//---------------------------------------------------------------------------
//
// yroom.cpp    2000年6月12日
//
// 类YRoom：房间/地点
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YRoom::YRoom(YString initFileName):YAbstractRoom(initFileName),
                                    m_UpdateTime(0),
                                    m_DestroyList(""),
                                    //m_RoomName(""),
                                    m_ThingList(""),
                                    m_NPCList(""),
                                    m_UpdateTimeInterval(0),
                                    m_ForbidFight(0),
                                    m_BossName(""),
                                    m_FoodConsume(0)
{
  setUpdateTime(0); //刷新时间
  setUpdateTimeInterval(g_Settings->getsitRefurbishTimeSkip());//getAsLong("刷新时间间隔")); //刷新时间间隔
  this->setSmallTime(2000);
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YRoom::isTypeOf(YString className)
{
  if(className=="YRoom") return 1;
  else return YAbstractRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YRoom::onAfterLoad(void)
{
  int retVal=YAbstractRoom::onAfterLoad();
  
  setUpdateTime(getAsLong("刷新时间"));
  setDestroyList(getAsString("销毁列表"));
//  setRoomName(getAsString("名字"));
  setThingList(getAsString("物品列表"));
  setNPCList(getAsString("NPC列表"));
  setUpdateTimeInterval(getAsLong("刷新时间间隔"));
  setForbidFight(getAsLong("禁止战斗"));
  setBossName(getAsString("老板名字"));
  setFoodConsume(getAsLong("饮食消耗"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YRoom::onBeforeSave(void)
{
  int retVal=YAbstractRoom::onBeforeSave();
  
  set("刷新时间",getUpdateTime());
  set("销毁列表",getDestroyList());
//  set("名字",getRoomName());
  set("物品列表",getThingList());
  set("NPC列表",getNPCList());
  set("刷新时间间隔",getUpdateTimeInterval());
  set("禁止战斗",getForbidFight());
  set("老板名字",getBossName());
  set("饮食消耗",getFoodConsume());

  return retVal;
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YRoom::getDisplayName(void)
{
  YString name=getRoomName(); //名字
  return "<font color="+g_Settings->getRoomNameColor()
          +"><a href='javascript:room(\""+name+"\")'>"+name+"</a></font>";
}
//----------------------------------------------------------
//把东西给Actor时要计算负重
bool YRoom::giveChildTo(YMUDObject* child, YMUDObject* another, long count, long No)
{
  if(YMUDObject::giveChildTo(child,another, count, No)) {
    if (another->isTypeOf("YActor"))
    {
     ((YActor*)another)->resumWeight();
    }
    return true;
  }
  return false;
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YRoom::onTimer(void)
{
  YAbstractRoom::onTimer(); //首先调用父类的处理函数

  long updateTime=getUpdateTime(); //刷新时间
  if(updateTime>=0){
    updateTime-=getSmallTime();
    setUpdateTime(updateTime); //set("刷新时间",updateTime);
  }
  else
  {
    letsUpdate();
    setUpdateTime(900000);//15分钟
  }
  playerquit(); //玩家退出的处理
  if(getDestroyList()!="") letsDestroy(); //销毁列表
  return 1;
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YRoom::executeCommand(YAbstractActor* executor, YString command)
{
  //处理睡眠
  if((executor->isTypeOf("YPlayer"))&& (((YActor*)executor)->getStatus() == "睡眠中")) { //还在睡
    executor->display("Zzzzzzzzzzz......");
    return 1;
  }

  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="quit") retVal=quit(executor);
  else if(commandVerb=="cunquit") retVal=cunquit(executor,cmd);
  else {
    //do nothing
  }

  return retVal;
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YRoom::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  return 0;
}
//--------------------------------------------------------
//事件onBeforeEnter的默认处理函数
int YRoom::onBeforeEnter(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=YAbstractRoom::onBeforeEnter(sender, actor);
  if(retVal) {
    //getRoomChat()->talk(NULL,actor->getAsString("名字")+"来到这里。");
    YString s="addActor(\""+((YActor*)actor)->getActorName(); //名字
    s+="\","+(YString)(actor->getX());
    s+=","+(YString)(actor->getY());
    s+=","+actor->getIcon();
    s+=");";
    getRoomChat()->talk(NULL,s,NULL,NULL,JAVASCRIPT_MSG,"");
    return retVal;
  }
  else return retVal;
}
//--------------------------------------------------------
//事件onAfterEnter的默认处理函数
int YRoom::onAfterEnter(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=1;
  YActor* objActor;
  if(actor->isTypeOf("YActor")){
    objActor=(YActor*)actor;
  }
  else return 1;
  if(actor->isTypeOf("YPlayer")) ((YPlayer*)actor)->look_b();
  YAbstractRoom::onAfterEnter(sender, actor);

  if(actor->isTypeOf("YPlayer")){
    long consume=getFoodConsume(); //在沙漠等特殊地点的食物,饮水有较大的消耗，饮食消耗
    long food,water; //食物,饮水
    if(consume>0){
      YPlayer* tempplayer = (YPlayer*)actor;
      food=tempplayer->getFood()-consume;
      water=tempplayer->getDrink()-consume;
      if(food<0) food=0;
      if(water<0) water=0;
      tempplayer->setFood(food);
      tempplayer->setDrink(water);
    }
  }
  //处理看是不是在对杀状态
  YString killname=objActor->getAllEnemyList(); //杀死人物列表
  YString name; //"sb."
  while ((name=killname.getWord()) != "")
  {
        YActor* sbkill=(YActor*)findChildActor(name);
        if (sbkill)//判断对杀人物的使用
        {
                  actor->display("<font color=red>>你大叫道:"+sbkill->getActorName()+"我们的帐还没有算完呢！！</font>");
                  sbkill->display ("<font color=red >你大叫道:"+objActor->getActorName()+"别跑我们的帐还没有算完呢！！</font>");
                  YString msg = actor->getDisplayName()+"冲这"+sbkill->getDisplayName()+"大叫道：别跑我们的帐还没有算完呢！";
                  getRoomChat()->talk(NULL, msg, sbkill,actor);
                  objActor->setSameRoomEnemyList(name+" "+objActor->getSameRoomEnemyList());
                  sbkill->setSameRoomEnemyList(objActor->getActorName()+" "+sbkill->getSameRoomEnemyList());
                  objActor->setStatus("战斗中");
                  sbkill->setStatus("战斗中");
        }                                                  
  }
  return retVal;
}
//--------------------------------------------------------
//事件onAfterLeave的默认处理函数
int YRoom::onAfterLeave(YMUDObject* sender, YAbstractActor* actor)
{
  YAbstractRoom::onAfterLeave(sender, actor);
  ((YActor*)actor)->setSameRoomEnemyList(""); //房间内敌人列表
  //getRoomChat()->talk(NULL,actor->getAsString("名字")+"离开了这里。");
  YString s="delActor(\""+((YActor*)actor)->getActorName()+"\");";
  getRoomChat()->talk(NULL,s,actor,NULL,JAVASCRIPT_MSG,"");
  return 1;
}
//--------------------------------------------------------
//显示房间里的人员列表
int YRoom::showActors(YActor* receiver)
{
  YString actorList=enumChildrenActor();
  YString name;
  receiver->display("clearActor()",false,JAVASCRIPT_MSG,"");
  receiver->display("setself(\""+receiver->getActorName()+"\")",false,JAVASCRIPT_MSG,"");
  YActor* actor;
  YString iconNo="0";
  YString s;
  while((name=actorList.getWord())!="")
  {
    actor=(YActor*)findChildActor(name);
    if(!actor) continue;
    s="addActor(\"";
    s+=actor->getActorName()+"\",";
    s+=(YString)(actor->getX())+",";
    s+=(YString)(actor->getY())+",";
    s+=actor->getIcon();;
    s+=")";
  	receiver->display(s,false,JAVASCRIPT_MSG,"");
  }

  actorList=enumChildrenActorForDisplay();
  receiver->display(actorList);
  return 1;
}
//--------------------------------------------------------
//显示房间里的人员列表(带绰号)
int YRoom::showNickActors(YActor* receiver)
{
  YString actorList=enumChildrenActor();
  YString actordisplay;
  YString name;
  YString s="clearActor();\n";
  s+="setself(\""+receiver->getActorName()+"\");\n";
  YActor* actor;
  while((name=actorList.getWord())!="")
  {
    actor=(YActor*)findChildActor(name);
    if(!actor) continue;
    s+="addActor(\"";
    //YString temptest = actor->getActorName();
    //        temptest = actor->getAsString("名字");
    s+=actor->getActorName()+"\",";
    s+=(YString)(actor->getX())+",";
    s+=(YString)(actor->getY())+",";
    s+=actor->getIcon();
    s+=");\n";
    if (actordisplay != "") actordisplay=actordisplay+"<br>"+(actor->getNickName())+" ";
    else  actordisplay=actordisplay+(actor->getNickName())+" ";
  }
  receiver->display(s,false,JAVASCRIPT_MSG,"");
  receiver->display(actordisplay);
  return 1;
}
//--------------------------------------------------------
//显示房间里的物体列表
int YRoom::showThings(YActor* receiver)
{
  YString thingsList=enumChildrenThingForDisplay();
  if (thingsList != "" ) receiver->display(thingsList);
  return 1;
}
//--------------------------------------------------------
//将一角色移动到另一房间(0-成功，1-该方向无出口，2-该场所无法装载)
int YRoom::sendActorTo(YActor* actor, YString direction)
{
  YString targetRoomName=getAsString(direction);
  if(targetRoomName=="") return 1; //该方向无出口
  else return sendActorToRoom(actor,targetRoomName);
}
//--------------------------------------------------------
//玩家退出MUD
int YRoom::quit(YAbstractActor* player)
{
  YString playerName=((YActor*)player)->getActorName(); //名字
  g_InfoChat->talk(NULL,playerName+"已经退出了仗剑江湖.",player);

  player->getRoom()->removeChild(player);

  if(player->isTypeOf("YPlayer")) {
    ((YPlayer*)player)->quit();
    ((YPlayer*)player)->display("window.close()",false,JAVASCRIPT_MSG);
    YString sessionID=((YPlayer*)player)->getSession()->getID();
    g_SessionManager->endSession(sessionID);
  }
  else delete player;
  return 1;
}

//玩家保存任务退出MUD
int YRoom::cunquit(YAbstractActor* player,YString command)
{
  if(player->isTypeOf("YPlayer")) {
     YString cmd=command;
     long ml = ((YPlayer*)player)->cunquit(cmd);
     if (ml == 1) return 1;
     YString playerName=((YActor*)player)->getActorName(); //名字
     g_InfoChat->talk(NULL,playerName+"已经退出了仗剑江湖.",player);

     player->getRoom()->removeChild(player);
    ((YPlayer*)player)->display("window.close()",false,JAVASCRIPT_MSG);
    YString sessionID=((YPlayer*)player)->getSession()->getID();
    g_SessionManager->endSession(sessionID);
  }
  else delete player;
  return 1;
}
//--------------------------------------------
//刷新物品及NPC
int YRoom::letsUpdate(void)
{
  //销毁原先在房间内的物品
  YString theoldthing = enumChildrenThing();
  if ( theoldthing != "")
  {
      YString oldtempthing = "";
      while ((oldtempthing = theoldthing.getWord()) != "")
      {
        YAbstractThing* oldthing = findChildThing(oldtempthing);
        if (oldthing)
        {
          if(removeChild(oldthing))
          {
            delete oldthing;
          }
          else YErr::show("房间刷新物品删除失败。");
        }
        else continue ;
      }
  }
  //原先的程序
  YString ss=getRoomName(); //房间名字
  YString thingList=getThingList(); //物品列表
  if(thingList!=""){
    YString theThing;
    YAbstractThing *objThing;
    while((theThing=thingList.getWord())!=""){
      objThing=findChildThing(theThing);
      if(!objThing){
        objThing=(YAbstractThing*)loadObject("thing/"+theThing);
        if(!objThing){
          g_err.show("[YRoom::letsUpdate]loadObject"+theThing+" is NULL");
          continue;
        }
        objThing->setCount(1);
        this->addChild(objThing);
      }
    }
  }
  YString NPCList=getNPCList(); //NPC列表
  if(NPCList!="")
  {
    YString theNPC;
    YActor *objNPC;
    while((theNPC=NPCList.getWord())!="")
    {
      objNPC=(YActor*)findChildActor(theNPC);
      if(!objNPC)
      {
        objNPC=g_PlayerManager->getNPC(theNPC);
        if(!objNPC) //全局为空
        {
          objNPC=(YActor*)loadObject("npc/"+theNPC);
          if(!objNPC)
          {
            g_err.show("[YRoom::letsUpdate]loadObject"+theNPC+" is NULL");
            continue;
          }
          this->addChild(objNPC);
        }
        else{
          YString str=this->getDataFileName();
          objNPC->gotoRoom("/"+str);
        }
      }
      if ((objNPC->getStatus())!="战斗中")objNPC->reload();
    }
  }
  setUpdateTime(getUpdateTimeInterval()); //刷新时间复位
  return 1;
}

//--------------------------------------------
//销毁子物品
int YRoom::letsDestroy(void)
{
  YString destroyList=getDestroyList(); //销毁列表
  YString theThing;
  YAbstractThing* tempthing;
  YDestroyThing* objThing;
  while((theThing=destroyList.getWord())!="")
  {
    tempthing = findChildThing(theThing) ;
    if(!tempthing)
    {
      g_err.show("[YRoom::letsDestroy] "+theThing+"指针为空(room="+getRoomName()+")");
      continue;
    }
    if (tempthing->isTypeOf("YDestroyThing"))
    {
      objThing=(YDestroyThing*)tempthing;
      if(removeChild(objThing))
      {
        delete objThing;
      }
      else g_err.show("[YRoom::letsDestroy] "+theThing+"remchild出错！");
    }
    else g_err.show("[YRoom::letsDestroy] "+theThing+"不是YDestroyThing");
  }
  setDestroyList("");
  return 1;
}
//--------------------------------------------
//玩家退出
int YRoom::playerquit(void)
{
  YString allName = getPlayListQuit();//enumChildrenActor();
  if (allName == "")return 1;
  else
  {
    YString name ;
    while ((name=allName.getWord())!="")
    {
      YActor* sb=(YActor*)findChildActor(name);
      if (sb)//找到人物后去查找是否退出
      {
        if ((sb->getStatus()) == "掉线中" )//确认退出
        {
           sb-> setStatus(""); //状态
           sb->display("你已经退出了《仗剑江湖》。");
           quit(sb);
        }
      }
    }//查找人物
  }
  setPlayListQuit("");
  return 1;
}



