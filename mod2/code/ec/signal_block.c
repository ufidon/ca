#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*
### demonstrates signal blocking and unblocking using `sigprocmask()`
1. Blocks SIGINT (Ctrl+C) and SIGTERM signals
2. Shows they're blocked by trying to trigger them
3. Unblocks them after a delay
4. Shows they now work normally

### How to Use This Program:

1. Compile it:
   ```bash
   gcc signal_block.c -o signal_block
   ```

2. Run it:
   ```bash
   ./signal_block
   ```

3. During execution:
   - First 5 seconds: Try Ctrl+C (won't work)
   - After unblocking: Try Ctrl+C (will work)

4. From another terminal (while it's running):
   ```bash
   kill -TERM <pid>  # Replace <pid> with the shown PID
   ```
*/

void signal_handler(int sig)
{
  const char *signame = strsignal(sig);
  printf("\nCaught signal %d (%s)\n", sig, signame);
}

void print_blocked_signals()
{
  /*
  3. **Signal Inspection**:
     - `sigprocmask()` with NULL gets current blocked set
     - `sigismember()` checks if a signal is blocked
  */
  sigset_t current_set;
  sigprocmask(SIG_BLOCK, NULL, &current_set); // Get current mask

  printf("Currently blocked signals: ");
  for (int sig = 1; sig < NSIG; sig++)
  {
    if (sigismember(&current_set, sig))
    {
      printf("%d (%s), ", sig, strsignal(sig));
    }
  }
  printf("\n");
}

int main()
{
  /*
  2. **Signal Handling**:
    - `signal()` sets up handlers for graceful signal processing
  */
  // Set up signal handlers
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  printf("My PID: %d\n", getpid());

  /*
  4. **Signal Set Operations**:
    - `sigemptyset()` initializes an empty set
    - `sigaddset()` adds signals to the set
  */
  // Create a set of signals to block
  sigset_t block_set;
  sigemptyset(&block_set);
  sigaddset(&block_set, SIGINT);  // Ctrl+C
  sigaddset(&block_set, SIGTERM); // Termination signal

  /*
  1. **Signal Blocking**:
    - `sigprocmask(SIG_BLOCK, ...)` prevents signals from being delivered
    - Blocked signals are queued and delivered when unblocked
  */
  // Block the signals
  printf("\nBlocking SIGINT and SIGTERM...\n");
  sigprocmask(SIG_BLOCK, &block_set, NULL);
  print_blocked_signals();

  printf("Try sending SIGINT (Ctrl+C) or SIGTERM (kill %d) now - they're blocked!\n", getpid());
  printf("Waiting 5 seconds...\n");
  sleep(5);

  // Unblock the signals
  printf("\nUnblocking signals...\n");
  sigprocmask(SIG_UNBLOCK, &block_set, NULL);
  print_blocked_signals();

  printf("Now signals will work. Try sending SIGINT (Ctrl+C) or SIGTERM (kill %d)\n", getpid());
  printf("Waiting 5 seconds...\n");
  sleep(5);

  printf("\nDone!\n");
  return 0;
}