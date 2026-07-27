//Ìæ»»È«¾ÖµÄnew¡¢delete¡¢malloc()¡¢free()

#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#include "yalloc.h"

using namespace std;

void* operator new(size_t sz) {
  return yalloc(sz);
}

void operator delete(void* m) {
  yfree(m);
}

void* malloc(size_t size) {
	return yalloc(size);
}

void free(void* ptr) {
	return yfree(ptr);
}

void* realloc(void* ptr, size_t size)
{
	return yralloc(ptr,size);
}

void* valloc(size_t size)
{
	return yvalloc(size);
}
