//
// Created by Volodymyr on 15/06/2026.
//

#ifndef CDOCKER_CONTAINER_H
#define CDOCKER_CONTAINER_H
int run_container(void *args);

typedef struct {
    char* path;
    char** args;
    char* contID;
} ContInit;
#endif //CDOCKER_CONTAINER_H

