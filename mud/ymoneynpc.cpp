//---------------------------------------------------------------------------
//
// ymoneynpc.cpp    2001年2月14日
//
// 类YMoneyNPC：收取礼金的NPC
//
// 作者：张勇,刘鹏   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YMoneyNPC::isTypeOf(YString className)
{
  if(className=="YMoneyNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YMoneyNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="ask") retVal=beAsk(executor,cmd);//询问
  else if(commandVerb=="give") retVal=beGive(executor,cmd);//递交贺礼

  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}
//--------------------------------------------------------
//询问
int YMoneyNPC::beAsk(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord();//被询问的对象
  YString command_About=cmd.getWord();//单词about
  YString commandThing=cmd.getWord();//询问的内容

  YString sMyName=getActorName();//getAsString("名字");
  YString sYourName=player->getActorName();//getAsString("名字");
  long nStep=player->getAsLong("结婚步骤");
  if(commandTarget!=sMyName) return 1;
  if(command_About!="about") return 1;
  YString sSex=player->getSexString();//getAsString("性别");
  if(sSex!="男"){
    player->display(sMyName+"瞪了你一眼：女流之辈，不要抛头露面！快去家去吧。");
    return 1;
  }
  if(commandThing=="订酒席"){
    //判断是不是结婚的人
    if(nStep >= 5 && nStep < 8) //设计的是三拜之后就可以定酒宴了
    {
      player->display(sMyName+"殷勤地说：知道了，马上就好。");
      YString peiouming = player-> getAsString("配偶");
      if (peiouming == "")
      {
         player-> display("你的婚礼还没有结束，跑这里干什么来了？");
         return 1;
      }
      g_NormalChat->talk(NULL,"<font color=#63B8FF>【恭喜】"
          +sYourName+"和"+peiouming+"在酒楼举办结婚喜筵，亲朋好友快来参加啊~~~！</font>",NULL,NULL,CHANNEL_MSG);
      set("新郎名字",sYourName);
      player->set("结婚步骤",8);
    }
    else if (nStep < 5 ){
      player->display(sMyName+"冷笑着对你说：你又没结婚，想来吃白食吗？");
      return 1;
    }
    else if (nStep == 8)
    {
      player->display(sMyName+"说道：我们什么时候开酒席啊？");
      return 1;
    }
    else
    {
      player->display(sMyName+"说道:你已经开过酒宴了怎么还要开啊！" );
      return 1;
    }
  }
  else if(commandThing=="开席"){
    if(nStep==8){
      player->display(sMyName+"大声嚷道：开席了，开席了！");
      g_NormalChat->talk(NULL,"<font color=#63B8FF>【恭喜】"
          +sYourName+"的结婚喜筵开席了~~~！</font>",NULL,NULL,CHANNEL_MSG);
      player->set("结婚步骤",9);
      player -> getRoom() -> set ("开席",1);
      player -> getRoom() -> set ("开席人名",player ->getActorName());
      player -> getRoom() -> set ("开席时间",getRoom()->getAsLong("开席时间"));//开席时间
    }
    else if (nStep < 8 ){
      player->display(sMyName+"对你说道：你得先订酒席，让我们好做准备啊。");
      return 1;
    }
    else{
      player->display(sMyName+"冲你摆摆手：一边去，吃饭不要钱的啊！");
      return 1;
    }
  }
  else return YNPC::beAsk(executor,command);
  return 1;
}
//--------------------------------------------------------
//递交贺礼
int YMoneyNPC::beGive(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString sMyName=getActorName();//getAsString("名字");
  YString sBridegroom=getAsString("新郎名字");
  if(sBridegroom==""){
    player->display(sMyName+"摇摇头说：今儿个没有酒宴，你送的哪门子礼？");
    return 1;
  }
  if(getAsString("上次人名") == player->getActorName()){
    player->display(sMyName+"眼睛一瞪说：怎么又是你？");
    return 1;
  }
  YString cmd=command;
  YString sTemp1=cmd.getWord();
  YString sTemp2=cmd.getWord();
  YString sTemp3=cmd.getWord();
  YString commandThing;
  long commandCount; //物品名，数量
  YString sentence;
  if(sTemp2=="to"){
    if(sTemp3!=sMyName){
      player->display(sMyName+"摇摇头说：你找错人了。");
      return 1;
    }
    sentence=sTemp1+" to "+sBridegroom;
    commandThing=sTemp1;
    commandCount=1;
  }
  else if(sTemp3=="to"){
    YString sTemp4=cmd.getWord();
    if(sTemp4!=sMyName){
      player->display(sMyName+"摇摇头说：你找错人了。");
      return 1;
    }
    sentence=sTemp1+" "+sTemp2+" to "+sBridegroom;
    commandThing=sTemp1;
    commandCount=sTemp2.toLong();
    if(commandCount <= 0){
      player->display("命令输入错误。");
      player->display("正确的格式是：give 物品名 (数量) to 人名");
      return 1;
    }
    else if(commandCount > 1000){
      player->display(sMyName+"摇摇头说：你送的东西太多了。");
      return 1;
    }
  }
  else{
    player->display("命令输入错误。");
    player->display("正确的格式是：give 物品名 (数量) to 人名");
    return 1;
  }
  
  YAbstractActor *objGroom; //新郎的指针
  objGroom=getRoom()->findChildActor(sBridegroom);
  if(!objGroom){
    player->display(sMyName+"摇摇头说道：新郎新娘还没有到，你先等会儿。");
    return 1;
  }
  YPlayer *objPlayerGroom; //新郎的确是玩家
  if(objGroom->isTypeOf("YPlayer")){
    objPlayerGroom=(YPlayer*)objGroom;
  }
  else{
    player->display(sMyName+"摇摇头说道：新郎新娘还没有到，你先等会儿。");
    return 1;
  }
  long nStep=objPlayerGroom->getAsLong("结婚步骤");
  if(nStep<8){
    player->display(sMyName+"摇摇头说：今儿个没有酒宴，你送的哪门子礼？");
    return 1;
  }
  else if(nStep>8){
    player->display(sMyName+"对你摆摆手：你来晚了，酒宴已经开始了！");
    return 1;
  }
  YAbstractThing *objThing; //贺礼的指针
  objThing=player->findChildThing(commandThing);
  if(!objThing){
    player->display(sMyName+"对你摆摆手：你没有这样东西。");
    return 1;
  }
  long count=objThing->getCount(); //玩家身上的物品数量
  if(commandCount>count){ //玩家数量不够
    player->display(sMyName+"对你摇摇头：你身上"+commandThing+"的数量不够。");
    return 1;
  }
  YString sUnit=((YThing*)objThing)->getQuantifier();//getAsString("量词");
  player->giveChildTo(objThing,objPlayerGroom,commandCount); //递交物品
  player->resumWeight();
  player->ActorAddRecoveryChange();
//  player->ActorAddFeatureChange();
  objPlayerGroom->resumWeight();
  YString sYourName=player->getActorName();//getAsString("名字");
  YString sChineseNumber=LongToChinese(commandCount);
  g_NormalChat->talk(NULL,"<font color=#FFAEB9>【恭喜】"
          +sYourName+"送来贺礼"+sChineseNumber+sUnit+commandThing
          +"，祝贺"+sBridegroom+"新婚大喜！</font>",NULL,NULL,CHANNEL_MSG);
  set("上次人名",sYourName);  //设置上次送礼的人的名字为本玩家的名字
  return 1;
}

