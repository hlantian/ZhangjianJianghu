//---------------------------------------------------------------------------
//
// ypropertygroup.cpp    2000年6月12日
//
// 类YPropertyGroup：属性集
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
/*#ifndef _DONOT_USE_OWNER
  //#include "webmudcore.h"
#else
  #include "ypropertygroup.h"
#endif
*/
#include <ostream>
#include "ymudobject.h"
#include "ypropertygroup.h"
#include <bits/stream_iterator.h>
using namespace std;
//---------------------------------------------------------------------------
//该属性是否存在
int YPropertyGroup::exist(YString name)
{
  return ((longGroup.find(name)!=longGroup.end()) ||
          (floatGroup.find(name)!=floatGroup.end()) ||
          (stringGroup.find(name)!=stringGroup.end()));
}
//---------------------------------------------------------------------------
//该属性的数据类型
YPropertyGroup::valueType YPropertyGroup::typeOf(YString name)
{
  if(name=="") return typeNotExist;
  if(longGroup.find(name)!=longGroup.end()) return typeLong;
  else if(floatGroup.find(name)!=floatGroup.end()) return typeFloat;
  else if(stringGroup.find(name)!=stringGroup.end()) return typeString;
  else return typeNotExist;
}
//---------------------------------------------------------------------------
//删除属性
void YPropertyGroup::remove(YString name)
{
  longGroup.erase(name);
  floatGroup.erase(name);
  stringGroup.erase(name);
}
//---------------------------------------------------------------------------
//删除所有属性
void YPropertyGroup::removeAll(void)
{
  longGroup.clear();
  floatGroup.clear();
  stringGroup.clear();
}
//---------------------------------------------------------------------------
void YPropertyGroup::set(YString name, long value)
{
  if(exist(name)) {    //该属性已存在，修改
    long oldValue;
    if(typeOf(name)!=typeLong) {
      oldValue=0;
      remove(name);
    }
    else {
      oldValue=longGroup[name];
    }
    if(!getOwner()) {
      longGroup[name]=value;
    }
    else {
      if(getOwner()->onBeforePropertyChange(getOwner(),name,oldValue,value)) {
        longGroup[name]=value;
        getOwner()->onAfterPropertyChange(getOwner(),name,oldValue,value);
      }
    }
  }
  else {  //属性不存在，添加
    longGroup[name]=value;
  }
}
//---------------------------------------------------------------------------
void YPropertyGroup::set(YString name, float value)
{
  if(exist(name)) {    //该属性已存在，修改
    float oldValue;
    if(typeOf(name)!=typeFloat) {
      oldValue=0.;
      remove(name);
    }
    else {
      oldValue=floatGroup[name];
    }
    if(!getOwner()) {
      floatGroup[name]=value;
    }
    else {
      if(getOwner()->onBeforePropertyChange(getOwner(),name,oldValue,value)) {
        floatGroup[name]=value;
        getOwner()->onAfterPropertyChange(getOwner(),name,oldValue,value);
      }
    }
  }
  else {  //属性不存在，添加
    floatGroup[name]=value;
  }
}
//---------------------------------------------------------------------------
//将"名字=值"形式的字符串加入属性集,返回属性名
//注：name 内容将被改变
YString YPropertyGroup::set(char* name, valueType type)
{
  char *val=strchr(name,'=');
  if(!val) return "";
  *val='\0';
  val++;
  trim(name);
  trim(val);
  switch(type) {
    case typeLong:
      set(name,atol(val));
      break;
    case typeFloat:
      set(name,atof(val));
      break;
    case typeString:
      set(name,val);
      break;
    default:
      break;
  }
  return YString(name);
}
//---------------------------------------------------------------------------
void YPropertyGroup::set(YString name, YString value)
{
  if(exist(name)) {    //该属性已存在，修改
    YString oldValue;
    if(typeOf(name)!=typeString) {
      oldValue="";
      remove(name);
    }
    else {
      oldValue=stringGroup[name];
    }
    if(!getOwner()) {
      stringGroup[name]=value;
    }
    else {
      if(getOwner()->onBeforePropertyChange(getOwner(),name,oldValue,value)) {
        stringGroup[name]=value;
        getOwner()->onAfterPropertyChange(getOwner(),name,oldValue,value);
      }
    }
  }
  else {  //属性不存在，添加
    stringGroup[name]=value;
  }
}
//---------------------------------------------------------------------------
long YPropertyGroup::getAsLong(YString name)
{
  if(typeOf(name)==typeLong)  return longGroup[name];
  else return 0;
}
//---------------------------------------------------------------------------
float YPropertyGroup::getAsFloat(YString name)
{
  if(typeOf(name)==typeFloat) return floatGroup[name];
  else return 0.;
}
//---------------------------------------------------------------------------
YString YPropertyGroup::getAsString(YString name)
{
  if(typeOf(name)==typeString) return stringGroup[name];
  else return "";
}
//---------------------------------------------------------------------------
void YPropertyGroup::save(ostream& os)
{
  os<<"begin of YPropertyGroup\n";
  os<<"string values:\n";
  os<<stringGroup;
  os<<"long values:\n";
  os<<longGroup;
  os<<"float values:\n";
  os<<floatGroup;
  os<<"end of YPropertyGroup\n";
}
//---------------------------------------------------------------------------
int YPropertyGroup::load(istream& is)
{
  char buffer[BUFSIZE];
  valueType type=typeString;
  while(!is.eof()) {
    is.getline(buffer,BUFSIZE);
    int n=strlen(buffer)-1;
    if(n<0) continue;  //空串
    if(buffer[n]=='\r') buffer[n]='\0'; //兼容UNIX
    if(strcmp(buffer,"begin of YPropertyGroup")==0) continue;
    if(strcmp(buffer,"end of YPropertyGroup")==0) break;
    if(strcmp(buffer,"string values:")==0) {
      type=typeString;
      continue;
    }
    if(strcmp(buffer,"long values:")==0) {
      type=typeLong;
      continue;
    }
    if(strcmp(buffer,"float values:")==0) {
      type=typeFloat;
      continue;
    }
    if(type==typeString) {
      YString name=set(buffer, type);
      if(getAsString(name)=="@LONG") { //长字符串
        YString sValue;
        while(is.getline(buffer,BUFSIZE), strncmp(buffer,"LONG",4)!=0) {
          sValue+=buffer;
          sValue+='\n';
        }
        set(name,sValue);
      }
    }
    else set(buffer, type);
  }
  return 0; //成功读出
}
//---------------------------------------------------------------------------
int YPropertyGroup::reload(istream& is)
{
  removeAll();
  return load(is);
}
//---------------------------------------------------------------------------
// Print out a pair (处理长字符串的情况)(此函数现已无用)
ostream& operator<<(ostream& out, const pair<string, string> & p)
{
  if(p.second.find('\n')==YString::npos) { //属性串中不包含换行
    out << p.first << "=" << p.second;
  }
  else { //属性串中包含换行
    out << p.first << "=@LONG" <<p.second<<"\nLONG";
  }
  return out;
}
//---------------------------------------------------------------------------
// Print out a pair
template <class First, class Second>
ostream& operator<<(ostream& out, const pair<First,Second> & p)
{
  out << p.first << "=" << p.second;
  return out;
}
//---------------------------------------------------------------------------
// Print out long map
ostream& operator<<(ostream& out, const map<YString, long, less<YString> > & l)
{

#ifdef __WIN32__
  copy(l.begin(),l.end(), ostream_iterator
                <map<YString, long, less<YString> >::value_type,char>(out,"\n"));
#else //unix
  copy(l.begin(),l.end(), ostream_iterator 
                <map<YString, long, less<YString> >::value_type>(out, "\n")); 
#endif //__WIN32__

  return out;
}
//---------------------------------------------------------------------------
// Print out float map
ostream& operator<<(ostream& out, const map<YString, float, less<YString> > & l)
{

 #ifdef __WIN32__
  copy(l.begin(),l.end(), ostream_iterator 
                <map<YString, float, less<YString> >::value_type,char>(out,"\n")); 
#else //unix
  copy(l.begin(),l.end(), ostream_iterator 
                <map<YString, float, less<YString> >::value_type>(out, "\n")); 
#endif //__WIN32__

  return out;
}
//---------------------------------------------------------------------------
// Print out YString map
ostream& operator<<(ostream& out, const map<YString, YString, less<YString> > & l)
{
  map<YString, YString, less<YString> >::const_iterator it=l.begin();
  while(it!=l.end()) {
    if(it->second.find('\n')==YString::npos) { //属性串中不包含换行
      out << it->first << "=" << it->second<<'\n';
    }
    else { //属性串中包含换行
      out << it->first << "=@LONG\n" <<it->second<<"\nLONG\n";
    }
    it++;
  }

  //copy(l.begin(),l.end(), ostream_iterator
  //              <map<YString, YString, less<YString> >::value_type,char>(out,"\n"));
  return out;
}
//---------------------------------------------------------------------------
//将所有属性复制到另一PropertyGroup
void YPropertyGroup::copyTo(YPropertyGroup* another)
{
  map<YString, long, less<YString> >::const_iterator l_it=longGroup.begin();
  while(l_it!=longGroup.end()) {
    another->set(l_it->first,l_it->second);
    l_it++;
  }

  map<YString, float, less<YString> >::const_iterator f_it=floatGroup.begin();
  while(f_it!=floatGroup.end()) {
    another->set(f_it->first,f_it->second);
    f_it++;
  }

  map<YString, YString, less<YString> >::const_iterator s_it=stringGroup.begin();
  while(s_it!=stringGroup.end()) {
    another->set(s_it->first,s_it->second);
    s_it++;
  }
}



