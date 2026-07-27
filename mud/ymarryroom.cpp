//---------------------------------------------------------------------------
//
// YMarryRoom.cpp    2001年2月13日
//
// 类YMarryRoom：结婚系统使用房间
//
// 作者：刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YMarryRoom::isTypeOf(YString className)
{
  if(className=="YMarryRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YMarryRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="marry") retVal=marry(executor,cmd);
  else if(commandVerb=="bai") retVal=bai(executor,cmd);
  else if(commandVerb=="zeng") retVal=zeng(executor,cmd);
  else if(commandVerb=="xian") retVal=xian(executor,cmd);
  else if(commandVerb=="qing") retVal=qing(executor,cmd);
  else if(commandVerb=="请") retVal=qing(executor,cmd);
  else if(commandVerb=="unmarry") retVal=unmarry(executor,cmd);
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}

//--------------------------------------------------------
//marry sb. 要查媒婆 (写入房间属性)
int YMarryRoom::marry(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  if (player -> getAsString("配偶") !="")
  {
    player ->display ("你一个结过婚的人在这里捣什么乱啊！！");
    return 1;
  }
  if (player -> getSexString() == "男")
  {
    if (player -> getActorAge() < getAsLong("男结婚年龄"))
    {
       player -> display (getAsString("男年龄不够时说话"));
       return 1;
    }
  }
  else if (player -> getSexString() == "女")
  {
    if (player -> getActorAge() < getAsLong("女结婚年龄"))
    {
       player -> display (getAsString("女年龄不够时说话"));
       return 1;
    }
  }
  YString needNPCname = getAsString ("需要NPC名称");
  YString condition = getAsString ("需要条件");
  long isture =  player->getAsLong (condition);
  if ( !isture )
  {
     player -> display ("你还没有给"+needNPCname+"交钱哪，");
     return 1;
  }
  else if ( isture > 1 ) //结婚步骤已经完成了
  {
     player -> display ("你现在该拜天地了啊！！");
     return 1;
  }
  YMUDObject* sb=findChildActor(needNPCname);
  if (!sb) //没有NPC的处理
  {
     player -> display (getAsString("没有NPC的情况"));
     return 1;
  }
  YString NPCnow = ((YActor*)sb)->getStatus();//getAsString ("状态");
  if (NPCnow == "晕倒中")
  {
    player -> display ("你先把"+needNPCname+"救醒再说吧");
    return 1;
  }
  else if ( NPCnow != "")
  {
    player -> display (needNPCname+"对你说道：等我忙完了再说。");
    return 1;
  }
  YPlayer* wantmarry;
  YMUDObject* marryply=findChildActor(command);
  if (!marryply)
  {
    player->display ("和你结婚的人没有再这里啊！");
    return 1;
  }
  if  (marryply->isTypeOf("YPlayer")) wantmarry=(YPlayer*)marryply; //换为player
  else
  {
    player -> display ("你不能和"+command+"结婚。");
    return 1;
  }
  if (player ->getSexString() == ((YActor*)marryply)->getSexString())//getAsString("性别"))
  {
    player -> display (needNPCname+"叹了一口气：唉，你们这等新式婚姻还是往别处去吧。");
    return 1;
  }
  player->set ("结婚对象",command);
  YString playername = player->getActorName();//getAsString("名字");
  if ( wantmarry -> getAsString("结婚对象") != playername) //第一个人下marry
  {
     wantmarry -> display( playername+"正等着和你结婚，请对"+playername+"下一次 marry "+playername+"命令。" );
     player ->  display ("你焦急的等待着"+command+"对你的回答。");
     return 1;
  }
  else // 第二个人下marry
  {
     wantmarry -> display (playername+"同意和你结婚了。");
     player -> display("你同意了"+command+"的要求，准备和他结婚了。");
     wantmarry -> display("<font color=#990000>一拜天地！</font>");
     wantmarry -> set (condition,2);
     getRoomChat()->talk(NULL,getAsString("两人都同意后显示1"),NULL, NULL);
     getRoomChat()->talk(NULL,getAsString("两人都同意后显示2"),NULL, NULL);
     getRoomChat()->talk(NULL,getAsString("两人都同意后显示3"),NULL, NULL);
     player -> display("<font color=#990000>一拜天地！</font>");
     player -> set (condition,2);
  }
  return 1;
}

//--------------------------------------------------------
//拜天地
int YMarryRoom::bai(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  //查找NPC
  YString needNPCname = getAsString ("需要NPC名称");
  YMUDObject* sb=findChildActor(needNPCname);
  if (!sb) //没有NPC的处理
  {
     player -> display (getAsString("没有NPC的情况"));
     return 1;
  }
  YString NPCnow = ((YActor*)sb)->getStatus();//getAsString ("状态");
  if (NPCnow == "晕倒中")
  {
    player -> display ("你先把"+needNPCname+"救醒再说吧");
    return 1;
  }
  else if ( NPCnow != "")
  {
    player -> display (needNPCname+"对你说道：等我忙完了再说。");
     return 1;
  }
  YString condition = getAsString ("需要条件");
  long isture =  player->getAsLong (condition);
  //查找player 的拜的步骤
  if ( !isture )
  {
     player -> display ("你又不结婚乱拜什么？");
     return 1;
  }
  YString marrywho = player -> getAsString ("结婚对象");//结婚对象
  YPlayer* wantmarry;
  YMUDObject* marryply=findChildActor(marrywho);
  if (!marryply) //对拜的人的指针
  {
    player->display ("和你对拜的人没有在这里啊！");
    return 1;
  }
  if  (marryply->isTypeOf("YPlayer")) wantmarry=(YPlayer*)marryply; //换为player
  else
  {
    player -> display ("你不能和"+marrywho+"结婚。");
    return 1;
  }
  YString playername = wantmarry->getActorName();//getAsString("名字");
  if ( marrywho != playername )
  {
    player -> display ("你不会看到什么人都想拜吧！！");
    return 1;
  }
  //开始检验对方的结婚程序
  long othture = marryply -> getAsLong (condition);
  YString sanbai; //三拜的提示语言
  YString myName = player -> getActorName();// getAsString("名字");
  if (isture < 2)
  {
    player-> display ("还没有人愿意同你结婚哪，乱拜什么啊！！");
    return 1;
  }
  //性别显示三拜的话语的不同
  YString mysex = player->getSexString();// getAsString("性别");
  if (isture == 2) //一拜天地
  {
     //一拜天地
     if ( command != "天地")
     {
        player-> display ("一拜天地，二拜高堂，然后是夫妻对拜。记住规矩，不要乐昏了头啊。");
        return 1;
     }
     //第一个人先拜天地
     if (othture == 2 )
     {
       //因为这种和fight比较相象所以不加如新的接口
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("拜天地1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("拜天地2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,3);
       wantmarry -> display (myName+"正等着和你拜天地那。");
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       return 1;
     }
     //第二个人拜天地
     else if (othture == 3 )
     {
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("拜天地1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("拜天地2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,3);
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       player ->display ("<font color=#bb0000>二拜高堂</font>");
       wantmarry ->display ("<font color=#bb0000>二拜高堂</font>");
       return 1;
     }
     else
     {
       player-> display ("程序有问题，请找巫师联系.");
       return 1;
     }
  }
  if (isture == 3) //二拜高堂
  {
     //一拜天地
     if ( command != "高堂")
     {
        player-> display ("一拜天地，二拜高堂，然后是夫妻对拜。记住规矩，不要乐昏了头啊。");
        return 1;
     }
     //第一个人先拜高堂
     if (othture == 3 )
     {
       //因为这种和fight比较相象所以不加如新的接口
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("拜高堂1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("拜高堂2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,4);
       wantmarry -> display (myName+"正等着和你拜高堂那。");
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       return 1;
     }
     //第二个人拜天地
     else if (othture == 4 )
     {
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("拜高堂1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("拜高堂2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,4);
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       player ->display ("<font color=#ff0000>夫妻对拜</font>");
       wantmarry ->display ("<font color=#ff0000>夫妻对拜</font>");
       return 1;
     }
     else if (othture == 2)//一个人手太快大的太多了
     {
       player -> display ("不要太着急了"+marrywho+"还没有拜天地哪。");
       return 1;
     }
     else
     {
       player-> display ("程序有问题，请找巫师联系.");
       return 1;
     }
  }
  if (isture == 4) //夫妻对拜
  {
     //对拜
     if ( command != marrywho)
     {
        player-> display ("一拜天地，二拜高堂，然后是夫妻对拜。记住规矩，不要乐昏了头啊。");
        return 1;
     }
     //第一个人对拜
     if (othture == 4 )
     {
       //因为这种和fight比较相象所以不加如新的接口
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("夫妻对拜1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("夫妻对拜2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,5);
       wantmarry -> display (myName+"正等着和你对拜那。");
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       return 1;
     }
     //第二个人对拜
     else if (othture == 5 )
     {
       if (mysex == "男")
       {
         sanbai = g_Wugong->fight_translate("夫妻对拜1",player,wantmarry,YWugong::OTHER) ;
       }
       else
       {
         sanbai = g_Wugong->fight_translate("夫妻对拜2",player,wantmarry,YWugong::OTHER) ;
       }
       player -> set (condition,5);
       getRoomChat()->talk(NULL,sanbai,NULL, NULL);
       //结婚程序完成设计人物属性
       wantmarry -> set ("配偶",wantmarry -> getAsString("结婚对象"));
       player -> set ("配偶", marrywho);
       //发布消息
       YString word = "<font color=#63B8FF>恭喜"+marrywho+"和"+player->getActorName()+"永结同心，百年好和。</font>";
       g_SystemChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
       return 1;
     }
     else if (othture == 3)//一个人手太快大的太多了
     {
       player -> display ("不要太着急了"+marrywho+"还没有拜高堂哪。");
       return 1;
     }
     else
     {
       player-> display ("程序有问题，请找巫师联系.");
       return 1;
     }
  }
  return 1;
}
//赠信物
int YMarryRoom::zeng(YAbstractActor* executor,YString command)
{
   YString marrywho = executor->getAsString ("配偶");
   if (marrywho == "")
   {
     executor -> display ("没有结婚你乱赠什么啊！！");
     return 1;
   }
   YString condition = getAsString ("需要条件");
   long thestep = executor ->getAsLong (condition);
   if (thestep  < 6)//第六步以前
   {
      executor -> display ("先结完婚再说了。" );
      return 1;
   }
   else if (thestep  > 6)//第六步以后
   {
      executor -> display ("你们好象已经互赠定情信物了。" );
      return 1;
   }
   //查找结婚的对象再不再
   YMUDObject* marryply=findChildActor(marrywho);
   if (!marryply) //赠物的人
   {
     executor->display (marrywho+"没有在这里啊！");
     return 1;
   }
   YPlayer* wantmarry;
   if  (marryply->isTypeOf("YPlayer")) wantmarry=(YPlayer*)marryply; //换为player
   else
   {
     executor -> display ("交换信物出错。请找巫师联系。");
     return 1;
   }
   YString sex = ((YActor*)executor) ->getSexString();// getAsString("性别");
   if (sex == "男")
   {
     executor -> display ("这好象是应该新娘子先给你的哦。");
    /* YString xinwu = g_Wugong->fight_translate("交换信物1",executor,wantmarry,YWugong::OTHER) ;
     executor -> set (condition,6);
     xinwu = executor -> getAsString("名字") +"送给"+ marrywho + "的玉配。" ;
     wantmarry -> set ("结婚信物",xinwu) ;
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = g_Wugong->fight_translate("交换信物2",wantmarry,executor,YWugong::OTHER) ;
     wantmarry -> set (condition,6);
     xinwu = marrywho + "送给"+  executor -> getAsString("名字") + "的香囊。";
     executor -> set("结婚信物",xinwu);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL); */
   }
   else if (sex == "女")
   {
     YString xinwu = g_Wugong->fight_translate("交换信物1",wantmarry,executor,YWugong::OTHER) ;
     wantmarry -> set (condition,7);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = g_Wugong->fight_translate("交换信物2",wantmarry,executor,YWugong::OTHER) ;
     executor -> set (condition,7);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = ((YActor*)executor) -> getActorName() +"送给"+ marrywho + "的香囊。" ;
     wantmarry -> set ("结婚信物",xinwu) ;
//     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = marrywho + "送给"+  ((YActor*)executor)-> getActorName() + "的玉佩。";
     executor -> set ("结婚信物",xinwu);
//     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     YString lastxianshi = getAsString("婚礼结束后描述");
     getRoomChat()->talk(NULL,lastxianshi,NULL,NULL);
     YString goroom =  getAsString("酒宴房间") ;
     ((YPlayer*)executor) -> gotoRoom (goroom);
     ((YPlayer*)wantmarry) -> gotoRoom (goroom);
   }
   else executor -> display ("交换信物中性别取值出错，请找巫师联系。");
   return 1;
}
//掀盖头
int YMarryRoom::xian(YAbstractActor* executor,YString command)
{
   YString marrywho = executor->getAsString ("配偶");
   if (marrywho == "")
   {
     executor -> display ("没有结婚你乱赠什么啊！！");
     return 1;
   }
   YString condition = getAsString ("需要条件");
   long thestep = executor->getAsLong (condition);
   if (thestep  < 5)//第五步以前
   {
      executor -> display ("还没有结完婚乱动什么啊你！" );
      return 1;
   }
   else if (thestep  > 5)//第五步以后
   {
      executor -> display ("都老夫老妻了，还要这样啊！！" );
      return 1;
   }
   //查找结婚的对象再不再
   YMUDObject* marryply=findChildActor(marrywho);
   if (!marryply) //行礼
   {
     executor->display (marrywho+"没有在这里啊！");
     return 1;
   }
   YPlayer* wantmarry;
   if  (marryply->isTypeOf("YPlayer")) wantmarry=(YPlayer*)marryply; //换为player
   else
   {
     executor -> display ("掀盖头出错。请找巫师联系。");
     return 1;
   }
   YString sex = ((YActor*)executor) ->getSexString();//getAsString("性别");
   if (sex == "男")
   {
     long marrystep =  wantmarry -> getAsLong (condition);
     if (marrystep < 5)
     {
       executor -> display ("还没有结婚成功哪，不要动手动脚的。");
       return 1;
     }
     else if (marrystep > 5)
     {
       executor -> display ("掀盖头顺序出了问题。请找巫师联系！");
       return 1;
     }
     YString xinwu = g_Wugong->fight_translate("掀盖头1",executor,wantmarry,YWugong::OTHER) ;
     executor -> set (condition,6);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = g_Wugong->fight_translate("掀盖头2",executor,wantmarry,YWugong::OTHER) ;
     wantmarry -> set (condition,6);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     /*executor -> set ("结婚信物","锦囊");
     wantmarry -> set ("结婚信物","玉佩");  */
   }
   else if (sex == "女")
   {
     executor -> display ("哪有女孩子自己去掀自己的盖头啊。。");
     /*YString xinwu = g_Wugong->fight_translate("掀盖头2",executor,wantmarry,YWugong::OTHER) ;
      set (condition,7);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     xinwu = g_Wugong->fight_translate("掀盖头1",wantmarry,executor,YWugong::OTHER) ;
     wantmarry -> set (condition,7);
     getRoomChat()->talk(NULL,xinwu,NULL, NULL);
     executor -> set ("结婚信物","玉佩");
     wantmarry -> set ("结婚信物","锦囊");  */
   }
   else executor -> display ("掀盖头中性别取值出错，请找巫师联系。");
   return 1;
}
//---------------------------------------------------------------------------------
//请宾客
int YMarryRoom::qing(YAbstractActor* executor,YString command)
{
   if (executor -> getAsLong("结婚步骤")  != 1)
   {
       executor -> display ("宾客要在结婚前到场的啊。");
       return 1;
   }
   YActor* sb=g_PlayerManager->getActor(command);
   if( !sb )//没有人物
   {
     executor -> display (getAsString("请的人物没有在线"));
     return 1;
   }
   executor -> display (getAsString("请的人在线"));
   YString miaoshu = ((YActor*)executor) ->getActorName();//getAsString("名字");
   miaoshu = miaoshu + getAsString("邀请话语");
   sb -> display (miaoshu);
   return 1;
}
//-------------------------------------------------------------------------------
//离婚
int YMarryRoom::unmarry(YAbstractActor* executor,YString command)
{
  if (executor -> isTypeOf("YPlayer"))
  {
    YPlayer* thisplayer = (YPlayer*)executor ;
    if ((executor-> getAsLong ("离婚步骤")) > 0)
    {
        if  (executor->getAsString("配偶") != command )
        {
          thisplayer->display ("夫妻俩个人都在才能离婚!");
          return 1;
        }
        YMUDObject* unmarryplayer=findChildActor(command);
        if (!unmarryplayer)
        {
          thisplayer->display ("夫妻俩个人都在才能离婚!");
          return 1;
        }
        if (unmarryplayer ->isTypeOf("YPlayer"))
        {
          YPlayer* thatplayer = (YPlayer*)unmarryplayer ;
          long step =  unmarryplayer->getAsLong("离婚步骤");
          if ( step == 0 || step == 1)  //开始问
          {
             unmarryplayer -> set("离婚步骤",1);
             thatplayer -> display ("你的配偶要求和你离婚，如果你同意请输入 unmarry 你的配偶名");
             executor ->set("离婚步骤",2);
          }
          else if (step == 2) //第二个人问
          {
              getRoomChat()->talk(NULL,getAsLong("离婚结束描述"),NULL, NULL);
              thisplayer->set("配偶","");
              thisplayer->set("结婚信物","离婚中");
              thisplayer->set("结婚步骤",0);
              thisplayer->set("离婚步骤",0);
              thisplayer->set("离婚次数",thisplayer->getAsLong("离婚次数")+1);
              thatplayer->set("配偶","");
              thatplayer->set("结婚信物","离婚中");
              thatplayer->set("结婚步骤",0);
              thatplayer->set("离婚步骤",0);
              thatplayer->set("离婚次数",thatplayer->getAsLong("离婚次数")+1);
              YString word = "<font color=#A52A2A>【传言】据官府通告"+thisplayer->getActorName()+"与"+thatplayer->getActorName()+"离婚了</font>";
              g_NormalChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
          }
        }
        else
        {
          thisplayer->display ("你要和谁离婚？");
          return 1;
        }
    }
    else
    {
      thisplayer->display("我们这里是收费办离婚的。");
      return 1;
    }
  }
  else return 0;
}



