//---------------------------------------------------------------------------
//
// global.h    2000年6月12日
//
// 定义程序中的几个全局变量
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#include "ymudsettings.h"
#include "yxiluusermanager.h"
#include "yusermanager.h"
#include "ysessionmanager.h"
#include "ymap.h"
#include "ycommand.h"
#include "ychat.h"
#include "ychatmanager.h"
#include "yemote.h"
#include "ywugong.h"
#include "yquest.h"
#include "yfaction.h"
#include "ystringlist.h"
#include "ystopwatch.h"
#include "ycounter.h"
#include "ycomm.h"

class YPlayerManager;

extern YMUDSettings* g_Settings;
extern YRoom* g_GrandpaRoom; //提供一个用作临时Owner的物体，避免错误
extern YRoom* g_LoadRoom; //预装载所有物品的房间，以增加装载速度
extern YXiluUserManager* g_XiluUserManager;
extern YUserManager* g_UserManager;
extern YPlayerManager* g_PlayerManager;
extern YSessionManager* g_SessionManager;
extern YMap* g_Map;
extern YChatManager* g_ChatManager;
extern YCommand* g_Command;
#ifndef __WIN32__
  extern YComm* g_Comm;
#endif

//公共chat
extern YChat* g_SystemChat;
extern YChat* g_InfoChat;
extern YChat* g_NormalChat;
extern YChat* g_NewUserChat;
extern YChat* g_RumorChat;
//错误chat
extern YChat* g_ErrorChat;
//门派chat
extern YChat* g_HuaShanChat;
extern YChat* g_WuDangChat;
extern YChat* g_GuMuChat;
extern YChat* g_ShaoLinChat;
extern YChat* g_EMeiChat;
extern YChat* g_GaiBangChat;
extern YChat* g_BaiTuoChat;
extern YChat* g_MingJiaoChat;
extern YChat* g_XueDaoChat;
extern YChat* g_XiaKeChat;
extern YChat* g_RiYueChat;
extern YChat* g_DaLiChat;
extern YChat* g_TaoHuaChat;
extern YChat* g_HongHuaChat;
extern YChat* g_LingJiuChat;
extern YChat* g_ShenLongChat;

extern YStringList* g_DeniedPlayerList;

extern YStopwatch* g_Stopwatch;
extern YCounter* g_Counter;

extern YEmote* g_Emote;
extern YWugong* g_Wugong;
extern YQuest* g_Quest;
extern YFaction* g_Faction;

extern int g_Busy;   //系统忙标志
extern int g_Busy_Wait;   //排队
#ifndef __WIN32__ //unix
extern sem_t* g_SystemSemaphore;
#endif
