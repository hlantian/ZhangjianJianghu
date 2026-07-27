//---------------------------------------------------------------------------
//
// ycounter.cpp    2001年2月2日
//
// 类YCounter：多路计数器，主要用于种类不定的计数，种类确定的计数器可以用YStopwatch(效率较高)
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "ycounter.h"

//---------------------------------------------------------------------------
//计数器加一
void YCounter::increase(YString name)
{
  if(m_counters.find(name)!=m_counters.end()) m_counters[name]=m_counters[name]+1;
  else m_counters[name]=1;
}
//---------------------------------------------------------------------------
//总的描述
YString YCounter::overview(bool html)
{
  YString retS;
  if(html)retS="项目    次数<br>\n";
  else retS="项目    次数\n";
  map<YString, int, less<YString> >::iterator it=m_counters.begin();
  while(it!=m_counters.end()) {
    if(html) retS+=(*it).first+"  "+(YString)(*it).second+"<br>\n";
    else retS+=(*it).first+"  "+(YString)(*it).second+"\n";
    it++;
  }
  return retS;
}

