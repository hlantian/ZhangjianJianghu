//---------------------------------------------------------------------------
//
// ychat.cpp    2000年6月12日
//
// 类YChat：频道，管理各种交谈，以及事件、动作、物体的描述
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YChat构造函数
YChat::YChat(bool readonly): YMUDObject(),m_Readonly(readonly)
{
  m_Subscribers=new YObjectGroup(this);
  disableTimer();
}
//---------------------------------------------------------------------------
//YChat析构函数
YChat::~YChat()
{
  delete m_Subscribers;
}
//---------------------------------------------------------------------------
//在Chat中说话(不受Readonly属性限制)
void YChat::_talk(YAbstractActor* speaker, YString message,
               YAbstractActor* deaf1, YAbstractActor* deaf2,
               msg_type messagetype, const YString& name)
{
  YObjectGroup::obj_iter it=m_Subscribers->begin();
  while(it!=m_Subscribers->end()) {
    if(((*it)!=deaf1) && ((*it)!=deaf2)) {
      ((YAbstractActor*)(*it))->message(speaker, message, true, messagetype, name);
    }
    it++;
  }
}
//---------------------------------------------------------------------------
//在Chat中说话(成功返回0, Chat为只读返回-1)
int YChat::talk(YAbstractActor* speaker, YString message,
               YAbstractActor* deaf1, YAbstractActor* deaf2,
               msg_type messagetype, const YString& name)
{
  if(getReadonly()) return -1;
  else {
    _talk(speaker, message, deaf1, deaf2, messagetype, name);
    return 0;
  }
}
//---------------------------------------------------------------------------
//与特定人密谈
void YChat::talk(YAbstractActor* speaker, YAbstractActor* reciever, YString message)
{
  message="【"+speaker->getDisplayName()+"(密谈)】"+message;
  reciever->message(speaker, message);
}
