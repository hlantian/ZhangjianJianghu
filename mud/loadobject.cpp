//---------------------------------------------------------------------------
//
// loadobject.cpp    2000年6月12日
//
// 函数loadobject：根据类名建立不同的对象，返回YMUDObject指针
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmud.h"

YMUDObject* loadObject(YString datafilename)
{
  if(YString(datafilename,0,5)=="thing") {   //物品，试图从loadroom中复制
    YString thingname;
    if(g_LoadRoom) {
      YThing* thing=(YThing*)g_LoadRoom->findChild("datafilename",datafilename,"YThing");
      if(thing!=NULL) {
        YThing* thing2=(YThing*)thing->clone();
        if(!thing2) return thing2;
      }
    }
  }

  if((datafilename[0]=='\\')||(datafilename[0]=='/')) datafilename.erase(0,1);
  YString fullfilename=g_Settings->getRootPath()
                       +g_Settings->getPathSeparator()
                       +PATH(datafilename)
                       +".profile";
  YString classname="";

  FILE *datafile=fopen(fullfilename.c_str(),"rt");
  if(datafile) {
    char s[1024];
    if(fgets(s,1024,datafile)!=NULL) {
      char *val=strchr(s,'=');
      if(!val) {
        fclose(datafile);
        return NULL;
      }
      *val='\0';
      val++;
      trim(s);
      trim(val);
      if(strcmp(s,"#class")==0) classname=val;
    }
    fclose(datafile);
  }

  return loadObject(classname, datafilename);
}
//----------------------------------------------------------------
YMUDObject* loadObject(YString classname, YString datafilename)
{
  YMUDObject* obj;

  if(classname=="YNPC") obj=new YNPC(datafilename);
  else if(classname=="YTeacherNPC") obj=new YTeacherNPC(datafilename);
  else if(classname=="YBetrayNPC") obj=new YBetrayNPC(datafilename);
  else if(classname=="YOfferRewardNPC") obj=new YOfferRewardNPC(datafilename);
  else if(classname=="YMarryNPC") obj=new YMarryNPC(datafilename);  //媒婆等结婚NPC
  else if(classname=="YMoneyNPC") obj=new YMoneyNPC(datafilename);  //收钱的NPC
  else if(classname=="YSpecialNPC") obj=new YSpecialNPC(datafilename);  //特殊NPC
  else if(classname=="YRoom") obj=new YRoom(datafilename);
  else if(classname=="YCookRoom") obj=new YCookRoom(datafilename); //厨房
  else if(classname=="YRetiringRoom") obj=new YRetiringRoom(datafilename); //休息室
  else if(classname=="YPawnRoom") obj=new YPawnRoom(datafilename); //当铺
  else if(classname=="YBankRoom") obj=new YBankRoom(datafilename); //银行
  else if(classname=="YNewPlayerRoom") obj=new YNewPlayerRoom(datafilename); //新人登录房间
  else if(classname=="YWorkRoom") obj=new YWorkRoom(datafilename); //新人登录房间
  else if(classname=="YCollectRoom") obj=new YCollectRoom(datafilename);
  else if(classname=="YJollityRoom") obj=new YJollityRoom(datafilename); //宴会房间
  else if(classname=="YYelianRoom") obj=new YYelianRoom(datafilename);
  else if(classname=="Ycangkuroom") obj=new Ycangkuroom(datafilename);   //仓库
  else if(classname=="YLianDanRoom") obj=new YLianDanRoom(datafilename);
  else if(classname=="YLingWuRoom") obj=new YLingWuRoom(datafilename); //宴会房间
  else if(classname=="YMarryRoom") obj=new YMarryRoom(datafilename);    //结婚房间
  else if(classname=="YJailRoom") obj=new YJailRoom(datafilename);    //酒宴房间
  else if(classname=="YDoorRoom") obj=new YDoorRoom(datafilename);
  else if(classname=="YHideDoorRoom") obj=new YHideDoorRoom(datafilename);
  else if(classname=="YLoadRoom") obj=new YLoadRoom(datafilename);
  else if(classname=="YThing") obj=new YThing(datafilename);
  else if(classname=="YDestroyThing") obj=new YDestroyThing(datafilename);
  else if(classname=="YQuest") obj=new YQuest(datafilename);
  else {
    g_applog->write("[loadObject]无法识别的类名："+classname+",filename="+datafilename);
    obj=NULL;
  }
  //刘鹏添加的各种物品人物在掉入后从新load
  if ((obj != NULL)&& (classname!="YQuest"))obj->onAfterLoad();

  return obj;
}
