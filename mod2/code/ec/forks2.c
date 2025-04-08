/*
 * forks2.c - Examples of Unix process control
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

/*
✅ **Basic Forking and Output Interleaving**
- **`fork0`**: Simple fork with separate messages from child and parent.
- **`fork1`**: Shows how variables are copied during fork (memory separation).
- **`fork2`, `fork3`**: Demonstrate exponential growth of processes.
- **`fork4`, `fork5`**: Conditional forks, affecting the process tree shape.

*/

void fork0() {
    if (fork() == 0) {
        printf("Hello from child\n");
    } else {
        printf("Hello from parent\n");
    }
}

void fork1() {
    int x = 1;
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child has x = %d\n", ++x);
    } else {
        printf("Parent has x = %d\n", --x);
    }
    printf("Bye from process %d with x = %d\n", getpid(), x);
}

void fork2() {
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("Bye\n");
}

void fork3() {
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("L2\n");
    fork();
    printf("Bye\n");
}

void fork4() {
    printf("L0\n");
    if (fork() != 0) {
        printf("L1\n");
        if (fork() != 0) {
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

void fork5() {
    printf("L0\n");
    if (fork() == 0) {
        printf("L1\n");
        if (fork() == 0) {
            printf("L2\n");
        }
    }
    printf("Bye\n");
}

/*
✅ **Cleanup and Exit Behavior**
- **`fork6`**: Demonstrates `atexit()` and exit handlers — only the calling process cleans up.
- **`fork7`, `fork8`**: Parent or child exits while the other loops — terminal state exploration.
*/

void cleanup(void) {
    printf("Cleaning up\n");
}

void fork6() {
    atexit(cleanup);
    fork();
    exit(0);
}

void fork7() {
    if (fork() == 0) {
        printf("Terminating Child, PID = %d\n", getpid());
        exit(0);
    } else {
        printf("Running Parent, PID = %d\n", getpid());
        while (1);
    }
}

void fork8() {
    if (fork() == 0) {
        printf("Running Child, PID = %d\n", getpid());
        while (1);
    } else {
        printf("Terminating Parent, PID = %d\n", getpid());
        exit(0);
    }
}

/*
✅ **Waiting and Status Checking**
- **`fork9`**: Basic `wait()` usage and process synchronization.
- **`fork10`**: Forks multiple children and waits in arbitrary order.
- **`fork11`**: Waits for children in reverse creation order using `waitpid()`.
*/

void fork9() {
    int child_status;
    if (fork() == 0) {
        printf("HC: hello from child\n");
        exit(0);
    } else {
        printf("HP: hello from parent\n");
        wait(&child_status);
        printf("CT: child has terminated\n");
    }
    printf("Bye\n");
}

#define N 5

void fork10() {
    pid_t pid[N];
    int i, child_status;

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            exit(100 + i);
        }
    }
    for (i = 0; i < N; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
}

void fork11() {
    pid_t pid[N];
    int i, child_status;

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            exit(100 + i);
        }
    }
    for (i = N - 1; i >= 0; i--) {
        pid_t wpid = waitpid(pid[i], &child_status, 0);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
}

/*
✅ **Signal Handling and Termination**
- **`fork12`**: Kills child processes via `SIGINT`.
- **`fork13`**: Adds a `SIGINT` handler so children can react before exiting.
- **`fork14`**: Uses a `SIGCHLD` handler to reap terminated children one-by-one.
- **`fork15`**: Improves `SIGCHLD` handler to reap all terminated children at once.
*/

void fork12() {
    pid_t pid[N];
    int i, child_status;

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            while (1);
        }
    }
    for (i = 0; i < N; i++) {
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }
    for (i = 0; i < N; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
}

void int_handler(int sig) {
    printf("Process %d received signal %d\n", getpid(), sig);
    exit(0);
}

void fork13() {
    pid_t pid[N];
    int i, child_status;

    signal(SIGINT, int_handler);
    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            while (1);
        }
    }
    for (i = 0; i < N; i++) {
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }
    for (i = 0; i < N; i++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status)) {
            printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
        } else {
            printf("Child %d terminated abnormally\n", wpid);
        }
    }
}

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

void fork14() {
    pid_t pid[N];
    int i;
    ccount = N;

    signal(SIGCHLD, child_handler);

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            sleep(1);
            exit(0);
        }
    }
    while (ccount > 0);
}

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

void fork15() {
    pid_t pid[N];
    int i;
    ccount = N;

    signal(SIGCHLD, child_handler2);

    for (i = 0; i < N; i++) {
        if ((pid[i] = fork()) == 0) {
            sleep(1);
            exit(0);
        }
    }
    while (ccount > 0);
}

/*
✅ **Process Grouping and Hierarchy**
- **`fork16`**: Demonstrates child-child relationship and `getpgrp()`.
- **`fork17`**: Observes parent-child process group behavior.
*/

void fork16() {
    if (fork() == 0) {
        printf("Child1: pid=%d pgrp=%d\n", getpid(), getpgrp());
        if (fork() == 0) {
            printf("Child2: pid=%d pgrp=%d\n", getpid(), getpgrp());
        }
        while (1);
    }
}

void fork17() {
    if (fork() == 0) {
        printf("Child: pid=%d pgrp=%d\n", getpid(), getpgrp());
    } else {
        printf("Parent: pid=%d pgrp=%d\n", getpid(), getpgrp());
    }
    while (1);
}

int main(int argc, char *argv[]) {
    int option = 0;
    if (argc > 1) {
        option = atoi(argv[1]);
    }

    switch (option) {
        case 0: fork0(); break;
        case 1: fork1(); break;
        case 2: fork2(); break;
        case 3: fork3(); break;
        case 4: fork4(); break;
        case 5: fork5(); break;
        case 6: fork6(); break;
        case 7: fork7(); break;
        case 8: fork8(); break;
        case 9: fork9(); break;
        case 10: fork10(); break;
        case 11: fork11(); break;
        case 12: fork12(); break;
        case 13: fork13(); break;
        case 14: fork14(); break;
        case 15: fork15(); break;
        case 16: fork16(); break;
        case 17: fork17(); break;
        default:
            printf("Unknown option %d\n", option);
            break;
    }
    return 0;
}