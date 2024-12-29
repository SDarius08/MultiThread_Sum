//
// Created by pafnu on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_FUNCTIONS_H
#define MULTITHREAD_SUM_FUNCTIONS_H

#define _MAX_DIM_VECTOR 1000

#include <pthread.h>

typedef struct{
    int *numbers;
    int start;
    int end;
    long partial_sum;
    pid_t pid;
}thread_data;

void* calculate_partial_sum(void *);

void calculate_chunked_sum(size_t, int);



#endif //MULTITHREAD_SUM_FUNCTIONS_H
