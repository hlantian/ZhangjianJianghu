//ymudsettings.h
//存储各种设置
#ifndef __YMUDSETTINGS_H__
#define __YMUDSETTINGS_H__

#include "ystring.h"
#include "ysession.h"

#include "ypropertygroup.h"

class YMUDSettings {
  private:
    YPropertyGroup *m_property_group;
	//属性：RootPath
	private:
		YString m_RootPath; //属性RootPath的成员变量
	public:
		YString getRootPath(void) {return m_RootPath;} //读属性RootPath
    YString getFullPlayerPath(void) {return m_RootPath+getPathSeparator()+"player";}
    YString getFullNPCPath(void) {return m_RootPath+getPathSeparator()+"npc";}
    YString getFullRoomPath(void) {return m_RootPath+getPathSeparator()+"room";}
    YString getPlayerPath(void) {return "player";}
    YString getNPCPath(void) {return "npc";}
    YString getRoomPath(void) {return "room";}
    YString getFIFOPath(void)
       {return m_RootPath+getPathSeparator()+"fifo";}
    YString getCommandFIFOPathName(YSession* session=NULL);
    YString getLoginFIFOPathName(void)
       {return getFIFOPath()+getPathSeparator()+"login.fifo";}

	//属性：MaxIdleTime
	private:
	  int m_MaxIdleTime;  //[最大空闲时间]--单位：秒。用户在此时间
                      //内必须有至少一次操作，否则会话自动终止
	public:
		int getMaxIdleTime(void) {return m_MaxIdleTime;} //读属性MaxIdleTime
		void setMaxIdleTime(int newMaxIdleTime) {m_MaxIdleTime=newMaxIdleTime;} //设置MaxIdleTime

	//属性：SessionIDLength
	private:
		int m_SessionIDLength; //属性SessionIDLength的成员变量
	public:
		int getSessionIDLength(void) {return m_SessionIDLength;} //读属性SessionIDLength
		void setSessionIDLength(int newSessionIDLength) {m_SessionIDLength=newSessionIDLength;} //设置SessionIDLength

	//属性：Server_IP
	private:
		YString m_Server_IP; //属性Server_IP的成员变量
	public:
		YString getServer_IP(void) {return m_Server_IP;} //读属性Server_IP
		void setServer_IP(YString newServer_IP) {m_Server_IP=newServer_IP;} //设置Server_IP

	//属性：MessagePort message使用的端口号
	private:
		short m_MessagePort; //属性MessagePort的成员变量
	public:
		short getMessagePort(void) {return m_MessagePort;} //读属性MessagePort

	//属性：PlayerNameColor(显示玩家名所用的颜色)
	private:
		YString m_PlayerNameColor; //属性PlayerNameColor(显示玩家名所用的颜色)的成员变量
	public:
		YString getPlayerNameColor(void) {return m_PlayerNameColor;} //读属性PlayerNameColor(显示玩家名所用的颜色)
		void setPlayerNameColor(YString newPlayerNameColor) {m_PlayerNameColor=newPlayerNameColor;} //设置PlayerNameColor(显示玩家名所用的颜色)

	//属性：RoomNameColor(显示房间名所用的颜色)
	private:
		YString m_RoomNameColor; //属性RoomNameColor(显示房间名所用的颜色)的成员变量
	public:
		YString getRoomNameColor(void) {return m_RoomNameColor;} //读属性RoomNameColor(显示房间名所用的颜色)
		void setRoomNameColor(YString newRoomNameColor) {m_RoomNameColor=newRoomNameColor;} //设置RoomNameColor(显示房间名所用的颜色)

	//属性：NPCNameColor(显示NPC名所用的颜色)
	private:
		YString m_NPCNameColor; //属性NPCNameColor(显示NPC名所用的颜色)的成员变量
	public:
		YString getNPCNameColor(void) {return m_NPCNameColor;} //读属性NPCNameColor(显示NPC名所用的颜色)
		void setNPCNameColor(YString newNPCNameColor) {m_NPCNameColor=newNPCNameColor;} //设置NPCNameColor(显示NPC名所用的颜色)

