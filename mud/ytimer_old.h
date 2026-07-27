//---------------------------------------------------------------------------
//
// ytimer.h    2000年6月12日
//
// 类YTimer：定时器(单位使用毫秒)
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YTIMER_H__
#define __YTIMER_H__

#include <list>
#include "thread.h"

class YMUDObject;
class YTimerControl : public Thread {
  friend class YTimer;
  public:
  YTimerControl(){Start();}
  ~YTimerControl();

  private:
    static int m_RealInterval; //一次OnTimer事件中的真正间隔时间
	//属性：SmallestTimeUnit
	private:
		static int m_SmallestTimeUnit; //属性SmallestTimeUnit的成员变量
	public:
		int getSmallestTimeUnit(void) {return m_SmallestTimeUnit;} //读属性SmallestTimeUnit
		void setSmallestTimeUnit(int newSmallestTimeUnit) {m_SmallestTimeUnit=newSmallestTimeUnit;} //设置SmallestTimeUnit

  private:
    //存储所有实例的list
    static list<YTimer*> m_timerlist;
    static list<YTimer*> m_timerlist_temp;
  protected:
    //从类Thread中继承
    virtual void Run(void);
  private:
    void onSmallestTimeUnit(list<YTimer*>::iterator t);  //每SmallestTimeUnit调用
};

class YTimer {
  friend class YTimerControl;
  public:
    typedef list<YTimer*>::iterator timer_type;

  //时钟控制器
  private:
    static YTimerControl m_TimerControl;

	//属性：SmallestTimeUnit
	public:
		int getSmallestTimeUnit(void) {return m_TimerControl.getSmallestTimeUnit();} //读属性SmallestTimeUnit
		void setSmallestTimeUnit(int newSmallestTimeUnit)
           {m_TimerControl.setSmallestTimeUnit(newSmallestTimeUnit);} //设置SmallestTimeUnit

	//属性：Interval
	private:
		int m_Interval; //属性Interval的成员变量
		int m_RealInterval; //一次OnTimer事件中的真正间隔时间
	public:
		int getInterval(void) {return m_Interval-m_resttime;} //读属性Interval(得到的是真正的间隔时间)
		void setInterval(int newInterval) {m_Interval=newInterval;} //设置Interval

	//属性：Owner
	private:
		YMUDObject* m_Owner; //属性Owner的成员变量
	public:
		YMUDObject* getOwner(void) {return m_Owner;} //读属性Owner
		void setOwner(YMUDObject* newOwner) {m_Owner=newOwner;} //设置Owner

  private:
    int m_resttime; //还剩多少时间启动onTimeout()
    void onTimeout(void); 
  public:
    void disable(void); //关闭计时器

  public:
	YTimer(YMUDObject* owner, int interval=0);  //构造函数
	~YTimer(); //析构函数
};

#endif //__YTIMER_H__
