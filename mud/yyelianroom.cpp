//---------------------------------------------------------------------------
//
// yyelianroom.cpp    2001年2月12日
//
// 类YYelianRoom：冶炼矿石的房间
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//--------------------------------------------------------
//构造函数
YYelianRoom::YYelianRoom(YString initFileName):YRoom(initFileName),
                                              m_MaxWinRate(0),
                                              m_MinWinRate(0)
{
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YYelianRoom::isTypeOf(YString className)
{
  if(className=="YYelianRoom") return 1;
  else return YRoom::isTypeOf(className);
}
//--------------------------------------------------------
//事件AfterLoad的默认处理函数
int YYelianRoom::onAfterLoad(void)
{
  int retVal=YRoom::onAfterLoad();
  
  setMaxWinRate(getAsLong("最大成功率"));
  setMinWinRate(getAsLong("最小成功率"));
  return retVal;
}
//--------------------------------------------------------
//事件BeforeSave的默认处理函数
int YYelianRoom::onBeforeSave(void)
{
  int retVal=YRoom::onBeforeSave();
  
  set("最大成功率",getMaxWinRate());
  set("最小成功率",getMinWinRate());
  
  return retVal;
}

//--------------------------------------------------------
//执行命令，已处理返回1，未处理返回0
int YYelianRoom::executeCommand(YAbstractActor* executor, YString command)
{
  int retVal=0;
  YString cmd=command;
  YString commandVerb=cmd.getWord();
  if(commandVerb=="yelian") retVal=yelian(executor,cmd);
  else if(commandVerb=="dazao") retVal=dazao(executor,cmd);
  else if(commandVerb=="list") retVal=list(executor);  
  else {
    //do nothing
  }
  if(!retVal) return YRoom::executeCommand(executor, command);
  else return retVal;
}
//--------------------------------------------------------
//冶炼
int YYelianRoom::yelian(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString temp=player->getStatus(); //状态
  if(temp!=""){
     player->display("你现在正忙着呢。");
     return 1;
  } //至此，玩家“状态“确定为空
  YString cmd=command;
  YString commandThing=cmd.getWord();
  if(commandThing==""){
    player->display("你要冶炼什么？");
    return 1;
  }
  YString commandCount=cmd.getWord();
  long nOreCount=commandCount.toLong(); //矿石数量
  if(nOreCount <= 1) nOreCount=1; //最少一块
  else if(nOreCount > 200) nOreCount=200; //最多200块
  YAbstractThing *objOre=player->findChildThing(commandThing);
  if(!objOre){
    player->display("你没有这件东西。");
    return 1;
  } //步骤1
  if(objOre->getAsLong("矿石")!=1){
    player->display(commandThing+"不是矿石。");
    return 1;
  }
  YString sBlockName=objOre->getAsString("冶炼以后");
  if(sBlockName==""){
    player->display(commandThing+"不是矿石。");
    return 1;
  }
  long nSmeltSkillLevel=player->getAsLong("冶炼");
  if(nSmeltSkillLevel < (objOre->getAsLong("冶炼要求"))){
    player->display("你的技能不足以冶炼"+commandThing);
    return 1;
  }
  //步骤2
  long count=objOre->getCount();
  if(nOreCount > count) nOreCount=count; //步骤3
  long nMaxWinRate=getMaxWinRate(); //最大成功率
  long nMinWinRate=getMinWinRate(); //最小成功率

  float fFinalWinRate=(nMaxWinRate-nMinWinRate)*nSmeltSkillLevel/100.0+nMinWinRate; //确定成功率
  long nWinRate=(long)fFinalWinRate; //比如：30-100之间的整数
  long nRandom=rand()%100; //随机,0-99之间的整数
  if(nRandom>nWinRate){ //不能成功冶炼
    player->display("你冶炼矿石失败。");
    player->set("冶炼_经验",player->getAsLong("冶炼_经验")+1);
    count-=1; //损失一块
    if(count<=0){
      if(player->removeChild(objOre)) delete objOre;
    }
    else{
      objOre->setCount(count);
    }
    return 1;
  }
  //冶炼成功则继续

  YAbstractThing *objBlock; //矿块
  YMUDObject* obj=loadObject("thing/"+sBlockName);
  if(!obj){
    g_err.show("[YCollectRoom::yelian]loadObject thing/"+sBlockName+" is NULL");
    player->display("你冶炼出的矿块不存在。");
    return 1;
  }
  if(obj->isTypeOf("YAbstractThing")){
    objBlock=(YAbstractThing*)obj;
  }
  else{
    g_err.show("[YCollectRoom::yelian]loadObject thing/"+sBlockName+" is not Thing(类名错误)");
    player->display("你冶炼出的矿块不是物品。");
    delete obj; //删除非法物品
    return 1;
  } //生成了一个矿块
  count-=nOreCount;
  if(count<=0){
    if(player->removeChild(objOre)) delete objOre;
  }
  else{
    objOre->setCount(count);
  } //减少数量
  player->resumWeight(); //计算负重百分比
  objBlock->setCount(nOreCount); //和消耗矿石数量相同的矿块
  addChild(objBlock); //加入到本room里面
  
  //取出矿石的颜色
  YString sColorBlockName=((YThing*)objBlock)->getThingFontName();//getAsString("显示名字"); //显示出来的带颜色的名字
  if(sColorBlockName=="") sColorBlockName=sBlockName; //默认为名字
  
  if(player->getWeight()<player->getMaxWeight()){ //说明负重还没有满
    giveChildTo(objBlock,player,nOreCount); //送给玩家
    player->display("你冶炼出了一些"+sColorBlockName+"把它们放在自己的背包里。");
    player->resumWeight(); //计算负重百分比
  }
  else{
    player->display("你冶炼出了一些"+sColorBlockName+"，但是感到太沉了。");
    player->display("你把一些"+sColorBlockName+"放在了地上。");
  }
    YString basic = "冶炼";
    YString playerwork = player->getworkskills(); //所会技能，所有技能列表
    if ( playerwork.size() == 0 ) //判断是否有这种基本武功
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
  player->set("冶炼_经验",player->getAsLong("冶炼_经验")+3);
  long MyGradeExp=player->getAsLong("冶炼_经验"); 
  long MySkillLevel=player->getSkillLevel("冶炼");//getAsLong(type);  //级别
  if(MyGradeExp>=(MySkillLevel+1)*(MySkillLevel+1)*10){
    MyGradeExp-=(MySkillLevel+1)*(MySkillLevel+1)*10; 
    player->playerlevelup("冶炼"); 
  }
  player->set("冶炼_经验",MyGradeExp);
  long exp = player->getExperience();
  player->setExperience(exp+2);
  long Potential = player->getPotential();
  player->setPotential(Potential+1);
  return 1;
}
//--------------------------------------------------------
//查看打造列表
int YYelianRoom::list(YAbstractActor* executor)
{
	YPlayer* player;
  	if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  	else return 1;	
	YString dazaoList=getAsString("打造列表");
	player->display("这里可以打造的物品为:"+dazaoList);
	return 1;
}

//--------------------------------------------------------
//打造
int YYelianRoom::dazao(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  if(player->getNowWork()==1){ //上次还没有结束
    player->set("劳动计时",0);
    player->setNowWork(0);//set("正在劳动",0);
    player->set("劳动制作","");
    player->display("你太心急了，结果打造失败了。");
    return 1; //上次没有结束时就再次输入，打铁失败
  }
  YString cmd=command;
  YString commandThing=cmd.getWord();
  if(commandThing==""){
    player->display("你要打造什么？");
    return 1;
  }
  YString temp=player->getStatus(); //状态
  if(temp!=""){
     player->display("你现在正忙着呢。");
     return 1;
  } //至此，玩家“状态“确定为空
  long nStithySkillLevel=player->getAsLong("打铁");
  if(nStithySkillLevel<80){ //打铁技能等级超过100则不用检验打铁工具
    YString sTool=player->getWeaponName(); //劳动工具 ，武器
    if(sTool==""){ //没有任何工具
      player->display("你赤手空拳怎么打铁？");
      return 1;
    }
    YAbstractThing *objTool=player->findChildThing(sTool);
    if(!objTool){
      player->display("你的打铁工具没有装备好。");
      return 1;
    }
    long nIsNotStithyTool=objTool->getAsLong("打铁"); //装备的武器是否打铁的工具
    if(nIsNotStithyTool!=1){
      player->display("打铁要使用专门的工具。");
      return 1;
    } //至此，玩家持有工具，并且该工具的确是打铁工具
  }
  long nBody=player->getBody(); //玩家气血
  if(nBody<=0){
     player->display("你太累了，还是休息一下吧。");
     return 1;
  } //至此玩家气血大于0
  YString sMaterialList=getAsString("制作_"+commandThing); //打造该物品的原料列表
  if(sMaterialList==""){
     player->display("这种物品无法打造。");
     return 1;
  }
  YString sMaterial,sCount; //原料，数量(字符串)
  long nCount; //数量(整型)
  long count;
  YAbstractThing *objBlock;
  while((sMaterial=sMaterialList.getWord())!=""){
    objBlock=player->findChildThing(sMaterial);
    if(!objBlock){
      player->display("你的原料不足，缺少"+sMaterial);
      return 1;
    }
    sCount=sMaterialList.getWord();
    nCount=sCount.toLong();
    if(nCount<=0){
      player->display("该物品的制作方法有误，请联系巫师解决。");
      return 1;
    }
    count=objBlock->getCount();
    if(nCount > count){
      player->display("你的原料不足，缺少"+sMaterial);
      return 1;
    }
  } //原料齐全
  YAbstractThing *objThing; //铁器
  YMUDObject* obj=loadObject("thing/"+commandThing);
  if(!obj){
    g_err.show("[YCollectRoom::dazao]loadObject thing/"+commandThing+" is NULL");
    player->display("你要打造的物品不存在。");
    return 1;
  }
  if(obj->isTypeOf("YAbstractThing")){
    objThing=(YAbstractThing*)obj;
  }
  else{
    g_err.show("[YCollectRoom::dazao]loadObject thing/"+commandThing+" is not Thing(类名错误)");
    player->display("你要打造的不是物品。");
    delete obj; //删除非法物品
    return 1;
  } //产生物品
  if(nStithySkillLevel < (objThing->getAsLong("打造要求"))){ //技能未达到打造要求
    player->display("你的技能不足以打造"+commandThing+"，技能要求为"+(YString)objThing->getAsLong("打造要求"));
    delete objThing; //删除该物品
    return 1;
  } //察看打造要求
  //
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
  
  player->display("你拿起工具，开始打造"+commandThing+"。");
  nBody-=nTimeSpan*10; //消耗气血
  if(nBody<=0) nBody=0; //最小为0
  player->setBody(nBody); //设置气血
  player->set("劳动计时",nTimeSpan*1000);
  player->setNowWork(1);//set("正在劳动",1);
  player->set("劳动","打铁");
  player->set("劳动制作",commandThing);
  delete objThing; //删除该物品
  return 1;
}
//--------------------------------------------------------
//打造结束
int YYelianRoom::dazaoEnd(YAbstractActor* executor,YString command)
{
  YPlayer* player;
  if(executor->isTypeOf("YPlayer")) player=(YPlayer*)executor;
  else return 1;
  YString commandThing=command;
  YString sMaterialList=getAsString("制作_"+commandThing);
  if(sMaterialList==""){
     player->display("这种物品无法打造。");
     return 1;
  }
  YString sMaterial,sCount; //原料，数量(字符串)
  long nCount; //数量(整型)
  long count;
  YAbstractThing *objBlock;
  while((sMaterial=sMaterialList.getWord())!=""){
    objBlock=player->findChildThing(sMaterial);
    if(!objBlock){
      player->display("你的原料不足，缺少"+sMaterial);
      return 1;
    }
    sCount=sMaterialList.getWord();
    nCount=sCount.toLong();
    if(nCount<=0){
      player->display("该物品的制作方法有误，请联系巫师解决。");
      return 1;
    }
    count=objBlock->getCount();
    if(nCount > count){
      player->display("你的原料不足，缺少"+sMaterial);
      return 1;
    }
    else count-=nCount; //消耗原料
    if(count<=0){
      if(player->removeChild(objBlock)) delete objBlock;
    }
    else{
      objBlock->setCount(count);
    }
  } //消耗原料完毕
  player->resumWeight(); //计算负重百分比
  
  long nMaxWinRate=getMaxWinRate(); //最大成功率
  long nMinWinRate=getMinWinRate(); //最小成功率
  long nStithySkillLevel=player->getAsLong("打铁");
  float fFinalWinRate=(nMaxWinRate-nMinWinRate)*nStithySkillLevel/100.0+nMinWinRate; //确定成功率
  long nWinRate=(long)fFinalWinRate; //比如：30-100之间的整数
  long nRandom=rand()%100; //随机,0-99之间的整数
  if(nRandom>nWinRate){ //不能成功打造
    player->display("你打造"+commandThing+"失败。");
    return 1;
  }
  YAbstractThing *objThing; //铁器
  YMUDObject* obj=loadObject("thing/"+commandThing);
  if(!obj){
    g_err.show("[YCollectRoom::dazaoEnd]loadObject thing/"+commandThing+" is NULL");
    player->display("你要打造的物品不存在。");
    return 1;
  }
  if(obj->isTypeOf("YAbstractThing")){
    objThing=(YAbstractThing*)obj;
  }
  else{
    g_err.show("[YCollectRoom::dazaoEnd]loadObject thing/"+commandThing+" is not Thing(类名错误)");
    player->display("你要打造的不是物品。");
    delete obj; //删除非法物品
    return 1;
  } //产生物品
  long dzdj = ((YThing*)objThing)->getAsLong("打造要求");
  if (dzdj>0) dzdj=dzdj/5;
  else dzdj=0;
  objThing->setCount(1); //数量为1
  addChild(objThing); //加入到本room里面
  YString sUnit=((YThing*)objThing)->getQuantifier();//getAsString("量词");
  if(sUnit=="") sUnit="个"; //默认
  
  //取出矿石的颜色
  YString sColorThingName=((YThing*)objThing)->getThingFontName();////getAsString("显示名字"); //显示出来的带颜色的名字
  if(sColorThingName=="") sColorThingName=commandThing; //默认为名字

  if(player->getWeight()<player->getMaxWeight()){ //说明负重还没有满
    giveChildTo(objThing,player,1); //送给玩家
    player->display("你打造出了一"+sUnit+sColorThingName+"把它们放在自己的背包里。");
    player->resumWeight(); //计算负重百分比
  }
  else{
    player->display("你打造出了一"+sUnit+sColorThingName+"，但是感到太沉了。");
    player->display("你把一"+sUnit+sColorThingName+"放在了地上。");
  }

    YString basic = "打铁";
    YString playerwork = player->getworkskills(); //所会技能，所有技能列表
    if ( playerwork.size() == 0 ) //判断是否有这种基本武功
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
  player->set("打铁_经验",player->getAsLong("打铁_经验")+dzdj+(fierce.toLong()+20)/10);
  long MyGradeExp=player->getAsLong("打铁_经验"); 
  long MySkillLevel=player->getSkillLevel("打铁");//getAsLong(type);  //级别
  if(MyGradeExp>=(MySkillLevel+1)*(MySkillLevel+1)*10){
    MyGradeExp-=(MySkillLevel+1)*(MySkillLevel+1)*10; 
    player->playerlevelup("打铁"); 
  }
  player->set("打铁_经验",MyGradeExp);
  long exp = player->getExperience();
  player->setExperience(exp+6);
  long Potential = player->getPotential();
  player->setPotential(Potential+3);
  return 1;
}

