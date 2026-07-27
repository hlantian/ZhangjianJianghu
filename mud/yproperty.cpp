//---------------------------------------------------------------------------
//
// yproperty.cpp    2000年6月12日
//
// 类YProperty：属性
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "yproperty.h"
#include <assert.h>

//---------------------------------------------------------------------------
//YProperty构造函数
YProperty::YProperty()
{
  value.stringValue=0;
}
//---------------------------------------------------------------------------
//YProperty析构函数
YProperty::~YProperty()
{
  if((type==typeString) && (value.stringValue!=0)) delete value.stringValue;
}
//---------------------------------------------------------------------------
void YProperty::set(YString newName, long newValue)
{
  if((type==typeString) && (value.stringValue!=0)) delete value.stringValue;
  if(newName!="") name=newName;
  type=typeLong;
  value.longValue=newValue;
}
//---------------------------------------------------------------------------
void YProperty::set(YString newName, float newValue)
{
  if((type==typeString) && (value.stringValue!=0)) delete value.stringValue;
  if(newName!="") name=newName;
  type=typeFloat;
  value.floatValue=newValue;
}
//---------------------------------------------------------------------------
void YProperty::set(YString newName, YString newValue)
{
  if((type==typeString) && (value.stringValue!=0)) delete value.stringValue;
  if(newName!="") name=newName;
  type=typeString;
  value.stringValue=new YString(newValue);
}
//---------------------------------------------------------------------------
long YProperty::getAsLong(YString name)
{
  assert(type==typeLong);
  return value.longValue;
}
//---------------------------------------------------------------------------
float YProperty::getAsFloat(YString name)
{
  assert(type==typeFloat);
  return value.floatValue;
}
//---------------------------------------------------------------------------
YString YProperty::getAsString(YString name)
{
  assert(type==typeString);
  return *(value.stringValue);
}
//---------------------------------------------------------------------------

