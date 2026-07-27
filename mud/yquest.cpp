//---------------------------------------------------------------------------
//
// yquest.h    2000年9月12日
//
// 类YQuest：任务
//
// 作者：张勇(zhy)   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmud.h"

//---------------------------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YQuest::isTypeOf(YString className)
{
  if(className=="YQuest") return 1;
  else return YMUDObject::isTypeOf(className);
}

//---------------------------------------------------------------------------
//随机返回一个任务的序号(Sequence number,简称number)
long YQuest::randomReturnQuestNumber(void)
{
  long questTotalNumber=getAsLong("任务总数");
  long randomNumber=rand()%questTotalNumber+1;
  return randomNumber;
  //return 122;
}
//---------------------------------------------------------------------------
//返回指定(Specify)序号的任务类型
YString YQuest::specifyNumberQuestType(long number)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString questType=questMessage.getWord(); //类型
  return questType;
}
//---------------------------------------------------------------------------
//返回指定序号的任务目标
YString YQuest::specifyNumberQuestTarget(long number)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  temp=questMessage.getWord(); //类型
  YString questTarget=questMessage.getWord(); //目标
  return questTarget;
}
//---------------------------------------------------------------------------
//返回指定序号,连续次数的任务奖励经验
long YQuest::questRewardExp(long number,long times)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<3;i++) temp=questMessage.getWord();
  long rewardExpBase=temp.toLong(); //基数
  float randomMultiple=(rand()%31+30)/10.0;  //3-6倍
  long endRewardExp=(long)((rewardExpBase+times)*randomMultiple);
  long nMax=g_Settings->getsitQuestExpUpLimit();//getAsLong("任务奖励经验上限");
  if(endRewardExp > nMax) endRewardExp=nMax; //最大不能超过nMax
  return endRewardExp;
}
//---------------------------------------------------------------------------
//返回指定序号,连续次数的任务奖励潜能
long YQuest::questRewardPotential(long number,long times)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<4;i++) temp=questMessage.getWord();
  long rewardPotentialBase=temp.toLong(); //基数
  float randomMultiple=(rand()%11+40)/10.0; //4-5倍
  long endRewardPotential=(long)((rewardPotentialBase+times)*randomMultiple);
  long nMax=g_Settings->getsitQuestQianUpLimit();//getAsLong("任务奖励潜能上限");
  if(endRewardPotential > nMax) endRewardPotential=nMax; //最大不能超过nMax
  return endRewardPotential;
}
//---------------------------------------------------------------------------
//返回指定序号,连续次数的任务奖励评价
long YQuest::questRewardAppraise(long number,long times)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<5;i++) temp=questMessage.getWord();
  long rewardAppraiseBase=temp.toLong(); //基数
  double randomMultiple=(rand()%16+5)/10.0;
  long endRewardAppraise=(long)((double)(rewardAppraiseBase+times)/randomMultiple);
  return endRewardAppraise;
}
//---------------------------------------------------------------------------

//返回指定序号,任务银子
long YQuest::questRewardMoney(long number,long times)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<4;i++) temp=questMessage.getWord();
  long rewardPotentialBase=temp.toLong(); //基数
  float randomMultiple=(rand()%21+40)/10.0; //4-6倍
  if (times > 500) times = 500;
  long endRewardPotential=(long)((rewardPotentialBase+times)*randomMultiple);
  return endRewardPotential;
}

//返回指定序号的任务物品
YString YQuest::specifyNumberQuestThing(long number)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<6;i++) temp=questMessage.getWord();
  YString questThing=temp; //物品
  return questThing;
}
//---------------------------------------------------------------------------
//返回指定序号的任务时间
long YQuest::specifyNumberQuestTime(long number)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<7;i++) temp=questMessage.getWord();
  long questTime=temp.toLong(); //时间以微秒为单位
  return questTime;
}
//---------------------------------------------------------------------------
//返回指定序号的任务目标类型
YString YQuest::specifyNumberQuestTargetType(long number)
{
  YString questMessage=getAsString("任务"+(YString)number);
  YString temp;
  for(int i=0;i<6;i++) temp=questMessage.getWord();
  YString questTargetType=temp; //物品
  return questTargetType;
}
//---------------------------------------------------------------------------
//返回所有发放任务的NPC名字，以空格分隔
YString YQuest::getAllNPCName(void)
{
	return enumChildren("","");
}

