#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    if (fork() == 0) {
        printf("Child: pid=%d pgrp=%d\n", getpid(), getpgrp());
    } else {
        printf("Parent: pid=%d pgrp=%d\n", getpid(), getpgrp());
    }
    while (1);
    return 0;
}