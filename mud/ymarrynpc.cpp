//---------------------------------------------------------------------------
//
// YMarryNPC.cpp    2000年10月16日
//
// 类YMarryNPC：媒婆NPC
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YMarryNPC::isTypeOf(YString className)
{
  if(className=="YMarryNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YMarryNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="ask") retVal=Ask(executor,cmd);//被询问
  else if(commandVerb=="give") retVal=Give(executor,cmd);//别人给东西

  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}
//---------------------------------------------------------
//事件RoommateEnter的默认处理函数
int YMarryNPC::onRoommateEnter(YMUDObject* sender,YAbstractActor* actor)
{
  YActor::onRoommateEnter(sender,actor); //首先调用父类的处理函数

  YPlayer* player;
  if(actor->isTypeOf("YPlayer")) player=(YPlayer*)actor;
  else return 1;
  if(getAsLong("进入时说话")!=1) return 1;
  YString msg=getAsString("进入时说话内容"); //进入时所说的话
  if(msg!="") OutputMsg(player,msg);
  return 1;
}
//--------------------------------------------------------
//被询问
int YMarryNPC::Ask(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1; //判断过空了
  YString cmd=command;
  YString marryNpc=cmd.getWord();//被ask的对象
  YString isabout=cmd.getWord();//单词about
  YString abouthing=cmd.getWord();//询问的内容
  if (isabout != "about") player->display ("格式不正确。正确格式为ask XXX about 问题");
  YString reply = getAsString (abouthing);
  if ( reply == "")
  {
    player -> display (marryNpc+"想了想说道：这个啊，我不清楚了，你问问别人吧。");
    return 1;
  }
  else player->display (marryNpc+reply);
  return 1;
}
//--------------------------------------------------------
//别人给东西 give (count) sth. to sb.
int YMarryNPC::Give(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString danwei =  command.getWord();
  long howmuch =  (command.getWord()).toLong();
  YString isto = command.getWord();
  YString NpcName = command.getWord();
  if (danwei != getAsString("货币种类"))
  {
    player -> display (NpcName+getAsString("货币种类不对时说话"));
    return 1;
  }
  if (howmuch < getAsLong("最小收费"))
  {
    player -> display (NpcName+getAsString("小于最少收费时说话"));
    return 1;
  }
  YAbstractThing* givething=player->findChildThing(danwei);
  if ( givething == NULL)
  {
    player->display (NpcName+getAsString("没钱时的说话"));
    return 1;
  }
  int thingcount = givething->getCount();
  if ( thingcount < howmuch )
  {
    player -> display (NpcName+getAsString("钱不够时说话"));
    return 1;
  }
  if  (thingcount-howmuch == 0)
  {
    if(removeChild(givething))
    {
      delete givething;
    }
  }
  else  givething->setCount( thingcount-howmuch );
  if (player -> getAsString("配偶") != "")
  {
     if (getAsLong("办理离婚") == 1 )  //处理离婚的时候的给钱问题
     {
         player ->  set("离婚步骤",1);
         getRoom()->getRoomChat()->talk(NULL,getAsString("离婚开始说话"),NULL, NULL);
         return 1;
     }
     player -> display (NpcName+getAsString("有配偶时说话"));
     return 1;
  }
  //物品的给出
  player ->display (NpcName+getAsString("条件符合时说话")) ;
  player -> set ("结婚步骤",1);
  getRoom()->getRoomChat()->talk(NULL,getAsString("给钱成功后说话"),NULL, NULL);
  return 1;
}


