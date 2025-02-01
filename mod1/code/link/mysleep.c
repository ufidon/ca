#include <unistd.h>

#ifdef COMPILETIME
unsigned int mysleep(unsigned int seconds);
#define sleep mysleep
#endif

int main()
{
  sleep(1);
  return 0;
}