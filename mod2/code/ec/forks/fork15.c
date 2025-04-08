#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int ccount = 0;

void child_handler2(int sig) {
    int olderrno = errno;
    pid_t pid;
    while ((pid = wait(NULL)) > 0) {
        ccount--;
        printf("Handler reaped child %ld\n", (long)pid);
    }
    if (errno != ECHILD) {
        perror("wait error");
    }
    errno = olderrno;
}

int main() {
    pid_t pid[5];
    int i;
    ccount = 5;

    signal(SIGCHLD, child_handler2);

    for (i = 0; i < 5; i++) {
        if ((pid[i] = fork()) == 0) {
            sleep(1);
            exit(0);
        }
    }
    while (ccount > 0);
    return 0;
}