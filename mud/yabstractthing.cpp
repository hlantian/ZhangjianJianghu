//---------------------------------------------------------------------------
//
// yabstractthing.cpp    2000年6月12日
//
// 类YAbstractThing：提供抽象的物件特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YAbstractThing::isTypeOf(YString className)
{
  if(className=="YAbstractThing") return 1;
  else return YMUDObject::isTypeOf(className);
}
//--------------------------------------------------------
//构造函数
YAbstractThing::YAbstractThing(YString initFileName, long count): YMUDObject(initFileName)
{
  setThingType(getAsLong("thing_type"));
  m_VarientName=getAsLong("变化量名");
  //if((getThingType()==1)&&(getVarientName()=="")) 
                                   //如果没有变化量名则看作same型
  //去掉对SameButOne类型的支持
  setThingType(0);
  setCount(count);
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YAbstractThing::getDisplayName(void)
{
  YString name=getObjectName();//getAsString("名字");
  return "<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=thing(\""+name+"\")>"+name+"</span>";
}
//--------------------------------------------------------
//设置Count
void YAbstractThing::setCount(long newCount)
{
  if(getThingType()!=1) m_Count=newCount;
  else g_err.show("[YAbstractThing::setCount]改变samethingbutone类型的Count.");
}
//--------------------------------------------------------
YString YAbstractThing::getVarientValueList(void)
{
  YString retS="";
  for(int i=0; i<diff_nums.size(); i++) {
    retS+=(YString)diff_nums[i]+" ";
  }
  return retS;
}
//--------------------------------------------------------
//增加一个
void YAbstractThing::addOne(int value)
{
  if(getThingType()==1) {
    diff_nums.push_back(value);
    setCount(getCount()+1);
  }
  else g_err.show("[YAbstractThing::addOne]对于非SameThingButOne类型使用addOne()");
}
//--------------------------------------------------------
//删掉一个
void YAbstractThing::deleteOne(int No)
{
  if(getThingType()==1) {
    diff_nums.erase(diff_nums.begin()+No-1);
    setCount(getCount()+1);
  }
  else g_err.show("[YAbstractThing::addOne]对于非SameThingButOne类型使用deleteOne()");
}
//--------------------------------------------------------
long YAbstractThing::getAsLong(YString name,int No)
{
	if(name==getVarientName()) return diff_nums[No-1];
	else return YMUDObject::getAsLong(name);
}
//--------------------------------------------------------
void YAbstractThing::set(YString name, long value, int No)
{
	if(name==getVarientName()) diff_nums[No-1]=value;
	else YMUDObject::set(name, value);
}
//--------------------------------------------------------
//复制本身
YMUDObject* YAbstractThing::clone(void)
{
  YMUDObject* another=YMUDObject::clone();
  if(!another) return another;
  ((YAbstractThing*)another)->m_ThingType=m_ThingType;
  ((YAbstractThing*)another)->set("count",0);
  return another;
}