	//属性：ThingNameColoe(显示物品名所用的颜色)
	private:
		YString m_ThingNameColor; //属性ThingNameColor(显示物品名所用的颜色)的成员变量
	public:
		YString getThingNameColor(void) {return m_ThingNameColor;} //读属性ThingNameColor(显示物品名所用的颜色)
		void setThingNameColor(YString newThingNameColor) {m_ThingNameColor=newThingNameColor;} //设置ThingNameColor(显示物品名所用的颜色)
	//属性：playerNameColor(player_name_color)
	private:
		YString m_playerNameColor; //属性playerNameColor(player_name_color)的成员变量
	public:
		YString getplayerNameColor(void) {return m_playerNameColor;} //读属性playerNameColor(player_name_color)
		void setplayerNameColor(YString newplayerNameColor) {m_playerNameColor=newplayerNameColor;} //设置playerNameColor(player_name_color)
	//属性：npcNameColor(npc_name_color)
	private:
		YString m_npcNameColor; //属性npcNameColor(npc_name_color)的成员变量
	public:
		YString getnpcNameColor(void) {return m_npcNameColor;} //读属性npcNameColor(npc_name_color)
		void setnpcNameColor(YString newnpcNameColor) {m_npcNameColor=newnpcNameColor;} //设置npcNameColor(npc_name_color)
	//属性：roomNameColoe(room_name_color)
	private:
		YString m_roomNameColoe; //属性roomNameColoe(room_name_color)的成员变量
	public:
		YString getroomNameColoe(void) {return m_roomNameColoe;} //读属性roomNameColoe(room_name_color)
		void setroomNameColoe(YString newroomNameColoe) {m_roomNameColoe=newroomNameColoe;} //设置roomNameColoe(room_name_color)
	//属性：chatColor(公用频道颜色)
	private:
		YString m_chatColor; //属性chatColor(公用频道颜色)的成员变量
	public:
		YString getchatColor(void) {return m_chatColor;} //读属性chatColor(公用频道颜色)
		void setchatColor(YString newchatColor) {m_chatColor=newchatColor;} //设置chatColor(公用频道颜色)
	//属性：chatpartyColor(门派频道颜色)
	private:
		YString m_partychatColor; //属性chatColor(门派频道颜色)的成员变量
	public:
		YString getpartychatColor(void) {return m_partychatColor;} //读属性chatColor(门派频道颜色)
		void setpartychatColor(YString newpartychatColor) {m_partychatColor=newpartychatColor;} //设置partychatColor(门派频道颜色)
	//属性：newbieChatColor(新手频道颜色)
	private:
		YString m_newbieChatColor; //属性newbieChatColor(新手频道颜色)的成员变量
	public:
		YString getnewbieChatColor(void) {return m_newbieChatColor;} //读属性newbieChatColor(新手频道颜色)
		void setnewbieChatColor(YString newnewbieChatColor) {m_newbieChatColor=newnewbieChatColor;} //设置newbieChatColor(新手频道颜色)
	//属性：rumorChatColor(谣言频道颜色)
	private:
		YString m_rumorChatColor; //属性rumorChatColor(谣言频道颜色)的成员变量
	public:
		YString getrumorChatColor(void) {return m_rumorChatColor;} //读属性rumorChatColor(谣言频道颜色)
		void setrumorChatColor(YString newrumorChatColor) {m_rumorChatColor=newrumorChatColor;} //设置rumorChatColor(谣言频道颜色)
	//属性：wizChatColor(巫师频道颜色)
	private:
		YString m_wizChatColor; //属性wizChatColor(巫师频道颜色)的成员变量
	public:
		YString getwizChatColor(void) {return m_wizChatColor;} //读属性wizChatColor(巫师频道颜色)
		void setwizChatColor(YString newwizChatColor) {m_wizChatColor=newwizChatColor;} //设置wizChatColor(巫师频道颜色)
	//属性：QuestColor(任务显示颜色)
	private:
		YString m_QuestColor; //属性QuestColor(任务显示颜色)的成员变量
	public:
		YString getQuestColor(void) {return m_QuestColor;} //读属性QuestColor(任务显示颜色)
		void setQuestColor(YString newQuestColor) {m_QuestColor=newQuestColor;} //设置QuestColor(任务显示颜色)
	//属性：newPlayerIn(新人房间)
	private:
		YString m_newPlayerIn; //属性newPlayerIn(新人房间)的成员变量
	public:
		YString getnewPlayerIn(void) {return m_newPlayerIn;} //读属性newPlayerIn(新人房间)
		void setnewPlayerIn(YString newnewPlayerIn) {m_newPlayerIn=newnewPlayerIn;} //设置newPlayerIn(新人房间)
	//属性：FistComrIn(初始房间)
	private:
		YString m_FistComrIn; //属性FistComrIn(初始房间)的成员变量
	public:
		YString getFistComrIn(void) {return m_FistComrIn;} //读属性FistComrIn(初始房间)
		void setFistComrIn(YString newFistComrIn) {m_FistComrIn=newFistComrIn;} //设置FistComrIn(初始房间)
	//属性：IsNewPlayer(新玩家)
	private:
		YString m_IsNewPlayer; //属性IsNewPlayer(新玩家)的成员变量
	public:
		YString getIsNewPlayer(void) {return m_IsNewPlayer;} //读属性IsNewPlayer(新玩家)
		void setIsNewPlayer(YString newIsNewPlayer) {m_IsNewPlayer=newIsNewPlayer;} //设置IsNewPlayer(新玩家)
	//属性：DeadRoom(死亡房间)
	private:
		YString m_DeadRoom; //属性DeadRoom(死亡房间)的成员变量
	public:
		YString getDeadRoom(void) {return m_DeadRoom;} //读属性DeadRoom(死亡房间)
		void setDeadRoom(YString newDeadRoom) {m_DeadRoom=newDeadRoom;} //设置DeadRoom(死亡房间)
	//属性：NPCDeadRoom(NPC死亡房间)
	private:
		YString m_NPCDeadRoom; //属性NPCDeadRoom(NPC死亡房间)的成员变量
	public:
		YString getNPCDeadRoom(void) {return m_NPCDeadRoom;} //读属性NPCDeadRoom(NPC死亡房间)
		void setNPCDeadRoom(YString newNPCDeadRoom) {m_NPCDeadRoom=newNPCDeadRoom;} //设置NPCDeadRoom(NPC死亡房间)
	//属性：NickColor(绰号颜色)
	private:
		YString m_NickColor; //属性NickColor(绰号颜色)的成员变量
	public:
		YString getNickColor(void) {return m_NickColor;} //读属性NickColor(绰号颜色)
		void setNickColor(YString newNickColor) {m_NickColor=newNickColor;} //设置NickColor(绰号颜色)
	//属性：DescribeColorColor(绰号颜色)
	private:
		YString m_DescribeColor; //属性Describe(个人描述颜色)的成员变量
	public:
		YString getDescribeColor(void) {return m_DescribeColor;} //读属性Describe(个人描述颜色)
		void setDescribeColor(YString newDescribeColor) {m_DescribeColor=newDescribeColor;} //设置Describe(个人描述颜色)
	//属性：HelpRoom1(helproom1)
	private:
		YString m_HelpRoom1; //属性HelpRoom1(helproom1)的成员变量
	public:
		YString getHelpRoom1(void) {return m_HelpRoom1;} //读属性HelpRoom1(helproom1)
		void setHelpRoom1(YString newHelpRoom1) {m_HelpRoom1=newHelpRoom1;} //设置HelpRoom1(helproom1)
	//属性：HelpRoom2(helproom2)
	private:
		YString m_HelpRoom2; //属性HelpRoom2(helproom2)的成员变量
	public:
		YString getHelpRoom2(void) {return m_HelpRoom2;} //读属性HelpRoom2(helproom2)
		void setHelpRoom2(YString newHelpRoom2) {m_HelpRoom2=newHelpRoom2;} //设置HelpRoom2(helproom2)
	//属性：HelpRoom3(helproom3)
	private:
		YString m_HelpRoom3; //属性HelpRoom3(helproom3)的成员变量
	public:
		YString getHelpRoom3(void) {return m_HelpRoom3;} //读属性HelpRoom3(helproom3)
		void setHelpRoom3(YString newHelpRoom3) {m_HelpRoom3=newHelpRoom3;} //设置HelpRoom3(helproom3)
	//属性：HelpRoom4(helproom4)
	private:
		YString m_HelpRoom4; //属性HelpRoom4(helproom4)的成员变量
	public:
		YString getHelpRoom4(void) {return m_HelpRoom4;} //读属性HelpRoom4(helproom4)
		void setHelpRoom4(YString newHelpRoom4) {m_HelpRoom4=newHelpRoom4;} //设置HelpRoom4(helproom4)
	//属性：HelpRoom5(helproom5)
	private:
		YString m_HelpRoom5; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom5(void) {return m_HelpRoom5;} //读属性HelpRoom5(helproom5)
		void setHelpRoom5(YString newHelpRoom5) {m_HelpRoom5=newHelpRoom5;} //设置HelpRoom5(helproom5)
	//属性：HelpRoom6(helproom6)
	private:
		YString m_HelpRoom6; //属性HelpRoom6(helproom6)的成员变量
	public:
		YString getHelpRoom6(void) {return m_HelpRoom6;} //读属性HelpRoom6(helproom6)
		void setHelpRoom6(YString newHelpRoom6) {m_HelpRoom6=newHelpRoom6;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom7)
	private:
		YString m_HelpRoom7; //属性HelpRoom7(helproom7)的成员变量
	public:
		YString getHelpRoom7(void) {return m_HelpRoom7;} //读属性HelpRoom6(helproom7)
		void setHelpRoom7(YString newHelpRoom7) {m_HelpRoom7=newHelpRoom7;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom8)
	private:
		YString m_HelpRoom8; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom8(void) {return m_HelpRoom8;} //读属性HelpRoom6(helproom6)
		void setHelpRoom8(YString newHelpRoom8) {m_HelpRoom8=newHelpRoom8;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom9)
	private:
		YString m_HelpRoom9; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom9(void) {return m_HelpRoom9;} //读属性HelpRoom6(helproom6)
		void setHelpRoom9(YString newHelpRoom9) {m_HelpRoom9=newHelpRoom9;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom6)
	private:
		YString m_HelpRoom10; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom10(void) {return m_HelpRoom10;} //读属性HelpRoom6(helproom6)
		void setHelpRoom10(YString newHelpRoom10) {m_HelpRoom10=newHelpRoom10;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom6)
	private:
		YString m_HelpRoom11; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom11(void) {return m_HelpRoom11;} //读属性HelpRoom6(helproom11)
		void setHelpRoom11(YString newHelpRoom11) {m_HelpRoom11=newHelpRoom11;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom12)
	private:
		YString m_HelpRoom12; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom12(void) {return m_HelpRoom12;} //读属性HelpRoom6(helproom6)
		void setHelpRoom12(YString newHelpRoom12) {m_HelpRoom12=newHelpRoom12;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom13)
	private:
		YString m_HelpRoom13; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom13(void) {return m_HelpRoom13;} //读属性HelpRoom6(helproom6)
		void setHelpRoom13(YString newHelpRoom13) {m_HelpRoom13=newHelpRoom13;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom14)
	private:
		YString m_HelpRoom14; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom14(void) {return m_HelpRoom14;} //读属性HelpRoom6(helproom6)
		void setHelpRoom14(YString newHelpRoom14) {m_HelpRoom14=newHelpRoom14;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom15)
	private:
		YString m_HelpRoom15; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom15(void) {return m_HelpRoom15;} //读属性HelpRoom6(helproom6)
		void setHelpRoom15(YString newHelpRoom15) {m_HelpRoom15=newHelpRoom15;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom16)
	private:
		YString m_HelpRoom16; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom16(void) {return m_HelpRoom16;} //读属性HelpRoom6(helproom6)
		void setHelpRoom16(YString newHelpRoom16) {m_HelpRoom16=newHelpRoom16;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom17)
	private:
		YString m_HelpRoom17; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom17(void) {return m_HelpRoom17;} //读属性HelpRoom6(helproom6)
		void setHelpRoom17(YString newHelpRoom17) {m_HelpRoom17=newHelpRoom17;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom18)
	private:
		YString m_HelpRoom18; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom18(void) {return m_HelpRoom18;} //读属性HelpRoom6(helproom6)
		void setHelpRoom18(YString newHelpRoom18) {m_HelpRoom18=newHelpRoom18;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom6(helproom19)
	private:
		YString m_HelpRoom19; //属性HelpRoom5(helproom5)的成员变量
	public:
		YString getHelpRoom19(void) {return m_HelpRoom19;} //读属性HelpRoom6(helproom6)
		void setHelpRoom19(YString newHelpRoom19) {m_HelpRoom19=newHelpRoom19;} //设置HelpRoom6(helproom6)
	//属性：HelpRoom20(helproom20)
	private:
		YString m_HelpRoom20; //属性HelpRoom20(helproom20)的成员变量
	public:
		YString getHelpRoom20(void) {return m_HelpRoom20;} //读属性HelpRoom20(helproom20)
		void setHelpRoom20(YString newHelpRoom20) {m_HelpRoom20=newHelpRoom20;} //设置HelpRoom20(helproom20)
	//属性：HelpRoom21(helproom21)
	private:
		YString m_HelpRoom21; //属性HelpRoom21(helproom21)的成员变量
	public:
		YString getHelpRoom21(void) {return m_HelpRoom21;} //读属性HelpRoom21(helproom21)
		void setHelpRoom21(YString newHelpRoom21) {m_HelpRoom21=newHelpRoom21;} //设置HelpRoom21(helproom21)
	//属性：HelpRoom22(helproom22)
	private:
		YString m_HelpRoom22; //属性HelpRoom22(helproom22)的成员变量
	public:
		YString getHelpRoom22(void) {return m_HelpRoom22;} //读属性HelpRoom22(helproom22)
		void setHelpRoom22(YString newHelpRoom22) {m_HelpRoom22=newHelpRoom22;} //设置HelpRoom22(helproom22)
	//属性：HelpRoom23(helproom23)
	private:
		YString m_HelpRoom23; //属性HelpRoom23(helproom23)的成员变量
	public:
		YString getHelpRoom23(void) {return m_HelpRoom23;} //读属性HelpRoom23(helproom23)
		void setHelpRoom23(YString newHelpRoom23) {m_HelpRoom23=newHelpRoom23;} //设置HelpRoom23(helproom23)
	//属性：HelpRoom24(helpRoom24)
	private:
		YString m_HelpRoom24; //属性HelpRoom24(helpRoom24)的成员变量
	public:
		YString getHelpRoom24(void) {return m_HelpRoom24;} //读属性HelpRoom24(helpRoom24)
		void setHelpRoom24(YString newHelpRoom24) {m_HelpRoom24=newHelpRoom24;} //设置HelpRoom24(helpRoom24)
	//属性：HelpRoom25(helpRoom25)
	private:
		YString m_HelpRoom25; //属性HelpRoom25(helpRoom25)的成员变量
	public:
		YString getHelpRoom25(void) {return m_HelpRoom25;} //读属性HelpRoom25(helpRoom25)
		void setHelpRoom25(YString newHelpRoom25) {m_HelpRoom25=newHelpRoom25;} //设置HelpRoom25(helpRoom25)
	//属性：jingDisplay(精力恢复描述)
	private:
		YString m_jingDisplay; //属性jingDisplay(精力恢复描述)的成员变量
	public:
		YString getjingDisplay(void) {return m_jingDisplay;} //读属性jingDisplay(精力恢复描述)
		void setjingDisplay(YString newjingDisplay) {m_jingDisplay=newjingDisplay;} //设置jingDisplay(精力恢复描述)
	//属性：QiDiaplay(气血恢复描述)
	private:
		YString m_QiDiaplay; //属性QiDiaplay(气血恢复描述)的成员变量
	public:
		YString getQiDiaplay(void) {return m_QiDiaplay;} //读属性QiDiaplay(气血恢复描述)
		void setQiDiaplay(YString newQiDiaplay) {m_QiDiaplay=newQiDiaplay;} //设置QiDiaplay(气血恢复描述)
	//属性：BodyDisplay0(平时气血形容0)
	private:
		YString m_BodyDisplay0; //属性BodyDisplay0(平时气血形容0)的成员变量
	public:
		YString getBodyDisplay0(void) {return m_BodyDisplay0;} //读属性BodyDisplay0(平时气血形容0)
		void setBodyDisplay0(YString newBodyDisplay0) {m_BodyDisplay0=newBodyDisplay0;} //设置BodyDisplay0(平时气血形容0)
	//属性：BodyDisplay1(平时气血形容1)
	private:
		YString m_BodyDisplay1; //属性BodyDisplay1(平时气血形容1)的成员变量
	public:
		YString getBodyDisplay1(void) {return m_BodyDisplay1;} //读属性BodyDisplay1(平时气血形容1)
		void setBodyDisplay1(YString newBodyDisplay1) {m_BodyDisplay1=newBodyDisplay1;} //设置BodyDisplay1(平时气血形容1)
	//属性：BodyDisplay2(平时气血形容2)
	private:
		YString m_BodyDisplay2; //属性BodyDisplay2(平时气血形容2)的成员变量
	public:
		YString getBodyDisplay2(void) {return m_BodyDisplay2;} //读属性BodyDisplay2(平时气血形容2)
		void setBodyDisplay2(YString newBodyDisplay2) {m_BodyDisplay2=newBodyDisplay2;} //设置BodyDisplay2(平时气血形容2)
	//属性：BodyDisplay3(平时气血形容3)
	private:
		YString m_BodyDisplay3; //属性BodyDisplay3(平时气血形容3)的成员变量
	public:
		YString getBodyDisplay3(void) {return m_BodyDisplay3;} //读属性BodyDisplay3(平时气血形容3)
		void setBodyDisplay3(YString newBodyDisplay3) {m_BodyDisplay3=newBodyDisplay3;} //设置BodyDisplay3(平时气血形容3)
	//属性：BodyDisplay4(平时气血形容4)
	private:
		YString m_BodyDisplay4; //属性BodyDisplay4(平时气血形容4)的成员变量
	public:
		YString getBodyDisplay4(void) {return m_BodyDisplay4;} //读属性BodyDisplay4(平时气血形容4)
		void setBodyDisplay4(YString newBodyDisplay4) {m_BodyDisplay4=newBodyDisplay4;} //设置BodyDisplay4(平时气血形容4)
	//属性：BodyDisplay5(平时气血形容5)
	private:
		YString m_BodyDisplay5; //属性BodyDisplay5(平时气血形容5)的成员变量
	public:
		YString getBodyDisplay5(void) {return m_BodyDisplay5;} //读属性BodyDisplay5(平时气血形容5)
		void setBodyDisplay5(YString newBodyDisplay5) {m_BodyDisplay5=newBodyDisplay5;} //设置BodyDisplay5(平时气血形容5)
	//属性：menFeature80(男性容貌形容>80)
	private:
		YString m_menFeature80; //属性menFeature80(男性容貌形容>80)的成员变量
	public:
		YString getmenFeature80(void) {return m_menFeature80;} //读属性menFeature80(男性容貌形容>80)
		void setmenFeature80(YString newmenFeature80) {m_menFeature80=newmenFeature80;} //设置menFeature80(男性容貌形容>80)
	//属性：menFeature70(男性容貌形容>70)
	private:
		YString m_menFeature70; //属性menFeature70(男性容貌形容>70)的成员变量
	public:
		YString getmenFeature70(void) {return m_menFeature70;} //读属性menFeature70(男性容貌形容>70)
		void setmenFeature70(YString newmenFeature70) {m_menFeature70=newmenFeature70;} //设置menFeature70(男性容貌形容>70)
	//属性：menFeature60(男性容貌形容>60)
	private:
		YString m_menFeature60; //属性menFeature60(男性容貌形容>60)的成员变量
	public:
		YString getmenFeature60(void) {return m_menFeature60;} //读属性menFeature60(男性容貌形容>60)
		void setmenFeature60(YString newmenFeature60) {m_menFeature60=newmenFeature60;} //设置menFeature60(男性容貌形容>60)
	//属性：menFeature50(男性容貌形容50)
	private:
		YString m_menFeature50; //属性menFeature50(男性容貌形容50)的成员变量
	public:
		YString getmenFeature50(void) {return m_menFeature50;} //读属性menFeature50(男性容貌形容50)
		void setmenFeature50(YString newmenFeature50) {m_menFeature50=newmenFeature50;} //设置menFeature50(男性容貌形容50)
	//属性：menFeature40(男性容貌形容>40)
	private:
		YString m_menFeature40; //属性menFeature40(男性容貌形容>40)的成员变量
	public:
		YString getmenFeature40(void) {return m_menFeature40;} //读属性menFeature40(男性容貌形容>40)
		void setmenFeature40(YString newmenFeature40) {m_menFeature40=newmenFeature40;} //设置menFeature40(男性容貌形容>40)
	//属性：menFeature30(男性容貌形容<40)
	private:
		YString m_menFeature30; //属性menFeature30(男性容貌形容<40)的成员变量
	public:
		YString getmenFeature30(void) {return m_menFeature30;} //读属性menFeature30(男性容貌形容<40)
		void setmenFeature30(YString newmenFeature30) {m_menFeature30=newmenFeature30;} //设置menFeature30(男性容貌形容<40)
	//属性：wemenFeature80(女性容貌形容>80)
	private:
		YString m_wemenFeature80; //属性wemenFeature80(女性容貌形容>80)的成员变量
	public:
		YString getwemenFeature80(void) {return m_wemenFeature80;} //读属性wemenFeature80(女性容貌形容>80)
		void setwemenFeature80(YString newwemenFeature80) {m_wemenFeature80=newwemenFeature80;} //设置wemenFeature80(女性容貌形容>80)
	//属性：wemenFeature70(女性容貌形容>70)
	private:
		YString m_wemenFeature70; //属性wemenFeature70(女性容貌形容>70)的成员变量
	public:
		YString getwemenFeature70(void) {return m_wemenFeature70;} //读属性wemenFeature70(女性容貌形容>70)
		void setwemenFeature70(YString newwemenFeature70) {m_wemenFeature70=newwemenFeature70;} //设置wemenFeature70(女性容貌形容>70)
	//属性：wemenFeature60(女性容貌形容>60)
	private:
		YString m_wemenFeature60; //属性wemenFeature60(女性容貌形容>60)的成员变量
	public:
		YString getwemenFeature60(void) {return m_wemenFeature60;} //读属性wemenFeature60(女性容貌形容>60)
		void setwemenFeature60(YString newwemenFeature60) {m_wemenFeature60=newwemenFeature60;} //设置wemenFeature60(女性容貌形容>60)
	//属性：wemenFeature55(女性容貌形容>55)
	private:
		YString m_wemenFeature55; //属性wemenFeature55(女性容貌形容>55)的成员变量
	public:
		YString getwemenFeature55(void) {return m_wemenFeature55;} //读属性wemenFeature55(女性容貌形容>55)
		void setwemenFeature55(YString newwemenFeature55) {m_wemenFeature55=newwemenFeature55;} //设置wemenFeature55(女性容貌形容>55)
	//属性：wemenFeature50(女性容貌形容>50)
	private:
		YString m_wemenFeature50; //属性wemenFeature50(女性容貌形容>50)的成员变量
	public:
		YString getwemenFeature50(void) {return m_wemenFeature50;} //读属性wemenFeature50(女性容貌形容>50)
		void setwemenFeature50(YString newwemenFeature50) {m_wemenFeature50=newwemenFeature50;} //设置wemenFeature50(女性容貌形容>50)
	//属性：wemenFeature45(女性容貌形容>45)
	private:
		YString m_wemenFeature45; //属性wemenFeature45(女性容貌形容>45)的成员变量
	public:
		YString getwemenFeature45(void) {return m_wemenFeature45;} //读属性wemenFeature45(女性容貌形容>45)
		void setwemenFeature45(YString newwemenFeature45) {m_wemenFeature45=newwemenFeature45;} //设置wemenFeature45(女性容貌形容>45)
	//属性：wemenFeature40(女性容貌形容>40)
	private:
		YString m_wemenFeature40; //属性wemenFeature40(女性容貌形容>40)的成员变量
	public:
		YString getwemenFeature40(void) {return m_wemenFeature40;} //读属性wemenFeature40(女性容貌形容>40)
		void setwemenFeature40(YString newwemenFeature40) {m_wemenFeature40=newwemenFeature40;} //设置wemenFeature40(女性容貌形容>40)
	//属性：wemenFeature30(女性容貌形容<40)
	private:
		YString m_wemenFeature30; //属性wemenFeature30(女性容貌形容<40)的成员变量
	public:
		YString getwemenFeature30(void) {return m_wemenFeature30;} //读属性wemenFeature30(女性容貌形容<40)
		void setwemenFeature30(YString newwemenFeature30) {m_wemenFeature30=newwemenFeature30;} //设置wemenFeature30(女性容貌形容<40)
	//属性：wugongDisplay0*(武功级别描述0)
	private:
		YString m_wugongDisplay0; //属性wugongDisplay0(武功级别描述0)的成员变量
	public:
		YString getwugongDisplay0(void) {return m_wugongDisplay0;} //读属性wugongDisplay0(武功级别描述0)
		void setwugongDisplay0(YString newwugongDisplay0) {m_wugongDisplay0=newwugongDisplay0;} //设置wugongDisplay0(武功级别描述0)
	//属性：wugongDisplay1(武功级别描述1)
	private:
		YString m_wugongDisplay1; //属性wugongDisplay1(武功级别描述1)的成员变量
	public:
		YString getwugongDisplay1(void) {return m_wugongDisplay1;} //读属性wugongDisplay1(武功级别描述1)
		void setwugongDisplay1(YString newwugongDisplay1) {m_wugongDisplay1=newwugongDisplay1;} //设置wugongDisplay1(武功级别描述1)
	//属性：wugongDisplay2(武功级别描述2)
	private:
		YString m_wugongDisplay2; //属性wugongDisplay2(武功级别描述2)的成员变量
	public:
		YString getwugongDisplay2(void) {return m_wugongDisplay2;} //读属性wugongDisplay2(武功级别描述2)
		void setwugongDisplay2(YString newwugongDisplay2) {m_wugongDisplay2=newwugongDisplay2;} //设置wugongDisplay2(武功级别描述2)
	//属性：wugongDisplay3(武功级别描述3)
	private:
		YString m_wugongDisplay3; //属性wugongDisplay3(武功级别描述3)的成员变量
	public:
		YString getwugongDisplay3(void) {return m_wugongDisplay3;} //读属性wugongDisplay3(武功级别描述3)
		void setwugongDisplay3(YString newwugongDisplay3) {m_wugongDisplay3=newwugongDisplay3;} //设置wugongDisplay3(武功级别描述3)
	//属性：wugongDisplay4(武功级别描述4)
	private:
		YString m_wugongDisplay4; //属性wugongDisplay4(武功级别描述4)的成员变量
	public:
		YString getwugongDisplay4(void) {return m_wugongDisplay4;} //读属性wugongDisplay4(武功级别描述4)
		void setwugongDisplay4(YString newwugongDisplay4) {m_wugongDisplay4=newwugongDisplay4;} //设置wugongDisplay4(武功级别描述4)
	//属性：wugongDisplay5(武功级别描述5)
	private:
		YString m_wugongDisplay5; //属性wugongDisplay5(武功级别描述5)的成员变量
	public:
		YString getwugongDisplay5(void) {return m_wugongDisplay5;} //读属性wugongDisplay5(武功级别描述5)
		void setwugongDisplay5(YString newwugongDisplay5) {m_wugongDisplay5=newwugongDisplay5;} //设置wugongDisplay5(武功级别描述5)
	//属性：wugongDisplay6(武功级别描述6)
	private:
		YString m_wugongDisplay6; //属性wugongDisplay6(武功级别描述6)的成员变量
	public:
		YString getwugongDisplay6(void) {return m_wugongDisplay6;} //读属性wugongDisplay6(武功级别描述6)
		void setwugongDisplay6(YString newwugongDisplay6) {m_wugongDisplay6=newwugongDisplay6;} //设置wugongDisplay6(武功级别描述6)
	//属性：wugongDisplay7(武功级别描述7)
	private:
		YString m_wugongDisplay7; //属性wugongDisplay7(武功级别描述7)的成员变量
	public:
		YString getwugongDisplay7(void) {return m_wugongDisplay7;} //读属性wugongDisplay7(武功级别描述7)
		void setwugongDisplay7(YString newwugongDisplay7) {m_wugongDisplay7=newwugongDisplay7;} //设置wugongDisplay7(武功级别描述7)
	//属性：wugongDisplay8(武功级别描述8)
	private:
		YString m_wugongDisplay8; //属性wugongDisplay8(武功级别描述8)的成员变量
	public:
		YString getwugongDisplay8(void) {return m_wugongDisplay8;} //读属性wugongDisplay8(武功级别描述8)
		void setwugongDisplay8(YString newwugongDisplay8) {m_wugongDisplay8=newwugongDisplay8;} //设置wugongDisplay8(武功级别描述8)
	//属性：wugongDisplay9(武功级别描述9)
	private:
		YString m_wugongDisplay9; //属性wugongDisplay9(武功级别描述9)的成员变量
	public:
		YString getwugongDisplay9(void) {return m_wugongDisplay9;} //读属性wugongDisplay9(武功级别描述9)
		void setwugongDisplay9(YString newwugongDisplay9) {m_wugongDisplay9=newwugongDisplay9;} //设置wugongDisplay9(武功级别描述9)
	//属性：wugongDisplay10(武功级别描述10)
	private:
		YString m_wugongDisplay10; //属性wugongDisplay10(武功级别描述10)的成员变量
	public:
		YString getwugongDisplay10(void) {return m_wugongDisplay10;} //读属性wugongDisplay10(武功级别描述10)
		void setwugongDisplay10(YString newwugongDisplay10) {m_wugongDisplay10=newwugongDisplay10;} //设置wugongDisplay10(武功级别描述10)
	//属性：wugongDisplay11(武功级别描述11)
	private:
		YString m_wugongDisplay11; //属性wugongDisplay11(武功级别描述11)的成员变量
	public:
		YString getwugongDisplay11(void) {return m_wugongDisplay11;} //读属性wugongDisplay11(武功级别描述11)
		void setwugongDisplay11(YString newwugongDisplay11) {m_wugongDisplay11=newwugongDisplay11;} //设置wugongDisplay11(武功级别描述11)
	//属性：wugongDisplay12(武功级别描述12)
	private:
		YString m_wugongDisplay12; //属性wugongDisplay12(武功级别描述12)的成员变量
	public:
		YString getwugongDisplay12(void) {return m_wugongDisplay12;} //读属性wugongDisplay12(武功级别描述12)
		void setwugongDisplay12(YString newwugongDisplay12) {m_wugongDisplay12=newwugongDisplay12;} //设置wugongDisplay12(武功级别描述12)
	//属性：wugongDisplay13(武功级别描述13)
	private:
		YString m_wugongDisplay13; //属性wugongDisplay13(武功级别描述13)的成员变量
	public:
		YString getwugongDisplay13(void) {return m_wugongDisplay13;} //读属性wugongDisplay13(武功级别描述13)
		void setwugongDisplay13(YString newwugongDisplay13) {m_wugongDisplay13=newwugongDisplay13;} //设置wugongDisplay13(武功级别描述13)
	//属性：wugongDisplay14(武功级别描述14)
	private:
		YString m_wugongDisplay14; //属性wugongDisplay14(武功级别描述14)的成员变量
	public:
		YString getwugongDisplay14(void) {return m_wugongDisplay14;} //读属性wugongDisplay14(武功级别描述14)
		void setwugongDisplay14(YString newwugongDisplay14) {m_wugongDisplay14=newwugongDisplay14;} //设置wugongDisplay14(武功级别描述14)
	//属性：wugongDisplay15(武功级别描述15)
	private:
		YString m_wugongDisplay15; //属性wugongDisplay15(武功级别描述15)的成员变量
	public:
		YString getwugongDisplay15(void) {return m_wugongDisplay15;} //读属性wugongDisplay15(武功级别描述15)
		void setwugongDisplay15(YString newwugongDisplay15) {m_wugongDisplay15=newwugongDisplay15;} //设置wugongDisplay15(武功级别描述15)
	//属性：wugongDisplay16(武功级别描述16)
	private:
		YString m_wugongDisplay16; //属性wugongDisplay16(武功级别描述16)的成员变量
	public:
		YString getwugongDisplay16(void) {return m_wugongDisplay16;} //读属性wugongDisplay16(武功级别描述16)
		void setwugongDisplay16(YString newwugongDisplay16) {m_wugongDisplay16=newwugongDisplay16;} //设置wugongDisplay16(武功级别描述16)
	//属性：wugongDisplay17(武功级别描述17)
	private:
		YString m_wugongDisplay17; //属性wugongDisplay17(武功级别描述17)的成员变量
	public:
		YString getwugongDisplay17(void) {return m_wugongDisplay17;} //读属性wugongDisplay17(武功级别描述17)
		void setwugongDisplay17(YString newwugongDisplay17) {m_wugongDisplay17=newwugongDisplay17;} //设置wugongDisplay17(武功级别描述17)
	//属性：wugongDisplay18(武功级别描述18)
	private:
		YString m_wugongDisplay18; //属性wugongDisplay18(武功级别描述18)的成员变量
	public:
		YString getwugongDisplay18(void) {return m_wugongDisplay18;} //读属性wugongDisplay18(武功级别描述18)
		void setwugongDisplay18(YString newwugongDisplay18) {m_wugongDisplay18=newwugongDisplay18;} //设置wugongDisplay18(武功级别描述18)
	//属性：wugongDisplay19(武功级别描述19)
	private:
		YString m_wugongDisplay19; //属性wugongDisplay19(武功级别描述19)的成员变量
	public:
		YString getwugongDisplay19(void) {return m_wugongDisplay19;} //读属性wugongDisplay19(武功级别描述19)
		void setwugongDisplay19(YString newwugongDisplay19) {m_wugongDisplay19=newwugongDisplay19;} //设置wugongDisplay19(武功级别描述19)
	//属性：wugongDisplay20(武功级别描述20)
	private:
		YString m_wugongDisplay20; //属性wugongDisplay20(武功级别描述20)的成员变量
	public:
		YString getwugongDisplay20(void) {return m_wugongDisplay20;} //读属性wugongDisplay20(武功级别描述20)
		void setwugongDisplay20(YString newwugongDisplay20) {m_wugongDisplay20=newwugongDisplay20;} //设置wugongDisplay20(武功级别描述20)
	//属性：wugongDisplay21(武功级别描述21)
	private:
		YString m_wugongDisplay21; //属性wugongDisplay21(武功级别描述21)的成员变量
	public:
		YString getwugongDisplay21(void) {return m_wugongDisplay21;} //读属性wugongDisplay21(武功级别描述21)
		void setwugongDisplay21(YString newwugongDisplay21) {m_wugongDisplay21=newwugongDisplay21;} //设置wugongDisplay21(武功级别描述21)
	//属性：wugongDisplay22(武功级别描述22)
	private:
		YString m_wugongDisplay22; //属性wugongDisplay22(武功级别描述22)的成员变量
	public:
		YString getwugongDisplay22(void) {return m_wugongDisplay22;} //读属性wugongDisplay22(武功级别描述22)
		void setwugongDisplay22(YString newwugongDisplay22) {m_wugongDisplay22=newwugongDisplay22;} //设置wugongDisplay22(武功级别描述22)
	//属性：wugongDisplay23(武功级别描述23)
	private:
		YString m_wugongDisplay23; //属性wugongDisplay23(武功级别描述23)的成员变量
	public:
		YString getwugongDisplay23(void) {return m_wugongDisplay23;} //读属性wugongDisplay23(武功级别描述23)
		void setwugongDisplay23(YString newwugongDisplay23) {m_wugongDisplay23=newwugongDisplay23;} //设置wugongDisplay23(武功级别描述23)
	//属性：wugongDisplay24(武功级别描述24)
	private:
		YString m_wugongDisplay24; //属性wugongDisplay24(武功级别描述24)的成员变量
	public:
		YString getwugongDisplay24(void) {return m_wugongDisplay24;} //读属性wugongDisplay24(武功级别描述24)
		void setwugongDisplay24(YString newwugongDisplay24) {m_wugongDisplay24=newwugongDisplay24;} //设置wugongDisplay24(武功级别描述24)
	//属性：wugongDisplay25(武功级别描述25)
	private:
		YString m_wugongDisplay25; //属性wugongDisplay25(武功级别描述25)的成员变量
	public:
		YString getwugongDisplay25(void) {return m_wugongDisplay25;} //读属性wugongDisplay25(武功级别描述25)
		void setwugongDisplay25(YString newwugongDisplay25) {m_wugongDisplay25=newwugongDisplay25;} //设置wugongDisplay25(武功级别描述25)
	//属性：wugongDisplay26(武功级别描述26)
	private:
		YString m_wugongDisplay26; //属性wugongDisplay26(武功级别描述26)的成员变量
	public:
		YString getwugongDisplay26(void) {return m_wugongDisplay26;} //读属性wugongDisplay26(武功级别描述26)
		void setwugongDisplay26(YString newwugongDisplay26) {m_wugongDisplay26=newwugongDisplay26;} //设置wugongDisplay26(武功级别描述26)
	//属性：wugongDisplay27(武功级别描述27)
	private:
		YString m_wugongDisplay27; //属性wugongDisplay27(武功级别描述27)的成员变量
	public:
		YString getwugongDisplay27(void) {return m_wugongDisplay27;} //读属性wugongDisplay27(武功级别描述27)
		void setwugongDisplay27(YString newwugongDisplay27) {m_wugongDisplay27=newwugongDisplay27;} //设置wugongDisplay27(武功级别描述27)
	//属性：wugongDisplay28(武功级别描述28)
	private:
		YString m_wugongDisplay28; //属性wugongDisplay28(武功级别描述28)的成员变量
	public:
		YString getwugongDisplay28(void) {return m_wugongDisplay28;} //读属性wugongDisplay28(武功级别描述28)
		void setwugongDisplay28(YString newwugongDisplay28) {m_wugongDisplay28=newwugongDisplay28;} //设置wugongDisplay28(武功级别描述28)
	//属性：wugongDisplay29(武功级别描述29)
	private:
		YString m_wugongDisplay29; //属性wugongDisplay29(武功级别描述29)的成员变量
	public:
		YString getwugongDisplay29(void) {return m_wugongDisplay29;} //读属性wugongDisplay29(武功级别描述29)
		void setwugongDisplay29(YString newwugongDisplay29) {m_wugongDisplay29=newwugongDisplay29;} //设置wugongDisplay29(武功级别描述29)
	//属性：wugongDisplay30(武功级别描述30)
	private:
		YString m_wugongDisplay30; //属性wugongDisplay30(武功级别描述30)的成员变量
	public:
		YString getwugongDisplay30(void) {return m_wugongDisplay30;} //读属性wugongDisplay30(武功级别描述30)
		void setwugongDisplay30(YString newwugongDisplay30) {m_wugongDisplay30=newwugongDisplay30;} //设置wugongDisplay30(武功级别描述30)
	//属性：wugongDisplay31(武功级别描述31)
	private:
		YString m_wugongDisplay31; //属性wugongDisplay31(武功级别描述31)的成员变量
	public:
		YString getwugongDisplay31(void) {return m_wugongDisplay31;} //读属性wugongDisplay31(武功级别描述31)
		void setwugongDisplay31(YString newwugongDisplay31) {m_wugongDisplay31=newwugongDisplay31;} //设置wugongDisplay31(武功级别描述31)
	//属性：wugongDisplay32(武功级别描述32)
	private:
		YString m_wugongDisplay32; //属性wugongDisplay32(武功级别描述32)的成员变量
	public:
		YString getwugongDisplay32(void) {return m_wugongDisplay32;} //读属性wugongDisplay32(武功级别描述32)
		void setwugongDisplay32(YString newwugongDisplay32) {m_wugongDisplay32=newwugongDisplay32;} //设置wugongDisplay32(武功级别描述32)
	//属性：wugongDisplay33(武功级别描述33)
	private:
		YString m_wugongDisplay33; //属性wugongDisplay33(武功级别描述33)的成员变量
	public:
		YString getwugongDisplay33(void) {return m_wugongDisplay33;} //读属性wugongDisplay33(武功级别描述33)
		void setwugongDisplay33(YString newwugongDisplay33) {m_wugongDisplay33=newwugongDisplay33;} //设置wugongDisplay33(武功级别描述33)
	//属性：wugongDisplay34(武功级别描述34)
	private:
		YString m_wugongDisplay34; //属性wugongDisplay34(武功级别描述34)的成员变量
	public:
		YString getwugongDisplay34(void) {return m_wugongDisplay34;} //读属性wugongDisplay34(武功级别描述34)
		void setwugongDisplay34(YString newwugongDisplay34) {m_wugongDisplay34=newwugongDisplay34;} //设置wugongDisplay34(武功级别描述34)
	//属性：wugongDisplay35(武功级别描述35)
	private:
		YString m_wugongDisplay35; //属性wugongDisplay35(武功级别描述35)的成员变量
	public:
		YString getwugongDisplay35(void) {return m_wugongDisplay35;} //读属性wugongDisplay35(武功级别描述35)
		void setwugongDisplay35(YString newwugongDisplay35) {m_wugongDisplay35=newwugongDisplay35;} //设置wugongDisplay35(武功级别描述354)
	//属性：ciDisplay10(刺伤10)
	private:
		YString m_ciDisplay10; //属性ciDisplay10(刺伤10)的成员变量
	public:
		YString getciDisplay10(void) {return m_ciDisplay10;} //读属性ciDisplay10(刺伤10)
		void setciDisplay10(YString newciDisplay10) {m_ciDisplay10=newciDisplay10;} //设置ciDisplay10(刺伤10)
	//属性：ciDisplay20(刺伤20)
	private:
		YString m_ciDisplay20; //属性ciDisplay20(刺伤20)的成员变量
	public:
		YString getciDisplay20(void) {return m_ciDisplay20;} //读属性ciDisplay20(刺伤20)
		void setciDisplay20(YString newciDisplay20) {m_ciDisplay20=newciDisplay20;} //设置ciDisplay20(刺伤20)
	//属性：ciDisplay40(刺伤40)
	private:
		YString m_ciDisplay40; //属性ciDisplay40(刺伤40)的成员变量
	public:
		YString getciDisplay40(void) {return m_ciDisplay40;} //读属性ciDisplay40(刺伤40)
		void setciDisplay40(YString newciDisplay40) {m_ciDisplay40=newciDisplay40;} //设置ciDisplay40(刺伤40)
	//属性：ciDisplay80(刺伤80)
	private:
		YString m_ciDisplay80; //属性ciDisplay80(刺伤80)的成员变量
	public:
		YString getciDisplay80(void) {return m_ciDisplay80;} //读属性ciDisplay80(刺伤80)
		void setciDisplay80(YString newciDisplay80) {m_ciDisplay80=newciDisplay80;} //设置ciDisplay80(刺伤80)
	//属性：ciDisplay120(刺伤120)
	private:
		YString m_ciDisplay120; //属性ciDisplay120(刺伤120)的成员变量
	public:
		YString getciDisplay120(void) {return m_ciDisplay120;} //读属性ciDisplay120(刺伤120)
		void setciDisplay120(YString newciDisplay120) {m_ciDisplay120=newciDisplay120;} //设置ciDisplay120(刺伤120)
	//属性：ciDisplay160u(刺伤160上)
	private:
		YString m_ciDisplay160u; //属性ciDisplay160u(刺伤160上)的成员变量
	public:
		YString getciDisplay160u(void) {return m_ciDisplay160u;} //读属性ciDisplay160u(刺伤160上)
		void setciDisplay160u(YString newciDisplay160u) {m_ciDisplay160u=newciDisplay160u;} //设置ciDisplay160u(刺伤160上)
	//属性：ciDisplay160d(刺伤160下)
	private:
		YString m_ciDisplay160d; //属性ciDisplay160d(刺伤160下)的成员变量
	public:
		YString getciDisplay160d(void) {return m_ciDisplay160d;} //读属性ciDisplay160d(刺伤160下)
		void setciDisplay160d(YString newciDisplay160d) {m_ciDisplay160d=newciDisplay160d;} //设置ciDisplay160d(刺伤160下)
	//属性：kongDisplay10(空手伤10)
	private:
		YString m_kongDisplay10; //属性kongDisplay10(空手伤10)的成员变量
	public:
		YString getkongDisplay10(void) {return m_kongDisplay10;} //读属性kongDisplay10(空手伤10)
		void setkongDisplay10(YString newkongDisplay10) {m_kongDisplay10=newkongDisplay10;} //设置kongDisplay10(空手伤10)
	//属性：kongDisplay20(空手伤20)
	private:
		YString m_kongDisplay20; //属性kongDisplay20(空手伤20)的成员变量
	public:
		YString getkongDisplay20(void) {return m_kongDisplay20;} //读属性kongDisplay20(空手伤20)
		void setkongDisplay20(YString newkongDisplay20) {m_kongDisplay20=newkongDisplay20;} //设置kongDisplay20(空手伤20)
	//属性：kongDisplay40(空手伤40)
	private:
		YString m_kongDisplay40; //属性kongDisplay40(空手伤40)的成员变量
	public:
		YString getkongDisplay40(void) {return m_kongDisplay40;} //读属性kongDisplay40(空手伤40)
		void setkongDisplay40(YString newkongDisplay40) {m_kongDisplay40=newkongDisplay40;} //设置kongDisplay40(空手伤40)
	//属性：kongDisplay80(空手伤80)
	private:
		YString m_kongDisplay80; //属性kongDisplay80(空手伤80)的成员变量
	public:
		YString getkongDisplay80(void) {return m_kongDisplay80;} //读属性kongDisplay80(空手伤80)
		void setkongDisplay80(YString newkongDisplay80) {m_kongDisplay80=newkongDisplay80;} //设置kongDisplay80(空手伤80)
	//属性：kongDisplay120(空手伤120)
	private:
		YString m_kongDisplay120; //属性kongDisplay120(空手伤120)的成员变量
	public:
		YString getkongDisplay120(void) {return m_kongDisplay120;} //读属性kongDisplay120(空手伤120)
		void setkongDisplay120(YString newkongDisplay120) {m_kongDisplay120=newkongDisplay120;} //设置kongDisplay120(空手伤120)
	//属性：kongDisplay160(空手伤160)
	private:
		YString m_kongDisplay160; //属性kongDisplay160(空手伤160)的成员变量
	public:
		YString getkongDisplay160(void) {return m_kongDisplay160;} //读属性kongDisplay160(空手伤160)
		void setkongDisplay160(YString newkongDisplay160) {m_kongDisplay160=newkongDisplay160;} //设置kongDisplay160(空手伤160)
	//属性：kongDisplay200(空手伤200)
	private:
		YString m_kongDisplay200; //属性kongDisplay200(空手伤200)的成员变量
	public:
		YString getkongDisplay200(void) {return m_kongDisplay200;} //读属性kongDisplay200(空手伤200)
		void setkongDisplay200(YString newkongDisplay200) {m_kongDisplay200=newkongDisplay200;} //设置kongDisplay200(空手伤200)
	//属性：kanDisplay10(砍伤10)
	private:
		YString m_kanDisplay10; //属性kanDisplay10(砍伤10)的成员变量
	public:
		YString getkanDisplay10(void) {return m_kanDisplay10;} //读属性kanDisplay10(砍伤10)
		void setkanDisplay10(YString newkanDisplay10) {m_kanDisplay10=newkanDisplay10;} //设置kanDisplay10(砍伤10)
	//属性：kanDisplay20(砍伤20)
	private:
		YString m_kanDisplay20; //属性kanDisplay20(砍伤20)的成员变量
	public:
		YString getkanDisplay20(void) {return m_kanDisplay20;} //读属性kanDisplay20(砍伤20)
		void setkanDisplay20(YString newkanDisplay20) {m_kanDisplay20=newkanDisplay20;} //设置kanDisplay20(砍伤20)
	//属性：kanDisplay40(砍伤40)
	private:
		YString m_kanDisplay40; //属性kanDisplay40(砍伤40)的成员变量
	public:
		YString getkanDisplay40(void) {return m_kanDisplay40;} //读属性kanDisplay40(砍伤40)
		void setkanDisplay40(YString newkanDisplay40) {m_kanDisplay40=newkanDisplay40;} //设置kanDisplay40(砍伤40)
	//属性：kanDisplay80(砍伤80)
	private:
		YString m_kanDisplay80; //属性kanDisplay80(砍伤80)的成员变量
	public:
		YString getkanDisplay80(void) {return m_kanDisplay80;} //读属性kanDisplay80(砍伤80)
		void setkanDisplay80(YString newkanDisplay80) {m_kanDisplay80=newkanDisplay80;} //设置kanDisplay80(砍伤80)
	//属性：kanDisplay120(砍伤120)
	private:
		YString m_kanDisplay120; //属性kanDisplay120(砍伤120)的成员变量
	public:
		YString getkanDisplay120(void) {return m_kanDisplay120;} //读属性kanDisplay120(砍伤120)
		void setkanDisplay120(YString newkanDisplay120) {m_kanDisplay120=newkanDisplay120;} //设置kanDisplay120(砍伤120)
	//属性：kanDisplay160(砍伤160)
	private:
		YString m_kanDisplay160; //属性kanDisplay160(砍伤160)的成员变量
	public:
		YString getkanDisplay160(void) {return m_kanDisplay160;} //读属性kanDisplay160(砍伤160)
		void setkanDisplay160(YString newkanDisplay160) {m_kanDisplay160=newkanDisplay160;} //设置kanDisplay160(砍伤160)
	//属性：yaoDisplay10(咬伤10)
	private:
		YString m_yaoDisplay10; //属性yaoDisplay10(咬伤10)的成员变量
	public:
		YString getyaoDisplay10(void) {return m_yaoDisplay10;} //读属性yaoDisplay10(咬伤10)
		void setyaoDisplay10(YString newyaoDisplay10) {m_yaoDisplay10=newyaoDisplay10;} //设置yaoDisplay10(咬伤10)
	//属性：yaoDisplay20(咬伤20)
	private:
		YString m_yaoDisplay20; //属性yaoDisplay20(咬伤20)的成员变量
	public:
		YString getyaoDisplay20(void) {return m_yaoDisplay20;} //读属性yaoDisplay20(咬伤20)
		void setyaoDisplay20(YString newyaoDisplay20) {m_yaoDisplay20=newyaoDisplay20;} //设置yaoDisplay20(咬伤20)
	//属性：yaoDisplay40(咬伤40)
	private:
		YString m_yaoDisplay40; //属性yaoDisplay40(咬伤40)的成员变量
	public:
		YString getyaoDisplay40(void) {return m_yaoDisplay40;} //读属性yaoDisplay40(咬伤40)
		void setyaoDisplay40(YString newyaoDisplay40) {m_yaoDisplay40=newyaoDisplay40;} //设置yaoDisplay40(咬伤40)
	//属性：yaoDisplay80(咬伤80)
	private:
		YString m_yaoDisplay80; //属性yaoDisplay80(咬伤80)的成员变量
	public:
		YString getyaoDisplay80(void) {return m_yaoDisplay80;} //读属性yaoDisplay80(咬伤80)
		void setyaoDisplay80(YString newyaoDisplay80) {m_yaoDisplay80=newyaoDisplay80;} //设置yaoDisplay80(咬伤80)
	//属性：yaoDisplay120(咬伤120)
	private:
		YString m_yaoDisplay120; //属性yaoDisplay120(咬伤120)的成员变量
	public:
		YString getyaoDisplay120(void) {return m_yaoDisplay120;} //读属性yaoDisplay120(咬伤120)
		void setyaoDisplay120(YString newyaoDisplay120) {m_yaoDisplay120=newyaoDisplay120;} //设置yaoDisplay120(咬伤120)
	//属性：shanghai5(伤害描述5)
	private:
		YString m_shanghai5; //属性shanghai5(伤害描述5)的成员变量
	public:
		YString getshanghai5(void) {return m_shanghai5;} //读属性shanghai5(伤害描述5)
		void setshanghai5(YString newshanghai5) {m_shanghai5=newshanghai5;} //设置shanghai5(伤害描述5)
	//属性：shanghai10(伤害描述10)
	private:
		YString m_shanghai10; //属性shanghai10(伤害描述10)的成员变量
	public:
		YString getshanghai10(void) {return m_shanghai10;} //读属性shanghai10(伤害描述10)
		void setshanghai10(YString newshanghai10) {m_shanghai10=newshanghai10;} //设置shanghai10(伤害描述10)
	//属性：shanghai20(伤害描述20)
	private:
		YString m_shanghai20; //属性shanghai20(伤害描述20)的成员变量
	public:
		YString getshanghai20(void) {return m_shanghai20;} //读属性shanghai20(伤害描述20)
		void setshanghai20(YString newshanghai20) {m_shanghai20=newshanghai20;} //设置shanghai20(伤害描述20)
	//属性：shanghai30(伤害描述30)
	private:
		YString m_shanghai30; //属性shanghai30(伤害描述30)的成员变量
	public:
		YString getshanghai30(void) {return m_shanghai30;} //读属性shanghai30(伤害描述30)
		void setshanghai30(YString newshanghai30) {m_shanghai30=newshanghai30;} //设置shanghai30(伤害描述30)
	//属性：shanghai50(伤害描述50)
	private:
		YString m_shanghai50; //属性shanghai50(伤害描述50)的成员变量
	public:
		YString getshanghai50(void) {return m_shanghai50;} //读属性shanghai50(伤害描述50)
		void setshanghai50(YString newshanghai50) {m_shanghai50=newshanghai50;} //设置shanghai50(伤害描述50)
	//属性：shanghai80(伤害描述80)
	private:
		YString m_shanghai80; //属性shanghai80(伤害描述80)的成员变量
	public:
		YString getshanghai80(void) {return m_shanghai80;} //读属性shanghai80(伤害描述80)
		void setshanghai80(YString newshanghai80) {m_shanghai80=newshanghai80;} //设置shanghai80(伤害描述80)
	//属性：shanghai100(伤害描述100)
	private:
		YString m_shanghai100; //属性shanghai100(伤害描述100)的成员变量
	public:
		YString getshanghai100(void) {return m_shanghai100;} //读属性shanghai100(伤害描述100)
		void setshanghai100(YString newshanghai100) {m_shanghai100=newshanghai100;} //设置shanghai100(伤害描述100)
	//属性：shanghai160(伤害描述160)
	private:
		YString m_shanghai160; //属性shanghai160(伤害描述160)的成员变量
	public:
		YString getshanghai160(void) {return m_shanghai160;} //读属性shanghai160(伤害描述160)
		void setshanghai160(YString newshanghai160) {m_shanghai160=newshanghai160;} //设置shanghai160(伤害描述160)
	//属性：shanghai200(伤害描述200)
	private:
		YString m_shanghai200; //属性shanghai200(伤害描述200)的成员变量
	public:
		YString getshanghai200(void) {return m_shanghai200;} //读属性shanghai200(伤害描述200)
		void setshanghai200(YString newshanghai200) {m_shanghai200=newshanghai200;} //设置shanghai200(伤害描述200)
	//属性：haltDisplay1(停手描述1)
	private:
		YString m_haltDisplay1; //属性haltDisplay1(停手描述1)的成员变量
	public:
		YString gethaltDisplay1(void) {return m_haltDisplay1;} //读属性haltDisplay1(停手描述1)
		void sethaltDisplay1(YString newhaltDisplay1) {m_haltDisplay1=newhaltDisplay1;} //设置haltDisplay1(停手描述1)
	//属性：haltDisplay2(停手描述2)
	private:
		YString m_haltDisplay2; //属性haltDisplay2(停手描述2)的成员变量
	public:
		YString gethaltDisplay2(void) {return m_haltDisplay2;} //读属性haltDisplay2(停手描述2)
		void sethaltDisplay2(YString newhaltDisplay2) {m_haltDisplay2=newhaltDisplay2;} //设置haltDisplay2(停手描述2)
	//属性：haltDisplay3(停手描述3)
	private:
		YString m_haltDisplay3; //属性haltDisplay3(停手描述3)的成员变量
	public:
		YString gethaltDisplay3(void) {return m_haltDisplay3;} //读属性haltDisplay3(停手描述3)
		void sethaltDisplay3(YString newhaltDisplay3) {m_haltDisplay3=newhaltDisplay3;} //设置haltDisplay3(停手描述3)
	//属性：haltDisplay4(停手描述4)
	private:
		YString m_haltDisplay4; //属性haltDisplay4(停手描述4)的成员变量
	public:
		YString gethaltDisplay4(void) {return m_haltDisplay4;} //读属性haltDisplay4(停手描述4)
		void sethaltDisplay4(YString newhaltDisplay4) {m_haltDisplay4=newhaltDisplay4;} //设置haltDisplay4(停手描述4)
	//属性：haltDisplay5(停手描述5)
	private:
		YString m_haltDisplay5; //属性haltDisplay5(停手描述5)的成员变量
	public:
		YString gethaltDisplay5(void) {return m_haltDisplay5;} //读属性haltDisplay5(停手描述5)
		void sethaltDisplay5(YString newhaltDisplay5) {m_haltDisplay5=newhaltDisplay5;} //设置haltDisplay5(停手描述5)
	//属性：haltDisplay6(停手描述6)
	private:
		YString m_haltDisplay6; //属性haltDisplay6(停手描述6)的成员变量
	public:
		YString gethaltDisplay6(void) {return m_haltDisplay6;} //读属性haltDisplay6(停手描述6)
		void sethaltDisplay6(YString newhaltDisplay6) {m_haltDisplay6=newhaltDisplay6;} //设置haltDisplay6(停手描述6)
	//属性：haltDisplay7(停手描述7)
	private:
		YString m_haltDisplay7; //属性haltDisplay7(停手描述7)的成员变量
	public:
		YString gethaltDisplay7(void) {return m_haltDisplay7;} //读属性haltDisplay7(停手描述7)
		void sethaltDisplay7(YString newhaltDisplay7) {m_haltDisplay7=newhaltDisplay7;} //设置haltDisplay7(停手描述7)
	//属性：haltDisplay8(停手描述8)
	private:
		YString m_haltDisplay8; //属性haltDisplay8(停手描述8)的成员变量
	public:
		YString gethaltDisplay8(void) {return m_haltDisplay8;} //读属性haltDisplay8(停手描述8)
		void sethaltDisplay8(YString newhaltDisplay8) {m_haltDisplay8=newhaltDisplay8;} //设置haltDisplay8(停手描述8)
	//属性：haltDisplay9(停手描述9)
	private:
		YString m_haltDisplay9; //属性haltDisplay9(停手描述9)的成员变量
	public:
		YString gethaltDisplay9(void) {return m_haltDisplay9;} //读属性haltDisplay9(停手描述9)
		void sethaltDisplay9(YString newhaltDisplay9) {m_haltDisplay9=newhaltDisplay9;} //设置haltDisplay9(停手描述9)
	//属性：haltDisplay10(停手描述10)
	private:
		YString m_haltDisplay10; //属性haltDisplay10(停手描述10)的成员变量
	public:
		YString gethaltDisplay10(void) {return m_haltDisplay10;} //读属性haltDisplay10(停手描述10)
		void sethaltDisplay10(YString newhaltDisplay10) {m_haltDisplay10=newhaltDisplay10;} //设置haltDisplay10(停手描述10)
	//属性：haltDisplay11(停手描述11)
	private:
		YString m_haltDisplay11; //属性haltDisplay11(停手描述11)的成员变量
	public:
		YString gethaltDisplay11(void) {return m_haltDisplay11;} //读属性haltDisplay11(停手描述11)
		void sethaltDisplay11(YString newhaltDisplay11) {m_haltDisplay11=newhaltDisplay11;} //设置haltDisplay11(停手描述11)
	//属性：workskills(劳动技能)
	private:
		YString m_workskills; //属性workskills(劳动技能)的成员变量
	public:
		YString getworkskills(void) {return m_workskills;} //读属性workskills(劳动技能)
		void setworkskills(YString newworkskills) {m_workskills=newworkskills;} //设置workskills(劳动技能)
	//属性：balckip(关闭ip)
	private:
		YString m_blackip; //balckip(关闭ip)属性的成员变量
	public:
		YString getblackip(void) {return m_blackip;} //读属性blackip
		void setblackip(YString newblackip) {m_blackip=newblackip;} //设置blackip

//长型变量
	//属性：sitMinX(min_x)
	private:
		long m_sitMinX; //属性sitMinX(min_x)的成员变量
	public:
		long getsitMinX(void) {return m_sitMinX;} //读属性sitMinX(min_x)
		void setsitMinX(long newsitMinX) {m_sitMinX=newsitMinX;} //设置sitMinX(min_x)

	//属性：sitMinY(min_y)
	private:
		long m_sitMinY; //属性sitMinY(min_y)的成员变量
	public:
		long getsitMinY(void) {return m_sitMinY;} //读属性sitMinY(min_y)
		void setsitMinY(long newsitMinY) {m_sitMinY=newsitMinY;} //设置sitMinY(min_y)

	//属性：sitMaxX(max_x)
	private:
		long m_sitMaxX; //属性sitMaxX(max_x)的成员变量
	public:
		long getsitMaxX(void) {return m_sitMaxX;} //读属性sitMaxX(max_x)
		void setsitMaxX(long newsitMaxX) {m_sitMaxX=newsitMaxX;} //设置sitMaxX(max_x)

	//属性：sitMaxY(max_y)
	private:
		long m_sitMaxY; //属性sitMaxY(max_y)的成员变量
	public:
		long getsitMaxY(void) {return m_sitMaxY;} //读属性sitMaxY(max_y)
		void setsitMaxY(long newsitMaxY) {m_sitMaxY=newsitMaxY;} //设置sitMaxY(max_y)

	//属性：sitIEOvertime(浏览器超时)
	private:
		long m_sitIEOvertime; //属性sitIEOvertime(浏览器超时)的成员变量
	public:
		long getsitIEOvertime(void) {return m_sitIEOvertime;} //读属性sitIEOvertime(浏览器超时)
		void setsitIEOvertime(long newsitIEOvertime) {m_sitIEOvertime=newsitIEOvertime;} //设置sitIEOvertime(浏览器超时)

	//属性：sitDazeTime(发呆时间)
	private:
		long m_sitDazeTime; //属性sitDazeTime(发呆时间)的成员变量
	public:
		long getsitDazeTime(void) {return m_sitDazeTime;} //读属性sitDazeTime(发呆时间)
		void setsitDazeTime(long newsitDazeTime) {m_sitDazeTime=newsitDazeTime;} //设置sitDazeTime(发呆时间)

	//属性：sitLoseTime(掉线时间)
	private:
		long m_sitLoseTime; //属性sitLoseTime(掉线时间)的成员变量
	public:
		long getsitLoseTime(void) {return m_sitLoseTime;} //读属性sitLoseTime(掉线时间)
		void setsitLoseTime(long newsitLoseTime) {m_sitLoseTime=newsitLoseTime;} //设置sitLoseTime(掉线时间)

	//属性：sitbodyRenewSpeed(身体恢复速度)
	private:
		long m_sitbodyRenewSpeed; //属性sitbodyRenewSpeed(身体恢复速度)的成员变量
	public:
		long getsitbodyRenewSpeed(void) {return m_sitbodyRenewSpeed;} //读属性sitbodyRenewSpeed(身体恢复速度)
		void setsitbodyRenewSpeed(long newsitbodyRenewSpeed) {m_sitbodyRenewSpeed=newsitbodyRenewSpeed;} //设置sitbodyRenewSpeed(身体恢复速度)

	//属性：sitFoodSpendTime(食品消耗时间)
	private:
		long m_sitFoodSpendTime; //属性sitFoodSpendTime(食品消耗时间)的成员变量
	public:
		long getsitFoodSpendTime(void) {return m_sitFoodSpendTime;} //读属性sitFoodSpendTime(食品消耗时间)
		void setsitFoodSpendTime(long newsitFoodSpendTime) {m_sitFoodSpendTime=newsitFoodSpendTime;} //设置sitFoodSpendTime(食品消耗时间)

	//属性：sitFightSkipTime(战斗间隔)
	private:
		long m_sitFightSkipTime; //属性sitFightSkipTime(战斗间隔)的成员变量
	public:
		long getsitFightSkipTime(void) {return m_sitFightSkipTime;} //读属性sitFightSkipTime(战斗间隔)
		void setsitFightSkipTime(long newsitFightSkipTime) {m_sitFightSkipTime=newsitFightSkipTime;} //设置sitFightSkipTime(战斗间隔)

	//属性：sitFoodSpend(食品消耗)
	private:
		long m_sitFoodSpend; //属性sitFoodSpend(食品消耗)的成员变量
	public:
		long getsitFoodSpend(void) {return m_sitFoodSpend;} //读属性sitFoodSpend(食品消耗)
		void setsitFoodSpend(long newsitFoodSpend) {m_sitFoodSpend=newsitFoodSpend;} //设置sitFoodSpend(食品消耗)

	//属性：sitAgeUpTime(年龄增长速度)
	private:
		long m_sitAgeUpTime; //属性sitAgeUpTime(年龄增长速度)的成员变量
	public:
		long getsitAgeUpTime(void) {return m_sitAgeUpTime;} //读属性sitAgeUpTime(年龄增长速度)
		void setsitAgeUpTime(long newsitAgeUpTime) {m_sitAgeUpTime=newsitAgeUpTime;} //设置sitAgeUpTime(年龄增长速度)

	//属性：sitFaintTime(晕倒时间)
	private:
		long m_sitFaintTime; //属性sitFaintTime(晕倒时间)的成员变量
	public:
		long getsitFaintTime(void) {return m_sitFaintTime;} //读属性sitFaintTime(晕倒时间)
		void setsitFaintTime(long newsitFaintTime) {m_sitFaintTime=newsitFaintTime;} //设置sitFaintTime(晕倒时间)

	//属性：sitFleeChance(逃跑机会)
	private:
		long m_sitFleeChance; //属性sitFleeChance(逃跑机会)的成员变量
	public:
		long getsitFleeChance(void) {return m_sitFleeChance;} //读属性sitFleeChance(逃跑机会)
		void setsitFleeChance(long newsitFleeChance) {m_sitFleeChance=newsitFleeChance;} //设置sitFleeChance(逃跑机会)

	//属性：sitFightUp(战斗成长)
	private:
		long m_sitFightUp; //属性sitFightUp(战斗成长)的成员变量
	public:
		long getsitFightUp(void) {return m_sitFightUp;} //读属性sitFightUp(战斗成长)
		void setsitFightUp(long newsitFightUp) {m_sitFightUp=newsitFightUp;} //设置sitFightUp(战斗成长)

	//属性：sitlianSpendqian(练武消耗潜能)
	private:
		long m_sitlianSpendqian; //属性sitlianSpendqian(练武消耗潜能)的成员变量
	public:
		long getsitlianSpendqian(void) {return m_sitlianSpendqian;} //读属性sitlianSpendqian(练武消耗潜能)
		void setsitlianSpendqian(long newsitlianSpendqian) {m_sitlianSpendqian=newsitlianSpendqian;} //设置sitlianSpendqian(练武消耗潜能)

	//属性：sitHitExpChange(攻击经验转换)
	private:
		long m_sitHitExpChange; //属性sitHitExpChange(攻击经验转换)的成员变量
	public:
		long getsitHitExpChange(void) {return m_sitHitExpChange;} //读属性sitHitExpChange(攻击经验转换)
		void setsitHitExpChange(long newsitHitExpChange) {m_sitHitExpChange=newsitHitExpChange;} //设置sitHitExpChange(攻击经验转换)

	//属性：sitDefExpChange(防御经验转换)
	private:
		long m_sitDefExpChange; //属性sitDefExpChange(防御经验转换)的成员变量
	public:
		long getsitDefExpChange(void) {return m_sitDefExpChange;} //读属性sitDefExpChange(防御经验转换)
		void setsitDefExpChange(long newsitDefExpChange) {m_sitDefExpChange=newsitDefExpChange;} //设置sitDefExpChange(防御经验转换)

	//属性：sitHitScale(攻击力比例)
	private:
		long m_sitHitScale; //属性sitHitScale(攻击力比例)的成员变量
	public:
		long getsitHitScale(void) {return m_sitHitScale;} //读属性sitHitScale(攻击力比例)
		void setsitHitScale(long newsitHitScale) {m_sitHitScale=newsitHitScale;} //设置sitHitScale(攻击力比例)

	//属性：sitDefScale(防御力比例)
	private:
		long m_sitDefScale; //属性sitDefScale(防御力比例)的成员变量
	public:
		long getsitDefScale(void) {return m_sitDefScale;} //读属性sitDefScale(防御力比例)
		void setsitDefScale(long newsitDefScale) {m_sitDefScale=newsitDefScale;} //设置sitDefScale(防御力比例)

	//属性：sitLelForceUp(每级内力增长)
	private:
		long m_sitLelForceUp; //属性sitLelForceUp(每级内力增长)的成员变量
	public:
		long getsitLelForceUp(void) {return m_sitLelForceUp;} //读属性sitLelForceUp(每级内力增长)
		void setsitLelForceUp(long newsitLelForceUp) {m_sitLelForceUp=newsitLelForceUp;} //设置sitLelForceUp(每级内力增长)

	//属性：sitLelBodyUp(每级气血增长)
	private:
		long m_sitLelBodyUp; //属性sitLelBodyUp(每级气血增长)的成员变量
	public:
		long getsitLelBodyUp(void) {return m_sitLelBodyUp;} //读属性sitLelBodyUp(每级气血增长)
		void setsitLelBodyUp(long newsitLelBodyUp) {m_sitLelBodyUp=newsitLelBodyUp;} //设置sitLelBodyUp(每级气血增长)

	//属性：sitLelBookUp(每级读书增长)
	private:
		long m_sitLelBookUp; //属性sitLelBookUp(每级读书增长)的成员变量
	public:
		long getsitLelBookUp(void) {return m_sitLelBookUp;} //读属性sitLelBookUp(每级读书增长)
		void setsitLelBookUp(long newsitLelBookUp) {m_sitLelBookUp=newsitLelBookUp;} //设置sitLelBookUp(每级读书增长)

	//属性：sitNpcBody(NPC气血)
	private:
		long m_sitNpcBody; //属性sitNpcBody(NPC气血)的成员变量
	public:
		long getsitNpcBody(void) {return m_sitNpcBody;} //读属性sitNpcBody(NPC气血)
		void setsitNpcBody(long newsitNpcBody) {m_sitNpcBody=newsitNpcBody;} //设置sitNpcBody(NPC气血)

	//属性：sitNpcHit(NPC默认攻击)
	private:
		long m_sitNpcHit; //属性sitNpcHit(NPC默认攻击)的成员变量
	public:
		long getsitNpcHit(void) {return m_sitNpcHit;} //读属性sitNpcHit(NPC默认攻击)
		void setsitNpcHit(long newsitNpcHit) {m_sitNpcHit=newsitNpcHit;} //设置sitNpcHit(NPC默认攻击)

	//属性：sitNpcDef(NPC默认防御)
	private:
		long m_sitNpcDef; //属性sitNpcDef(NPC默认防御)的成员变量
	public:
		long getsitNpcDef(void) {return m_sitNpcDef;} //读属性sitNpcDef(NPC默认防御)
		void setsitNpcDef(long newsitNpcDef) {m_sitNpcDef=newsitNpcDef;} //设置sitNpcDef(NPC默认防御)

	//属性：sitNpcLevel(NPC武功级别)
	private:
		long m_sitNpcLevel; //属性sitNpcLevel(NPC武功级别)的成员变量
	public:
		long getsitNpcLevel(void) {return m_sitNpcLevel;} //读属性sitNpcLevel(NPC武功级别)
		void setsitNpcLevel(long newsitNpcLevel) {m_sitNpcLevel=newsitNpcLevel;} //设置sitNpcLevel(NPC武功级别)

	//属性：sitRefurbishTimeSkip(刷新时间间隔)
	private:
		long m_sitRefurbishTimeSkip; //属性sitRefurbishTimeSkip(刷新时间间隔)的成员变量
	public:
		long getsitRefurbishTimeSkip(void) {return m_sitRefurbishTimeSkip;} //读属性sitRefurbishTimeSkip(刷新时间间隔)
		void setsitRefurbishTimeSkip(long newsitRefurbishTimeSkip) {m_sitRefurbishTimeSkip=newsitRefurbishTimeSkip;} //设置sitRefurbishTimeSkip(刷新时间间隔)

	//属性：sitPowerUpTime(powerup时间)
	private:
		long m_sitPowerUpTime; //属性sitPowerUpTime(powerup时间)的成员变量
	public:
		long getsitPowerUpTime(void) {return m_sitPowerUpTime;} //读属性sitPowerUpTime(powerup时间)
		void setsitPowerUpTime(long newsitPowerUpTime) {m_sitPowerUpTime=newsitPowerUpTime;} //设置sitPowerUpTime(powerup时间)

	//属性：sitNewbieBeginAge(新手开始年龄)
	private:
		long m_sitNewbieBeginAge; //属性sitNewbieBeginAge(新手开始年龄)的成员变量
	public:
		long getsitNewbieBeginAge(void) {return m_sitNewbieBeginAge;} //读属性sitNewbieBeginAge(新手开始年龄)
		void setsitNewbieBeginAge(long newsitNewbieBeginAge) {m_sitNewbieBeginAge=newsitNewbieBeginAge;} //设置sitNewbieBeginAge(新手开始年龄)

	//属性：sitNewbieAge(新手年龄)
	private:
		long m_sitNewbieAge; //属性sitNewbieAge(新手年龄)的成员变量
	public:
		long getsitNewbieAge(void) {return m_sitNewbieAge;} //读属性sitNewbieAge(新手年龄)
		void setsitNewbieAge(long newsitNewbieAge) {m_sitNewbieAge=newsitNewbieAge;} //设置sitNewbieAge(新手年龄)

	//属性：sitLianSpendJing(练功精力)
	private:
		long m_sitLianSpendJing; //属性sitLianSpendJing(练功精力)的成员变量
	public:
		long getsitLianSpendJing(void) {return m_sitLianSpendJing;} //读属性sitLianSpendJing(练功精力)
		void setsitLianSpendJing(long newsitLianSpendJing) {m_sitLianSpendJing=newsitLianSpendJing;} //设置sitLianSpendJing(练功精力)

	//属性：sitLianSpendQi(练功气血)
	private:
		long m_sitLianSpendQi; //属性sitLianSpendQi(练功气血)的成员变量
	public:
		long getsitLianSpendQi(void) {return m_sitLianSpendQi;} //读属性sitLianSpendQi(练功气血)
		void setsitLianSpendQi(long newsitLianSpendQi) {m_sitLianSpendQi=newsitLianSpendQi;} //设置sitLianSpendQi(练功气血)

	//属性：sitLianUp(练功成长)
	private:
		long m_sitLianUp; //属性sitLianUp(练功成长)的成员变量
	public:
		long getsitLianUp(void) {return m_sitLianUp;} //读属性sitLianUp(练功成长)
		void setsitLianUp(long newsitLianUp) {m_sitLianUp=newsitLianUp;} //设置sitLianUp(练功成长)

	//属性：sitQuestExpUpLimit(任务奖励经验上限)
	private:
		long m_sitQuestExpUpLimit; //属性sitQuestExpUpLimit(任务奖励经验上限)的成员变量
	public:
		long getsitQuestExpUpLimit(void) {return m_sitQuestExpUpLimit;} //读属性sitQuestExpUpLimit(任务奖励经验上限)
		void setsitQuestExpUpLimit(long newsitQuestExpUpLimit) {m_sitQuestExpUpLimit=newsitQuestExpUpLimit;} //设置sitQuestExpUpLimit(任务奖励经验上限)

	//属性：sitQuestQianUpLimit(任务奖励潜能上限)
	private:
		long m_sitQuestQianUpLimit; //属性sitQuestQianUpLimit(任务奖励潜能上限)的成员变量
	public:
		long getsitQuestQianUpLimit(void) {return m_sitQuestQianUpLimit;} //读属性sitQuestQianUpLimit(任务奖励潜能上限)
		void setsitQuestQianUpLimit(long newsitQuestQianUpLimit) {m_sitQuestQianUpLimit=newsitQuestQianUpLimit;} //设置sitQuestQianUpLimit(任务奖励潜能上限)
	//属性：TextCost(大车的消耗)
	private:
		long m_sitTextCost; //属性TextCost(大车的消耗)的成员变量
	public:
		long getsitTextCost(void) {return m_sitTextCost;} //读属性sitTextCost(大车的消耗)
		void setsitTextCost(long newsitTextCost) {m_sitTextCost=newsitTextCost;} //设置sitTextCost(大车的消耗)




#ifdef __WIN32__
    YString getPathSeparator(void) {return "\\";}
#else
    YString getPathSeparator(void) {return "/";}
#endif //__WIN32__
  protected:
    void processPhrase(char *s); //处理Var=Val格式语句
    void setDefaultValues(void);
    void setInternalVaribles(void); //将属性转存到成员变量中
  public:
    YMUDSettings();
    YMUDSettings(int argc, char* argv[],char* filename);
    int load(int argc, char* argv[],char* filename);
    ~YMUDSettings(){delete m_property_group;};

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

};
#ifdef __WIN32__
  #define PATH(p) (convertToWinPath(p))
#else
  #define PATH(p) (p)
#endif //__WIN32__
YString convertToWinPath(const YString unixpath);
#endif //__YMUDSETTINGS_H__

