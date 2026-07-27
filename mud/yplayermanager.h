//---------------------------------------------------------------------------
//
// yplayermanager.h    2000年6月12日
//
// 类YPlayerManager：玩家登录、退出等操作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YPLAYERMANAGER_H__
#define __YPLAYERMANAGER_H__

#include <map>
#include "yactor.h"
#include "yplayer.h"
#include "ynpc.h"

class YPlayerManager {
  private:
    map<YString, YPlayer*, less<YString> > m_playergroup;
    map<YString, YNPC*, less<YString> > m_npcgroup;
  public:
		YPlayerManager();  //构造函数
		~YPlayerManager(); //析构函数
    //登录，成功返回创建的YPlayer对象，失败返回NULL
    YPlayer* login(YString username, YString password);
    //退出
    void quit(YString username);
    //用户是否在线
    inline bool isOnline(YString username);
    //用户是否在线
    inline bool isNPCExist(YString npcname);
    //查用户，返回YPlayer对象指针，没找到返回NULL
    YActor* getActor(const YString& actorname);
    YPlayer* getPlayer(const YString& playername);
    YNPC* getNPC(const YString& npcname);
    //登记NPC
    void addNPC(YNPC* NPC){m_npcgroup[NPC->getObjectName()]=NPC;};
    //去除NPC
    void removeNPC(const YString& NPCName){m_npcgroup.erase(NPCName);};
    //返回用户数据文件名, userdatafilename传回用户的文件名，
    //realuserdatafilename传回用于初始化的数据文件名(主要用于新人)
    void getUserDataFileName(const YString& username,YString& userdatafilename,YString& realuserdatafilename);
    YString getNPCDataFileName(YString npcname);

    //返回在线玩家列表
    YString enumPlayer(void);
    YString enumPlayerForDisplay(void);
};

#endif //__YPLAYERMANAGER_H__
