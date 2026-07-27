//CGI输出所用到的一些例程

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writecgi.h"
using namespace std;

//--------------------------------------------------------------------
//PrintMIMEHeader--Print content-type header
void PrintMIMEHeader(void)
{
    setvbuf(stdout,NULL,_IONBF,0);
    cout<<"Content-type:text/html\n\n";
}
//--------------------------------------------------------------------
//PrintHTMLHeader--输出HTML文件头
void PrintHTMLHeader(char *sTitle)
{
    cout<<"<html>\n";
    cout<<"<head><title>"<<sTitle<<"</title></head>\n";
    cout<<"<body>\n";
}
//--------------------------------------------------------------------
//PrintHTMLTrailer--输出HTML文件结尾
void PrintHTMLTrailer(void)
{
    cout<<"</body>\n";
    cout<<"</html>\n";
}
//--------------------------------------------------------------------
//PrintErrorMessagePage--打印错误信息(HTML页)
void PrintErrorMessagePage(const char *ErrMsg)
{
    PrintMIMEHeader();
    PrintHTMLHeader("错误");

    cout<<"\n<br><br><br>";
    cout<<"<center>"<<ErrMsg<<"</center>";
    cout<<"<p><form><div align=\"center\">";
    cout<<"<input type=\"button\" value=\"返回\" onClick=\"history.go(-1)\" name=\"button\" class=\"pt9\">";
    cout<<"</form></p>";

    PrintHTMLTrailer();
}
