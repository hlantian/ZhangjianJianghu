//---------------------------------------------------------------------------
//
// YFIFO_UNIX_unix.cpp    2000年6月12日
//
// 类YFIFO_UNIX：在unix环境下提供对FIFO的支持
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#include <fstream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef __WIN32__
  #include <windows.h>
  #include <fcntl.h>
  #include <io.h>
#endif //__WIN32__

#include "yfifo_unix.h"
#include "yerr.h"
#include "ylogfile.h"
#include "ydatetime.h"

#ifndef EEXIST
#define EEXIST 10
#endif
//---------------------------------------------------------------------------
//YFIFO_UNIX构造函数
YFIFO_UNIX::YFIFO_UNIX(YString name, YString mode, int shm_size):
m_name(name),
m_mode(mode),
delim("\n-------##&*43fjiHH^*##--------"),
MAXLEN(1024)
{
  //这里有安全问题----以后修改
  #define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

  if((mkfifo(name.c_str(),FILE_MODE)<0)&&(errno!=EEXIST)) {
    g_applog->write("cannot create fifo "+name);
  }
}
//---------------------------------------------------------------------------
//YFIFO_UNIX析构函数
YFIFO_UNIX::~YFIFO_UNIX()
{
#ifdef __WIN32__ 
 if(m_mode[0]=='r') _unlink(m_name.c_str());
#else //UNIX
 if(m_mode[0]=='r') unlink(m_name.c_str());
#endif //__WIN32__ 
}
//---------------------------------------------------------------------------
int YFIFO_UNIX::write(YString s, unsigned long timeout)
{
  if(m_mode[0]!='w') {
    g_err.ErrDescription="mode!=w";
    g_applog->write(g_err.ErrDescription);
    return -1;
  }
  YDateTime begin_time;
  int flags=O_WRONLY;
  if(timeout!=-1) {
    flags |= O_NONBLOCK;
  }
  int fd=open(m_name.c_str(),flags,0);
  if(fd<0) {
    g_err.ErrDescription="[YFIFO_UNIX::write]cannot open "+m_name+"("+strerror(errno)+")";
    YErr::show(g_err.ErrDescription);
    return -2;
  }
  int n;
  while(true) {
    n=::write(fd,s.c_str(),s.size());
    if(n<0) {   //出错
      if(errno==EAGAIN) {  //非阻塞方式中没有写入数据
        if((YDateTime::now()-begin_time)*1000>=timeout) {
          n=0;
          YErr::show("[YFIFO_UNIX::write]写超时("+m_name+")。");
          break;
        }
      }
      else {
        YErr::show("fifo "+m_name+" write NOT successed."+"("+strerror(errno)+")");
        n=0;
        break;
      }
    }
    else break;
  }
  close(fd);
  if(n>0) return 0;
  else return -3;
}
//---------------------------------------------------------------------------
YString YFIFO_UNIX::read(int maxlen, unsigned long timeout)
{
  if(m_mode[0]!='r') {
    g_err.ErrDescription="mode!=r";
    g_applog->write(g_err.ErrDescription);
    return "";
  }
  YDateTime begin_time;
  int flags=O_RDONLY;
  if(timeout!=-1) {
    flags |= O_NONBLOCK;
  }
  int fd=open(m_name.c_str(),flags,0);
  if(fd<0) {
    YErr::show("cannot open fifo "+m_name+"("+strerror(errno)+")");
    return "";
  }
  int max=(maxlen==0?MAXLEN:maxlen);
  char buf[max];
  int n;
  while(true) {
    n=::read(fd,buf,max-1);
    if(n<0) {   //出错
      if(errno==EAGAIN) {  //非阻塞方式中没有读到数据
        if((YDateTime::now()-begin_time)*1000>=timeout) {
          n=0;
          break;
        }
      }
      else {
        YErr::show("fifo "+m_name+" read NOT successed."+"("+strerror(errno)+")");
        n=0;
        break;
      }
    }
    else break;
  }
  buf[n]='\0';
  close(fd);
  return buf; 
}

