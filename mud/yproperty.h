//---------------------------------------------------------------------------
//
// yproperty.h    2000年6月12日
//
// 类YProperty：属性
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YPROPERTY_H__
#define __YPROPERTY_H__
#include "ystring.h"
class YProperty {
  public:
    enum valueType{typeLong,typeFloat,typeString};
  private:
    union {
      long longValue;
      float floatValue;
      YString* stringValue;
    }value;
    YString name;
    valueType type;
  protected:

  public:
	YProperty();  //构造函数
	YProperty(YString newName, long newValue);
	~YProperty(); //析构函数
  void set(YString newName, long newValue);
  void set(YString newName, float newValue);
  void set(YString newName, YString newValue);   //YProperty保存字符串的副本，并负责销毁
  void set(long newValue){set("",newValue);};
  void set(float newValue){set("",newValue);};
  void set(YString newValue){set("",newValue);};
  long getAsLong(YString name="");
  float getAsFloat(YString name="");
  YString getAsString(YString name="");
};

#endif //__YPROPERTY_H__
