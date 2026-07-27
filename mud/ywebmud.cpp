//---------------------------------------------------------------------------
//
// ywebmud.cpp    2000年6月12日
//
// 类YWebMUD：控制MUD系统的启动、运行、关闭等操作
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YWebMUD构造函数
YWebMUD::YWebMUD()
{
	m_MajorVersionNo=0;
	m_MinorVersionNo=1;
	m_Version="V 0.1a";
	m_Copyright="版权所有，北京西陆信息技术有限公司 2000";
	m_RegisteredPlayerCount=0;
	m_RegisteredWizardCount=2;
	m_RegisteredGodCount=1;
	m_OnlinePlayerCount=0;
	m_OnlineWizardCount=0;
	m_OnlineGodCount=0;
}
//---------------------------------------------------------------------------
//YWebMUD析构函数
YWebMUD::~YWebMUD()
{
}
//---------------------------------------------------------------------------
//启动系统
int YWebMUD::start(void)
{
  cout<<"Starting WebMUD ..."<<endl;
  g_SessionManager->start();
  #ifdef __WIN32__
    g_Command->startReading();
  #else
    g_Comm->run();
  #endif

  return 1;
}
//---------------------------------------------------------------------------
void YWebMUD::shutdown(int delaySecond)
{
}

