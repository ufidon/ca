#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("Bye\n");
    return 0;
}