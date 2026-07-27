//---------------------------------------------------------------------------
//
// yxiluusermanager.h    2000年6月12日
//
// 类YXiluUserManager：负责西陆用户的检查
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YXILUUSERMANAGER_H__
#define __YXILUUSERMANAGER_H__

#include "ystring.h"
#include "yxiluuser.h"

class YXiluUserManager {
  private:

  protected:

  public:
		YXiluUserManager();  //构造函数
		~YXiluUserManager(); //析构函数
    YXiluUser* login(YString name, YString password);
};

#endif //__YXILUUSERMANAGER_H__
