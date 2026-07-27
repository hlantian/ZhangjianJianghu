//---------------------------------------------------------------------------
//
// yobjectgroup.h    2000年6月12日
//
// 类YObjectGroup：物体集合，提供动态物体集，检索
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YOBJECTGROUP_H__
#define __YOBJECTGROUP_H__

#include <list>

class YMUDObject;

class YObjectGroup {
  private:
    list<YMUDObject*> group;
  public:
    typedef list<YMUDObject*>::iterator obj_iter;
    obj_iter begin() {return group.begin();}
    obj_iter end() {return group.end();}
  //属性：Owner
  private:
    YMUDObject* m_Owner;
  public:
    void setOwner(YMUDObject* newOwner) {m_Owner=newOwner;}
    YMUDObject* getOwner(void) {return m_Owner;}

  public:
  	YObjectGroup(YMUDObject* owner);  //构造函数
	  ~YObjectGroup(); //析构函数
    bool add(YMUDObject* obj);       //添加
    bool remove(YMUDObject* obj);    //删除
    void _add(YMUDObject* obj);      //强行添加(不受事件影响)
    void _remove(YMUDObject* obj);   //强行删除(不受事件影响)
    void _bare_remove(YMUDObject* obj);   //仅仅删除，不发出任何通知消息

    //从列表中删除具有特定属性的子物体
    void remove(YString propertyName, YString propertyValue, YString className="YMUDObject");
    void remove(YString propertyName, long propertyValue, YString className="YMUDObject");
    void remove(YString propertyName, float propertyValue, YString className="YMUDObject");

    //对所有子物体进行一定的操作
    void forEach(void(*func)(YMUDObject*));

    //对具有特定属性的子物体进行一定的操作
    void forEach(YString propertyName, YString propertyValue, void(*func)(YMUDObject*));
    void forEach(YString propertyName, long propertyValue, void(*func)(YMUDObject*));
    void forEach(YString propertyName, float propertyValue, void(*func)(YMUDObject*));

    //查找子物体
    bool find(YMUDObject* child);
    //查找具有特定属性的子物体(递归查找，子子物体也会被查到)
    YMUDObject* find(YString propertyName, YString propertyValue, YString className="YMUDObject");
    YMUDObject* find(YString propertyName, long propertyValue, YString className="YMUDObject");
    YMUDObject* find(YString propertyName, float propertyValue, YString className="YMUDObject");

    //列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
    YString enumChildren(YString propertyName="", YString propertyValue="", YString className="YMUDObject");
    YString enumChildren(YString propertyName="", long propertyValue=0, YString className="YMUDObject");
    YString enumChildren(YString propertyName="", float propertyValue=0, YString className="YMUDObject");

    //列举所有物体(列出用空格分隔的子物体名称列表)(用于显示在页面上) (propertyName==""代表任何属性值)
    YString enumChildrenForDisplay(YString propertyName="", YString propertyValue="", YString className="YMUDObject");
    YString enumChildrenForDisplay(YString propertyName="", long propertyValue=0, YString className="YMUDObject");
    YString enumChildrenForDisplay(YString propertyName="", float propertyValue=0, YString className="YMUDObject");

    //删除并析构所有子物体
    void destoryAll(void);

    void save(ostream& os, YString excludeClassName="");
    int load(istream& is);
		//方法reload--重新从文件中生成物体
		int reload(istream& is);

    //将所有子物体复制到另一ObjectGroup
    void copyTo(YObjectGroup* another);

    //用名字来查找人物，物品
    YMUDObject* findWithName(YString TheName ,YString ThingType);

};

#endif //__YOBJECTGROUP_H__
