//---------------------------------------------------------------------------
//
// webmud.cpp    2000年7月20日
//
// WebMud 系统主程序
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmud.h"

//一些全局变量
YMUDSettings* g_Settings;
YRoom* g_GrandpaRoom; //提供一个用作临时Owner的物体，避免错误
YRoom* g_LoadRoom=NULL; //预装载所有物品的房间，以增加装载速度

YXiluUserManager* g_XiluUserManager;
YUserManager* g_UserManager;
YPlayerManager* g_PlayerManager;
YSessionManager* g_SessionManager;
YMap* g_Map;
YChatManager* g_ChatManager;
YCommand* g_Command;
#ifndef __WIN32__
  YComm* g_Comm;
#endif

//公共chat
YChat* g_SystemChat;
YChat* g_InfoChat;  //进入退出信息
YChat* g_NormalChat;
YChat* g_NewUserChat;
YChat* g_RumorChat;
//错误chat
YChat* g_ErrorChat=NULL;
//门派chat
YChat* g_HuaShanChat;
YChat* g_WuDangChat;
YChat* g_GuMuChat;
YChat* g_ShaoLinChat;
YChat* g_EMeiChat;
YChat* g_GaiBangChat;
YChat* g_BaiTuoChat;
YChat* g_MingJiaoChat;
YChat* g_XueDaoChat;
YChat* g_XiaKeChat;
YChat* g_RiYueChat;
YChat* g_DaLiChat;
YChat* g_TaoHuaChat;
YChat* g_HongHuaChat;
YChat* g_LingJiuChat;
YChat* g_ShenLongChat;

YStringList* g_DeniedPlayerList;

YStopwatch* g_Stopwatch;
YCounter* g_Counter;

YEmote* g_Emote;
YWugong* g_Wugong;
YQuest* g_Quest;
YFaction* g_Faction;

int g_Busy=0;
int g_Busy_Wait=0;

#ifndef __WIN32__ //UNIX
  sem_t* g_SystemSemaphore;
  //extern char *_sys_errlist[];
#endif


int main(int argc, char* argv[])
{
  umask(0);

  #ifndef __WIN32__ //UNIX
    struct rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim); //取进程最大打开文件限制
    cout<<"最大打开文件="<<rlim.rlim_cur<<"/"<<rlim.rlim_max<<endl;
    //rlim.rlim_cur=RLIM_INFINITY;
    //rlim.rlim_max=RLIM_INFINITY;
    rlim.rlim_cur=8192;
    rlim.rlim_max=8192;
    if(setrlimit(RLIMIT_NOFILE, &rlim)==0) {
      cout<<"设置最大打开文件="<<rlim.rlim_cur<<"/"<<rlim.rlim_max<<endl;
    }
    else {
      cout<<"设置最大打开文件失败。"<<endl;
    }
    getrlimit(RLIMIT_NOFILE, &rlim); //取进程最大打开文件限制
    cout<<"现在最大打开文件="<<rlim.rlim_cur<<"/"<<rlim.rlim_max<<endl;
    cout<<"openmax="<<sysconf(_SC_OPEN_MAX)<<endl;
  #endif

  YWebMUD* WebMUD;
  if((argc>1)&&(strcmp(argv[1],"continue")==0)) {  //继续使用上次内存中的对象
  }
  else {  //新建内存中的对象
    g_Counter=new YCounter;
    g_Stopwatch=new YStopwatch(20);
    g_Stopwatch->setName(0,"总计时");
    g_Stopwatch->start(0);
    g_Stopwatch->setName(1,"命令处理");
    g_Stopwatch->setName(2,"OnTimer(All)");
    g_Stopwatch->setName(3,"poll循环");
    g_Stopwatch->setName(4,"poll循环(未写)");

    g_applog=new YLogFile("/var/log/webmud/newmud.log");
    if(g_applog->write("[main]start**********************************************************")!=0) cout<<"log error"<<endl;

    g_Settings=new YMUDSettings(argc, argv, "webmud.conf");
    g_LoadRoom=new YRoom("room/loadroom");
    g_GrandpaRoom=new YRoom("room/defaultroom");
    g_XiluUserManager=new YXiluUserManager;
    g_UserManager=new YUserManager;
    g_PlayerManager=new YPlayerManager;
    g_SessionManager=new YSessionManager;
    g_Map=new YMap;
    g_ChatManager=new YChatManager;
    g_Command=new YCommand;
    #ifndef __WIN32__
      g_Comm=new YComm(6038,256,6000,10);
    #endif

    //公共chat
    g_SystemChat=new YChat;
    g_InfoChat=new YChat;
    g_NormalChat=new YChat;
    g_NewUserChat=new YChat;
    g_RumorChat=new YChat;
    //错误chat
    g_ErrorChat=new YChat;
    //门派chat
    g_HuaShanChat=new YChat;
    g_WuDangChat=new YChat;
    g_GuMuChat=new YChat;
    g_ShaoLinChat=new YChat;
    g_EMeiChat=new YChat;
    g_GaiBangChat=new YChat;
    g_BaiTuoChat=new YChat;
    g_MingJiaoChat=new YChat;
    g_XueDaoChat=new YChat;
    g_XiaKeChat=new YChat;
    g_RiYueChat=new YChat;
    g_DaLiChat=new YChat;
    g_TaoHuaChat=new YChat;
    g_HongHuaChat=new YChat;
    g_LingJiuChat=new YChat;
    g_ShenLongChat=new YChat;
    
    g_DeniedPlayerList=new YStringList(g_Settings->getAsString("禁止登陆玩家名单文件名"));


    g_Emote=new YEmote("common/emote");
    g_Wugong=new YWugong("common/wugong");
    g_Quest=new YQuest("common/quest");
    g_Faction=new YFaction("common/faction");
    g_Faction->onAfterLoad();

    WebMUD=new YWebMUD;
    #ifndef __WIN32__ //UNIX
      //yalloc_setkey(1,g_applog);
      //yalloc_setkey(2,g_Settings);
    #endif //UNIX
  }

  #ifndef __WIN32__ //UNIX
  YString sem_name=g_Settings->getRootPath()+g_Settings->getPathSeparator()+"system.sem";
  g_SystemSemaphore=sem_open(sem_name.c_str(),O_CREAT,
                             S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH,1);
  if(g_SystemSemaphore==SEM_FAILED) {
    g_err.show("[main]Semphore of system("+sem_name+") create failed, ("+_sys_errlist[errno]+")");
  }
  //else g_err.show("[main]Semphore of system("+sem_name+") create successfully.");
  #endif
  
  WebMUD->start();

  return 0;

  #ifndef __WIN32__ //UNIX
  if(sem_close(g_SystemSemaphore)==0) g_err.show("[main]Semphore of system close successfully.");
  else g_err.show("[main]Semphore of system close failed.");
  if(sem_unlink((g_Settings->getRootPath()+g_Settings->getPathSeparator()+"system.sem").c_str())==0) g_err.show("[main]Semphore of system unlink successfully.");
  else g_err.show("[main]Semphore of system unlink failed.");
  #endif

  delete g_Settings;
  delete g_XiluUserManager;
  delete g_UserManager;
  delete g_PlayerManager;
  delete g_SessionManager;
  delete g_Map;
  delete g_ChatManager;
  delete g_Command;

  delete g_SystemChat;
  delete g_NormalChat;
  delete g_RumorChat;
  delete g_SystemChat;

  delete g_Wugong;
  delete g_Quest;
  delete g_Faction;
  
  delete g_GrandpaRoom;

  delete WebMUD;
}


