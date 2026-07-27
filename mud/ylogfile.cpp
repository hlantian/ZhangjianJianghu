#include "ylogfile.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

YLogFile *g_applog;
//-----------------------------------------------------------------
YLogFile::YLogFile(YString name)
:m_name(name)
{
   int handle=open(name.c_str(),O_RDONLY,S_IREAD);
   if(handle==-1) {
    if(errno==ENOENT) {
      creat(name.c_str(),O_CREAT|O_EXCL|S_IRUSR|S_IWUSR);
    }
   }
   else close(handle);
}
//-----------------------------------------------------------------
int YLogFile::write(YString info)
{
  FILE *fp;
  fp=fopen(m_name.c_str(),"a+");
  time_t t=time(0);
  info="------------------------------------------------------------------------\n"
        +(YString)ctime(&t)
        +info+"\n";
  if(!fp) return -1;
  //fseek(fp,0,SEEK_END);
  fwrite(info.c_str(),1,info.size(),fp);
  fclose(fp);
  return 0;
}


