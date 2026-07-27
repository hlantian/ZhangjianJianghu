//YSession.cpp--类YSession(会话)的实现

#include "webmudcore.h"

//--------------------------------------------------------
//构造函数
YSession::YSession(YString ID, YPlayer* player): m_Player(player), m_ID(ID)
{
  #ifndef __WIN32__
  	g_Comm->addSession(this);
  #endif
	m_StartTime=YDateTime::now();
  m_LastAccessTime=YDateTime::now();
  //建立用于写消息的FIFO
  m_MessageFIFO=new YFIFO(getMessageFIFOName(), "ws", 10*1024);
  m_CommandExecutor=0;
  #ifdef MULTI_THREAD_MUD
    //建立该Session对应的命令处理器
    m_CommandExecutor=new YCommand(this);
  #endif //MULTI_THREAD_MUD
}
//--------------------------------------------------------
//析构函数
YSession::~YSession()
{
  //从玩家列表中删除与Session相连的用户
	g_PlayerManager->quit(m_Player->getName());
  #ifndef __WIN32__
	  g_Comm->deleteSession(this);
  #endif
  if(m_MessageFIFO) delete m_MessageFIFO;
  if(m_CommandExecutor) delete m_CommandExecutor;
}
//--------------------------------------------------------
//接收一条消息
void YSession::message(YString msg, bool newline, msg_type messagetype, const YString& name)
{
  m_LastMessageTime=YDateTime::now();
  if((newline)&&(messagetype==ORIGINAL_MSG)) msg+="<br>";
#ifdef __JAVACLIENT__
  switch(messagetype) {
    case CHANNEL_MSG:   //交谈频道
      msg="say(\""+name+"\",\""+msg.toInnerString()+"\")";
      break;
    case ORIGINAL_MSG:  //原始信息
      msg="showinfo(\""+msg.toInnerString()+"\")";
      break;
    case JAVASCRIPT_MSG:  //javascript命令
      //不需要改变
      break;
    default:
      g_err.show("[YSession::message]Unknown message type.");
  }
  if(message_buf.size()>10000) message_buf.erase(); //防止信息过多占用内存
  message_buf+=msg+'\n';
#else  //__JAVACLIENT__
  switch(messagetype) {
    case CHANNEL_MSG:   //交谈频道
      msg="<script>say(\""+name+"\",\""+msg.toInnerString()+"\")</script>";
      break;
    case ORIGINAL_MSG:  //原始信息
      msg="<script>showinfo(\""+msg.toInnerString()+"\")</script>";
      break;
    case JAVASCRIPT_MSG:  //javascript命令
      msg="<script>"+msg+"</script>";
      break;
    default:
      g_err.show("[YSession::message]Unknown message type.");
  }
  #ifdef __BUFFERFIFO__
		m_MessageFIFO->write(getID()+" "+msg+"\xff");
	#else
		m_MessageFIFO->write(msg);
	#endif
#endif  //__JAVACLIENT__
  //cout<<"[YSession::message]write "<<msg<<" to "<<getMessageFIFOName()<<endl;
}
//--------------------------------------------------------
YString YSession::getMessageFIFOName()
{
  #ifdef __BUFFERFIFO__
		return "/home/newmud/data/fifo/buffer.fifo";
	#else
		return g_Settings->getFIFOPath()+g_Settings->getPathSeparator()+getID()+".fifo";
	#endif
}


