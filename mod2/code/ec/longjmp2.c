#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

/*
1. **Initial Call**:
   - `setjmp()` returns 0 when called directly
   - Saves execution context in `env`

2. **First Jump**:
   - `function_a()` calls `longjmp(env, 1)`
   - Program returns to `setjmp()`, which now returns 1

3. **Second Jump**:
   - `function_b()` calls `longjmp(env, 2)`
   - Returns to `setjmp()` again, now returning 2

4. **Control Flow**:
   ```
   main() → setjmp() (returns 0) → function_a()
     → longjmp() → setjmp() (returns 1) → function_b()
     → longjmp() → setjmp() (returns 2) → exits
   ```

### Important Notes:
1. `volatile` prevents compiler optimizations that might interfere with jumps
2. Local variables changed between `setjmp`/`longjmp` may have undefined values
3. Not suitable for C++ (use exceptions instead)
4. Primarily used for error recovery or custom control flow
*/

jmp_buf env; // Jump buffer for setjmp/longjmp

void function_b()
{
  printf("In function_b()\n");
  longjmp(env, 2); // Second return from setjmp (returns 2)
}

void function_a()
{
  printf("In function_a()\n");
  longjmp(env, 1); // First return from setjmp (returns 1)
}

int main()
{
  volatile int count = 0; // volatile prevents optimization issues

  // First call to setjmp returns 0
  // Subsequent returns come from longjmp calls
  switch (setjmp(env))
  {
  case 0:
    printf("Initial setjmp() call (direct)\n");
    function_a();
    break;

  case 1:
    printf("First longjmp() return\n");
    count++;
    function_b();
    break;

  case 2:
    printf("Second longjmp() return\n");
    count++;
    break;

  default:
    printf("Unexpected return value!\n");
    exit(1);
  }

  printf("Final count: %d\n", count);
  return 0;
}