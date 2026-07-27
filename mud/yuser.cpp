//---------------------------------------------------------------------------
//
// yuser.cpp    2000年6月12日
//
// 类YUser：系统用户
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YUser构造函数
YUser::YUser()
{
  this->setLevel(0);
  this->setLevelString("平民");
}
//---------------------------------------------------------------------------
//构造函数(通过西陆用户构造)
YUser::YUser(YXiluUser* xiluuser)
{
  this->setXiluUserManager(xiluuser->getXiluUserManager());
  this->setName(xiluuser->getName());
  this->setPassword(xiluuser->getPassword());
  this->setEncryptedPassword(xiluuser->getEncryptedPassword());
  this->setSex(xiluuser->getSex());
  this->setAge(xiluuser->getAge());
  this->setProvence(xiluuser->getProvence());
  this->setEmail(xiluuser->getEmail());
  this->setHomepage(xiluuser->getHomepage());

  this->setLevel(0);
  this->setLevelString("平民");
}
//---------------------------------------------------------------------------
//YUser析构函数
YUser::~YUser()
{
}
//---------------------------------------------------------------------------
//读属性LevelString
YString YUser::getLevelString(void)
{
  char s[33];
  sprintf(s,"%d",getLevel());
  return YString(s);
}
//---------------------------------------------------------------------------
//设置LevelString
void YUser::setLevelString(YString newLevelString)
{
}
