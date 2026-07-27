//---------------------------------------------------------------------------
//
// ycounter.h    2001年2月2日
//
// 类YCounter：多路计数器，主要用于种类不定的计数，种类确定的计数器可以用YStopwatch(效率较高)
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YCOUNTER_H__
#define __YCOUNTER_H__

#include <map>
#include "ystring.h"

class YCounter {
  private:
    map<YString, int, less<YString> > m_counters;
  protected:

  public:
		YCounter(){};  //构造函数
		~YCounter(){}; //析构函数
    void increase(YString name); //计数器加一
    void reset(void){m_counters.clear();} //所有计数器请零
    YString overview(bool html=false); //总的描述
};

#endif //__YCOUNTER_H__
