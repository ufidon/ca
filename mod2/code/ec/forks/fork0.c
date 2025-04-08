#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    if (fork() == 0) {
        printf("Hello from child\n");
    } else {
        printf("Hello from parent\n");
    }
    return 0;
}