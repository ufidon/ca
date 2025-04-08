#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    if (fork() == 0) {
        printf("Running Child, PID = %d\n", getpid());
        while (1);
    } else {
        printf("Terminating Parent, PID = %d\n", getpid());
        exit(0);
    }
    return 0;
}