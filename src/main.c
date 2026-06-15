#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// This is the isolated "container" space
int child_process(void *arg) {
    // 1. Cast the argument back to a string array (your command, like "/bin/bash")
    // 2. Print a message saying "Container started!"
    // 3. Swap out this running C program for the requested command using execvp()

    return 0;
}
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
// This is the "host" space (your mini-daemon)
int main(int argc, char **argv) {
    // 1. Check if the user passed a command (e.g., argc > 1)
    if (argc >1) {
        int i = 9;
    }
    // 2. Allocate memory for the new process's stack (e.g., 65536 bytes using malloc)
    // Note: Stacks grow downwards in memory on most architectures,
    // so you need to point to the END of the allocated memory block.
    char* memoryStart = malloc(65536) + 65536;


    // 3. Call clone(), passing it:
    //    - The child_process function
    //    - The top of the stack you just created
    //    - The flags: CLONE_NEWPID | SIGCHLD
    //    - The arguments (argv + 1)

    // 4. Use waitpid() to pause the host program until the container exits

    return 0;
}