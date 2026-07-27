//---------------------------------------------------------------------------
//
// yobjectgroup.cpp    2000年6月12日
//
// 类YObjectGroup：物体集合，提供动态物体集，检索
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YObjectGroup构造函数
YObjectGroup::YObjectGroup(YMUDObject* owner) : m_Owner(owner)
{

}
//---------------------------------------------------------------------------
//YObjectGroup析构函数
YObjectGroup::~YObjectGroup()
{
}
//---------------------------------------------------------------------------
bool YObjectGroup::add(YMUDObject* obj)
{
  if(!obj) {
    g_err.show("[YObjectGroup::add]Add NULL child.");
    return false;
  }
  if(find(obj)) {
    g_err.show("[YObjectGroup::add]Add child "+obj->getDataFileName()+" twice.");
    return true;
  }
  if(m_Owner) {
    if(m_Owner->onBeforeChildAdd(m_Owner, obj)) {
   YString tempname =  obj->getDataFileName();
      group.push_back(obj);
      obj->addOwnerGroup(this);
      m_Owner->onAfterChildAdd(m_Owner, obj);
      return true;
    }
    else return false;
  }
  else {
    group.push_back(obj);
    obj->addOwnerGroup(this);
    return true;
  }
}
//---------------------------------------------------------------------------
bool YObjectGroup::remove(YMUDObject* obj)
{
  if(!obj) {
    g_err.show("[YObjectGroup::remove]Remove NULL child.");
    return false;
  }

  if(m_Owner) {
    if(m_Owner->onBeforeChildRemove(m_Owner, obj)) {
      group.remove(obj);
      obj->removeOwnerGroup(this);
      m_Owner->onAfterChildRemove(m_Owner, obj);
      return true;
    }
    else return false;
  }
  else {
    group.remove(obj);
    obj->removeOwnerGroup(this);
    return true;
  }
}
//---------------------------------------------------------------------------
void YObjectGroup::_add(YMUDObject* obj)
{
  if(!obj) {
    g_err.show("[YObjectGroup::_add]Add NULL child.");
    return;
  }
  if(find(obj)) {
    g_err.show("[YObjectGroup::_add]Add child "+obj->getDataFileName()+" twice.");
    return;
  }
  if(m_Owner) m_Owner->onBeforeChildAdd(m_Owner, obj);
  group.push_back(obj);
  obj->addOwnerGroup(this);
  if(m_Owner) m_Owner->onAfterChildAdd(m_Owner, obj);
}
//---------------------------------------------------------------------------
void YObjectGroup::_remove(YMUDObject* obj)
{
  if(!obj) {
    g_err.show("[YObjectGroup::_remove]Remove NULL child.");
    return;
  }
  if(m_Owner) m_Owner->onBeforeChildRemove(m_Owner, obj);
  group.remove(obj);
  obj->removeOwnerGroup(this);
  if(m_Owner) m_Owner->onAfterChildRemove(m_Owner, obj);
}
//---------------------------------------------------------------------------
//仅仅删除，不发出任何通知消息
void YObjectGroup::_bare_remove(YMUDObject* obj)
{
  if(!obj) {
    g_err.show("[YObjectGroup::_bare_remove]Remove NULL child.");
    return;
  }
  group.remove(obj);
}
//---------------------------------------------------------------------------
//对所有子物体进行一定的操作
void YObjectGroup::forEach(void(*func)(YMUDObject*))
{
  obj_iter it=group.begin();
  while(it!=group.end()) func(*it++);
}
//---------------------------------------------------------------------------
//对具有特定属性的子物体进行一定的操作
void YObjectGroup::forEach(YString propertyName, YString propertyValue, void(*func)(YMUDObject*))
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if((*it)->getAsString(propertyName)==propertyValue) {
      func(*it);
    }
    it++;
  }
}
//---------------------------------------------------------------------------
//对具有特定属性的子物体进行一定的操作
void YObjectGroup::forEach(YString propertyName, long propertyValue, void(*func)(YMUDObject*))
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if((*it)->getAsLong(propertyName)==propertyValue) {
      func(*it);
    }
    it++;
  }
}
//---------------------------------------------------------------------------
//对具有特定属性的子物体进行一定的操作
void YObjectGroup::forEach(YString propertyName, float propertyValue, void(*func)(YMUDObject*))
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if((*it)->getAsFloat(propertyName)==propertyValue) {
      func(*it);
    }
    it++;
  }
}
//---------------------------------------------------------------------------
//查找子物体
bool YObjectGroup::find(YMUDObject* child)
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if((*it)==child) return true;
    it++;
  }
  return false;
}
//---------------------------------------------------------------------------
//查找具有特定属性的子物体
YMUDObject* YObjectGroup::find(YString propertyName, YString propertyValue, YString className)
{
  obj_iter it=group.begin();
  YMUDObject* obj;
  while(it!=group.end()) {
    if(((*it)->getAsString(propertyName)==propertyValue)&&
       (*it)->isTypeOf(className)) {
      return *it;
    }
    else if((obj=(*it)->findChild(propertyName, propertyValue))!=NULL) {
      return obj;
    }
    it++;
  }
  return NULL;
}
//---------------------------------------------------------------------------
//查找具有特定属性的子物体
YMUDObject* YObjectGroup::find(YString propertyName, long propertyValue, YString className)
{
  obj_iter it=group.begin();
  YMUDObject* obj;
  while(it!=group.end()) {
    if(((*it)->getAsLong(propertyName)==propertyValue) &&
       (*it)->isTypeOf(className)) {
      return *it;
    }
    else if((obj=(*it)->findChild(propertyName, propertyValue))!=NULL) {
      return obj;
    }
    it++;
  }
  return NULL;
}
//---------------------------------------------------------------------------
//查找具有特定属性的子物体
YMUDObject* YObjectGroup::find(YString propertyName, float propertyValue, YString className)
{
  obj_iter it=group.begin();
  YMUDObject* obj;
  while(it!=group.end()) {
    if(((*it)->getAsFloat(propertyName)==propertyValue) &&
       (*it)->isTypeOf(className)) {
      return *it;
    }
    else if((obj=(*it)->findChild(propertyName, propertyValue))!=NULL) {
      return obj;
    }
    it++;
  }
  return NULL;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
YString YObjectGroup::enumChildren(YString propertyName, YString propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsString(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getObjectName()+" ";
      //retS+=(*it)->getAsString("名字")+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
YString YObjectGroup::enumChildren(YString propertyName, long propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsLong(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getObjectName()+" ";//getAsString("名字")+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
YString YObjectGroup::enumChildren(YString propertyName, float propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsFloat(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getObjectName()+" ";//getAsString("名字")+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (用于显示在页面上)(propertyName==""代表任何属性值)
YString YObjectGroup::enumChildrenForDisplay(YString propertyName, YString propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsString(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getDisplayNameAndCount()+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (用于显示在页面上)(propertyName==""代表任何属性值)
YString YObjectGroup::enumChildrenForDisplay(YString propertyName, long propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsLong(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getDisplayNameAndCount()+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//列举所有物体(列出用空格分隔的子物体名称列表) (用于显示在页面上)(propertyName==""代表任何属性值)
YString YObjectGroup::enumChildrenForDisplay(YString propertyName, float propertyValue, YString className)
{
  obj_iter it=group.begin();
  YString retS="";
  while(it!=group.end()) {
    if(((propertyName=="")||((*it)->getAsFloat(propertyName)==propertyValue))&&
       (*it)->isTypeOf(className)) {
      retS+=(*it)->getDisplayNameAndCount()+" ";
    }
    it++;
  }
  return retS;
}
//---------------------------------------------------------------------------
//从列表中删除具有特定属性的子物体
void YObjectGroup::remove(YString propertyName, YString propertyValue, YString className)
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if(((*it)->getAsString(propertyName)==propertyValue) &&
       (*it)->isTypeOf(className)) {
      remove(*it);
    }
    else it++;
  }
}
//---------------------------------------------------------------------------
//从列表中删除具有特定属性的子物体
void YObjectGroup::remove(YString propertyName, long propertyValue, YString className)
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if(((*it)->getAsLong(propertyName)==propertyValue) &&
       (*it)->isTypeOf(className)) {
      remove(*it);
    }
    else it++;                  
  }
}
//---------------------------------------------------------------------------
//从列表中删除具有特定属性的子物体
void YObjectGroup::remove(YString propertyName, float propertyValue, YString className)
{
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if(((*it)->getAsFloat(propertyName)==propertyValue) &&
       (*it)->isTypeOf(className)) {
      remove(*it);
    }
    else it++;
  }
}
//---------------------------------------------------------------------------
//删除并析构所有子物体
void YObjectGroup::destoryAll(void)
{
  obj_iter it=group.begin();
  YString s=m_Owner->getObjectName()+" ";//getAsString("名字");
  while((it=group.begin())!=group.end()) {
    YMUDObject* obj=*it;
    remove(*it);
    if(obj) delete (obj);
  }
}
//---------------------------------------------------------------------------
//将所有子物体复制到另一ObjectGroup
void YObjectGroup::copyTo(YObjectGroup* another)
{
  if(!another) return;
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if(!(*it)) {
      it++;
      continue;
    }
    another->add((*it)->clone());
    it++;
  }
}
//---------------------------------------------------------------------------
void YObjectGroup::save(ostream& os, YString excludeClassName)
{
  os<<"begin of YObjectGroup\n";
  obj_iter it=group.begin();
  while(it!=group.end()) {
    if(!((*it)->isTypeOf(excludeClassName))) {
      os<<"object="<<(*it)->getDataFileName();
      if((*it)->isTypeOf("YAbstractThing")) {
        YAbstractThing* thing=(YAbstractThing*)(*it);
        if(thing->getThingType()==0) {
          if((thing)->getCount()>1) os<<" "<<thing->getCount();
        }
        else if(thing->getThingType()==1) {
          os<<" "<<thing->getVarientValueList();
        }
        else {
          //do nothing
        }
      }
      os<<"\n";
    }
    it++;
  }
  os<<"end of YObjectGroup\n";
}
//---------------------------------------------------------------------------
int YObjectGroup::load(istream& is)
{
  char buffer[BUFSIZE];
  bool ChildrenLoadOK=true;

  while(!is.eof()) {
    is.getline(buffer,BUFSIZE);
    int n=strlen(buffer)-1;
    if(n<0) continue;  //空串
    if(buffer[n]=='\r') buffer[n]='\0'; //兼容UNIX
    if(strcmp(buffer,"begin of YObjectGroup")==0) continue;
    if(strcmp(buffer,"end of YObjectGroup")==0) break;

    //分析字符串
    char *filename=strchr(buffer,'=');
    if(!filename) continue;
    *filename='\0';
    filename++;
    trim(buffer);
    trim(filename);
    if(strcmp(buffer,"object")==0) {
      YString name=filename;
      YString FileName=name.getWord();
      YMUDObject* obj=loadObject(FileName);
      if(!obj) {
        YErr::show("[YObjectGroup::load]cannot load "+FileName+" "+name);
        ChildrenLoadOK=false;
        continue;
      }
      else add(obj);
      if(!obj->isLoadOK()) ChildrenLoadOK=false;
      long count;
      if(obj->isTypeOf("YAbstractThing")) {
        YAbstractThing* thing=(YAbstractThing*)obj;
        if(thing->getThingType()==0) {
          YString s=name.getWord();
          if((count=s.toLong())>1) {
            thing->setCount(count);
          }
          else thing->setCount(1);
          if((s=name.getWord())!="") { //可能以前是SameButOne类型
            thing->setCount(2);
            while((s=name.getWord())!="") {
              thing->setCount(thing->getCount()+1);
            }
          }
        }
        else if(thing->getThingType()==1) {
          while(true) {
            YString s=name.getWord();
            if(s=="") break;
            thing->addOne(s.toLong());
          }
        }
        else {
          //do nothing
        }
      }
    }
  }
  if(ChildrenLoadOK) return 0; //成功读出
  else return -1;
}
//---------------------------------------------------------------------------
//方法reload--重新从文件中生成物体
int YObjectGroup::reload(istream& is)
{
  char buffer[BUFSIZE];
  bool ChildrenLoadOK=true;

  while(!is.eof()) {
    is.getline(buffer,BUFSIZE);
    int n=strlen(buffer)-1;
    if(n<0) continue;  //空串
    if(buffer[n]=='\r') buffer[n]='\0'; //兼容UNIX
    if(strcmp(buffer,"begin of YObjectGroup")==0) continue;
    if(strcmp(buffer,"end of YObjectGroup")==0) break;

    //分析字符串
    char *filename=strchr(buffer,'=');
    if(!filename) continue;
    *filename='\0';
    filename++;
    trim(buffer);
    trim(filename);
    if(strcmp(buffer,"object")==0) {
      YString name=filename;
      YString FileName=name.getWord();
      //**************************
      //判断是否已经有此物体
      YString childname=FileName;
      YString sType=childname.getWord("/");
      if(sType=="npc") continue; //不处理NPC
      //如果该物体仍然存在，则不用重新生成
      if(find("名字",childname)) continue;
      //不处理common目录下的
      if(FileName.find("common")!=YString::npos) continue;
      //**************************
      YMUDObject* obj=loadObject(FileName);
      if(!obj) {
        YErr::show("[YObjectGroup::load]cannot load "+FileName+" "+name);
        ChildrenLoadOK=false;
        continue;
      }
      else add(obj);
      if(!obj->isLoadOK()) ChildrenLoadOK=false;
      long count;
      if(obj->isTypeOf("YAbstractThing")) {
        YAbstractThing* thing=(YAbstractThing*)obj;
        if(thing->getThingType()==0) {
          if((count=name.toLong())>1) {
                  thing->setCount(count);
          }
        }
        else if(thing->getThingType()==1) {
          while(true) {
            YString s=name.getWord();
            if(s=="") break;
            thing->addOne(s.toLong());
          }
        }
        else {
          //do nothing
        }
      }
    }
  }
  if(ChildrenLoadOK) return 0; //成功读出
  else return -1;
}
//---------------------------------------------------------------------------
//查找具有特定属性的子物体
YMUDObject* YObjectGroup::findWithName(YString TheName , YString ThingType)
{
  obj_iter it=group.begin();
  YMUDObject* obj;
  while(it!=group.end())
  {
    YString thingname = (*it)->getObjectName(); 
    if((*it)->getObjectName() == TheName &&
       (*it)->isTypeOf(ThingType))
    {
      return *it;
    }
    else if((obj=(*it)->findChild("名字", TheName))!=NULL) {
      return obj;
    }
    it++;
  }
  return NULL;
}


