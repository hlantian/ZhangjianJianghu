//---------------------------------------------------------------------------
//
// ydestroything.cpp    2001年2月6日
//
// 类YDestroyThing：可销毁的物品
//
// 作者：叶林 张勇 刘鹏  单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YDestroyThing::YDestroyThing(YString initFileName):YThing(initFileName)
{
  if(getAsLong("销毁时间间隔")>0){
    set("销毁时间",getAsLong("销毁时间间隔"));
  }
  this->setSmallTime(180000); //3分钟
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YDestroyThing::onTimer(void)
{
  YThing::onTimer(); //首先调用父类的处理函数

 //if(getAsLong("销毁时间间隔")>0){ //表示这是可以销毁的物品
    long destroyTime=getAsLong("销毁时间");
    if(destroyTime>=0){
      set("销毁时间",destroyTime-getSmallTime());
    }
    else addToDestroyList();
  //}
  return 1;
}
//---------------------------------------
//添加到父物体的销毁列表
int YDestroyThing::addToDestroyList(void)
{
  YMUDObject *obj=getOwner();
  if(!obj){
    g_err.show("[YDestroyThing::addToDestroyList]NULL Owner.");
    return 1;
  }
  YString destroyList;
  if(obj->isTypeOf("YRoom"))
  {
    destroyList=((YRoom*)obj)->getDestroyList();//getAsString("销毁列表");
  }
  else if (obj->isTypeOf("YActor"))
  {
    destroyList=((YActor*)obj)->getDestroyList();//getAsString("销毁列表");
  }
  else
  {
    YString errstr="[YDestroyThing::addToDestroyList]type 不对.(name="+getObjectName()+
        "Owner="+obj->getObjectName()+"Class="+obj->getRuntimeClass()+")";
    g_err.show(errstr);
   return 1;
  }
  YString tempString;
  YString findString=destroyList; //要查找的字符串
  YString thingName=getThingName();//getAsString("名字");
  while((tempString=findString.getWord())!=""){
    if(tempString==thingName){ //说明已经设置
      return 1;
    }
  }
  if(destroyList==""){
    if(obj->isTypeOf("YRoom"))
    {
      ((YRoom*)obj)->setDestroyList(thingName);//set("销毁列表",thingName);
    }
    else if (obj->isTypeOf("YActor"))
    {
      ((YActor*)obj)->setDestroyList(thingName);//set("销毁列表",thingName);
    }
  }
  else{
    if(obj->isTypeOf("YRoom"))
    {
      ((YRoom*)obj)->setDestroyList(destroyList+" "+thingName);//set("销毁列表",destroyList+" "+thingName);
    }
    else if (obj->isTypeOf("YActor"))
    {
      ((YActor*)obj)->setDestroyList(destroyList+" "+thingName);//set("销毁列表",destroyList+" "+thingName);
    }
  }
  return 1;
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YDestroyThing::isTypeOf(YString className)
{
  if(className=="YDestroyThing") return 1;
  else return YThing::isTypeOf(className);
}
//--------------------------------------------------------
//作为中介物体执行命令，已处理返回1，未处理返回0
int YDestroyThing::executeCommand(YAbstractActor* executor, YString command)
{
  return 0;
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YDestroyThing::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  return 0;
}

 
