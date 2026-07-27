//---------------------------------------------------------------------------
//
// ymap.cpp    2000年6月12日
//
// 类YMap：提供Room的加载、释放、检索等功能
//         Room在有Player进入时方加载到内存，长时间没有Player时将释放掉
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YMap构造函数
YMap::YMap():m_DefaultRoom(NULL)
{
  loadRoom(g_Settings->getFistComrIn());//getAsString("初始房间"));
  m_DefaultRoom=loadRoom("/room/defaultroom");
}
//---------------------------------------------------------------------------
//YMap析构函数
YMap::~YMap()
{
}
//---------------------------------------------------------------------------
//返回roomname指定的room对象，没找到返回NULL
YAbstractRoom* YMap::getRoom(YString roomname, YAbstractRoom* currentRoom)
{
  roomname=PATH(roomname);
  char sep=g_Settings->getPathSeparator()[0];
  if(roomname[0]==sep) { //绝对路径
    roomname.erase(0,1); //去掉'/'
  }
  else if(currentRoom) { //相对路径且currentRoom不为NULL
    YString currentdir=currentRoom->getDataFileName();
    int pos=currentdir.find_last_of(g_Settings->getPathSeparator());
    if(pos==currentdir.size()) currentdir="";
    else currentdir.erase(pos+1);
    roomname=currentdir+roomname;
  }

  if(isLoaded(roomname)) return m_roomgroup[roomname];
  else return loadRoom(roomname);
}
//---------------------------------------------------------------------------
YAbstractRoom* YMap::loadRoom(YString name)
{
  YMUDObject* room;
  room=loadObject(name);
  if(!room) { //简单的错误处理，使用YRoom类代替具体的类
    YErr::show("[YMap::loadRoom]Room "+name+" not loaded, Default Room class loaded.\n");
    room=m_DefaultRoom;
  }
  else if(!room->isTypeOf("YRoom")) { //简单的错误处理，使用YRoom类代替具体的类
    YErr::show("[YMap::loadRoom]No class infomation("+name+"), Default Room class loaded.\n");
    room=m_DefaultRoom;
  }

  m_roomgroup[name]=(YAbstractRoom*)room; //加入用户组

  //设置每一个Actor的room属性
  YObjectGroup::obj_iter it=room->getChildren()->begin();
  while(it!=room->getChildren()->end()) {
    if((*it)->isTypeOf("YAbstractActor"))
      ((YAbstractActor*)(*it))->setRoom((YAbstractRoom*)room);
    it++;
  }

  return (YAbstractRoom*)room;
}
//---------------------------------------------------------------------------
//room是否已经加载
bool YMap::isLoaded(YString roomname)
{
  return m_roomgroup.find(roomname)!=m_roomgroup.end();
}
//---------------------------------------------------------------------------
//返回room数据文件名
YString YMap::getRoomDataFileName(YString roomname)
{
   return g_Settings->getRoomPath()
          +g_Settings->getPathSeparator()
          +roomname+".profile";
}


