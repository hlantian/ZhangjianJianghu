//---------------------------------------------------------------------------
//
// ystringlist.cpp    2001年2月2日
//
// 类YStringList：字符串列表，提供查找，存储等功能
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmudcore.h"
/*
#include <stdio.h>
#include "ystringlist.h"
*/
//---------------------------------------------------------------------------
//YStringList构造函数
YStringList::YStringList(YString initFileName,int maxlen)
:m_FileName(initFileName),m_maxlen(maxlen)
{
  load();
}
//---------------------------------------------------------------------------
//从文件中读
bool YStringList::load()
{
  if(m_FileName=="") return false;
  FILE* f=fopen(m_FileName.c_str(),"rt");
  if(!f) return false;
  char* buf=(char*)malloc(m_maxlen);
  if(!buf) {
    fclose(f);
    return false;
  }
  while(fgets(buf,m_maxlen,f)) {
    int last=strlen(buf)-1;
    if((buf[last]=='\n')||(buf[last]=='\r')) buf[last]='\0';
    if((buf[last-1]=='\n')||(buf[last-1]=='\r')) buf[last-1]='\0';
    m_stringgroup[buf]=1;
  }
  free(buf);
  fclose(f);
  return true;
}
//---------------------------------------------------------------------------
//写入文件
bool YStringList::save()
{
  if(m_FileName=="") return false;
  FILE* f=fopen(m_FileName.c_str(),"wt");
  if(!f) return false;

  map<YString, char, less<YString> >::iterator it=m_stringgroup.begin();
  YString retS="";
  while(it!=m_stringgroup.end()) {
    fputs((*it).first.c_str(),f);
    fputc('\n',f);
    it++;
  }
  fclose(f);
  return true;
}
//---------------------------------------------------------------------------
//列表中是否有某个字符串
bool YStringList::isIn(YString s)
{
  return  m_stringgroup.find(s)!=m_stringgroup.end();
}

