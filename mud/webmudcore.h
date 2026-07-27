#ifndef __WEDMUDCORE_H__
#define __WEDMUDCORE_H__

#include "ytimer.h"
//#include "config.h"
#include <cc++/common.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h> 
#include <string.h>
#include <fcntl.h>
#ifdef __WIN32__
  #include <windows.h>
  #include <io.h>
#else //UNIX
  #ifndef __USE_XOPEN
  	#define __USE_XOPEN
  #endif
  #include <sys/resource.h>
  #include <unistd.h>
  //#include <mysql.h>
  //#include <semaphore.h>
  #ifndef SEM_FAILED
    #define SEM_FAILED ((sem_t*)-1)
  #endif
#endif //__WIN32__


#include "ymudobject.h"
#include "yabstractactor.h"
#include "yabstractroom.h"
#include "yabstractthing.h"
#include "yabstractsamething.h"

#include "loadobject.h"

#include "yobjectgroup.h"
#include "ypropertygroup.h"

#include "ywebmud.h"
#include "ymudsettings.h"
#include "yxiluuser.h"
#include "yxiluusermanager.h"
#include "yuser.h"
#include "yusermanager.h"
#include "ysession.h"
#include "ysessionmanager.h"
#include "ymap.h"
#include "ycommand.h"
#include "ychat.h"
#include "ychatmanager.h"
#include "yemote.h"
#ifndef __WIN32__
  #include "ycomm.h"
#endif

#include "global.h"

#include "ycommand.h"
#include "yfifo.h"
#ifndef __WIN32__
  #include "yfifo_unix.h"
#endif
#include "debug.h"
#include "yerr.h"
#include "ydatetime.h"
#include "ystring.h"
#include "ystringlist.h"
#include "ylogfile.h"

#include "yalloc.h"

#endif //__WEDMUDCORE_H__
