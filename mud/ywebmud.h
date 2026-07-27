//---------------------------------------------------------------------------
//
// ywebmud.h    2000年6月12日
//
// 类YWwbMUD：控制MUD系统的启动、运行、关闭等操作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YWEBMUD_H__
#define __YWEBMUD_H__

#include "yplayermanager.h"

class YWebMUD {
	//属性：MajorVersionNo
	private:
		int m_MajorVersionNo; //属性MajorVersionNo的成员变量
	public:
		int getMajorVersionNo(void) {return m_MajorVersionNo;} //读属性MajorVersionNo

	//属性：MinorVersionNo
	private:
		int m_MinorVersionNo; //属性MinorVersionNo的成员变量
	public:
		int getMinorVersionNo(void) {return m_MinorVersionNo;} //读属性MinorVersionNo

	//属性：Version
	private:
		YString m_Version; //属性Version的成员变量
	public:
		YString getVersion(void) {return m_Version;} //读属性Version
		void setVersion(YString newVersion) {m_Version=newVersion;} //设置Version

	//属性：Copyright
	private:
		YString m_Copyright; //属性Copyright的成员变量
	public:
		YString getCopyright(void) {return m_Copyright;} //读属性Copyright
		void setCopyright(YString newCopyright) {m_Copyright=newCopyright;} //设置Copyright

	//属性：SysInfo
	private:
		YString m_SysInfo; //属性SysInfo的成员变量
	public:
		YString getSysInfo(void) {return m_SysInfo;} //读属性SysInfo
		void setSysInfo(YString newSysInfo) {m_SysInfo=newSysInfo;} //设置SysInfo

	//属性：RegisteredPlayerCount
	private:
		int m_RegisteredPlayerCount; //属性RegisteredPlayerCount的成员变量
	public:
		int getRegisteredPlayerCount(void) {return m_RegisteredPlayerCount;} //读属性RegisteredPlayerCount
		void setRegisteredPlayerCount(int newRegisteredPlayerCount) {m_RegisteredPlayerCount=newRegisteredPlayerCount;} //设置RegisteredPlayerCount

	//属性：RegisteredWizardCount
	private:
		int m_RegisteredWizardCount; //属性RegisteredWizardCount的成员变量
	public:
		int getRegisteredWizardCount(void) {return m_RegisteredWizardCount;} //读属性RegisteredWizardCount
		void setRegisteredWizardCount(int newRegisteredWizardCount) {m_RegisteredWizardCount=newRegisteredWizardCount;} //设置RegisteredWizardCount

	//属性：RegisteredGodCount
	private:
		int m_RegisteredGodCount; //属性RegisteredGodCount的成员变量
	public:
		int getRegisteredGodCount(void) {return m_RegisteredGodCount;} //读属性RegisteredGodCount
		void setRegisteredGodCount(int newRegisteredGodCount) {m_RegisteredGodCount=newRegisteredGodCount;} //设置RegisteredGodCount

	//属性：OnlinePlayerCount
	private:
		int m_OnlinePlayerCount; //属性OnlinePlayerCount的成员变量
	public:
		int getOnlinePlayerCount(void) {return m_OnlinePlayerCount;} //读属性OnlinePlayerCount
		void setOnlinePlayerCount(int newOnlinePlayerCount) {m_OnlinePlayerCount=newOnlinePlayerCount;} //设置OnlinePlayerCount

	//属性：OnlineWizardCount
	private:
		int m_OnlineWizardCount; //属性OnlineWizardCount的成员变量
	public:
		int getOnlineWizardCount(void) {return m_OnlineWizardCount;} //读属性OnlineWizardCount
		void setOnlineWizardCount(int newOnlineWizardCount) {m_OnlineWizardCount=newOnlineWizardCount;} //设置OnlineWizardCount

	//属性：OnlineGodCount
	private:
		int m_OnlineGodCount; //属性OnlineGodCount的成员变量
	public:
		int getOnlineGodCount(void) {return m_OnlineGodCount;} //读属性OnlineGodCount
		void setOnlineGodCount(int newOnlineGodCount) {m_OnlineGodCount=newOnlineGodCount;} //设置OnlineGodCount

  public:

  public:
		YWebMUD();  //构造函数
		~YWebMUD(); //析构函数
    int start(void);
    void shutdown(int delaySecond);

};

#endif //__YWEBMUD_H__
