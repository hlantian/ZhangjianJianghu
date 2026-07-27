//---------------------------------------------------------------------------
//
// ymudobject.h    2000年6月8日
//
// 类YMUDObject：所有物体的基类
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#ifndef __YMUDOBJECT_H__
#define __YMUDOBJECT_H__

#include <list>
#include "ystring.h"

class YObjectGroup;
class YPropertyGroup;
class YTimer;

class YAbstractActor;
class YAbstractRoom;
class YAbstractThing;

class YMUDObject {
    list<YObjectGroup*> m_OwnerGroups; //存储该Object所加入的组
  public:
    void addOwnerGroup(YObjectGroup* group);  //添加该Object所加入的组
    void removeOwnerGroup(YObjectGroup* group);  //删除该Object所加入的组

  //属性：ObjectName(名字)
	private:
		YString m_ObjectName; //属性ObjectName(名字)的成员变量
	public:
		YString getObjectName(void) {return m_ObjectName;} //读属性ObjectName(名字)
		void setObjectName(YString newObjectName) {m_ObjectName = newObjectName;} //设置ObjectName(名字)
  
	//属性：X(位置横坐标)
	private:
		long m_X; //属性X(位置横坐标)的成员变量
	public:
		long getX(void) {return m_X;} //读属性X(位置横坐标)
		void setX(long newX) {m_X=newX;} //设置X(位置横坐标)

	//属性：Y(位置纵坐标)
	private:
		long m_Y; //属性Y(位置纵坐标)的成员变量
	public:
		long getY(void) {return m_Y;} //读属性Y(位置纵坐标)
		void setY(long newY) {m_Y=newY;} //设置Y(位置纵坐标)

  //属性：Owner
  private:
    YMUDObject* m_Owner;
  public:
    void setOwner(YMUDObject* newOwner) {m_Owner=newOwner;}
    YMUDObject* getOwner(void) {return m_Owner;}

  //属性：DisplayName(用于显示在页面上的名字，带有颜色和javascript等内容)
  public:
    virtual YString getDisplayName(void);
    virtual YString getDisplayNameAndCount(void){return getDisplayName();};  //后面加一括弧显示数量

	//属性：DataFileName
	private:
		YString m_DataFileName; //属性DataFileName的成员变量
	public:
		YString getFullDataFileName(void); //读属性DataFileName(全路径)
		YString getDataFileName(void) {return m_DataFileName;} //读属性DataFileName(相对路径)
    //设置DataFileName(相对路径)
		void setDataFileName(YString newDataFileName) {m_DataFileName=newDataFileName;}

	//属性：Timer
	private:
		YTimer* m_Timer; //属性Timer的成员变量
    int m_initalized; //是否已产生过Init事件
  public:
    void disableTimer(void); //关闭计时器
	//属性：SmallTime
	private:
	public:
    void setSmallTime(int newSmallTime);
		int getSmallTime(void); //读属性SmallTime

	//属性：Children
	private:
		YObjectGroup* m_Children; //属性Children的成员变量
	public:
		YObjectGroup* getChildren(void) {return m_Children;} //读属性Children

	//属性：Properties
	private:
		YPropertyGroup* m_Properties; //属性Properties的成员变量
		YPropertyGroup* getProperties(void) {return m_Properties;} //读属性Properties
	public:

	//属性：LoadOK
	private:
		bool m_LoadOK; //属性LoadOK的成员变量
	public:
		bool isLoadOK(void) {return m_LoadOK;} //读属性LoadOK

	//属性：RuntimeClass
  public:
		virtual YString getRuntimeClass(void) {return YString("YMUDObject");} //读属性RuntimeClass

