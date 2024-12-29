//
// Created by pafnu on 12/24/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "../headers/error_handling.h"
#include <unistd.h>

void file_error_handling()
{
    fprintf(stderr, "Error number: %d : %s\n", errno, strerror(errno));
    exit(EXIT_FAILURE);
}

