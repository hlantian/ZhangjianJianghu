//---------------------------------------------------------------------------
//
// yloadroom.cpp    2001年6月6日
//
// 类YLoadRoom：事先Load所有物品的Room
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YLoadRoom::YLoadRoom(YString initFileName):YRoom(initFileName)
{
  disableTimer();
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YLoadRoom::isTypeOf(YString className)
{
  if(className=="YLoadRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YLoadRoom::onTimer(void)
{
  //YRoom::onTimer(); //首先调用父类的处理函数
  setDestroyList(""); //清空销毁列表
  return 1;
}