  public:
		//事件BeforeChildAdd的默认处理函数
		virtual int onBeforeChildAdd(YMUDObject* sender, YMUDObject* child);
		//事件AfterChildAdd的默认处理函数
		virtual int onAfterChildAdd(YMUDObject* sender, YMUDObject* child);
		//事件BeforeChildRemove的默认处理函数
		virtual int onBeforeChildRemove(YMUDObject* sender, YMUDObject* child);
		//事件AfterChildRemove的默认处理函数
		virtual int onAfterChildRemove(YMUDObject* sender, YMUDObject* child);
		//事件BeforePropertyChange的默认处理函数
		virtual int onBeforePropertyChange(YMUDObject* sender, YString PropertyName,
                                        long oldValue, long newValue);
		virtual int onBeforePropertyChange(YMUDObject* sender, YString PropertyName,
                                        float oldValue, float newValue);
		virtual int onBeforePropertyChange(YMUDObject* sender, YString PropertyName,
                                        YString oldValue, YString newValue);
		//事件AfterPropertyChange的默认处理函数
		virtual int onAfterPropertyChange(YMUDObject* sender, YString PropertyName,
                                        long oldValue, long newValue);
		virtual int onAfterPropertyChange(YMUDObject* sender, YString PropertyName,
                                        float oldValue, float newValue);
		virtual int onAfterPropertyChange(YMUDObject* sender, YString PropertyName,
                                        YString oldValue, YString newValue);
		//事件Init的默认处理函数
		virtual int onInit(void);
		//事件Destroy的默认处理函数
		virtual int onDestroy(void);
		//事件Timer的默认处理函数
		virtual int onTimer(void);
		//事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);

    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command)=0;

  private:
    int init();
    //
  public:
    YMUDObject(YString initFileName=""); //指定数据文件
    virtual ~YMUDObject();

		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);

		//方法save--属性保存到文件
		virtual int save(YString filename="");

		//方法load--从文件中读取属性
		virtual int load(YString filename);
		//方法reload--重新从文件中读取属性
		virtual int reload(void);

    //存取属性(map到YPropertyGroup)
    inline void set(YString name, float value);
    void set(YString name, long value);
    inline void set(YString name, short value){set(name,(long)value);};
    void set(YString name, int value){set(name,(long)value);};
    void set(YString name, double value){set(name,(float)value);};
    void set(YString name, YString value);
    long getAsLong(YString name);
    float getAsFloat(YString name);
    YString getAsString(YString name);

    //查找具有特定属性的子物体(map到YObjectGroup)
    YMUDObject* findChild(YString propertyName, YString propertyValue, YString className);
    YMUDObject* findChild(YString propertyName, long propertyValue, YString className="YMUDObject");
    YMUDObject* findChild(YString propertyName, float propertyValue, YString className="YMUDObject");
    YMUDObject* findChild(YString name, YString className="YMUDObject");  //查找名字为name子物体

    YAbstractActor* findChildActor(YString name);  //查找名字为name子物体(Actor)
    YAbstractRoom* findChildRoom(YString name);  //查找名字为name子物体(Room)
    YAbstractThing* findChildThing(YString name);  //查找名字为name子物体(Thing)

    //列举所有物体(列出用空格分隔的子物体名称列表) (propertyName==""代表任何属性值)
    //(map到YObjectGroup)
    YString enumChildren(YString propertyName="", YString propertyValue="", YString className="YMUDObject");
    inline YString enumChildren(YString propertyName="", long propertyValue=0, YString className="YMUDObject");
    inline YString enumChildren(YString propertyName="", float propertyValue=0, YString className="YMUDObject");
    inline YString enumChildrenActor(void){return enumChildren("","","YAbstractActor");}
    inline YString enumChildrenRoom(void){return enumChildren("","","YAbstractRoom");}
    inline YString enumChildrenThing(void){return enumChildren("","","YAbstractThing");}
    //列举所有物体(列出用空格分隔的子物体名称列表)(用于显示在页面上)(propertyName==""代表任何属性值)
    //(map到YObjectGroup)
    YString enumChildrenForDisplay(YString propertyName="", YString propertyValue="", YString className="YMUDObject");
    inline YString enumChildrenForDisplay(YString propertyName="", long propertyValue=0, YString className="YMUDObject");
    inline YString enumChildrenForDisplay(YString propertyName="", float propertyValue=0, YString className="YMUDObject");
    inline YString enumChildrenActorForDisplay(void){return enumChildrenForDisplay("","","YAbstractActor");}
    inline YString enumChildrenRoomForDisplay(void){return enumChildrenForDisplay("","","YAbstractRoom");}
    inline YString enumChildrenThingForDisplay(void){return enumChildrenForDisplay("","","YAbstractThing");}


    //将子物体传给另一物体
    virtual bool giveChildTo(YMUDObject* child, YMUDObject* another, long count=1, long No=1);
    //增加子物体
    bool addChild(YMUDObject* child);
    //移除子物体
    bool removeChild(YMUDObject* child);
    //删除并销毁所有子物体
    inline void destoryAllChild(void);
    //删除所有属性
    inline void removeAllProperties(void);
    //复制本身
    virtual YMUDObject* clone(void);
};

#endif //__YMUDOBJECT_H__
