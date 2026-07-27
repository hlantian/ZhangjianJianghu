//---------------------------------------------------------------------------
//
// yemote.cpp    2000年8月10日
//
// 类YEmote：聊天表情
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//将FIGHT翻译成描述(whom是显示对象)
YString Fight::translate(const YString& fight, YAbstractActor* actor1,
                          YAbstractActor* actor2, Fight_displayer_t whom)
{
  if(!actor1) return "??";
  YString suffix;
  if(actor1==actor2) suffix="_self";
  else if(!actor2) suffix="_no";
  else suffix="_target";

  YString s=getAsString(fight+suffix);
  YString sSelf, sTarget;
  if(whom==SELF) {
    sSelf="你";
    sTarget=(actor2!=NULL)? actor2->getDisplayName() : YString("xx");
  }
  else if(whom==TARGET) {
    sSelf=actor1->getDisplayName();
    sTarget="你";
  }
  else {
    sSelf=actor1->getDisplayName();
    sTarget=(actor2!=NULL)? actor2->getDisplayName() : YString("xx");
  }

  YString retS="";
  for(int i=0; i<s.size(); i++) {
    if(s[i]=='&') {
      i++;
      if(s[i]=='s') retS+=sSelf;
      else if((s[i]=='t') && (actor2!=NULL)) retS+=sTarget;
    }
    else retS+=s[i];
  }
  return retS;
}

