//---------------------------------------------------------------------------
//
// ystring.h    2000年6月8日
//
// 类YSring：提供字符串的封装，解决C中字符串的繁琐操作及容易产生越界的问题
//          改为使用C++中的标准string, 但增加一YString层，以便于添加功能
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YSTRING_H__
#define __YSTRING_H__
#include <string>
using namespace std;
class YString : public string {
  public:
    YString():string() {}
    YString(string s):string(s) {}
    YString(const char* const S):string(S) {}
    YString(YString s, int pos, int n):string(s,pos,n) {}
    YString(int n, char c):string(n,c) {}
    YString(const int);
    YString(const short);
    YString(const long);
    YString(const float);
    YString(const double);

    //取第一个单词（字符串将被改变）
    YString getWord(YString delim=" ");
    //转换成HTML格式，比如'\n'转换成<BR>
    YString HTMLFormat(void);
    //将"转换成\",用于写程序中的字符串
    YString toInnerString(void);
    //转换成长整型变量
    long toLong(void);
    //转换成双精度变量
    double toDouble(void);
    //对字符串进行URL编码，
    YString url_encode(void);

  public:
      //	用 base64 编码方式编码  alfa 添加
      void Base64_Encode ();
      //	用 base64 编码方式解码  alfa 添加
      void Base64_Decode ();
  private:
      int Base64DecodeVal (unsigned char a);

  public:
    //lp
    //查找字符在字符串中
    bool findStr(YString findstr);

  public:
    //zhy
    //从字符串中删除若干单词（字符串将被改变）
    void removeWord(YString target,int num=-1);
    void removeAnyWord(YString target,int num=-1); //原removeWord
		//是否全是由GB2312字符集中的汉字(包括ASCII字符)构成
		bool isGB2312(void);
};

void trim(char* s); //删除前后空白
//数字转换为汉字
YString LongToChinese(long i);
#endif //__YSTRING_H__
