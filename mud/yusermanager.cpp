//---------------------------------------------------------------------------
//
// yusermanager.cpp    2000年6月12日
//
// 类YUserManager：负责用户的注册、登录、注销、黑名单维护等工作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YUserManager构造函数
YUserManager::YUserManager()
{
}
//---------------------------------------------------------------------------
//YUserManager析构函数
YUserManager::~YUserManager()
{
}
//---------------------------------------------------------------------------
YUser* YUserManager::login(YString name, YString password)
{
   YXiluUser* xiluuser=g_XiluUserManager->login(name,password);
   if(!xiluuser) return NULL;

   YUser* user=new YUser(xiluuser);
   delete xiluuser;

   user->setUserManager(this);
   return user;
}
