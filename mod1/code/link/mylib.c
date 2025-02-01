#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Preprocessing directive to control the interpositioning method */
#ifdef RUNTIME

#include <dlfcn.h>

/* Run-time interpositioning of sleep using LD_PRELOAD mechanism */
unsigned int sleep(unsigned int seconds)
{
    unsigned int (*sleepp)(unsigned int seconds);
    char *error;

    sleepp = dlsym(RTLD_NEXT, "sleep"); /* Get address of libc sleep */
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    printf("runtime sleep(%u)\n", seconds);  // Trace the sleep function call
    return sleepp(seconds);  /* Call libc sleep */
}

#endif  /* RUNTIME */

/* $begin interposer */
#ifdef LINKTIME
#include <stdio.h>

unsigned int __real_sleep(unsigned int seconds);

/* Link-time interpositioning of sleep using the static linker "--wrap" flag */
unsigned int __wrap_sleep(unsigned int seconds)
{
    printf("linktime sleep(%u)\n", seconds);  // Trace the sleep function call
    return __real_sleep(seconds);    /* Call libc sleep */
}
#endif  /* LINKTIME */

/* $begin interposer */
#ifdef COMPILETIME
#include <stdio.h>
#include <unistd.h>

/* Compile-time interpositioning of sleep using preprocessor */
unsigned int mysleep(unsigned int seconds)
{
    printf("compiletime sleep(%u)\n", seconds);  // Trace the sleep function call
    return sleep(seconds);  // Call the actual sleep function
}
#endif  /* COMPILETIME */

