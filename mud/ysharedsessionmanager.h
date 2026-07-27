//---------------------------------------------------------------------------
//
// ysharedsessionmanager.h    2000年12月12日
//
// 类YSharedSessionManager：可在进程间共享的任务列表，用于查看任务是否存在
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YSHAREDSESSIONMANAGER_H__
#define __YSHAREDSESSIONMANAGER_H__

class YSharedSessionManager {
  private:
    int m_shm_id; //共享内存句柄
    int m_shm_size; //共享内存大小
    unsigned char* m_shm_base; //共享内存开始地址
		int* m_piCount;
		unsigned char* m_pSessions;
		int m_capacity;
		int m_recordLength;
  protected:

  public:
		YSharedSessionManager(YString filename,int size);  //构造函数
		~YSharedSessionManager(); //析构函数
		void init(void);
		bool add(YSession* session);
		bool remove(YSession* session);
		int exist(YSession* session);		
};

#endif //__YSHAREDSESSIONMANAGER_H__
