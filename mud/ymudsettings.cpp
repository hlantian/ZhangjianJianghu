#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "ymudsettings.h"
#include "yerr.h"

//------------------------------------------------------------------------
YMUDSettings::YMUDSettings()
{
  m_property_group=new YPropertyGroup;
  setDefaultValues();
}
//------------------------------------------------------------------------
YMUDSettings::YMUDSettings(int argc, char* argv[],char* filename)
{
  m_property_group=new YPropertyGroup;
  setDefaultValues();
  load(argc,argv,filename);
}
//--------------------------------------------------------------------------
void YMUDSettings::setDefaultValues(void)
{
  //缺省值
  m_RootPath=".";
  m_MaxIdleTime=300;
  m_SessionIDLength=10;
  m_MessagePort=4825;
	m_PlayerNameColor="green"; //显示玩家名所用的颜色
	m_RoomNameColor="red"; //显示房间名所用的颜色
	m_NPCNameColor="grey"; //显示NPC名所用的颜色
	m_ThingNameColor="blue"; //显示物品名所用的颜色
      m_playerNameColor="player_name_color出错";//player_name_color的初始化
      m_npcNameColor="npc_name_color出错";//npc_name_color的初始化
      m_roomNameColoe="room_name_color出错";//room_name_color的初始化
      m_chatColor="公用频道颜色出错";//公用频道颜色的初始化
      m_partychatColor="门派频道颜色出错";//门派频道颜色的初始化
      m_newbieChatColor="新手频道颜色出错";//新手频道颜色的初始化
      m_rumorChatColor="谣言频道颜色出错";//谣言频道颜色的初始化
      m_wizChatColor="巫师频道颜色出错";//巫师频道颜色的初始化
      m_QuestColor="任务显示颜色出错";//任务显示颜色的初始化
      m_newPlayerIn="新人房间出错";//新人房间的初始化
      m_FistComrIn="初始房间出错";//初始房间的初始化
      m_IsNewPlayer="新玩家出错";//新玩家的初始化
      m_DeadRoom="死亡房间出错";//死亡房间的初始化
      m_NPCDeadRoom="NPC死亡房间出错";//NPC死亡房间的初始化
      m_NickColor="绰号颜色出错";//绰号颜色的初始化
      m_DescribeColor="个人描述颜色出错";//个人描述颜色的初始化
      m_HelpRoom1="helproom1出错";//helproom1的初始化
      m_HelpRoom2="helproom2出错";//helproom2的初始化
      m_HelpRoom3="helproom3出错";//helproom3的初始化
      m_HelpRoom4="helproom4出错";//helproom4的初始化
      m_HelpRoom5="helproom5出错";//helproom5的初始化
      m_HelpRoom6="helproom6出错";//helproom6的初始化
      m_HelpRoom7="helproom7出错";//helproom7的初始化
      m_HelpRoom8="helproom8出错";//helproom8的初始化
      m_HelpRoom9="helproom9出错";//helproom9的初始化
      m_HelpRoom10="helproom10出错";//helproom10的初始化
      m_HelpRoom11="helproom11出错";//helproom11的初始化
      m_HelpRoom12="helproom12出错";//helproom12的初始化
      m_HelpRoom13="helproom13出错";//helproom13的初始化
      m_HelpRoom14="helproom14出错";//helproom14的初始化
      m_HelpRoom15="helproom15出错";//helproom15的初始化
      m_HelpRoom16="helproom16出错";//helproom16的初始化
      m_HelpRoom17="helproom17出错";//helproom17的初始化
      m_HelpRoom18="helproom18出错";//helproom18的初始化
      m_HelpRoom19="helproom19出错";//helproom19的初始化
      m_HelpRoom20="helproom20出错";//helproom20的初始化
      m_HelpRoom21="helproom21出错";//helproom21的初始化
      m_HelpRoom22="helproom22出错";//helproom22的初始化
      m_HelpRoom23="helproom23出错";//helproom23的初始化
      m_HelpRoom24="helproom24出错";//helproom24的初始化
      m_HelpRoom25="helproom25出错";//helproom25的初始化
      m_jingDisplay="精力恢复描述出错";//精力恢复描述的初始化
      m_QiDiaplay="气血恢复描述出错";//气血恢复描述的初始化
      m_BodyDisplay0="平时气血形容0出错";//平时气血形容0的初始化
      m_BodyDisplay1="平时气血形容1出错";//平时气血形容1的初始化
      m_BodyDisplay2="平时气血形容2出错";//平时气血形容2的初始化
      m_BodyDisplay3="平时气血形容3出错";//平时气血形容3的初始化
      m_BodyDisplay4="平时气血形容4出错";//平时气血形容4的初始化
      m_BodyDisplay5="平时气血形容5出错";//平时气血形容5的初始化
      m_menFeature80="男性容貌形容>80出错";//男性容貌形容>80的初始化
      m_menFeature70="男性容貌形容>70出错";//男性容貌形容>70的初始化
      m_menFeature60="男性容貌形容>60出错";//男性容貌形容>60的初始化
      m_menFeature50="男性容貌形容>50出错";//男性容貌形容50的初始化
      m_menFeature40="男性容貌形容>40出错";//男性容貌形容>40的初始化
      m_menFeature30="男性容貌形容<40出错";//男性容貌形容<40的初始化
      m_wemenFeature80="女性容貌形容>80出错";//女性容貌形容>80的初始化
      m_wemenFeature70="女性容貌形容>70出错";//女性容貌形容>70的初始化
      m_wemenFeature60="女性容貌形容>60出错";//女性容貌形容>60的初始化
      m_wemenFeature55="女性容貌形容>55出错";//女性容貌形容>55的初始化
      m_wemenFeature50="女性容貌形容>50出错";//女性容貌形容>50的初始化
      m_wemenFeature45="女性容貌形容>45出错";//女性容貌形容>45的初始化
      m_wemenFeature40="女性容貌形容>40出错";//女性容貌形容>40的初始化
      m_wemenFeature30="女性容貌形容<40出错";//女性容貌形容<40的初始化
      m_wugongDisplay0="武功级别描述0出错";//武功级别描述0的初始化
      m_wugongDisplay1="武功级别描述1出错";//武功级别描述1的初始化
      m_wugongDisplay2="武功级别描述2出错";//武功级别描述2的初始化
      m_wugongDisplay3="武功级别描述3出错";//武功级别描述3的初始化
      m_wugongDisplay4="武功级别描述4出错";//武功级别描述4的初始化
      m_wugongDisplay5="武功级别描述5出错";//武功级别描述5的初始化
      m_wugongDisplay6="武功级别描述6出错";//武功级别描述6的初始化
      m_wugongDisplay7="武功级别描述7出错";//武功级别描述7的初始化
      m_wugongDisplay8="武功级别描述8出错";//武功级别描述8的初始化
      m_wugongDisplay9="武功级别描述9出错";//武功级别描述9的初始化
      m_wugongDisplay10="武功级别描述10出错";//武功级别描述10的初始化
      m_wugongDisplay11="武功级别描述11出错";//武功级别描述11的初始化
      m_wugongDisplay12="武功级别描述12出错";//武功级别描述12的初始化
      m_wugongDisplay13="武功级别描述13出错";//武功级别描述13的初始化
      m_wugongDisplay14="武功级别描述14出错";//武功级别描述14的初始化
      m_wugongDisplay15="武功级别描述15出错";//武功级别描述15的初始化
      m_wugongDisplay16="武功级别描述16出错";//武功级别描述16的初始化
      m_wugongDisplay17="武功级别描述17出错";//武功级别描述17的初始化
      m_wugongDisplay18="武功级别描述18出错";//武功级别描述18的初始化
      m_wugongDisplay19="武功级别描述19出错";//武功级别描述19的初始化
      m_wugongDisplay20="武功级别描述20出错";//武功级别描述20的初始化
      m_wugongDisplay21="武功级别描述21出错";//武功级别描述21的初始化
      m_wugongDisplay22="武功级别描述22出错";//武功级别描述22的初始化
      m_wugongDisplay23="武功级别描述23出错";//武功级别描述23的初始化
      m_wugongDisplay24="武功级别描述24出错";//武功级别描述24的初始化
      m_wugongDisplay25="武功级别描述25出错";//武功级别描述25的初始化
      m_wugongDisplay26="武功级别描述26出错";//武功级别描述26的初始化
      m_wugongDisplay27="武功级别描述27出错";//武功级别描述27的初始化
      m_wugongDisplay28="武功级别描述28出错";//武功级别描述28的初始化
      m_wugongDisplay29="武功级别描述29出错";//武功级别描述29的初始化
      m_wugongDisplay30="武功级别描述30出错";//武功级别描述30的初始化
      m_wugongDisplay31="武功级别描述31出错";//武功级别描述31的初始化
      m_wugongDisplay32="武功级别描述32出错";//武功级别描述32的初始化
      m_wugongDisplay33="武功级别描述33出错";//武功级别描述33的初始化
      m_wugongDisplay34="武功级别描述34出错";//武功级别描述34的初始化
      m_wugongDisplay35="武功级别描述35出错";//武功级别描述35的初始化
      m_ciDisplay10="刺伤10出错";//刺伤10的初始化
      m_ciDisplay20="刺伤20出错";//刺伤20的初始化
      m_ciDisplay40="刺伤40出错";//刺伤40的初始化
      m_ciDisplay80="刺伤80出错";//刺伤80的初始化
      m_ciDisplay120="刺伤120出错";//刺伤120的初始化
      m_ciDisplay160u="刺伤160上出错";//刺伤160上的初始化
      m_ciDisplay160d="刺伤160下出错";//刺伤160下的初始化
      m_kongDisplay10="空手伤10出错";//空手伤10的初始化
      m_kongDisplay20="空手伤20出错";//空手伤20的初始化
      m_kongDisplay40="空手伤40出错";//空手伤40的初始化
      m_kongDisplay80="空手伤80出错";//空手伤80的初始化
      m_kongDisplay120="空手伤120出错";//空手伤120的初始化
      m_kongDisplay160="空手伤160出错";//空手伤160的初始化
      m_kongDisplay200="空手伤200出错";//空手伤200的初始化
      m_kanDisplay10="砍伤10出错";//砍伤10的初始化
      m_kanDisplay20="砍伤20出错";//砍伤20的初始化
      m_kanDisplay40="砍伤40出错";//砍伤40的初始化
      m_kanDisplay80="砍伤80出错";//砍伤80的初始化
      m_kanDisplay120="砍伤120出错";//砍伤120的初始化
      m_kanDisplay160="砍伤160出错";//砍伤160的初始化
      m_yaoDisplay10="咬伤10出错";//咬伤10的初始化
      m_yaoDisplay20="咬伤20出错";//咬伤20的初始化
      m_yaoDisplay40="咬伤40出错";//咬伤40的初始化
      m_yaoDisplay80="咬伤80出错";//咬伤80的初始化
      m_yaoDisplay120="咬伤120出错";//咬伤120的初始化
      m_shanghai5="伤害描述5出错";//伤害描述5的初始化
      m_shanghai10="伤害描述10出错";//伤害描述10的初始化
      m_shanghai20="伤害描述20出错";//伤害描述20的初始化
      m_shanghai30="伤害描述30出错";//伤害描述30的初始化
      m_shanghai50="伤害描述50出错";//伤害描述50的初始化
      m_shanghai80="伤害描述80出错";//伤害描述80的初始化
      m_shanghai100="伤害描述100出错";//伤害描述100的初始化
      m_shanghai160="伤害描述160出错";//伤害描述160的初始化
      m_shanghai200="伤害描述200出错";//伤害描述200的初始化
      m_haltDisplay1="停手描述1出错";//停手描述1的初始化
      m_haltDisplay2="停手描述2出错";//停手描述2的初始化
      m_haltDisplay3="停手描述3出错";//停手描述3的初始化
      m_haltDisplay4="停手描述4出错";//停手描述4的初始化
      m_haltDisplay5="停手描述5出错";//停手描述5的初始化
      m_haltDisplay6="停手描述6出错";//停手描述6的初始化
      m_haltDisplay7="停手描述7出错";//停手描述7的初始化
      m_haltDisplay8="停手描述8出错";//停手描述8的初始化
      m_haltDisplay9="停手描述9出错";//停手描述9的初始化
      m_haltDisplay10="停手描述10出错";//停手描述10的初始化
      m_haltDisplay11="停手描述11出错";//停手描述11的初始化
      m_workskills="劳动技能出错";//停手描述11的初始化
      m_blackip="";//封锁ip
//长型的变量
      m_sitMinX=0;//用于min_x由变量m_sitMinX表示
      m_sitMinY=0;//用于min_y由变量m_sitMinY表示
      m_sitMaxX=0;//用于max_x由变量m_sitMaxX表示
      m_sitMaxY=0;//用于max_y由变量m_sitMaxY表示
      m_sitIEOvertime=0;//用于浏览器超时由变量m_sitIEOvertime表示
      m_sitDazeTime=0;//用于发呆时间由变量m_sitDazeTime表示
      m_sitLoseTime=0;//用于掉线时间由变量m_sitLoseTime表示
      m_sitbodyRenewSpeed=0;//用于身体恢复速度由变量m_sitbodyRenewSpeed表示
      m_sitFoodSpendTime=0;//用于食品消耗时间由变量m_sitFoodSpendTime表示
      m_sitFightSkipTime=0;//用于战斗间隔由变量m_sitFightSkipTime表示
      m_sitFoodSpend=0;//用于食品消耗由变量m_sitFoodSpend表示
      m_sitAgeUpTime=0;//用于年龄增长速度由变量m_sitAgeUpTime表示
      m_sitFaintTime=0;//用于晕倒时间由变量m_sitFaintTime表示
      m_sitFleeChance=0;//用于逃跑机会由变量m_sitFleeChance表示
      m_sitFightUp=0;//用于战斗成长由变量m_sitFightUp表示
      m_sitlianSpendqian=0;//用于练武消耗潜能由变量m_sitlianSpendqian表示
      m_sitHitExpChange=0;//用于攻击经验转换由变量m_sitHitExpChange表示
      m_sitDefExpChange=0;//用于防御经验转换由变量m_sitDefExpChange表示
      m_sitHitScale=0;//用于攻击力比例由变量m_sitHitScale表示
      m_sitDefScale=0;//用于防御力比例由变量m_sitDefScale表示
      m_sitLelForceUp=0;//用于每级内力增长由变量m_sitLelForceUp表示
      m_sitLelBodyUp=0;//用于每级气血增长由变量m_sitLelBodyUp表示
      m_sitLelBookUp=0;//用于每级读书增长由变量m_sitLelBookUp表示
      m_sitNpcBody=0;//用于NPC气血由变量m_sitNpcBody表示
      m_sitNpcHit=0;//用于NPC默认攻击由变量m_sitNpcHit表示
      m_sitNpcDef=0;//用于NPC默认防御由变量m_sitNpcDef表示
      m_sitNpcLevel=0;//用于NPC武功级别由变量m_sitNpcLevel表示
      m_sitRefurbishTimeSkip=0;//用于刷新时间间隔由变量m_sitRefurbishTimeSkip表示
      m_sitPowerUpTime=0;//用于powerup时间由变量m_sitPowerUpTime表示
      m_sitNewbieBeginAge=0;//用于新手开始年龄由变量m_sitNewbieBeginAge表示
      m_sitNewbieAge=0;//用于新手年龄由变量m_sitNewbieAge表示
      m_sitLianSpendJing=0;//用于练功精力由变量m_sitLianSpendJing表示
      m_sitLianSpendQi=0;//用于练功气血由变量m_sitLianSpendQi表示
      m_sitLianUp=0;//用于练功成长由变量m_sitLianUp表示
      m_sitQuestExpUpLimit=0;//用于任务奖励经验上限由变量m_sitQuestExpUpLimit表示
      m_sitQuestQianUpLimit=0;//用于任务奖励潜能上限由变量m_sitQuestQianUpLimit表示
      m_sitTextCost=0;//用于大车的消耗m_sitTextCost表示
}
//------------------------------------------------------------------------
//将属性转存到成员变量中
void YMUDSettings::setInternalVaribles(void)
{
  if(m_property_group->getAsString("root_path")!="")
    m_RootPath=m_property_group->getAsString("root_path");
  if(m_property_group->getAsLong("max_idle_time")!=0)
    m_MaxIdleTime=m_property_group->getAsLong("max_idle_time");
  if(m_property_group->getAsLong("max_sessionID_length")!=0)
    m_SessionIDLength=m_property_group->getAsLong("max_sessionID_length");
  if(m_property_group->getAsLong("message_port")!=0)
    m_MessagePort=m_property_group->getAsLong("message_port");
	if(m_property_group->getAsString("player_name_color")!="")
    m_PlayerNameColor=m_property_group->getAsString("player_name_color"); //显示玩家名所用的颜色
  if(m_property_group->getAsString("room_name_color")!="")
    m_RoomNameColor=m_property_group->getAsString("room_name_color"); //显示房间名所用的颜色
	if(m_property_group->getAsString("npc_name_color")!="")
    m_NPCNameColor=m_property_group->getAsString("npc_name_color"); //显示NPC名所用的颜色
	if(m_property_group->getAsString("thing_name_color")!="")
    m_ThingNameColor=m_property_group->getAsString("thing_name_color"); //显示物品名所用的颜色
  if(m_property_group->getAsString("server_IP")!="")
    m_Server_IP=m_property_group->getAsString("server_IP");
      setplayerNameColor(m_property_group->getAsString("player_name_color"));  //变量m_playerNameColor取值（player_name_color）
      setnpcNameColor(m_property_group->getAsString("npc_name_color"));  //变量m_npcNameColor取值（npc_name_color）
      setroomNameColoe(m_property_group->getAsString("room_name_color"));  //变量m_roomNameColoe取值（room_name_color）
      setchatColor(m_property_group->getAsString("公用频道颜色"));  //变量m_chatColor取值（公用频道颜色）
      setpartychatColor(m_property_group->getAsString("门派频道颜色"));  //变量m_partychatColor取值（门派频道颜色）
      setnewbieChatColor(m_property_group->getAsString("新手频道颜色"));  //变量m_newbieChatColor取值（新手频道颜色）
      setrumorChatColor(m_property_group->getAsString("谣言频道颜色"));  //变量m_rumorChatColor取值（谣言频道颜色）
      setwizChatColor(m_property_group->getAsString("巫师频道颜色"));  //变量m_wizChatColor取值（巫师频道颜色）
      setQuestColor(m_property_group->getAsString("任务显示颜色"));  //变量m_QuestColor取值（任务显示颜色）
      setnewPlayerIn(m_property_group->getAsString("新人房间"));  //变量m_newPlayerIn取值（新人房间）
      setFistComrIn(m_property_group->getAsString("初始房间"));  //变量m_FistComrIn取值（初始房间）
      setIsNewPlayer(m_property_group->getAsString("新玩家"));  //变量m_IsNewPlayer取值（新玩家）
      setDeadRoom(m_property_group->getAsString("死亡房间"));  //变量m_DeadRoom取值（死亡房间）
      setNPCDeadRoom(m_property_group->getAsString("NPC死亡房间"));  //变量m_NPCDeadRoom取值（NPC死亡房间）
      setNickColor(m_property_group->getAsString("绰号颜色"));  //变量m_NickColor取值（绰号颜色）
      setDescribeColor(m_property_group->getAsString("个人描述颜色"));  //变量m_DescribeColor取值（个人描述颜色）
      setHelpRoom1(m_property_group->getAsString("helproom1"));  //变量m_HelpRoom1取值（helproom1）
      setHelpRoom2(m_property_group->getAsString("helproom2"));  //变量m_HelpRoom2取值（helproom2）
      setHelpRoom3(m_property_group->getAsString("helproom3"));  //变量m_HelpRoom3取值（helproom3）
      setHelpRoom4(m_property_group->getAsString("helproom4"));  //变量m_HelpRoom4取值（helproom4）
      setHelpRoom5(m_property_group->getAsString("helproom5"));  //变量m_HelpRoom5取值（helproom5）
      setHelpRoom6(m_property_group->getAsString("helproom6"));  //变量m_HelpRoom6取值（helproom6）
      setHelpRoom7(m_property_group->getAsString("helproom7"));  //变量m_HelpRoom7取值（helproom7）
      setHelpRoom8(m_property_group->getAsString("helproom8"));  //变量m_HelpRoom8取值（helproom8）
      setHelpRoom9(m_property_group->getAsString("helproom9"));  //变量m_HelpRoom9取值（helproom9）
      setHelpRoom10(m_property_group->getAsString("helproom10"));  //变量m_HelpRoom10取值（helproom10）
      setHelpRoom11(m_property_group->getAsString("helproom11"));  //变量m_HelpRoom11取值（helproom11）
      setHelpRoom12(m_property_group->getAsString("helproom12"));  //变量m_HelpRoom12取值（helproom12）
      setHelpRoom13(m_property_group->getAsString("helproom13"));  //变量m_HelpRoom13取值（helproom13）
      setHelpRoom14(m_property_group->getAsString("helproom14"));  //变量m_HelpRoom14取值（helproom14）
      setHelpRoom15(m_property_group->getAsString("helproom15"));  //变量m_HelpRoom15取值（helproom15）
      setHelpRoom16(m_property_group->getAsString("helproom16"));  //变量m_HelpRoom16取值（helproom15）
      setHelpRoom17(m_property_group->getAsString("helproom17"));  //变量m_HelpRoom17取值（helproom15）
      setHelpRoom18(m_property_group->getAsString("helproom18"));  //变量m_HelpRoom18取值（helproom15）
      setHelpRoom19(m_property_group->getAsString("helproom19"));  //变量m_HelpRoom19取值（helproom15）
      setHelpRoom20(m_property_group->getAsString("helproom20"));  //变量m_HelpRoom20取值（helproom20）
      setHelpRoom21(m_property_group->getAsString("helproom21"));  //变量m_HelpRoom21取值（helproom21）
      setHelpRoom22(m_property_group->getAsString("helproom22"));  //变量m_HelpRoom22取值（helproom22）
      setHelpRoom23(m_property_group->getAsString("helproom23"));  //变量m_HelpRoom23取值（helproom23）
      setHelpRoom24(m_property_group->getAsString("helproom24"));  //变量m_HelpRoom24取值（helproom24）
      setHelpRoom25(m_property_group->getAsString("helproom25"));  //变量m_HelpRoom25取值（helproom25）
      setjingDisplay(m_property_group->getAsString("精力恢复描述"));  //变量m_jingDisplay取值（精力恢复描述）
      setQiDiaplay(m_property_group->getAsString("气血恢复描述"));  //变量m_QiDiaplay取值（气血恢复描述）
      setBodyDisplay0(m_property_group->getAsString("平时气血形容0"));  //变量m_BodyDisplay0取值（平时气血形容0）
      setBodyDisplay1(m_property_group->getAsString("平时气血形容1"));  //变量m_BodyDisplay1取值（平时气血形容1）
      setBodyDisplay2(m_property_group->getAsString("平时气血形容2"));  //变量m_BodyDisplay2取值（平时气血形容2）
      setBodyDisplay3(m_property_group->getAsString("平时气血形容3"));  //变量m_BodyDisplay3取值（平时气血形容3）
      setBodyDisplay4(m_property_group->getAsString("平时气血形容4"));  //变量m_BodyDisplay4取值（平时气血形容4）
      setBodyDisplay5(m_property_group->getAsString("平时气血形容5"));  //变量m_BodyDisplay5取值（平时气血形容5）
      setmenFeature80(m_property_group->getAsString("男性容貌形容>80"));  //变量m_menFeature80取值（男性容貌形容>80）
      setmenFeature70(m_property_group->getAsString("男性容貌形容>70"));  //变量m_menFeature70取值（男性容貌形容>70）
      setmenFeature60(m_property_group->getAsString("男性容貌形容>60"));  //变量m_menFeature60取值（男性容貌形容>60）
      setmenFeature50(m_property_group->getAsString("男性容貌形容>50"));  //变量m_menFeature50取值（男性容貌形容50）
      setmenFeature40(m_property_group->getAsString("男性容貌形容>40"));  //变量m_menFeature40取值（男性容貌形容>40）
      setmenFeature30(m_property_group->getAsString("男性容貌形容<40"));  //变量m_menFeature30取值（男性容貌形容<40）
      setwemenFeature80(m_property_group->getAsString("女性容貌形容>80"));  //变量m_wemenFeature80取值（女性容貌形容>80）
      setwemenFeature70(m_property_group->getAsString("女性容貌形容>70"));  //变量m_wemenFeature70取值（女性容貌形容>70）
      setwemenFeature60(m_property_group->getAsString("女性容貌形容>60"));  //变量m_wemenFeature60取值（女性容貌形容>60）
      setwemenFeature55(m_property_group->getAsString("女性容貌形容>55"));  //变量m_wemenFeature55取值（女性容貌形容>55）
      setwemenFeature50(m_property_group->getAsString("女性容貌形容>50"));  //变量m_wemenFeature50取值（女性容貌形容>50）
      setwemenFeature45(m_property_group->getAsString("女性容貌形容>45"));  //变量m_wemenFeature45取值（女性容貌形容>45）
      setwemenFeature40(m_property_group->getAsString("女性容貌形容>40"));  //变量m_wemenFeature40取值（女性容貌形容>40）
      setwemenFeature30(m_property_group->getAsString("女性容貌形容<40"));  //变量m_wemenFeature30取值（女性容貌形容<40）
      setwugongDisplay0(m_property_group->getAsString("武功级别描述0"));  //变量m_wugongDisplay0取值（武功级别描述0）
      setwugongDisplay1(m_property_group->getAsString("武功级别描述1"));  //变量m_wugongDisplay1取值（武功级别描述1）
      setwugongDisplay2(m_property_group->getAsString("武功级别描述2"));  //变量m_wugongDisplay2取值（武功级别描述2）
      setwugongDisplay3(m_property_group->getAsString("武功级别描述3"));  //变量m_wugongDisplay3取值（武功级别描述3）
      setwugongDisplay4(m_property_group->getAsString("武功级别描述4"));  //变量m_wugongDisplay4取值（武功级别描述4）
      setwugongDisplay5(m_property_group->getAsString("武功级别描述5"));  //变量m_wugongDisplay5取值（武功级别描述5）
      setwugongDisplay6(m_property_group->getAsString("武功级别描述6"));  //变量m_wugongDisplay6取值（武功级别描述6）
      setwugongDisplay7(m_property_group->getAsString("武功级别描述7"));  //变量m_wugongDisplay7取值（武功级别描述7）
      setwugongDisplay8(m_property_group->getAsString("武功级别描述8"));  //变量m_wugongDisplay8取值（武功级别描述8）
      setwugongDisplay9(m_property_group->getAsString("武功级别描述9"));  //变量m_wugongDisplay9取值（武功级别描述9）
      setwugongDisplay10(m_property_group->getAsString("武功级别描述10"));  //变量m_wugongDisplay10取值（武功级别描述10）
      setwugongDisplay11(m_property_group->getAsString("武功级别描述11"));  //变量m_wugongDisplay11取值（武功级别描述11）
      setwugongDisplay12(m_property_group->getAsString("武功级别描述12"));  //变量m_wugongDisplay12取值（武功级别描述12）
      setwugongDisplay13(m_property_group->getAsString("武功级别描述13"));  //变量m_wugongDisplay13取值（武功级别描述13）
      setwugongDisplay14(m_property_group->getAsString("武功级别描述14"));  //变量m_wugongDisplay14取值（武功级别描述14）
      setwugongDisplay15(m_property_group->getAsString("武功级别描述15"));  //变量m_wugongDisplay15取值（武功级别描述15）
      setwugongDisplay16(m_property_group->getAsString("武功级别描述16"));  //变量m_wugongDisplay16取值（武功级别描述16）
      setwugongDisplay17(m_property_group->getAsString("武功级别描述17"));  //变量m_wugongDisplay17取值（武功级别描述17）
      setwugongDisplay18(m_property_group->getAsString("武功级别描述18"));  //变量m_wugongDisplay18取值（武功级别描述18）
      setwugongDisplay19(m_property_group->getAsString("武功级别描述19"));  //变量m_wugongDisplay19取值（武功级别描述19）
      setwugongDisplay20(m_property_group->getAsString("武功级别描述20"));  //变量m_wugongDisplay20取值（武功级别描述20）
      setwugongDisplay21(m_property_group->getAsString("武功级别描述21"));  //变量m_wugongDisplay21取值（武功级别描述21）
      setwugongDisplay22(m_property_group->getAsString("武功级别描述22"));  //变量m_wugongDisplay22取值（武功级别描述22）
      setwugongDisplay23(m_property_group->getAsString("武功级别描述23"));  //变量m_wugongDisplay23取值（武功级别描述23）
      setwugongDisplay24(m_property_group->getAsString("武功级别描述24"));  //变量m_wugongDisplay24取值（武功级别描述24）
      setwugongDisplay25(m_property_group->getAsString("武功级别描述25"));  //变量m_wugongDisplay25取值（武功级别描述25）
      setwugongDisplay26(m_property_group->getAsString("武功级别描述26"));  //变量m_wugongDisplay26取值（武功级别描述26）
      setwugongDisplay27(m_property_group->getAsString("武功级别描述27"));  //变量m_wugongDisplay27取值（武功级别描述27）
      setwugongDisplay28(m_property_group->getAsString("武功级别描述28"));  //变量m_wugongDisplay28取值（武功级别描述28）
      setwugongDisplay29(m_property_group->getAsString("武功级别描述29"));  //变量m_wugongDisplay29取值（武功级别描述29）
      setwugongDisplay30(m_property_group->getAsString("武功级别描述30"));  //变量m_wugongDisplay30取值（武功级别描述30）
      setwugongDisplay31(m_property_group->getAsString("武功级别描述31"));  //变量m_wugongDisplay31取值（武功级别描述31）
      setwugongDisplay32(m_property_group->getAsString("武功级别描述32"));  //变量m_wugongDisplay32取值（武功级别描述32）
      setwugongDisplay33(m_property_group->getAsString("武功级别描述33"));  //变量m_wugongDisplay33取值（武功级别描述33）
      setwugongDisplay34(m_property_group->getAsString("武功级别描述34"));  //变量m_wugongDisplay34取值（武功级别描述34）
      setwugongDisplay35(m_property_group->getAsString("武功级别描述35"));  //变量m_wugongDisplay35取值（武功级别描述35）
      setciDisplay10(m_property_group->getAsString("刺伤10"));  //变量m_ciDisplay10取值（刺伤10）
      setciDisplay20(m_property_group->getAsString("刺伤20"));  //变量m_ciDisplay20取值（刺伤20）
      setciDisplay40(m_property_group->getAsString("刺伤40"));  //变量m_ciDisplay40取值（刺伤40）
      setciDisplay80(m_property_group->getAsString("刺伤80"));  //变量m_ciDisplay80取值（刺伤80）
      setciDisplay120(m_property_group->getAsString("刺伤120"));  //变量m_ciDisplay120取值（刺伤120）
      setciDisplay160u(m_property_group->getAsString("刺伤160上"));  //变量m_ciDisplay160u取值（刺伤160上）
      setciDisplay160d(m_property_group->getAsString("刺伤160下"));  //变量m_ciDisplay160d取值（刺伤160下）
      setkongDisplay10(m_property_group->getAsString("空手伤10"));  //变量m_kongDisplay10取值（空手伤10）
      setkongDisplay20(m_property_group->getAsString("空手伤20"));  //变量m_kongDisplay20取值（空手伤20）
      setkongDisplay40(m_property_group->getAsString("空手伤40"));  //变量m_kongDisplay40取值（空手伤40）
      setkongDisplay80(m_property_group->getAsString("空手伤80"));  //变量m_kongDisplay80取值（空手伤80）
      setkongDisplay120(m_property_group->getAsString("空手伤120"));  //变量m_kongDisplay120取值（空手伤120）
      setkongDisplay160(m_property_group->getAsString("空手伤160"));  //变量m_kongDisplay160取值（空手伤160）
      setkongDisplay200(m_property_group->getAsString("空手伤200"));  //变量m_kongDisplay200取值（空手伤200）
      setkanDisplay10(m_property_group->getAsString("砍伤10"));  //变量m_kanDisplay10取值（砍伤10）
      setkanDisplay20(m_property_group->getAsString("砍伤20"));  //变量m_kanDisplay20取值（砍伤20）
      setkanDisplay40(m_property_group->getAsString("砍伤40"));  //变量m_kanDisplay40取值（砍伤40）
      setkanDisplay80(m_property_group->getAsString("砍伤80"));  //变量m_kanDisplay80取值（砍伤80）
      setkanDisplay120(m_property_group->getAsString("砍伤120"));  //变量m_kanDisplay120取值（砍伤120）
      setkanDisplay160(m_property_group->getAsString("砍伤160"));  //变量m_kanDisplay160取值（砍伤160）
      setyaoDisplay10(m_property_group->getAsString("咬伤10"));  //变量m_yaoDisplay10取值（咬伤10）
      setyaoDisplay20(m_property_group->getAsString("咬伤20"));  //变量m_yaoDisplay20取值（咬伤20）
      setyaoDisplay40(m_property_group->getAsString("咬伤40"));  //变量m_yaoDisplay40取值（咬伤40）
      setyaoDisplay80(m_property_group->getAsString("咬伤80"));  //变量m_yaoDisplay80取值（咬伤80）
      setyaoDisplay120(m_property_group->getAsString("咬伤120"));  //变量m_yaoDisplay120取值（咬伤120）
      setshanghai5(m_property_group->getAsString("伤害描述5"));  //变量m_shanghai5取值（伤害描述5）
      setshanghai10(m_property_group->getAsString("伤害描述10"));  //变量m_shanghai10取值（伤害描述10）
      setshanghai20(m_property_group->getAsString("伤害描述20"));  //变量m_shanghai20取值（伤害描述20）
      setshanghai30(m_property_group->getAsString("伤害描述30"));  //变量m_shanghai30取值（伤害描述30）
      setshanghai50(m_property_group->getAsString("伤害描述50"));  //变量m_shanghai50取值（伤害描述50）
      setshanghai80(m_property_group->getAsString("伤害描述80"));  //变量m_shanghai80取值（伤害描述80）
      setshanghai100(m_property_group->getAsString("伤害描述100"));  //变量m_shanghai100取值（伤害描述100）
      setshanghai160(m_property_group->getAsString("伤害描述160"));  //变量m_shanghai160取值（伤害描述160）
      setshanghai200(m_property_group->getAsString("伤害描述200"));  //变量m_shanghai200取值（伤害描述200）
      sethaltDisplay1(m_property_group->getAsString("停手描述1"));  //变量m_haltDisplay1取值（停手描述1）
      sethaltDisplay2(m_property_group->getAsString("停手描述2"));  //变量m_haltDisplay2取值（停手描述2）
      sethaltDisplay3(m_property_group->getAsString("停手描述3"));  //变量m_haltDisplay3取值（停手描述3）
      sethaltDisplay4(m_property_group->getAsString("停手描述4"));  //变量m_haltDisplay4取值（停手描述4）
      sethaltDisplay5(m_property_group->getAsString("停手描述5"));  //变量m_haltDisplay5取值（停手描述5）
      sethaltDisplay6(m_property_group->getAsString("停手描述6"));  //变量m_haltDisplay6取值（停手描述6）
      sethaltDisplay7(m_property_group->getAsString("停手描述7"));  //变量m_haltDisplay7取值（停手描述7）
      sethaltDisplay8(m_property_group->getAsString("停手描述8"));  //变量m_haltDisplay8取值（停手描述8）
      sethaltDisplay9(m_property_group->getAsString("停手描述9"));  //变量m_haltDisplay9取值（停手描述9）
      sethaltDisplay10(m_property_group->getAsString("停手描述10"));  //变量m_haltDisplay10取值（停手描述10）
      sethaltDisplay11(m_property_group->getAsString("停手描述11"));  //变量m_haltDisplay11取值（停手描述11）
      setworkskills(m_property_group->getAsString("劳动技能种类"));  //变量m_workskills取值（劳动技能种类）
      setblackip(m_property_group->getAsString("封锁ip")); //变量ip的变化

      //长型变量的显示
      setsitMinX(m_property_group->getAsLong("min_x"));  //变量m_sitMinX取值（min_x）
      setsitMinY(m_property_group->getAsLong("min_y"));  //变量m_sitMinY取值（min_y）
      setsitMaxX(m_property_group->getAsLong("max_x"));  //变量m_sitmaxX取值（max_x）
      setsitMaxY(m_property_group->getAsLong("max_y"));  //变量m_sitmaxY取值（max_y）
      setsitIEOvertime(m_property_group->getAsLong("浏览器超时"));  //变量m_sitIEOvertime取值（浏览器超时）
      setsitDazeTime(m_property_group->getAsLong("发呆时间"));  //变量m_sitDazeTime取值（发呆时间）
      setsitLoseTime(m_property_group->getAsLong("掉线时间"));  //变量m_sitLoseTime取值（掉线时间）
      setsitbodyRenewSpeed(m_property_group->getAsLong("身体恢复速度"));  //变量m_sitbodyRenewSpeed取值（身体恢复速度）
      setsitFoodSpendTime(m_property_group->getAsLong("食品消耗时间"));  //变量m_sitFoodSpendTime取值（食品消耗时间）
      setsitFightSkipTime(m_property_group->getAsLong("战斗间隔"));  //变量m_sitFightSkipTime取值（战斗间隔）
      setsitFoodSpend(m_property_group->getAsLong("食品消耗"));  //变量m_sitFoodSpend取值（食品消耗）
      setsitAgeUpTime(m_property_group->getAsLong("年龄增长速度"));  //变量m_sitAgeUpTime取值（年龄增长速度）
      setsitFaintTime(m_property_group->getAsLong("晕倒时间"));  //变量m_sitFaintTime取值（晕倒时间）
      setsitFleeChance(m_property_group->getAsLong("逃跑机会"));  //变量m_sitFleeChance取值（逃跑机会）
      setsitFightUp(m_property_group->getAsLong("战斗成长"));  //变量m_sitFightUp取值（战斗成长）
      setsitlianSpendqian(m_property_group->getAsLong("练武消耗潜能"));  //变量m_sitlianSpendqian取值（练武消耗潜能）
      setsitHitExpChange(m_property_group->getAsLong("攻击经验转换"));  //变量m_sitHitExpChange取值（攻击经验转换）
      setsitDefExpChange(m_property_group->getAsLong("防御经验转换"));  //变量m_sitDefExpChange取值（防御经验转换）
      setsitHitScale(m_property_group->getAsLong("攻击力比例"));  //变量m_sitHitScale取值（攻击力比例）
      setsitDefScale(m_property_group->getAsLong("防御力比例"));  //变量m_sitDefScale取值（防御力比例）
      setsitLelForceUp(m_property_group->getAsLong("每级内力增长"));  //变量m_sitLelForceUp取值（每级内力增长）
      setsitLelBodyUp(m_property_group->getAsLong("每级气血增长"));  //变量m_sitLelBodyUp取值（每级气血增长）
      setsitLelBookUp(m_property_group->getAsLong("每级读书增长"));  //变量m_sitLelBookUp取值（每级读书增长）
      setsitNpcBody(m_property_group->getAsLong("NPC气血"));  //变量m_sitNpcBody取值（NPC气血）
      setsitNpcHit(m_property_group->getAsLong("NPC默认攻击"));  //变量m_sitNpcHit取值（NPC默认攻击）
      setsitNpcDef(m_property_group->getAsLong("NPC默认防御"));  //变量m_sitNpcDef取值（NPC默认防御）
      setsitNpcLevel(m_property_group->getAsLong("NPC武功级别"));  //变量m_sitNpcLevel取值（NPC武功级别）
      setsitRefurbishTimeSkip(m_property_group->getAsLong("刷新时间间隔"));  //变量m_sitRefurbishTimeSkip取值（刷新时间间隔）
      setsitPowerUpTime(m_property_group->getAsLong("powerup时间"));  //变量m_sitPowerUpTime取值（powerup时间）
      setsitNewbieBeginAge(m_property_group->getAsLong("新手开始年龄"));  //变量m_sitNewbieBeginAge取值（新手开始年龄）
      setsitNewbieAge(m_property_group->getAsLong("新手年龄"));  //变量m_sitNewbieAge取值（新手年龄）
      setsitLianSpendJing(m_property_group->getAsLong("练功精力"));  //变量m_sitLianSpendJing取值（练功精力）
      setsitLianSpendQi(m_property_group->getAsLong("练功气血"));  //变量m_sitLianSpendQi取值（练功气血）
      setsitLianUp(m_property_group->getAsLong("练功成长"));  //变量m_sitLianUp取值（练功成长）
      setsitQuestExpUpLimit(m_property_group->getAsLong("任务奖励经验上限"));  //变量m_sitQuestExpUpLimit取值（任务奖励经验上限）
      setsitQuestQianUpLimit(m_property_group->getAsLong("任务奖励潜能上限"));  //变量m_sitQuestQianUpLimit取值（任务奖励潜能上限）
      setsitTextCost(m_property_group->getAsLong("叫车的花费"));//变量m_sitTextCost取值（大车的花费）
}
//------------------------------------------------------------------------
int YMUDSettings::load(int argc, char* argv[],char* filename)
{
  int retval=0;
  ifstream in_file(filename);
  if(!in_file.is_open()) return -1;
  m_property_group->load(in_file);
  in_file.close();

  setInternalVaribles();

/* ---旧版本---
  //处理文件
  FILE *configFile=fopen(filename,"rt");
  if(configFile) {
    char s[1024];
    while(fgets(s,1024,configFile)!=NULL) {
      //cout<<"\nline is: "<<s;
      processPhrase(s);
    }
    fclose(configFile);
  }
  else {
    retval=-1;
  }

  //处理命令行
  for(int i=0; i<argc; i++) {
    processPhrase(argv[i]);
  }
*/
  return retval;
}
//--------------------------------------------------------------------------
//处理Var=Val格式语句
void YMUDSettings::processPhrase(char *s)
{
  if(s[0]=='#') return; //注释语句
  char *val=strchr(s,'=');
  if(!val) return;
  *val='\0';
  val++;
  trim(s);
  trim(val);
  //cout<<"\ns="<<s<<"; val="<<val;
  if(strcmp(s,"root_path")==0) {
    m_RootPath=val;
  }
  else if(strcmp(s,"max_idle_time")==0) {
    m_MaxIdleTime=atoi(val);
  }
  else if(strcmp(s,"max_sessionID_length")==0) {
    m_SessionIDLength=atoi(val);
  }
  else if(strcmp(s,"message_port")==0) {
    m_MessagePort=atoi(val);
  }
  else if(strcmp(s,"server_IP")==0) {
    m_Server_IP=val;
  }
  else {
    char errmsg[256];
    sprintf(errmsg,"不能识别的单词：%s",s);
    YErr::show(errmsg);
  }
}
//--------------------------------------------------------------------------
//将"/"替换成"\\"
YString convertToWinPath(const YString unixpath)
{
  int n;
  YString path=unixpath;
  while((n=path.find("/")),n!=YString::npos){
    path[n]='\\';
  }
  return path;
}
//--------------------------------------------------------------------------
YString YMUDSettings::getCommandFIFOPathName(YSession* session)
{
  if(!session) { //单线程命令处理
    return getFIFOPath()+getPathSeparator()+"command.fifo";
  }
  else {  //多线程命令处理(每Session一个线程)
    return getFIFOPath()+getPathSeparator()+session->getID()+"_cmd.fifo";
  }
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDSettings::set(YString name, float value)
{
  m_property_group->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDSettings::set(YString name, long value)
{
  m_property_group->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDSettings::set(YString name, YString value)
{
  m_property_group->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
long YMUDSettings::getAsLong(YString name)
{
  return m_property_group->getAsLong(name);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
float YMUDSettings::getAsFloat(YString name)
{
  return m_property_group->getAsFloat(name);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
YString YMUDSettings::getAsString(YString name)
{
  return m_property_group->getAsString(name);
}


