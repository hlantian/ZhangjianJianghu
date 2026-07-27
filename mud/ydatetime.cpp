//---------------------------------------------------------------------------
//
// ydatetime.cpp    2000年6月12日
//
// 类YDateTime：提供对日期/时间的封装
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "ydatetime.h"
//---------------------------------------------------------------------------
//YDateTime构造函数
YDateTime::YDateTime()
{
  ::ftime(&time);
}
//---------------------------------------------------------------------------
YDateTime YDateTime::now(void)
{
  return YDateTime();
}
//---------------------------------------------------------------------------
void YDateTime::operator =(YDateTime t)
{
  time.time=t.time.time;
}
//---------------------------------------------------------------------------
int operator==(const YDateTime& left, const YDateTime& right)
{
  if((difftime(left.time.time,right.time.time)==0)
        &&(left.time.millitm==right.time.millitm)) return true;
  else return false;
}
//---------------------------------------------------------------------------
int operator!=(const YDateTime& left, const YDateTime& right)
{
  if((difftime(left.time.time,right.time.time)==0)
        &&(left.time.millitm==right.time.millitm)) return false;
  else return true;
}
//---------------------------------------------------------------------------
int operator<(const YDateTime& left, const YDateTime& right)
{
  return ((left-right)<0);
}
//---------------------------------------------------------------------------
int operator>(const YDateTime& left, const YDateTime& right)
{
  return ((left-right)>0);
}
//---------------------------------------------------------------------------
int operator<=(const YDateTime& left, const YDateTime& right)
{
  return ((left-right)<=0);
}
//---------------------------------------------------------------------------
int operator>=(const YDateTime& left, const YDateTime& right)
{
  return ((left-right)>=0);
}
//---------------------------------------------------------------------------
//这个函数中要暗中调用两次strcpy,有时间应改掉
const double operator-(const YDateTime& left,const YDateTime& right)
{
  return difftime(left.time.time, right.time.time)
         +((double)(left.time.millitm-right.time.millitm))/1000.;
}
//---------------------------------------------------------------------------
//输出
ostream& operator<<(ostream& os, const YDateTime& t) {
  YString retS=ctime(&t.time.time);
  retS.erase(retS.length()-1,1);
  retS+=(YString)t.time.millitm;
  return os << retS;
}

