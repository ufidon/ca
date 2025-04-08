#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void cleanup(void) {
    printf("Cleaning up\n");
}

int main() {
    atexit(cleanup);
    fork();
    exit(0);
}