//---------------------------------------------------------------------------
//
// yfifo.cpp    2000年6月12日
//
// 类YFIFO：提供对FIFO的支持，在WIN32用文件仿真
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#ifdef __WIN32__
  #include <windows.h>
  #include <io.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>
  #ifndef SEM_FAILED
    #define SEM_FAILED ((sem_t*)-1)
  #endif
#endif //__WIN32__

#include "yfifo.h"
#include "yerr.h"
#include "ylogfile.h"
#define MAX_FIFO_FILE_SIZE 16386
//---------------------------------------------------------------------------
//YFIFO构造函数
YFIFO::YFIFO(const YString& name, const YString& mode, int shm_size):
m_name(name),
m_mode(mode),
delim("\n-------##&*43fjiHH^*##--------"),
MAXLEN(0),
m_sem(SEM_FAILED),
m_shm_size(shm_size),
m_usedtime(0)
{
  //创建文件
/*  int handle;
  if((handle=creat(m_name.c_str(), 0666))==-1) {
	  g_applog->write("[YFIFO::YFIFO]creat file "+m_name+" failed.");
  }
  close(handle);
*/
	FILE* f=fopen(m_name.c_str(),"a");
	if(!f) g_applog->write("[YFIFO::YFIFO]creat file(fopen) "+m_name+" failed.");
	fclose(f);
	
	m_LastFileOffset=0;
		
  //创建信号灯
  #ifdef __USE_SEMAPHORE__
  m_sem=sem_open((m_name+".sem").c_str(),O_CREAT,0666,1);
  if(m_sem==SEM_FAILED) g_applog->write("[YFIFO::YFIFO]Semphore of "+m_name+" create failed.");
  #endif
  //创建共享内存
		//无共享内存版本
		m_HasSHM=false;
		return;
		//end of 无共享内存版本
	
	
	key_t key=ftok(m_name.c_str(),'Y');
	if(key==-1) {
		g_applog->write((YString)"[YFIFO::YFIFO]ftok error.("+sys_errlist[errno]+")");
		m_HasSHM=false;
		return;
	}
	
	m_shm_id=shmget(key,m_shm_size,IPC_CREAT|0666);
	if(m_shm_id==-1) {
		g_applog->write((YString)"[YFIFO::YFIFO]shmget error.("+sys_errlist[errno]+")");
		m_HasSHM=false;
		return;
	}
	
	m_shm_base=(unsigned char*)shmat(m_shm_id,NULL,0);
	if(m_shm_base==(unsigned char*)-1) {
		g_applog->write((YString)"[YFIFO::YFIFO]shmat error.("+sys_errlist[errno]+")");
		m_HasSHM=false;
		return;
	}
	m_HasSHM=true;
	m_pSign=m_shm_base;
	m_pBusy=m_pSign+2;
	m_pMemHasData=m_pBusy+1;
	m_pFileHasData=m_pMemHasData+1;
	m_pStart=(int*)(m_pFileHasData+1);
	m_pEnd=m_pStart+sizeof(int);
	m_pDataStart=(unsigned char*)(m_pEnd+sizeof(int));
	m_pDataEnd=m_shm_base+m_shm_size;
	m_shm_data_size=m_shm_size-(m_pDataStart-m_shm_base);
	if((*m_pSign=='y')&&(*(m_pSign+1)=='l')) { //有效共享内存
		//do nothing
	}
	else {
		*m_pSign='y';
		*(m_pSign+1)='l';
		*m_pBusy='f';
		*m_pMemHasData='f';
		*m_pFileHasData='f';
		*m_pStart=0;
		*m_pEnd=0;
	}
}
//---------------------------------------------------------------------------
//YFIFO析构函数
YFIFO::~YFIFO()
{
  //删除文件
#ifdef __WIN32__
 if(m_mode[0]=='r') _unlink(m_name.c_str());
#else //UNIX
 if(m_mode[0]=='r')  {
 	unlink(m_name.c_str());
  #ifdef __USE_SEMAPHORE__
  if(sem_close(m_sem)==0) {
  	//g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" close successfully.");
  }
  else g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" close failed.");
  if(sem_unlink((m_name+".sem").c_str())==0){
  	//g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" unlink successfully.");
  }
  else g_applog->write("[YFIFO::~YFIFO]Semphore of "+m_name+" unlink failed.");
  #endif
 //删除共享内存
 if(m_HasSHM && (shmctl(m_shm_id,IPC_RMID,NULL)!=0)) {
		g_applog->write((YString)"[YFIFO::YFIFO]共享内存无法删除.("+strerror(errno)+")");
 }
}
#endif //__WIN32__

}
//---------------------------------------------------------------------------
int YFIFO::write(YString s)
{
    #ifdef __USE_SEMAPHORE__
    if(m_sem!=SEM_FAILED) sem_wait(m_sem);
    #endif
	
  if(m_mode[0]=='w') {
		//先试图写共享内存
		int size=s.size();
		bool writeSuccess=false;
		if(m_HasSHM && (*m_pFileHasData=='f')) writeSuccess=writeshm(s);  //文件里没有数据，写入共享内存
		if(!writeSuccess) { //共享内存不足,或已经开始使用文件，写入文件
	    //g_applog->write("[YFIFO::write]共享内存不足,或已经开始使用文件，写入文件");
	    FILE* f=fopen(m_name.c_str(),"ab+");
	    if(!f) {
	      g_err.ErrDescription=YString("[YFIFO::write]open ")+m_name+" eror("+strerror(errno)+")";
	      g_applog->write(g_err.ErrDescription);
	      if(m_sem!=SEM_FAILED) sem_post(m_sem);
	      return -1;
	    }
	    //fseek(f,0L,SEEK_END);
			if(m_mode[1]=='d') { //加入有效标志和长度
				unsigned char buf[1+sizeof(int)];
				buf[0]='@'; //有效标志
				int* pSize=(int*)(buf+1);
				*pSize=size;
				fwrite(buf,1+sizeof(int),1,f);
			}
	    fwrite(s.c_str(),size,1,f);
	    fclose(f);
	    //g_applog->write("[YFIFO::write]write "+s+" to "+m_name);
	    if(m_HasSHM) *m_pFileHasData='t';
	  } //endif 共享内存不足,或已经开始使用文件，写入文件
  }
  #ifdef __USE_SEMAPHORE__
  if(m_sem!=SEM_FAILED) sem_post(m_sem);
  #endif
  return 0;
}
//---------------------------------------------------------------------------
bool YFIFO::writeshm(const YString& s)
{
	//计算剩余的共享内存
	int free_shm;
	if(*m_pMemHasData=='t') {
		if(*m_pStart<*m_pEnd) {
			free_shm=m_shm_data_size-(*m_pEnd-*m_pStart);
		}
		else {
			free_shm=*m_pStart-*m_pEnd;
		}
	}
	else {
		free_shm=m_shm_data_size;
	}
	int size=s.size();
	if(((m_mode[1]=='d')&&((size+3)<=free_shm)) ||
	   ((m_mode[1]=='s')&&(size<=free_shm))) {  //共享内存足够,写入共享内存
		if(m_mode[1]=='d') { //加入有效标志和长度
			*(m_pDataStart+*m_pEnd)='@'; //有效标志
			(*m_pEnd)++;
			if(*m_pEnd==m_shm_data_size) *m_pEnd=0;
			*(m_pDataStart+*m_pEnd)=(unsigned char)(size%256);
			(*m_pEnd)++;
			if(*m_pEnd==m_shm_data_size) *m_pEnd=0;
			*(m_pDataStart+*m_pEnd)=(unsigned char)(size/256);
			(*m_pEnd)++;
			if(*m_pEnd==m_shm_data_size) *m_pEnd=0;
		}
		if(m_shm_data_size-*m_pEnd>=size) {
			memcpy(m_pDataStart+*m_pEnd, s.c_str(), size);
			(*m_pEnd)+=size;
			if(*m_pEnd==m_shm_data_size) *m_pEnd=0;
		}
		else {
			memcpy(m_pDataStart+*m_pEnd, s.c_str(), m_shm_data_size-*m_pEnd);
			memcpy(m_pDataStart, s.c_str()+(m_shm_data_size-*m_pEnd), size-(m_shm_data_size-*m_pEnd));
			*m_pEnd=size-(m_shm_data_size-*m_pEnd);
			if(*m_pEnd==m_shm_data_size) *m_pEnd=0;
		}
		*m_pMemHasData='t';
		return true;
	}
	else return false;
}
//---------------------------------------------------------------------------
YString YFIFO::read(int maxlen, unsigned long timeout)
{
	YString s;
	while(true) {
		#ifdef __USE_SEMAPHORE__
		if(m_sem!=SEM_FAILED) sem_wait(m_sem);
		#endif
		if((s=readOnce())!="") break;
		#ifdef __USE_SEMAPHORE__
		if(m_sem!=SEM_FAILED) sem_post(m_sem);
		#endif
    unsigned long t=rand()%1000;
    m_usedtime+=t;
    if((timeout!=-1)&&(m_usedtime>timeout)) break;
		usleep(t);
	}
  if(m_sem!=SEM_FAILED) sem_post(m_sem);
  m_usedtime=0;
  return s;
}
//---------------------------------------------------------------------------
YString YFIFO::readOnce(void)
{
	if(!m_HasSHM) return readFromFile();
	
	if(m_HasSHM && (*m_pMemHasData=='f')&&(*m_pFileHasData=='f')) return ""; //没有数据
	
	if(m_HasSHM && (*m_pMemHasData=='f')&&(*m_pFileHasData=='t')) {
	      //如果内存中没有数据，而文件里有，则将文件中的数据读入内存
		YString s=readFromFile();
		if(s!="") return s;
	}//end if 内存中没有数据，而文件里有

	//从共享内存里读数据
  if(m_HasSHM) {
  	if(*m_pMemHasData=='t') {
  		YString s;
  		char *buf;
  		if(m_mode[1]=='d'){ //分段数据
  			if(*(m_pDataStart+*m_pStart)!='@') {
  				g_applog->write("[YFIFO::readOnce]共享内存数据标志不正确。");
  				*m_pStart=0;
  				*m_pEnd=0;
  				*m_pMemHasData='f';
  				return "";
  			}
  			bool flip=(*m_pStart>=*m_pEnd)?true:false;
  			int size;
  			(*m_pStart)++;
  			if(*m_pStart==m_shm_data_size) { //过边界
  				*m_pStart=0;
  				flip=true;
  			}
  			size=*(m_pDataStart+*m_pStart);
  			(*m_pStart)++;
  			if(*m_pStart==m_shm_data_size) { //过边界
  				*m_pStart=0;
  				flip=true;
  			}
  			size+=(*(m_pDataStart+*m_pStart))*256;
  			(*m_pStart)++;
  			if(*m_pStart==m_shm_data_size) { //过边界
  				*m_pStart=0;
  				flip=true;
  			}
  			buf=(char*)malloc(size+1);
  			if(!buf) {
  				g_applog->write("[YFIFO::readOnce]内存不足");
  				exit(-1);
  			}
  			if(*m_pStart+size>m_shm_data_size) { //过边界
  				int n=m_shm_data_size-*m_pStart;
  				memcpy(buf, m_pDataStart+*m_pStart, n);
  				memcpy(buf+n, m_pDataStart, size-n);
  				*m_pStart=size-n;
  				flip=true;
  			}
  			else { //没过边界
  				memcpy(buf, m_pDataStart+*m_pStart, size);
  				*m_pStart+=size;
  			}
  			if(flip&&(*m_pStart>=*m_pEnd)) *m_pMemHasData='f'; //没数据了
  			buf[size]='\0';
  		}//endif 分段数据
  		else if(m_mode[1]=='s'){ //流数据,一次取光
  			int size;
  			if(*m_pEnd>=*m_pStart) { //没过边界
  				size=*m_pEnd-*m_pStart;
  				buf=(char*)malloc(size+1);
  				if(!buf) {
  					g_applog->write("[YFIFO::readOnce]内存不足");
  					exit(-1);
  				}
  				memcpy(buf, m_pDataStart+*m_pStart, size);
  				buf[size]='\0';
  			}
  			else { //过边界
  				size=m_shm_data_size-(*m_pStart-*m_pEnd);
  				buf=(char*)malloc(size+1);
  				if(!buf) {
  					g_applog->write("[YFIFO::readOnce]内存不足");
  					exit(-1);
  				}
  				memcpy(buf, m_pDataStart+*m_pStart, m_shm_data_size-*m_pStart);
  				memcpy(buf+m_shm_data_size-*m_pStart, m_pDataStart, *m_pEnd);
  				buf[size]='\0';
  			}
  			*m_pEnd=*m_pStart=0;
  			*m_pMemHasData='f'; //没数据了
  		}//endif 流数据
  		s=buf;
  		free(buf);
  		return s;	
  	}
  } //endif(m_HasSHM)
	return "";
}
//---------------------------------------------------------------------------
//从文件中读出送入\共享内存,返回"",如果不能写入共享内存,返回所取得的字符串
YString YFIFO::readFromFile(void)
{
  struct stat statbuf;
 	bool bFileHasData=true;
 	if(stat(m_name.c_str(), &statbuf)!=0) {
 		g_applog->write("[YFIFO::read]文件中有数据，但stat()出错。("+m_name+")");
 		if(m_HasSHM) *m_pFileHasData='f';
 		bFileHasData=false;
 		if(m_HasSHM) *m_pBusy='f';
 		return "";
 	}
 	//g_applog->write("[YFIFO::read]statbuf.st_size="+(YString)statbuf.st_size+" m_LastFileOffset="+(YString)m_LastFileOffset);
 	if(statbuf.st_size>m_LastFileOffset) { //文件中确实有新数据，读取到内存
 		//g_applog->write("[YFIFO::read]文件中确实有新数据，读取到内存。("+m_name+")");
 		FILE* f=fopen(m_name.c_str(),"rb");
    if(!f) { //文件没有正确打开
      g_applog->write("[YFIFO::readFromFile]文件"+m_name+"打不开!("+strerror(errno)+")");
      return "";
    }
 		fseek(f,m_LastFileOffset,SEEK_SET);
 		YString s;
 		if(m_mode[1]=='d') {  //分段数据
 			unsigned char buf[1+sizeof(int)];
 			bool first=true;
			while(true) { //逐条取数据
 			
  			fread(buf,1+sizeof(int),1,f);
  			m_LastFileOffset+=1+sizeof(int);
  			if(buf[0]!='@') { //有效标志不正确，
  				g_applog->write("[YFIFO::read]文件中有效标志不正确。("+m_name+")");
  				creat(m_name.c_str(), 0666); //清空文件
  				if(m_HasSHM) *m_pFileHasData='f';
  				bFileHasData=false;
  				m_LastFileOffset=0;
  				fclose(f);
  				return "";
  			}
  			int* pSize=(int*)(buf+1);
  			char* buf1=(char*)malloc(*pSize+1);
  			if(!buf1) {
  				g_applog->write("[YFIFO::readOnce]内存不足");
  				exit(-1);
  			}
  			fread(buf1,*pSize,1,f);
  			m_LastFileOffset+=*pSize;
  			//g_applog->write("[YFIFO::read]statbuf.st_size="+(YString)statbuf.st_size+" m_LastFileOffset="+(YString)m_LastFileOffset);
  			if(m_LastFileOffset>=statbuf.st_size) {    //文件中已经没有数据
  				if(m_HasSHM) *m_pFileHasData='f';
  				bFileHasData=false;
  			}
  			buf1[*pSize]='\0';
  			s=buf1;
 				bool writeSuccess=m_HasSHM? writeshm(s):false;
 				if(!writeSuccess) {
 					if(first||(!m_HasSHM)) {
 						free(buf1);
 						fclose(f);
      			if((!bFileHasData)&&(m_LastFileOffset>MAX_FIFO_FILE_SIZE)) {
      				creat(m_name.c_str(), 0666); //清空文件
      				m_LastFileOffset=0;
      			}
 						return s;
 					}
 					else {
 						m_LastFileOffset-=(*pSize+1+sizeof(int));
 						free(buf1);
  					fclose(f);
 						break;
 					}
 				}
  			if((!bFileHasData)&&(m_LastFileOffset>MAX_FIFO_FILE_SIZE)) {
  				creat(m_name.c_str(), 0666); //清空文件
  				m_LastFileOffset=0;
  			}
 				free(buf1);
  			first=false;
  		} //end while 逐条取数据
 		}//end if 分段数据
 		else if(m_mode[1]=='s'){ //流数据
 			int size=statbuf.st_size-m_LastFileOffset;
 			char* buf1=(char*)malloc(size+1);
 			if(!buf1) {
 				g_applog->write("[YFIFO::readOnce]内存不足");
 				exit(-1);
 			}
 			fread(buf1,size,1,f);
 			m_LastFileOffset+=size;
 			//g_applog->write("[YFIFO::read]statbuf.st_size="+(YString)statbuf.st_size+" m_LastFileOffset="+(YString)m_LastFileOffset);
 			if(m_LastFileOffset>=statbuf.st_size) {  //文件中已经没有数据
 				if(m_HasSHM) *m_pFileHasData='f';
 				bFileHasData=false;
 			}
  		if((!bFileHasData)&&(m_LastFileOffset>MAX_FIFO_FILE_SIZE)) {
  			creat(m_name.c_str(), 0666); //清空文件
  			m_LastFileOffset=0;
  		}
 			buf1[size]='\0';
 			s=buf1;
 			free(buf1);
 		}//end if 流数据
 		fclose(f);
 		return s;
 	}//end if 文件中确实有新数据
  else if(m_LastFileOffset-statbuf.st_size>10) { //文件被trunc过，表明有程序接管
    YString retS="<script>top.window.close()</script>";
    return retS;
  }
 	else { //文件中并没有新数据
 		//g_applog->write("[YFIFO::read]文件中并没有新数据。("+m_name+")");
 		if(m_HasSHM) *m_pFileHasData='f';
 		return "";
 	}
}
//---------------------------------------------------------------------------
void YFIFO::clear(void)
{
  //实现不完全，没有考虑共享内存的版本 ！！！！！！！！！
  #ifdef __WIN32__
    _unlink(m_name.c_str());
  #else
    unlink(m_name.c_str());
  #endif
}
