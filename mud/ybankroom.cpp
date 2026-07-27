//---------------------------------------------------------------------------
//
// ybankroom.cpp    2000年8月4日
//
// 类YBankRoom：钱庄
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YBankRoom::isTypeOf(YString className)
{
  if(className=="YBankRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//作为场所执行命令，已处理返回1，未处理返回0
int YBankRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="cun") retVal=cun(executor,cmd);
  else if(commandVerb=="qu") retVal=qu(executor,cmd);
  else if(commandVerb=="convert") retVal=convert(executor,cmd);
  else if(commandVerb=="check") retVal=check(executor);
  //else if(commandVerb=="go") retVal=go(cmd.getWord());
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//向钱庄存钱
int YBankRoom::cun(YAbstractActor* executor, YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandQuantifier=cmd.getWord(); //数量
  YString commandUnit=cmd.getWord(); //货币单位
  YString ChinaNum; //中国数量
  long num,numCash,numDeposit; //要存入的数量,身上现金数量,存款数量
  YAbstractThing *objThing;
  YString bossName=getBossName(); //老板名字
  if(!findChildActor(bossName)){
     player->display("这儿的老板不在。");
     return 1;
  }
  num=commandQuantifier.toLong(); //要存入的数量
  if(num <= 0){
     player->display(bossName+"眼睛一瞪：你在开什么玩笑！");
     return 1;
  }
  else if(num > 200){
    player->display(bossName+"呵呵一笑：一次存不了这么多钱。");
    return 1;
  }
  ChinaNum=LongToChinese(num); //long转换为中国数量
  if((commandUnit=="金子")||(commandUnit=="银子")||(commandUnit=="铜板")){
     objThing=player->findChildThing(commandUnit);
     if(!objThing){
       player->display("你身上没有"+commandUnit+"。");
       return 1;
     }
     numCash=objThing->getCount();
     if(num>numCash){
       player->display("你没有这么多的"+commandUnit+"。");
       return 1;
     }
     else if(num==numCash){
       if(player->removeChild(objThing)){
         delete objThing;
       }
     } //剩余量为0则删除
     else{
       objThing->setCount(numCash-num);
     }
     if(commandUnit=="金子") num*=10000;
     else if(commandUnit=="银子") num*=100;
     numDeposit=player->getDeposit();//getAsLong("存款");
     player->setDeposit(numDeposit+num);//set("存款",numDeposit+num);
     if(commandUnit=="铜板")
       player->display("你存进了"+ChinaNum+"文铜板。");
     else
       player->display("你存进了"+ChinaNum+"两"+commandUnit+"。");
  }
  else{
     player->display("钱庄只能存金子,银子或铜板.");
  }
  player->resumWeight();
  return 1;
}

//--------------------------------------------------------
//从钱庄取钱
int YBankRoom::qu(YAbstractActor* executor, YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString commandQuantifier=cmd.getWord();
  YString commandUnit=cmd.getWord();
  YString ChinaNum;
  long num,numBaseCoin,numDeposit; //要取出的数量,以铜板为单位的数量,存款数量
  YAbstractThing *objThing;

  YString bossName=getBossName(); //老板名字
  if(!findChildActor(bossName)){
     player->display("这儿的老板不在。");
     return 1;
  }
  num=commandQuantifier.toLong(); //取出的数量
  if(num <= 0){
     player->display(bossName+"眼睛一瞪:你在开什么玩笑！");
     return 1;
  }
  else if(num > 200){
    player->display(bossName+"呵呵一笑：一次取不了这么多钱。");
    return 1;
  }
  ChinaNum=LongToChinese(num); //中国数量
  if((commandUnit=="金子")||(commandUnit=="银子")||(commandUnit=="铜板")){
     if(num<=0){
       player->display("你要取多少"+commandUnit+"?");
       return 1;
     } //不能取出0个货币
     numDeposit=player->getDeposit();//getAsLong("存款");
     if(numDeposit==0){
       player->display("你在本钱庄没有存款.");
       return 1;
     }
     if(commandUnit=="金子") numBaseCoin=num*10000;
     else if(commandUnit=="银子") numBaseCoin=num*100;
     else numBaseCoin=num;
     if(numBaseCoin>numDeposit){
       player->display("你没有这么多的"+commandUnit+"。");
       return 1;
     } //要取出的钱大于存款
     else{
       player->setDeposit(numDeposit-numBaseCoin);//set("存款",numDeposit-numBaseCoin); //存款减少
       if(commandUnit=="铜板")
         player->display("你取出了"+ChinaNum+"文铜板。");
       else
         player->display("你取出了"+ChinaNum+"两"+commandUnit+"。");
       objThing=player->findChildThing(commandUnit);
       if(!objThing){
         objThing=(YAbstractThing*)loadObject("thing/"+commandUnit);
         if(!objThing){
           g_err.show("[YBankRoom::qu]loadObject"+commandUnit+"is NULL");
           return 1;
         }
         player->addChild(objThing);
         objThing->setCount(0); //新的数量为0的物品
       }
       objThing->setCount(objThing->getCount()+num);
     }
  }
  else{
     player->display("钱庄只能取出金子,银子或铜板.");
  }
  player->resumWeight();
  return 1;
}

//--------------------------------------------------------
//兑换货币
int YBankRoom::convert(YAbstractActor* executor, YString command)
{
  YPlayer* player;
  YString cmd=command;
  YString commandQuantifier;//源货币数量字符串
  YString command_To;//单词to
  YString commandUnitSrc,commandUnitDes;//源货币,目标货币
  YString ChinaNum;//中国数量(一,二...)
  long numSrc,numDes,numRemainder;//源数量,目标数量,剩余数量
  long rateSrc=1,rateDes=1;//源货币兑换比率,目标货币兑换比率
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString bossName=getBossName(); //老板名字
  if(!findChildActor(bossName)){
     player->display("这儿的老板不在。");
     return 1;
  }
  commandQuantifier=cmd.getWord();
  commandUnitSrc=cmd.getWord();
  command_To=cmd.getWord();
  commandUnitDes=cmd.getWord();
  numSrc=commandQuantifier.toLong();
  if(numSrc <= 0){
     player->display(bossName+"眼睛一瞪:你在开什么玩笑！");
     return 1;
  }
  else if(numSrc > 1000){
    player->display(bossName+"呵呵一笑：一次兑换不了这么多钱。");
    return 1;
  }
  if(command_To!="to"){
     player->display("convert <数量> <源货币单位> to <目标货币单位>");
     player->display("例如: convert 500 铜板 to 银子");
     return 1;
  }
  if(commandUnitSrc=="金子") rateSrc=10000;
  else if(commandUnitSrc=="银子") rateSrc=100;
  else if(commandUnitSrc=="铜板") rateSrc=1;
  else {
     player->display("convert <数量> <源货币单位> to <目标货币单位>");
     player->display("例如: convert 500 铜板 to 银子");
     return 1;
  }
  YAbstractThing* objThing=player->findChildThing(commandUnitSrc);
  if(!objThing){
     player->display("你身上没有"+commandUnitSrc+"。"); //player无此货币
     return 1;
  }
  if(numSrc>objThing->getCount()){
     player->display("你没有这么多"+commandUnitSrc+"。");
     return 1;
  }
  numSrc*=rateSrc;
  if(commandUnitDes=="金子") rateDes=10000;
  else if(commandUnitDes=="银子") rateDes=100;
  else if(commandUnitDes=="铜板") rateDes=1;
  else {
     player->display("convert <数量> <源货币单位> to <目标货币单位>");
     player->display("例如: convert 500 铜板 to 银子");
     return 1;
  }
  numDes=numSrc/rateDes;
  if (numDes < 1){
     return 1;
  }
  numRemainder=(numSrc%rateDes)/rateSrc;
  long overplus=objThing->getCount()-commandQuantifier.toLong()+numRemainder; //剩余数量
  if(overplus==0){
    if(player->removeChild(objThing)){
      delete objThing;
    }
  }
  else
    objThing->setCount(overplus);
  objThing=player->findChildThing(commandUnitDes); //目标货币
  if(!objThing){
     objThing=(YAbstractThing*)loadObject("thing/"+commandUnitDes);
     if(!objThing){
        g_err.show("[YBankRoom::convert]loadObject thing/"+commandUnitDes+" is NULL");
        return 1;
     }
     player->addChild(objThing);
     objThing->setCount(0);
  }   //如果player没有此货币,则制造此货币并给与player
  objThing->setCount(objThing->getCount()+numDes);
  ChinaNum=LongToChinese(numDes);
  if(commandUnitDes=="金子") player->display("你换到了"+ChinaNum+"两金子。");
  if(commandUnitDes=="银子") player->display("你换到了"+ChinaNum+"两银子。");
  if(commandUnitDes=="铜板") player->display("你换到了"+ChinaNum+"文铜板。");
  player->resumWeight();
  return 1;
}

//--------------------------------------------------------
//查询存款
int YBankRoom::check(YAbstractActor* executor)
{
  YPlayer* player;
  YString priceString;
  long goldnum,silvernum,coinnum,numDeposit;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;

  YString bossName=getBossName(); //老板名字
  if(!findChildActor(bossName)){
     player->display("这儿的老板不在。");
     return 1;
  }
  numDeposit=player->getDeposit();//getAsLong("存款");
  if(numDeposit>0)
  {
     if((goldnum=numDeposit/10000)!=0) priceString=LongToChinese(goldnum)+"两黄金";
     if((silvernum=(numDeposit-goldnum*10000)/100)!=0) priceString=priceString+LongToChinese(silvernum)+"两白银";
     if((coinnum=numDeposit%100)!=0) priceString=priceString+LongToChinese(coinnum)+"文铜板";
     player->display("您在本钱庄共存有"+priceString+"。");
  }
  else
     player->display("您在本钱庄没有存款。");
  return 1;
}

