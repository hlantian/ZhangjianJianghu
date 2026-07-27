//---------------------------------------------------------------------------
//
// yquest.h    2000年9月12日
//
// 类YQuest：武功招数
//
// 作者：张勇(zhy)   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YQUEST_H__
#define __YQUEST_H__

class YQuest : public YMUDObject{

  public:
    YQuest(YString filename):YMUDObject(filename){disableTimer();};  //构造函数
    virtual ~YQuest(){}; //析构函数

    //方法isTypeOf--是否是某种类型或其派生类型
    virtual int isTypeOf(YString className);
    
    //随机返回一个任务的序号(Sequence number,简称number)
    long randomReturnQuestNumber(void);
    //返回指定(Specify)序号的任务类型
    YString specifyNumberQuestType(long number);
    //返回指定序号的任务目标
    YString specifyNumberQuestTarget(long number);
    //返回指定序号,连续次数的任务奖励经验
    long questRewardExp(long number,long times);
    //返回指定序号,连续次数的任务奖励潜能
    long questRewardPotential(long number,long times);
    //返回指定序号,连续次数的任务奖励评价
    long questRewardAppraise(long number,long times);
    //返回指定序号,任务银子
    long questRewardMoney(long number,long times);
    //返回指定序号的任务物品(送专用)
    YString specifyNumberQuestThing(long number);
    //返回指定序号的任务时间(送,屠城专用)
    long specifyNumberQuestTime(long number);
    //返回指定序号的任务目标类型(屠城专用)
    YString specifyNumberQuestTargetType(long number);
    
    //返回所有发放任务的NPC名字，以空格分隔
    YString getAllNPCName(void);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};
};

#endif //__YQUEST_H__
