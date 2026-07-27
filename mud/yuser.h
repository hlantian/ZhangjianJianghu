//---------------------------------------------------------------------------
//
// yuser.h    2000年6月12日
//
// 类YUser：系统用户
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YUSER_H__
#define __YUSER_H__

#include "ystring.h"
#include "yxiluuser.h"

class YUserManager;

class YUser : public YXiluUser{
	//属性：UserManager
	private:
		YUserManager* m_UserManager; //属性UserManager的成员变量
	public:
		YUserManager* getUserManager(void) {return m_UserManager;} //读属性UserManager
		void setUserManager(YUserManager* newUserManager) {m_UserManager=newUserManager;} //设置UserManager

	//属性：Level
	private:
		int m_Level; //属性Level的成员变量
	public:
		int getLevel(void) {return m_Level;} //读属性Level
		void setLevel(int newLevel) {m_Level=newLevel;} //设置Level

	//属性：LevelString
	public:
		YString getLevelString(void); //读属性LevelString
		void setLevelString(YString newLevelString); //设置LevelString

  public:
		YUser();  //构造函数
    YUser(YXiluUser* xiluuser);     //构造函数(通过西陆用户构造)

		~YUser(); //析构函数
    void quit(void); //退出登录     
};

#endif //__YUSER_H__
