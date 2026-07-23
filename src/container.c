#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mount.h>
#include <sys/syscall.h>
#include "../include/container.h"

int run_container(void *args) {
    ContInit *parsed_args = (ContInit *)args;
    
    int mount_res = mount(NULL, "/", NULL, MS_PRIVATE | MS_REC, NULL);
    int mount2_res = mount(parsed_args->path, parsed_args->path, NULL, MS_BIND | MS_REC, NULL);
    
    if (mount_res == -1 || mount2_res == -1) {
        perror("mounts have failed");
        exit(1);
    }
    
    char* new_root = parsed_args->path;
    char put_old[256];
    snprintf(put_old, sizeof(put_old), "%s/old_root", new_root);
        
    int result = syscall(SYS_pivot_root, new_root, put_old);
    if (result == -1) {
        perror("pivot_root failed");
        exit(1);
    }
    
    chdir("/");
    
    if (umount2("/old_root", MNT_DETACH) == -1) {
        perror("umount2 failed");
        exit(1);
    }
    
    mount("proc", "/proc", "proc", 0, NULL);
    
    execvp(parsed_args->args[0], parsed_args->args);
    perror("execvp failed to find the program");
    
    return -1;
}
