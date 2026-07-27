//---------------------------------------------------------------------------
//
// ything.cpp    2000年6月12日
//
// 类YThing：物品
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YThing::YThing(YString initFileName):YAbstractThing(initFileName),m_ThingWeight(0),
								m_Describe(""),
                                                                m_Thingprice(0),
								m_Quantifier("")
{
  this->setSmallTime(0);
  //onAfterLoad();
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YThing::isTypeOf(YString className)
{
  if(className=="YThing") return 1;
  else return YAbstractThing::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YThing::onAfterLoad(void)
{
  int retVal=YAbstractThing::onAfterLoad();
  
//  setThingName(getAsString("名字"));
  setThingFontName(getAsString("显示名字"));
  setThingWeight(getAsLong("重量"));
  setThingprice(getAsLong("价格"));
  setDescribe(getAsString("描述"));
  setQuantifier(getAsString("量词"));


  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YThing::onBeforeSave(void)
{
  int retVal=YAbstractThing::onBeforeSave();
  
//  set("名字",getThingName());
  set("显示名字",getThingFontName());
  set("重量",getThingWeight());
  set("价格",getThingprice());
  set("描述",getDescribe());
  set("量词",getQuantifier());

  return retVal;
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YThing::onTimer(void)
{
  YAbstractThing::onTimer(); //首先调用父类的处理函数

  return 1;
}
//----------------------------------------------------------------
//事件giveChildTo的默认处理函数
bool YThing::giveChildTo(YMUDObject* child, YMUDObject* another, long count, long No)
{
  if (YMUDObject::giveChildTo(child,another, count, No))
  {
    if (another->isTypeOf("YActor"))
    {
     ((YActor*)another)->resumWeight();
    }
    return true ;
  }
  return false;
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YThing::getDisplayName(void)
{
  YString name=getThingName();//getAsString("名字");
  return "<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=thing(\""+name+"\")>"
          +"<font color="+g_Settings->getThingNameColor()+">"+name+"</font></span>";
}
//--------------------------------------------------------
//属性：DisplayNameAndCount(用于显示在页面上的名字，带有颜色和javascript等内容)
//后面加一括弧显示数量
YString YThing::getDisplayNameAndCount(void)
{
  YString name=getThingName();//getAsString("名字");
  return "<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=thing(\""+name+"\")>"
          +"<font color="+g_Settings->getThingNameColor()+">"
          +name+"("+YString(getCount())+getQuantifier()//getAsString("量词")
          +")</font></span>";
}
//--------------------------------------------------------
//作为中介物体执行命令，已处理返回1，未处理返回0
int YThing::executeCommand(YAbstractActor* executor, YString command)
{
  return 0;
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YThing::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  return 0;
}

//----------------------------------------------------
YMUDObject* YThing::clone(void)
{
  YMUDObject* another=YAbstractThing::clone();
  if(!another) return another;
  another -> onAfterLoad();
  another->setObjectName(getObjectName());
  /*setThingName(another->getObjectName());
  setThingFontName(((YThing*)another)->getThingFontName());
  setThingWeight(((YThing*)another)->getThingWeight());
  setDescribe(((YThing*)another)->getDescribe());
  setQuantifier(((YThing*)another)->getQuantifier());*/
  return another;
}


