//---------------------------------------------------------------------------
//
// ycomm.h    2001年2月28日
//
// 类YComm：处理客户端与服务器的通讯
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YCOMM_H__
#define __YCOMM_H__
#include <map>
#include "ysessionmanager.h"
#include <cc++/common.h>
using namespace ost;
class YComm : public Thread {
  private:
    int m_port; //服务端口
    int m_maxline; //最大的命令字节数（读缓冲大小）
    int m_maxopen; //最大连接数
    int m_sessionLen; //sessionID的长度
    char* m_rdbuf;  //读缓冲
    map<int, YSession*, less<int> > m_fd_session_dic; //通过描述符查session的字典
    map<YSession*, int, less<YSession*> > m_session_fd_dic; //通过session查描述符的字典
    time_t* m_fd_accept_time; //连接accept时间，用于判断超时
		struct pollfd *m_client;
		struct pollfd *m_client_wr;  //用于写的
    int m_maxi;
    bool m_finish; //结束标志
    void init(void) {};
    void cleanTimeoutConnection(void);
  protected:

  public:
		YComm(int port=6050, int maxline=256, int maxopen=1500, int sessionLen=10);  //构造函数
		~YComm(); //析构函数
    virtual void run(void);
    void stop(void){m_finish=true;};
		void deleteSession(YSession* session);
		void addSession(YSession* session);
};

#endif //__YCOMM_H__
