#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <time.h>

/*
1. **Multi-level Error Handling**:
   - Warnings (continue with notification)
   - Recoverable errors (retry operation)
   - Fatal errors (system shutdown)

2. **Nested Recovery Points**:
   ```
   main (fatal_env)
     → operation_A (warning_env)
       → operation_B (recoverable_env)
         → operation_C (error generator)
   ```

3. **Realistic Simulation**:
   - Random error generation (0-3)
   - Different behaviors for different error levels
   - Multiple test runs

### How It Works:

1. **Establish Checkpoints**:
   - Each `setjmp()` establishes a return point
   - Different buffers for different recovery levels

2. **Error Propagation**:
   - Errors bubble up through the call stack
   - Each level handles what it can

3. **Clean Shutdown**:
   - Fatal errors exit the program
   - Other errors continue execution

This pattern is useful for:
- Embedded systems
- Protocol implementations
- Resource-constrained environments where exceptions aren't available

**Important Note**: While powerful, `setjmp`/`longjmp` bypass normal stack unwinding. Don't use them as a general exception mechanism in C++ (where destructors wouldn't be called).   
*/

// Error severity levels
typedef enum
{
  NO_ERROR,
  WARNING,
  RECOVERABLE_ERROR,
  FATAL_ERROR
} ErrorLevel;

// Jump buffers for different recovery points
jmp_buf warning_env;
jmp_buf recoverable_env;
jmp_buf fatal_env;

void handle_error(ErrorLevel level)
{
  switch (level)
  {
  case WARNING:
    printf("⚠️ Handling warning (level %d)\n", level);
    longjmp(warning_env, level);
    break;

  case RECOVERABLE_ERROR:
    printf("🛠 Handling recoverable error (level %d)\n", level);
    longjmp(recoverable_env, level);
    break;

  case FATAL_ERROR:
    printf("💀 Handling fatal error (level %d)\n", level);
    longjmp(fatal_env, level);
    break;

  default:
    fprintf(stderr, "Unknown error level!\n");
    exit(EXIT_FAILURE);
  }
}

void operation_C()
{
  printf("Performing operation C\n");

  // Simulate random error (0-3)
  ErrorLevel error = rand() % 4;
  if (error != NO_ERROR)
  {
    handle_error(error);
  }
  printf("Operation C completed successfully\n");
}

void operation_B()
{
  printf("Performing operation B\n");

  if (setjmp(recoverable_env) == NO_ERROR)
  {
    operation_C();
  }
  else
  {
    printf("↩️ Recovered in operation B\n");
  }

  printf("Operation B completed\n");
}

void operation_A()
{
  printf("Performing operation A\n");

  if (setjmp(warning_env) == NO_ERROR)
  {
    operation_B();
  }
  else
  {
    printf("⚠️ Warning handled in operation A\n");
  }

  printf("Operation A completed\n");
}

int main()
{
  srand(time(NULL));

  printf("=== System Startup ===\n");

  if (setjmp(fatal_env))
  {
    printf("🆘 Critical failure! Shutting down...\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < 5; i++)
  {
    printf("\n=== Run %d ===\n", i + 1);
    operation_A();
  }

  printf("\n=== System Shutdown (Normal) ===\n");
  return EXIT_SUCCESS;
}