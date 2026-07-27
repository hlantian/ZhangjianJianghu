//---------------------------------------------------------------------------
//
// ycomm.cpp    2001年2月2日
//
// 类YComm：处理客户端与服务器的通讯
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmudcore.h"
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/stropts.h>
#include <unistd.h>
#include "ycomm.h"
#ifndef INFTIM
	#define INFTIM -1
#endif
//---------------------------------------------------------------------------
//YComm构造函数
YComm::YComm(int port, int maxline, int maxopen, int sessionLen)
:m_port(port),m_maxline(maxline),m_maxopen(maxopen),
 m_sessionLen(sessionLen),m_maxi(0)
{
  m_rdbuf=(char*)new char[m_maxopen*m_maxline];
  m_fd_accept_time=new time_t[maxopen];
  m_client=(struct pollfd *)malloc(maxopen*sizeof(pollfd));
  m_client_wr=(struct pollfd *)malloc(maxopen*sizeof(pollfd));
  for(int i=0; i<maxopen; i++) {
    *(m_rdbuf+i*maxline)='\0';
    m_fd_accept_time[i]=0;
  }
  init();
}
//---------------------------------------------------------------------------
//YComm析构函数
YComm::~YComm()
{
  delete[] m_rdbuf;
}
//---------------------------------------------------------------------------
//增加一个session
void YComm::addSession(YSession* session)
{
	m_session_fd_dic[session]=-1;
}
//---------------------------------------------------------------------------
//删除一个session及对应的连接
void YComm::deleteSession(YSession* session)
{
	int fd=-1;

  //删除字典中的相关条目
  fd=m_session_fd_dic[session];
 	m_fd_session_dic.erase(fd);
  m_session_fd_dic.erase(session);

  //中断连接
  if(fd!=-1) {
  	for(int i=0; i<m_maxi; i++) {
  		if(m_client[i].fd==fd) {
  			::close(fd);
  			m_client[i].fd=-1;
  			m_client_wr[i].fd=-1;
  			break;
  		}
  	}
  }
}
//---------------------------------------------------------------------------
//YComm析构函数
void YComm::run(void)
{
	int connfd, sockfd;
	socklen_t clilen;
	struct sockaddr_in	cliaddr, servaddr;

  //设置信号处理
  struct sigaction act;
  act.sa_handler=SIG_IGN;
  sigemptyset(&act.sa_mask);
  act.sa_flags=SA_INTERRUPT;
  if(sigaction(SIGPIPE,&act,NULL)<0) {
    YErr::show("[YComm::Run]安装信号处理出错。");
  }

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd<0) {
    YString err=(YString)"[YComm::Run]Sock error("+strerror(errno)+").";
    g_applog->write(err);
    cout<<err<<endl;
    return;
  }
	
  //设置SO_REUSEADDR属性，以便重启服务时能绑定端口
  int val=1;
  int len=sizeof(val);

  //设置
  if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&val,len)<0) {
    g_applog->write("[YComm::Run]Setsockopt error.");
    //return;
  }

	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(m_port);

	if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) {
    g_applog->write("[YComm::Run]Bind error.");
    return;
  }

	if(listen(listenfd, 15)<0) {
    g_applog->write("[YComm::Run]Listen error.");
    return;
  }

	m_client[0].fd = listenfd;
	m_client[0].events = POLLIN;
	m_client_wr[0].fd = -1;
	for (int i = 1; i < m_maxopen; i++) {
		m_client[i].fd = -1;		/* -1 indicates available entry */
		m_client_wr[i].fd = -1;		/* -1 indicates available entry */
  }
	
	m_maxi = 0;					/* max index into m_client[] array */

	int nready;
	ssize_t n;

	bool writesomething=true;  //用于检测这个循环中是否写了东东
	bool first1=true;
	bool shouldWrite;
  m_finish=false;
  time_t last_clean_time=time(NULL); //上次清理超时连接的时间
	for ( ; ; ) {
    if(m_finish) break;

    //关于同步的处理
    if(!first1) g_Stopwatch->stop(3); //计时结束

    if(!first1) g_Busy=0;
    first1=false;
    //end of 关于同步的处理
		nready = poll(m_client, m_maxi+1, 2000); //设置2秒的超时用于给写

		if(writesomething==false) {g_Stopwatch->start(4);g_Stopwatch->stop(4);}
		writesomething=false;
    //关于同步的处理
    bool first=true;
    if((!g_Busy) && g_Busy_Wait) sleep(10);
    while(g_Busy) {
      if(first) {
        if(!g_Busy_Wait) g_Busy_Wait=2;
        g_applog->write("[YComm::Run]系统忙(g_Busy="+(YString)g_Busy+")");
      }
      first=false;
    }
    g_Busy=2;
    if(g_Busy_Wait==2) g_Busy_Wait=0;
    g_Stopwatch->start(3);  //计时开始
    //end of 关于同步的处理

    if(difftime(time(NULL),last_clean_time)>10) { //每10秒钟
      cleanTimeoutConnection();                  //清理超时连接
      last_clean_time=time(NULL);
    }

    if(nready<0) {  //错误
      g_applog->write("[YComm::Run]Poll Error.");
      continue;
    }
    if(nready==0) shouldWrite=true;  //超时,设置写标志
    else shouldWrite=false;

		if ((!shouldWrite)&&(m_client[0].revents & POLLIN)) {	/* 新连接 */
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
      if(connfd<0) {
        g_applog->write("[YComm::Run]Cannot Accept.");
        continue;
      }
      //cout<<"新联结\n";
      //将新连接设为非阻塞模式
      int val=fcntl(connfd, F_GETFL, 0);
      fcntl(connfd, F_SETFL, val|O_NONBLOCK);
      int index=-1;
			for (int i = 1; i < m_maxopen; i++) {
				if (m_client[i].fd < 0) {
					m_client[i].fd = connfd;	/* save descriptor */
					m_client_wr[i].fd = connfd;	/* save descriptor */
          m_fd_accept_time[i]=time(NULL); //保存连接时间
					*(m_rdbuf+i*m_maxline)='\0'; //清空读缓冲
          index=i;
					break;
				}
      }
			if (index==-1) {
        YErr::show("[YComm::Run]连接过多.");
        ::close(connfd);
        continue;
      }
			m_client[index].events = POLLIN;  //设置为可读
			m_client_wr[index].events = POLLOUT;  //设置为可写
      m_fd_session_dic[connfd]=NULL; //该连接还没有对应的Session

			if (index > m_maxi)
				m_maxi = index;				/* max index in m_client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}  //endif 新连接

		if (!shouldWrite) for (int i = 1; i <= m_maxi; i++) {	/* check all clients for data */
			if ( (sockfd = m_client[i].fd) < 0)	continue;

      if(m_client[i].revents &(POLLHUP|POLLNVAL|POLLERR)) {  //出错
        YSession* sess=m_fd_session_dic[sockfd];
        if(sess) m_session_fd_dic[sess]=-1;
        m_fd_session_dic.erase(sockfd);
				::close(sockfd);
				m_client[i].fd = -1;
				m_client_wr[i].fd = -1;
        continue;
      }

			if (m_client[i].revents & POLLIN) {  //可读
        //cout<<"可读\n";
        char *buf=m_rdbuf+m_maxline*i;
        int len=strlen(buf);  //取缓冲区已经读到的长度
				if ( (n = read(sockfd, buf+len, m_maxline-len-1)) < 0) {  //读
					if (errno == ECONNRESET) {   /*4connection reset by client */
            //cout<<"读时connection reset by client"<<endl;
            YSession* sess=m_fd_session_dic[sockfd];
            if(sess) m_session_fd_dic[sess]=-1;
            m_fd_session_dic.erase(sockfd);
						::close(sockfd);
						m_client[i].fd = -1;
						m_client_wr[i].fd = -1;
					}
          else {
            g_applog->write("[YComm::Run]读错误.");
            continue;
          }
				}
        else if(n == 0) {  /*4connection closed by client */
          //cout<<"读时connection closed by client"<<endl;
          YSession* sess=m_fd_session_dic[sockfd];
          if(sess) m_session_fd_dic[sess]=-1;
          m_fd_session_dic.erase(sockfd);
					::close(sockfd);
					m_client[i].fd = -1;
					m_client_wr[i].fd = -1;
				}
        else {  //真正读到了东西
          buf[len+n]='\0';  //设置结束标志
          //cout<<"读到的="<<buf<<endl;
          YSession* session=m_fd_session_dic[sockfd];
          if(session) { //session已确定
            char* loc=strchr(buf,'\n');
            if(loc==NULL) {   //没有换行符到达
              if((len+n)>=(m_maxline-1)) {   //但长度已经到maxline
                g_Command->executeCommand(session,buf); //执行命令
                buf[0]='\0'; //清空缓冲
              }
            }
            else {  //有换行符
              do {
                *loc='\0'; // 将换行符作为字符串结尾
                if(m_fd_session_dic.find(sockfd)==m_fd_session_dic.end()) {
                	break;   //如果执行过程中session已被删除，则不可再执行命令
                }
                g_Command->executeCommand(session,buf); //执行命令
                strcpy(buf,loc+1); //删去已执行的命令
              } while((loc=strchr(buf,'\n'))!=NULL); //还有命令的话继续执行
            }
          } //end if session已确定
          else if((len+n)>=m_sessionLen) { //读到了足够长的SessionID
            buf[m_sessionLen]='\0';
            YSession* tmp_session=g_SessionManager->getSession(buf);
            if(tmp_session==NULL) { //该Session不存在,关闭连接
            	//cout<<"该Session不存在,关闭连接"<<endl;
              m_fd_session_dic.erase(sockfd);
    					::close(sockfd);
    					m_client[i].fd = -1;
    					m_client_wr[i].fd = -1;
            }
            else {  //session存在
              int fd1;
              if((fd1=m_session_fd_dic[tmp_session])!=-1) { //session已经有对应的连接，关闭以前的连接
								for(int i=0; i<m_maxi; i++) {
							  	if(m_client[i].fd==fd1) {
							  		::close(fd1);
							  		m_client[i].fd=-1;
							  		m_client_wr[i].fd=-1;
							  		break;
							  	}
							  }
							  m_fd_session_dic.erase(fd1);
              }
              m_fd_session_dic[sockfd]=tmp_session;
              m_session_fd_dic[tmp_session]=sockfd;
            }
            strcpy(buf,buf+m_sessionLen+1); //删去SessionID
          } //end if --else 读到了足够长的SessionID

        } //end if -- else //真正读到了东西
				if (--nready <= 0) break;	   //没有可读写的描述符了
 			} //end if -- 可读
		} //end for -- check all clients for data
 			
		//-------------------------------
		//测试可写的描述符
		nready = poll(m_client_wr, m_maxi+1, 0); //写不阻塞

    if(nready<0) {  //错误
      g_applog->write("[YComm::Run]Read Poll Error.");
      continue;
    }
    if(nready==0) continue;  //超时
		for (int i = 1; i <= m_maxi; i++) {	/* check all clients for data to write*/
			if ( (sockfd = m_client_wr[i].fd) < 0)	continue;
      if(m_client_wr[i].revents &(POLLHUP | POLLNVAL|POLLERR)) {  //出错
        YSession* sess=m_fd_session_dic[sockfd];
        if(sess) m_session_fd_dic[sess]=-1;
        m_fd_session_dic.erase(sockfd);
				::close(sockfd);
				m_client[i].fd = -1;
				m_client_wr[i].fd = -1;
        continue;
      }

      if(m_client_wr[i].revents & POLLOUT) { //可写
      	//cout<<"可写"<<endl;
        YSession* session=m_fd_session_dic[sockfd];
        if(!session) {  //session不存在
          if (--nready <= 0) break;  //没有可读写的描述符了
          else continue;
        }
        if(session->message_buf.size()==0) { //没有东西需要写
          if (--nready <= 0) break;  //没有可读写的描述符了
          else continue;
        }
        writesomething=true;
        //cout<<"写的东东="<<session->message_buf<<endl;
				if ( (n = write(sockfd, session->message_buf.c_str(), session->message_buf.size())) < 0) {  //写
					if (errno == ECONNRESET) {   /*4connection reset by client */
            //cout<<"写时connection reset by client"<<endl;
            YSession* sess=m_fd_session_dic[sockfd];
            if(sess) m_session_fd_dic[sess]=-1;
            m_fd_session_dic.erase(sockfd);
						::close(sockfd);
						m_client[i].fd = -1;
						m_client_wr[i].fd = -1;
					}
          else {
            g_applog->write("[YComm::Run]写错误.");
            continue;
          }
				}
        else if(n == 0) {  /*4connection closed by client */
          //cout<<"写时connection closed by client"<<endl;
          YSession* sess=m_fd_session_dic[sockfd];
          if(sess) m_session_fd_dic[sess]=-1;
          m_fd_session_dic.erase(sockfd);
					::close(sockfd);
					m_client[i].fd = -1;
					m_client_wr[i].fd = -1;
				}
        else {  //真正写了东西
          session->message_buf.erase(0,n); //删除已写的部分
        }
				if (--nready <= 0) break;	   //没有可读写的描述符了
      }  //end if --  可写
		} //end for -- check all clients for data to write

    //关于同步的处理
    //end of 关于同步的处理
	} //end for -- 无限循环
}
//---------------------------------------------------------------------------
//清理超时连接
void YComm::cleanTimeoutConnection(void)
{
  static int times=0;
  int all=0,youxiao=0,bucha=0,chaoshi=0,yiyou=0,qingchu=0;
  times++;
  bool cleanall=false;
  if(times%10==0) {
    cleanall=true;
    YErr::show("[YComm::cleanTimeoutConnection]cleanall");
    times=0;
  }
  time_t now=time(NULL);
  for (int i = 1; i < m_maxi; i++) {
    all++;
    if (m_client[i].fd > 0) {  //有效描述符
      youxiao++;
      if(m_fd_accept_time[i]==0) {
        bucha++;
        continue; //不必检查
      }
      if((cleanall)||(difftime(now,m_fd_accept_time[i])>10)) { //10秒超时,另外每10次作彻底清除
        chaoshi++;
        if(m_fd_session_dic[m_client[i].fd]!=NULL) { //已经有session
          yiyou++;
          m_fd_accept_time[i]=0;  //以后就不用检查了
        }
        else {  //没有session与之连接，清除
          qingchu++;
          m_fd_session_dic.erase(m_client[i].fd);
          ::close(m_client[i].fd);
					m_client[i].fd = -1;
					m_client_wr[i].fd = -1;
        }
      }//endif 10秒超时
    } //endif 有效描述符
  } //end for
  YString errmsg="All:"+(YString)all+" 有效："+(YString)youxiao+" 不必检查："+(YString)bucha+"<BR>";
  errmsg+="超时："+(YString)chaoshi+" 已有session:"+(YString)yiyou+" 清除："+(YString)qingchu;
  YErr::show(errmsg);
}
