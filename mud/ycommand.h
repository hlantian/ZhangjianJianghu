//---------------------------------------------------------------------------
//
// ycommand.h    2000年6月12日
//
// 类YCommand：负责命令短语分析及命令别名的处理
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YCOMMAND_H__
#define __YCOMMAND_H__

#include "ystring.h"
#include "yfifo.h"
#include <cc++/thread.h>
using namespace ost;  
class YSession;

class YCommand : public Thread{
  private:
    bool m_finish;  //停止标志，用于停止线程运行
    YSession* m_session;
    YFIFO* m_FIFO;
    virtual void run(void);
  public:
		YCommand(YSession* session=NULL):m_session(session){};  //构造函数
		~YCommand(){}; //析构函数

    //执行命令
    void executeCommand(YString sessionID, YString command);
    void executeCommand(YSession* session, YString command);
    //命令别名处理
    YString translate(const YString command);
    //建立FIFO并开始读取命令
    int startReading(void);
    //停止读取命令（异步）
    void endReading(void);
};

#endif //__YCOMMAND_H__
