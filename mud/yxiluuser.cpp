//---------------------------------------------------------------------------
//
// yxiluuser.cpp    2000年6月12日
//
// 类YXiluUser：西陆用户
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------------------
//YXiluUser构造函数
YXiluUser::YXiluUser()
{
  setSex(SEX_UNKNOWN);
}
//---------------------------------------------------------------------------
//YXiluUser析构函数
YXiluUser::~YXiluUser()
{
}
//---------------------------------------------------------------------------
void YXiluUser::setSex(YString sex)
{
	if((sex=="m")||(sex=="M")||(sex=="male")||(sex=="MALE")||(sex=="Male")||(sex=="男")) 
		setSex(MALE);
	else if((sex=="f")||(sex=="F")||(sex=="female")||(sex=="FEMALE")||(sex=="Female")||(sex=="女"))
		setSex(FEMALE);
	else setSex(SEX_UNKNOWN);
}

