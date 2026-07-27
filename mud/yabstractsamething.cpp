//---------------------------------------------------------------------------
//
// yabstractsamething.cpp    2000年8月30日
//
// 类YAbstractSameThing：在MUD中每个这样的物体的属性都完全一样
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YAbstractSameThing::isTypeOf(YString className)
{
  if(className=="YAbstractSameThing") return 1;
  else return YAbstractThing::isTypeOf(className);
}
//--------------------------------------------------------
//构造函数
YAbstractSameThing::YAbstractSameThing(YString initFileName): YAbstractThing(initFileName)
{
  setCount(1);
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YAbstractSameThing::getDisplayName(void)
{
  YString name=getAsString("名字");
  return "<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=thing(\""+name+"\")>"+name+"("+YString(getCount())+")</span>";
}
//--------------------------------------------------------
//读属性Count
long YAbstractSameThing::getCount(void)
{
  return getAsLong("count");
}
//--------------------------------------------------------
//设置Count
void YAbstractSameThing::setCount(long newCount)
{
  set("count",newCount);
}
//--------------------------------------------------------
long YAbstractSameThing::getAsLong(YString name,int No)
{
	if(name==getAsString("变化量名")) return diff_nums[No];
	else return YAbstractThing::getAsLong(name);
}
//--------------------------------------------------------
void YAbstractSameThing::set(YString name, long value, int No)
{
	if(name==getAsString("变化量名")) diff_nums[No]=value;
	else YAbstractThing::set(name, value);
}


