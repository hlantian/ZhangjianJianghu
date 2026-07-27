//---------------------------------------------------------------------------
//
// ystringtest.cpp    2000年6月7日
//
// 类YSring：提供字符串的封装，解决C中字符串的繁琐操作及容易产生越界的问题
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "ystring.h"
#include <iostream>

#pragma hdrstop
#pragma argsused
int main(int argc, char* argv[])
{
  YString c1("internet call"), c2("xilu bbs");
  #define TRY(op) \
  cout<<"c1 =\""<<c1<<"\""; cout<<", c2 =\""<<c2<<"\""; \
  cout<<"; c1" #op "c2 produces "; \
  cout<<(c1 op c2); \
  cout << endl;
  TRY(+)  
  TRY(<) TRY(>) TRY(==) TRY(!=) TRY(<=)
  TRY(>=) TRY(+=)
  cin.get();
  return 0;
}

