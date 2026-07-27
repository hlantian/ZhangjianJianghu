//---------------------------------------------------------------------------
//
// ycommand.cpp    2000年6月12日
//
// 类YCommand：负责命令短语分析及命令别名的处理
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------
//执行命令
void YCommand::executeCommand(YString sessionID, YString command)
{
  //cout<<"[YCommand::executeCommand]"<<sessionID<<"-"<<command<<endl;
  //确定Session(也就是知道了动作执行者)
  YSession* session=g_SessionManager->getSession(sessionID);
  if(!session) {    //session不存在
    //cout<<"[YCommand::executeCommand]session\""<<sessionID<<"\" does not exist in SessionManager."<<endl;
    return;
  }
  executeCommand(session, command);
}
//---------------------------------------------------------------
//执行命令
void YCommand::executeCommand(YSession* session, YString command)
{
  g_Stopwatch->start(1);  //计时开始
  g_applog->write("[YCommand::executeCommand]"+session->getPlayer()->getAsString("名字")+"--"+command);
  command=translate(command);
  //确定Room
  YAbstractRoom* room=(YAbstractRoom*)session->getPlayer()->getRoom();
  if(!room) {    //room不存在
    //cout<<"[YCommand::executeCommand]room of "<<session->getPlayer()->getName()<<"\" does not exist in SessionManager."<<endl;
    if(session) session->getPlayer()->display("房间已经消失。<br>请退出WEB MUD,并与巫师联系。");
    return;
  }
  //处理人物的空闲

  if( session->getPlayer() ) session->getPlayer()->setFreeTime(0);
  int retVal=0;
  //先让Room处理命令
  retVal=room->executeCommand(session->getPlayer(),command);
  //YErr::show("[YCommand::executeCommand]room->executeCommand-"+command);
  if(!retVal) { //需要后续处理
    //然后让执行者处理
    retVal=session->getPlayer()->executeCommand(command);
  }
  //好不容易处理完了
  g_Stopwatch->stop(1); //计时结束
}
//---------------------------------------------------------------
//建立FIFO并开始读取命令,成功返回0
int YCommand::startReading(void)
{
  cout<<"[YCommand]start reading command";
  if(m_session) {
    cout<<" of "<<m_session->getPlayer()->getName()<<"("<<m_session->getID()<<")";
  }
  cout<<"..."<<endl;
  m_finish=false; //重置停止标志
  //建立FIFO以读取命令
  m_FIFO=new YFIFO(g_Settings->getCommandFIFOPathName(m_session),"rd", 100*1024);
  while(!m_finish) {
    
    YString s=m_FIFO->read();
    //YErr::show("[YCommand::startReading]get command "+s);
    #ifdef __USE_SEMAPHORE__
      if(g_SystemSemaphore!=SEM_FAILED) {
        //YErr::show("[YCommand::startReading]等待系统信号灯....");
        if(sem_wait(g_SystemSemaphore)==0) {
          //g_err.show("[YCommand::startReading]等待系统信号灯结束.");
        }
        else {
          g_err.show("[YCommand::startReading]等待系统信号灯失败.");
        }
      }
    #endif
    bool first=true;
    if((!g_Busy) && g_Busy_Wait) sleep(10);
    while(g_Busy) {
      if(first) {
        if(!g_Busy_Wait) g_Busy_Wait=2;
        g_applog->write("[YCommand::startReading]系统忙(g_Busy="+(YString)g_Busy+")");
      }
      first=false;
    }
    g_Busy=2;
    if(g_Busy_Wait==2) g_Busy_Wait=0;

    g_Stopwatch->start(1);  //计时开始
    if(!m_session) { //单线程命令处理
      int l=g_Settings->getSessionIDLength();
      int ssize=s.size();
      executeCommand(YString(s,0,(l<ssize)?l:ssize), YString(s,(l<ssize)?l:ssize,(l<ssize)?(ssize-l):0));
    }
    else { //多线程命令处理(每session一个线程)
      executeCommand(m_session,s);
    }
    g_Stopwatch->stop(1); //计时结束
    
    g_Busy=0;
    #ifdef __USE_SEMAPHORE__
    if(g_SystemSemaphore!=SEM_FAILED) {
      //YErr::show("[YCommand::startReading]挂出系统信号灯....");
      if(sem_post(g_SystemSemaphore)==0) {
        //g_err.show("[YCommand::startReading]挂出系统信号灯结束.");
      }
      else {
        g_err.show("[YCommand::startReading]挂出系统信号灯失败.");
      }
    }
    #endif
  }
  delete m_FIFO;
  return 0;
}
//---------------------------------------------------------------
//停止读取命令（异步）
void YCommand::endReading(void)
{
  m_finish=true;  //设置停止标志，startReading检查到此标志就会返回
}
//---------------------------------------------------------------
//运行线程(继承自Thread)
void YCommand::run(void)
{
  startReading();
}
