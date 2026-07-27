#include "ystring.h"
#include "yfifo.h"

int main(void)
{
  YFIFO fifo("/etc/test.fifo","r");
  YString s=fifo.read();
  cout<<s<<endl;
  return 0;
}
