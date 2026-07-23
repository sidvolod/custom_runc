cmake_minimum_required(VERSION 4.2)
project(CDocker C)

set(CMAKE_C_STANDARD 11)

add_executable(CDocker src/main.c
        include/container.h
        src/container.c)
        
target_compile_definitions(CDocker PRIVATE ROOTFS_PATH=\"${CMAKE_SOURCE_DIR}/rootfs\")
