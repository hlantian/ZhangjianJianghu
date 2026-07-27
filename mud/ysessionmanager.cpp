//YSessionmanager.cpp--类YSessionManager(会话集)的实现
#include "webmudcore.h"

//--------------------------------------------------------
//构造函数
YSessionManager::YSessionManager():m_playerCount(0)
{
  #ifdef __WIN32__
  randomize();
  #else //UNIX
  srand(time(0));
  #endif //__WIN32__
  m_PlayerCountFileName=g_Settings->getAsString("上线人数文件名");
}
//-------------------------------------------------------- 
//指定Session是否存在 
bool YSessionManager::exist(YString ID) 
{ 
  return m_sessiongroup.find(ID)!=m_sessiongroup.end(); 
} 
//--------------------------------------------------------
//getSession(会话)--返回指定ID的会话
YSession* YSessionManager::getSession(YString ID)
{
  if(exist(ID)) return m_sessiongroup[ID];
  else return NULL;
}
//--------------------------------------------------------
//CheckTime(验证时效)--检查所有会话的时效，终止过期会话
bool YSessionManager::checkTime(void)
{
    map<YString, YSession*, less<YString> >::iterator it;
    it=m_sessiongroup.begin();
    while(it!=m_sessiongroup.end()) {
      if(YDateTime::now()-(*it).second->getLastAccessTime() > g_Settings->getMaxIdleTime()) {
        endSession((*it).second->getID());
      }
    }
    return true; //临时
}
//--------------------------------------------------------
//EndSession(终止会话)--终止会话
bool YSessionManager::endSession(YString ID)
{
   YSession* session=NULL;
   if(exist(ID)) session=m_sessiongroup[ID];
   //从列表中删除
   m_sessiongroup.erase(ID);
   //人数减一
   decreasePlayerCount();
   //析构会话
   if(session) delete session;
   return true;
}
//--------------------------------------------------------
//NewSession(建立会话)--建立一次会话
YSession* YSessionManager::newSession(YString username, YString password)
{
    //YErr::show("[YSessionManager::newSession]entered.");
    YPlayer* player;
    if((player=g_PlayerManager->getPlayer(username))!=NULL) { //该玩家上次未正常退出
      //YErr::show("[YSessionManager::newSession]Player logined again.");
      //player->display("$%$$^Dfkw34&#@#!-----quit1-----&^*^*57%$&*9##",false,JAVASCRIPT_MSG);
      g_InfoChat->talk(NULL,player->getDisplayName()+"再次连线来到了仗剑江湖。",player);
      YSession* session=player->getSession();
      #ifndef __WIN32__
        g_Comm->deleteSession(session);
        g_Comm->addSession(session);
      #endif
      session->message_buf.erase();
      player->look_b();
      session->getMessageFIFO()->clear();
      return session;
    }
    YString ID=createUniqueID();
    player=g_PlayerManager->login(username, password);
    if(!player) {
      YErr::show("[YSessionManager::newSession]player "+username+" is NULL.");
      return NULL;
    }
    YSession* session=new YSession(ID, player);
    increasePlayerCount();
    player->setSession(session);
    g_InfoChat->talk(NULL,player->getDisplayName()+"来到了仗剑江湖。",player);
    //g_SystemChat->subscribe(player);

    YString roomName=player->getAsString("room_name");
 	  if(roomName=="") roomName=g_Settings->getFistComrIn();//getAsString("初始房间");
   	player->setRoom(roomName);
    YAbstractRoom* room=g_Map->getRoom(roomName, NULL);
 	  if(room) room->addChild(player);
   	else g_err.show("[YSessionManager::newSession]room of user cannot load.");

    m_sessiongroup[ID]=session;
    #ifdef MULTI_THREAD_MUD
      session->startReadingCommand();
    #endif //MULTI_THREAD_MUD
    return session;
}
//--------------------------------------------------------
//创建一个唯一的ID
YString YSessionManager::createUniqueID(void)
{
  YString ID(g_Settings->getSessionIDLength(), 'X');
  do {
    for(int i=0; i<g_Settings->getSessionIDLength(); i++) {
      char r=rand()%62; //62=26+26+10 大小写字母、数字
      if(r<26) { //大写字母
        ID[i]='A'+r;
      }
      else if((r>=26)&&(r<52)) { //小写字母
        ID[i]='a'+r-26;
      }
      else { //数字
        ID[i]='0'+r-52;
      }
    }
  }while(exist(ID));
  return ID;
}
//---------------------------------------------------------------
//建立FIFO并开始读取命令,成功返回0
int YSessionManager::startAcceptLogin(void)
{
  unsigned long write_timeout=-1; //回写session号的超时时间

  cout<<"[YSessionManager]starting accept longin ..."<<endl;
  m_finish=false; //重置停止标志
  //建立FIFO以读取命令
  #ifdef __WIN32__
    m_FIFO=new YFIFO(g_Settings->getLoginFIFOPathName(),"rd",100*1024);
  #else //UNIX
    m_FIFO=new YFIFO_UNIX(g_Settings->getLoginFIFOPathName(),"rd",100*1024);
  #endif //__WIN32__
  while(!m_finish) {
    YString userinfo=m_FIFO->read();
    #ifdef __USE_SEMAPHORE__
      if(g_SystemSemaphore!=SEM_FAILED) {
        //g_err.show("[YSessionManager::startAcceptLogin]等待系统信号灯....");
        if(sem_wait(g_SystemSemaphore)==0) {
          //g_err.show("[YSessionManager::startAcceptLogin]等待系统信号灯结束.");
        }
        else {
          g_err.show("[YSessionManager::startAcceptLogin]等待系统信号灯失败.");
        }
      }
    #endif
    bool first=true;
    if((!g_Busy) && g_Busy_Wait) sleep(10);
    while(g_Busy) {
      if(first) {
        if(!g_Busy_Wait) g_Busy_Wait=2;
        g_applog->write("[YSessionManager::startAcceptLogin]系统忙(g_Busy="+(YString)g_Busy+")");
      }
      first=false;
    }
    g_Busy=1;          
    if(g_Busy_Wait==1) g_Busy_Wait=0;

    //cout<<"userinfo="<<userinfo<<endl;
    YString name=userinfo.getWord("\t");
    YString password=userinfo.getWord("\t");
    YString sessionid=userinfo.getWord("\t");
    //cout<<"fifoSessionID="<<sessionid<<endl;
    #ifdef __WIN32__
      YFIFO fifoSessionID(sessionid, "wd", 128);
    #else //UNIX
      YFIFO_UNIX fifoSessionID(sessionid, "wd", 128);
    #endif //__WIN32__
    if(g_DeniedPlayerList->isIn(name)) {
      fifoSessionID.write("denied",write_timeout);
    }
    else {
      YSession* session=newSession(name,password);
      //cout<<"User "<<name<<"("<<password<<") login ";
      //if(session) cout<<"successfully"<<endl;
      //else cout<<"failed."<<endl;
      if(session) {
        fifoSessionID.write(session->getID(),write_timeout);
        //cout<<"fifoSessionID.write("<<session->getID()<<")"<<endl;

        session->getPlayer()->setSex(userinfo.getWord("\t"));
        session->getPlayer()->set("IP",userinfo); //userinfo中只剩下IP了
      	//session->getPlayer()->look();
      }
      else {
        fifoSessionID.write("fail",write_timeout);
        //cout<<"fifoSessionID.write(\"notuser\")"<<endl;
      }
    }
    g_Busy=0;
    #ifdef __USE_SEMAPHORE__
      if(g_SystemSemaphore!=SEM_FAILED) {
        //g_err.show("[YSessionManager::startAcceptLogin]挂出系统信号灯....");
        if(sem_post(g_SystemSemaphore)==0) {
          //g_err.show("[YSessionManager::startAcceptLogin]挂出系统信号灯结束.");
        }
        else {
          g_err.show("[YSessionManager::startAcceptLogin]挂出系统信号灯失败.");
        }
      }
    #endif
  }
  delete m_FIFO;

  return 0;
}
//---------------------------------------------------------------
//运行线程(继承自Thread)
void YSessionManager::run(void)
{ 
  startAcceptLogin();
}
//---------------------------------------------------------------
//人数加一
void YSessionManager::increasePlayerCount(void)
{
  m_playerCount++;
  if(m_playerCount>m_max_playerCount)m_max_playerCount=m_playerCount;
  writePlayerCount();
}
//---------------------------------------------------------------
//人数减一
void YSessionManager::decreasePlayerCount(void)
{
  m_playerCount--;
  writePlayerCount();
}
//---------------------------------------------------------------
//将人数写至外部文件
void YSessionManager::writePlayerCount(void)
{
  FILE* f=fopen(m_PlayerCountFileName.c_str(),"wt");
  if(!f) {
    YErr::show("[YSessionManager::writePlayerCount]无法打开文件："+m_PlayerCountFileName);
    return;
  }
  fprintf(f,"%d",m_playerCount);
  fclose(f);
}

