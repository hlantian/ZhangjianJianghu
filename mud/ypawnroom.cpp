//---------------------------------------------------------------------------
//
// ypawnroom.cpp    2000年8月4日
//
// 类YPawnRoom：当铺
//
// 作者：刘鹏.张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YPawnRoom::YPawnRoom(YString initFileName):YRoom(initFileName),
                                            m_IsNotSell(""),
                                            m_SellThingNoChange(0),
                                            m_ChaKanFuYuan(0),
                                            m_PawnPercent(0),
                                            m_PawnThingList("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YPawnRoom::isTypeOf(YString className)
{
  if(className=="YPawnRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YPawnRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setIsNotSell(getAsString("是否收购"));
  setSellThingNoChange(getAsLong("销售物品不变"));
  setChaKanFuYuan(getAsLong("查看福缘"));
  setPawnPercent(getAsLong("典当百分比"));
  setPawnThingList(getAsString("物品"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YPawnRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("是否收购",getIsNotSell());
  set("销售物品不变",getSellThingNoChange());
  set("查看福缘",getChaKanFuYuan());
  set("典当百分比",getPawnPercent());
  set("物品",getPawnThingList());
  
  return retVal;
}

//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YPawnRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="sell") retVal=sell(executor,cmd);
  else if(commandVerb=="buy") retVal=buy(executor,cmd);
  else if(commandVerb=="list") retVal=list(executor,cmd);
  else if(commandVerb=="lookfy") retVal=lookfy(executor);
  //else if(commandVerb=="go") retVal=go(cmd.getWord());
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//---------------------------------------------
//卖东西给当铺
int YPawnRoom::sell(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  YString cmd=command;
  YString commandThing=cmd.getWord();
  long price;
  YNPC* objActor; //NPC类
  YAbstractThing *objThing;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString bossName=getBossName(); //老板名字
  YString msg;
  YAbstractActor *tempActor=findChildActor(bossName);
  if(!tempActor){
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if(tempActor->isTypeOf("YNPC")){
     objActor=(YNPC*)tempActor;
  }
  else{
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if(getIsNotSell()!="是"){ //是否收购，是否允许卖东西，注意：YString型
     player->display(bossName+"笑着说:我们这儿不收东西。");
     return 1;
  }
  objThing=player->findChildThing(commandThing);
  if(!objThing){
     msg=bossName+"哈哈一笑:别开玩笑了,你有没有这东西?";
     objActor->OutputMsg(player,msg);
     return 1;
  }
  //price=objActor->getAsLong(commandThing+"_价格");
  price=getPrice(player,commandThing); //得到物品价格
  if(price <= 0){
     msg=bossName+"不屑一顾地说:这种破烂值几个钱,还好意思来卖!";
     objActor->OutputMsg(player,msg);
     return 1;
  }
  long lThingCount=objThing->getCount();  //得到物品重量
  YString unit=((YThing*)objThing)->getQuantifier();//getAsString("量词");
  if(unit=="") unit="个";
  player->giveChildTo(objThing,objActor);
  if(lThingCount==1){
//     player->ActorAddFeatureChange();
     player->ActorAddRecoveryChange();
  }
  long gainMoney=price*getPawnPercent()/100; //卖东西得到的钱 ，典当百分比
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  YString priceString=""; //例:一两金子二十两银子五十文铜板
  if((goldnum=gainMoney/10000)!=0) priceString=LongToChinese(goldnum)+"两金子";
  if((silvernum=(gainMoney-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两银子";
  if((coinnum=gainMoney%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
  YThing *objMoney;
  if(goldnum!=0){
    objMoney=(YThing*)player->findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::sell]loadObject thing/金子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
      objMoney->setCount(0);
    }
    objMoney->setCount(objMoney->getCount()+goldnum);
  }
  if(silvernum!=0){
    objMoney=(YThing*)player->findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::sell]loadObject thing/银子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
      objMoney->setCount(0);
    }
    objMoney->setCount(objMoney->getCount()+silvernum);
  }
  if(coinnum!=0){
    objMoney=(YThing*)player->findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::sell]loadObject thing/铜板 is NULL");
        return 1;
      }
      player->addChild(objMoney);
      objMoney->setCount(0);
    }
    objMoney->setCount(objMoney->getCount()+coinnum);
  }
  msg="&s卖掉了一"+unit+commandThing+"给"+bossName+"。";
  objActor->OutputMsg(player,msg);
  player->display("你得到了"+priceString+"。");
  YString thingList=getPawnThingList(); //物品列表
  if(thingList=="") thingList=commandThing;
  else{
    YString tempStr,tempList;
    int i=0; //是否找到的标志
    tempList=thingList; //临时物品列表
    while((tempStr=tempList.getWord())!=""){
      if(tempStr==commandThing){
        i=1;
        break;
      }
    }
    if(i!=1){
      thingList+=" "+commandThing; //添加新物品
    }
  }
  setPawnThingList(thingList); //刷新物品列表
  player->resumWeight();
  return 1;
}
//---------------------------------------------
//从当铺买东西
int YPawnRoom::buy(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandThing=cmd.getWord();
  long price,numCash;
  YNPC *objActor;
  YAbstractThing *objThing;
  YString bossName=getBossName(); //老板名字
  YString msg;
  YAbstractActor *tempActor=findChildActor(bossName);
  if(!tempActor){
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if(tempActor->isTypeOf("YNPC")){
     objActor=(YNPC*)tempActor;
  }
  else{
     player->display(bossName+"不在这儿。");
     return 1;
  }
  YString sMyThingList=getPawnThingList(); //物品
  YString sThing="";
  int i=0;
  int count =0;
  while((sThing=sMyThingList.getWord())!=""){
    if(count++>200) {
      YString errmsg;
      errmsg="当铺物品超过200啦~~~~~~~~~~~~~~~！！！！！！！！！\n"+
        getPawnThingList()+"\n"+sThing;
      YErr::show(errmsg);
      break;
    }
    if(sThing==commandThing){
      i=1;
      break;
    }
  }
  if(i!=1){
    player->display(bossName+"对你说:很抱歉,本店没有这种东西。");
    return 1;
  }
  objThing=objActor->findChildThing(commandThing);
  if(!objThing)
  {
     msg=bossName+"对&s说:很抱歉,本店没有这种东西。";
     objActor->OutputMsg(player,msg);
     return 1;
  }
  if((player->getWeight()) > (player->getMaxWeight())){
    player->display(bossName+"对你说：你拿的东西太多了。");
    return 1;
  }
  YThing *objMoney;
  numCash=0;
  objMoney=(YThing*)player->findChildThing("金子");
  if(objMoney){
     numCash+=(objMoney->getCount())*10000;
  }
  objMoney=(YThing*)player->findChildThing("银子");
  if(objMoney){
     numCash+=(objMoney->getCount())*100;
  }
  objMoney=(YThing*)player->findChildThing("铜板");
  if(objMoney){
     numCash+=objMoney->getCount();
  }
  //price=objActor->getAsLong(commandThing+"_价格");
  price=getPrice(player,commandThing); //得到物品价格
  if(price <= 0){
    player->display("本物品价格错误，暂不出售！");
    return 1;
  }
  if(numCash<price){
     msg=bossName+"一撇嘴:开什么玩笑,你买的起吗?";
     objActor->OutputMsg(player,msg);
     return 1;
  }
  numCash-=price; //剩下的钱
  YString unit=((YThing*)objThing)->getQuantifier(); //"量词"
  if(unit=="") unit="个";
  objActor->giveChildTo(objThing,player); //卖给东西
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  YString priceString=""; //例:一两金子二十两银子五十文铜板
  if((goldnum=price/10000)!=0) priceString=LongToChinese(goldnum)+"两金子";
  if((silvernum=(price-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两银子";
  if((coinnum=price%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
  goldnum=numCash/10000; //剩余金
  silvernum=(numCash-goldnum*10000)/100; //剩余银
  coinnum=numCash%100; //剩余铜板
  if(goldnum!=0){
    objMoney=(YThing*)player->findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/金子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(goldnum);
  }
  else if(goldnum==0){
    objMoney=(YThing*)player->findChildThing("金子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(silvernum!=0){
    objMoney=(YThing*)player->findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/银子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(silvernum);
  }
  else if(silvernum==0){
    objMoney=(YThing*)player->findChildThing("银子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(coinnum!=0){
    objMoney=(YThing*)player->findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/铜板 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(coinnum);
  }
  else if(coinnum==0){
    objMoney=(YThing*)player->findChildThing("铜板");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  msg="&s从"+bossName+"那里买下了一"+unit+commandThing+"。";
  objActor->OutputMsg(player,msg);
  player->display("你花掉了"+priceString+"。");
  YString thingList=getPawnThingList(); //物品列表
  objThing=objActor->findChildThing(commandThing); //查找是否还有该物品
  if(!objThing){ //如无此物品,则从列表中删除
    thingList.removeWord(commandThing);
  }
  else{
    if(getSellThingNoChange()==1){ //销售物品不变
      objThing->setCount(objThing->getCount()+1); //数量+1等于不变
    }
    if(objThing->getCount()==0){ //如果此物品数量为0,则从列表中删除
      thingList.removeWord(commandThing);
      if(objActor->removeChild(objThing)){
        delete objThing;
      }
      //并且删除该非法物品
    }
  }
  setPawnThingList(thingList); //刷新物品列表
  player->resumWeight();
  return 1;
}
//---------------------------------------------
//列出物品清单
int YPawnRoom::list(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  YString cmd=command;
  YString commandThing=cmd.getWord();
  YString thingList,sth;//物品列表，物品
  YString unit; //量词单位
  long goldnum,silvernum,coinnum;//某物品值多少金，多少银，多少铜板
  long price;
  YString priceString="";
  YMUDObject *objActor;
  YAbstractThing *objThing;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString bossName=getBossName(); //老板名字
  objActor=findChildActor(bossName);
  if(!objActor) {
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if(commandThing=="")
  {
     thingList=getPawnThingList();//得到物品列表
     player->display("本店可以出售的物品有：");
     while((sth=thingList.getWord())!="") //得到一个物品
     {
        objThing=objActor->findChildThing(sth);
        if(objThing!=0)
        {
           if(objThing->getCount()!=0){
              priceString="";
              //price=objActor->getAsLong(sth+"_价格");
              price=getPrice(player,sth); //得到物品价格
              if((goldnum=price/10000)!=0) priceString=LongToChinese(goldnum)+"两金子";
              if((silvernum=(price-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两银子";
              if((coinnum=price%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
              unit=((YThing*)objThing)->getQuantifier();//getAsString("量词");
              if(unit=="") unit="个";
              player->display(LongToChinese(objThing->getCount())+unit+objThing->getDisplayName()+priceString);
           }
        }
     }
     return 1;
   }
   else
   {
     objThing=objActor->findChildThing(commandThing);
     if(objThing!=0)
     {
        if(objThing->getCount()==0){
           player->display("本店没有这种物品。");
        }
        else
        {
           //price=objActor->getAsLong(commandThing+"_价格");
           price=getPrice(player,commandThing); //得到物品价格
           if((goldnum=price/10000)!=0) priceString=LongToChinese(goldnum)+"两金子";
           if((silvernum=(price-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两银子";
           if((coinnum=price%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
           unit=((YThing*)objThing)->getQuantifier();//getAsString("量词");
           if(unit=="") unit="个";
           player->display(LongToChinese(objThing->getCount())+unit+commandThing+"&nbsp;"+priceString);
        }
        return 1;
     }
     else player->display("本店没有这种物品。");
   }
  return 1;
}

//---------------------------------------------
//查看福缘
int YPawnRoom::lookfy(YAbstractActor* executor)
{
  YPlayer* player;
  YMUDObject *objActor;
  YAbstractThing* objMoney;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString bossName=getBossName(); //老板名字
  objActor=findChildActor(bossName);
  if(!objActor) {
     player->display(bossName+"不在这儿。");
     return 1;
  }
  if (getChaKanFuYuan() == 1)
  {
  long nLuck=player->getLuck(); 
  long addLuck=player->getAddLuck(); 
  long nFeature=player->getFeature(); 
  long addFeature=player->getAddFeature(); 
  long numCash=0;
  objMoney=player->findChildThing("金子");
  if(objMoney){
     numCash+=(objMoney->getCount())*10000;
  }
  objMoney=player->findChildThing("银子");
  if(objMoney){
     numCash+=(objMoney->getCount())*100;
  }
  objMoney=player->findChildThing("铜板");
  if(objMoney){
     numCash+=objMoney->getCount();
  }
  if(numCash < 10000){
     player->display ("你身上没那么多现金！");
     return 1;
  }
  numCash-= 10000; //剩下的钱
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  goldnum=numCash/10000; //剩余金
  silvernum=(numCash-goldnum*10000)/100; //剩余银
  coinnum=numCash%100; //剩余铜板
  if(goldnum!=0){
    objMoney=player->findChildThing("金子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/金子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/金子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(goldnum);
  }
  else if(goldnum==0){
    objMoney=player->findChildThing("金子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(silvernum!=0){
    objMoney=player->findChildThing("银子");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/银子");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/银子 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(silvernum);
  }
  else if(silvernum==0){
    objMoney=player->findChildThing("银子");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  if(coinnum!=0){
    objMoney=player->findChildThing("铜板");
    if(!objMoney){
      objMoney=(YThing*)loadObject("thing/铜板");
      if(!objMoney){
        g_err.show("[YPawnRoom::buy]loadObject thing/铜板 is NULL");
        return 1;
      }
      player->addChild(objMoney);
    }
    objMoney->setCount(coinnum);
  }
  else if(coinnum==0){
    objMoney=player->findChildThing("铜板");
    if(objMoney){
      if(player->removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  player->display ("您的福缘是"+(YString)nLuck+"("+(YString)addLuck+"),容貌是"+(YString)nFeature+"("+(YString)addFeature+")！");
  player->display ("本次收费为1金子，谢谢惠顾！");
}
else{
  player->display ("本店没有这个服务！");
}
  return 1;
}

//------------------------------------------------------
//得到某物品价格
long YPawnRoom::getPrice(YPlayer* player,YString sThing)
{
  YString bossName=getBossName(); //老板名字
  YAbstractActor *pAbstractActor=findChildActor(bossName); //当铺老板指针
  if(!pAbstractActor) return -1; //返回-1，失败
  long lPrice=pAbstractActor->getAsLong(sThing+"_价格"); //经商NPC文件中的价格
  if(lPrice == 0){
    YAbstractThing *pAbstractThing=pAbstractActor->findChildThing(sThing); //物品指针
    if(!pAbstractThing){ //老板身上没有
      pAbstractThing=player->findChildThing(sThing); //物品指针
      if(!pAbstractThing){ //player身上没有
        return -1; //返回-1，失败
      }
    }
    lPrice=pAbstractThing->getAsLong("价格"); //物品文件中的属性"价格=100"
  }
  return lPrice;
}

