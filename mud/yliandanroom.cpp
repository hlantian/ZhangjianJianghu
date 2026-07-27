//---------------------------------------------------------------------------
//
// yliandanroom.h    2001年7月17日
//
// 类YLIAMDANROOM：生成丹药的房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YLianDanRoom::YLianDanRoom(YString initFileName):YRoom(initFileName)

{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YLianDanRoom::isTypeOf(YString className)
{
  if(className=="YLianDanRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YLianDanRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
