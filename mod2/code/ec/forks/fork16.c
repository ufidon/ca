#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    if (fork() == 0) {
        printf("Child1: pid=%d pgrp=%d\n", getpid(), getpgrp());
        if (fork() == 0) {
            printf("Child2: pid=%d pgrp=%d\n", getpid(), getpgrp());
        }
        while (1);
    }
    return 0;
}