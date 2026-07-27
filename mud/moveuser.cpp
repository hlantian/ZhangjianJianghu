//---------------------------------------------------------------------------
//
// login.cpp    2000年7月21日
//
// 用于处理玩家登录的CGI
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#include <iostream.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#ifdef __WIN32__
	#include <io.h>
#endif
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <utime.h>

//#include
#include "readcgi.h"
#include "writecgi.h"
#include "ystring.h"
#include "yerr.h"
#include "ylogfile.h"

bool login(YString name,YString password);
YString comm39(const YString& command,const YString& name,
            const YString& password,const YString& others="");
int legal(YString name);  //名字是否合法（比如不能有空格）
int copyfile(char* srcFileName, char* dstFileName);

int main(int argc, char* argv[])
{
    umask(0);
    g_applog=new YLogFile("/home/nobody/moveuser.log");

    YString sOldName;
    YString sOldPassword;
    YString sNewName;
    YString sNewPassword;
    YString sUserIP;

    if(iGetRequestMethod()==NO_REQUEST_METHOD) {
        cout<<"This Program is designed to run as a CGI script,";
        cout<<"not from the command line";
        return 0;
    }
    else if(iGetRequestMethod()==GET_REQUEST_METHOD) {
      PrintErrorMessagePage("请使用正确的方法登录系统!!");
      return 0;
    }
    else if(iGetRequestMethod()==POST_REQUEST_METHOD) {
        GetPOSTData();
        sOldName=FindPOSTValue("oldname");
        sOldPassword=FindPOSTValue("oldpassword");
        sNewName=FindPOSTValue("newname");
        sNewPassword=FindPOSTValue("newpassword");
        sUserIP=getenv("REMOTE_ADDR");

        if((sNewName=="")||(sNewPassword=="")||(sOldName=="")||(sOldPassword=="")) {
          PrintErrorMessagePage("信息填写不完整。");
					return 0;
        }
        if(legal(sOldName)==0) {
          PrintErrorMessagePage("旧代号合法，不能拷贝用户数据。");
					return 0;					
				}
        if(legal(sNewName)<0) {
          PrintErrorMessagePage("新代号不合法，不能拷贝用户数据。");
					return 0;					
				}
				if(!login(sOldName.url_encode(),sOldPassword.url_encode())) {
          PrintErrorMessagePage("旧代号/密码不正确，不能拷贝用户数据。");
					return 0;					
				}
				if(!login(sNewName.url_encode(),sNewPassword.url_encode())) {
          PrintErrorMessagePage("新代号/密码不正确，不能拷贝用户数据。");
					return 0;					
				}
				//条件符合，现在可以拷贝了
				int retval=setuid(0); //成为root,以便拷贝用户数据
				if(retval<0) {
          PrintErrorMessagePage("内部错误(201)，请与巫师联系。");
					return 0;					
				}
   			//旧玩家数据文件是否存在
				YString oldFileName="/home/mud/data/player/"+sOldName+".profile";
   			int handle=open(oldFileName.c_str(),O_RDONLY,S_IREAD);
   			if(handle==-1) {
    			if(errno==ENOENT) { //不存在
          	PrintErrorMessagePage(((YString)("代号"+sOldName+"没有对应的玩家数据。")).c_str());
      			close(handle); 
						return 0;					
    			}
    			else {  //新玩家数据文件可能存在，但文件打不开
          	PrintErrorMessagePage("内部错误(202)，请与巫师联系。");
      			g_applog->write(oldFileName+"可能存在，但文件打不开");
      			close(handle); //也不用备份
						return 0;					
    			}
   			}
   			//备份旧玩家数据文件
				YString srcFileName="/home/mud/data/player/"+sOldName+".profile";
				YString dstFileName="/home/mud/data/playerbak/old/"+sOldName+".profile";
   			retval=copyfile(srcFileName.c_str(),dstFileName.c_str());
   			if(retval<0) g_applog->write((YString)"备份失败"+srcFileName+"=>"+dstFileName);
   			

				//备份新玩家数据文件
				srcFileName="/home/mud/data/player/"+sNewName+".profile";
				dstFileName="/home/mud/data/playerbak/new/"+sNewName+".profile";
   			//新玩家数据文件是否存在
   			handle=open(srcFileName.c_str(),O_RDONLY,S_IREAD);
   			if(handle==-1) {
    			if(errno==ENOENT) { //新玩家数据文件不存在
      			close(handle); //不用备份
    			}
    			else {  //新玩家数据文件可能存在，但文件打不开
      			g_applog->write(srcFileName+"可能存在，但文件打不开");
      			close(handle); //也不用备份
    			}
   			}
   			else { //新玩家数据文件存在,需要备份
   				close(handle);
   				retval=copyfile(srcFileName.c_str(),dstFileName.c_str());
   				if(retval<0) g_applog->write((YString)"备份失败"+srcFileName+"=>"+dstFileName);
   			}

				//拷贝玩家数据
				srcFileName="/home/mud/data/player/"+sOldName+".profile";
				dstFileName="/home/mud/data/player/"+sNewName+".profile";
 				retval=copyfile(srcFileName.c_str(),dstFileName.c_str());
 				if(retval<0) { //拷贝失败
 					g_applog->write((YString)"备份失败："+srcFileName+"=>"+dstFileName);
          PrintErrorMessagePage("内部错误(203)，请与巫师联系。");
 				}
				else {  //拷贝成功
 					g_applog->write((YString)"备份成功："+srcFileName+"=>"+dstFileName);
          PrintMessagePage("成功移动用户数据，请点<a href=http://mud.xilu.com>这里</a>登陆。");
          //删除旧玩家文件
          int retval=unlink(srcFileName.c_str());
          if(retval<0) {
          	g_applog->write("删除失败："+srcFileName);
          }
  			}
    }
    else {  //其它Request Method
            PrintErrorMessagePage("请使用正确的方法登录系统!");
            return 0;
    }

  return 0;
}
//------------------------------------------------------------------------
bool login(YString name,YString password)
{
    char retVal=(comm39("v",name,password))[0];

    if(retVal=='#') return false;

    if(retVal=='t') return true;
    else if((retVal=='f')||(retVal=='v')) {
        g_err.ErrDescription="用户名/口令不正确，请重新登陆。";
        return false;
    }
    else {
        g_err.ErrDescription="错误，请重新登陆。";
        return false;
    }
}
//------------------------------------------------------------------------
YString comm39(const YString& command,const YString& name,
            const YString& password,const YString& others)
{
    int sockfd;
    char buf[5];
    struct hostent *he;
    struct sockaddr_in their_addr; // connector's address information
    char instr[1024];
    int err;

  #ifdef __WIN32__
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD( 2, 0 );

    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        // Tell the user that we couldn't find a usable
        // WinSock DLL.
        g_err.ErrDescription="WSA init error." ;
        return "#err";
    }
  #endif

    strcpy(instr,"GET /cgi-bin/comm39/sqlserver?command=");
    strcat(instr,command.c_str());
    strcat(instr,"&nickname=");
    strcat(instr,name.c_str());
    strcat(instr,"&passwd=");
    strcat(instr,password.c_str());
    strcat(instr,others.c_str());
    strcat(instr,"\n");

    YString comm39IP="202.108.255.106";
    if ((he=gethostbyname(comm39IP.c_str())) == NULL) {  // get the host info
        #ifdef __WIN32__
        err=WSAGetLastError();
        YErr::show("error is "+err);
        #endif
        YErr::show("[YXiluUserManager::login]gethostbyname error.");
        g_err.ErrDescription="无法连接数据库.";
        return "#err";
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        YErr::show("[YXiluUserManager::login]socket error.");
        g_err.ErrDescription="无法连接数据库.";
        return "#err";
    }

    their_addr.sin_family = AF_INET;         // host byte order
    their_addr.sin_port = htons(80);     // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    //bzero(&(their_addr.sin_zero), 8);        // zero the rest of the struct
    memset(&(their_addr.sin_zero),0, 8);
    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
        YErr::show("[YXiluUserManager::login]connect error.");
        g_err.ErrDescription="无法连接数据库.";
        close(sockfd);
        return "#err";
    }

    if(send(sockfd, instr, strlen(instr), 0) == -1) {
        YErr::show("[YXiluUserManager::login]send error.");
        g_err.ErrDescription="无法连接数据库.";
        close(sockfd);
        return "#err";
    }

    //接收数据
    int bytes;
    if ((bytes=recv(sockfd, buf, 5, 0))== -1) {
        YErr::show("[YXiluUserManager::login]recv error.");
        g_err.ErrDescription="无法连接数据库.";
        close(sockfd);
        return "#err";
    }
    buf[bytes]='\0';
    close(sockfd);
    return buf;
}
//------------------------------------------------------------------------
//名字是否合法（比如不能有空格）
int legal(YString name)
{
  if(!name.isGB2312()) return -1;
  if(name.find(" ")!=YString::npos) return -1;
  if(name.find("\t")!=YString::npos) return -1;
  return 0;
}
//-----------------------------------------------------------------------------
//UNIX下拷贝文件
int copyfile(char* srcFileName, char* dstFileName)
{
  int success;
  int from,to;
  //打开
  from=open(srcFileName,O_RDONLY);
  struct stat buf;
  fstat(from,&buf);
  to=open(dstFileName,O_WRONLY|O_CREAT|O_TRUNC,buf.st_mode);
	register int kount=0;
  #define BUFFERSIZE 10240
	char buffer[BUFFERSIZE];
  //拷贝
	while ((kount == 0) && (kount=read(from,buffer,BUFFERSIZE)) > 0)
		kount -= write (to,buffer,kount);
	success=kount ? -1 : 0;
  //设置用户ID和组ID
  fchown(to,buf.st_uid,buf.st_gid);
  //设置存取权
  fchmod(to,buf.st_mode);
  //关闭文件
  close(from);
  close(to);
  //设置文件最后修改时间
  struct utimbuf timebuf1;
  timebuf1.actime=buf.st_atime;
  timebuf1.modtime=buf.st_mtime;
  utime(dstFileName,&timebuf1);

  return success;
}
