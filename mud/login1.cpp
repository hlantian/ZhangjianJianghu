//---------------------------------------------------------------------------
//
// login1.cpp    2000年7月21日
//
// 用于处理玩家登录的CGI
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#ifdef __WIN32__
	#include <io.h>
#endif
//#include
#include "readcgi.h"
#include "writecgi.h"
#include "ystring.h"
#ifdef __WIN32__
  #include "yfifo.h"
#else  //UNIX
  #include "yfifo_unix.h"
#endif

#include <mysql.h>
#include "ymudsettings.h"
#include "yerr.h"
#include "ylogfile.h"


YMUDSettings* g_Settings;
YString generateFIFOName(void);
void printFirstPlayHTML(void);
void printMUDHTML(YString sessionID,YString UserIP);
bool login(YString name,YString password);
char getSex(const YString& name,const YString& password);
YString comm39(const YString& command,const YString& name,
            const YString& password,const YString& others="");
bool isNewPlayer(YString name);
int legal(YString name);  //名字是否合法（比如不能有空格）

const int PORT=6038;

int main(int argc, char* argv[])
{
    umask(0);
    g_applog=new YLogFile("/home/nobody/login.log");
    g_applog->write("[main]start...");
    g_Settings=new YMUDSettings(argc, argv, "webmud.conf");
    

    YString sName;
    YString sPassword;
    YString sUserIP;

    if(iGetRequestMethod()==NO_REQUEST_METHOD) {
        cout<<"This Program is designed to run as a CGI script,\n";
        cout<<"not from the command line\n";
        return 0;
    }
    else if(iGetRequestMethod()==GET_REQUEST_METHOD) {
      PrintErrorMessagePage("请使用正确的方法登录系统!!");
      return 0;
    }
    else if(iGetRequestMethod()==POST_REQUEST_METHOD) {
        GetPOSTData();
        sName=FindPOSTValue("name");
        sPassword=FindPOSTValue("password");
        sUserIP=getenv("REMOTE_ADDR");

        if(sName=="") {
            PrintErrorMessagePage("请填写用户名。");
        }
        else { //条件符合
					#ifdef __WIN32__
	          YFIFO fifoLoginMessage(g_Settings->getLoginFIFOPathName(),"wd", 100*1024);
	          YString fifoSessionName=generateFIFOName();
	          YFIFO fifoSession(fifoSessionName,"rd", 128);
				  #else  //UNIX
	          YFIFO_UNIX fifoLoginMessage(g_Settings->getLoginFIFOPathName(),"wd", 100*1024);
	          YString fifoSessionName=generateFIFOName();
	          YFIFO_UNIX fifoSession(fifoSessionName,"rd", 128);
				  #endif
          char sex;
          if(legal(sName)<0) {
            PrintErrorMessagePage("您的用户名不合法");
            return 0;
          }
          if((sex=getSex(sName.url_encode(),sPassword.url_encode()))==0) {
            PrintErrorMessagePage(g_err.ErrDescription.c_str());
            return -1;
          }
          if(isNewPlayer(sName)) { //如果是新玩家
            printFirstPlayHTML();
            return 0;
          }
          YString loginMessage=sName+"\t"+sPassword+"\t"+fifoSession.getName()+"\t"+sex+"\t"+sUserIP;
          //g_applog->write("[main]write "+loginMessage+" to "+fifoLoginMessage.getName());
          if(fifoLoginMessage.write(loginMessage)!=0) {
             YErr::show(g_err.ErrDescription);
             PrintErrorMessagePage("[40001]内部错误。");
             return -1;
          }
          //g_applog->write("[main]read from "+fifoSession.getName());
          YString sessionID=fifoSession.read();
          //g_applog->write("[main]read from "+fifoSession.getName()+"successfully, sessionID="+sessionID);
          if(sessionID=="fail") {
            PrintErrorMessagePage("登录失败，可能是系统忙，请稍后再试。");
            return 0;
          }
          if(sessionID=="denied") {
            PrintErrorMessagePage("您被拒绝登陆.");
            return 0;
          }
          printMUDHTML(sessionID,sUserIP);
        }
    }
    else {  //其它Request Method
            PrintErrorMessagePage("请使用正确的方法登录系统!");
            return 0;
    }

  return 0;
}
//------------------------------------------------------------------------
//生成唯一的FIFO名
YString generateFIFOName(void)
{
  #ifdef __WIN32__
  randomize(); 
  #else //UNIX
  srand(time(0));
  #endif //__WIN32__
  YString name(8, 'X');
  YString pathname;
  do {
    for(int i=0; i<g_Settings->getSessionIDLength(); i++) {
      char r=rand()%62; //62=26+26+10 大小写字母、数字
      if(r<26) { //大写字母
        name[i]='A'+r;
      }
      else if((r>=26)&&(r<52)) { //小写字母
        name[i]='a'+r-26;
      }
      else { //数字
        name[i]='0'+r-52;
      }
    }
    pathname=g_Settings->getFIFOPath()+g_Settings->getPathSeparator()+name+".fifo";
    FILE* f=fopen(pathname.c_str(),"r");
    if(!f) break;
    else fclose(f);
  }while(true);
  
  return pathname;
}
//------------------------------------------------------------------------
void printMUDHTML(YString sessionID,YString UserIP)
{
  PrintMIMEHeader();

	cout<<"<html>\n";
	cout<<"<head>\n";
	cout<<"<title>仗剑江湖http://mud.senmee.com</title>\n";
	cout<<"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=GBK\">\n";
	cout<<"<style type=\"text/css\">\n";
	cout<<"<!--\n";
	cout<<".small {  font-size: 9pt}\n";
	cout<<"a:link {  font-size: 9pt; color: #FFFFFF; text-decoration: none}\n";
	cout<<"a:hover {  font-size: 9pt; text-decoration: none}\n";
	cout<<"a:active {  font-size: 9pt; text-decoration: none}\n";
	cout<<"a:visited {  text-decoration: none; color: #FFFFFF}\n";
	cout<<".middle {  font-size: 10.5pt}\n";
	cout<<".large {  font-size: 12pt}\n";
	cout<<"input {  font-size: 12px; border-style: solid; border-right-width: 1px; border-bottom-width: 1px; border-top-width: 1px; border-left-width: 1px}\n";
	cout<<".box {position: absolute; color : Black; font-size : 9pt; background-color : Silver; border-style : solid; border-width : thin;}\n";
	cout<<".qx {font-size: 9pt; color : #000000}\n";
	cout<<".cc { font: 9pt \"宋体\"; cursor: hand; color: #000000}\n";
	cout<<".cc:hover   { font: 9pt \"宋体\"; cursor: hand; color: #FF0033; background-color : #0000FF;}\n";
	cout<<".roomdes {font-size: 9pt; color: #000000;}\n";
	cout<<"-->\n";
	cout<<"</style>\n";
	cout<<"<script language=javascript src=\"/mud/menu.js\"></script>\n";
	cout<<"<script language=javascript>\n";
	cout<<"<!--\n";
	cout<<"var length=50;\n";
	cout<<"var actor;\n";
	cout<<"var wa;\n";
	cout<<"var wb;\n";
	cout<<"var wc;\n";
	cout<<"var actimg;\n";
	cout<<"var actname;\n";
	cout<<"var actNo;\n";
	cout<<"var selfname;\n";
	cout<<"var X=new Array(length);\n";
	cout<<"var Y=new Array(length);\n";
	cout<<"for(i=0; i<length; i++) {X[i]=-1;Y[i]=-1;}\n";
	cout<<"var selname=\"\";\n";
	cout<<"var DoDimWord=false;\n";
	cout<<"var infoFrameLoaded=false;\n";
	cout<<"var infoFrameInited=false;\n";
	cout<<"var showfunc;\n";
	cout<<"var dic=new Array(length);\n";
	cout<<"var anix=new Array(length);\n";
	cout<<"var aniy=new Array(length);\n";
	cout<<"var imgno=new Array(length);\n";
	cout<<"var s_move=new Array(length)\n";
	cout<<"for(i=0; i<length; i++){imgno[i]=1;s_move[i]=0;}\n";
	cout<<"var cs=new Array(20);\n";
	cout<<"var cd=new Array(\"我闪\",\"任务\",\"放弃\",\"补血\",\"精力\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\",\"★★\");\n";
	cout<<"var ctimes=new Array(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);\n";
	cout<<"var ctimesnow=new Array(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);\n";
	cout<<"for(i=0;i<cs.length;i++) {\n";
	cout<<"cs[i]=new Array();\n";
	cout<<"}\n";
	cout<<"cs[0][0]=\"我闪！\";\n";
	cout<<"cs[1][0]=\"quest\";\n";
	cout<<"cs[2][0]=\"giveup\";\n";
	cout<<"cs[3][0]=\"yun qi\";\n";
	cout<<"cs[4][0]=\"yun jing\";\n";
cout<<"var pic=new Array(110);\n";
cout<<"for(i=0;i<pic.length;i++)pic[i]=new Image(38,39);\n";
cout<<"pic[0].src=\"/mud/images/p1.gif\";\n";
cout<<"pic[1].src=\"/mud/images/p2.gif\";\n";
cout<<"pic[2].src=\"/mud/images/p3.gif\";\n";
cout<<"pic[3].src=\"/mud/images/p4.gif\";\n";
cout<<"pic[4].src=\"/mud/images/m1.gif\";\n";
cout<<"pic[5].src=\"/mud/images/m2.gif\";\n";
cout<<"pic[6].src=\"/mud/images/m3.gif\";\n";
cout<<"pic[7].src=\"/mud/images/m4.gif\";\n";
cout<<"pic[8].src=\"/mud/images/p6.gif\";\n";
cout<<"pic[9].src=\"/mud/images/m6.gif\";\n";
cout<<"pic[10].src=\"/mud/images/man1.gif\";\n";
cout<<"pic[11].src=\"/mud/images/man2.gif\";\n";
cout<<"pic[12].src=\"/mud/images/man3.gif\";\n";
cout<<"pic[13].src=\"/mud/images/man4.gif\";\n";
cout<<"pic[14].src=\"/mud/images/weman1.gif\";\n";
cout<<"pic[15].src=\"/mud/images/weman2.gif\";\n";
cout<<"pic[16].src=\"/mud/images/weman3.gif\";\n";
cout<<"pic[17].src=\"/mud/images/weman4.gif\";\n";
cout<<"pic[18].src=\"/mud/images/man5.gif\";\n";
cout<<"pic[19].src=\"/mud/images/weman5.gif\";\n";
cout<<"pic[20].src=\"/mud/images/hes1.gif\";\n";
cout<<"pic[21].src=\"/mud/images/hes2.gif\";\n";
cout<<"pic[22].src=\"/mud/images/hes3.gif\";\n";
cout<<"pic[23].src=\"/mud/images/hes4.gif\";\n";
cout<<"pic[24].src=\"/mud/images/nigu1.gif\";\n";
cout<<"pic[25].src=\"/mud/images/nigu2.gif\";\n";
cout<<"pic[26].src=\"/mud/images/nigu3.gif\";\n";
cout<<"pic[27].src=\"/mud/images/nigu4.gif\";\n";
cout<<"pic[28].src=\"/mud/images/hes5.gif\";\n";
cout<<"pic[29].src=\"/mud/images/nigu5.gif\";\n";
cout<<"pic[30].src=\"/mud/images/daoshi1.gif\";\n";
cout<<"pic[31].src=\"/mud/images/daoshi2.gif\";\n";
cout<<"pic[32].src=\"/mud/images/daoshi3.gif\";\n";
cout<<"pic[33].src=\"/mud/images/daoshi4.gif\";\n";
cout<<"pic[34].src=\"/mud/images/daog1.gif\";\n";
cout<<"pic[35].src=\"/mud/images/daog2.gif\";\n";
cout<<"pic[36].src=\"/mud/images/daog3.gif\";\n";
cout<<"pic[37].src=\"/mud/images/daog4.gif\";\n";
cout<<"pic[38].src=\"/mud/images/daoshi5.gif\";\n";
cout<<"pic[39].src=\"/mud/images/daog5.gif\";\n";
cout<<"pic[40].src=\"/mud/images/qigai1.gif\";\n";
cout<<"pic[41].src=\"/mud/images/qigai2.gif\";\n";
cout<<"pic[42].src=\"/mud/images/qigai3.gif\";\n";
cout<<"pic[43].src=\"/mud/images/qigai4.gif\";\n";
cout<<"pic[44].src=\"/mud/images/nvqigai1.gif\";\n";
cout<<"pic[45].src=\"/mud/images/nvqigai2.gif\";\n";
cout<<"pic[46].src=\"/mud/images/nvqigai3.gif\";\n";
cout<<"pic[47].src=\"/mud/images/nvqigai4.gif\";\n";
cout<<"pic[48].src=\"/mud/images/qigai5.gif\";\n";
cout<<"pic[49].src=\"/mud/images/nvqigai5.gif\";\n";
cout<<"pic[50].src=\"/mud/images/she.gif\";\n";
cout<<"pic[51].src=\"/mud/images/she.gif\";\n";
cout<<"pic[52].src=\"/mud/images/she.gif\";\n";
cout<<"pic[53].src=\"/mud/images/she.gif\";\n";
cout<<"pic[54].src=\"/mud/images/dog.gif\";\n";
cout<<"pic[55].src=\"/mud/images/dog.gif\";\n";
cout<<"pic[56].src=\"/mud/images/dog.gif\";\n";
cout<<"pic[57].src=\"/mud/images/dog.gif\";\n";
cout<<"pic[58].src=\"/mud/images/she.gif\";\n";
cout<<"pic[59].src=\"/mud/images/dog.gif\";\n";
cout<<"pic[60].src=\"/mud/images/shib1.gif\";\n";
cout<<"pic[61].src=\"/mud/images/shib2.gif\";\n";
cout<<"pic[62].src=\"/mud/images/shib3.gif\";\n";
cout<<"pic[63].src=\"/mud/images/shib4.gif\";\n";
cout<<"pic[64].src=\"/mud/images/jiangjun1.gif\";\n";
cout<<"pic[65].src=\"/mud/images/jiangjun2.gif\";\n";
cout<<"pic[66].src=\"/mud/images/jiangjun3.gif\";\n";
cout<<"pic[67].src=\"/mud/images/jiangjun4.gif\";\n";
cout<<"pic[68].src=\"/mud/images/shib5.gif\";\n";
cout<<"pic[69].src=\"/mud/images/jiangjun5.gif\";\n";
cout<<"pic[70].src=\"/mud/images/xiaobao1.gif\";\n";
cout<<"pic[71].src=\"/mud/images/xiaobao2.gif\";\n";
cout<<"pic[72].src=\"/mud/images/xiaobao3.gif\";\n";
cout<<"pic[73].src=\"/mud/images/xiaobao4.gif\";\n";
cout<<"pic[74].src=\"/mud/images/bwc1.gif\";\n";
cout<<"pic[75].src=\"/mud/images/bwc2.gif\";\n";
cout<<"pic[76].src=\"/mud/images/bwc3.gif\";\n";
cout<<"pic[77].src=\"/mud/images/bwc1.gif\";\n";
cout<<"pic[78].src=\"/mud/images/xiaobao15.gif\";\n";
cout<<"pic[79].src=\"/mud/images/bwc1.gif\";\n";
cout<<"pic[80].src=\"/mud/images/qiubai1.gif\";\n";
cout<<"pic[81].src=\"/mud/images/qiubai2.gif\";\n";
cout<<"pic[82].src=\"/mud/images/qiubai3.gif\";\n";
cout<<"pic[83].src=\"/mud/images/qiubai4.gif\";\n";
cout<<"pic[84].src=\"/mud/images/hongniang1.gif\";\n";
cout<<"pic[85].src=\"/mud/images/hongniang2.gif\";\n";
cout<<"pic[86].src=\"/mud/images/hongniang3.gif\";\n";
cout<<"pic[87].src=\"/mud/images/hongniang4.gif\";\n";
cout<<"pic[88].src=\"/mud/images/qiubai1.gif\";\n";
cout<<"pic[89].src=\"/mud/images/hongniang5.gif\";\n";
cout<<"pic[90].src=\"/mud/images/tuotou1.gif\";\n";
cout<<"pic[91].src=\"/mud/images/tuotou2.gif\";\n";
cout<<"pic[92].src=\"/mud/images/tuotou3.gif\";\n";
cout<<"pic[93].src=\"/mud/images/tuotou4.gif\";\n";
cout<<"pic[94].src=\"/mud/images/nw1.gif\";\n";
cout<<"pic[95].src=\"/mud/images/nw2.gif\";\n";
cout<<"pic[96].src=\"/mud/images/nw3.gif\";\n";
cout<<"pic[97].src=\"/mud/images/nw4.gif\";\n";
cout<<"pic[98].src=\"/mud/images/tuotou5.gif\";\n";
cout<<"pic[99].src=\"/mud/images/nw5.gif\";\n";
cout<<"pic[100].src=\"/mud/images/zg1.gif\";\n";
cout<<"pic[101].src=\"/mud/images/zg2.gif\";\n";
cout<<"pic[102].src=\"/mud/images/zg3.gif\";\n";
cout<<"pic[103].src=\"/mud/images/zg4.gif\";\n";
cout<<"pic[104].src=\"/mud/images/m1.gif\";\n";
cout<<"pic[105].src=\"/mud/images/m2.gif\";\n";
cout<<"pic[106].src=\"/mud/images/m3.gif\";\n";
cout<<"pic[107].src=\"/mud/images/m4.gif\";\n";
cout<<"pic[108].src=\"/mud/images/zg5.gif\";\n";
cout<<"pic[109].src=\"/mud/images/m6.gif\";\n";
	cout<<"var infofrminited=false;\n";
	cout<<"function init() {\n";
	cout<<"if(!infofrminited) {\n";
	cout<<"document.frames[\"ifrmmsg\"].document.write(\"<script src=\\\"http://"<<g_Settings->getServer_IP()<<"/mud/info.js\\\"></script>\\n<style type=\\\"text/css\\\">\\n<!--body{font-size: 9pt}-->\\n</style>\");\n";
	cout<<"infofrminited=true;\n";
	cout<<"showinfo(\"\");\n";
	cout<<"}\n";
	cout<<"//send_msg(\"look_b\");\n";
	cout<<"}\n";
	cout<<"function documentclick() {\n";
	cout<<"if (event.button==2) {\n";
	cout<<"s=prompt(\"请输入命令:\",\"在此键入命令\");\n";
	cout<<"if((s!=\"\") && (s!=\"在此键入命令\") && (s!=null)) send_msg(s);\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"document.onmousedown=documentclick;\n";
	cout<<"function clearsay() {\n";
	cout<<"document.frmCommand.command.value = document.frmCommand.tmpcmd.value;\n";
	cout<<"if (document.frmCommand.command.value==\"\") {\n";
	cout<<"  \n";
	cout<<"alert('你总得说点什么吧？');\n";
	cout<<"  \n";
	cout<<"return false;\n";
	cout<<"}\n";
	cout<<"showinfo(\"<font color=ff7777>\"+document.frmCommand.tmpcmd.value+\"</font><br>\");\n";
	cout<<"document.frmCommand.tmpcmd.select();\n";
	cout<<"document.frmCommand.tmpcmd.focus();\n";
	cout<<"  var message=document.frmCommand.command.value;\n";
	cout<<"  if(message.charAt(0)=='/') message=message.substr(1);\n";
	cout<<"  else if(message.charAt(0)=='\\\'') message=\"say \"+message.substr(1);\n";
	cout<<"  else {\n";
	cout<<"  for(var i=1; i<document.frmCommand.channel.options.length; i++) {\n";
	cout<<"  \n";
	cout<<"if(document.frmCommand.channel.options[i].selected) {\n";
	cout<<"  \n";
	cout<<" \n";
	cout<<"message=document.frmCommand.channel.options[i].value+\" \"+document.frmCommand.command.value;\n";
	cout<<"  \n";
	cout<<" \n";
	cout<<"break;\n";
	cout<<"  \n";
	cout<<"}\n";
	cout<<"  \n";
	cout<<"}\n";
	cout<<"  }\n";
	cout<<"  send_msg(message);\n";
	cout<<"  return false;\n";
	cout<<"}\n";
	cout<<"function sendmsg(cmd) {send_msg(cmd)}\n";
	cout<<"var javaInited=false;\n";
	cout<<"var jcmd=new Array();\n";
	cout<<"var jcmdcount=0;\n";
	cout<<"function send_msg(cmd) {\n";
	cout<<"hidemenu();\n";
	cout<<"if(!javaInited) {\n";
	cout<<"jcmd[jcmdcount]=cmd;\n";
	cout<<"jcmdcount++;\n";
	cout<<"}\n";
	cout<<"else {\n";
	cout<<"if(jcmdcount!=0) {\n";
	cout<<"for(i=0; i<jcmdcount; i++) document.mudapplet.ws(jcmd[i]);\n";
	cout<<"jcmdcount=0;\n";
	cout<<"}\n";
	cout<<"document.mudapplet.ws(cmd);\n";
	cout<<"}\n";
	cout<<"document.frmCommand.tmpcmd.focus();\n";
	cout<<"}\n";
	cout<<"function movehere() {\n";
	cout<<"hidemenu();\n";
	cout<<"x=event.clientX + document.body.scrollLeft-document.all.main.style.pixelLeft-10;\n";
	cout<<"y=event.clientY + document.body.scrollTop-document.all.main.style.pixelTop-50;\n";
	cout<<"move(selfname,x,y);\n";
	cout<<"send_msg(\"move \"+x+\" \"+y);\n";
	cout<<"}\n";
	cout<<"var actorReady=false;\n";
	cout<<"var largestActorNo=0;\n";
	cout<<"function printActor(No,name) {\n";
	cout<<"document.write(\"<div id=actor\"+No+\" style=\'position:absolute; font-size=7pt; display:none; Left:50; Top:50\'>\");\n";
	cout<<"document.write(\"<table  cellspacing=\\\"2\\\" cellpadding=\\\"2\\\" border=\\\"0\\\">\");\n";
	cout<<"document.write(\"<tr>\");\n";
	cout<<"document.write(\"    <td>\");\n";
	cout<<"document.write(\"<font class=\\\"small\\\" id=word\"+No+\"c size=\\\"-1\\\" color=\\\"00cc00\\\"></font><br>\");\n";
	cout<<"document.write(\"<font class=\\\"small\\\" id=word\"+No+\"b size=\\\"2\\\" color=\\\"009900\\\"></font><br>\");\n";
	cout<<"document.write(\"<font class=\\\"small\\\" id=word\"+No+\"a color=\\\"003300\\\"></font>\");\n";
	cout<<"document.write(\"</td>\");\n";
	cout<<"document.write(\"</tr>\");\n";
	cout<<"document.write(\"<tr>\");\n";
	cout<<"document.write(\"    <td><img onMouseOver=\\\"this.style.cursor=\'hand\';\\\" width=38 height=39\");\n";
	cout<<"document.write(\" onMouseDown=\\\"selname=document.all.name\"+No+\".innerHTML;showmenu(1);\\\" id=pic\"+No+\" src=\\\"images/p1.gif\\\"></td>\");\n";
	cout<<"document.write(\"</tr>\");\n";
	cout<<"document.write(\"<tr>\");\n";
	cout<<"document.write(\"    <td><font class=\\\"small\\\" color=black id=name\"+No+\">\"+name+\"</font></td>\");\n";
	cout<<"document.write(\"</tr>\");\n";
	cout<<"document.write(\"</table>\");\n";
	cout<<"document.write(\"</div>\");\n";
	cout<<"largestActorNo=largestActorNo>No?largestActorNo:No;\n";
	cout<<"dic[No]=name;\n";
	cout<<"}\n";
	cout<<"function selActor(name) {\n";
	cout<<"if(!actorReady){\n";
	cout<<"printActor(largestActorNo+1,name);\n";
	cout<<"largestActorNo++;\n";
	cout<<"}\n";
	cout<<"for(i=0; i<dic.length; i++) {\n";
	cout<<"if((dic[i]==name)||(i==dic.length-1)) {\n";
	cout<<"eval(\"actor=document.all.actor\"+i+\".style\");\n";
	cout<<"eval(\"wa=document.all.word\"+i+\"a\");\n";
	cout<<"eval(\"wb=document.all.word\"+i+\"b\");\n";
	cout<<"eval(\"wc=document.all.word\"+i+\"c\");\n";
	cout<<"eval(\"actimg=document.all.pic\"+i);\n";
	cout<<"eval(\"actname=document.all.name\"+i);\n";
	cout<<"actNo=i;\n";
	cout<<"break;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function addActor(name,x,y,pn) {\n";
	cout<<"for(i=0; i<dic.length-1; i++) {\n";
	cout<<"if(dic[i]==\"\") {\n";
	cout<<"dic[i]=name;\n";
	cout<<"selActor(name);\n";
	cout<<"actname.innerHTML=name;\n";
	cout<<"actor.pixelLeft=x;\n";
	cout<<"actor.pixelTop=y;\n";
	cout<<"wa.innerHTML=\"\"\n";
	cout<<"wb.innerHTML=\"\"\n";
	cout<<"wc.innerHTML=\"\"\n";
	cout<<"if(pn!=null) {actimg.src=pic[pn].src; imgno[i]=pn;}\n";
	cout<<"actor.display=\"\";\n";
	cout<<"break;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function setself(name) {\n";
	cout<<"selfname=name;\n";
	cout<<"}\n";
	cout<<"var deadname;\n";
	cout<<"function setdead(name) {\n";
	cout<<"deadname=name;\n";
	cout<<"}\n";
	cout<<"function delActor(name) {\n";
	cout<<"if(name==deadname) {deadani(name,0); return;};\n";
	cout<<"selActor(name);\n";
	cout<<"actor.display=\"none\";\n";
	cout<<"dic[actNo]=\"\";\n";
	cout<<"}\n";
	cout<<"var cleared;\n";
	cout<<"function deadani(name,times) {\n";
	cout<<"if(times==0) cleared=false;\n";
	cout<<"if(cleared) delActor(name);\n";
	cout<<"selActor(name);\n";
	cout<<"if((times%2)==0) actor.display=\"none\";\n";
	cout<<"else actor.display=\"\";\n";
	cout<<"if(times>=4) dic[actNo]=\"\";\n";
	cout<<"else setTimeout(\"deadani(\\\"\"+name+\"\\\",\"+(times+1)+\")\",300);\n";
	cout<<"}\n";
	cout<<"function clearActor() {\n";
	cout<<"deadname=\"\";\n";
	cout<<"cleared=true;\n";
	cout<<"for(i=0; i<length-1; i++) {\n";
	cout<<"if(dic[i]!=\"\") delActor(dic[i]);\n";
	cout<<"s_move[i]=0;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function move(name,x,y,t) {\n";
	cout<<"selActor(name);\n";
	cout<<"if(t==1) {\n";
	cout<<"actor.pixelLeft=x;\n";
	cout<<"actor.pixelTop=y;\n";
	cout<<"return;\n";
	cout<<"}\n";
	cout<<"X[actNo]=x;\n";
	cout<<"Y[actNo]=y;\n";
	cout<<"s_move[actNo]=1;\n";
	cout<<"moveOne(actNo);\n";
	cout<<"}\n";
	cout<<"function moveOne(No) {\n";
	cout<<"if((X[No]==-1)||(Y[No]==-1)||(!(s_move[i]))) {s_move[i]=0;return;}\n";
	cout<<"eval(\"act=document.all.actor\"+No+\".style\");\n";
	cout<<"var dx=X[No]-act.pixelLeft;\n";
	cout<<"var dy=Y[No]-act.pixelTop;\n";
	cout<<"if((dx==0)&&(dy==0)) {\n";
	cout<<"dx=-1; dy=-1;\n";
	cout<<"return;\n";
	cout<<"}\n";
	cout<<"var dxy=Math.abs(dx)-Math.abs(dy);\n";
	cout<<"var mx,my;\n";
	cout<<"if(dxy>0) {mx=(dx>0)?10:-10;my=dy/(Math.abs(dx)/10);}\n";
	cout<<"else {my=(dy>0)?10:-10;mx=dx*10/Math.abs(dy);}\n";
	cout<<"if(((mx==0)&&(dx!=0))||(Math.abs(mx)>Math.abs(dx))) mx=dx;\n";
	cout<<"if(((my==0)&&(dy!=0))||(Math.abs(my)>Math.abs(dy))) my=dy;\n";
	cout<<"act.pixelLeft+=mx;\n";
	cout<<"act.pixelTop+=my;\n";
	cout<<"setTimeout(\"moveOne(\"+No+\")\",2);\n";
	cout<<"}\n";
	cout<<"function say(name,word) {\n";
	cout<<"selActor(name);\n";
	cout<<"if(name!=\"\") {\n";
	cout<<"if(wa!=\"\") {\n";
	cout<<"if(wb!=\"\") {\n";
	cout<<"wc.innerHTML=wb.innerHTML;\n";
	cout<<"wc.style.color=wb.style.color;\n";
	cout<<"}\n";
	cout<<"wb.innerHTML=wa.innerHTML;\n";
	cout<<"wb.style.color=wa.style.color;\n";
	cout<<"} \n";
	cout<<"wa.innerHTML=word;\n";
	cout<<"wa.style.color=\"#000000\";\n";
	cout<<"showinfo(\"【<span style=\\\"color=#0000ff;text-decoration:underline;cursor:hand;\\\" onclick=actor(\\\"\"+name+\"\\\")>\"+name+\"</span>】\"+word+\"<br>\");\n";
	cout<<"DoDimWord=true;\n";
	cout<<"}\n";
	cout<<"else {\n";
	cout<<"showinfo(word+\"<br>\");\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function dimword() {\n";
	cout<<"if(DoDimWord) {\n";
	cout<<"for(var i=0; i<dic.length-1; i++) {\n";
	cout<<"if(dic[i]==\"\") continue;\n";
	cout<<"dimm(eval(\"document.all.word\"+i+\"c\"));\n";
	cout<<"dimm(eval(\"document.all.word\"+i+\"b\"));\n";
	cout<<"dimm(eval(\"document.all.word\"+i+\"a\"));\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"setTimeout(\"dimword()\",5000);\n";
	cout<<"}\n";
	cout<<"function dimm(word) {\n";
	cout<<"if(word.innerHTML==\"\") return;\n";
	cout<<"s=word.style.color;\n";
	cout<<"s1=\"#\";\n";
	cout<<"for(var i=1; i<=6; i++){\n";
	cout<<"switch(s.charAt(i)) {\n";
	cout<<"case \"0\": \n";
	cout<<"s1+=\"1\";\n";
	cout<<"break;\n";
	cout<<"case \"1\":\n";
	cout<<"s1+=\"2\";\n";
	cout<<"break;\n";
	cout<<"case \"2\":\n";
	cout<<"s1+=\"4\";\n";
	cout<<"break;\n";
	cout<<"case \"4\":\n";
	cout<<"s1+=\"8\"\n";
	cout<<"break;\n";
	cout<<"default:\n";
	cout<<"s1+=\"F\";\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"if(s1==\"#FFFFFF\") word.innerHTML=\"\";\n";
	cout<<"else word.style.color=s1;\n";
	cout<<"}\n";
	cout<<"var chedpic=true;\n";
	cout<<"function chpic(name,No) {\n";
	cout<<"if(No>=pic.length) return;\n";
	cout<<"selActor(name);\n";
	cout<<"actimg.src=pic[No].src;\n";
	cout<<"imgno[actNo]=No;\n";
	cout<<"chedpic=true;\n";
	cout<<"}\n";
	cout<<"function near(n1,n2) {\n";
	cout<<"selActor(n2);\n";
	cout<<"if(actNo>=length) return;\n";
	cout<<"var x=actor.pixelLeft;\n";
	cout<<"var y=actor.pixelTop;\n";
	cout<<"selActor(n1);\n";
	cout<<"if(actor.pixelLeft<x) {x-=35; retVal=1;}\n";
	cout<<"else {x+=35;retVal=2;}\n";
	cout<<"move(n1,x,y,1);\n";
	cout<<"return retVal;\n";
	cout<<"}\n";
	cout<<"function hit(n1,n2) {\n";
	cout<<"selActor(n1);\n";
	cout<<"if(actNo>=length) return;\n";
	cout<<"var x=actor.pixelLeft;\n";
	cout<<"var y=actor.pixelTop;\n";
	cout<<"var dir=near(n1,n2);\n";
	cout<<"var pic_no=imgno[actNo];\n";
	cout<<"if(imgno[actNo]<4) {\n";
	cout<<"if(dir==1) chpic(n1,3);\n";
	cout<<"else chpic(n1,8)\n";
	cout<<"}\n";
	cout<<"else if((imgno[actNo]>=4)&&(imgno[actNo]<=7)) {\n";
	cout<<"if(dir==1) chpic(n1,7);\n";
	cout<<"else chpic(n1,9)\n";
	cout<<"}\n";
	cout<<"chedpic=false;\n";
	cout<<"setTimeout(\"move_chpic(\\\"\"+n1+\"\\\",\"+x+\",\"+y+\",\"+pic_no+\")\",400);\n";
	cout<<"}\n";
	cout<<"function move_chpic(name,x,y,pic_no) {\n";
	cout<<"move(name,x,y,1);\n";
	cout<<"if(!chedpic) chpic(name,pic_no);\n";
	cout<<"}\n";
	cout<<"var infofrmtext=\"\";\n";
	cout<<"function showinfo(info) {\n";
	cout<<"if(infofrminited) {\n";
	cout<<"document.frames[\"ifrmmsg\"].document.write(infofrmtext+info);\n";
	cout<<"infofrmtext=\"\";\n";
	cout<<"}\n";
	cout<<"else {\n";
	cout<<"infofrmtext+=info;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function switchscroll() {\n";
	cout<<"if(!infofrminited) return;\n";
	cout<<"if(document.all.scrlbtn.innerHTML==\"8\") {\n";
	cout<<"document.frames[\"ifrmmsg\"].scrollOn();\n";
	cout<<"document.all.scrlbtn.innerHTML=\"x\";\n";
	cout<<"}\n";
	cout<<"else {\n";
	cout<<"document.frames[\"ifrmmsg\"].scrollOff();\n";
	cout<<"document.all.scrlbtn.innerHTML=\"8\";\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function showinfo2(info) {\n";
	cout<<"document.frames[\"frmoth\"].showinfo(info);\n";
	cout<<"}\n";
	cout<<"var roomfrmloaded=false;\n";
	cout<<"var roomfrmtitle=\"\";\n";
	cout<<"var roomfrmtext=\"Loading......\";\n";
	cout<<"function showroom(title,description) {\n";
	cout<<"if(roomfrmloaded) {\n";
	cout<<"document.all.roomtitle.innerHTML=title;\n";
	cout<<"showinfo(\"你来到了<font color=00ffff>\"+title+\"</font><br>\");\n";
	cout<<"document.frames[\"ifrmroom\"].showroom(description);\n";
	cout<<"//document.all.roomdescription.innerHTML=description;\n";
	cout<<"}\n";
	cout<<"else {\n";
	cout<<"roomfrmtitle=title;\n";
	cout<<"roomfrmtext=description;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"function changeall(qx,mqx,jl,mjl,nl,mnl,sw,ys,jy,qn) {\n";
	cout<<"document.frames[\"frmhp\"].changeall(qx,mqx,jl,mjl,nl,mnl,sw,ys,jy,qn);\n";
	cout<<"}\n";
	cout<<"function cbClick(No) {\n";
	cout<<"ctimesnow[No]=1;\n";
	cout<<"doScript(No,0);\n";
	cout<<"}\n";
	cout<<"function doScript(No,line) {\n";
	cout<<"if((cs[No][line]==\"#end\")||(cs[No][line]==\"\")||(cs[No][line]==null)) {\n";
	cout<<"if(ctimesnow[No]>=ctimes[No]) return;\n";
	cout<<"else {\n";
	cout<<"ctimesnow[No]++;\n";
	cout<<"doScript(No,0);\n";
	cout<<"return;\n";
	cout<<"}\n";
	cout<<"}\n";
	cout<<"send_msg(cs[No][line]);\n";
	cout<<"setTimeout(\"doScript(\"+No+\",\"+(line+1)+\")\",500);\n";
	cout<<"}\n";
	cout<<"function show_map(layerid){\n";
	cout<<"if(layerid!=\"mudmap\") hidden_map(\"mudmap\");\n";
	cout<<"if(layerid!=\"config\") hidden_map(\"config\");\n";
	cout<<"if(layerid!=\"message\") hidden_map(\"message\");\n";
	cout<<"eval(layerid+\".style.visibility='';\");\n";
	cout<<"}\n";
	cout<<"function showhp() {\n";
	cout<<"document.all.oth.style.display=\"none\";\n";
	cout<<"document.all.hp.style.display=\"\";\n";
	cout<<"}\n";
	cout<<"function showoth(cmd) {\n";
	cout<<"document.all.hp.style.display=\"none\";\n";
	cout<<"document.frames[\"frmoth\"].showinfo(\"&nbsp;&nbsp;Loading....\");\n";
	cout<<"document.all.oth.style.display=\"\";\n";
	cout<<"send_msg(cmd);\n";
	cout<<"}\n";
	cout<<"function hidden_map(layerid){\n";
	cout<<"eval(layerid+\".style.visibility='hidden';\");\n";
	cout<<"}\n";
	cout<<"function MM_findObj(n, d) { //v3.0\n";
	cout<<"  var p,i,x;  if(!d) d=document; if((p=n.indexOf(\"?\"))>0&&parent.frames.length) {\n";
	cout<<"    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}\n";
	cout<<"  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];\n";
	cout<<"  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document); return x;\n";
	cout<<"}\n";
	cout<<"//-->\n";
	cout<<"</script>\n";
	cout<<"<script language=javascript>\n";
        cout<<"<!--\n";
        cout<<"function fresh() {\n";
        cout<<"window.open(\"about:blank\",\"ifrmmsg\");\n";
        cout<<"document.frames[\"ifrmmsg\"].document.open();\n";
        cout<<"document.frames[\"ifrmmsg\"].document.close();\n";
	cout<<"document.frames[\"ifrmmsg\"].document.write(\"<script src=\\\"http://"<<g_Settings->getServer_IP()<<"/mud/info.js\\\"></script>\\n<style type=\\\"text/css\\\">\\n<!--body{font-size: 9pt}-->\\n</style>刷新成功！<br>\");\n";
        cout<<"}\n";
        cout<<"//-->\n";
        cout<<"</script>\n";
	cout<<"</head>\n";
	cout<<"<body leftmargin=\"0\" topmargin=\"0\" bgcolor=\"#2F5F90\" text=\"#FFFFFF\" onload=\"init();\">\n";
	cout<<"<script>genmenu();</script>\n";
	cout<<"<div id=\"man\" style=\"position:absolute; left:451px; top:443px; width:312px; height:96px; z-index:4\"> \n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" class=\"middle\" bordercolorlight=\"#FFFFFF\" bordercolordark=\"#306090\" background=\"/mud/images/1.gif\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td width=\"294\" height=\"18\">&nbsp;<span class=\"small\">&nbsp;\n";
	cout<<"  \n";
	cout<<"<a href=\"javascript:showhp()\"><font color=\"#FFFFFF\">体力</font></a> |  \n";
	cout<<"        <a href=\"javascript:showoth('skills_b')\"><font color=\"#FFFFFF\">技能</font></a> | \n";
	cout<<"        <a href=\"javascript:showoth('score_b')\"><font color=\"#FFFFFF\">状态</font></a> | \n";
	cout<<"<a href=\"javascript:showoth('i_b')\"><font color=\"#FFFFFF\">物品</font></a> \n";
	cout<<"        |</span></td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#989898\" height=\"85\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td height=\"80\"> \n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#E0E0E0\" bordercolorlight=\"#E8E8E8\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr> \n";
	cout<<"            <td height=\"71\" width=\"100%\">\n";
	cout<<"<div id=\"oth\" style=\"position:absolute; display:none width:299px; height:68px; z-index:7; left: 9px; top: 30px\">\n";
	cout<<"<iframe name=frmoth frameborder=0 width=100% height=100%\" src=\"/mud/other.html\"></iframe>\n";
	cout<<"</div>\n";
	cout<<"<div id=\"hp\" style=\"position:absolute; display:on; width:299px; height:68px; z-index:7; left: 9px; top: 30px\">\n";
	cout<<"<iframe name=frmhp frameborder=0 width=98% height=100% scrolling=\"no\" src=\"/mud/hp.html\"></iframe>\n";
	cout<<"</div>\n";
	cout<<"</td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  </div>\n";
	cout<<"<div id=\"main\" style=\"position:absolute; left:16px; top:45px; width:432px; height:492px; z-index:5\"> \n";
	cout<<"  <table width=\"425\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#FFFFFF\"  bordercolorlight=\"#FFFFFF\" bordercolordark=\"#336699\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td width=\"417\" class=\"middle\" background=\"/mud/images/1.gif\" height=\"17\"><span class=\"middle\">&nbsp;</span>\n";
	cout<<"        <span id=roomtitle class=\"small\">主窗口</span></td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  <table width=\"425\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#989898\">\n";
	cout<<"    <tr>\n";
	cout<<"      <td height=\"482\" width=\"678\"> \n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#E3E3E3\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr>\n";
	cout<<"            <td height=\"100\" background=\"/mud/images/bg1.gif\">\n";
	cout<<"<iframe frameborder=0 name=ifrmroom height=100 width=100% src=/mud/roomdes.html></iframe>\n";
	cout<<"</td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr valign=\"top\"> \n";
	cout<<"            <td height=\"318\" background=\"/mud/images/bg1.gif\" onClick=\"showmenu(2);\"> <br>\n";
	cout<<"<script>for(i=0;i<dic.length;i++) {printActor(i,\"\");};actorReady=true;</script>\n";
	cout<<"</td>\n";
	cout<<"          </tr>\n";
	cout<<"          <tr bgcolor=\"#666666\"> \n";
	cout<<"            <td height=\"32\" width=\"100%\"> \n";
	cout<<"              <table width=\"98%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#666666\">\n";
	cout<<"<form action=\"#\" method=\"post\" name=\"frmCommand\" onSubmit=\"return clearsay();\">\n";
	cout<<"                  <tr valign=\"middle\">\n";
	cout<<"                    <td height=\"28\" width=\"20%\" valign=\"middle\" align=\"center\"> \n";
	cout<<"                      <select name=\"channel\">\n";
	cout<<"                        <option selected>命令</option>\n";
	cout<<"                        <option value=say>说话</option>\n";
	cout<<"                        <option value=chat>公用频道</option>\n";
	cout<<"                        <option value=rumor>谣言频道</option>\n";
	cout<<"                        <option value=newbie>新手频道</option>\n";
	cout<<"                        <option value=party>门派频道</option>\n";
	cout<<"                      </select>\n";
	cout<<"                    </td>\n";
	cout<<"                    <td height=\"28\" width=\"69%\" valign=\"middle\" align=\"center\"> \n";
	cout<<"<input type=\"hidden\" name=\"sessionid\" value=\"0000000\">\n";
	cout<<"<input type=\"hidden\" name=\"command\" value=\"\">\n";
	cout<<"                      \n";
	cout<<"<input type=\"text\" name=\"tmpcmd\" size=\"40\">\n";
	cout<<"                    </td>\n";
	cout<<"                    <td colspan=\"4\" height=\"28\" width=\"11%\" align=\"left\" valign=\"bottom\"> \n";
	cout<<"                      <input type=\"image\" style=\"border-width: 0px\" name=\"image\" src=\"/mud/images/2.gif\">\n";
	cout<<"                    </td>\n";
	cout<<"                  </tr>\n";
	cout<<"                </form>\n";
	cout<<"              </table>\n";
	cout<<"            </td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"<script>dimword();</script>\n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" height=\"25\" class=\"small\" align=\"center\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\" background=\"/mud/images/bg2.gif\">\n";
	cout<<"          <tr>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb0 href=\"javascript:cbClick(0)\">[我闪]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb1 href=\"javascript:cbClick(1)\">[任务]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb2 href=\"javascript:cbClick(2)\">[放弃]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb3 href=\"javascript:cbClick(3)\">[补血]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb4 href=\"javascript:cbClick(4)\">[精力]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb5 href=\"javascript:cbClick(5)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb6 href=\"javascript:cbClick(6)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb7 href=\"javascript:cbClick(7)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb8 href=\"javascript:cbClick(8)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb9 href=\"javascript:cbClick(9)\">[★★]</a></td>\n";
	cout<<"          </tr>\n";
	cout<<"          <tr>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb10 href=\"javascript:cbClick(10)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb11 href=\"javascript:cbClick(11)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb12 href=\"javascript:cbClick(12)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb13 href=\"javascript:cbClick(13)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb14 href=\"javascript:cbClick(14)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb15 href=\"javascript:cbClick(15)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb16 href=\"javascript:cbClick(16)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb17 href=\"javascript:cbClick(17)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb18 href=\"javascript:cbClick(18)\">[★★]</a></td>\n";
	cout<<"            <td width=\"10%\"><a align=\"center\" id=cb19 href=\"javascript:cbClick(19)\">[★★]</a></td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  </div>\n";
	cout<<"<div id=\"mudmap\" style=\"position:absolute; left:451px; top:47px; width:320px; height:367px; z-index:3; visibility:hidden\"> \n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bordercolorlight=\"#FFFFFF\" bordercolordark=\"#306090\" class=\"small\" background=\"/mud/images/1.gif\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td height=\"18\" width=\"300\">&nbsp;<span class=\"small\">&nbsp;地图 | <a href=\"/mud/map/map.htm\" target=\"zmap\"><font color=\"#FFFFFF\">总图</font></a></span></td>\n";
	cout<<"      <td height=\"18\" width=\"20\" align=\"center\" onMouseOver=\"this.style.cursor='hand';\" onClick=\"hidden_map('mudmap');\"><font face=\"Wingdings\" class=\"middle\">x</font><font face=\"Webdings\"></font></td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#999999\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td height=\"365\"> \n";
	cout<<"        <table width=\"98%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#E3E3E3\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr> \n";
	cout<<"            <td height=\"342\" width=\"100%\"><iframe name=zmap width=100% height=100% src=\"/mud/map/map.htm\" ></iframe></td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"</div>\n";
	cout<<"<div id=\"config\" style=\"position:absolute; left:450px; top:47px; width:311px; height:384px; z-index:6; visibility: hidden\"> \n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bordercolorlight=\"#FFFFFF\" bordercolordark=\"#306090\" class=\"small\" background=\"/mud/images/1.gif\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td width=\"295\" height=\"18\">&nbsp;<span class=\"small\">&nbsp;设置快捷按钮</span></td>\n";
	cout<<"      <td width=\"19\"  onMouseOver=\"this.style.cursor='hand';\" onClick=\"hidden_map('config');\" height=\"18\"> \n";
	cout<<"        <div align=\"center\"><font face=\"Wingdings\" class=\"middle\">x</font></div>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#999999\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td height=\"363\"> \n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#E3E3E3\" height=\"300\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr> \n";
	cout<<"            <td height=\"349\" width=\"100%\">\n";
	cout<<"<iframe name=messages src=\"/mud/config.html\" width=100% height=100%></iframe></td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"</div>\n";
	cout<<"<div id=\"message\" style=\"position:absolute; left:450px; top:46px; width:311px; height:370px; z-index:1\"> \n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bordercolorlight=\"#FFFFFF\" bordercolordark=\"#306090\" class=\"small\" background=\"/mud/images/1.gif\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td width=\"235\" height=\"18\">&nbsp;<span class=\"small\">&nbsp;信息窗口</span></td>\n";
	cout<<"      <td width=\"40\" height=\"18\">&nbsp;<span class=\"small\">&nbsp;<a href=\"#\" onclick=\"fresh();\">刷新</a></span></td>\n";
	cout<<"      <td width=\"20\" onMouseOver=\"this.style.cursor='hand';\" onClick=\"switchscroll();\" height=\"18\"> \n";
	cout<<"        <div align=\"center\"><font id=scrlbtn face=\"Webdings\" size=1>x</font></div>\n";
	cout<<"      </td>\n";
	cout<<"      <td width=\"20\"  onMouseOver=\"this.style.cursor='hand';\" onClick=\"hidden_map('message');\" height=\"18\"> \n";
	cout<<"        <div align=\"center\"><font face=\"Wingdings\" class=\"middle\">x</font></div>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"  <table width=\"315\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#999999\">\n";
	cout<<"    <tr> \n";
	cout<<"      <td height=\"365\"> \n";
	cout<<"        <table width=\"97%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#E3E3E3\" height=\"300\" bordercolorlight=\"#E0E0E0\" bordercolordark=\"#000000\">\n";
	cout<<"          <tr> \n";
	cout<<"            <td height=\"352\" width=\"100%\">\n";
	cout<<"<iframe name=ifrmmsg src=\"about:blank\" width=100% height=100%  style=\"font-size=9pt\" onLoad=\"infoFrameLoaded=true;\"></iframe>\n";
	cout<<"</td>\n";
	cout<<"          </tr>\n";
	cout<<"        </table>\n";
	cout<<"      </td>\n";
	cout<<"    </tr>\n";
	cout<<"  </table>\n";
	cout<<"</div>\n";
	cout<<"<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#0F3F80\">\n";
	cout<<"  <tr> \n";
	cout<<"    \n";
	cout<<"    <td height=\"40\" width=\"0%\">&nbsp;</td>\n";
	cout<<"    \n";
	cout<<"    <td height=\"40\" width=\"27%\"> \n";
	cout<<"      <div align=\"center\"><img src=\"/mud/images/13.gif\" width=\"192\" height=\"35\"></div>\n";
	cout<<"    </td>\n";
	cout<<"    \n";
	cout<<"    <td height=\"40\" width=\"73%\"> \n";
	cout<<"      <table width=\"80%\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"#2F2F2F\" class=\"small\" bordercolor=\"#606060\" height=\"15\">\n";
	cout<<"        <tr> \n";
	cout<<"          <td width=\"20%\" height=\"15\"> \n";
	cout<<"            <div align=\"center\"><font class=\"middle\" face=\"Webdings\" color=\"#FF9900\">2</font><a href=\"javascript:show_map('mudmap')\">地图窗口</a></div>\n";
	cout<<"          </td>\n";
	cout<<"          <td width=\"20%\" height=\"15\"> \n";
	cout<<"            <div align=\"center\"><font class=\"middle\" face=\"Webdings\" color=\"#FF9900\">2</font><a href=\"javascript:show_map('config')\">按钮设置</a></div>\n";
	cout<<"          </td>\n";
	cout<<"          <td width=\"20%\" height=\"15\"> \n";
	cout<<"            <div align=\"center\"><font class=\"middle\" face=\"Webdings\" color=\"#FF9900\">2</font><a href=\"javascript:show_map('message')\">信息窗口</a></div>\n";
	cout<<"          </td>\n";
	cout<<"          <td width=\"20%\" height=\"15\"> \n";
	cout<<"            <div align=\"center\"><font class=\"middle\" face=\"Webdings\" color=\"#FF9900\">s</font><a href=\"/mud/help.htm\" target=\"_blank\">帮助信息</a></div>\n";
	cout<<"          </td>\n";
	cout<<"          <td width=\"20%\" height=\"15\"> \n";
	cout<<"            <div align=\"center\"><font class=\"middle\" face=\"Webdings\" color=\"#FF9900\">8</font><a href=\"javascript:send_msg('quit')\">退出游戏</a></div>\n";
	cout<<"          </td>\n";
	cout<<"        </tr>\n";
	cout<<"      </table>\n";
	cout<<"    </td>\n";
	cout<<"  </tr>\n";
	cout<<"</table>\n";
	cout<<"<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" height=\"66%\" align=\"center\" bgcolor=\"#2F5F90\">\n";
	cout<<"  <tr> \n";
	cout<<"    <td height=\"515\" width=\"1%\" valign=\"top\">&nbsp; </td>\n";
	cout<<"    <td height=\"515\" width=\"98%\" valign=\"top\">&nbsp;</td>\n";
	cout<<"    <td height=\"515\" width=\"1%\" valign=\"top\">&nbsp;</td>\n";
	cout<<"  </tr>\n";
	cout<<"</table>\n";
	cout<<"<APPLET codebase=\"/mud\" CODE=mud121 name=mudapplet width=1 height=1 MAYSCRIPT>\n";
	cout<<"<PARAM name=host value=\""<<g_Settings->getServer_IP()<<"\">\n";
	cout<<"<PARAM name=sessionID value=\""<<sessionID<<"\">\n";
	cout<<"</APPLET>\n";
	cout<<"</body>\n";
	cout<<"</html>\n";
}
//------------------------------------------------------------------------
void printFirstPlayHTML(void)
{
  //暂时未实现
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
char getSex(const YString& name,const YString& password)
{
    //return 'm';
    YString retVal=comm39("g",name,password,"&sex");

    if(retVal=="#err") return false;

    if(retVal[0]=='m')   return 'm';
    else return 'f';
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

	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
        char sqluser[20]="root";
        char sqlpass[20]="yinglei$";
	YString tempcommand="";
	char mycommand[500]; 


	if (!(mysql_connect(&mysql,"",sqluser,sqlpass)))
	{ 
		g_err.ErrDescription="故障: 无法连接数据库";		
		return "#err";
	}
	if (mysql_select_db(&mysql, "lp"))
	{
		g_err.ErrDescription="故障: 数据库出错1";		
		return "#err";
	}
	char tempname[50];
	strncpy(tempname,name.c_str(),49);
	tempname[49]='\0';
	URLDecode(tempname);
	YString nametemp=tempname;
	tempcommand ="select name from mytest where name = '"+nametemp+"'";
	strcpy(mycommand,tempcommand.c_str());
	if (mysql_query(&mysql,mycommand))
//		error_info(mysql_error(&mysql));

	{
		g_err.ErrDescription="故障: 数据库出错2";		
		return "#err";
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		g_err.ErrDescription="故障: 数据库出错3";		
		return "#err";
	}
	if ((row = mysql_fetch_row(res) )==NULL )
	{	
	    g_err.ErrDescription="请输入正确的密码！！";
	    mysql_close(&mysql);
	    return "#err";

	}
	tempcommand = "select name,sex,passwd from mytest where name = '"+nametemp+"' AND passwd = password('"+password+"')";
	strcpy(mycommand,tempcommand.c_str());
	if (mysql_query(&mysql,mycommand))
	{
//		error_info(mysql_error(&mysql));
		g_err.ErrDescription="故障: 数据库出错2";		
		return "#err";
	}

	if (!(res = mysql_store_result(&mysql)))
	{
		g_err.ErrDescription="故障: 数据库出错3";		
		return "#err";
	}

	if ((row = mysql_fetch_row(res)) ==NULL) g_err.ErrDescription="请不要盗用别人的密码.";
	else 
	{
	  //if (row[1] != "")playername=row[1];
	  //if (row[0] != NULL) name=row[0];
	  //if (row[2] != NULL) password=row[2];
	  mysql_close(&mysql);
	  return row[1];
	}
	mysql_close(&mysql);
	return "#err";
}
//------------------------------------------------------------------------
//是否是MUD新玩家
bool isNewPlayer(YString name)
{
   return false;   //暂时不开放功能
   YString datafilename=g_Settings->getPlayerPath()+g_Settings->getPathSeparator()+name;
   YString realdatafilename=g_Settings->getRootPath()+g_Settings->getPathSeparator()
                     +PATH(datafilename)+".profile";
   int handle=open(realdatafilename.c_str(),O_RDONLY,S_IREAD);
   if(handle==-1) {
    if(errno==ENOENT) {
      close(handle);
      return true;
    }
    else {
      close(handle);
      return false;
    }
   }
   close(handle);
   return false;
}
//------------------------------------------------------------------------
//名字是否合法（比如不能有空格）
int legal(YString name)
{
  if(!name.isGB2312()) return -1;
  if(name.find(" ")!=YString::npos) return -1;
  if(name.find("\t")!=YString::npos) return -1;
  return 0; //很好
}
