
#ifndef __YALLOC_H__
#define __YALLOC_H__

void _yalloc_init(void);
void* yalloc(size_t size);
void yfree(void* ptr);
void yalloc_setkey(int keyNo, void* key);
void* yalloc_getkey(int keyNo);
void* yrealloc(void* ptr, size_t size);
void* yvalloc(size_t size);

#endif //__YALLOC_H__
