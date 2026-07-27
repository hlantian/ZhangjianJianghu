//---------------------------------------------------------------------------
//
// ydoorroom.cpp    2001年5月22日
//
// 类YDoorRoom：有守门NPC的Room
//
// 作者：刘鹏 张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YDoorRoom::YDoorRoom(YString initFileName):YRoom(initFileName)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YDoorRoom::isTypeOf(YString className)
{
  if(className=="YDoorRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YDoorRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YDoorRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();

  return retVal;
}

//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YDoorRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="go") retVal=fnWantGo(executor,cmd);  //cmd 为 "东"....等
    
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//玩家要走
int YDoorRoom::fnWantGo(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString cmd=command.getWord();
  YString sForbidDirection=getAsString("禁止方向列表");
  YString sDirection;
  while((sDirection=sForbidDirection.getWord())!=""){
    if(cmd == sDirection){  //说明该方向被禁止
      if(getAsLong("玩家帮派大门") == 1){
        YString sFactionName=getAsString("玩家帮派名字");
        if((sFactionName == "") || (g_Faction->isFacionExisting(sFactionName) != 1)){
          player->display("这个帮会的总舵暂时关闭了！");
          return 1;
        }
        if(player->getFactionName() == sFactionName){     //"加入帮派"
          player->display("<font color=green>欢迎回到["+sFactionName+"]总舵！</font>");
          return 0;
        }
        long nCount;
        if((nCount=player->getAsLong("邀请参观次数_"+sFactionName)) > 0){
          if(nCount != 99){ //99表示永远允许进入
            nCount--; //减少一次
            player->set("邀请参观次数_"+sFactionName,nCount);
          }
          player->display("<font color=green>欢迎光临["+sFactionName+"]总舵！</font>");
          return 0;
        }
        else{
          player->display("["+sFactionName+"]总舵，闲人免进！");
          return 1;
        }
      }
      if (getAsLong("没有守卫") == 1 )
      {
         YString goneed = getAsString ("通过条件");
         if (goneed != "") player->onBeforeSave();
         YString tempneed = goneed.getWord() ;
         while ( tempneed!= "" )
         {
            //如果出现问题要先进行save
            long longneed = getAsLong (tempneed);
            YString strneed = getAsString (tempneed);
            if (strneed != "" )//字符的条件
            {
                if (player->getAsString(tempneed)  != strneed )
                {
                        YString shuohua = getAsString("不能通过显示");
                        if (shuohua == "") shuohua = "你的"+tempneed+"不是"+strneed;
                        player->display (shuohua);
                        return 1;
                }
            }
            else if (longneed != 0)
            {
                if (player->getAsLong(tempneed) < longneed)
                {
                        YString shuohua = getAsString("不能通过显示");
                        if (shuohua == "") shuohua = "你的"+tempneed+"还没有到达"+(YString)longneed;
                        player->display (shuohua);
                        return 1;
                }
            }
            tempneed = goneed.getWord() ;
         }
      }
      YString sBossName=getBossName();  //"老板名字",得到守门NPC的名字列表
      YString sNPCName;
      while((sNPCName=sBossName.getWord())!=""){
        YAbstractActor *pAbstractActor=findChildActor(sNPCName);  //寻找守门NPC
        if(pAbstractActor){ //如果该NPC活着
          if(pAbstractActor->isTypeOf("YNPC")){ //如果的确是NPC
            YNPC *pNPC=(YNPC*)pAbstractActor;   //强制转换为NPC类
            if((pNPC->getStatus())!="晕倒中"){  //NPC没有晕倒
              if(pNPC->conditionEstimation(player,"玩家要走") == 1) return 1; //条件不满足，被拒绝
              if(getAsLong("禁止所有人")==1){
                YString sAlertMessage=getAsString(sNPCName+"警告信息");
                if(sAlertMessage == "") sAlertMessage=sNPCName+"挡住了你的去路。"; //默认信息
                player->display(sAlertMessage); //显示
                return 1; //处理完毕
              }
            }
          }
        }
      }
    }
  }
  return 0; //未被禁止，继续执行
}

