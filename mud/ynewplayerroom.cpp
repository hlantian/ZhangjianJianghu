//---------------------------------------------------------------------------
//
// ynewplayerroom.cpp    2000年8月23日
//
// 类YNewPlayerRoom：新人登录的专用房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YNewPlayerRoom::YNewPlayerRoom(YString initFileName):YRoom(initFileName),
                                                      m_Declare(""),
                                                      m_OutRoom("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YNewPlayerRoom::isTypeOf(YString className)
{
  if(className=="YNewPlayerRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YNewPlayerRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setDeclare(getAsString("声明"));
  setOutRoom(getAsString("出口房间"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YNewPlayerRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("声明",getDeclare());
  set("出口房间",getOutRoom());
  
  return retVal;
}

//--------------------------------------------------------
//事件onBeforeEnter的默认处理函数
int YNewPlayerRoom::onBeforeEnter(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=YRoom::onBeforeEnter(sender, actor);
  if(retVal) {
    g_NormalChat->unsubscribe(actor);
    g_RumorChat->unsubscribe(actor);
    g_NewUserChat->unsubscribe(actor);
    return retVal;
  }
  else return retVal;
}
//--------------------------------------------------------
//事件onAfterLeave的默认处理函数
int YNewPlayerRoom::onAfterLeave(YMUDObject* sender, YAbstractActor* actor)
{
  int retVal=1;
  YRoom::onAfterEnter(sender, actor);
  g_NormalChat->subscribe(actor);
  g_RumorChat->subscribe(actor);
  g_NewUserChat->subscribe(actor);
  return retVal;
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YNewPlayerRoom::executeCommand(YAbstractActor* executor, YString command)
{
  YPlayer* player;//新人
  int step=0;//新人登录步骤
  YString cmd=command;//玩家的输入
  YString commandFirst;//第一个单词
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  step=player->getAsLong("新人登录步骤");
  switch (step){
    case 0:player->set("新人登录步骤",1);//第一步
           player->display(getDeclare()); //显示声明
           player->display("您同意吗? 同意请输入(yes),不同意请输入(no):");
           break;
    case 1:{
       commandFirst=cmd.getWord();
       if((commandFirst=="yes")||(commandFirst=="y")||(command=="say yes")||(command=="say y")){
          player->set("新人登录步骤",2);
          player->display("请决定您的天赋:<br>");
          player->display("您可以决定的天赋有臂力,悟性,根骨,身法。<br>\
                           其总和为100,各项最低为20,最高为40,<br>\
                           请你慎重考虑并依次输入:<br>");
          player->display("例如您输入:30 25 20 25,则分别代表臂力30,悟性25,根骨20,身法25.<br>");
       }
       else if((commandFirst=="no")||(commandFirst=="n")||(command=="say no")){
          player->display("那好吧,欢迎下次再来!");
          quit(player);
       }
       else if (commandFirst == "quit")
       {
          quit(player);
       }
       else{
          player->display(getDeclare()); //显示声明
          player->display("您同意吗? 同意请输入(yes),不同意请输入(no):");
       }
       break;
    }
    case 2:{
       long Muscle;//臂力
       long Savvy;//悟性
       long Body;//根骨
       long Agility;//身法
       Muscle=(cmd.getWord()).toLong();
       Savvy=(cmd.getWord()).toLong();
       Body=(cmd.getWord()).toLong();
       Agility=(cmd.getWord()).toLong();
       if((Muscle>=20)&&(Muscle<=40)&&(Savvy>=20)&&(Savvy<=40)&&
          (Body>=20)&&(Body<=40)&&(Agility>=20)&&(Agility<=40)&&
          ((Muscle+Savvy+Body+Agility)==100))
       {
          //设置初始属性
          player->set("年龄",g_Settings->getsitNewbieBeginAge());//getAsLong("新手开始年龄")); //年龄
          player->set("先天臂力",Muscle);
          player->set("先天悟性",Savvy);
          player->set("先天根骨",Body);
          player->set("先天身法",Agility);
          player->set("容貌",rand()%41+40); //容貌
          player->set("福缘",rand()%41+40); //福缘
          player->set("后天臂力",Muscle);
          player->set("后天悟性",Savvy);
          player->set("后天根骨",Body);
          player->set("后天身法",Agility);
          player->set("最大负重",15*Muscle);
          player->set("最大饮水",15*Muscle);
          player->set("最大食物",15*Muscle);
          player->set("固定攻击力",Muscle); //固定攻击力
          player->set("固定防御力",Muscle); //固定防御力
          player->set("头衔","<font color=buue>普通百姓</font>"); //头衔
          player->set("衣服","布衣"); //衣服
          player->set("潜能",100); //潜能
          player->set("食物",150);
          player->set("饮水",150);
          player->set("状态",""); //状态
          player->set("空闲时间",0); //空闲时间
          player->onAfterLoad();
          //设置结束
          YThing *objThing; //给新人的物品-布衣,银子20两,潜能100点
          objThing=(YThing*)loadObject("thing/布衣");
          if(objThing){
            objThing->setCount(1);
            player->addChild(objThing);
          }
          objThing=(YThing*)loadObject("thing/银子");
          if(objThing){
            objThing->setCount(20);
            player->addChild(objThing);
          }
          player->setAppendDefense(5); //附加防御力
          player->set("新人登录步骤",3);
          player->display("您可以开始闯荡江湖了......<br>");
          player->resumWeight();
          player->gotoRoom(getOutRoom()); //出口房间
       }
       else{
          player->display("输入错误,请重新输入。<br>");
          player->display("例如您输入:30 25 20 25,则分别代表臂力30,悟性25,根骨20,身法25<br>");
          player->set("新人登录步骤",2);
       }
       break;
    }
    default:break;//do nothing
  }
  onAfterLoad();
  return 1;
}
