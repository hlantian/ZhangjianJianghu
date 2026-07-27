//---------------------------------------------------------------------------
//
// register.cpp    2002年1月23日
//
// 用于处理玩家注册的CGI
//
// 作者：叶林,刘鹏   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
//数据库结构
//+----------+-------------+------+-----+------------+-------+
//| Field    | Type        | Null | Key | Default    | Extra |
//+----------+-------------+------+-----+------------+-------+
//| name     | varchar(20) |      |     |            |       |
//| nickname | varchar(20) | YES  |     | NULL       |       |
//| passwd   | varchar(20) |      |     |            |       |
//| email    | varchar(50) |      |     |            |       |
//| ipdres   | varchar(20) |      |     |            |       |
//| firstday | date        |      |     | 0000-00-00 |       |
//| lastday  | date        |      |     | 0000-00-00 |       |
//| bakmail  | varchar(50) |      |     |            |       |
//| backpass | varchar(20) | YES  |     | NULL       |       |
//+----------+-------------+------+-----+------------+-------+

//#include<chatinet.h>
//#include
#include <mysql.h>
#include "ymudsettings.h"
#include "yerr.h"
#include "ylogfile.h"
#include "readcgi.h"
#include "writecgi.h"
#include "ystring.h"
#include <time.h>
void printform();
void error_info(char *msg);

int main(void){
	
char command[500];	


int flag=0;	
char *strtemp;
	
	char nickname[20]="";
	char passwd[20]="";		
	char passwd1[20]="";
	char sex[5]="";
	char allyear[40]="";
	char email[30]="";
	char safemail[30]="";
	char yearnow[50]="";
	char monnow[10]="";
	char daynow[10]="";
	char *tempstr="";
	char strltime[50]="";
	char myip[30]="";
	time_t atnow = time(NULL);
	struct tm *nowtime = localtime(&atnow);
//读程序
    YString sName;
    YString sPassword="";
    YString sUserIP;
    YString Srepasswd="";
    YString Semail="";
    YString Ssafemail="";
    YString Ssex="";
   
    if(iGetRequestMethod()==NO_REQUEST_METHOD) {
        cout<<"This Program is designed to run as a CGI script,\n";
        cout<<"not from the command line\n";
        return 0;
    }
    else if(iGetRequestMethod()==GET_REQUEST_METHOD) {
			PrintMIMEHeader();
			printf("test");
		
		//printform();
		return 0;
    }
    else if(iGetRequestMethod()==POST_REQUEST_METHOD) {
        GetPOSTData();
        sName=FindPOSTValue("nickname");
        sPassword=FindPOSTValue("passwd");
	Srepasswd=FindPOSTValue("repasswd");
	Semail=FindPOSTValue("email");
	Ssafemail=FindPOSTValue("safemail");
	Ssex=FindPOSTValue("sex");
        sUserIP=getenv("REMOTE_ADDR");
    }
    else {  //其它Request Method
	    printform();exit(0);
            //PrintErrorMessagePage("请使用正确的方法登录系统!");
            //return 0;
    }

//读数据结束
/*
	sprintf(yearnow ,"%d",nowtime->tm_year+1900);
	sprintf(monnow ,"%d",nowtime->tm_mon+1);
	sprintf(daynow ,"%d",nowtime->tm_mday);
	xstrcpy (allyear,yearnow,":",monnow,":",daynow,0);
*/
	if (sUserIP != "")
		strcpy(myip,sUserIP.c_str());
	

	if (sName != "")	{
		strcpy(nickname , sName.c_str());
		tempstr = nickname;
		URLDecode(tempstr);
		
		strcpy(passwd ,sPassword.c_str());
		tempstr = passwd;
		URLDecode(tempstr);
		
		strcpy(passwd1 , Srepasswd.c_str());
		tempstr = passwd1;
		URLDecode(tempstr);
		
		strcpy(email , Semail.c_str());
		tempstr = email;
		URLDecode(tempstr);
		
		strcpy(safemail ,Ssafemail.c_str());
		tempstr = safemail;
		URLDecode(tempstr);
		
		strcpy(sex ,Ssex.c_str());
		tempstr = sex;
		URLDecode(tempstr);
		
	}
	else {
		printform();
	}
	
	if (strcmp(nickname,"") == 0) error_info("代号不合法,(代号应为GB汉字、英文字母和数字, 不能超过10个字符)");
	
	if (strcmp(passwd, "") == 0) error_info("密码没有填写, 请重新注册");
	
	if (strcmp(passwd, passwd1) != 0) error_info("两次密码不一致, 请重新注册");
	
	if((strcmp(sex,"m")!=0)&&(strcmp(sex,"f")!=0)) error_info("性别必须为m或f");
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
        char sqluser[20]="root";
        char sqlpass[20]="yinglei$";
	YString tempcommand="";
	char mycommand[500]; 
	// 连结general库
	if (!(mysql_connect(&mysql,"",sqluser,sqlpass))) 
		error_info("故障: 无法连接数据库");		

	if (mysql_select_db(&mysql, "lp"))
		error_info("故障: 数据库出错1");		
	// 名字是否注册
	strcat (command , "select name from mytest where name = '");
	strcat (command ,nickname);
	strcat (command ,"'");
	if (mysql_query(&mysql,command))
//		error_info(mysql_error(&mysql));
		error_info("故障: 数据库出错2");		
	if (!(res = mysql_store_result(&mysql)))
		error_info("故障: 数据库出错3");		
	if ((row = mysql_fetch_row(res))!=NULL) error_info("该代号已存在, 请另选一个代号");
	strcpy (command ,"");
	strcat (command, "insert into mytest set name='");
	strcat (command, nickname);
	strcat (command, "',passwd=password('");
	strcat (command,passwd);
	strcat (command,"'), email='");
	strcat (command,email);
	strcat (command, "',bakmail='");
	strcat (command,safemail);
	strcat (command, "',backpass='");
	strcat (command,passwd);
	strcat (command, "',firstday=now()");
	strcat (command,",ipdres='");
	strcat (command,myip);
	strcat (command,"',sex='");
	strcat (command,sex);
	strcat (command,"'");
	if (mysql_query(&mysql,command))
		error_info(mysql_error(&mysql));
		//error_info("该代号已存在, 或操作错误");		
			
	mysql_close(&mysql);		
	PrintMIMEHeader();
        		error_info("您已经注册成功了");		
;

					
	exit(0);
}


