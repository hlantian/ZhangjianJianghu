//---------------------------------------------------------------------------
//
// yusermanager.h    2000年6月12日
//
// 类YUserManager：负责用户的注册、登录、注销、黑名单维护等工作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YUSERMANAGER_H__
#define __YUSERMANAGER_H__

#include "yuser.h"

class YUserManager {
  public:
		YUserManager();  //构造函数
		~YUserManager(); //析构函数

    YUser* login(YString name, YString password);
};

#endif //__YUSERMANAGER_H__
