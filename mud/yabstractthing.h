//---------------------------------------------------------------------------
//
// yabstractthing.h    2000年6月12日
//
// 类YAbstractThing：提供抽象的物件特征及行为
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YABSTRACTTHING_H__
#define __YABSTRACTTHING_H__

#include <deque>

#include "ymudobject.h"

class YAbstractActor;
class YAbstractRoom;

class YAbstractThing : public YMUDObject {
  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);

	//属性：Count(数量)
	private:
		long m_Count; //属性Count(数量)的成员变量
	public:
		long getCount(void) {return m_Count;} //读属性Count(数量)
		void setCount(long newCount); //设置Count(数量)

	//属性：VarientName(变化量名)
  private:
    YString m_VarientName;
	public:
		YString getVarientName(void){return m_VarientName;}; //读属性VarientName(变化量名)

	//属性：ThingType(物体类型:0-same-1-sameButOne-2-different)
	private:
		int m_ThingType; //属性ThingType(物体类型)的成员变量
	public:
		int getThingType(void) {return m_ThingType;} //读属性ThingType(物体类型)
		void setThingType(int newThingType) {m_ThingType=newThingType;} //设置ThingType(物体类型)

	//处理多个物体的不同属性
	private:
		deque<int> diff_nums;
	public:
		long getAsLong(YString name, int No=1);
		void set(YString name, long value, int No=1);
		void set(YString name, YString value) {YMUDObject::set(name,value);};
    long getVarientValue(int No) {return getAsLong(getVarientName());};
    void setVarientValue(int No, long value) {set(getVarientName(), value);};
    YString getVarientValueList(void);
    void addOne(int value); //增加一个
    void deleteOne(int No); //删掉一个

  public:
  	YAbstractThing(YString initFileName="", long count=1);  //构造函数
  	virtual ~YAbstractThing(){}; //析构函数

    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YAbstractThing");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command)=0; //作为中介物体
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command)=0;

    //复制本身
    virtual YMUDObject* clone(void);
    //量词
};

#endif //__YABSTRACTTHING_H__
