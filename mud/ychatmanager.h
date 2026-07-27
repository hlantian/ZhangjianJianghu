//---------------------------------------------------------------------------
//
// ychatmanager.h    2001年6月22日
//
// 类YChatManager：聊天频道管理
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YCHATMANAGER_H__
#define __YCHATMANAGER_H__

#include <map>
#include "ystring.h"
#include "ychat.h"

class YChatManager {
  private:
    map<YString, YChat*, less<YString> > m_chatgroup;

    inline bool isLoaded(YString chatname);         //chat是否已经加载
    YChat* loadChat(YString chatname);              //load一个chat，加入组

  public:
		YChatManager();  //构造函数
		~YChatManager(); //析构函数

    YChat* getChat(YString chatname);     //返回chatname指定的chat对象，没找到load一个
};

#endif //__YCHATMANAGER_H__

