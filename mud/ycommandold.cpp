//---------------------------------------------------------------------------
//
// ycommand.cpp    2000年6月12日
//
// 类YCommand：负责命令短语分析及命令别名的处理
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "ycommand.h"
#include "yfifo.h"
#include "global.h"
#include "ything.h"
#include "yerr.h"

//---------------------------------------------------------------
//执行命令
void YCommand::executeCommand(YString sessionID, YString command)
{
  cout<<"[YCommand::executeCommand]"<<sessionID<<"-"<<command<<endl;
  YString targetName, thingName;
  YString commandVerb, arg1, arg2, arg3;
  parse(command, commandVerb, targetName, thingName, arg1, arg2, arg3);
  //确定Session(也就是知道了动作执行者)
  YSession* session=g_SessionManager.getSession(sessionID);
  if(!session) {    //session不存在
    cout<<"[YCommand::executeCommand]session\""<<sessionID<<"\" does not exist in SessionManager."<<endl;
    return;
  }
  //确定Room
  YAbstractRoom* room=session->getPlayer()->getRoom();
  if(!room) {    //room不存在
    cout<<"[YCommand::executeCommand]room of "<<session->getPlayer()->getName()<<"\" does not exist in SessionManager."<<endl;
    //return;
  }
  //确定动作的对象
  YMUDObject* target=room->findChild("名字",targetName); //先在屋子里找
  if(!target) {  //不在屋子里
    target=g_PlayerManager.getActor(targetName); //动作的对象可能是玩家或NPC(Actor)
  }
  if(!target) {  //也不是Actor
    if(room->getAsString("名字")==targetName) { //可能就是Room本身
      target=room;
    }
  }
  if(!target) { //都不是，我也没办法
    //用户命令写错了
  }
  //确定中介物体
  YMUDObject* obj=room->findChild("名字",thingName);
  YThing* thing=NULL;
  if((obj!=NULL)&&(obj->isTypeOf("YThing"))) {
    thing=(YThing*)room->findChild("名字",thingName);
  }
  int retVal=0;
  //先让Room处理命令
  retVal=room->executeCommand(commandVerb, session->getPlayer(), target, room,
                               thing, arg1, arg2, arg3);
  cout<<"[YCommand::executeCommand]"<<"room->executeCommand"<<"-"<<commandVerb<<endl;
  if(!retVal) { //需要后续处理
    //然后让执行者处理
    retVal=session->getPlayer()->executeCommand(commandVerb, session->getPlayer(),
                                       target, room, thing, arg1, arg2, arg3);
  }
  if(!retVal) { //需要后续处理
    //最后让动作对象处理
    retVal=target->executeCommandAsTarget(commandVerb, session->getPlayer(),
                                       target, room, thing, arg1, arg2, arg3);
  }
  //好不容易处理完了
}
//---------------------------------------------------------------
//建立FIFO并开始读取命令,成功返回0
int YCommand::startReading(void)
{
  cout<<"[YCommand]start reading command ..."<<endl;
  m_finish=false; //重置停止标志
  //建立FIFO以读取命令
  m_FIFO=new YFIFO(g_Settings.getCommandFIFOPathName(),"r");
  while(!m_finish) {
    YString s=m_FIFO->read();
    cout<<"[YCommand]get command "<<s<<endl;
    int l=g_Settings.getSessionIDLength();
    executeCommand(YString(s,0,l), YString(s,l,s.size()-l));
  }
  delete m_FIFO;
  return 0;
}
//---------------------------------------------------------------
//停止读取命令（异步）
void YCommand::endReading(void)
{
  m_finish=true;  //设置停止标志，startReading检查到此标志就会返回
}
//---------------------------------------------------------------
//运行线程(继承自Thread)
void YCommand::Run(void)
{
  startReading();
}
