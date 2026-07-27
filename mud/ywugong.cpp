//---------------------------------------------------------------------------
//
// ywugong.h    2000年8月30日
//
// 类YWugong：武功招数
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmud.h"


//---------------------------------------------------------------------------
//返回武功描述
YString YWugong::wugong_miaoshu(const YString& wugong)
{
  return getAsString(wugong);
}
//---------------------------------------------------------------------------
//返回武功门派
YString YWugong::wugong_menpai(const YString& wugong)
{
  return getAsString(wugong+"_门派");
}
//---------------------------------------------------------------------------
//返回武功类型(如：拳法、掌法、剑发、暗器等)
YString YWugong::wugong_leixing(const YString& wugong)
{
  YString type=getAsString(wugong+"_类型");
  return type;
}
//---------------------------------------------------------------------------
//返回指定武功的所有招数，以空格分隔
YString YWugong::wugong_zhaoshu(const YString& wugong)
{
  return getAsString(wugong+"_招数");
}
//---------------------------------------------------------------------------
//返回指定武功的招数数量
long YWugong::wugong_zhaoshu_count(const YString& wugong)
{
  return getAsLong(wugong+"_招数数量");
}
//---------------------------------------------------------------------------
//返回学指定武功所需内功
long YWugong::wugong_neigong_needed(const YString& wugong)
{
  return getAsLong(wugong+"_所需内功");
}
//---------------------------------------------------------------------------
//返回学指定武功所需基本武功
long YWugong::wugong_jiben_needed(const YString& wugong)
{
  return getAsLong(wugong+"_所需基本武功");
}
//---------------------------------------------------------------------------
//返回学指定武功所需经验
long YWugong::wugong_jingyan_needed(const YString& wugong)
{
  return getAsLong(wugong+"_所需经验");
}
//---------------------------------------------------------------------------
//返回学指定武功每次消耗的精力
long YWugong::wugong_jingli_used(const YString& wugong)
{
  return getAsLong(wugong+"_消耗精力");
}
//---------------------------------------------------------------------------
//返回学指定武功每次消耗的潜能
long YWugong::wugong_qianneng_used(const YString& wugong)
{
  return getAsLong(wugong+"_消耗潜能");
}
//---------------------------------------------------------------------------
//返回当前应学的招数
YString YWugong::CurrentLearningZhaoshu(const YString& wugong, long level)
{
  YString all_zhaoshu=wugong_zhaoshu(wugong);
  YString zhaoshu;
  YString retS="";
  while((zhaoshu=all_zhaoshu.getWord())!="") {
    if(level>=getAsLong(zhaoshu+"_等级")) retS=zhaoshu;
    else break;
  }
  return retS;
}
//---------------------------------------------------------------------------
//根据特殊武功等级随机返回一个招数
YString YWugong::randomAttack(const YString& wugong, long level)
{
  YString all_zhaoshu=wugong_zhaoshu(wugong);
  YString zhaoshu;
  YString LearnedZhaoshu;
  int count=0;
  while((zhaoshu=all_zhaoshu.getWord())!="") {
    if(level>getAsLong(zhaoshu+"_等级")) {
      LearnedZhaoshu+=zhaoshu+" ";
      count++;
    }
    else break;
  }
  YString retS="";
  if(count!=0) count=rand()%count+1;
  for(int i=0; i<count; i++) {
    retS=LearnedZhaoshu.getWord();
  }
  return retS;
}
//---------------------------------------------------------------------------
//返回招数描述
YString YWugong::zhaoshu_miaoshu(const YString& zhaoshu,
                                 const YString& actor1name, const YString& actor2name)
{
  YString s=getAsString(zhaoshu);
  if(s=="") s=getAsString("默认发招描述");
  int jos = 0;
  while (s.find('&',jos)!=YString::npos)
  {
    jos = s.find('&',jos)+1;
    if (s[jos] == 's' )
    {
          s.erase(jos-1,2);            //替换
          s.insert(jos-1,actor1name);     //插入
    }
    else if (s[jos] =='t')
    {
          s.erase(jos-1,2);            //替换
          s.insert(jos-1,actor2name);     //插入
    }
    else if (s[jos] =='z' )
    {
          s.erase(jos-1,2);            //替换
          s.insert(jos-1,zhaoshu);     //插入
    }
  }
  return s;

/*  YString retS="";
  for(int i=0; i<s.size(); i++) {
    if(s[i]=='&') {
      i++;
      if(s[i]=='s') retS+=actor1name;
      else if(s[i]=='t') retS+=actor2name;
      else if(s[i]=='z') retS+=zhaoshu;
    }
    else retS+=s[i];
  }
  return retS; */
}
//---------------------------------------------------------------------------
//返回招数攻击力
long YWugong::zhaoshu_gongjili(const YString& zhaoshu)
{
  return getAsLong(zhaoshu+"_攻击力");
}
//---------------------------------------------------------------------------
//返回武功防守力
long YWugong::wugong_fangshouli(const YString& wugong)
{
  return getAsLong(wugong+"_防守力");
}
//zhy
//---------------------------------------------------------------------------
//返回指定武功是否特殊武功
YString YWugong::wugong_isnot_especialWugong(const YString& wugong)
{
  return getAsString(wugong+"_是否特殊武功");
}
//---------------------------------------------------------------------------
//返回指定武功对应的基本武功
YString YWugong::wugong_corresponding_basicWugong(const YString& wugong)
{
  return getAsString(wugong+"_基本武功");
}
//---------------------------------------------------------------------------
//返回指定武功的所有招数，以空格分隔
YString YWugong::wugong_allUniqueSkill(const YString& wugong)
{
  return getAsString(wugong+"_绝招");
}
//---------------------------------------------------------------------------
//返回指定武功可以使用绝招的等级
long YWugong::wugong_usable_uniqueSkill(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_使用");
}
//---------------------------------------------------------------------------
//返回指定武功所应使用的兵器
YString YWugong::wugong_use_weapon(const YString& wugong)
{
  return getAsString(wugong+"_兵器");
}
//---------------------------------------------------------------------------
//返回指定武功的绝招所需的特殊内功名
YString YWugong::uniqueSkill_need_especialInsideKongfuName(const YString& uniqueSkill)
{
  return getAsString(uniqueSkill+"_特殊内功名");
}
//---------------------------------------------------------------------------
//返回指定武功的绝招所需的特殊内功等级
long YWugong::uniqueSkill_need_especialInsideKongfuGrade(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_特殊内功等级");
}
//---------------------------------------------------------------------------
//返回指定武功的绝招所需的内力
long YWugong::uniqueSkill_need_InsidePower(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_所需内力");
}
//---------------------------------------------------------------------------
//返回绝招成功后对方忙的回合数
long YWugong::uniqueSkill_success_adversaryBusy(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_成功对方忙");
}
//---------------------------------------------------------------------------
//返回绝招成功后自己忙的回合数
long YWugong::uniqueSkill_success_selfBusy(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_成功自己忙");
}
//---------------------------------------------------------------------------
//返回绝招失败后自己忙的回合数
long YWugong::uniqueSkill_failed_selfBusy(const YString& uniqueSkill)
{
  return getAsLong(uniqueSkill+"_不成功自己忙");
}
//---------------------------------------------------------------------------
//返回学指定武功闪躲附加值
long YWugong::wugong_add_dodge(const YString& wugong)
{
  return getAsLong(wugong+"_闪躲附加");
}
// 返回武功的powerup后的攻击比例
long YWugong::wugong_powerup(const YString& wugong)
{
  return getAsLong(wugong+"_powerup附加");
}
//返回战斗的起始描述
//将FIGHT翻译成描述(whom是显示对象)
YString YWugong::fight_translate(const YString& fight, YAbstractActor* actor1,
                          YAbstractActor* actor2, fight_displayer_t whom)
{
  if(!actor1) return "??";
  YString suffix;
  if(actor1==actor2) suffix="_self";
  else if(!actor2) suffix="_no";
  else suffix="_target";

  YString s=getAsString(fight+suffix);
  YString sSelf, sTarget;
  if(whom==SELF) {
    sSelf="你";
    sTarget=(actor2!=NULL)? actor2->getDisplayName() : YString("xx");
  }
  else if(whom==TARGET) {
    sSelf=actor1->getDisplayName();
    sTarget="你";
  }
  else {
    sSelf=actor1->getDisplayName();
    sTarget=(actor2!=NULL)? actor2->getDisplayName() : YString("xx");
  }
  int jos = 0;
  while (s.find('&',jos)!=YString::npos)
  {
    jos = s.find('&',jos)+1;
    if (s[jos] == 's' )
    {
          s.erase(jos-1,2);            //替换
          s.insert(jos-1,sSelf);     //插入
    }
    else if (s[jos] =='t' && (actor2!=NULL))
    {
          s.erase(jos-1,2);            //替换
          s.insert(jos-1,sTarget);     //插入
    }
  }
  return s;
/*  YString retS="";
  for(int i=0; i<s.size(); i++) {
    if(s[i]=='&') {
      i++;
      if(s[i]=='s') retS+=;
      else if((s[i]=='t') && (actor2!=NULL)) retS+=sTarget;
    }
    else retS+=s[i];
  }
  return retS; */
}
//3个人物引入同一句话里（直接用YString引用，这样不用去处理指针）
//使用顺序m,y,o,
YString YWugong::three_people_str (const YString& miaoshu ,const YString& play1,const YString& play2,const YString& play3)
{
  YString changeword = getAsString(miaoshu);
  int jos = 0;
  while( changeword.find ('&',jos)!=YString::npos )
  {

        jos=changeword.find ('&',jos)+1;  //查看替换为什么
        if (changeword[jos] == 'm')
        {
          changeword.erase(jos-1,2);            //替换
          changeword.insert(jos-1,play1);     //插入
        }
        else if (changeword[jos] == 'y')
        {
          changeword.erase(jos-1,2);            //替换
          changeword.insert(jos-1,play2);     //插入
        }
        else if (changeword[jos] == 'o')
        {
          changeword.erase(jos-1,2);            //替换
          changeword.insert(jos-1,play3);     //插入
        }
  }
  return changeword;
}
