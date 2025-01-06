//
// Created by pafnu on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_FUNCTIONS_H
#define MULTITHREAD_SUM_FUNCTIONS_H

#define _MAX_DIM_VECTOR 1000

#include <pthread.h>
#include <stdint.h>

typedef __uint128_t uint128;

typedef struct {
    int *numbers;
    size_t start;
    size_t end;
    uint128 partial_sum;
    pid_t pid;
} thread_data;

void* calculate_partial_sum(void *);
void calculate_chunked_sum(size_t, int);
void print_uint128(uint128 value);

#endif //MULTITHREAD_SUM_FUNCTIONS_H
