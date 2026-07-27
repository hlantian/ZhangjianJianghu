#ifndef __YLOGFILE_H__
#define __YLOGFILE_H__

#include "ystring.h"

class YLogFile {
  private:
    YString m_name;
  public:
    YLogFile(YString name);
    int write(YString info);
};
extern YLogFile *g_applog; 

#endif //__YLOGFILE_H__