void printform(){
	PrintMIMEHeader();

printf("<html><head><title>用户注册</title>\n");
printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\n");
printf("<style type=text/css>TD {FONT-FAMILY: 宋体; FONT-SIZE: 12px}\n");
printf("P {FONT-FAMILY: 宋体; FONT-SIZE: 12px}\n");
printf("LI {FONT-FAMILY: 宋体; FONT-SIZE: 12px}\n");
printf("A:link {COLOR: #000066; FONT-SIZE: 12px ;TEXT-DECORATION: none}\n");
printf("A:visited {COLOR: #000066; FONT-SIZE: 12px ;TEXT-DECORATION: none}\n");
printf("A:active {COLOR: #000000; FONT-SIZE: 12px; TEXT-DECORATION: underline}\n");
printf("A:hover {COLOR: #ff0000; FONT-SIZE: 12px ;TEXT-DECORATION: underline}\n");
printf("A.a:link {COLOR: #ffcc99; FONT-SIZE: 16px; TEXT-DECORATION: none}\n");
printf("A.a:visited {COLOR: #000000; FONT-SIZE: 16px ;TEXT-DECORATION: none}\n");
printf("A.a:active {FONT-SIZE: 16px; TEXT-DECORATION: none}\n");
printf("A.a:hover {COLOR: #ff0000; FONT-SIZE: 16px; TEXT-DECORATION: none}\n");
printf("</style></head>\n");
printf("<script language=\"JavaScript\">\n");
printf("function checkform(){\n");
printf("if(document.inform.nickname.value == \"\"){\n");
printf("alert(\"您没有输入代号，请输入代号\");\n");
printf("return false;\n");
printf("}\n"); 
printf("if(document.inform.passwd.value.length < 5){\n");
printf("alert(\"为了您能使用安全，请至少输入5位密码！\");\n");
printf("return false;\n");
printf("}\n");
printf("if(document.inform.passwd.value != document.inform.repasswd.value){\n");
printf("alert(\"您输入的两次密码不一致，请检查您输入的密码\");\n");
printf("return false;\n");
printf("}\n");
printf("return true;\n");
printf("}\n");
printf("</script>\n");
printf("<body bgcolor=\"#F6F6F6\">\n");
printf("<p align=\"center\"> \n");
printf("<br>\n");
printf("<table width=\"80%%\" border=\"1\" align=\"center\" bgcolor=\"#F4FFF4\" cellpadding=\"0\" cellspacing=\"0\" bordercolorlight=\"#FF9999\" bordercolordark=\"#FFFFFF\">\n");
printf("<tr>\n");
printf("<td>\n");
printf("      <div align=\"center\">----<font face=\"Wingdings\" size=\"6\" color=\"#666666\">8</font> \n");
printf("        <font color=\"#FF0000\">欢迎您注册本游戏! 请填写您的个人资料!</font> <font face=\"Wingdings\" size=\"6\" color=\"#009999\">4</font>----</div>\n");
printf("</td>\n");
printf("</tr>\n");
printf("</table><br>\n");
printf("<form name=\"inform\" action=\"register\" method=\"post\" onSubmit=\"return checkform()\">\n");
printf("  <table bgcolor=\"#E0F1FE\"\n");
printf("width=\"80%%\" align=\"center\">\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"8\" width=\"34%%\"><strong>代&nbsp;&nbsp; \n");
printf("        号</strong><strong>：</strong></td>\n");
printf("      <td valign=\"middle\" height=\"8\" width=\"18%%\" > \n");
printf("        <input  type=\"text\" name=\"nickname\" size=\"25\" maxlength=\"10\">\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" height=\"8\" width=\"48%%\" > <font color=\"#FF3333\">**</font> \n");
printf("        您在游戏的身份代号,不要超过10个字节，只能为汉字、小写字母和数字</td>\n");
printf("    </tr>\n");
printf("    <tr valign=\"middle\"> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"5\" width=\"34%%\"><strong>密 码(5-10位)</strong><strong>：</strong></td>\n");
printf("      <td height=\"5\" valign=\"middle\" width=\"18%%\"> \n");
printf("        <input type=\"password\" name=\"passwd\" value=\"\" size=\"25\" maxlength=\"10\">\n");
printf("      </td>\n");
printf("      <td height=\"5\" valign=\"middle\" width=\"48%%\"> \n");
printf("        <p> <font color=\"#FF3333\">**</font> 为了您的密码安全,最好使用字母、数字和其它字符组成</p>\n");
printf("      </td>\n");
printf("    </tr>\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"9\" width=\"34%%\"><strong>再输入一次确认：</strong></td>\n");
printf("      <td valign=\"middle\" height=\"9\" width=\"18%%\"> \n");
printf("        <input type=\"password\" name=\"repasswd\" value=\"\" size=\"25\" maxlength=\"10\">\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" height=\"9\" width=\"48%%\"> <font color=\"#FF3333\">**</font></td>\n");
printf("    </tr>\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"6\" width=\"34%%\"><strong><b>性别</b></strong><strong>：</strong></td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"18%%\"> \n");
printf("        <input type=\"text\" name=\"sex\" value=\"\" size=\"25\" maxlength=\"50\">\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"48%%\"> \n");
printf("        <p> <font color=\"#FF3333\">**</font> (m为男性,f为女性，登陆后如果性别不对，退出再次进入就可以了)</p>\n");
printf("      </td>\n");
printf("    </tr>\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"6\" width=\"34%%\"><strong><b>E-mail</b></strong><strong>：</strong></td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"18%%\"> \n");
printf("        <input type=\"text\" name=\"email\" value=\"\" size=\"25\" maxlength=\"50\">\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"48%%\"> \n");
printf("        <p> <font color=\"#FF3333\">**</font> （保密）您的联系方式。</p>\n");
printf("      </td>\n");
printf("    </tr>\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"6\" width=\"34%%\"><strong><b>密码保护mail</b>：</strong></td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"18%%\"> \n");
printf("        <input type=\"text\" name=\"safemail\" value=\"\" size=\"25\" maxlength=\"50\">\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" height=\"6\" width=\"48%%\"> \n");
printf("        <p> <font color=\"#FF3333\">**</font> (<font color=\"#FF3333\">不能修改</font>)请填写正确的email地址，通过email地址，您可以找回你的密码。</p>\n");
printf("      </td>\n");
printf("    </tr>\n");
printf("    <tr> \n");
printf("      <td valign=\"middle\" align=\"left\" height=\"41\" colspan=\"2\"> \n");
printf("        <p align=\"center\"> \n");
printf("          <input type=\"submit\" value=\" 提  交 \" name=\"submit2\">\n");
printf("          &nbsp;&nbsp; \n");
printf("          <input type=\"reset\" value=\"重新填写\" name=\"reset2\">\n");
printf("        </p>\n");
printf("      </td>\n");
printf("      <td valign=\"middle\" align=\"left\" height=\"41\">&nbsp;</td>\n");
printf("    </tr>\n");
printf("    <input type=\"hidden\" name=\"method\" value=\"\">\n");
printf("  </table>\n");
printf("<div align=\"center\"> \n");
printf("<p> <font color=\"#990033\"> </font></p>\n");
printf("  </div>\n");
printf("  <div align=\"center\"> </div>\n");
printf("</form> \n");
printf("</body> \n");
printf("</html> \n");

return;
	
}

void   error_info(char *msg)
{
	char	buffer[1024]="";
	
	PrintMIMEHeader();
	strcpy(buffer,"<script> alert('");
	strcat(buffer,msg);
	strcat(buffer,"'); history.go(-1);	</script> ");	
	printf("%s\n",buffer);
	exit(0);
}
