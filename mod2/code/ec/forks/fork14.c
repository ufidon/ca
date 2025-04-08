#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int ccount = 0;

void child_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    if ((pid = wait(NULL)) < 0) {
        perror("wait error");
        return;
    }
    ccount--;
    printf("Handler reaped child %ld\n", (long)pid);
    sleep(1);
    errno = olderrno;
}

int main() {
    pid_t pid[5];
    int i;
    ccount = 5;

    signal(SIGCHLD, child_handler);

    for (i = 0; i < 5; i++) {
        if ((pid[i] = fork()) == 0) {
            sleep(1);
            exit(0);
        }
    }
    while (ccount > 0);
    return 0;
}