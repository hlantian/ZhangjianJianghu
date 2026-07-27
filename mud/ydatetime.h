//---------------------------------------------------------------------------
//
// ydatetime.h    2000年6月12日
//
// 类YDateTime：提供对日期/时间的封装
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YDATETIME_H__
#define __YDATETIME_H__
#include <time.h>
#include <sys/timeb.h>
#include <iostream>
#include <ostream>
using namespace std;
#include "ystring.h"

class YDateTime {
  private:
    timeb time;
  protected:

  public:
		YDateTime();  //构造函数，初始化为当前时间
		~YDateTime(){}; //析构函数

    //重载赋值运算符
    //这里有一些问题，为什么用参考做参数不能正常使用，以后解决
    //void operator =(YDateTime&);
    void operator =(YDateTime);
    //返回当前时间
    static YDateTime now(void);

    //日期/时间比较
    friend int operator==(const YDateTime& left, const YDateTime& right);
    friend int operator!=(const YDateTime& left, const YDateTime& right);
    friend int operator<(const YDateTime& left, const YDateTime& right);
    friend int operator>(const YDateTime& left, const YDateTime& right);
    friend int operator<=(const YDateTime& left, const YDateTime& right);
    friend int operator>=(const YDateTime& left, const YDateTime& right);

    //返回时间之差，单位为秒
    friend const double operator-(const YDateTime& left, const YDateTime& right);

    //输出
    friend ostream& operator<<(ostream& os,const YDateTime& S);
};

#endif //__YDATETIME_H__
