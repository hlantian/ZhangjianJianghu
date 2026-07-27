//---------------------------------------------------------------------------
//
// yxiluuser.h    2000年6月12日
//
// 类YXiluUser：西陆用户
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YXILUUSER_H__
#define __YXILUUSER_H__

#include "ystring.h"

typedef enum{FEMALE=0, MALE=1, SEX_UNKNOWN}sex_type;

class YXiluUserManager;

class YXiluUser {
	//属性：XiluUserManager
	private:
		YXiluUserManager* m_XiluUserManager; //属性XiluUserManager的成员变量
	public:
		YXiluUserManager* getXiluUserManager(void) {return m_XiluUserManager;} //读属性XiluUserManager
		void setXiluUserManager(YXiluUserManager* newXiluUserManager) {m_XiluUserManager=newXiluUserManager;} //设置XiluUserManager

	//属性：Name
	private:
		YString m_Name; //属性Name的成员变量
	public:
		YString getName(void) {return m_Name;} //读属性Name
		void setName(YString newName) {m_Name=newName;} //设置Name

	//属性：Password
	private:
		YString m_Password; //属性Password的成员变量
	public:
		YString getPassword(void) {return m_Password;} //读属性Password
		void setPassword(YString newPassword) {m_Password=newPassword;} //设置Password

	//属性：EncryptedPassword
	private:
		YString m_EncryptedPassword; //属性EncryptedPassword的成员变量
	public:
		YString getEncryptedPassword(void) {return m_EncryptedPassword;} //读属性EncryptedPassword
		void setEncryptedPassword(YString newEncryptedPassword) {m_EncryptedPassword=newEncryptedPassword;} //设置EncryptedPassword

	//属性：Sex
	private:
		sex_type m_Sex; //属性Sex的成员变量
	public:
		sex_type getSex(void) {return m_Sex;} //读属性Sex
		void setSex(sex_type newSex) {m_Sex=newSex;} //设置Sex
		void setSex(YString sex); //设置Sex 

	//属性：Age
	private:
		int m_Age; //属性Age的成员变量
	public:
		int getAge(void) {return m_Age;} //读属性Age
		void setAge(int newAge) {m_Age=newAge;} //设置Age

	//属性：Provence
	private:
		YString m_Provence; //属性Provence的成员变量
	public:
		YString getProvence(void) {return m_Provence;} //读属性Provence
		void setProvence(YString newProvence) {m_Provence=newProvence;} //设置Provence

	//属性：Email
	private:
		YString m_Email; //属性Email的成员变量
	public:
		YString getEmail(void) {return m_Email;} //读属性Email
		void setEmail(YString newEmail) {m_Email=newEmail;} //设置Email

	//属性：Homepage
	private:
		YString m_Homepage; //属性Homepage的成员变量
	public:
		YString getHomepage(void) {return m_Homepage;} //读属性Homepage
		void setHomepage(YString newHomepage) {m_Homepage=newHomepage;} //设置Homepage


  public:
		YXiluUser();  //构造函数
		~YXiluUser(); //析构函数
};

#endif //__YXILUUSER_H__
