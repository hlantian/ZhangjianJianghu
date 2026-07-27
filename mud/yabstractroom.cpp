//---------------------------------------------------------------------------
//
// yabstractroom.cpp    2000年6月12日
//
// 类YAbstractRoom：提供抽象的Room(Player活动场所的基本单位)特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YAbstractRoom::isTypeOf(YString className)
{
  if(className=="YAbstractRoom") return 1;
  else return YMUDObject::isTypeOf(className);
}


//--------------------------------------------------------
//构造函数
YAbstractRoom::YAbstractRoom(YString initFileName)
  : YMUDObject(initFileName)
   ,m_RoomDescribe("")
{
  m_RoomChat=new YChat;
}

//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YAbstractRoom::onAfterLoad(void)
{
  int retVal=YMUDObject::onAfterLoad();
  setRoomDescribe(getAsString("描述"));
  return retVal;

}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YAbstractRoom::onBeforeSave(void)
{
  int retVal=YMUDObject::onBeforeSave();
  set("描述",getRoomDescribe());
  return retVal;
}
//----------------------------------------------------------------
//事件Init的默认处理函数
int YAbstractRoom::onInit(void)
{
  YMUDObject::onInit();

  //设置每一个Actor的room属性
  YObjectGroup::obj_iter it=getChildren()->begin();
  while(it!=getChildren()->end()) {
    if((*it)->isTypeOf("YAbstractActor"))
      ((YAbstractActor*)(*it))->setRoom(this);
    it++;
  }

	return 1; //必须返回1，表示处理结束
}
//--------------------------------------------------------
//事件onBeforeEnter的默认处理函数
int YAbstractRoom::onBeforeEnter(YMUDObject* sender, YAbstractActor* actor)
{
  return 1;
}
//--------------------------------------------------------
//事件onAfterEnter的默认处理函数
int YAbstractRoom::onAfterEnter(YMUDObject* sender, YAbstractActor* actor)
{
  if(m_RoomChat)  m_RoomChat->subscribe(actor);
  else  YErr::show("[YAbstractRoom::onAfterEnter]m_RoomChat is NULL.");

  //派遣onRoommateEnter 事件给每一个Actor
  YObjectGroup::obj_iter it=getChildren()->begin();
  while(it!=getChildren()->end()) {
    if(*it) {
      if(((*it)!=actor)&&((*it)->isTypeOf("YAbstractActor")))
        ((YAbstractActor*)(*it))->onRoommateEnter(sender, actor);
    }
    else  YErr::show("[YAbstractRoom::onAfterEnter]Child is NULL.");
    it++;
  }
  return 1;
}
//--------------------------------------------------------
//事件onBeforeLeave的默认处理函数
int YAbstractRoom::onBeforeLeave(YMUDObject* sender, YAbstractActor* actor)
{
  return 1;
}
//--------------------------------------------------------
//事件onAfterLeave的默认处理函数
int YAbstractRoom::onAfterLeave(YMUDObject* sender, YAbstractActor* actor)
{
  m_RoomChat->unsubscribe(actor);
  YObjectGroup::obj_iter it=getChildren()->begin();
  while(it!=getChildren()->end()) {
    if(((*it)!=actor)&&((*it)->isTypeOf("YAbstractActor")))
      ((YAbstractActor*)(*it))->onRoommateLeave(sender, actor);
    it++;
  }
  return 1;
}
//----------------------------------------------------------------
//事件BeforeChildAdd的默认处理函数
int YAbstractRoom::onBeforeChildAdd(YMUDObject* sender, YMUDObject* child)
{
  if(!child) {
    g_err.show("[YAbstractRoom::onBeforeChildAdd]child is NULL.");
    return 0;
  }
  int retVal;
  retVal=YMUDObject::onBeforeChildAdd(sender, child);
  if(retVal==0) return retVal;
  if(child->isTypeOf("YAbstractActor")) retVal=retVal && onBeforeEnter(sender, (YAbstractActor*)child);
	return retVal;
}
//----------------------------------------------------------------
//事件AfterChildAdd的默认处理函数
int YAbstractRoom::onAfterChildAdd(YMUDObject* sender, YMUDObject* child)
{
  int retVal;
  retVal=YMUDObject::onAfterChildAdd(sender, child);
  if(child->isTypeOf("YAbstractActor")) {
    ((YAbstractActor*)child)->setRoom(this);
    retVal=retVal && onAfterEnter(sender, (YAbstractActor*)child);
  }
	return retVal;
}
//----------------------------------------------------------------
//事件BeforeChildRemove的默认处理函数
int YAbstractRoom::onBeforeChildRemove(YMUDObject* sender, YMUDObject* child)
{
  int retVal;
  retVal=YMUDObject::onBeforeChildRemove(sender, child);
  if(child->isTypeOf("YAbstractActor")) retVal=retVal && onBeforeLeave(sender, (YAbstractActor*)child);
	return retVal;
}
//----------------------------------------------------------------
//事件AfterChildRemove的默认处理函数
int YAbstractRoom::onAfterChildRemove(YMUDObject* sender, YMUDObject* child)
{
  int retVal;
  retVal=YMUDObject::onAfterChildRemove(sender, child);
  if(child->isTypeOf("YAbstractActor")) retVal=retVal && onAfterLeave(sender, (YAbstractActor*)child);
	return retVal;
}
//--------------------------------------------------------
//将一角色移动到另一房间(0-成功，2-该场所无法装载，3-房间不允许出/入)
int YAbstractRoom::sendActorToRoom(YAbstractActor* actor, YString roomName)
{
   YAbstractRoom* targetRoom=g_Map->getRoom(roomName, this);
   if(!targetRoom) return 2; //该场所无法装载

   if(giveChildTo(actor,targetRoom)) {
     return 0; //成功
   }
   else return 3;
}
