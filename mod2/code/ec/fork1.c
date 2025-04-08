#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // for fork()
#include <sys/types.h> // for pid_t

int main() {
    pid_t pid;
    int x = 1;

    pid = fork();
    
    if (pid == 0) {  // Child process
        printf("child : x=%d\n", ++x);
        exit(0);
    }
    
    // Parent process
    printf("parent: x=%d\n", --x);
    exit(0);
}