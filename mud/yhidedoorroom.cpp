//---------------------------------------------------------------------------
//
// yhidedoorroom.cpp    2001年7月10日
//
// 类YHideDoorRoom：含有隐藏方向的需要条件的房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YHideDoorRoom::YHideDoorRoom(YString initFileName):YRoom(initFileName)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YHideDoorRoom::isTypeOf(YString className)
{
  if(className=="YHideDoorRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YHideDoorRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();

  return retVal;
}
//------------------------------------------
//时间onBeforeSave的默认处理函数
int YHideDoorRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();

  return retVal;
}
//--------------------------------------------------------
//事件onAfterLeave的默认处理函数
int YHideDoorRoom::onAfterLeave(YMUDObject* sender, YAbstractActor* actor)
{
    int retVal=YRoom::onAfterLeave(sender, actor);
    actor->set("准备开始",0);
    return retVal;
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YHideDoorRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(getAsString("准备命令") == commandVerb) retVal=readly(executor,cmd);
  else if ((getAsString("隐藏前进命令") == commandVerb)||("go" == commandVerb)) retVal=next(executor,cmd);
  else {
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//----------------------------------------------------------------
//准备可以行动的属性
int YHideDoorRoom::readly(YAbstractActor* executor,YString command)
{
    YPlayer* player;
    if(executor->isTypeOf("YPlayer")) player = (YPlayer*) executor;
    else return 0;
    if (getAsString("准备对象") == command)
    {
      //需要的条件
      YString wieldneed =  getAsString ("准备条件");
      YString tempneed = wieldneed.getWord() ;
      while ( tempneed!= "" )
      {
        //如果出现问题要先进行save
        long longneed =  getAsLong (tempneed);
        YString strneed =  getAsString (tempneed);
        if (strneed != "" )//字符的条件
        {
          if ( player->getAsString(tempneed)  != strneed )
          {
             player->display (getAsString("准备失败后显示"));
             //player->display ("你的"+tempneed+"不是"+strneed);
             return 1;
          }
        }
        else if (longneed != 0)
        {
          if (player->getAsLong(tempneed) < longneed)
          {
             player->display (getAsString("准备失败后显示"));
             //player->display ("你的"+tempneed+"还没有到达"+(YString)longneed);
             return 1;
           }
        }
        tempneed = wieldneed.getWord() ;
      }

       player->set ("准备开始",1);
       player->display (getAsString("准备成功后显示"));
       return 1;
    }
    else return 0;
}
//-----------------------------------------------------------------
//要有第一步准备后才可以实行的去别的房间的命令
int YHideDoorRoom::next(YAbstractActor* executor,YString command)
{
    YPlayer* player;
    if(executor->isTypeOf("YPlayer")) player = (YPlayer*) executor;
    else return 1;
    if (getAsString("限制前进方向") == command)
    {
      if (executor->getAsLong("准备开始") != 1)
      {
        player -> display("这个方向没有出路");
        return 1;
      }
      //需要的条件
      YString wieldneed =  getAsString ("进入条件");
      YString tempneed = wieldneed.getWord() ;
      while ( tempneed!= "" )
      {
        //如果出现问题要先进行save
        long longneed =  getAsLong (tempneed);
        YString strneed =  getAsString (tempneed);
        if (strneed != "" )//字符的条件
        {
          if ( player->getAsString(tempneed)  != strneed )
          {
             player->display(getAsString("失败通过后显示"));
             //player->display ("你的"+tempneed+"不是"+strneed);
             return 1;
          }
        }
        else if (longneed != 0)
        {
          if (player->getAsLong(tempneed) < longneed)
          {
             player->display(getAsString("失败通过后显示"));
             //player->display ("你的"+tempneed+"还没有到达"+(YString)longneed);
             return 1;
           }
        }
        tempneed = wieldneed.getWord() ;
      }
      player->display(getAsString("成功通过后显示"));

        if (sendActorTo(((YActor*)executor),command)==0)
        {
        }
        else player->display(getAsString("失败通过后显示"));
        return 1;
    }
    return 0;
}
