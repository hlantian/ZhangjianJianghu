//---------------------------------------------------------------------------
//
// YJollityRoom.cpp    2000年9月16日
//
// 类YJollityRoom：结婚开酒席的房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YJollityRoom::isTypeOf(YString className)
{
  if(className=="YJollityRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件onTimer的默认处理函数
int YJollityRoom::onTimer(void)
{
  //YRoom::onTimer(); //首先调用父类的处理函数
  long turnon = getAsLong("开席"); //是否是开席
  //由于在开酒宴的时候刷新可能有问题，所以没开时继承omtime
  if (turnon == 1) //开席
  {
     long timelost = getAsLong ("开席时间");
     if (timelost > 0)
     {
        set ("开席时间" , timelost - getSmallTime());
     }
     else //到关席时间了
     {
        YString myname = getAsString("开席人名");
        myname ="<font color = #63B8FF>"+  myname +"的酒宴结束了。。。</font>";
        set ("开席",0);
        g_SystemChat-> talk(NULL,myname,NULL,NULL,CHANNEL_MSG);
     }
  }
  else
  {
    YRoom::onTimer(); //首先调用父类的处理函数
  }
  return 1;
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YJollityRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="eat") retVal=eat(executor,cmd);
  else if(commandVerb=="drink") retVal=drink(executor,cmd);
  else if(commandVerb=="kill") retVal=kill(executor,cmd);
  else if(commandVerb=="killget") retVal=kill(executor,cmd);
  else if(commandVerb=="killge") retVal=kill(executor,cmd);
  else if(commandVerb=="touxi") retVal=kill(executor,cmd);
  else if(commandVerb=="fight") retVal=kill(executor,cmd);
  else if(commandVerb=="hit") retVal=kill(executor,cmd);
  else if(commandVerb=="dazuo") retVal=dazuo(executor,cmd);
  else if(commandVerb=="tuna") retVal=tuna(executor,cmd);
//  else if(commandVerb=="look") retVal=look(executor,cmd);
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}

//--------------------------------------------------------
//吃
int YJollityRoom::eat(YAbstractActor* executor,YString command)
{
  if (getAsLong("开席") != 1) //没有人开席
  {
     return 0;//不处理返回让player处理
  }
  YString allfood = getAsString("房间内食物");
  if (allfood.find(command,0) != YString::npos);
  else
  {
    executor -> display ("酒宴里没有这种东西啊！");
    return 1;
  }
  YAbstractThing* loadthing=(YAbstractThing*)loadObject("thing/"+command);
  if ( !loadthing )
  {
     g_err.show("[YJollityRoom::eat]load"+command+"出错。");
     return 1;
  }
  long food ;
  YPlayer* tempexecutor;
  if (executor->isTypeOf("YPlayer")) tempexecutor = (YPlayer*)executor;
  else return 1;
  if ( loadthing->getAsLong("食物") == 1 )
  {
     food = tempexecutor -> getFood();//getAsLong("食物");
     if (food >= tempexecutor->getMaxFood())//getAsLong("最大食物"))
     {
       executor->display ("你吃的已经是够饱的了，再也不能吃东西了。");
       return 1 ;
     }
     getRoomChat()->talk(NULL,executor->getObjectName()+"咬了几口"+command+"。",NULL, NULL);
     tempexecutor->setFood(food+50);//set("食物",  );
  }
  /*else if ( loadthing->getAsLong("饮水") == 1 )
  {
     food = executor -> getAsLong("饮水");
     if (food >= executor->getAsLong("最大饮水"))
     {
       executor->display ("你喝的已经是够饱的了，再也不能喝下什么了。");
       return 1 ;
     }
     getRoomChat()->talk(NULL,executor->getAsString("名字")+"喝了几口"+command+"。",NULL, NULL);
     executor->set("饮水", food+50 );
  }     */
  if(removeChild(loadthing))
  {
    delete loadthing;
  }
  else  g_err.show("[YJollityRoom::eat]delete"+command+"出错。");
  return 1;
}
//--------------------------------------------------------
//喝
int YJollityRoom::drink(YAbstractActor* executor,YString command)
{
  if (getAsLong("开席") != 1) //没有人开席
  {
     return 0;//不处理返回让player处理
  }
  YString allfood = getAsString("房间内食物");
  if (allfood.find(command,0) != YString::npos);
  else
  {
    executor -> display ("酒宴里没有这种东西啊！");
    return 1;
  }
  YPlayer* tempexecutor;
  if (executor->isTypeOf("YPlayer")) tempexecutor = (YPlayer*)executor;
  else return 1;
  YAbstractThing* loadthing=(YAbstractThing*)loadObject("thing/"+command);
  if ( !loadthing )
  {
     g_err.show("[YJollityRoom::eat]load"+command+"出错。");
     return 1;
  }
  long food ;
  /*if ( loadthing->getAsLong("食物") == 1 )
  {
     food = executor -> getAsLong("食物");
     if (food >= executor->getAsLong("最大食物"))
     {
       executor->display ("你吃的已经是够饱的了，再也不能吃东西了。");
       return 1 ;
     }
     getRoomChat()->talk(NULL,executor->getAsString("名字")+"咬了几口"+command+"。",NULL, NULL);
     executor->set("食物", food+50 );
  } */
  if ( loadthing->getAsLong("饮水") == 1 )
  {
     food = tempexecutor ->getDrink();// getAsLong("饮水");
     if (food >= tempexecutor->getMaxDrink())//getAsLong("最大饮水"))
     {
       executor->display ("你喝的已经是够饱的了，再也不能喝下什么了。");
       return 1 ;
     }
     getRoomChat()->talk(NULL,executor->getObjectName()+"喝了几口"+command+"。",NULL, NULL);
     tempexecutor->setDrink(food+50);//set("饮水", food+50 );
  }
  if(removeChild(loadthing))
  {
    delete loadthing;
  }
  else  g_err.show("[YJollityRoom::eat]delete"+command+"出错。");
  return 1;
}
//--------------------------------------------------------
//杀
int YJollityRoom::kill(YAbstractActor* executor,YString command)
{
  YString killmiaoshu = getAsString ("主动杀人");
  getRoomChat()->talk(NULL,killmiaoshu,NULL, NULL);
  ((YPlayer*)executor)-> gotoRoom ("/room/长安/黑牢");
  ((YPlayer*)executor) -> faint();
  return 1;
}
//--------------------------------------------------------
//打坐
int YJollityRoom::dazuo(YAbstractActor* executor,YString command)
{
  YString liangongmiaoshu = getAsString ("练功显示");
  getRoomChat()->talk(NULL,liangongmiaoshu,NULL, NULL);
  ((YPlayer*)executor) -> gotoRoom ("/room/长安/钟楼");
  return 1;
}
//--------------------------------------------------------
//吐纳
int YJollityRoom::tuna(YAbstractActor* executor,YString command)
{
  YString liangongmiaoshu = getAsString ("练功显示");
  getRoomChat()->talk(NULL,liangongmiaoshu,NULL, NULL);
  ((YPlayer*)executor) -> gotoRoom ("/room/长安/钟楼");
  return 1;
}
/*
//--------------------------------------------------------
//看
int YJollityRoom::look(YAbstractActor* executor,YString command)
{
  return 0;
}  */


