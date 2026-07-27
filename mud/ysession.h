//YSession.hpp--类YSession(会话)的声明
#ifndef __YSession_H__
#define __YSession_H__

#include "ystring.h"
#include "ydatetime.h"
#include "ycommand.h"

class YPlayer;
enum msg_type{ORIGINAL_MSG,CHANNEL_MSG,JAVASCRIPT_MSG};
class YSession {
	//属性：ID
	private:
		YString m_ID; //属性ID的成员变量
	public:
		YString getID(void) {return m_ID;} //读属性ID
		void setID(YString newID) {m_ID=newID;} //设置ID

	//属性：Player
	private:
		YPlayer* m_Player; //属性Player的成员变量
	public:
		YPlayer* getPlayer(void) {return m_Player;} //读属性Player
		void setPlayer(YPlayer* newPlayer) {m_Player=newPlayer;} //设置Player

	//属性：StartTime, 会话开始时间
	private:
		YDateTime m_StartTime; //属性StartTime的成员变量
	public:
		YDateTime getStartTime(void) {return m_StartTime;} //读属性StartTime
		void setStartTime(YDateTime newStartTime) {m_StartTime=newStartTime;} //设置StartTime

	//属性：LastAccessTime, 用户最后一次访问的时间，用于在用户不响应超过一定的时间后终止会话
	private:
		YDateTime m_LastAccessTime; //属性LastAccessTime的成员变量
	public:
		YDateTime getLastAccessTime(void) {return m_LastAccessTime;} //读属性LastAccessTime
		void setLastAccessTime(YDateTime newLastAccessTime) {m_LastAccessTime=newLastAccessTime;} //设置LastAccessTime

	//属性：LastMessageTime(用户最后一次收到消息的时间，用于防止用户浏览器超时)
	private:
		YDateTime m_LastMessageTime; //属性LastMessageTime(用户最后一次收到消息的时间，用于防止用户浏览器超时)的成员变量
	public:
		YDateTime getLastMessageTime(void) {return m_LastMessageTime;} //读属性LastMessageTime(用户最后一次收到消息的时间，用于防止用户浏览器超时)
		void setLastMessageTime(YDateTime newLastMessageTime) {m_LastMessageTime=newLastMessageTime;} //设置LastMessageTime(用户最后一次收到消息的时间，用于防止用户浏览器超时)

	//属性：Message(发往客户端的信息)
	public:
		YString message_buf; //属性Message(发往客户端的信息)的成员变量

  private:
    YCommand* m_CommandExecutor;

  public:
	  YSession(YString ID, YPlayer* player);  //构造函数
	  ~YSession(); //析构函数
  	//Terminate--终止会话
	  bool Terminate(void);

  public:
    //接收一条消息
    void message(YString msg, bool newline=true, msg_type messagetype=ORIGINAL_MSG, const YString& name="");

	//属性：MessageFIFO
	private:
		YFIFO* m_MessageFIFO; //属性MessageFIFO的成员变量
	public:
		YFIFO* getMessageFIFO(void) {return m_MessageFIFO;} //读属性MessageFIFO
		void setMessageFIFO(YFIFO* newMessageFIFO) {m_MessageFIFO=newMessageFIFO;} //设置MessageFIFO
  private:
    inline YString getMessageFIFOName();
  public:
  #ifdef MULTI_THREAD_MUD
    int startReadingCommand(void){return m_CommandExecutor->Start();};
    void endReadingCommand(void){m_CommandExecutor->endReading();};
  #endif //MULTI_THREAD_MUD
};

#endif //__YSession_H__
