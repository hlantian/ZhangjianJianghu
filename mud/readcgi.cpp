//Read CGI
//分析CGI输入的一些例程

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#ifdef __WIN32__ 
  #include <windows.h> 
  #include <io.h> 
#else //UNIX 
//  #include <unistd.h> 
#endif //__WIN32__ 
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "readcgi.h"
using namespace std;

char InputBuffer[1024];
unsigned char *BinBuffer;
long sizeofBinBuffer;
const long MAX_BIN_BUFFER_SIZE=2000000;
vector<YVarValPair> AllVarValPairs;

//--------------------------------------------------------------------
//iGetRequestMethod--取得请求方法类型
int iGetRequestMethod(void)
{
    char *pRequestMethod;
    pRequestMethod=getenv("REQUEST_METHOD");
    if(pRequestMethod==NULL) return NO_REQUEST_METHOD;
    /*FILE *fp;
    fp=fopen("/etc/readcgi.log","rw");
    fprintf(fp,"pRequestMethod=%s\n",pRequestMethod);
    fclose(fp); */
    yelin::strupr(pRequestMethod);
/*
    fp=fopen("/etc/readcgi.log","rw+");
    fprintf(fp,"pRequestMethod=%s\n",pRequestMethod);
    fclose(fp);
*/    
    if(strcmp(pRequestMethod,"POST")==0) return POST_REQUEST_METHOD;
    else return OTHER_REQUEST_METHOD;
}
//--------------------------------------------------------------------
//SwapChar--将字符串pOriginal中所有的字符cBad换为cGood
void SwapChar(char *pOriginal, char cBad, char cGood)
{
    int i=0;
    while(pOriginal[i]) {
        if(pOriginal[i]==cBad) pOriginal[i]=cGood;
        i++;
    }
}
//--------------------------------------------------------------------
//IntFromHex--返回字符串前两个字符所代表的16进制数
int IntFromHex(char *pChars)
{
    //将第一个字节送入Hi
    int Hi=pChars[0];
    if('0'<=Hi && Hi<='9') {
        Hi-='0';
    }
    else if('a'<=Hi && Hi<='f') {
        Hi-=('a'-10);
    }
    else if('A'<=Hi && Hi<='F') {
        Hi-=('A'-10);
    }

    //将第二个字节送入Lo
    int Lo=pChars[1];
    if('0'<=Lo && Lo<='9') {
        Lo-='0';
    }
    else if('a'<=Lo && Lo<='f') {
        Lo-=('a'-10);
    }
    else if('A'<=Lo && Lo<='F') {
        Lo-=('A'-10);
    }

    //返回16进制数
    return Lo+(16*Hi);
}
//--------------------------------------------------------------------
//URLDecode--对输入字符串pEncoded进行解码,'+'号换为空格,%xx格式的恢复
void URLDecode(char *pEncoded)
{
    char *pDecoded;
    SwapChar(pEncoded,'+',' '); //将加号换为空格

    //处理换码
    pDecoded=pEncoded;
    while(*pDecoded) {
        if(*pEncoded=='%') {
            //百分号'%'后面跟两位16进制字符,须解码
            pEncoded++;
            if(isxdigit(pEncoded[0]) && isxdigit(pEncoded[1])) {
                *pDecoded++=(char)IntFromHex(pEncoded);
                pEncoded+=2;
            }
        }
        else {
            *pDecoded++=*pEncoded++;
        }
    }
    *pDecoded='\0';
}
//--------------------------------------------------------------------
//GetPOSTData--读PSOT方式的数据
void GetPOSTData(void)
{
    //判断是否multipart/form-data
    char *pContentType=getenv("CONTENT_TYPE");
    yelin::strlwr(pContentType);
    if(strncmp(pContentType,"multipart/form-data",19)==0) {
        GetPOSTMultipartData();
        return;
    }

    char *pContentLength=getenv("CONTENT_LENGTH");
    long lContentLength;
    if(pContentLength!=NULL) {
        lContentLength=atol(pContentLength);
    }
    else lContentLength=0;

    //输入长度不得大于缓冲区
    if(lContentLength>sizeof(InputBuffer)-1) {
        lContentLength=sizeof(InputBuffer)-1;
    }
    //从标准输入读入
    long l=0;
    while(l<lContentLength) {
        int x=fgetc(stdin);
        if(x==EOF) break;
        InputBuffer[l++]=x;
    }
    InputBuffer[l]='\0'; //加终止字符

    lContentLength=l;  //更新ContengLength(废语句?)
    LoadPOSTData();
}
//--------------------------------------------------------------------
//PrintVars--打印所有的环境变量(可用于测试)
void PrintVars(void)
{
    cout<<"<b>环境变量:</b>\n";
    #ifdef __WIN32__
    cout<<"<ul>\n";

    //解码并打印所有环境变量
    int i=0;
    while(_environ[i]) {
        strcpy(InputBuffer,_environ[i]);
        URLDecode(InputBuffer);
        cout<<"<li>"<<InputBuffer<<"\n";
        i++;
    }
    cout<<"</ul>\n";
    #else //UNIX
    cout<<"UNIX 下暂时无法工作.<br>\n";
    #endif
}
//--------------------------------------------------------------------
//LoadVarValPair--将Var=Value对装入AllVarValPairs中
void LoadVarValPair(char *VarVal)
{
    char *pEquals=strchr(VarVal,'='); //找等号
    if(pEquals!=NULL) {
        *pEquals++='\0';
        URLDecode(VarVal);  //解码变量名
        URLDecode(pEquals); //解码变量值
        //装入Var=Value对
        YVarValPair pair;
        pair.Var=VarVal;
        pair.Val=pEquals;
        AllVarValPairs.insert(AllVarValPairs.begin(),pair);
    }
}
//--------------------------------------------------------------------
//LoadPOSTData--将输入缓冲区中POST数据装入AllVarValPairs中
void LoadPOSTData(void)
{
    //装入所有变量
    char *pToken=strtok(InputBuffer,"&");
    while(pToken!=NULL) {
        LoadVarValPair(pToken);
        pToken=strtok(NULL,"&");
    }
}
//--------------------------------------------------------------------
//PrintPOSTData--打印所有POST数据Var=Value对(可用于测试)
void PrintPOSTData(void)
{
    cout<<"<b>POST DATA:</b>\n";
    cout<<"<ul>\n";

    //打印所有变量
    for(int i=0; i<AllVarValPairs.size(); i++) {
        cout<<"<li>"<<AllVarValPairs[i].Var<<"="<<AllVarValPairs[i].Val;
    }
    cout<<"</ul>\n";
}
//--------------------------------------------------------------------
//FindPOSTValue--读取变量名对应的值
char* FindPOSTValue(char *sVarName)
{
    for(int i=0; i<AllVarValPairs.size(); i++) {
        if(strcmp(AllVarValPairs[i].Var,sVarName)==0) {
            return AllVarValPairs[i].Val;
        }
    }
    return "";   //以后应改为返回NULL
}
//--------------------------------------------------------------------
//GetPOSTMultipartData--读POST multipart/form-data方式的数据
void GetPOSTMultipartData(void)
{
    char *pContentLength=getenv("CONTENT_LENGTH");
    long lContentLength;
    if(pContentLength!=NULL) {
        lContentLength=atol(pContentLength);
    }
    else lContentLength=0;

    //输入长度不得大于缓冲区限制
    if(lContentLength>MAX_BIN_BUFFER_SIZE) {
        lContentLength=MAX_BIN_BUFFER_SIZE;
    }
    sizeofBinBuffer=lContentLength;

    //申请内存
    BinBuffer=(unsigned char*)new char[lContentLength];

    //更改标准输入属性
    #ifdef __WIN32__
    setmode(fileno(stdin),O_BINARY);
    #else
    #endif //__WIN32__
    setvbuf(stdout,NULL,_IONBF,0);

    //从标准输入读入
    long l=0;
    while(l<lContentLength) {
        int x=fgetc(stdin);
        BinBuffer[l++]=x;
    }

    LoadPOSTMultipartData();

    delete[] BinBuffer;
}
//--------------------------------------------------------------------
//LoadPOSTMultipartData--将BinBuffer缓冲区中POST数据装入AllVarValPairs中
void LoadPOSTMultipartData(void)
{
    //确定分割串
    char *sContentType=getenv("CONTENT_TYPE");
    char *sBoundary=strstr(sContentType,"boundary")+9;

    char *pCurrent=(char*)BinBuffer;
    char *pEnd;
    while((pCurrent=(char*)memchr(pCurrent,*sBoundary,sizeofBinBuffer))!=NULL) {
        if(strncmp(pCurrent,sBoundary,strlen(sBoundary))!=0) {
                    //不是边界分割串
            pCurrent++;
            continue;
        }

        //查找name=xxxxx;对
        if((pCurrent=strstr(pCurrent,"name="))==NULL) break;
        pCurrent+=6;   //"name=\""
        pEnd=strchr(pCurrent,'\"');  //右边的双引号
        *pEnd='\0';
        char *sName=(char*) new char[strlen(pCurrent)+1];
        strcpy(sName,pCurrent);
        pCurrent=pEnd+3;   //"\"; " or "\"\x0a\x0d"

        if(strncmp(pCurrent,"filename=",9)==0) { //如果为File Field
            //装入文件名
            pCurrent+=10;  // "filename=\""
            pEnd=strchr(pCurrent,'\"');
            *pEnd='\0';
            char *sClientFileName=(char*) new char[strlen(pCurrent)+1];
            strcpy(sClientFileName,pCurrent);
            //装入Var=Value对:FileField名称=文件名(FileField中填的内容)
            addVarValPair(sName,sClientFileName);

            //分离出文件
            //记录文件类型
            pCurrent=pEnd+3; //越过"\"\x0d\x0a"
            if(strncmp(pCurrent,"Content-Type",12)!=0) {
                //cout<<"jjjjjjjjjjjjjj";
                continue;
            }
            pCurrent+=14; //"Content-Type: "
            pEnd=strchr(pCurrent,'\x0d');
            *pEnd='\0';
            char *sFileContentType=(char *)new char[strlen(pCurrent)+1];
            strcpy(sFileContentType,pCurrent);
            char *sNameOfContentType=(char *)new char[strlen(sName)+14];
            strcpy(sNameOfContentType,sName);
            strcat(sNameOfContentType,"-ContentType");
            //记录文件的类型
            addVarValPair(sNameOfContentType,sFileContentType);
            //确定文件的开始和结尾
            pCurrent=pEnd+4; //两个"\x0d\x0a"
            do {  //查找下一个分割串
                pEnd=(char*)memchr(pEnd,*sBoundary,sizeofBinBuffer);
                if(strncmp(pEnd,sBoundary,strlen(sBoundary))!=0) {
                                            //不是边界分割串
                    pEnd++;
                    continue;
                }
                else break;
            }while(1);
            pEnd-=4; //让回"\x0d\x0a--",得到文件尾
            //确定写入文件名
            char *sTempFileName=(char *)new char[1024];
            #ifdef __WIN32__
              randomize(); 
            #else //UNIX
              srand(time(0));
            #endif //__WIN32__
            do {
                sprintf(sTempFileName,"%s\\%08ld.UPL",getenv("TEMP"),rand()%100000000L);
                FILE* f=fopen(sTempFileName,"r");
                if(!f) break;
                else fclose(f);
            }while(true);
            //文件写入磁盘
            FILE *tmpFile=fopen(sTempFileName,"wb");
            if(tmpFile) {
                fwrite(pCurrent,pEnd-pCurrent,1,tmpFile);
                fclose(tmpFile);
            }
            //记录写入文件长度
            char *sLengthOfTempFile=(char *)new char[strlen(sName)+13];
            strcpy(sLengthOfTempFile,sName);
            strcat(sLengthOfTempFile,"-FileLength");
            char *sLength=new char[11];
            sprintf(sLength,"%d",pEnd-pCurrent);
            addVarValPair(sLengthOfTempFile,sLength);

            //记录写入文件名
            char *sNameOfTempFile=(char *)new char[strlen(sName)+11];
            strcpy(sNameOfTempFile,sName);
            strcat(sNameOfTempFile,"-TempFile");
            addVarValPair(sNameOfTempFile,sTempFileName);

            pCurrent=pEnd+2;
        }
        else {  //不是File Field
            pCurrent+=2; //再越过一对"\x0d\x0a"
            pEnd=strchr(pCurrent,'\x0d');
            *pEnd='\0';
            char *sValue=(char *)new char[strlen(pCurrent)+1];
            strcpy(sValue,pCurrent);
            addVarValPair(sName,sValue);

            pCurrent=pEnd+2;
        }
    }//endwhile--查找分隔串
}
//--------------------------------------------------------------------
//addVarValPair--将一对Var=Value添加到AllVarValPairs中
void addVarValPair(char *sVar,char *sValue)
{
    YVarValPair *pair=(YVarValPair *)new YVarValPair;
    pair->Var=sVar;
    pair->Val=sValue;
    AllVarValPairs.insert(AllVarValPairs.begin(),*pair);
}
//--------------------------------------------------------------------
//strtrim--删除字符串末尾的空白符,字符串将被改变
char* strtrim(char *s)
{
    for(char *p=s+strlen(s)-1; p>=s; p--) {
        if((*p==' ')||(*p=='\t')||(*p=='\n')||(*p=='\r')) {
            *p='\0';
        }
        else break;
    }
    return s;
}
//-------------------------------------------------------------------- 
//strupr--将字符串中的所有字母转换为大写
char* yelin::strupr(char *s)
{
  for(int i=0; i<strlen(s); i++) {
    s[i]=toupper(s[i]);
  }
  return s;
}
//--------------------------------------------------------------------
//strupr--将字符串中的所有字母转换为小写
char* yelin::strlwr(char *s)
{
  for(int i=0; i<strlen(s); i++) {
    s[i]=tolower(s[i]);
  }
  return s;
}

