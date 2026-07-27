//---------------------------------------------------------------------------
//
// yabstractactor.cpp    2000年6月12日
//
// 类YAbstractActor：提供抽象的人物特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YAbstractActor::isTypeOf(YString className)
{
  if(className=="YAbstractActor") return 1;
  else return YMUDObject::isTypeOf(className);
}
//--------------------------------------------------------
//构造函数
YAbstractActor::YAbstractActor(YString initFileName)
  : YMUDObject(initFileName),m_Room((YAbstractRoom*)g_GrandpaRoom)
{
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YAbstractActor::getDisplayName(void)
{
  YString name=getObjectName();//getAsString("名字");
  return "<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+name+"\")>"+name+"</span>";
}
//--------------------------------------------------------
//设置Room
void YAbstractActor::setRoom(YAbstractRoom* newRoom)
{
  m_Room=newRoom;
  set("room_name",m_Room->getDataFileName());
}
//--------------------------------------------------------
//设置Room
void YAbstractActor::setRoom(YString roomName)
{
  YAbstractRoom* room=g_Map->getRoom(roomName, getRoom());
  if(room) setRoom(room);
}
//--------------------------------------------------------
//事件Message的默认处理函数
int YAbstractActor::onMessage(YAbstractActor* speaker, YString message)
{
  return 1;
}
//--------------------------------------------------------
//事件RoommateEnter的默认处理函数
int YAbstractActor::onRoommateEnter(YMUDObject* sender, YAbstractActor* actor)
{
  return 1;
}
//--------------------------------------------------------
//事件RoommateLeave的默认处理函数
int YAbstractActor::onRoommateLeave(YMUDObject* sender, YAbstractActor* actor)
{
  return 1;
}
//--------------------------------------------------------
//接收一条消息
void YAbstractActor::message(YAbstractActor* speaker, YString msg, bool newline,
                            msg_type messagetype, const YString& name)
{
  onMessage(speaker, msg);
}
//--------------------------------------------------------
//方法reload--重新从文件中读取属性
int YAbstractActor::reload(void)
{
  int retVal=YMUDObject::reload();
  setRoom(getRoom());
  return retVal;
}

