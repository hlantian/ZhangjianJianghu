//---------------------------------------------------------------------------
//
// ycollectroom.cpp    2001年1月31日
//
// 类YCollectRoom：采集职业原料的房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YCollectRoom::YCollectRoom(YString initFileName):YRoom(initFileName),m_MineTotal(0),
                                                                    m_MaxWinRate(0),
                                                                    m_MinWinRate(0),
                                                                    m_MineType("")
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YCollectRoom::isTypeOf(YString className)
{
  if(className=="YCollectRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YCollectRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setMineTotal(getAsLong("矿藏总数"));
  setMaxWinRate(getAsLong("最大成功率"));
  setMinWinRate(getAsLong("最小成功率"));
  setMineType(getAsString("矿藏种类"));

  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YCollectRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("矿藏总数",getMineTotal());
  set("最大成功率",getMaxWinRate());
  set("最小成功率",getMinWinRate());
  set("矿藏种类",getMineType());

  return retVal;
}

//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YCollectRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="caikuang") retVal=caikuang(executor);
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//采矿
int YCollectRoom::caikuang(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  if(player->getNowWork()==1){ //上次还没有结束
    player->set("劳动计时",0);
    player->setNowWork(0);//set("正在劳动",0);
    player->display("你挖了一会，没有挖出什么矿石来。");
    return 1; //上次没有结束时就再次输入，挖矿失败
  }
  //假设条件之第一点自动满足
  YString temp=player->getStatus(); //状态
  if(temp!=""){
     player->display("你现在正忙着呢。");
     return 1;
  } //至此，玩家“状态“确定为空
  long nBody=player->getBody(); //玩家气血
  if(nBody<=0){
     player->display("你太累了，还是休息一下吧。");
     return 1;
  }
  //假设条件之第三点满足
  long nMineSkillLevel=player->getAsLong("采矿");
  if(nMineSkillLevel<80){ //采矿技能等级超过80则不用检验采矿工具
    YString sTool=player->getWeaponName(); //劳动工具，武器
    if(sTool==""){ //没有任何工具
      player->display("你赤手空拳怎么采矿？");
      return 1;
    }
    YAbstractThing *objTool=player->findChildThing(sTool);
    if(!objTool){
      player->display("你的采矿工具没有装备好。");
      return 1;
    }
    long nIsNotMineTool=objTool->getAsLong("采矿"); //装备的武器是否采矿的工具
    if(nIsNotMineTool!=1){
      player->display("采矿要使用专门的工具。");
      return 1;
    } //至此，玩家持有工具，并且该工具的确是采矿工具
  } //假设条件之第二点满足
  //至此，假设条件全部满足
  
  long nMineTotal=getMineTotal(); //矿藏总数
  if(nMineTotal<=0){
    player->display("这里的矿已经采完了。");
    return 1;
  } //步骤1之a方案
  long nTimeSpan=rand()%9+2; //时间间隔2-10秒
  
  //福缘带来的时间节省，福缘100的劳动时间为2-4秒,节省6秒
  long naddluck = player->getAddLuck();
  long nLuck=player->getLuck(); //"福缘"
  nLuck = nLuck + naddluck;
  long nLuckTime=(nLuck-40)/10; //福缘带来的时间节省
  if(nLuckTime < 0) nLuckTime=0;
  if(nLuckTime > 6) nLuckTime=6; //最大福缘100，节省时间6秒
  nTimeSpan-=nLuckTime; //节省时间
  if(nTimeSpan < 2) nTimeSpan=2; //最少延时2秒
  //福缘节省时间
  
  player->display("你在地上挖了起来。");
  nBody-=nTimeSpan*10; //消耗气血
  if(nBody<=0) nBody=0; //最小为0
  player->setBody(nBody); //设置气血
  player->set("劳动计时",nTimeSpan*1000);
  player->setNowWork(1);//set("正在劳动",1);
  player->set("劳动","采矿");
  return 1;
}
//--------------------------------------------------------
//采矿结束
int YCollectRoom::caikuangEnd(YAbstractActor* executor)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  long nMaxWinRate=getMaxWinRate(); //最大成功率
  long nMinWinRate=getMinWinRate(); //最小成功率
  long nMineSkillLevel=player->getAsLong("采矿");
  float fFinalWinRate=(nMaxWinRate-nMinWinRate)*nMineSkillLevel/100.0+nMinWinRate; //确定成功率
  long nWinRate=(long)fFinalWinRate; //比如：30-90之间的整数
  long nRandom=rand()%100; //随机,0-99之间的整数
  if(nRandom>nWinRate){ //不能成功挖出矿
    player->display("你没有挖出任何矿石。");
    return 1;
  } //步骤2
  YString sMineName; //矿石的名字(铁矿，银矿...)
  YString sMineType=getMineType(); //"矿藏种类"
  long nAppearRate; //出现机率
  long nBaseAppearRate=0; //基础出现机率
  nRandom=rand()%1001; //0-1000随机整数
  while((sMineName=sMineType.getWord())!=""){
    nAppearRate=getAsLong(sMineName+"_出现机率");
    if((nRandom>nBaseAppearRate)&&(nRandom<(nAppearRate+nBaseAppearRate))){ //在一个区间里
      break; //选定这种矿石
    }
    else{
      nBaseAppearRate+=nAppearRate; //基数增加
    }
  }
  if(sMineName==""){ //没有随机到矿石名字，失败
    player->display("你没有挖出任何矿石。");
    return 1;
  } //矿石名字产生了
  YAbstractThing *objOre; //矿石对象的指针
  YMUDObject* obj=loadObject("thing/"+sMineName);
  if(!obj){
    g_err.show("[YCollectRoom::caikuangEnd]loadObject thing/"+sMineName+" is NULL");
    player->display("你挖出了一些没有用的矿石。");
    return 1;
  }
  if(obj->isTypeOf("YAbstractThing")){
    objOre=(YAbstractThing*)obj;
  }
  else{
    g_err.show("[YCollectRoom::caikuangEnd]loadObject thing/"+sMineName+" is not Thing(类名错误)");
    player->display("你挖出了一些没有用的矿石。");
    delete obj; //删除非法物品
    return 1;
  } //生成了一个矿石
  if(nMineSkillLevel < (objOre->getAsLong("开采要求"))){ //技能未达到开采要求
    player->display("你挖出了矿石，但是把它毁坏了。");
    delete objOre; //删除该物品
    return 1;
  } //步骤3
  //步骤4 暂时不启用
  long nInhereAppearNumber=getAsLong(sMineName+"_固有出现数量");
  if(nInhereAppearNumber<=0){
    player->display("你没有挖出任何矿石。");
    delete objOre; //删除该物品
    return 1;
  }
  long nInhereConsumeNumber=getAsLong(sMineName+"_固有消耗数量");
  if(nInhereConsumeNumber<=0){
    player->display("你没有挖出任何矿石。");
    delete objOre; //删除该物品
    return 1;
  }
  long nAppearNumber,nConsumeNumber; //出现和消耗的数量
  long nHalf; //一半数量
  if(nInhereAppearNumber>5){ //一般矿藏产量 > 5
    nHalf=nInhereAppearNumber*50/100; //产量的一半
    if(nHalf<=0) nHalf=1; //以防万一
    nRandom=rand()%(nHalf+1)+nHalf; //50%-100%随机
    if(nRandom<=0) nRandom=1; //最少为1
    nAppearNumber=nRandom; // 产量
  }
  else{
    nAppearNumber=nInhereAppearNumber; //否则等于固有出现数量
  }
  if(nInhereConsumeNumber<100){ //一般矿藏消耗 < 100
    nHalf=nInhereConsumeNumber*50/100; //消耗的一半
    if(nHalf<=0) nHalf=1; //以防万一
    nRandom=rand()%(nHalf+1)+nHalf; //50%-100%随机
    if(nRandom<=0) nRandom=1; //最少为1
    nConsumeNumber=nRandom; // 消耗
  }
  else{
    nConsumeNumber=nInhereConsumeNumber; //否则等于固有消耗数量
  } //步骤5
  long nMineTotal=getMineTotal(); //矿藏总数
  nMineTotal-=nConsumeNumber;
//  setMineTotal(nMineTotal);
  //步骤7

  objOre->setCount(nAppearNumber); //设置产量
  //步骤8
  addChild(objOre); //加入到本room里面
  
  //取出矿石的颜色
  YString sColorMineName=objOre->getAsString("显示名字"); //显示出来的带颜色的名字
  if(sColorMineName=="") sColorMineName=sMineName; //默认为名字
  
  if(player->getWeight()<player->getMaxWeight()){ //说明负重还没有满
    giveChildTo(objOre,player,nAppearNumber); //送给玩家
    player->display("你挖出了一些"+sColorMineName+"把它们放在自己的背包里。");
    player->resumWeight(); //计算负重百分比
  }
  else{
    player->display("你挖出了一些"+sColorMineName+"，但是感到太沉了。");
    player->display("你把一些"+sColorMineName+"放在了地上。");
  } //步骤9
    YString basic = "采矿";
    YString playerwork = player->getworkskills(); //所会技能，所有技能列表
    if ( playerwork.size() == 0 ) 
    {
       player->setworkskills(basic);
    }
    else
    {
        if (player->playerfindname(playerwork,basic)== 0)
        {
            playerwork = playerwork +" "+ basic;
            player->setworkskills(playerwork);
        }
   }
  YString fierce=player->getWeaponAttack();
  if (fierce.toLong() < 0)   //武器攻击力
  {
     fierce = "0" ;
  }
  player->set("采矿_经验",player->getAsLong("采矿_经验")+3+(fierce.toLong()-10)/10);
  long MyGradeExp=player->getAsLong("采矿_经验"); 
  long MySkillLevel=player->getSkillLevel("采矿");//getAsLong(type);  //级别
  if(MyGradeExp>=(MySkillLevel+1)*(MySkillLevel+1)*10){
    MyGradeExp-=(MySkillLevel+1)*(MySkillLevel+1)*10; 
    player->playerlevelup("采矿"); 
  }
  player->set("采矿_经验",MyGradeExp);
  long exp = player->getExperience();
  player->setExperience(exp+6);
  long Potential = player->getPotential();
  player->setPotential(Potential+3);
  return 1;
}


