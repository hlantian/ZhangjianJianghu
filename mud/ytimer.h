//---------------------------------------------------------------------------
//
// ytimer.h    2000年6月12日
//
// 类YTimer：定时器(单位使用毫秒),这个版本只提供4种不同的定时间隔
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YTIMER_H__
#define __YTIMER_H__

#include <list>
#include <cc++/thread.h>
using namespace ost;
using namespace std;

class YTimer;
struct YTimerSpec { //描述
  int interval; //时间间隔
  int resttime; //还剩多少时间启动onTimeout()
  int capacity; //容量
  YTimer** timers; //Timer数组
};

class YMUDObject;
class YTimerControl : public Thread {
  friend class YTimer;
  private:
    int m_TimersInitCapacity; //初始容纳YTimer的数量
    int m_TimersResizeStep;   //容量不够时增加步长
    int m_TimerSpecsNum;      //定时器组数组大小
    YTimerSpec* m_TimerSpecs; //定时器组数组

  public:
    YTimerControl(int TimersInitCapacity=1000,int TimersResizeStep=1000);
    ~YTimerControl();
  private:
    void init(void);
    void add(YTimer* timer);
    void remove(YTimer* timer);
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
    void run(void);
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
		int getInterval(void); //读属性Interval(得到的是真正的间隔时间)
		void setInterval(int newInterval);  //设置Interval

	//属性：Owner
	private:
		YMUDObject* m_Owner; //属性Owner的成员变量
	public:
		YMUDObject* getOwner(void) {return m_Owner;} //读属性Owner
		void setOwner(YMUDObject* newOwner) {m_Owner=newOwner;} //设置Owner

  private:
    YTimerSpec* m_timespec; //自己所在的TimerSpec
    int m_resttime; //还剩多少时间启动onTimeout()
    bool m_added; //是否已经把自己加到YTimerControl中
    void onTimeout(void); 
  public:
    void disable(void); //关闭计时器

  public:
	YTimer(YMUDObject* owner, int interval=0);  //构造函数
	~YTimer(); //析构函数
};

#endif //__YTIMER_H__
