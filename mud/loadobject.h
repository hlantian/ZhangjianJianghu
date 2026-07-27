//---------------------------------------------------------------------------
//
// loadobject.h    2000年6月12日
//
// 函数loadobject：根据类名建立不同的对象，返回YMUDObject指针
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __LOADOBJECT_H__
#define __LOADOBJECT_H__

#include "ymudobject.h"
#include "ystring.h"

YMUDObject* loadObject(YString datafilename="");
YMUDObject* loadObject(YString classname, YString datafilename);

#endif //__LOADOBJECT_H__
