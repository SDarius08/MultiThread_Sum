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

void free_int(int *n, uint size)
{
    if(n == 0)
        return;
    memset(n,0,size*sizeof(int));
    free(n);
    n = 0;
}

void free_thread_data(thread_data* data, uint number_threads)
{
    if(data == NULL)
        return;
    memset(data,0,number_threads*sizeof(thread_data));
    free(data);
    data = 0;
}
void free_pthread_t(pthread_t* thread_args, uint number_threads)
{
    if(thread_args == NULL)
        return;
    memset(thread_args,0,number_threads*sizeof(pthread_t));
    free(thread_args);
    thread_args = 0;
}

