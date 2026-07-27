//---------------------------------------------------------------------------
//
// ymap.h    2000年6月12日
//
// 类YMap：提供Room的加载、释放、检索等功能
//         Room在有Player进入时方加载到内存，长时间没有Player时将释放掉
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YMAP_H__
#define __YMAP_H__

#include <map>
#include "ystring.h"
#include "yabstractroom.h"

class YMap {
  private:
    map<YString, YAbstractRoom*, less<YString> >m_roomgroup;
    //room是否已经加载
    inline bool isLoaded(YString roomname);
    YAbstractRoom* loadRoom(YString roomname);
    YAbstractRoom* m_DefaultRoom;
    YString getRoomDataFileName(YString roomname);
  public:
		YMap();  //构造函数
		~YMap(); //析构函数
    //返回roomname指定的room对象，没找到返回NULL
    YAbstractRoom* getRoom(YString roomname, YAbstractRoom* currentRoom);
};

#endif //__YMAP_H__
