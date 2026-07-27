//---------------------------------------------------------------------------
//
// yretiringroom.h    2000年8月4日
//
// 类YRetiringRoom：休息室
//
// 作者：张勇   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------

#ifndef __YRETIRINGROOM_H__
#define __YRETIRINGROOM_H__
#include "yroom.h"
class YRetiringRoom : public YRoom {
  //属性：RoomSchool(房间的门派)
	private:
		YString m_RoomSchool; //属性RoomSchool(房间的门派)的成员变量
	public:
		YString getRoomSchool(void) {return m_RoomSchool;} //读属性RoomSchool(房间的门派)
		void setRoomSchool(YString newRoomSchool) {m_RoomSchool=newRoomSchool;} //设置RoomSchool(房间的门派)
  //属性：RoomSex(房间的性别)
	private:
		YString m_RoomSex; //属性RoomSex(房间的性别)的成员变量
	public:
		YString getRoomSex(void) {return m_RoomSex;} //读属性RoomSex(房间的性别)
		void setRoomSex(YString newRoomSex) {m_RoomSex=newRoomSex;} //设置RoomSex(房间的性别)
  
  public:
    //读属性RuntimeClass
		virtual YString getRuntimeClass(void) {return YString("YRetiringRoom");}
		//方法isTypeOf--是否是某种类型或其派生类型
		virtual int isTypeOf(YString className);
  public:
		YRetiringRoom(YString initFileName="");  //构造函数
		virtual ~YRetiringRoom(){}; //析构函数

    //事件AfterLoad的默认处理函数
		virtual int onAfterLoad(void);
		//事件BeforeSave的默认处理函数
		virtual int onBeforeSave(void);
    
  public:
    //执行命令，已处理返回1，未处理返回0
  virtual int executeCommand(YAbstractActor* executor, YString command); //作为场所
  //各种命令处理
  public:
  virtual int gosleep(YAbstractActor* executor); //休息
};

#endif //__YRETIRINGROOM_H__
