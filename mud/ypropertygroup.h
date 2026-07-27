//---------------------------------------------------------------------------
//
// ypropertygroup.h    2000年6月12日
//
// 类YPropertyGroup：属性集
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YPROPERTYGROUP_H__
#define __YPROPERTYGROUP_H__

#include <map>
#include <iostream>
#include "ystring.h"

#define BUFSIZE 1024   //属性名+属性值总长度+5


using namespace std;

class YMUDObject;

class YPropertyGroup {
  public:
    enum valueType{typeLong,typeFloat,typeString,typeNotExist};
  private:
    map<YString, long, less<YString> > longGroup;
    map<YString, float, less<YString> > floatGroup;
    map<YString, YString, less<YString> > stringGroup;
  private:
    // Print out a pair
    friend ostream& operator<<(ostream& out, const pair<string, string> & p);
    template <class First, class Second>
    friend ostream& operator<<(ostream& out,const pair<First,Second> & p);

    // Print out a map
    typedef map<string, int, less<string> > months_type;
    friend ostream& operator<<(ostream& out, const map<YString, long, less<YString> > & l);
    friend ostream& operator<<(ostream& out, const map<YString, float, less<YString> > & l);
    friend ostream& operator<<(ostream& out, const map<YString, YString, less<YString> > & l);


  //属性：Owner
  private:
    YMUDObject* m_Owner;
  public:
    void setOwner(YMUDObject* newOwner) {m_Owner=newOwner;}
    YMUDObject* getOwner(void) {return m_Owner;}

  private:
  public:
  	YPropertyGroup(YMUDObject* owner=NULL):m_Owner(owner){};  //构造函数
	  ~YPropertyGroup(){}; //析构函数
    int exist(YString name); //该属性是否存在
    valueType typeOf(YString name); //该属性的数据类型
    void remove(YString name); //删除属性
    void removeAll(void); //删除所有属性

    //存取属性(map到YPropertyGroup)
    void set(YString name, float value);
    void set(YString name, long value);
    void set(YString name, short value){set(name,(long)value);};
    void set(YString name, int value){set(name,(long)value);};
    void set(YString name, double value){set(name,(float)value);};
    void set(YString name, YString value);
    //将"名字=值"形式的字符串加入属性集,返回属性名
    YString set(char* name, valueType type);
    long getAsLong(YString name);
    float getAsFloat(YString name);
    YString getAsString(YString name);
    void save(ostream& os);
    int load(istream& is);
    int reload(istream& is);

    //将所有属性复制到另一PropertyGroup
    void copyTo(YPropertyGroup* another);
};

#endif //__YPROPERTYGROUP_H__
