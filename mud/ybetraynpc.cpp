//---------------------------------------------------------------------------
//
// ybetraynpc.cpp    2001年1月3日
//
// 类YBetrayNPC：主管叛师的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YBetrayNPC::isTypeOf(YString className)
{
  if(className=="YBetrayNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YBetrayNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="ask") retVal=beAsk(executor,cmd);//别人问关于叛师
  else if(commandVerb=="answer") retVal=beAnswer(executor,cmd);//别人回答叛师的问题

  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}
//--------------------------------------------------------
//别人问关于叛师
int YBetrayNPC::beAsk(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord();//被询问的对象
  YString command_About=cmd.getWord();//单词about
  YString commandThing=cmd.getWord();//询问的内容
  YString msg;
  YString MyName=getActorName(); //本NPC名字
  if(commandTarget!=MyName) return 1;
  if(command_About!="about") return 1;
  if(commandThing!="叛师") return YNPC::beAsk(executor,command);
  //
  YString YourName=player->getActorName(); //名字
  YString YourTeacher=player->getTeacherName(); //师父
  YString YourTitle=player->getTitle(); //头衔
  long YourBetrayNumber=player->getAsLong("叛师次数");
  if(YourBetrayNumber>=10){
    player->display(MyName+"眉头一皱,说道：你在江湖中已经恶名远播,恐怕没人愿意收留你了,你还是走吧。");
    return 1;
  }
  if(YourTeacher==""){
    player->display(MyName+"眉头一皱,说道：你一个普通老百姓,哪里来的师父?");
    return 1;
  }
  //
  player->display(MyName+"对你说道:"+YourName+",你目前是"+YourTitle+",你的师父是"+YourTeacher+",你真的要背叛师门吗?");
  player->set("叛师步骤",1);
  return 1;
}
//--------------------------------------------------------
//别人回答叛师的问题
int YBetrayNPC::beAnswer(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandTarget=cmd.getWord();//被回答的对象
  YString commandThing=cmd.getWord();//回答的内容
  YString msg;
  YString MyName=getActorName();//getAsString("名字");
  if(commandTarget!=MyName) return 1;
  long step=player->getAsLong("叛师步骤");
  if((step>0)&&(commandThing=="取消")){
    player->display(MyName+"对你点了点头,说道：好吧,既然如此,你还是回本门去吧。");
    player->set("叛师步骤",0);
    return 1;
  }
  if(step==1){ //第一步，回答是否叛师
    if(commandThing=="是"){
      player->display("<font color=red>你决定背叛师门!!!</font>");
      player->display("请输入你的密码。");
      player->set("叛师步骤",2);
    }
    else{
      player->display("<font color=green>你打消了背叛师门的念头。</font>");
      player->display(MyName+"对你点了点头,说道：好吧,既然如此,你还是回本门去吧。");
      player->set("叛师步骤",0);
      return 1;
    }
  }
  else if(step==2){ //第二步，回答密码
    //YString YourPassword=player->getAsString("密码");
    //if(commandThing==YourPassword){
      long YourBetrayNumber=player->getAsLong("叛师次数");
      if(YourBetrayNumber>=10){
        player->display(MyName+"眉头一皱,说道：你在江湖中已经恶名远播,恐怕没人愿意收留你了,你还是走吧。");
        player->set("叛师步骤",0);
        return 1;
      }
      YString YourName=player->getActorName();//getAsString("名字");
      YString YourTeacher=player->getTeacherName(); //师父
      YString YourSchool=player->getSchool(); //门派
      long YourSchoolPlace=player->getSchoolPlace(); //辈分
      YString YourTitle=player->getTitle(); //头衔
      YString YourSkillList=player->getAllSkillsList(); //所会技能
      YString YourSkill; //你的武功
      long YourSkillGrade; //你的武功等级
      long YourExp=player->getExperience(); //经验
      if(YourExp>50000){ //大于50K，各种武功降低一半
        while((YourSkill=YourSkillList.getWord())!=""){
          YourSkillGrade=player->getSkillLevel(YourSkill);//getAsLong(YourSkill);
          YourSkillGrade/=2;
          player->setSkillLevel(YourSkill,YourSkillGrade);//set(YourSkill,YourSkillGrade);
        }
      }
      player->set("叛师次数",YourBetrayNumber+1); //叛师次数加一
      player->setTeacherName(""); //师父
      player->setSchool(""); //门派
      player->setTitle("<font color=red>普通百姓</font>"); //头衔
      player->setSchoolPlace(0); //辈分
      player->display("<font color=red>你背叛了"+YourSchool+"!</font>");
      g_RumorChat->talk(NULL,"<font color="+g_Settings->getrumorChatColor()+">【谣言】"
          +"某人: 据江湖传言"+YourName+"背叛了"+YourSchool+",从此和"+YourSchool+"一刀两断!</font>",NULL,NULL,CHANNEL_MSG);
      player->set("叛师步骤",0); //叛师结束
    //}
    /*else{
      player->display("<font color=red>你的密码错误!</font>");
      player->display("<font color=green>你打消了背叛师门的念头。</font>");
      player->display(MyName+"对你点了点头,说道：好吧,既然如此,你还是回本门去吧。");
      player->set("叛师步骤",0);
      return 1;
    }*/
  }
  else{
    player->display(MyName+"眉头一皱,说道：你想说什么?");
  }
  return 1;
}
