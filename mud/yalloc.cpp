//提供malloc()/free()的替代

#ifndef YALLOC_MEM_FILE
	#define YALLOC_MEM_FILE "/home/newmud/memfile"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <mmalloc.h>
#include <iostream.h>

void* _yalloc_mem_descriptor=NULL;

//-------------------------------------------------------------------------------
void _yalloc_init(void)
{
	static bool running=false; //防止重入
	if(running) {
		printf("[_yalloc_init]running\n");
		return;
	}
	running=true;
	int fd=open(YALLOC_MEM_FILE,O_RDWR|O_CREAT);
	if(fd<0) {
		cerr<<"不能打开"<<YALLOC_MEM_FILE<<endl;
		perror("");
		exit(-1);
	}

	_yalloc_mem_descriptor=mmalloc_attach(fd, NULL);
	if(_yalloc_mem_descriptor==NULL) {
		perror("mmalloc_attach()失败");
		exit(-1);
	}
	running=false;
	//close(fd);
}
//-------------------------------------------------------------------------------
void* yalloc(size_t size)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yalloc]running\n");
	}
	running=true;

	if(_yalloc_mem_descriptor==NULL) _yalloc_init();

	void* p=mmalloc(_yalloc_mem_descriptor,size);
	if(p) cout<<"成功申请"<<size<<"byte内存."<<endl;
	else cout<<"申请"<<size<<"byte内存失败."<<endl;

	running=false;
	
	return p;
}
//-------------------------------------------------------------------------------
void yfree(void* ptr)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yfree]running\n");
	}
	running=true;
	
	if(_yalloc_mem_descriptor==NULL) _yalloc_init();
	mfree(_yalloc_mem_descriptor,ptr);
	
	running=false;
}
//-------------------------------------------------------------------------------
void yalloc_setkey(int keyNo, void* key)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yalloc_setkey]running\n");
	}
	running=true;
	
	mmalloc_setkey(_yalloc_mem_descriptor,keyNo,key);
	
	running=false;
}
//-------------------------------------------------------------------------------
void* yalloc_getkey(int keyNo)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yfree]running\n");
	}
	running=true;
	
	void* p=mmalloc_getkey(_yalloc_mem_descriptor,keyNo);
	
	running=false;
	
	return p;
}
//-------------------------------------------------------------------------------
void* yrealloc(void* ptr, size_t size)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yrealloc]running\n");
	}
	running=true;
	
	if(_yalloc_mem_descriptor==NULL) _yalloc_init();

	void* p=mmralloc(_yalloc_mem_descriptor,ptr,size);
	if(p) cout<<"成功改变申请"<<size<<"byte内存(yrealloc)."<<endl;
	else cout<<"改变申请"<<size<<"byte内存失败(yrealloc)."<<endl;
	
	running=false;
	
	return p;
}
//-------------------------------------------------------------------------------
void* yvalloc(size_t size)
{
	static bool running=false; //防止重入
	while(running) {
		printf("[yrealloc]running\n");
	}
	running=true;
	
	if(_yalloc_mem_descriptor==NULL) _yalloc_init();

	void* p=mmvalloc(_yalloc_mem_descriptor,size);
	if(p) cout<<"成功申请"<<size<<"byte内存(yvalloc)."<<endl;
	else cout<<"申请"<<size<<"byte内存失败(yalloc)."<<endl;
	
	running=false;
	
	return p;
}
