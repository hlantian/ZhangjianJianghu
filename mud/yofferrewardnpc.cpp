//---------------------------------------------------------------------------
//
// yofferrewardnpc.cpp    2001年1月12日
//
// 类YOfferRewardNPC：主管悬赏杀人的NPC
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YOfferRewardNPC::YOfferRewardNPC(YString initFileName):YNPC(initFileName),
                                                        m_IsNotOfferReward(0)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YOfferRewardNPC::isTypeOf(YString className)
{
  if(className=="YOfferRewardNPC") return 1;
  else return YNPC::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YOfferRewardNPC::onAfterLoad(void)
{
  int retVal=YNPC::onAfterLoad();
  
  setIsNotOfferReward(getAsLong("是否悬赏"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YOfferRewardNPC::onBeforeSave(void)
{
  int retVal=YNPC::onBeforeSave();
  
  set("是否悬赏",getIsNotOfferReward());
  
  return retVal;
}

//--------------------------------------------------------
//作为动作的承受者处理命令，已处理返回1，未处理返回0
int YOfferRewardNPC::executeCommandAsTarget(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();

  if(commandVerb=="xuanshang") retVal=beXuanshang(executor,cmd);//悬赏杀某人
  else if(commandVerb=="list") retVal=beList(executor,cmd);//察看目前的悬赏情况
  else if(commandVerb=="give") retVal=beGive(executor,cmd);//递交首级并领取赏金

  if(!retVal) return YNPC::executeCommandAsTarget(executor,command);
  else return retVal;
}
//--------------------------------------------------------
//悬赏杀某人
int YOfferRewardNPC::beXuanshang(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString MyName=getActorName(); //NPC的名字
  YString cmd=command;
  YString commandType=cmd.getWord();//悬赏的类型(杀,找...)
  YString commandTarget=cmd.getWord();//悬赏的对象(某人,某物...)
  long num=0,nGold=0,nSilver=0,nCoin=0; //金子，银子，铜板的数量
  YString commandNumber; //数量字符串
  YString commandUnit; //数量单位字符串
  while((commandNumber=cmd.getWord())!=""){
    num=commandNumber.toLong(); //转化为长型数字
    commandUnit=cmd.getWord(); //单位
    if(commandUnit=="金子"){
      nGold+=num;
    }
    else if(commandUnit=="银子"){
      nSilver+=num;
    }
    else if(commandUnit=="铜板"){
      nCoin+=num;
    }
    else{
      player->display("命令格式错误,正确格式为“xuanshang 杀 <某人> <货币数量> <货币单位> [<货币数量> <货币单位> ...]”");
      return 1;
    }
  }
  long nMoney=nGold*10000+nSilver*100+nCoin; //钱的总数
  if(nMoney<=0){ //钱的总数小于0,则认为没有付正确的价钱,拒绝请求
    player->display(MyName+"不耐烦地说：你到底要悬赏多少钱？");
    return 1;
  }
  YThing *objMoney;
  long nCash=0;
  objMoney=(YThing*)player->findChildThing("金子");
  if(objMoney){
     nCash+=(objMoney->getCount())*10000;
  }
  objMoney=(YThing*)player->findChildThing("银子");
  if(objMoney){
     nCash+=(objMoney->getCount())*100;
  }
  objMoney=(YThing*)player->findChildThing("铜板");
  if(objMoney){
     nCash+=objMoney->getCount();
  } //现金总数
  if(nMoney>nCash){ //赏金数额大于现金数
    player->display(MyName+"眼睛一瞪：你有这么多钱么？");
    return 1;
  }
  if(commandType=="杀"){
    YActor *objActor=g_PlayerManager->getActor(commandTarget);
    if(!objActor){
      player->display(MyName+"为难地说：找不到这个人!");
      return 1;
    }
    YString sShowMoney=""; //显示的钱
    if(nGold!=0){
      sShowMoney+=LongToChinese(nGold)+"两金子";
    }
    if(nSilver!=0){
      sShowMoney+=LongToChinese(nSilver)+"两银子";
    }
    if(nCoin!=0){
      sShowMoney+=LongToChinese(nCoin)+"文铜板";
    }
    YString sItem; //悬赏项目
    YString sType,sTarget,sMoney; //类型，目标，钱
    long nMoreMoney; //长型的钱
    bool bFull=true; //是否满了20个
    int i; //索引
    for(i=0;i<MAXNUMBER;i++){ //第一次查找：如果已经有同样悬赏,钱增加;如果满了,bFull不变,仍为"真"
      sItem=offerreward[i];
      sType=sItem.getWord(); //类型
      if(sType!="杀"){
        bFull=false; //假，表示不满
        continue; //此项目为“空“
      }
      sTarget=sItem.getWord();
      if(sTarget==commandTarget){ //有相同的项目
        sMoney=sItem.getWord(); //赏金=NNNNN
        nMoreMoney=sMoney.toLong()+nMoney; //赏金增加
        offerreward[i]=sType+" "+sTarget+" "+(YString)nMoreMoney;
        player->display("你加上了"+sShowMoney+"悬赏杀"+commandTarget+"。");
        bFull=false; //已经加上了，相当于不满
        break;
      }
    }
    if(bFull){ //项目满了
      player->display(MyName+"为难地说：目前的悬赏已经够多了!");
      return 1;
    }
    if(i>=MAXNUMBER){ //说明没有同样悬赏,但是项目没有满
      for(i=0;i<MAXNUMBER;i++){ //第二次查找：添加新项目
        sItem=offerreward[i];
        sType=sItem.getWord();
        if(sType=="杀") continue; //已经有了
        else{ //添加新项目
          sType="杀";
          sTarget=commandTarget;
          sMoney=(YString)nMoney;
          offerreward[i]=sType+" "+sTarget+" "+sMoney;
          player->display("你悬赏了"+sShowMoney+"杀"+commandTarget+"。");
          g_RumorChat->talk(NULL,"<font color="+g_Settings->getrumorChatColor()+">【谣言】"
              +"某人: 据江湖传言有人悬赏"+sShowMoney+"取"+commandTarget+"的人头!</font>",NULL,NULL,CHANNEL_MSG);
          break;
        }
      }
      if(i>=MAXNUMBER){ //说明添加失败，项目已经满
        player->display(MyName+"为难地说：目前的悬赏已经够多了!");
        return 1;
      }
    }
    //
    nCash-=nMoney; //现金数字减去赏金
    long nYourGold,nYourSilver,nYourCoin;
    nYourGold=nCash/10000;
    nYourSilver=(nCash-nYourGold*10000)/100;
    nYourCoin=nCash%100;
    if(nYourGold!=0){
      objMoney=(YThing*)player->findChildThing("金子");
      if(!objMoney){
        objMoney=(YThing*)loadObject("thing/金子");
        if(!objMoney){
          g_err.show("[YOfferRewardNPC::beXuanshang]loadObject thing/金子 is NULL");
          return 1;
        }
        player->addChild(objMoney);
      }
      objMoney->setCount(nYourGold);
    }
    else if(nYourGold==0){
      objMoney=(YThing*)player->findChildThing("金子");
      if(objMoney){
        if(player->removeChild(objMoney)){
          delete objMoney;
        }
      }
    }
    if(nYourSilver!=0){
      objMoney=(YThing*)player->findChildThing("银子");
      if(!objMoney){
        objMoney=(YThing*)loadObject("thing/银子");
        if(!objMoney){
          g_err.show("[YOfferRewardNPC::beXuanshang]loadObject thing/银子 is NULL");
          return 1;
        }
        player->addChild(objMoney);
      }
      objMoney->setCount(nYourSilver);
    }
    else if(nYourSilver==0){
      objMoney=(YThing*)player->findChildThing("银子");
      if(objMoney){
        if(player->removeChild(objMoney)){
          delete objMoney;
        }
      }
    }
    if(nYourCoin!=0){
      objMoney=(YThing*)player->findChildThing("铜板");
      if(!objMoney){
        objMoney=(YThing*)loadObject("thing/铜板");
        if(!objMoney){
          g_err.show("[YOfferRewardNPC::beXuanshang]loadObject thing/铜板 is NULL");
          return 1;
        }
        player->addChild(objMoney);
      }
      objMoney->setCount(nYourCoin);
    }
    else if(nYourCoin==0){
      objMoney=(YThing*)player->findChildThing("铜板");
      if(objMoney){
        if(player->removeChild(objMoney)){
          delete objMoney;
        }
      }
    }
  }
  else{
    player->display(MyName+"对你说道：你要悬赏做什么？");
    return 1;
  }
  return 1;
}
//--------------------------------------------------------
//察看悬赏列表
int YOfferRewardNPC::beList(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString MyName=getActorName(); //NPC的名字
  YString cmd=command;
  YString commandTarget=cmd.getWord();//悬赏的对象(某人,某物...)
  YString sItem; //悬赏项目
  YString sType,sTarget,sMoney; //类型，目标，钱
  long nMoney,nGold,nSilver,nCoin; //总钱数和金，银，铜的数目
  YString sShowMoney; //显示的钱字符串
  long nNumber=0; //总的悬赏个数
  if(commandTarget==""){
    player->display("<font color=red>-----悬赏-----</font>");
  }
  int i;
  for(i=0;i<MAXNUMBER;i++){
    sItem=offerreward[i];
    sType=sItem.getWord();
    if(sType!="杀") continue; //空
    sTarget=sItem.getWord();
    if(commandTarget!=""){
      if(sTarget!=commandTarget) continue;
    }
    sMoney=sItem.getWord(); //赏金=NNNNN
    nMoney=sMoney.toLong(); //转化为长型
    nGold=nMoney/10000; //金
    nSilver=(nMoney-nGold*10000)/100; //银
    nCoin=nMoney%100; //铜
    sShowMoney="";
    if(nGold!=0){
      sShowMoney+=LongToChinese(nGold)+"两金子";
    }
    if(nSilver!=0){
      sShowMoney+=LongToChinese(nSilver)+"两银子";
    }
    if(nCoin!=0){
      sShowMoney+=LongToChinese(nCoin)+"文铜板";
    }
    player->display(sTarget+"的首级&nbsp;&nbsp;<font color=red>悬赏</font>："+sShowMoney);
    nNumber+=1;
    if(commandTarget!=""){ //查询某一个项目
      break;
    }
  }
  if(commandTarget==""){
    player->display("目前共有"+(YString)nNumber+"个人被悬赏。");
  }
  else{
    if(nNumber==0){
      player->display(MyName+"摇了摇头,对你说道：没有人悬赏杀这个人。");
      return 1;
    }
  }
  return 1;
}
//--------------------------------------------------------
//递交悬赏的物品
int YOfferRewardNPC::beGive(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString MyName=getActorName(); //NPC的名字
  YString cmd=command;
  YString msg;
  YString commandThing=cmd.getWord(); //要给的东西名
  YString command_To=cmd.getWord();//单词to
  YString commandTarget=cmd.getWord(); //给谁
  if((command_To!="to")||(commandTarget!=MyName)){
     player->display("命令格式错误。");
     player->display("正确的格式是:give <物品> to <人名>");
     return 1;
  }
  YAbstractThing* objThing=player->findChildThing(commandThing);
  if(!objThing){
     g_err.show("[YOfferRewardNPC::beGive]findChildThing_"+commandThing+" is NULL");
     player->display("你没有这种东西。");
     return 1;
  }
  //递交悬赏的物品
  long isOffer=getIsNotOfferReward(); //是否悬赏
  if(isOffer!=1){
    return YNPC::beGive(executor,command);
  }
  else{
    YString sItem; //悬赏项目
    YString sType,sTarget,sMoney; //类型，目标，钱
    long nMoney,nGold,nSilver,nCoin; //总钱数和金，银，铜的数目
    YString sShowMoney; //显示的钱字符串
    bool bFind=false; //是否找到
    int i;
    for(i=0;i<MAXNUMBER;i++){
      sItem=offerreward[i];
      sType=sItem.getWord();
      if(sType!="杀") continue; //空
      sTarget=sItem.getWord();
      if((sTarget+"的首级")==commandThing){
        long count=objThing->getCount();
        if(count<1){
          player->display("你没有这种东西。");
          return 1;
        }
        else if(count==1){
          if(player->removeChild(objThing)) delete objThing;
        }
        else{
          objThing->setCount(count-1);
        }
        msg="&s把"+commandThing+"递给"+MyName+"。";
        bFind=true; //找到
        sMoney=sItem.getWord(); //赏金=NNNNN
        nMoney=sMoney.toLong(); //转化为长型
        nGold=nMoney/10000; //金
        nSilver=(nMoney-nGold*10000)/100; //银
        nCoin=nMoney%100; //铜
        sShowMoney="";
        YThing *objMoney;
        if(nGold!=0){ //给金子
          objMoney=(YThing*)player->findChildThing("金子");
          if(!objMoney){
            objMoney=(YThing*)loadObject("thing/金子");
            if(!objMoney){
              g_err.show("[YOfferRewardNPC::beGive]loadObject thing/金子 is NULL");
              return 1;
            }
            objMoney->setCount(nGold);
            player->addChild(objMoney);
          }
          else{
            objMoney->setCount(objMoney->getCount()+nGold);
          }
          sShowMoney+=LongToChinese(nGold)+"两金子";
        }
        if(nSilver!=0){
          objMoney=(YThing*)player->findChildThing("银子");
          if(!objMoney){
            objMoney=(YThing*)loadObject("thing/银子");
            if(!objMoney){
              g_err.show("[YOfferRewardNPC::beGive]loadObject thing/银子 is NULL");
              return 1;
            }
            objMoney->setCount(nSilver);
            player->addChild(objMoney);
          }
          else{
            objMoney->setCount(objMoney->getCount()+nSilver);
          }
          sShowMoney+=LongToChinese(nSilver)+"两银子";
        }
        if(nCoin!=0){
          objMoney=(YThing*)player->findChildThing("铜板");
          if(!objMoney){
            objMoney=(YThing*)loadObject("thing/铜板");
            if(!objMoney){
              g_err.show("[YOfferRewardNPC::beGive]loadObject thing/铜板 is NULL");
              return 1;
            }
            objMoney->setCount(nCoin);
            player->addChild(objMoney);
          }
          else{
            objMoney->setCount(objMoney->getCount()+nCoin);
          }
          sShowMoney+=LongToChinese(nCoin)+"文铜板";
        }
        player->display("你得到了悬赏的"+sShowMoney);
        offerreward[i]=""; //清除此项目
        break;
      }
    }
    if(!bFind){ //没有找到
      player->display(MyName+"摇摇头说：我要的不是这个。");
      return 1;
    }
  }
  return 1;
}

