//---------------------------------------------------------------------------
//
// yfifo.cpp    2000年6月12日
//
// 类YFIFO：提供对FIFO的支持，在WIN32用文件仿真
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

/*
#include <io.h>
#include <sys/stat.h>
#include <fstream.h>
#include <sstream.h>
#include <string.h>
#ifdef __WIN32__
  #include <windows.h>
  #include <fcntl.h>
  #include <io.h>
#endif //__WIN32__

#include "yfifo.h"
#include "yerr.h"
*/
//---------------------------------------------------------------------------
//YFIFO构造函数
YFIFO::YFIFO(YString name, YString mode, int shm_size):
m_name(name),
m_mode(mode),
#ifndef __WIN32__  //UNIX
  m_sem(SEM_FAILED),
#endif
delim("\n-------##&*43fjiHH^*##--------"),
MAXLEN(1024)
{
  int handle;
  #ifdef __WIN32__
  	if((handle=_creat(m_name.c_str(), S_IWRITE))==-1) {
  #else //UNIX
	  #ifdef __USE_SEMAPHORE__
  		m_sem=sem_open((m_name+".sem").c_str(),O_CREAT,0666,1);
	  	if(m_sem==SEM_FAILED) g_applog->write("[YFIFO::YFIFO]Semphore of "+m_name+" create failed.");
  		else g_applog->write("[YFIFO::YFIFO]Semphore of "+m_name+" create successfully.");
	 	#endif
  	if((handle=creat(m_name.c_str(), 0666))==-1) {
  #endif //__WIN32__
  g_applog->write("[YFIFO::YFIFO]creat file "+m_name+" failed.");
  }
  g_applog->write("[YFIFO::YFIFO]file "+m_name+" created.");
  close(handle);
}
//---------------------------------------------------------------------------
//YFIFO析构函数
YFIFO::~YFIFO()
{
#ifdef __WIN32__
 if(m_mode[0]=='r') _unlink(m_name.c_str());
#else //UNIX
 if(m_mode[0]=='r') {
  unlink(m_name.c_str());
  #ifdef __USE_SEMAPHORE__
  if(sem_close(m_sem)==0) g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" close successfully.");
  else g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" close failed.");
  if(sem_unlink((m_name+".sem").c_str())==0) g_err.show("[YFIFO::~YFIFO]Semphore of "+m_name+" unlink successfully.");
  else g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" unlink failed.");
 	#endif
 }
#endif //__WIN32__
}
//---------------------------------------------------------------------------
int YFIFO::write(YString s, unsigned long timeout)
{
  #ifdef __USE_SEMAPHORE__
    //g_applog->write("[YFIFO::write]Semphore of "+m_name+" wait.");
    if(m_sem!=SEM_FAILED) sem_wait(m_sem);
    //g_applog->write("[YFIFO::write]Semphore of "+m_name+" wait end.");
  #endif
  if(m_mode[0]=='w') {
    ofstream out(m_name.c_str(),ios::out|ios::app);
    if(!out) {
      g_err.ErrDescription=YString("[YFIFO::write]open ")+m_name+" eror\n";
      g_err.show(g_err.ErrDescription);
      return -1;
    }
    out<<s;
    out<<delim;
    out.close();
    g_err.show("[YFIFO::write]write "+s+" to "+m_name);
  }
  #ifdef __USE_SEMAPHORE__
    //g_err.show("[YFIFO::write]Semphore of "+m_name+" post.");
    if(m_sem!=SEM_FAILED) sem_post(m_sem);
    //g_err.show("[YFIFO::write]Semphore of "+m_name+" post end.");
  #endif
  return 0;
}
//---------------------------------------------------------------------------
YString YFIFO::read(int maxlen, unsigned long timeout)
{
  if(maxlen==0)maxlen=MAXLEN;
  struct stat statbuf;
  #ifdef __WIN32__
    ostringstream outs;
  #else //UNIX
    ostrstream outs;
  #endif //__WIN32__ 
  while(messages.empty()) {
    if(m_mode[0]=='r') {
      while((stat(m_name.c_str(), &statbuf)!=0) || (statbuf.st_size==0)){
        //cout<<"stat:"<<stat(m_name.c_str(), &statbuf)<<" size:"<<statbuf.st_size<<endl;
        #ifdef __WIN32__
          Sleep(500); //等待0.5秒后再检查文件
        #else
          sleep(1);
        #endif //__WIN32__
      }
      //cout<<"stat:"<<stat(m_name.c_str(), &statbuf)<<" size:"<<statbuf.st_size<<endl;
      #ifdef __USE_SEMAPHORE__
        //g_err.show("[YFIFO::read]Semphore of "+m_name+" wait.");
        if(m_sem!=SEM_FAILED) sem_wait(m_sem);
        //g_err.show("[YFIFO::read]Semphore of "+m_name+" wait end.");
      #endif
      ifstream in(m_name.c_str());
      outs<<in.rdbuf()<<endl;
      in.close();
      //清空文件
      int handle;
      #ifdef __WIN32__
      if((handle=_creat(m_name.c_str(), S_IWRITE))==-1) {
      #else //UNIX
      if((handle=creat(m_name.c_str(), 0666))==-1) {
      #endif //__WIN32__
        cerr<<"[YFIFO::read]trunc file failed."<<endl;
      }
      close(handle);
      #ifdef __USE_SEMAPHORE__
        //g_err.show("[YFIFO::read]Semphore of "+m_name+" post.");
        if(m_sem!=SEM_FAILED) sem_post(m_sem);
        //g_err.show("[YFIFO::read]Semphore of "+m_name+" post end.");
      #endif
      //int handle=open(m_name.c_str(),O_TRUNC);
      //chsize(handle,0);
      //close(handle);
      //FILE *f=fopen(m_name.c_str(),"w");
      //fclose(f);
    }

    //把文件中取出的字符串分解放入队列
    YString ss;
    YString s=outs.str();
    int start=0;
    while(true) {
      int end=s.find(delim, start);
      if(end!=YString::npos) {
        YString ss(s,start,end-start);
        if(ss.size()>maxlen) ss.resize(maxlen);
        messages.push(ss);
        start=end+delim.size();
      }
      else {  //未找到分隔符
        if((start==0) && (s.size()>maxlen)) {
          s.resize(maxlen);
          messages.push(s);
        }
        break;
      }
    }
    #ifdef __WIN32__
      Sleep(500); //等待0.5秒后再检查文件
    #else
      sleep(1);
    #endif //__WIN32__
  }

  YString retVal=messages.front();
  if(retVal[retVal.size()-1]=='\n')retVal.resize(retVal.size()-1);
  messages.pop();
  return retVal;
}
//---------------------------------------------------------------------------
void YFIFO::clear(void)
{
  #ifdef __WIN32__
    _unlink(m_name.c_str());
  #else
    unlink(m_name.c_str());
  #endif
}
