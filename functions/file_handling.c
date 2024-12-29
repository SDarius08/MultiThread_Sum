//
// Created by pafnu on 12/24/2024.
//
#include <fcntl.h>
#include "../headers/file_handling.h"
#include "../headers/error_handling.h"

void file_access(const char* file_name)
{
    int rez;

    rez = access(file_name, F_OK | R_OK);

    if(rez == -1)
        file_error_handling();
}

int open_file(const char* file_name)
{
    int fd = -1;

    file_access(file_name);

    fd = open(file_name, O_RDONLY);
    if(fd == -1)
        file_error_handling();

    return fd;
}

void close_file(int *fd)
{
    int rez;
    if(*fd == 0 || *fd == -1)
        file_error_handling();

    rez = close(*fd);

    if(rez == -1)
        file_error_handling();

    *fd = 0;
}

void read_file(int fd)
{
    char buffer[_MAX_BUFFER];
    ssize_t bytes_read;
    if(fd == -1)
        file_error_handling();

    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1)
        file_error_handling();

    // Process buffer as needed
}