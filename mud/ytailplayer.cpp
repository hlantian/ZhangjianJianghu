//---------------------------------------------------------------------------
//
// YTailPlayer.cpp    2001年7月10日
//
// 类YTailPlayer：监视玩家
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#include "webmud.h"

//--------------------------------------------------------
//构造函数
YTailPlayer::YTailPlayer(YUser* user, YString initFileName): YPlayer(user, initFileName),
 tailplayerlog (g_Settings->getRootPath()+
                        g_Settings->getPathSeparator()+
                        "tailplayer"+g_Settings->getPathSeparator()+
                        getAsString("名字")+".log")
{
}
//--------------------------------------------------------
//析构函数
YTailPlayer::~YTailPlayer()
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YTailPlayer::isTypeOf(YString className)
{
  if(className=="YTailPlayer") return 1;
  else return YPlayer::isTypeOf(className);
}
//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YTailPlayer::executeCommand(YString command)
{
        tailplayerlog.write(command);   //监视玩家的命令
        return YPlayer::executeCommand(command);        //由player处理
}
//----------------------------------------------------------------------
