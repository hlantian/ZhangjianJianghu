//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------
#include <iostream.h>

#include "ymudobject.h"

#pragma argsused

int main(int argc, char* argv[])
{
  YMUDObject o1,o2,o11,o12;
  o1.setSmallTime(5000);
  o1.getChildren()->add(&o11);
  o1.getChildren()->add(&o12);
  o1.getChildren()->remove(&o11);
  o1.set("名字","张三");
  cout<<o1.getAsString("名字")<<endl;
  cin.get();
  return 0;
}
//---------------------------------------------------------------------------

