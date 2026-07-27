//---------------------------------------------------------------------------
//
// yretiringroom.cpp    2000年8月4日
//
// 类YRetiringRoom：休息室
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YRetiringRoom::YRetiringRoom(YString initFileName):YRoom(initFileName),
                                                  m_RoomSchool(""),
                                                  m_RoomSex("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YRetiringRoom::isTypeOf(YString className)
{
  if(className=="YRetiringRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YRetiringRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setRoomSchool(getAsString("门派"));
  setRoomSex(getAsString("性别"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YRetiringRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("门派",getRoomSchool());
  set("性别",getRoomSex());
  
  return retVal;
}

//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YRetiringRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="sleep") retVal=gosleep(executor);//休息
  //else if(commandVerb=="go") retVal=go(cmd.getWord());
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//休息
int YRetiringRoom::gosleep(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  if(getRoomSchool()!=player->getSchool()) //判断门派
     player->display("只有"+getRoomSchool()+"弟子才能在这里休息。");
  else
  if(getRoomSex()!=player->getSexString())//判断性别
    player->display("你弄错了吧，这里可是"+getRoomSex()+"弟子休息的地方呀。");
  else{
    player->goSleep();//调用YPlayer的休息函数
    //player->display("你休息了。");
  }
  return 1;
}

