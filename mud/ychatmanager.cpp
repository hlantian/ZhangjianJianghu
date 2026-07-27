//---------------------------------------------------------------------------
//
// ychatmanager.cpp    2001年6月22日
//
// 类YChatManager：聊天频道管理
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YChatManager构造函数
YChatManager::YChatManager()
{
}
//---------------------------------------------------------------------------
//YChatManager析构函数
YChatManager::~YChatManager()
{
}
//---------------------------------------------------------------------------
//chat是否已经加载
bool YChatManager::isLoaded(YString chatname)
{
  return m_chatgroup.find(chatname)!=m_chatgroup.end();
}
//---------------------------------------------------------------------------
YChat* YChatManager::loadChat(YString chatname)
{
  YChat* pFactionChat=new YChat;
  if(!pFactionChat) {           //简单的错误信息输出，new Chat不成功。
    YErr::show("[YChatManager::loadChat]Chat "+chatname+" ：new Chat 不成功.\n");
  }
  
  m_chatgroup[chatname]=pFactionChat; //加入频道组

  return pFactionChat;
}
//---------------------------------------------------------------------------
//返回chatname指定的chat对象，没找到load一个
YChat* YChatManager::getChat(YString chatname)
{
  if(isLoaded(chatname)) return m_chatgroup[chatname];
  else return loadChat(chatname);
}
