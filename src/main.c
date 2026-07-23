#define _GNU_SOURCE
#define BASE_MEMORY_ALLOCATION 1024 * 64
#define NAME_SIZE 64

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/container.h"
#include <signal.h>
#include <time.h>
#include <libgen.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Error: Not enough arguments\n");
        return 1;
    }
    srand(time(NULL));
    
    ContInit* container = malloc(sizeof(ContInit));
    container->path = ROOTFS_PATH; 
    container->args = argv + 1;
    container->contID = malloc(NAME_SIZE);
    
    char* temp_cmd = strdup(argv[1]); 
    char* name = basename(temp_cmd);
    
    snprintf(container->contID, NAME_SIZE, "%s-%06X", name, rand() % 0x1000000);
    
    free(temp_cmd);
    
    char* memoryStart = malloc(BASE_MEMORY_ALLOCATION);
    if (memoryStart == NULL) {
        printf("Error: Memory allocation failed\n");
        return 2;
    }
    char* memoryEnd = memoryStart + BASE_MEMORY_ALLOCATION;

    pid_t process_id = clone(run_container, memoryEnd, CLONE_NEWPID | SIGCHLD | CLONE_NEWNS, container);

    waitpid(process_id, NULL, 0);
    
    free(memoryStart);
    free(container->contID);
    free(container);
    return 0;
}
