#include <stdio.h>
#include <stdint.h>

int main()
{
  int a = 10;
  int b = 20;
  int result;

  // Demonstrate CMP instruction (comparison)
  // `CMP S1, S2`
  // - signed comparision bases on signed subtraction `S2 -ᵗ S1`
  //  - the result is indicated by the combinations of SF - OF and ZF

  if (a < b)
  {
    printf("a is less than b\n");
  }
  else
  {
    printf("a is not less than b\n");
  }


  // - unsigned comparision bases on unsigned subtraction `S2 -ᵘ S1`
  //  - the result is indicated by the combinations of CF and ZF
  
  uint64_t s1=30, s2=10;
  if (s1 < s2)
  {
    printf("s1 is less than s2\n");
  }
  else
  {
    printf("s1 is not less than s2\n");
  }  
 
  // Demonstrate TEST instruction (bitwise AND)
  if (a & 0x01)
  {
    printf("a is odd\n");
  }
  else
  {
    printf("a is even\n");
  }

  // Another example of TEST instruction
  result = a & b;
  if (result)
  {
    printf("a and b share common bits\n");
  }
  else
  {
    printf("a and b do not share common bits\n");
  }

  return 0;
}
