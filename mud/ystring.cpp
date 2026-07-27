//---------------------------------------------------------------------------
//
// ystring.cpp   2000年6月8日
//
// 类YSring：提供字符串的封装，解决C中字符串的繁琐操作及容易产生越界的问题
//          改为使用C++中的标准string, 但增加一YString层，以便于添加功能
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include <stdio.h>
#include <ctype.h>
#include "ystring.h"

//---------------------------------------------------------------------------
YString::YString(const long l)
{
  char s[33];
  sprintf(s,"%ld",l);
  assign(s);
}
//---------------------------------------------------------------------------
YString::YString(const short i)
{
  char s[33];
  sprintf(s,"%d",i);
  assign(s);
}
//---------------------------------------------------------------------------
YString::YString(const int i)
{
  char s[33];
  sprintf(s,"%d",i);
  assign(s);
}
//---------------------------------------------------------------------------
YString::YString(const float f)
{
  char s[33];
  sprintf(s,"%f",f);
  assign(s);
}
//---------------------------------------------------------------------------
YString::YString(const double f)
{
  char s[33];
  sprintf(s,"%f",f);
  assign(s);
}
//-------------------------------------------------------------
//取第一个单词（字符串将被改变）
YString YString::getWord(YString delim)
{
  int pos=find(delim);
  YString retS(*this,0,pos);
  if(pos!=npos) erase(0,pos+1);
  else assign("");
  while(retS==delim) retS=getWord(delim);
  return retS;
}
//-------------------------------------------------------------
//转换成HTML格式，比如'\n'转换成<BR>
YString YString::HTMLFormat(void)
{
  YString html(*this);
  int pos=0;
  while((pos=html.find("\n",pos))!=npos) {
    html.insert(pos,"<br>");
    pos+=5;
  }
  return html;
}
//-------------------------------------------------------------
//将"转换成\",用于写程序中的字符串
YString YString::toInnerString(void)
{
  YString retS(*this);
  int pos=0;
  while((pos=retS.find("\\",pos))!=npos) {
    retS.insert(pos,"\\");
    pos+=2;
  }
  pos=0;
  while((pos=retS.find("\"",pos))!=npos) {
    retS.insert(pos,"\\");
    pos+=2;
  }
  pos=0;
  while((pos=retS.find("\'",pos))!=npos) {
    retS.insert(pos,"\\");
    pos+=2;
  }
  pos=0;
  while((pos=retS.find("\n",pos))!=npos) {
    retS.erase(pos,1);
  }
  while((pos=retS.find("\r",pos))!=npos) { 
    retS.erase(pos,1); 
  } 
  return retS;
}
//-------------------------------------------------------------
//转换成长整型变量
long YString::toLong(void)
{
  return atol(c_str());
}
//-------------------------------------------------------------
//转换成双精度变量
double YString::toDouble(void)
{
  return atof(c_str());
}
//-------------------------------------------------------------
//删除前后空白
void trim(char* s)
{
  char *head=s;
  char *tail=s+strlen(s);
  for(int i=0; i<strlen(s); i++) {
    if(!isspace(*head)) break;
    head++;
  }
  char *p=s;
  for(head; head<tail; head++) {
    *p=*head;
    p++;
  }
  *p='\0';
  p--;
  for(p; p>=s; p--) {
    if(isspace(*p)) *p='\0';
    else break;
  }
}
//--------------------------------------------------------
//阿拉伯数字转换为汉字数字
YString LongToChinese(long i)
{
  YString c_digit[]={"零","十","百","千","万","亿","兆"};
  YString c_num[]={"零","一","二","三","四","五","六","七","八","九","十"};
  if(i<0)
    return "负"+LongToChinese(-i);
  if(i<11)
    return c_num[i];
  if(i<20)
    return c_digit[1]+c_num[i-10];
  if(i<100){
    if(i%10)
      return c_num[i/10]+c_digit[1]+c_num[i%10];
    else
      return c_num[i/10]+c_digit[1];
  }
  if(i<1000){
    if(i%100==0)
      return c_num[i/100]+c_digit[2];
    else if(i%100<10)
      return c_num[i/100]+c_digit[2]+c_num[0]+LongToChinese(i%100);
    else if(i%100<10)
           return c_num[i/100]+c_digit[2]+c_num[1]+LongToChinese(i%100);
         else
	   return c_num[i/100]+c_digit[2]+LongToChinese(i%100);
   }
   if(i<10000){
     if(i%1000==0)
       return c_num[i/1000]+c_digit[3];
     else if(i%1000<100)
       return c_num[i/1000]+c_digit[3]+c_num[0]+LongToChinese(i%1000);
     else
       return c_num[i/1000]+c_digit[3]+LongToChinese(i%1000);
   }
   if(i<100000000){
     if(i%10000==0)
       return LongToChinese(i/10000)+c_digit[4];
     else if(i%10000<1000)
       return LongToChinese(i/10000)+c_digit[4]+c_num[0]+LongToChinese(i%10000);
     else
       return LongToChinese(i/10000)+c_digit[4]+LongToChinese(i%10000);
   }
}
//-------------------------------------------------------------
//从一个字符串中查找另一个字符串
bool YString::findStr(YString findstr)
{
  int targetSize=findstr.size(); //目标字符串长度
  if (targetSize <= 0 ) return false;
  long temp = size();
  if ((temp < targetSize) || (temp == 0 ))
  {
    return false;
  }
  if(c_str()==findstr) return true;
  else
  {
    YString tempstr="";
    tempstr=findstr+" ";
    if (tempstr.size() > temp ) return false;
    YString ceshistr = c_str();
    if (c_str()==tempstr) return true;
    tempstr=" "+findstr+" ";
    YString myusestring ;
    targetSize = targetSize+2 ;
    int pos =0;
    if((pos=find(tempstr,pos))!=npos)
    {
      return true;
    }
    targetSize = targetSize-2 ; //目标字符串长度
    tempstr=" "+findstr;
    long aa=size()-targetSize -1;
    if (aa >= 0 )
    {
       myusestring = substr (size()-targetSize -1 );
       if (myusestring == tempstr)   return true;
       myusestring = substr (0,targetSize+1);
       tempstr = findstr+" ";
       if (myusestring == tempstr)   return true;
    }
  }
  return false;
}
//-------------------------------------------------------------
//从一个字符串列表中删除一个项
void YString::removeWord(YString target,int num)
{
  int targetSize=target.size(); //目标串的长度
  if(targetSize == 0) return;
  for(int pos=0;(num!=0)&&((pos=find(target,pos))!=npos);){
    if((pos+targetSize) < size()){
      if(at(pos+targetSize) == ' '){
        if(pos >0 ){
          if(at(pos-1) == ' '){
            erase(pos,targetSize+1);  //两边都是0
            num--;
          }
          else pos+=targetSize;
        }
        else{
          erase(pos,targetSize+1); //开头
          num--;
        }
      }
      else pos+=targetSize;
    }
    else{
      if(pos == 0){
        erase(pos,targetSize);        //完全相同
        num--;
      }
      else{
        if(at(pos-1) == ' '){
          erase(pos-1,targetSize+1);  //结尾
          num--;
        }
        else pos+=targetSize;
      }
    }
  }
}
//-------------------------------------------------------------
//从字符串中删除若干单词（字符串将被改变）
//-1表示所有,其他表示删除前几个
void YString::removeAnyWord(YString target,int num)
{
  int targetSize=target.size(); //目标字符串长度
  if(targetSize==0) return;
  
  for(int pos=0;(num!=0)&&((pos=find(target,pos))!=npos);num--){
    erase(pos,targetSize);
  }
}
//-------------------------------------------------------------
/* rfc1738:

   ...The characters ";",
   "/", "?", ":", "@", "=" and "&" are the characters which may be
   reserved for special meaning within a scheme...

   ...Thus, only alphanumerics, the special characters "$-_.+!*'(),", and
   reserved characters used for their reserved purposes may be used
   unencoded within a URL...

   For added safety, we only leave -_. unencoded.
 */

