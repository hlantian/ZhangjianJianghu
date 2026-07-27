//---------------------------------------------------------------------------
//
// ytimer.cpp    2000年6月12日
//
// 类YTimer：定时器(单位使用毫秒),这个版本只提供4种不同的定时间隔
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

YTimerControl YTimer::m_TimerControl;
int YTimerControl::m_SmallestTimeUnit=2000;
int YTimerControl::m_RealInterval=0;
list<YTimer*> YTimerControl::m_timerlist;
list<YTimer*> YTimerControl::m_timerlist_temp;
//---------------------------------------------------------------------------
//YTimer构造函数
YTimer::YTimer(YMUDObject* owner, int interval)
:m_Owner(owner),
 m_Interval(interval),
 m_resttime(1),
 m_added(false)
{
}
//---------------------------------------------------------------------------
//YTimer析构函数
YTimer::~YTimer()
{
  disable();
}
//---------------------------------------------------------------------------
void YTimer::disable(void)
{
  m_TimerControl.remove(this);
  m_added=false;
}
//---------------------------------------------------------------------------
//YTimerControl构造函数
YTimerControl::YTimerControl(int TimersInitCapacity,int TimersResizeStep):
          m_TimersInitCapacity(TimersInitCapacity),
          m_TimersResizeStep(TimersResizeStep),
          m_TimerSpecsNum(0),
          m_TimerSpecs(NULL)
{
  init();
  start();
}
//---------------------------------------------------------------------------
//YTimerControl析构函数
YTimerControl::~YTimerControl()
{
  YErr::show("[YTimerControl::~YTimerControl]I am distroyed!!!!");
}
//---------------------------------------------------------------------------
//YTimerControl初始化
void YTimerControl::init(void)
{
  m_TimerSpecsNum=10;  //10种不同的定时间隔
  m_TimerSpecs=(YTimerSpec*)malloc(sizeof(YTimerSpec)*(m_TimerSpecsNum));
  if(!m_TimerSpecs) {
    g_applog->write("[YTimerControl::init]内存不足。");
    return;
  }
  for(int i=0; i<m_TimerSpecsNum; i++) {
    m_TimerSpecs[i].interval=0;
    m_TimerSpecs[i].resttime=0;
    m_TimerSpecs[i].capacity=0;
    m_TimerSpecs[i].timers=NULL;
  }
}
//---------------------------------------------------------------------------
void YTimerControl::add(YTimer* timer)
{
  if(timer->m_Interval==0) return; //定时间隔为零，不必处理timer->m_Interval
  YTimer** timers=NULL;
  int time_spec_no;
  for(int i=0; i<m_TimerSpecsNum; i++) { //查找合适的定时器组
    if(m_TimerSpecs[i].interval==timer->m_Interval) {  //找到了
      timers=m_TimerSpecs[i].timers;
      time_spec_no=i;
      break;
    }
  }
  if(!timers) { //没找到，新建
    for(int i=0; i<m_TimerSpecsNum; i++) { //查找合适的定时器组
      if(m_TimerSpecs[i].interval==0) {  //找到了
        m_TimerSpecs[i].interval=timer->m_Interval;
        m_TimerSpecs[i].resttime=timer->m_Interval;
        m_TimerSpecs[i].capacity=m_TimersInitCapacity;
        m_TimerSpecs[i].timers=(YTimer**)malloc(m_TimersInitCapacity*sizeof(YTimer*));
        if(!m_TimerSpecs[i].timers) {
          g_applog->write("[YTimerControl::add]内存不足。");
          return;
        }
        for(int j=0; j<m_TimersInitCapacity; j++) {
          m_TimerSpecs[i].timers[j]=NULL;
        }
        timers=m_TimerSpecs[i].timers;
        time_spec_no=i;
        break;
      }
    }
  }
  
  bool ok=false;
  for(int i=0; i<m_TimerSpecs[time_spec_no].capacity; i++) {  //添加timer
    if(!timers[i]) {
      timers[i]=timer;
      timer->m_timespec=&(m_TimerSpecs[time_spec_no]);
      ok=true;
      break;
    }
  }
  if(!ok) {  //timer数组满，增加容量
    int old_capacity=m_TimerSpecs[time_spec_no].capacity;
    int new_capacity=old_capacity+m_TimersResizeStep;
    m_TimerSpecs[time_spec_no].timers
       =(YTimer**)realloc(m_TimerSpecs[time_spec_no].timers,new_capacity*sizeof(YTimer*));
    if(!m_TimerSpecs[time_spec_no].timers) {
      g_applog->write("[YTimerControl::add]内存不足。");
      return;
    }
    //添加timer
    m_TimerSpecs[time_spec_no].timers[old_capacity]=timer;
    timer->m_timespec=&(m_TimerSpecs[time_spec_no]);
    //将其余的timer指针置为空
    for(int i=old_capacity+1; i<new_capacity; i++) {
      m_TimerSpecs[time_spec_no].timers[i]=NULL;
    }
    //更改TimerSpec容量
    m_TimerSpecs[time_spec_no].capacity=new_capacity;
  }
}
//---------------------------------------------------------------------------
void YTimerControl::remove(YTimer* timer)
{
  YTimer** timers=NULL;
  int time_spec_no;
  for(int i=0; i<m_TimerSpecsNum; i++) { //查找合适的定时器组
    if(m_TimerSpecs[i].interval==timer->m_Interval) {
      timers=m_TimerSpecs[i].timers;
      time_spec_no=i;
      break;
    }
  }
  if(!timers) return; //没找到

  for(int i=0; i<m_TimerSpecs[time_spec_no].capacity; i++) {  //删除timer
    if(timers[i]==timer) timers[i]=NULL;
  }
}
//---------------------------------------------------------------------------
//从类Thread中继承
void YTimerControl::run(void)
{
  YDateTime starttime=YDateTime::now();
  YDateTime overtime;
  double lasttime;
  while(true) {
    //******信号灯/同步的处理
    #ifdef __USE_SEMAPHORE__
      if(g_SystemSemaphore!=SEM_FAILED)
        if(sem_wait(g_SystemSemaphore)!=0)
          g_err.show("[YTimerControl::onSmallestTimeUnit]等待系统信号灯失败.");
    #endif
    bool first=true;
    if((!g_Busy) && g_Busy_Wait) sleep(10);
    while(g_Busy) {
      if(first) {
       if(!g_Busy_Wait) g_Busy_Wait=3;
        g_applog->write("[YTimerControl::onSmallestTimeUnit]系统忙(g_Busy="+(YString)g_Busy+")");
       }
      first=false;
    }
    g_Busy=3;
    if(g_Busy_Wait==3) g_Busy_Wait=0;

    //处理所有的OnTimer事件
    g_Counter->reset();
    g_Stopwatch->start(2);
    YDateTime t_now=YDateTime::now();
    m_RealInterval=(t_now-starttime)*1000; //真正的间隔时间是现在减去上一次的开始时间
    starttime=t_now;

    for(int i=0; i<m_TimerSpecsNum; i++) { //查找合适的定时器组
      if(m_TimerSpecs[i].interval==0) break;
      m_TimerSpecs[i].resttime-=m_RealInterval;
      if(m_TimerSpecs[i].resttime<=0) { //时间到
        YTimer** timers=m_TimerSpecs[i].timers;
        for(int j=0; j<m_TimerSpecs[i].capacity; j++) { //对该组中所有的Timer
          if(timers[j]) {
            timers[j]->m_Owner->onTimer();              //激发OnTimer事件
            g_Counter->increase(timers[j]->m_Owner->getRuntimeClass());
          }
        }
        m_TimerSpecs[i].resttime=m_TimerSpecs[i].interval;
      }
    }

    overtime=YDateTime::now();
    lasttime=overtime-starttime;
    //cout<<"lasttime="<<lasttime;
    if(lasttime<0) lasttime=0;
    int sleeptime=(double)m_SmallestTimeUnit-lasttime*1000.;
    if(sleeptime<0) {
      char err[100];
      sprintf(err,"[YTimerControl::onSmallestTimeUnit]OnTimer运行时间过长(%f秒)。",lasttime);
      g_err.show(err);
      sleeptime=0;
    }
    g_Stopwatch->stop(2);
  //******下面又是有关同步的处理
  g_Busy=0;
  #ifdef __USE_SEMAPHORE__
    if(g_SystemSemaphore!=SEM_FAILED)
      if(sem_post(g_SystemSemaphore)!=0)
        g_err.show("[YTimerControl::onSmallestTimeUnit]挂出系统信号灯失败.");
  #endif
    //cout<<"sleep "<<sleeptime<<"ms."<<endl;

    sleep(m_SmallestTimeUnit);
  }
}
//---------------------------------------------------------------------------
//读属性Interval(得到的是真正的间隔时间)
int YTimer::getInterval(void)
{
  return m_timespec->interval-m_timespec->resttime;
}
//---------------------------------------------------------------------------
//设置Interval
void YTimer::setInterval(int newInterval)
{
  if(m_added) m_TimerControl.remove(this);
  m_Interval=newInterval;
  m_TimerControl.add(this);
  m_added=true;
}




