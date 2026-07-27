//---------------------------------------------------------------------------
//
// ystopwatch.cpp    2001年2月2日
//
// 类YStopwatch：多路秒表
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "ystopwatch.h"
#include "yerr.h"

//---------------------------------------------------------------------------
//开始计时
void YStopwatch::start(int No)
{
  watches[No].used=true;
  watches[No].running=true;
  watches[No].starttime=YDateTime::now();
}
//---------------------------------------------------------------------------
//结束计时
void YStopwatch::stop(int No)
{
  if((!watches[No].used)||(!watches[No].running)) {
    YErr::show("[YStopwatch::stop]非法使用秒表");
    return;
  }
  watches[No].count++;
  watches[No].time+=YDateTime::now()-watches[No].starttime;
  watches[No].running=false;
}
//---------------------------------------------------------------------------
//总的描述
YString YStopwatch::overview(bool html)
{
  YString retS="";
  if(html)retS="项目    次数   总耗时   平均<br>\n";
  else retS="项目    次数   总耗时   平均\n";
  for(int i=0; i<m_capacity; i++) {
    if(!watches[i].used) continue;
    if(html) retS+=watches[i].name+"  "+(YString)watches[i].count+"  "+(YString)watches[i].time+"  "+(YString)(watches[i].time/watches[i].count)+"<br>\n";
    else retS+=watches[i].name+"  "+(YString)watches[i].count+"  "+(YString)watches[i].time+"  "+(YString)(watches[i].time/watches[i].count)+"\n";
  }
  return retS;
}

