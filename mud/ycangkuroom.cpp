//---------------------------------------------------------------------------
//
// Ycangkuroom.cpp    2004年8月27日
//
// 类Ycangkuroom：仓库的房间
//
// 作者：龚丽炜
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
Ycangkuroom::Ycangkuroom(YString initFileName):YRoom(initFileName)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int Ycangkuroom::isTypeOf(YString className)
{
  if(className=="Ycangkuroom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------

//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int Ycangkuroom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="daxiao") retVal=daxiao(executor,cmd);       //赌大小
  else if(commandVerb=="dianshu") retVal=dianshu(executor,cmd);    //赌点数
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//-----------------------------------------------------------------
//--------------------------------------------------------
//赌大小
int Ycangkuroom::daxiao(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString dx=cmd.getWord();   //大小
  YString Count=cmd.getWord(); 
  long howmuch=Count.toLong();    //赌的金子数
  if (dx == ""){
  	player->display("您是赌大还是赌小呢！");
  	return 1;
  }
  if (dx != "大" && dx != "小"){
  	player->display("您是赌大还是赌小呢！");
  	return 1;
  }
  if (howmuch > 100)
  {
  	player->display("这里赌注上限为100金子！");
  	return 1;
  }
  else if ( howmuch > 0 ) 
  {
//  	howmuch=howmuch;
  }
  else
  {
  	howmuch = 0;
  	player->display("就压这么点钱还赌什么，赶快回去睡觉吧！");
  	return 1;
  }
  long numCash=0;
  YThing *objMoney;
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
  long moneycount = howmuch * 10000;
  if(numCash < moneycount){
     player->display ("你身上没那么多现金！");
     return 1;
  }
  player->display("你压了"+(YString)howmuch+"金子，庄家拿起骰子摇了起来！");	  
  long dian=(rand() % 6)+1;
  long naddluck = player->getAddLuck();
  long nlock=player->getLuck();
  nlock = nlock +  naddluck;
  YString jilv; 
  if (dian == 1)
  {
     jilv = "小";
  }
  else if (dian == 2)
  {
     jilv = "小";
  }
  else if (dian == 3)
  {
     jilv = "小";
  }
  else if (dian == 4)
  {
     jilv = "大";
  }
  else if (dian == 5)
  {
     jilv = "大";
  }
  else if (dian == 6)
  {
     jilv = "大";
  }
  long jl=(rand() % 100)+1;
  if (jl > nlock )
  {
    if (dx == "大")
     {  
       jilv = "小";
       dian = (rand() % 3)+1;
     }
    else
     {
      jilv = "大";
      dian = rand()%3+4;
     }
  }
  player->display("骰子停了下来，点数是"+(YString)dian+"，<font color=red>"+jilv+"！！！</font>");	  
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  if (dx != jilv)
  { 
    numCash-= moneycount; //剩下的钱
    player->display("你输了"+(YString)howmuch+"金子！");
   }	
  else
  { 
    numCash+= moneycount; //剩下的钱
    player->display("你赢了"+(YString)howmuch+"金子！");	
  }
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
      if(removeChild(objMoney)){
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
      if(removeChild(objMoney)){
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
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  return 1;
}

//--------------------------------------------------------
//赌点数
int Ycangkuroom::dianshu(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString cmd=command;
  YString dx=cmd.getWord();   //点数
  YString count=cmd.getWord(); 
  long howmuch=count.toLong();    //赌的金子数
  if (dx == ""){
  	player->display("您是赌几点呢！");
  	return 1;
  }
  if (dx != "1" && dx != "2" && dx != "3" && dx != "4" && dx != "5" && dx != "6"){
  	player->display("您是赌几点呢！");
  	return 1;
  }
  if (howmuch > 100)
  {
  	player->display("这里赌注上限为100金子！");
  	return 1;
  }
  else if ( howmuch > 0 ) 
  {
//  	howmuch=howmuch;
  }
  else
  {
  	howmuch = 0;
  	player->display("就压这么点钱还赌什么，赶快回去睡觉吧！");
  	return 1;
  }
  long numCash=0;
  YThing *objMoney;
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
  long moneycount = howmuch * 10000;
  if(numCash < moneycount){
     player->display ("你身上没那么多现金！");
     return 1;
  }
  player->display("你压了"+(YString)howmuch+"金子，庄家拿起骰子摇了起来！");	   
  long dian=(rand() % 6)+1;
  long naddluck = player->getAddLuck();
  long nlock=player->getLuck();
  nlock = nlock +  naddluck;
  YString jilv; 
  if (dian == 1)
  {
     jilv = "1";
  }
  else if (dian == 2)
  {
     jilv = "2";
  }
  else if (dian == 3)
  {
     jilv = "3";
  }
  else if (dian == 4)
  {
     jilv = "4";
  }
  else if (dian == 5)
  {
     jilv = "5";
  }
  else if (dian == 6)
  {
     jilv = "6";
  }
  long jl=(rand() % 100)+1;
  if (jl > nlock)
  {
    if (dx != "5")
    {
      jilv = "5";
      dian = 5;
    }
    else{
      jilv = "2";
      dian = 2;
    }
  }
  player->display("骰子停了下来，点数是<font color=red>"+(YString)dian+"</font>！！！");
  long goldnum,silvernum,coinnum;//多少金，多少银，多少铜板
  if (dx != jilv)
  { 
    numCash-= moneycount; //剩下的钱
    player->display("你输了"+(YString)howmuch+"金子！");
  }
  else
  { 
    moneycount = moneycount * 5;
    numCash+= moneycount; //剩下的钱
    moneycount = moneycount/10000;
    player->display("你赢了"+(YString)moneycount+"金子！");	
  }
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
      if(removeChild(objMoney)){
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
      if(removeChild(objMoney)){
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
      if(removeChild(objMoney)){
        delete objMoney;
      }
    }
  }
  return 1;
}
