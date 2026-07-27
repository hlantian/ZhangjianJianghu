#include "ystring.h"
#include "yfifo.h"

int main(void)
{
  YFIFO fifo("/etc/test.fifo","w");
  fifo.write("ÄãºÃ!");
  return 0;
}
