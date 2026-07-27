//---------------------------------------------------------------------------
//
// yjailroom.cpp    2001年2月19日
//
// 类YJailRoom：监狱
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YJailRoom::isTypeOf(YString className)
{
  if(className=="YJailRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YJailRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="say") retVal=0;
  else if(commandVerb=="tell") retVal=0;
  else if(commandVerb=="wizgoto") retVal=0;
  else if(commandVerb=="wizkick") retVal=0;
  else if(commandVerb=="wizchat") retVal=0;
  else if(commandVerb=="wizget") retVal=0;
  else if(commandVerb=="goto") retVal=0;
  else if(commandVerb=="wizlook") retVal=0;
  else retVal=jail(executor);
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//坐牢中
int YJailRoom::jail(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  player->display("你目前被监禁中，不能使用这个命令。");
  return 1;
}

