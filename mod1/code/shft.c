#include <stdio.h>

// 1. C compiler automatically generates shift/add code when multiplying by constant
long mul42(long x)
{
  return x*42;
}

// 2. Compiled unsigned division code uses logical shift
unsigned long udiv32(unsigned long x)
{
  return x/32;
}

// 3. Signed power-of-2 divide with shift
// x≫k gives ⌊x/2ᵏ⌋ using arithmetic shift
// Rounds in wrong direction when x<0 
// since we want to round towards 0

long divbyshft(long x, int k)
{
  return (x >> k);
}

// fix with biasing on negative numbers based on ⌈x/y⌉=⌊(x+y-1)/y⌋
// ⌊(x+2ᵏ-1)/2ᵏ⌋
long divbyshftfix(long x, int k)
{
  if(x<0)
    return ((x + (1<<k)-1) >> k);
  else
    return (x >> k);
}

long divk(long x, int k)
{
  return x/k;
}

int main(){
  long x = -25341;
  long  d=1;
  for (int k = 0; k < 20; k++, d*=2)
  {
    // printf("div: %8ld/%6ld=%8ld | ", x, d, x/d);
    printf("div: %8ld/%6ld=%8ld | ", x, d, divk(x, d));
    printf("sht: %8ld/%6ld=%8ld | ", x, d, divbyshft(x, k));
    printf("fix: %8ld/%6ld=%8ld \n", x, d, divbyshftfix(x, k));
  }
  
  return 0;
}