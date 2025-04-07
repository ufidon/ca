#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int x = 0;
  printf("Parent: Starting (PID %d)\n", getpid());
  pid_t pid = fork();

  if (pid == 0)
  { // Child process
    x = 1;
    printf("Child: x = %d (PID %d)\n", x, getpid());
  }
  else if (pid > 0)
  { // Parent process
    x = 2;
    wait(NULL); // Wait for child to finish
    printf("Parent: x = %d (PID %d)\n", x, getpid());
  }
  return 0;
}