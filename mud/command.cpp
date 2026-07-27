//---------------------------------------------------------------------------
//
// command.cpp    2000年7月21日
//
// 用于处理玩家命令的CGI
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#include <iostream.h>
#ifdef __WIN32__
  #include <io.h>
#else //UNIX
  #include <sys/types.h>
  #include <sys/stat.h>
#endif
#include "readcgi.h"
#include "writecgi.h"
#include "ystring.h"
#include "yfifo.h"
#include "ymudsettings.h"
#include "yerr.h"
#include "ylogfile.h"

YMUDSettings g_Settings;
YString generateFIFOName(void);
void printFirstPlayHTML(void);
void printMUDHTML(YString sessionID);

int main(int argc, char* argv[])
{
    umask(0);
    g_applog=new YLogFile("/home/nobody/command.log");

    g_Settings.load(argc, argv, "webmud.conf");

    if(iGetRequestMethod()==NO_REQUEST_METHOD) {
        cout<<"This Program is designed to run as a CGI script,";
        cout<<"not from the command line";
    }
    else if(iGetRequestMethod()==GET_REQUEST_METHOD) {
            PrintErrorMessagePage("请使用正确的方法登录系统!");
    }
    else if(iGetRequestMethod()==POST_REQUEST_METHOD) {
        GetPOSTData();
        YString sSessionID=FindPOSTValue("sessionid");
        YString sCommand=FindPOSTValue("command");
        YString sChannel=FindPOSTValue("channel");
        if(sCommand[0]=='/') sCommand.erase(0,1);  //命令
        else if(sCommand[0]=='\'') { //说话
          sCommand.erase(0,1);
          sCommand="say "+sCommand;
        }
        else if(sChannel=="说话") sCommand="say "+sCommand;
        else if(sChannel=="命令") ; //do nothing
        else if(sChannel=="公用频道") sCommand="chat "+sCommand;
        else if(sChannel=="谣言频道") sCommand="rumor "+sCommand;
        else if(sChannel=="新手频道") sCommand="newbie "+sCommand;

        if(sSessionID=="") {
            PrintErrorMessagePage("请使用正确的方法登录系统!");
        }
        else { //条件符合
          YFIFO fifoCommandMessage(g_Settings.getCommandFIFOPathName(),"wd", 100*1024);
          YString commandMessage=sSessionID+sCommand;
          //g_applog->write("[main]write "+commandMessage+" to "+fifoCommandMessage.getName());
          if(fifoCommandMessage.write(commandMessage)!=0) {
             //g_applog->write("[main]write "+commandMessage+" to "+fifoCommandMessage.getName()+" Failed.");
             PrintErrorMessagePage(g_err.ErrDescription.c_str());
             return -1;
          }
          //g_applog->write("[main]write "+commandMessage+" to "+fifoCommandMessage.getName()+" OK.");
          PrintErrorMessagePage("ok");
        }
    }
    else {  //其它Request Method
        PrintErrorMessagePage("请使用正确的方法登录系统!");
    }
  return 0;
}

