//---------------------------------------------------------------------------
//
// ysharedsessionmanager.cpp    2000年12月12日
//
// 类YSharedSessionManager：可在进程间共享的任务列表，用于查看任务是否存在
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "ysharedsessionmanager.h"
#include "ylogfile.h"
#include "ysettings.h"

//---------------------------------------------------------------------------
//YSharedSessionManager构造函数
YSharedSessionManager::YSharedSessionManager(YString filename,int size):m_shm_size(size)
{
	m_shm_base=NULL;
	key_t key=ftok(filename.c_str(),'Y');
	if(key==-1) {
		g_applog->write((YString)"[YSharedSessionManager::YSharedSessionManager]ftok error.("+sys_errlist[errno]+")");
		return;
	}
	
	m_shm_id=shmget(key,m_shm_size,IPC_CREAT|0666);
	if(m_shm_id==-1) {
		g_applog->write((YString)"[YSharedSessionManager::YSharedSessionManager]shmget error.("+sys_errlist[errno]+")");
		return;
	}
	
	m_shm_base=shmat(m_shm_id,NULL,0);
	if(m_shm_base==(unsigned char*)-1) {
		g_applog->write((YString)"[YSharedSessionManager::YSharedSessionManager]shmat error.("+sys_errlist[errno]+")");
		m_shm_base=NULL;
		return;
	}
	m_piCount=m_shm_base+2;
	m_pSessions=m_piCount+sizeof(int);
	m_recordLength=g_Settings->getSessionIDLength()+1;
	m_capacity=(m_shm_size-sizeof(int)-2)/m_recordLength;
}
//---------------------------------------------------------------------------
//YSharedSessionManager析构函数
YSharedSessionManager::~YSharedSessionManager()
{
 //删除共享内存
 if(shmctl(m_shm_id,IPC_RMID,NULL)!=0) {
		g_applog->write((YString)"[YSharedSessionManager::~YSharedSessionManager]共享内存无法删除.("+sys_errlist[errno]+")");
 }
}
//---------------------------------------------------------------------------
bool YSharedSessionManager::init(void)
{
	*m_shm_base='y';
	*(m_shm_base+1)='l';
	*m_piCount=0;
	for(int i=0; i<m_capacity; i++) {
		*(m_pSessions+(m_recordLength*i))='u'; //unused 
	}
}
//---------------------------------------------------------------------------
bool YSharedSessionManager::add(YSession* session)
{
	bool success=false;
	for(int i=0; i<m_capacity; i++) {
		if((*(m_pSessions+(m_recordLength*i))=='u')||(*(m_pSessions+(m_recordLength*i))=='d')) { //unused or dead
			strncpy(m_pSessions+(m_recordLength*i)+1, session->getID().c_str(), m_recordLength);
			*(m_pSessions+(m_recordLength*i))='a'; //active;
			success=true;
			break;
		}
		if(*(m_pSessions+(m_recordLength*i))!='a') {
			g_applog->write("[YSharedSessionManager::add]纪录标志错误.");
		}
	}
	return success;
}
//---------------------------------------------------------------------------
bool YSharedSessionManager::remove(YSession* session)
{
}
//---------------------------------------------------------------------------
bool YSharedSessionManager::exist(YSession* session)		
{
}
//---------------------------------------------------------------------------
