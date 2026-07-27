//---------------------------------------------------------------------------
//
// yabstractsamething.h    2000年8月30日
//
// 类YAbstractSameThing：在MUD中每个这样的物体的属性都完全一样
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YABSTRACTSAMETHING_H__
#define __YABSTRACTSAMETHING_H__

#include <vector>
#include "yabstractthing.h"


class YAbstractSameThing : public YAbstractThing {
  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);

	//属性：Count
	public:
		inline long getCount(void); //读属性Count
		inline void setCount(long newCount); //设置Count
	
	//处理多个物体的不同属性
	private:
		vector<int> diff_nums;
	public:
		long getAsLong(YString name,int No=1);
		void set(YString name, long value, int No=1);

  public:
  	YAbstractSameThing(YString initFileName="");  //构造函数
  	virtual ~YAbstractSameThing(){}; //析构函数

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YAbstractSameThing");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

};

#endif //__YABSTRACTSAMETHING_H__
