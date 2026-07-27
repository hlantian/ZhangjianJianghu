//---------------------------------------------------------------------------
//
// ywizard.cpp    2001年5月21日
//
// 类YWizard：巫师
//
// 作者：刘鹏。张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#include "webmud.h"

//--------------------------------------------------------
//构造函数
YWizard::YWizard(YUser* user, YString initFileName): YPlayer(user, initFileName),
 wizardlog (g_Settings->getRootPath()+
                        g_Settings->getPathSeparator()+
                        "wiz"+g_Settings->getPathSeparator()+
                        getAsString("名字")+".log")
{
}
//--------------------------------------------------------
//析构函数
YWizard::~YWizard()
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YWizard::isTypeOf(YString className)
{
  if(className=="YWizard") return 1;
  else return YPlayer::isTypeOf(className);
}
//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YWizard::executeCommand(YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  
  if(commandVerb=="goto") retVal=cmd_goto(cmd);                   //去room
  else if(commandVerb=="wizgoto") retVal=wizgoto(cmd);            //去player/npc的房间
  else if(commandVerb=="wizclose") retVal=wizclose(cmd);          //关闭频道
  else if(commandVerb=="wizopen") retVal=wizopen(cmd);            //开启频道
  else if(commandVerb=="wizlook") retVal=wizlook(cmd);            //查看player/npc属性
  else if(commandVerb=="wizlookroom") retVal=wizlookroom(cmd);    //查看room属性
  else if(commandVerb=="wizset") retVal=wizset(cmd);              //设置long型属性
  else if(commandVerb=="wizsets") retVal=wizsets(cmd);            //设置YString型属性
  else if(commandVerb=="wizsetadd") retVal=wizsetadd(cmd);        //设置文字添加????
  else if(commandVerb=="wizsetaddsb") retVal=wizsetaddsb(cmd);    //设置他人文字添加????
  else if(commandVerb=="wizsetsb") retVal=wizsetsb(cmd);          //设置他人long型属性
  else if(commandVerb=="wizsetssb") retVal=wizsetssb(cmd);        //设置他人YString属性
  else if(commandVerb=="wizkick") retVal=wizkick(cmd);            //使人物晕倒
  else if(commandVerb=="wizkickout") retVal=wizkickout(cmd);      //强制他人退出游戏
  else if(commandVerb=="wizget") retVal=wizget(cmd);              //把人物抓到自己这里
  else if(commandVerb=="wizgetthing") retVal=wizgetthing(cmd);    //从别人那里去东西
  else if(commandVerb=="wizjianyu") retVal=wizjianyu(cmd);        //把人物抓到监狱
  else if(commandVerb=="wizfree") retVal=wizfree(cmd);        //把人物抓到监狱
  else if(commandVerb=="wizchat") retVal=wizchat(cmd);            //巫师专用公共频道
  else if(commandVerb=="timeuse") retVal=timeuse();               //查看系统参数
  else if(commandVerb=="reload") retVal=cmd_reload(cmd);          //重新装载object的属性
  else if(commandVerb=="wizcreate") retVal=wizcreate(cmd);        //创造物品
  else if(commandVerb=="shutdown") retVal=shutdown(cmd);          //保存所有玩家数据
  else if(commandVerb=="setuselevel") retVal=uselevel(cmd);       //设置"玩家级别"
  else if(commandVerb=="lookrumor") retVal=lookrumor(cmd);       //察看谣言
  else if(commandVerb=="blackip") retVal=blackip(cmd);       //封锁ip
  else if(commandVerb=="unblackip") retVal=unblackip(cmd);       //开放封锁ip

  if(retVal == 0) {
        wizardlog.write(command);   //纪录巫师命令
        return YPlayer::executeCommand(command);        //非巫师指令，由player处理
  }
  else if(retVal == 2){
    wizardlog.write(command+"(没有相应的权限)");   //纪录巫师命令
    display("你没有相应的权限。");
    return 1;
  }
  else{
    wizardlog.write(command);   //纪录巫师命令
    return retVal;
  }
}
//----------------------------------------------------------------------
//去room
int YWizard::cmd_goto(YString command)
{
  if(getAsLong("允许goto")!=1) return 2;  //条件判断/zhy

  gotoRoom(command.getWord());
  return 1;
}
//----------------------------------------------------------------------
//去player/npc的房间
int YWizard::wizgoto(YString sentence)
{
  if(getAsLong("允许wizgoto")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     YString roomName = "";
     roomName="/"+sb->getRoom()->getDataFileName();
     if ( getRoom()->sendActorToRoom(this,roomName) == 0 )
     display("你已经成功的来到了"+s+"的房间"+roomName);
     else display ("没有成功");
  }
  else display("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//关闭频道
int YWizard::wizclose(YString sentence)
{
   if(getAsLong("允许wizclose")!=1) return 2;  //条件判断/zhy

   YPlayer* sb=g_PlayerManager->getPlayer(sentence);
   if (sb)     //人物查看
   {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>由于你言行不当，你的频道被封闭了。</font>");
     sb->setWizCloseChat(1);
     display ("成功关闭"+sentence+"的频道");
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//开启频道
int YWizard::wizopen(YString sentence)
{
   if(getAsLong("允许wizopen")!=1) return 2;  //条件判断/zhy

   YPlayer* sb=g_PlayerManager->getPlayer(sentence);
   if (sb)   //查看人物
   {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>你的频道被开启了。</font>");
     sb->setWizCloseChat(0);
     display ("你开启了"+sentence+"的频道。");
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//查看room属性
int YWizard::wizlookroom(YString sentence)
{
   if(getAsLong("允许wizlookroom")!=1) return 2;  //条件判断/zhy
   YString shuxing= sentence.getWord();
   long number=0;
   YString zifu ="";
   number = getRoom()->getAsLong(shuxing);
   zifu = getRoom()->getAsString(shuxing);
   if (number != 0)display (shuxing + " : "+ (YString)number);
   else if (zifu != "") display (shuxing +" : " +zifu);
   else display ("没有属性"+shuxing + "或其值为0");
   return 1;
}
//----------------------------------------------------------------------
//查看player/npc属性
int YWizard::wizlook(YString sentence)
{
   if(getAsLong("允许wizlook")!=1) return 2;  //条件判断/zhy

   YString sbname = sentence.getWord();
   YString shuxing="" ;
   long number=0;
   YString zifu ="";
   long flag = 0;
   YActor* sb=g_PlayerManager->getActor(sbname);
   if (sb)   //查看人物
   {
     if (wizcompare(sb)) return 1;
     sb->onBeforeSave();
     while ((shuxing = sentence.getWord()) != "")
     {
        if (shuxing == "allthing")
        {
          YString allthing = sb->enumChildrenThing();
          display (sbname+"携带物品："+allthing);
          YString onething = "";
          YAbstractThing* mything;
          while ( (onething = allthing.getWord()) != "")
          {
             mything = sb->findChildThing(onething);
             if (mything)
             {
               display (onething+"数量是"+(YString)mything->getCount());
             }
          }
          display (sbname+"携带人物："+sb->enumChildrenActor());
          return 1;
        }
        number = sb->getAsLong(shuxing);
        zifu = sb->getAsString(shuxing);
        if (number != 0)display (shuxing + " : "+ (YString)number);
        else if (zifu != "") display (shuxing +" : " +zifu);
        else display ("没有属性"+shuxing + "或其值为0");
        flag = 1;
     }
     if (flag == 1 ) return 1;
     display("年龄"+(YString)sb->getActorAge());
     // 显示技能
     YString jineng = sb->getAllSkillsList();//getAsString("所会技能");
     display("所会技能"+jineng);
     YString tempjineng = jineng.getWord();
     YString exp;
     while ((tempjineng = jineng.getWord()) != "")
     {
       exp = jineng + "_经验";
       display (tempjineng+"技能级别"+(YString)sb->getAsLong(tempjineng)+"技能经验"+(YString)sb->getAsLong(exp));
     }
     display("气血"+(YString)sb->getBody()
             +"最大气血"+(YString)sb->getMaxBody());
     display("内力"+(YString)sb->getInternalForce()
             +"最大内力"+(YString)sb->getMaxInternalForce());
     display("精力"+(YString)sb->getEnergy()
             +"最大精力"+(YString)sb->getMaxEnergy());
     display("经验"+(YString)sb->getExperience()
             +"潜能"+(YString)sb->getPotential());
     display("容貌"+(YString)sb->getFeature()
             +"福缘"+(YString)sb->getLuck());
     if ( sb->isTypeOf("YPlayer"))
     {
       YPlayer* TempPlayer = (YPlayer*)sb;
       display("杀人次数"+(YString)TempPlayer->getKillTimes()
             +"被杀次数"+(YString)TempPlayer->getBeKillTimes());
       display("后天悟性"+(YString)TempPlayer->getLastLearn()
             +"后天根骨"+(YString)TempPlayer->getLastForce());
       display("后天臂力"+(YString)TempPlayer->getLastArm()
            +"后天身法"+(YString)TempPlayer->getlaseDodge());
       display("攻击力"+(YString)TempPlayer->getInhereAttack()
             +"防御力"+(YString)TempPlayer->getInhereDefense());
       display("负重"+(YString)TempPlayer->getWeight()
             +"最大负重"+(YString)TempPlayer->getMaxWeight());
     }
     YString allthing = sb->enumChildrenThing();
     display (sbname+"携带物品："+allthing);
     YString onething = "";
     YAbstractThing* mything;
     while ( (onething = allthing.getWord()) != "")
     {
        mything = sb->findChildThing(onething);
        if (mything)
        {
            display (onething+"数量是"+(YString)mything->getCount());
        }
     }
     display (sbname+"携带人物："+sb->enumChildrenActor());
     sb->onAfterLoad();
   }
   else display ("没有这个人物。");
   return 1;
}
//----------------------------------------------------------------------
//设置long型属性
int YWizard::wizset(YString sentence)
{
  if(getAsLong("允许wizset")!=1) return 2;  //条件判断/zhy

  YString type=sentence.getWord(); //类型
  if(!fnAllowSet(type)){           //不允许设置这个属性
    display("你说什么?");
    return 1;
  }
  YString much=sentence.getWord(); //数量
  if (type == "玩家级别")
    {
      display("你不能对这个属性进行设定。");
      return 1;
    }
  onBeforeSave();
  set(type,much.toLong());
  onAfterLoad();
  display("你设定你的"+type+"为"+much);
  return 1;
}
//----------------------------------------------------------------------
//设置YString型属性
int YWizard::wizsets(YString sentence)
{
  if(getAsLong("允许wizsets")!=1) return 2;  //条件判断/zhy

  YString type=sentence.getWord(); //类型
  YString much=sentence; //字符串
  onBeforeSave();
  set(type,much);
  onAfterLoad();
  display("你设定你的"+type+"为"+much);
  return 1;

}
//----------------------------------------------------------------------
//设置文字添加????
int YWizard::wizsetadd(YString sentence)
{
  if(getAsLong("允许wizsetadd")!=1) return 2;  //条件判断/zhy

  YString type=sentence.getWord(); //类型
  YString munch=sentence.getWord(); //添加的
  munch=munch+" "+getAsString(type);
  onBeforeSave();
  set(type,munch);
  onAfterLoad();
  display("你设定你的"+type+"为"+munch);
  return 1;
}
//----------------------------------------------------------------
//设置他人文字添加????
int YWizard::wizsetaddsb(YString sentence)
{
  if(getAsLong("允许wizsetaddsb")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)    //人物判别
  { display ("没有这个人物。"); }
  else
  {
     if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        YString munch=sentence.getWord(); //数量
        munch= munch+" "+sb->getAsString(type);
        sb->onBeforeSave();
        sb->set(type,munch);
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+munch);
  }
  return 1;
}
//------------------------------------------------------------------
//设置他人long型属性
int YWizard::wizsetsb(YString sentence)
{
  if(getAsLong("允许wizsetsb")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)  //人物判别
  { display ("没有这个人物。"); }
  else
  {
        if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        if(!fnAllowSet(type)){           //不允许设置这个属性
          display("你说什么?");
          return 1;
        }
        YString much=sentence.getWord(); //数字
        if (type == "玩家级别")
        {
            display ("不可使用命令，");
            return 1;
        }
        sb->onBeforeSave();
        sb->set(type,much.toLong());
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+much);
  }
  return 1;

}
//----------------------------------------------------------------------
//设置他人YString属性
int YWizard::wizsetssb(YString sentence)
{
  if(getAsLong("允许wizsetssb")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)   //人物判别
  { display ("没有这个人物。"); }
  else
  {
        if (wizcompare(sb)) return 1;
        YString type=sentence.getWord(); //类型
        YString much=sentence; //字符
        sb->onBeforeSave();
        sb->set(type,much);
        sb->onAfterLoad();
        display("你设定"+s+"的"+type+"为"+much);
  }
  return 1;
}
//----------------------------------------------------------------------
//使人物晕倒
int YWizard::wizkick(YString sentence)
{
  if(getAsLong("允许wizkick")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)    //人物的查看
  {
     if (wizcompare(sb)) return 1;
     sb->display("<font color=red>由于你言行不当，惩罚自天而降。。。。。</font>");
     sb->faint();
     display ("你已经成功的使"+s+"昏到了");
  }
  else display ("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//强制他人退出游戏
int YWizard::wizkickout(YString sentence)
{
  if(getAsLong("允许wizkickout")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if(!sb)   //人物判别
  { display ("没有这个人物。"); }
  else
  {
        getRoom()->setPlayListQuit(sb->getActorName()+" "+(getRoom()->getPlayListQuit())) ;
        sb->setStatus("掉线中");
        display("开始把"+s+"踢出系统");
  }
  return 1;
}
//----------------------------------------------------------------------
//把人物抓到自己这里
int YWizard::wizget(YString sentence)
{
  if(getAsLong("允许wizget")!=1) return 2;  //条件判断/zhy

  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     if (wizcompare(sb)) return 1;
     YString roomName= sentence;
     if (roomName == "") roomName="/"+getRoom()->getDataFileName();
     if (sb->getRoom()->sendActorToRoom(sb,roomName) == 0)
     display("你已经成功的把"+s+"抓到了"+roomName);
     else display ("没有成功。");
  }
  else display("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//把人物抓到监狱
int YWizard::wizjianyu(YString sentence)
{
  if(getAsLong("允许wizjianyu")!=1) return 2;  //条件判断/zhy
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     if (wizcompare(sb)) return 1;
     if (sb->getRoom()->sendActorToRoom(sb,"/room/a") == 0)
     display("你已经成功的把"+s+"抓到了监狱");
     else display ("没有成功。");
  }
  else display("没有这个人物。");
  return 1;
}
//----------------------------------------------------------------------
//把人物抓到监狱
int YWizard::wizfree(YString sentence)
{
  if(getAsLong("允许wizjianyu")!=1) return 2;  //条件判断/zhy
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     if (wizcompare(sb)) return 1;
     if (sb->getRoom()->sendActorToRoom(sb,"/room/长安/城隍庙") == 0)
     display("你已经成功的把"+s+"放出了监狱");
     else display ("没有成功。");
  }
  else display("没有这个人物。");
  return 1;
}
//---------------------------------------------------------------------
//从别人那里取得东西
int YWizard::wizgetthing(YString sentence)         //wizgetthing
{
  if (getAsLong("允许wizgetthing") != 1) return 2 ;
  YString s=sentence.getWord(); //"sb."
  YActor* sb=g_PlayerManager->getActor(s);
  if (sb)  //人物的查看
  {
     YString thingname = sentence.getWord(); //thing名字
     YThing* thing ;
     thing =(YThing*)( sb->findChildThing(thingname));
     if (thing)
     {
       YString thingcount = sentence.getWord();  //物品数量
       long count = thingcount.toLong();
       if (count <=0 ) count = 1 ;
       if (count > thing->getCount())count = thing->getCount() ;
       if (sb->giveChildTo(thing,this,count))
       {
         display("取得了"+(YString)count+"个"+thingname);
         sb->display ("巫师"+getActorName()+"从你这里取得了"+(YString)count+"个"+thingname);
       }
       else display ("没有取得成功！！");
     }
     else display ("没有"+thingname+"这个物品");
  }
  else display ("没有这个人物");
  return 1;
}

//-------------------------------------------------
//巫师专用公共频道
int YWizard::wizchat(YString word)
{
  if(getAsLong("允许wizchat")!=1) return 2;  //条件判断/zhy

  //查找替换< >   注：由于>在页面没反映所以不与处理
  word = changeword (word);
  word ="<font color=" + g_Settings->getAsString("巫师频道颜色") + ">【系统消息】" +
        getActorName()+":"+word+"</font>" ;
  g_SystemChat->talk(NULL,word,NULL,NULL,CHANNEL_MSG);
  return 1;
}
//--------------------------------------------------------------------------
//查看系统参数
int YWizard::timeuse(void)
{
  if(getAsLong("允许timeuse")!=1) return 2;  //条件判断/zhy

  g_Stopwatch->stop(0);
  display(g_Stopwatch->overview(true));
  g_Stopwatch->resetAll();
  g_Stopwatch->start(0);
  display(g_Counter->overview(true));
  return 1;
}
//--------------------------------------------------------------------------
//重新装载object的属性
int YWizard::cmd_reload(YString command)
{
  if(getAsLong("允许reload")!=1) return 2;  //条件判断/zhy

  YString type=command.getWord();
  if(type=="room") {
    if(getRoom()->reload()==1) display("room 已经刷新。");
    else display("room 刷新时出错。");
  }
  else if(type=="NPC") {
    YString npcname=command.getWord();
    YNPC* npc=g_PlayerManager->getNPC(npcname);
    if(!npc) {
      display("没有这个NPC。");
      return 1;
    }
    if(npc->reload()==1) display("NPC已经刷新。");
    else display("NPC刷新时出错。");
  }
  else if(type=="quest") {
    g_Quest->reload();
    display("任务已经刷新。");
  }
  else if(type=="wugong") {
    g_Wugong->reload();
    display("武功已经刷新。");
  }
  else if(type=="emote") {
    g_Emote->reload();
    display("表情已经刷新。");
  }
  else if(type=="conf") {
    g_Settings->load(0,NULL,"webmud.conf");
    display("系统设置已经刷新。");
  }
  else {
    display("目前只支持quest、wugong、emote、room、conf和NPC。");
  }
  return 1;
}
//--------------------------------------------------------------------------
//创造物品
int YWizard::wizcreate(YString command)
{
  if(getAsLong("允许wizcreate")!=1) return 2;  //条件判断/zhy

  if(command=="") {
    display("你要制造什么东西？");
    return 1;
  }
  YString thingname = command.getWord();
  YMUDObject* obj=loadObject(thingname);
  if(!obj) {
    display("无法装载此物品。");
    return 1;
  }
  getRoom()->addChild(obj);
  if (obj->isTypeOf("YThing"))
  {
    long thingcount = command.toLong();
    if  (thingcount <= 0 ) thingcount = 1;
    ((YThing*)obj)->setCount(thingcount);
  }
  display("创造成功。");
  return 1;
}
//---------------------------------------------------------------------------
//保存所有玩家数据
int YWizard::shutdown(YString cmd)
{
  if(getAsLong("允许shutdown")!=1) return 2;  //条件判断/zhy

  YString canshu = cmd.getWord();
  YString allname =  g_PlayerManager->enumPlayer();
  YString tempname = "";
  YPlayer* sb=NULL; //人物的指针
  while ((tempname = allname.getWord()) != "")
  {
    sb=g_PlayerManager->getPlayer(tempname);
    if (sb)
    {
      if((sb->YMUDObject::save())==1) display (sb->getActorName()+"保存。");
      else display(tempname+"数据无法保存");
    }
    else display (tempname+"没找到指针。");
  }
  display ("存储完毕。");
  if(canshu=="-f") {
    display("关闭MUD......");
    #ifndef __WIN32__
    g_Comm->stop();
    #endif
    //exit(0);
  }
  return 1;
}
//-----------------------------------------
//设置"玩家级别"
int YWizard::uselevel(YString sentence)
{
   if(getAsLong("允许setuselevel")!=1) return 2;  //条件判断/zhy

   long melevel = getLevel();
   if (melevel < 50)         //查看是否是巫师
   {
     YString name = sentence.getWord();
     YPlayer* sb=g_PlayerManager->getPlayer(name);
     if (sb)                           //查找人物
     {
       if ( sb->getLevel() < melevel)         //查看级别权限
       {
         long level = sentence.toLong();
         if (melevel > level)                      //捡测设定等级
         {
           sb->setLevel(level);
           display ("你已经设定"+name+"的级别为"+sentence+"级。");
         }
         else display ("你设定的级别要低于自己的级别。");
       }
       else display ("你的只能设定比自己级别低的人。");
     }
     else display("没有这个玩家。");
   }
   else display ("你的级别不足以使用这个命令。");
   return 1;
}
//设置"玩家级别"
int YWizard::lookrumor(YString sentence)
{
    if(getAsLong("允许lookrumor")!=1) return 2;
    YActor* sb=g_PlayerManager->getActor("白无常");
    if (sb)
    {
      display(sb->getAsString("造谣10"));
      display(sb->getAsString("造谣1"));
      display(sb->getAsString("造谣2"));
      display(sb->getAsString("造谣3"));
      display(sb->getAsString("造谣4"));
      display(sb->getAsString("造谣5"));
      display(sb->getAsString("造谣6"));
      display(sb->getAsString("造谣7"));
      display(sb->getAsString("造谣8"));
      display(sb->getAsString("造谣9"));
      return 1;
    }
    else display ("没有人造谣。");
    return 1;
}
//---------------------------------------------
//这个字符串是否允许set
bool YWizard::fnAllowSet(YString string)
{
  if((string == "允许goto") ||
     (string == "允许wizgoto") ||
     (string == "允许wizclose") ||
     (string == "允许wizopen") ||
     (string == "允许wizlook") ||
     (string == "允许wizset") ||
     (string == "允许wizsets") ||
     (string == "允许wizsetadd") ||
     (string == "允许wizsetaddsb") ||
     (string == "允许wizsetsb") ||
     (string == "允许wizsetssb") ||
     (string == "允许wizkick") ||
     (string == "允许wizkickout") ||
     (string == "允许wizget") ||
     (string == "允许wizchat") ||
     (string == "允许timeuse") ||
     (string == "允许reload") ||
     (string == "允许wizlookroom")||
     (string == "允许wizcreate") ||
     (string == "允许wizgetthing") ||
     (string == "允许shutdown") ||
     (string == "允许setuselevel") ||
     (string == "允许wizdisbandfaction") ||
     (string == "允许lookrumor") ||
     (string == "允许blackip")
      ) {
       return false; //不允许
  }
  else return true;  //允许
}
//-----------------------------------------
//封锁ip的命令
int YWizard:: blackip(YString cmmand)
{
  if(getAsLong("允许blackip")!=1) return 2;
  cmmand=cmmand+" "+g_Settings->getblackip();
  g_Settings->setblackip(cmmand);
  display("现在关闭的ip列表为"+cmmand);
  return 1;
}
//-----------------------------------------
//封锁ip的命令
int YWizard:: unblackip(YString cmmand)
{
  if(getAsLong("允许blackip")!=1) return 2;
  YString tempstr = g_Settings->getblackip();
  tempstr.removeWord(cmmand,1);
  g_Settings->setblackip(tempstr);
  display("现在关闭的ip列表为"+tempstr);
  return 1;
}
//-----------------------------------------
//巫师强制解散一个帮会
int YWizard::wizdisband(YString command)
{
  if(getAsLong("允许wizdisbandfaction")!=1) return 2;
  YString sFactionName=command.getWord();
  YString sAction=command.getWord();
  int i=g_Faction->isFacionExisting(sFactionName);
  if(i != 1){ //不存在这个帮派
    display("这个帮派不存在！请用faction查询。---gm.doom宣");
    return 1;
  }
  if(sAction == "解散"){
    g_Faction->fnRemoveFaction(sFactionName);  //删除一个帮派
    g_Faction->save();
    display("<font color=red>你强制解散了["+sFactionName+"]</font>");
  }
  else if(sAction == "关闭"){
    g_Faction->fnSetFacionStatus(sFactionName,"被巫师关闭");
    g_Faction->save();
    display("<font color=red>你关闭了["+sFactionName+"]</font>");
  }
  else if(sAction == "打开"){
    g_Faction->fnSetFacionStatus(sFactionName,"");
    g_Faction->save();
    display("<font color=red>你打开了["+sFactionName+"]</font>");
  }
  else{
    display("请指定更多信息！---gm.doom宣");
  }
  return 1;
}

