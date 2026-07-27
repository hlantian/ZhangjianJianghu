//---------------------------------------------------------------------------
//
// ymudobject.cpp    2000年6月8日
//
// 类YMUDObject：所有物体的基类
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"
using namespace std;
//----------------------------------------------------------------
//属性(写)：SmallTime
void YMUDObject::setSmallTime(int newSmallTime)
{
  TRACE_FUNC0(setSmallTime);
  m_Timer->setInterval(newSmallTime);
}
//----------------------------------------------------------------
//属性(读)：SmallTime
int YMUDObject::getSmallTime(void)
{
  TRACE_FUNC0(getSmallTime);
  return m_Timer->getInterval();
}
//----------------------------------------------------------------
//事件BeforeChildAdd的默认处理函数
int YMUDObject::onBeforeChildAdd(YMUDObject* sender, YMUDObject* child)
{
  TRACE_FUNC0(onBeforeChildAdd);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterChildAdd的默认处理函数
int YMUDObject::onAfterChildAdd(YMUDObject* sender, YMUDObject* child)
{
  TRACE_FUNC0(onAfterChildAdd);
  child->setOwner(this);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件BeforeChildRemove的默认处理函数
int YMUDObject::onBeforeChildRemove(YMUDObject* sender, YMUDObject* child)
{
  TRACE_FUNC0(onBeforeChildRemove);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterChildRemove的默认处理函数
int YMUDObject::onAfterChildRemove(YMUDObject* sender, YMUDObject* child)
{
  TRACE_FUNC0(onAfterChildRemove);
  if(getOwner()) child->setOwner(getOwner());
  else child->setOwner(g_GrandpaRoom);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件BeforePropertyChange的默认处理函数
int YMUDObject::onBeforePropertyChange(YMUDObject* sender, YString Property,
                                        long oldValue, long newValue)
{
  TRACE_FUNC0(onBeforePropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件BeforePropertyChange的默认处理函数
int YMUDObject::onBeforePropertyChange(YMUDObject* sender, YString Property,
                                        float oldValue, float newValue)
{
  TRACE_FUNC0(onBeforePropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件BeforePropertyChange的默认处理函数
int YMUDObject::onBeforePropertyChange(YMUDObject* sender, YString Property,
                                        YString oldValue, YString newValue)
{
  TRACE_FUNC0(onBeforePropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterPropertyChange的默认处理函数
int YMUDObject::onAfterPropertyChange(YMUDObject* sender, YString Property,
                                        long oldValue, long newValue)
{
  TRACE_FUNC0(onAfterPropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterPropertyChange的默认处理函数
int YMUDObject::onAfterPropertyChange(YMUDObject* sender, YString Property,
                                        float oldValue, float newValue)
{
  TRACE_FUNC0(onAfterPropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterPropertyChange的默认处理函数
int YMUDObject::onAfterPropertyChange(YMUDObject* sender, YString Property,
                                        YString oldValue, YString newValue)
{
  TRACE_FUNC0(onAfterPropertyChange);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件Init的默认处理函数
int YMUDObject::onInit(void)
{
  TRACE_FUNC0(onInit);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件Destroy的默认处理函数
int YMUDObject::onDestroy(void)
{
  TRACE_FUNC0(onDestroy);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件Timer的默认处理函数
int YMUDObject::onTimer(void)
{
  TRACE_FUNC0(onTimer);
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件AfterLoad的默认处理函数
int YMUDObject::onAfterLoad(void)
{
  setObjectName(getAsString("名字"));
	return 1; //必须返回1，表示处理结束
}
//----------------------------------------------------------------
//事件BeforeSave的默认处理函数
int YMUDObject::onBeforeSave(void)
{
  set("名字",getObjectName());
	return 1; //必须返回1，表示处理结束
}
//--------------------------------------------------------
//方法isTypeOf--是否是某种类型或其派生类型
int YMUDObject::isTypeOf(YString className)
{
  if(className=="YMUDObject") return 1;
  else return 0;
}
//--------------------------------------------------------
//读属性DataFileName (全路径)
YString YMUDObject::getFullDataFileName(void)
{
  return g_Settings->getRootPath()+g_Settings->getPathSeparator()+PATH(m_DataFileName)+".profile";
}
//--------------------------------------------------------
//方法save--属性保存到文件
int YMUDObject::save(YString filename)
{
  onBeforeSave();
  //不保存YPlayer及其派生类型<--保存，在YRoom中才不保存
  if(filename!="") setDataFileName(filename);
  ofstream out(getFullDataFileName().c_str(), ios::out);
  if(!out.is_open()) {
    YErr::show("[YMUDObject::save]文件"+getFullDataFileName()+"打不开。");
	return -1;
  }
  else {
    out<<"#class="<<getRuntimeClass()<<"\n";
    m_Properties->save(out);
    m_Children->save(out);
    out.close();
  }
  return 1;
}
//--------------------------------------------------------
//方法load--从文件中读取属性
int YMUDObject::load(YString filename)
{
  m_LoadOK=true;
  setDataFileName(filename);
  ifstream in(getFullDataFileName().c_str(), ios::in);
  if(!in.is_open()) {
    YErr::show("[YMUDObject::load]文件"+getFullDataFileName()+"打不开。");
	return -1;
  }
  else {
    m_Properties->load(in);
    if(m_Children->load(in)<0) m_LoadOK=false;
    in.close();
  }
  int maxx=g_Settings->getsitMaxX();//getAsLong("max_x");
  int maxy=g_Settings->getsitMaxY();//getAsLong("max_y");
  int minx=g_Settings->getsitMinX();//getAsLong("min_x");
  int miny=g_Settings->getsitMinY();//getAsLong("min_y");
  if(getAsLong("X")!=0) setX(getAsLong("X"));
  else setX(rand()%(maxx-minx)+minx+1);
  if(getAsLong("Y")!=0) setY(getAsLong("Y"));
  else setY(rand()%(maxy-miny)+miny+1);
  onInit();
  this->onAfterLoad();
  return 1;
}
//--------------------------------------------------------
//方法reload--重新从文件中读取属性
int YMUDObject::reload(void)
{
  m_LoadOK=true;
  ifstream in(getFullDataFileName().c_str(), ios::in);
  if(!in.is_open()) {
    YErr::show("[YMUDObject::reload]文件"+getFullDataFileName()+"打不开。");
	return -1;
  }
  else {
    m_Properties->reload(in);
    if(m_Children->reload(in)<0) m_LoadOK=false;
    in.close();
  }
  onAfterLoad();
  return 1;
}
//--------------------------------------------------------
//方法init--初始化
int YMUDObject::init()
{
  if(this!=g_GrandpaRoom) m_Owner=g_GrandpaRoom;
  else m_Owner=NULL;
  m_Timer=new YTimer(this);
  m_Children=new YObjectGroup(this);
  m_Properties=new YPropertyGroup(this);
  m_Properties->set("名字","");
  return 1;
}
//--------------------------------------------------------
//构造函数
YMUDObject::YMUDObject(YString initFileName)
:m_X(1),m_Y(1),m_DataFileName(initFileName),m_ObjectName(""),m_LoadOK(false)
{
  init();
  if(initFileName!="") load(initFileName);
  set("datafilename",getDataFileName());
  onInit();
}
//--------------------------------------------------------
//析构函数
YMUDObject::~YMUDObject()
{
  //从所有所属的组中退出
  list<YObjectGroup*>::iterator it=m_OwnerGroups.begin();
  while(it!=m_OwnerGroups.end()) {
    (*it)->_bare_remove(this);
    it++;
  }

  delete m_Timer;
  if(m_Children) {
    m_Children->destoryAll();
    delete m_Children;
  }
  delete m_Properties;
}
//--------------------------------------------------------
//添加该Object所加入的组
void YMUDObject::addOwnerGroup(YObjectGroup* group)
{
  list<YObjectGroup*>::iterator it=m_OwnerGroups.begin();
  while(it!=m_OwnerGroups.end()) {
    if((*it)==group) return;
    it++;
  }
  m_OwnerGroups.push_back(group);
}
//--------------------------------------------------------
//删除该Object所加入的组
void YMUDObject::removeOwnerGroup(YObjectGroup* group)
{
  m_OwnerGroups.remove(group);
}
//--------------------------------------------------------
//属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
YString YMUDObject::getDisplayName(void)
{
  YString name=getObjectName();//getAsString("名字");
  return YString("<a href='javascript:object('")+name+"')'>"+name+"</a>";
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDObject::set(YString name, float value)
{
  m_Properties->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDObject::set(YString name, long value)
{
  m_Properties->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
void YMUDObject::set(YString name, YString value)
{
  m_Properties->set(name,value);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
long YMUDObject::getAsLong(YString name)
{
  return m_Properties->getAsLong(name);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
float YMUDObject::getAsFloat(YString name)
{
  return m_Properties->getAsFloat(name);
}
//--------------------------------------------------------
//存取属性(map到YPropertyGroup)
YString YMUDObject::getAsString(YString name)
{
  return m_Properties->getAsString(name);
}
//--------------------------------------------------------
//查找具有特定属性的子物体(map到YObjectGroup)
YMUDObject* YMUDObject::findChild(YString propertyName, YString propertyValue, YString className)
{
  return m_Children->find(propertyName,propertyValue,className);
}
//--------------------------------------------------------
//查找具有特定属性的子物体(map到YObjectGroup)
YMUDObject* YMUDObject::findChild(YString propertyName, long propertyValue, YString className)
{
  return m_Children->find(propertyName,propertyValue,className);
}
//--------------------------------------------------------
//查找具有特定属性的子物体(map到YObjectGroup)
YMUDObject* YMUDObject::findChild(YString propertyName, float propertyValue, YString className)
{
  return m_Children->find(propertyName,propertyValue,className);
}
//--------------------------------------------------------
//查找名字为name子物体
YMUDObject* YMUDObject::findChild(YString name, YString className)
{
  return findChild("名字",name,className);
}
//--------------------------------------------------------
//查找名字为name子物体(Actor)
YAbstractActor* YMUDObject::findChildActor(YString name)
{
  return (YAbstractActor*)m_Children->findWithName(name,"YAbstractActor");
  //return (YAbstractActor*)findChild("名字",name,"YAbstractActor");
}
//--------------------------------------------------------
//查找名字为name子物体(Room)
YAbstractRoom* YMUDObject::findChildRoom(YString name)
{
  return (YAbstractRoom*)m_Children->findWithName(name,"YAbstractRoom");
  //return (YAbstractRoom*)findChild("名字",name,"YAbstractRoom");
}
//--------------------------------------------------------
//查找名字为name子物体(Thing)
YAbstractThing* YMUDObject::findChildThing(YString name)
{
  return (YAbstractThing*)(m_Children->findWithName(name,"YAbstractThing"));
  //return (YAbstractThing*)findChild("名字",name,"YAbstractThing");
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildren(YString propertyName, YString propertyValue, YString className)
{
  return m_Children->enumChildren(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildren(YString propertyName, long propertyValue, YString className)
{
  return m_Children->enumChildren(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildren(YString propertyName, float propertyValue, YString className)
{
  return m_Children->enumChildren(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表)(用于显示在页面上)(propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildrenForDisplay(YString propertyName, YString propertyValue, YString className)
{
  return m_Children->enumChildrenForDisplay(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表)(用于显示在页面上)(propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildrenForDisplay(YString propertyName, long propertyValue, YString className)
{
  return m_Children->enumChildrenForDisplay(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表)(用于显示在页面上)(propertyName==""代表任何属性值)
//(map到YObjectGroup)
YString YMUDObject::enumChildrenForDisplay(YString propertyName, float propertyValue, YString className)
{
  return m_Children->enumChildrenForDisplay(propertyName, propertyValue, className);
}
//--------------------------------------------------------
//将子物体传给另一物体
#ifndef __OUT_OF_WEBMUD__
bool YMUDObject::giveChildTo(YMUDObject* child, YMUDObject* another, long count, long No)
{
  if((!child) || (!another)) return false;
  int thing_type; //0,1,2-type of YAbstractThing; 1000-another
  if(child->isTypeOf("YAbstractThing")) thing_type=((YAbstractThing*)child)->getThingType();
  else thing_type=1000;

  if(count==0) return false; //数量为零表示什么都没给
  if(count<0) return false;
  if(!m_Children->find(child)) return false;  //chile不是自己的子物体
  if((count==1) && (thing_type>1)) {
    if(m_Children->remove(child)) {
      if(another->getChildren()->add(child)) {
        return true;
      }
      else {
        m_Children->_add(child); //送回去
        return false;
      }
    }
    else return false;
  }
  else if(thing_type<=1) {  //0-same-1-sameButOne
    if((thing_type==1)&&((count!=1)||(No<1)||(No>count))) {
      return false; //对于,count必须等于1,而且No必须在1~count之间
    }
    //No--; //No在1~count之间,而list下标是从0开始 <--yabstractthing里已处理减1问题
    YAbstractThing *thing1, *thing2;
    thing1=(YAbstractThing*)child;
    long count1=thing1->getCount();
    if(count1<count) return false; //不够
    else {
      thing2=(YAbstractThing*)another->findChildThing(thing1->getObjectName());//getAsString("名字"));
      if(!thing2) {    //对方没有此物体
        thing2=(YAbstractThing*)thing1->clone();
        if(another->getChildren()->add(thing2)) { //添加成功
          if(thing_type==0) {   //same
            thing1->setCount(count1-count);
            thing2->setCount(count);
          }
          else { //thing_type==1, SameButOne
            thing2->addOne(thing1->getVarientValue(No));
            thing1->deleteOne(No);
          }
        }
        else {  //对方不允许添加
          delete thing2;
          return false;
        }
      }
      else {   //对方有此物体
        if(thing_type==0) {   //same
          thing1->setCount(count1-count);
          thing2->setCount(thing2->getCount()+count);
        }
        else { //thing_type==1, SameButOne
          thing2->addOne(thing1->getVarientValue(No));
          thing1->deleteOne(No);
        }
      }
      if(thing1->getCount()==0) { //该物体计数为零，应删除
        if(m_Children->remove(child)) { //成功删除thing1
          delete child;
          return true;
        }
        else {   //不允许删除thing1
          if(thing_type==0) {   //same
            thing2->setCount(thing2->getCount()-count);
            thing1->setCount(count);
          }
          else { //thing_type==1, SameButOne
            thing1->addOne(thing2->getVarientValue(thing2->getCount()));
            thing2->deleteOne(thing2->getCount());
          }
          if(thing2->getCount()==0) {
            another->getChildren()->_remove(thing2);
            delete thing2;
          }
        }
      }
      return true;
    }
  }
  else return false;  //count!=1而且不是YAbstractThing
}
//--------------------------------------------------------
//增加子物体(map到YObjectGroup)
bool YMUDObject::addChild(YMUDObject* child)
{
  if(child) child->setOwner(this);//在OnAfterChildAdd中也有设置Owner,这儿多放一个保险
  return m_Children->add(child);
}
//--------------------------------------------------------
//移除子物体(map到YObjectGroup)
bool YMUDObject::removeChild(YMUDObject* child)
{
  if(child) {
    if(getOwner()) child->setOwner(getOwner());
    else child->setOwner(g_GrandpaRoom);
  }
  return m_Children->remove(child);
}
//--------------------------------------------------------
//删除并销毁所有子物体
void YMUDObject::destoryAllChild(void)
{
  m_Children->destoryAll();
}
//--------------------------------------------------------
//删除所有属性
void YMUDObject::removeAllProperties(void)
{
  m_Properties->removeAll();
}
//--------------------------------------------------------
//复制本身
YMUDObject* YMUDObject::clone(void)
{
  YMUDObject* another=loadObject(getRuntimeClass(),"");
  if(!another) return another;
  m_Children->copyTo(another->m_Children);
  m_Properties->copyTo(another->m_Properties);

  another->m_DataFileName=m_DataFileName;
  another->m_initalized=m_initalized;
  another->m_Owner=m_Owner;
  another->m_X=m_X;
  another->m_Y=m_Y;

  return another;
}
//--------------------------------------------------------
//关闭计时器
void YMUDObject::disableTimer(void)
{
  m_Timer->disable();
}
#endif //__OUT_OF_WEBMUD__
