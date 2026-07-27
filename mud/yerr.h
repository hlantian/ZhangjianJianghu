#ifndef __YERR_H__
#define __YERR_H__

#include "ystring.h"

class YErr {
  private:

  protected:

  public:
    YErr(){};
    ~YErr(){};
    static void show(YString errmsg);
    YString ErrDescription;
};
extern YErr g_err;
#endif //__YERR_H__
