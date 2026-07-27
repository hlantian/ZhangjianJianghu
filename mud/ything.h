//---------------------------------------------------------------------------
//
// ything.h    2000年6月12日
//
// 类YThing：物品
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YTHING_H__
#define __YTHING_H__
#include "yabstractthing.h"

class YThing : public YAbstractThing {
  //属性：ThingName(名字)
	private:
		//YString m_ThingName; //属性ThingName(名字)的成员变量
	public:
		YString getThingName(void) {return getObjectName();} //读属性ThingName(名字)
		void setThingName(YString newThingName) {setObjectName(newThingName);} //设置ThingName(名字)
  //属性：ThingFontName(显示名字)
	private:
		YString m_ThingFontName; //属性ThingName(显示名字)的成员变量
	public:
		YString getThingFontName(void) {return m_ThingFontName;} //读属性ThingFontName(显示名字)
		void setThingFontName(YString newThingFontName) {m_ThingFontName=newThingFontName;} //设置ThingFontName(显示名字)
  //属性：ThingWeight(重量)
	private:
		long m_ThingWeight; //属性ThingWeight(重量)的成员变量
	public:
		long getThingWeight(void) {return m_ThingWeight;} //读属性ThingWeight(重量)
		void setThingWeight(long newWeight) {m_ThingWeight=newWeight;} //设置ThingWeight(重量)
  //属性：Thingprice(钱数)
	private:
		long m_Thingprice; //属性Thingprice(价格)的成员变量
	public:
		long getThingprice(void) {return m_Thingprice;} //读属性Thingprice(价格)
		void setThingprice(long newThingprice) {m_Thingprice=newThingprice;} //设置Thingprice(价格)
  //属性：Describe(描述)
	private:
		YString m_Describe; //属性Describe(描述)的成员变量
	public:
		YString getDescribe(void) {return m_Describe;} //读属性Describe(描述)
		void setDescribe(YString newDescribe) {m_Describe=newDescribe;} //设置Describe(描述)
  //属性：Quantifier(量词)
	private:
		YString m_Quantifier; //属性Quantifier(量词)的成员变量
	public:
		YString getQuantifier(void) {return m_Quantifier;} //读属性Quantifier(量词)
		void setQuantifier(YString newQuantifier) {m_Quantifier=newQuantifier;} //设置Quantifier(量词)

  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);
    virtual YString getDisplayNameAndCount(void);  //后面加一括弧显示数量

  public:
		YThing(YString initFileName="");  //构造函数
		virtual ~YThing(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YThing");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为中介物体
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command);

    //将子物体传给另一物体
    virtual bool giveChildTo(YMUDObject* child, YMUDObject* another, long count=1, long No=1);

    virtual int onTimer(void); //事件Timer的默认处理函数


    //复制本身
    virtual YMUDObject* clone(void);

};

#endif //__YTHING_H__
