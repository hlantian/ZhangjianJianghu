//---------------------------------------------------------------------------
//
// yxiluusermanager.cpp    2000年6月12日
//
// 类YXiluUserManager：负责西陆用户的检查
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YXiluUserManager构造函数
YXiluUserManager::YXiluUserManager()
{
}
//---------------------------------------------------------------------------
//YXiluUserManager析构函数
YXiluUserManager::~YXiluUserManager()
{
}
//---------------------------------------------------------------------------
YXiluUser* YXiluUserManager::login(YString name, YString password)
{     //错误，这段应放在login.cpp中

  YXiluUser* user=new YXiluUser;
	user->setXiluUserManager(this);
	user->setName(name);
	//user->setSex(row[1]);
	user->setPassword(password);
	//user->setEncryptedPassword(cryptpass_c);
	return user;
}
