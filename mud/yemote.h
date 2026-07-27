//---------------------------------------------------------------------------
//
// yemote.h    2000年8月10日
//
// 类YEmote：聊天表情
//
// 作者：叶林,刘鹏   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YEMOTE_H__
#define __YEMOTE_H__

class YEmote : public YMUDObject{

  public:
		YEmote(YString filename):YMUDObject(filename){disableTimer();};  //构造函数
		virtual ~YEmote(){}; //析构函数
    enum emote_displayer_t{SELF, TARGET, OTHER};
    //将emote翻译成描述 (whom是显示对象)
    YString translate(const YString& emote, YAbstractActor* actor1, YAbstractActor* actor2,
                      emote_displayer_t whom);
    //将emote翻译成描述对于没有表示人名的描述 (whom是显示对象)
    YString Strtranslate(const YString& emote, YString Player1Name,YAbstractActor* actor2,
                      emote_displayer_t whom);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};
};

#endif //__YEMOTE_H__
