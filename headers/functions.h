//
// Created by Darius on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_FUNCTIONS_H
#define MULTITHREAD_SUM_FUNCTIONS_H

#define _MAX_DIM_VECTOR 1024  // Maximum size of the vector to be processed

#include <pthread.h>
#include <stdint.h>

// Alias for 128-bit unsigned integer
typedef __uint128_t uint128;

// Structure for passing data to threads
typedef struct {
    int *numbers;             // Pointer to the array of numbers
    unsigned long long thread_id; // ID of the thread (for debugging/logging)
    size_t start;             // Start index of the chunk to process
    size_t end;               // End index of the chunk to process (exclusive)
    uint128 partial_sum;      // Partial sum calculated by the thread
} thread_data;

// Function to calculate a partial sum in a thread
void* calculate_partial_sum(void *arg);

// Function to calculate the sum of numbers using multiple threads
void calculate_chunked_sum(size_t num_threads, int fd);
void calculate_chunked_sumv2(size_t num_threads, FILE*);

// Function to print a 128-bit unsigned integer
void print_uint128(uint128 value);

#endif // MULTITHREAD_SUM_FUNCTIONS_H
