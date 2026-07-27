//---------------------------------------------------------------------------

#ifndef __FIGHT_H__
#define __FIGHT_H__

class Fight : public YMUDObject{

  public:
		Fight(YString filename):YMUDObject(filename){};  //构造函数
		virtual ~Fight(){}; //析构函数
    enum Fight_displayer_t{SELF, TARGET, OTHER};
    //将FIGHT翻译成描述 (whom是显示对象)
    YString translate(const YString& fight, YAbstractActor* actor1, YAbstractActor* actor2,
                      Fight_displayer_t whom);
    //执行命令，已处理返回1，未处理返回0
    virtual int executeCommandAsTarget(YAbstractActor* executor, YString command){return 1;};
};

#endif //__FIGHT_H__
 