#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();
  if (pid == 0)
  { // Child
    printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
    char *args[] = {"ls", NULL};
    execve("/bin/ls", args, NULL);
  }
  else if (pid > 0)
  { // Parent
    printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
    wait(NULL);
  }
  else
  {
    perror("fork failed");
  }
  return 0;
}