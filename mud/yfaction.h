//---------------------------------------------------------------------------
//
// yfaction.h    2001年6月18日
//
// 类YFaction：玩家帮派
//
// 作者：张勇  单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YFACTION_H__
#define __YFACTION_H__

class YFaction : public YMUDObject{

  //属性：FactionList(帮派列表)
	private:
		YString m_FactionList; //属性FactionList(帮派列表)的成员变量
	public:
		YString getFactionList(void) {return m_FactionList;} //读属性FactionList(帮派列表)
		void setFactionList(YString newFactionList) {m_FactionList=newFactionList;} //设置FactionList(帮派列表)
  //属性：FactionAmount(帮派总数)
	private:
		long m_FactionAmount; //属性FactionAmount(帮派总数)的成员变量
	public:
		long getFactionAmount(void) {return m_FactionAmount;} //读属性FactionAmount(帮派总数)
		void setFactionAmount(long newFactionAmount) {m_FactionAmount=newFactionAmount;} //设置FactionAmount(帮派总数)

  public:
    YFaction(YString filename);  //构造函数
    virtual ~YFaction(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YFaction");}

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};

    //函数
    virtual int fnAddFaction(YString name); //添加新帮派
    virtual int fnSubFaction(YString name); //减去一个帮派
    virtual int fnSetFacionBanner(YString name,YString banner); //设置帮派的口号
    virtual YString fnGetFacionBanner(YString name);            //得到帮派的口号
    virtual int fnSetFacionOwner(YString name,YString owner);   //设置帮派的帮主
    virtual YString fnGetFacionOwner(YString name);             //得到帮派的帮主
    virtual int fnSetFacionColor(YString name,YString color);   //设置帮派的颜色
    virtual YString fnGetFacionColor(YString name);             //得到帮派的颜色
    virtual int fnSetPlayerAmount(YString name,long amount);   //设置帮派的玩家数量
    virtual long fnGetPlayerAmount(YString name);             //得到帮派的玩家数量
    virtual int fnSetFactionPower(YString name,long sub,long add);  //设置帮派的势力值
    virtual long fnGetFactionPower(YString name);                   //得到帮派的势力值
    int isFacionExisting(YString name);   //该帮派是否存在？
    virtual int fnSetFactionClose(YString name,long close);  //设置帮派的团结度
    virtual long fnGetFactionClose(YString name);            //得到帮派的团结度
    virtual int fnSetFacionStatus(YString name,YString status);   //设置帮派的状态
    virtual YString fnGetFacionStatus(YString name);              //得到帮派的状态
    virtual int fnFacionAddPlayer(YString name,YString playername); //帮派增加一人
    virtual int fnFacionSubPlayer(YString name,YString playername); //帮派减少一人
    virtual int isFacionPlayerExisting(YString name,YString playername);  //帮派成员是否存在？
    virtual int fnRemoveFaction(YString name);                      //删除一个帮派
};

#endif //__YFACTION_H__
