#define _GNU_SOURCE
#define BASE_MEMORY_ALLOCATION 1024 * 64
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/container.h"
#include "signal.h"

int main(int argc, char **argv) {
    
    if (argc < 2) {
        printf("Error: Not enough arguments\n");
        return 1;
    }

    char* memoryStart = malloc(BASE_MEMORY_ALLOCATION);
    if (memoryStart == NULL) {
        printf("Error: Memory allocation failed\n");
        return 2;
    }
    char* memoryEnd = memoryStart + BASE_MEMORY_ALLOCATION;

    pid_t process_id = clone(run_container, memoryEnd, CLONE_NEWPID | SIGCHLD, argv+1);

    waitpid(process_id, NULL, 0);
    free(memoryStart);
    return 0;
}