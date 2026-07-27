#ifndef __YLINGWUROOM_H__
#define __YLINGWUROOM_H__
#include "yroom.h"

class YLingWuRoom : public YRoom{
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YLingWuRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);

    YLingWuRoom(YString initFileName="");  //构造函数
    virtual ~YLingWuRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所

    //实现开席后的时间处理
    virtual int onTimer(void); //领悟房间的ontime

   private:
		long m_LingWuSpend; //属性LingWuSpend(领悟消耗)的成员变量
	public:
		long getLingWuSpend(void) {return m_LingWuSpend;} //读属性LingWuSpend(领悟消耗)
		void setLingWuSpend(long newLingWuSpend) {m_LingWuSpend=newLingWuSpend;} //设置LingWuSpend(领悟消耗)

   private:
		long m_QianNengSpend; //属性QianNengSpend(潜能消耗)的成员变量
	public:
		long getQianNengSpend(void) {return m_QianNengSpend;} //读属性QianNengSpend(潜能消耗)
		void setQianNengSpend(long newQianNengSpend) {m_QianNengSpend=newQianNengSpend;} //设置QianNengSpend(潜能消耗)


	//属性：LingWuMax(领悟的最大级别)
	private:
		long m_LingLingWuMax; //属性LingLingWuMax(领悟最大级别)的成员变量
	public:
		long getLingLingWuMax(void) {return m_LingLingWuMax;} //读属性LingLingWuMax(领悟最大级别)
		void setLingLingWuMax(long newLingLingWuMax) {m_LingLingWuMax=newLingLingWuMax;} //设置LingLingWuMax(领悟最大级别)

	//属性：RoomAllSkills(可以领悟的武功)
	private:
		YString m_RoomAllSkills; //属性RoomAllSkills(可以领悟的武功)的成员变量
	public:
		YString getRoomAllSkills(void) {return m_RoomAllSkills;} //读属性RoomAllSkills(可以领悟的武功)
		void setRoomAllSkills(YString newRoomAllSkills) {m_RoomAllSkills=newRoomAllSkills;} //设置RoomAllSkills(可以领悟的武功)

    //各种命令处理
    virtual int lingwu(YAbstractActor* executor,YString command); //吃东西
    virtual int lian(YAbstractActor* executor,YString command); //吃东西
    virtual int qifu(YAbstractActor* executor); //祈福
    virtual int canhui(YAbstractActor* executor); //忏悔
};

#endif //__YLINGWUROOM_H__
 
