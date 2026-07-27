//ysessionmanager.h--类YSessionManager(会话集)的声明
#ifndef __YSessionManager_H__
#define __YSessionManager_H__

#include <map>
#include <stdlib.h>
#include "ystring.h"
#include "ysession.h"
//#include "thread.h"
#ifdef __WIN32__
  #include "yfifo.h"
#else  //UNIX
  #include "yfifo_unix.h"
#endif

class YSessionManager : public Thread{
  private:
    map<YString, YSession*, less<YString> > m_sessiongroup;
    bool m_finish;  //停止标志，用于停止线程运行
    #ifdef __WIN32__
       YFIFO* m_FIFO;
    #else  //UNIX
       YFIFO_UNIX* m_FIFO;
    #endif
    YString m_PlayerCountFileName;
  protected:
    void run(void);   //运行线程(继承自Thread)

  private:
    int m_max_playerCount;
    int m_playerCount;
    void increasePlayerCount(void);  //人数加一
    void decreasePlayerCount(void);  //人数减一
    void writePlayerCount(void); //将人数写至外部文件
  public:
    int getPlayerCount(void){return m_playerCount;};
  public:
	  //YSessionManager(构造函数)
    YSessionManager();
	  ~YSessionManager(){}; //析构函数

    //帧听FIFO，处理用户登录
    int YSessionManager::startAcceptLogin(void);
    //停止用户登录(异步)
    void YSessionManager::stopAcceptLogin(void){m_finish=true;};
    //创建一个唯一的ID
    YString createUniqueID(void);
    //创建一个Session
    YSession* newSession(YString username, YString password);
    //指定Session是否存在
    inline bool exist(YString ID);
	  //Session(会话)--返回指定ID的会话
	  YSession* getSession(YString ID);
	  //CheckTime(验证时效)--检查所有会话的时效，终止过期会话
	  bool checkTime(void);
	  //EndSession(终止会话)--终止会话
	  bool endSession(YString ID);
};

#endif //__YSessionManager_H__
