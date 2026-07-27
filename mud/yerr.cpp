#include "yerr.h"
#include "ystring.h"
#include "ylogfile.h"

YErr g_err;
//---------------------------------------------------------------------------
void YErr::show(YString errmsg)
{
  //if(g_ErrorChat) g_ErrorChat->talk(NULL,errmsg);
  //cerr<<errmsg<<endl;
  g_applog->write(errmsg);
}

