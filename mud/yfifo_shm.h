//---------------------------------------------------------------------------
//
// yfifo_shm.h    2000年11月30日
//
// 类YFIFO：提供对FIFO的支持，这个版本使用共享内存作为主要交换方式，共享内存不够时
//          用文件保存。
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YFIFO_SHM_H__
#define __YFIFO_SHM_H__

#include <queue>
#include <semaphore.h>
#include "ystring.h"

class YFIFO {
  private:
    YString m_name; //FIFO的名字
    YString m_mode;
    YString delim; //消息之间的分割符
    sem_t *m_sem; //信号灯，防止同时读写
    queue<YString> messages;
    int MAXLEN;
    off_t m_LastFileOffset; //上一次读取后的文件位置
    bool m_HasSHM;
    int m_shm_id; //共享内存句柄
    int m_shm_size; //共享内存大小
    unsigned char* m_shm_base; //共享内存开始地址
    unsigned char* m_pBusy; //忙标志
    int* m_pStart; //信息头相对数据区开始的偏移
    int* m_pEnd;  //信息尾相对数据区开始的偏移
    unsigned char* m_pSign; //有效标志
    unsigned char* m_pMemHasData; //内存中有数据
    unsigned char* m_pFileHasData; //文件中有数据
    int m_shm_data_size; //共享内存中数据区的大小
    unsigned char* m_pDataStart; //数据区开始
    unsigned char* m_pDataEnd; //数据区结束
    unsigned long m_usedtime; //已经等待的时间
		bool writeshm(const YString& s);
		YString readOnce(void);
		YString readFromFile(void); //从文件中读出送入\共享内存,返回"",如果不能写入共享内存,返回所取得的字符串
  protected:

  public:
		YFIFO(const YString& name, const YString& mode, int shm_size);  //构造函数
		     //mode: "w"写，"r"读，"s"流方式，不需分隔，"d"需要分隔，每条纪录要单独读出
		     //可用"ws""wd""rs"等组合
		~YFIFO(); //析构函数
    YString getName(void) {return m_name;}
    int write(YString s);
    YString read(int maxlen=0, unsigned long timeout=-1);
    void clear(void); //清空缓存
};

#endif //__YFIFO_SHM_H__
