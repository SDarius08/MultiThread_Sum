#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/file_handling.h"
#include "../headers/error_handling.h"

void file_access(const char* file_name) {
    if (access(file_name, F_OK | R_OK) == -1) {
        perror("File access error");
        file_error_handling("Failed to access file");
    }
}

FILE* open_file_v2(const char* file_name)
{
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
        return NULL;
    }
}

int open_file(const char* file_name) {
    file_access(file_name);

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        file_error_handling("Failed to open file");
    }

    return fd;
}

void close_file(int *fd) {
    if (*fd < 0) {
        perror("Invalid file descriptor");
        file_error_handling("File descriptor is invalid");
    }

    if (close(*fd) == -1) {
        perror("Error closing file");
        file_error_handling("Failed to close file");
    }

    *fd = -1; // Mark as closed
}