static unsigned char hexchars[] = "0123456789ABCDEF";

YString YString::url_encode(void)
{
	register int x, y,len;
	char *str;
	const char * pself = c_str();

	str = new char[3 * size() + 1];
	len = size();

	for (x = 0, y = 0; len--; x++, y++) {
		str[y] = pself[x];
		if (str[y] == ' ') {
			str[y] = '+';
#ifndef CHARSET_EBCDIC
		} else if ((str[y] < '0' && str[y] != '-' && str[y] != '.') ||
				   (str[y] < 'A' && str[y] > '9') ||
				   (str[y] > 'Z' && str[y] < 'a' && str[y] != '_') ||
				   (str[y] > 'z')) {
			str[y++] = '%';
			str[y++] = hexchars[(pself[x] >> 4) & 0x0F];
			str[y] = hexchars[pself[x] & 0x0F];
		}
#else /*CHARSET_EBCDIC*/
		} else if (!isalnum(str[y]) && strchr("_-.", str[y]) == NULL) {
			/* Allow only alphanumeric chars and '_', '-', '.'; escape the rest */
			str[y++] = '%';
			str[y++] = hexchars[os_toascii[(unsigned char) pself[x]] >> 4];
			str[y] = hexchars[os_toascii[(unsigned char) pself[x]] & 0x0F];
		}
#endif /*CHARSET_EBCDIC*/
	}
	str[y] = '\0';
	return str;
}
//-------------------------------------------------------------
void YString::Base64_Encode ()
{
  //## begin mystring::Base64_Encode%3A92105A02FE.body preserve=yes
	char m_sBase64_Encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
		//// 这串字符串是在编码的时候用的，专门用于Base64为编码！
		//// 只能放在这里，前面会出错误，靠，不能赋值
	int InLen,InPos = 0,OutLen,OutPos = 0;	/// InLen,InPos 用来表示编码以前的字符的长度、位置，OutLen 表示编码以后的字符的长度、位置
	char *InStr,*OutStr;
	int c1,c2,c3,i,n;	//// 用来保存三个变量，i 保存循环变量 ，n 保存循环结尾

	InLen = length();	//// 取得源字符串的长度
	OutLen = (InLen/3+1)*4;	//// 计算出编码后的长度
	InStr = new char[InLen+1];
	OutStr = new char[OutLen+1];
	
	strcpy(InStr,c_str());	//// 取的字符串内容
	n = InLen/3;	//// 先取前面固定的字符编码
	for(i=0;i<n;i++)
	{
		c1 = InStr[InPos++] & 0xFF;	/// InStr[i]
		c2 = InStr[InPos++] & 0xFF;	/// InStr[i+1]
		c3 = InStr[InPos++] & 0xFF;	/// InStr[i+2]，此时的 InPos = i+3,In

		OutStr[OutPos++] = m_sBase64_Encode[(c1&0xFC)>>2];  //// 00111111--11
		OutStr[OutPos++] = m_sBase64_Encode[((c1&0x03)<<4) | ((c2&0xF0)>>4)];	//// 00112222--2222
		OutStr[OutPos++] = m_sBase64_Encode[((c2&0x0F)<<2) | ((c3&0xC0)>>6)];	//// 00222233--333333
		OutStr[OutPos++] = m_sBase64_Encode[c3&0x3F];	//// 00333333
	}
	
	switch(InLen%3)
	{
		case 0:		//// 能够整除就不管他
			break;
		case 1:		//// 剩下一个多余的
			c1 = InStr[InPos++] &0xFF;
			OutStr[OutPos++] = m_sBase64_Encode[(c1&0xFC)>>2];
			OutStr[OutPos++] = m_sBase64_Encode[(c1&0x03)<<4];
			OutStr[OutPos++] = '*';		////  更改 "*" 号为结束符号
			OutStr[OutPos++] = '*';

			break;
		case 2:		//// 剩下两个多余的
			c1 = InStr[InPos++] & 0xFF;
			c2 = InStr[InPos++] & 0xFF;

			OutStr[OutPos++] = m_sBase64_Encode[(c1&0xFC)>>2];
			OutStr[OutPos++] = m_sBase64_Encode[((c1&0x03)<<4) | ((c2&0xF0)>>4)];
			OutStr[OutPos++] = m_sBase64_Encode[((c2&0x0F)<<2)];
			OutStr[OutPos++] = '=';		//// 这是结尾
			
			break;
		default:	//// 其它的
			break;
	}
	OutStr[OutPos] = '\0';	//// 表示编码完成，这是结尾
	assign(OutStr);
  //## end mystring::Base64_Encode%3A92105A02FE.body
}
//-------------------------------------------------------------
void YString::Base64_Decode ()
{
  //## begin mystring::Base64_Decode%3A9210730386.body preserve=yes
	int InLen,InPos = 0,OutLen,OutPos = 0;	/// InLen,InPos 用来表示编码以前的字符的长度、位置，OutLen 表示编码以后的字符的长度、位置
	char *InStr,*OutStr;
	int c1,c2,c3,c4,i,n;	//// 用来保存四个变量，i 保存循环变量 ，n 保存循环结尾
	
	InLen = length();
	n =InLen /4;	/// 必须能被4整除
	OutLen = n * 3;
	InStr = new char[InLen+1];
	OutStr = new char[OutLen+1];
	strcpy(InStr,c_str());
	for(i=0;i<n;i++)
	{
		c1 = Base64DecodeVal(InStr[InPos++]);
		c2 = Base64DecodeVal(InStr[InPos++]);
		c3 = Base64DecodeVal(InStr[InPos++]);
		c4 = Base64DecodeVal(InStr[InPos++]);
		
		OutStr[OutPos++] = ((c1&0X3F)<<2) | ((c2&0X3F)>>4);	//// 00--11111122-2222
		OutStr[OutPos++] = ((c2&0X3F)<<4) | ((c3&0X3F)>>2);	//// 00--22223333-33
		OutStr[OutPos++] = ((c3&0X3F)<<6) | (c4&0X3F);	//// 00--33444444
	}
	OutStr[OutPos]='\0';
	assign(OutStr);		//// 保存编码后的数值
  //## end mystring::Base64_Decode%3A9210730386.body
}
//-------------------------------------------------------------
int YString::Base64DecodeVal (unsigned char a)
{
  //## begin mystring::Base64DecodeVal%3A92108402EB.body preserve=yes
	if(a<=90&&a>=65) 	return a-65;	////// base64 编码 A~Z	26
	if(a<=122&&a>=97) 	return a-71;	////// a~z		+ 26
	if(a<=57&&a>=48) 	return a+4;	////// 0~9		+ 10
	if(a==43)		return 62;	//////  +		+  1
	if(a==47)		return 63;	//////  /		+  1
	if(a==61)		return 0;	//////  =		+  1  /// 这是结尾，给他一个结束标志
								/////	=  26+26+10+1+1+1= 65
	return 0;	////////////////返回错误信息
  //## end mystring::Base64DecodeVal%3A92108402EB.body
}
//-------------------------------------------------------------
//是否全是由GB2312字符集中的汉字(包括ASCII字符)构成
bool YString::isGB2312(void)
{
  size_t len=size();
  int i=0;
  unsigned char c;
  while(i<len) {
    c=at(i);
    if(c & 0x80) { //首位为1
      if((c>=0xb0)&&(c<=0xf7)) { //区号正确(GB2312汉字)
        i++;
        c=at(i);
        if((c<0xa1)||(c>0xfe)) return false;
      } //end half if -- GB2312汉字
      else if((c>=0xa1)&&(c<=0xa9)) { //GB2312非汉字符号
        unsigned char c1=c;
        i++;
        c=at(i);
        if((c<0xa1)||(c>0xfe)) return false;
        switch(c1) { //区
        	case 0xa1:
        		if(c==0xa1) return false;  //A1A1是空格，所以也封掉
        		break;
        	case 0xa2:
        		
        		break;
        	case 0xa3:
        		//ok;
        		break;
        	case 0xa4:
        		if((c>=0xf4)&&(c<=0xfe)) return false;
        		break;
        	case 0xa5:
        		if((c>=0xf7)&&(c<=0xfe)) return false;
        		break;
        	case 0xa6:
        		if((c>=0xb9)&&(c<=0xc0)) return false;
        		if((c>=0xd9)&&(c<=0xfe)) return false;
        		break;
        	case 0xa7:
        		if((c>=0xc2)&&(c<=0xd0)) return false;
        		if((c>=0xf2)&&(c<=0xfe)) return false;
        		break;
        	case 0xa8:
        		if((c>=0xa1)&&(c<=0xc4)) return false;
        		if((c>=0xea)&&(c<=0xfe)) return false;
        		break;
        	case 0xa9:
        		if((c>=0xa1)&&(c<=0xa3)) return false;
        		if((c>=0xf0)&&(c<=0xfe)) return false;
        		break;
        }
      } //end half if -- GB2312非汉字符号
      else return false;  //区号不正确
    } //end if 首位为1
    i++;
  } //end while
  return true;
}

