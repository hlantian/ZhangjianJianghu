//---------------------------------------------------------------------------
//
// ycollectroom.h    2001年1月31日
//
// 类YCollectRoom：采集职业原料的房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YCOLLECTROOM_H__
#define __YCOLLECTROOM_H__
#include "yroom.h"

class YCollectRoom : public YRoom{
  //属性：MineTotal(矿藏总数)
	private:
		long m_MineTotal; //属性MineTotal(矿藏总数)的成员变量
	public:
		long getMineTotal(void) {return m_MineTotal;} //读属性MineTotal(矿藏总数)
		void setMineTotal(long newMineTotal) {m_MineTotal=newMineTotal;} //设置MineTotal(矿藏总数)
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
  //属性：MineType(矿藏种类)
	private:
		YString m_MineType; //属性MineType(矿藏种类)的成员变量
	public:
		YString getMineType(void) {return m_MineType;} //读属性MineType(矿藏种类)
		void setMineType(YString newMineType) {m_MineType=newMineType;} //设置MineType(矿藏种类)
  
  public:
    //读属性RuntimeClass
    virtual YString getRuntimeClass(void) {return YString("YCollectRoom");}
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    YCollectRoom(YString initFileName="");  //构造函数
    virtual ~YCollectRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
    //各种命令处理
    virtual int caikuang(YAbstractActor* executor); //各种采矿

    virtual int caikuangEnd(YAbstractActor* executor); //采矿结束
};

#endif //__YCOLLECTROOM_H__
