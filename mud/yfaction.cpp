//---------------------------------------------------------------------------
//
// yfaction.h    2001年6月18日
//
// 类YFaction：玩家帮派
//
// 作者：张勇  单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YFaction::YFaction(YString filename)
  : YMUDObject(filename),m_FactionList(""),m_FactionAmount(0)
{
  disableTimer();
}
//---------------------------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YFaction::isTypeOf(YString className)
{
  if(className=="YFaction") return 1;
  else return YMUDObject::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YFaction::onAfterLoad(void)
{
  int retVal=YMUDObject::onAfterLoad();
  
  setFactionList(getAsString("帮派列表"));
  setFactionAmount(getAsLong("帮派总数"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YFaction::onBeforeSave(void)
{
  int retVal=YMUDObject::onBeforeSave();
  
  set("帮派列表",getFactionList());
  set("帮派总数",getFactionAmount());
  
  return retVal;
}

//---------------------------------------------------------------------------
//添加新帮派
int YFaction::fnAddFaction(YString name)
{
  if(isFacionExisting(name) == 1) return -1;  //表示该帮派已经存在
  setFactionList(name+" "+getFactionList());  //"帮派列表"
  setFactionAmount(getFactionAmount()+1);     //"帮派总数"
  return 1; //表示已经添加
}
//---------------------------------------------------------------------------
//减去一个帮派
int YFaction::fnSubFaction(YString name)
{
  if(isFacionExisting(name) != 1) return -1;  //表示该帮派不存在，返回
  YString sFactionList=getFactionList();      //"帮派列表"
  sFactionList.removeWord(name);  //删除一个字符串
  setFactionList(sFactionList);               //"帮派列表"
  setFactionAmount(getFactionAmount()-1);     //"帮派总数"
  return 1; //表示已经添加
}
//---------------------------------------------------------------------------
//帮派是否存在？
int YFaction::isFacionExisting(YString name)
{
  YString sFactionList=getFactionList();      //"帮派列表"
  int i=0;
  YString sFactionName;
  while((sFactionName=sFactionList.getWord())!=""){
    if(sFactionName == name){
      i=1;
      break;
    }
  }
  if(i==1) return 1; //表示该帮派名字已经存在
  else return 0;      //表示不存在
}
//---------------------------------------------------------------------------
//设置帮派的口号
int YFaction::fnSetFacionBanner(YString name,YString banner)
{
  set(name+"_口号",banner);
}
//---------------------------------------------------------------------------
//得到帮派的口号
YString YFaction::fnGetFacionBanner(YString name)
{
  return getAsString(name+"_口号");
}
//---------------------------------------------------------------------------
//设置帮派的帮主
int YFaction::fnSetFacionOwner(YString name,YString owner)
{
  set(name+"_帮主",owner);
}
//---------------------------------------------------------------------------
//得到帮派的帮主
YString YFaction::fnGetFacionOwner(YString name)
{
  return getAsString(name+"_帮主");
}
//---------------------------------------------------------------------------
//设置帮派的颜色
int YFaction::fnSetFacionColor(YString name,YString color)
{
  set(name+"_帮派颜色",color);
}
//---------------------------------------------------------------------------
//得到帮派的颜色
YString YFaction::fnGetFacionColor(YString name)
{
  return getAsString(name+"_帮派颜色");
}
//---------------------------------------------------------------------------
//设置帮派的玩家数量
int YFaction::fnSetPlayerAmount(YString name,long amount)
{
  set(name+"_人数",amount);
}
//---------------------------------------------------------------------------
//得到帮派的玩家数量
long YFaction::fnGetPlayerAmount(YString name)
{
  return getAsLong(name+"_人数");
}
//---------------------------------------------------------------------------
//设置帮派的势力值
int YFaction::fnSetFactionPower(YString name,long sub,long add)
{
  long power=getAsLong(name+"_势力值");
  power=power-sub+add;
  if(power<0) power=0;
  set(name+"_势力值",power);
}
//---------------------------------------------------------------------------
//得到帮派的势力值
long YFaction::fnGetFactionPower(YString name)
{
  return getAsLong(name+"_势力值");
}
//---------------------------------------------------------------------------
//设置帮派的团结度
int YFaction::fnSetFactionClose(YString name,long close)
{
  set(name+"_团结度",close);
}
//---------------------------------------------------------------------------
//得到帮派的团结度
long YFaction::fnGetFactionClose(YString name)
{
  return getAsLong(name+"_团结度");
}
//---------------------------------------------------------------------------
//设置帮派的状态
int YFaction::fnSetFacionStatus(YString name,YString status)
{
  set(name+"_状态",status);
}
//---------------------------------------------------------------------------
//得到帮派的状态
YString YFaction::fnGetFacionStatus(YString name)
{
  return getAsString(name+"_状态");
}
//---------------------------------------------------------------------------
//帮派增加一人
int YFaction::fnFacionAddPlayer(YString name,YString playername)
{
  if(isFacionPlayerExisting(name,playername) == 1) return -1;  //表示该成员已经存在
  if (sizeof(getAsString(name+"_成员列表")) >= 1000 ) return -2;//超出字符的范围
  set(name+"_成员列表",playername+" "+getAsString(name+"_成员列表"));
  fnSetPlayerAmount(name,fnGetPlayerAmount(name)+1); //帮派人数+1
  return 1;
}
//---------------------------------------------------------------------------
//帮派减少一人
int YFaction::fnFacionSubPlayer(YString name,YString playername)
{
  if(isFacionPlayerExisting(name,playername) != 1) return -1;  //表示该成员不存在
  YString sPlayerList=getAsString(name+"_成员列表");
  sPlayerList.removeWord(playername);  //删除一个字符串
  set(name+"_成员列表",sPlayerList);
  fnSetPlayerAmount(name,fnGetPlayerAmount(name)-1);  //帮派人数-1
  return 1; //表示已经添加
}
//---------------------------------------------------------------------------
//帮派成员是否存在？
int YFaction::isFacionPlayerExisting(YString name,YString playername)
{
  YString sPlayerList=getAsString(name+"_成员列表");
  int i=0;
  YString sPlayerName;
  while((sPlayerName=sPlayerList.getWord())!=""){
    if(sPlayerName == playername){
      i=1;
      break;
    }
  }
  if(i==1) return 1; //表示该帮派名字已经存在
  else return 0;      //表示不存在
}
//---------------------------------------------------------------------------
//删除一个帮派
int YFaction::fnRemoveFaction(YString name)
{
  YString sFactionName=name;
  fnSubFaction(sFactionName);  //减去一个帮派
  fnSetFacionOwner(sFactionName,"");  //帮主
  fnSetFacionBanner(sFactionName,""); //口号
  fnSetFacionColor(sFactionName,"");  //帮派颜色
  set(sFactionName+"_势力值",0);      //势力值
  fnSetFactionClose(sFactionName,0);  //团结度
  fnSetFacionStatus(sFactionName,"已经解散"); //状态
  time_t t=time(0);
  YString sDisbandTime=(YString)ctime(&t);
  int pos=0;
  if((pos=sDisbandTime.find("\n",pos))!=YString::npos) {
    sDisbandTime.erase(pos,1);
  }       //删除"\n"
  set(sFactionName+"_解散时间",sDisbandTime); //解散时间
  YPlayer *player;
  YString sPlayerList=getAsString(sFactionName+"_成员列表");
  long nCount=fnGetPlayerAmount(sFactionName);  //帮派的人数
  YString sPlayerName;  //帮派成员名字
  YChat* pFactionChat;  //帮派频道
  for(int i=0;i<nCount;i++){
    sPlayerName=sPlayerList.getWord();
    if(sPlayerName=="") break;
    player=g_PlayerManager->getPlayer(sPlayerName); //全局找这个玩家
    if(!player) continue;
    player->setFactionName("");       //"加入帮派"
    player->setFactionTitle("");      //"帮派头衔"
    player->setOldPower(0);           //"上次势力"
    player->setIsFactionOwner(0);     //"是否帮主"
    player->set("加入_"+sFactionName,"");
    pFactionChat=player->getFactionChat(); //得到对方身上存的频道指针
    if(!pFactionChat) continue;
    pFactionChat->unsubscribe(player);    //退订频道
    player->setFactionChat(NULL);         //频道指针请空
  }
  set(sFactionName+"_成员列表","");   //成员列表清空
  fnSetPlayerAmount(sFactionName,0);  //人数清0
  return 1;
}


