//---------------------------------------------------------------------------
//
// yplayermanager.cpp    2000年6月12日
//
// 类YPlayerManager：玩家登录、退出等操作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

//---------------------------------------------------------------------------
//YPlayerManager构造函数
YPlayerManager::YPlayerManager()
{
}
//---------------------------------------------------------------------------
//YPlayerManager析构函数
YPlayerManager::~YPlayerManager()
{
}
//---------------------------------------------------------------------------
//登录，成功返回创建的YPlayer对象，失败返回NULL
YPlayer* YPlayerManager::login(YString username, YString password)
{
   YUser* user=g_UserManager->login(username,password);
   if(!user) return NULL;

   YString userdatafilename,realuserdatafilename;
   getUserDataFileName(username,userdatafilename,realuserdatafilename);
   //zhy_begin
   YString classname="";
   YString datafilenamepath=g_Settings->getRootPath()+g_Settings->getPathSeparator()
                     +PATH(realuserdatafilename)+".profile";

   FILE *datafile=fopen(datafilenamepath.c_str(),"rt");
   if(datafile) {
    char s[1024];
    if(fgets(s,1024,datafile)!=NULL) {
      char *val=strchr(s,'=');
      if(!val) {
        fclose(datafile);
        delete user;
        return NULL;
      }
      *val='\0';
      val++;
      trim(s);
      trim(val);
      if(strcmp(s,"#class")==0) classname=val;
    }
    fclose(datafile);
   }
   YPlayer* player;
   if(classname=="YWizard") player=new YWizard(user,realuserdatafilename);  //巫师
   else if(classname=="YTailPlayer") player = new YTailPlayer(user,realuserdatafilename);  //受监视玩家
   else player=new YPlayer(user, realuserdatafilename);                     //普通玩家
   if(!player) {
     delete user;
     return NULL;
   }
   if((player->isLoadOK())||(classname=="YWizard") ||(classname=="YTailPlayer")) {
     //YPlayer* player=new YPlayer(user, realuserdatafilename);
     player->setDataFileName(userdatafilename);
     player->setUserManager(user->getUserManager());

     m_playergroup[username]=player; //加入用户组
   }
   else {
     delete player;
     delete user;
     return NULL;
   }

   delete user;
   return player;
}
//---------------------------------------------------------------------------
//退出
void YPlayerManager::quit(YString username)
{
   YPlayer* player=NULL;
   if(isOnline(username)) player=m_playergroup[username];
   //从列表中删除
   m_playergroup.erase(username);
   //析构用户
   if(player) delete player;
}
//---------------------------------------------------------------------------
//用户是否在线
bool YPlayerManager::isOnline(YString username)
{
  return m_playergroup.find(username)!=m_playergroup.end();
}
//---------------------------------------------------------------------------
//用户是否在线
bool YPlayerManager::isNPCExist(YString npcname)
{
  return m_npcgroup.find(npcname)!=m_npcgroup.end();
}
//---------------------------------------------------------------------------
//查用户，返回YPlayer对象指针，没找到返回NULL
YActor* YPlayerManager::getActor(const YString& actorname)
{
  if(isNPCExist(actorname)) return m_npcgroup[actorname];
  else if(isOnline(actorname)) return m_playergroup[actorname];
  else return NULL;
}
//---------------------------------------------------------------------------
//查用户，返回YPlayer对象指针，没找到返回NULL
YPlayer* YPlayerManager::getPlayer(const YString& username)
{
  if(isOnline(username)) return m_playergroup[username];
  else return NULL;
}
//---------------------------------------------------------------------------
//查用户，返回YPlayer对象指针，没找到返回NULL
YNPC* YPlayerManager::getNPC(const YString& npcname)
{
  if(isNPCExist(npcname)) return m_npcgroup[npcname];
  else return NULL;
}
//---------------------------------------------------------------------------
//返回用户数据文件名, userdatafilename传回用户的文件名，
//realuserdatafilename传回用于初始化的数据文件名(主要用于新人)
void YPlayerManager::getUserDataFileName(const YString& username,
                                      YString& datafilename,
                                      YString& realdatafilename)
{
   datafilename=g_Settings->getPlayerPath()+g_Settings->getPathSeparator()+username;
   realdatafilename=g_Settings->getRootPath()+g_Settings->getPathSeparator()
                     +PATH(datafilename)+".profile";
   int handle=open(realdatafilename.c_str(),O_RDONLY,S_IREAD);
   if(handle==-1) {
    if(errno==ENOENT) {
      realdatafilename=g_Settings->getAsString("新玩家");
    }
   }
   else realdatafilename=datafilename;
   close(handle);
   return;
}
//---------------------------------------------------------------------------
//返回在线玩家列表
YString YPlayerManager::enumPlayerForDisplay(void)
{
  map<YString, YPlayer*, less<YString> >::iterator it=m_playergroup.begin();
  YString retS="";
  while(it!=m_playergroup.end()) {
    retS+=(*it).second->getDisplayName()+" ";
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//返回在线玩家列表
YString YPlayerManager::enumPlayer(void)
{
  map<YString, YPlayer*, less<YString> >::iterator it=m_playergroup.begin();
  YString retS="";
  while(it!=m_playergroup.end()) {
    retS+=(*it).second->getObjectName()+" ";
    it++;
  }
  return retS;
}

