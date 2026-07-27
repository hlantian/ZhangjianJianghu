//---------------------------------------------------------------------------
//
// ystringlist.h    2001年2月2日
//
// 类YStringList：字符串列表，提供查找，存储等功能
//
// 作者：叶林   单位：北京西陆信息技术有限公司
//
//---------------------------------------------------------------------------

#ifndef __YSTRINGLIST_H__
#define __YSTRINGLIST_H__

#include <map>
#include "ystring.h"

class YStringList {
  private:
    map<YString, char, less<YString> > m_stringgroup;
    int m_maxlen; //字符串最大长度
	//属性：FileName(存储文件名)
	private:
		YString m_FileName; //属性FileName(存储文件名)的成员变量
	public:
		YString getFileName(void) {return m_FileName;} //读属性FileName(存储文件名)
		void setFileName(YString newFileName) {m_FileName=newFileName;} //设置FileName(存储文件名)

  protected:

  public:
		YStringList(YString initFileName="",int maxlen=1024);  //构造函数
		~YStringList(){}; //析构函数
    bool load();  //从文件中读
    bool save();  //写入文件
    bool isIn(YString s); //列表中是否有某个字符串
};

#endif //__YSTRINGLIST_H__
