//---------------------------------------------------------------------------
//
// ystopwatch.h    2001年2月2日
//
// 类YStopwatch：多路秒表(程序中没有考虑下标溢出，使用时千万注意)
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "ydatetime.h"
#include "ystring.h"

#ifndef __YSTOPWATCH_H__
#define __YSTOPWATCH_H__
struct YSingleStopWatch {
  bool used; //是否开启
  bool running; //是否正在计时
  YString name; //名字
  YDateTime starttime; //开始计时时刻
  int count;  //次数
  double time;  //总耗时
  //构造函数
  YSingleStopWatch():used(false),running(false),name("未命名"),count(0),time(0.){}
};
class YStopwatch {
  private:
    YSingleStopWatch* watches;
    int m_capacity; //容纳的秒表数
  protected:

  public:
		YStopwatch(int capacity):m_capacity(capacity){watches=new YSingleStopWatch[capacity];};  //构造函数
		~YStopwatch(){delete[] watches;}; //析构函数
    void setName(int No, YString name){watches[No].name=name;};
    void enable(int No){watches[No].used=true;}; //使用
    void disable(int No){watches[No].used=true;}; //不使用
    void start(int No); //开始计时
    void stop(int No); //结束计时
    void reset(int No){watches[No].count=0;watches[No].time=0.;}; //清零
    void resetAll(void){for(int i=0; i<m_capacity; i++) reset(i);}; //清零
    void addCount(int No){watches[No].count++;}; //不计时，仅增加计数
    YString overview(bool html=false); //总的描述
};

#endif //__YSTOPWATCH_H__

