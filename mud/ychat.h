//---------------------------------------------------------------------------
//
// ychat.h    2000年6月12日
//
// 类YChat：频道，管理各种交谈，以及事件、动作、物体的描述
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YCHAT_H__
#define __YCHAT_H__
#include "ymudobject.h"
#include "yobjectgroup.h"
#include "yabstractactor.h"
#include "ystring.h"

class YChat : private YMUDObject{
	//属性：Subscribers (订阅者)
	private:
		YObjectGroup* m_Subscribers; //属性Subscribers的成员变量
	public:
		YObjectGroup* getSubscribers(void) {return m_Subscribers;} //读属性Subscribers
		void setSubscribers(YObjectGroup* newSubscribers) {m_Subscribers=newSubscribers;} //设置Subscribers
	//属性：Readonly(玩家能否用其交谈)
	private:
		bool m_Readonly; //属性Readonly的成员变量
	public:
		bool getReadonly(void) {return m_Readonly;} //读属性Readonly
		void setReadonly(bool newReadonly) {m_Readonly=newReadonly;} //设置Readonly


  private:

  protected:

  public:
		YChat(bool readonly=false);  //构造函数
		~YChat(); //析构函数
    //订阅
    void subscribe(YAbstractActor* subscriber)
          {m_Subscribers->add(subscriber);}
    //退订
    void unsubscribe(YAbstractActor* subscriber){m_Subscribers->remove(subscriber);}
    //在Chat中说话(不受Readonly属性限制)
    void _talk(YAbstractActor* speaker, YString message,
               YAbstractActor* deaf1=NULL, YAbstractActor* deaf2=NULL,
               msg_type messagetype=ORIGINAL_MSG, const YString& name="");
    //在Chat中说话(成功返回0, Chat为只读返回-1)
    int talk(YAbstractActor* speaker, YString message,
               YAbstractActor* deaf1=NULL, YAbstractActor* deaf2=NULL,
               msg_type messagetype=ORIGINAL_MSG, const YString& name="");
    //与特定人密谈
    static void talk(YAbstractActor* speaker, YAbstractActor* reciever, YString message);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};
};

#endif //__YCHAT_H__
