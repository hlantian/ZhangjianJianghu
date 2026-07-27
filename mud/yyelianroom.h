//---------------------------------------------------------------------------
//
// yyelianroom.h    2001年2月12日
//
// 类YYelianRoom：冶炼矿石的房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YYELIANROOM_H__
#define __YYELIANROOM_H__
#include "yroom.h"

class YYelianRoom : public YRoom{
  //属性：MaxWinRate(最大成功率)
	private:
		long m_MaxWinRate; //属性MaxWinRate(最大成功率)的成员变量
	public:
		long getMaxWinRate(void) {return m_MaxWinRate;} //读属性MaxWinRate(最大成功率)
		void setMaxWinRate(long newMaxWinRate) {m_MaxWinRate=newMaxWinRate;} //设置MaxWinRate(最大成功率)
  //属性：MinWinRate(最小成功率)
	private:
		long m_MinWinRate; //属性MinWinRate(最小成功率)的成员变量
	public:
		long getMinWinRate(void) {return m_MinWinRate;} //读属性MinWinRate(最小成功率)
		void setMinWinRate(long newMinWinRate) {m_MinWinRate=newMinWinRate;} //设置MinWinRate(最小成功率)
  
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YYelianRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    YYelianRoom(YString initFileName="");  //构造函数
    virtual ~YYelianRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    //各种命令处理
    virtual int yelian(YAbstractActor* executor,YString command); //冶炼
    virtual int list(YAbstractActor* executor); //查询打造列表
    virtual int dazao(YAbstractActor* executor,YString command); //打造
    virtual int dazaoEnd(YAbstractActor* executor,YString command); //打造结束
};

#endif //__YYELIANROOM_H__
