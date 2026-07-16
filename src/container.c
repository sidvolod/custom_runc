#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int run_container(void *args) {
    char **parsed_args = (char **)args;
    execvp(parsed_args[0], parsed_args);
    perror("execvp failed to find the program");

    return -1;
}