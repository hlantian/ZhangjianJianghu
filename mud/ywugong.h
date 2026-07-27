//---------------------------------------------------------------------------
//
// ywugong.h    2000年8月30日
//
// 类YWugong：武功招数
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YWUGONG_H__
#define __YWUGONG_H__

class YWugong : public YMUDObject{

  public:
		YWugong(YString filename):YMUDObject(filename){disableTimer();};  //构造函数
		virtual ~YWugong(){}; //析构函数

    //返回武功描述
    inline YString wugong_miaoshu(const YString& wugong);
    //返回武功门派
    inline YString wugong_menpai(const YString& wugong);
    //返回武功类型(如：拳法、掌法、剑法、暗器等)
    YString wugong_leixing(const YString& wugong);
    //返回指定武功的所有招数，以空格分隔
    inline YString wugong_zhaoshu(const YString& wugong);
    //返回指定武功的招数数量
    inline long wugong_zhaoshu_count(const YString& wugong);
    //返回学指定武功所需内功
    inline long wugong_neigong_needed(const YString& wugong);
    //返回学指定武功所需基本武功
    inline long wugong_jiben_needed(const YString& wugong);
    //返回学指定武功所需经验
    inline long wugong_jingyan_needed(const YString& wugong);
    //返回学指定武功每次消耗的精力
    long wugong_jingli_used(const YString& wugong);
    //返回学指定武功每次消耗的潜能
    long wugong_qianneng_used(const YString& wugong);
    //返回当前应学的招数
    YString CurrentLearningZhaoshu(const YString& wugong, long level);
    //根据特殊武功等级随机返回一个招数
    YString randomAttack(const YString& wugong, long level);
    //返回招数描述
    YString zhaoshu_miaoshu(const YString& zhaoshu, const YString& actor1, const YString& actor2);
    //返回招数攻击力
    long zhaoshu_gongjili(const YString& zhaoshu);
    //返回武功防守力
    inline long wugong_fangshouli(const YString& wugong);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};
    //zhy
    //返回指定武功是否特殊武功
    YString wugong_isnot_especialWugong(const YString& wugong);
    //返回指定武功对应的基本武功
    YString wugong_corresponding_basicWugong(const YString& wugong);
    //返回指定武功的所有绝招,以空格分隔
    inline YString wugong_allUniqueSkill(const YString& wugong);
    //返回指定武功可以使用绝招的等级
    inline long wugong_usable_uniqueSkill(const YString& uniqueSkill);
    //返回指定武功所应使用的兵器
    inline YString wugong_use_weapon(const YString& wugong);
    //返回指定武功的绝招所需的特殊内功名
    inline YString uniqueSkill_need_especialInsideKongfuName(const YString& uniqueSkill);
    //返回指定武功的绝招所需的特殊内功等级
    inline long uniqueSkill_need_especialInsideKongfuGrade(const YString& uniqueSkill);
    //返回指定武功的绝招所需的内力
    inline long uniqueSkill_need_InsidePower(const YString& uniqueSkill);
    //返回绝招成功后对方忙的回合数
    inline long uniqueSkill_success_adversaryBusy(const YString& uniqueSkill);
    //返回绝招成功后自己忙的回合数
    inline long uniqueSkill_success_selfBusy(const YString& uniqueSkill);
    //返回绝招失败后自己忙的回合数
    inline long uniqueSkill_failed_selfBusy(const YString& uniqueSkill);
    //刘鹏
    //返回轻功的使用躲闪机会
    long wugong_add_dodge(const YString& wugong);
    //返回武功的powerup后的攻击比例
    long wugong_powerup(const YString& wugong);

    enum fight_displayer_t{SELF, TARGET, OTHER};
    //将FIGHT翻译成描述 (whom是显示对象)
    YString fight_translate(const YString& fight, YAbstractActor* actor1, YAbstractActor* actor2,
                      fight_displayer_t whom);
    //3个人物引入同一句话里（直接用YString引用，这样不用去处理指针）
    YString three_people_str (const YString& miaoshu,const YString& play1,const YString& play2,const YString& play3);
    //返回
};

#endif //__YWUGONG_H__
