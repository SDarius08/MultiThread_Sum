//
// Created by pafnu on 12/24/2024.
//
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include "../headers/functions.h"

void* calculate_partial_sum(void *arg) {
    thread_data *data = (thread_data *)arg;
    size_t i = 0;

    data->pid = getpid();
    uint128 local_sum = 0;

    // Calculate sum
    for (i = data->start; i < data->end; ++i) {
        local_sum += (__uint128_t)data->numbers[i];
    }

    // Store the partial sum
    data->partial_sum = local_sum;

    return NULL;
}

void calculate_chunked_sum(size_t num_threads, int fd) {
    int *numbers = malloc(_MAX_DIM_VECTOR * sizeof(int));
    if (!numbers) {
        perror("Failed to allocate memory for numbers");
        return;
    }

    size_t size = 0;
    ssize_t bytes_read;

    // Read numbers from file
    while ((bytes_read = read(fd, &numbers[size], sizeof(int))) > 0) {
        size++;
        if (size >= _MAX_DIM_VECTOR) {
            fprintf(stderr, "File contains more numbers than the allocated buffer size\n");
            free(numbers);
            return;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        free(numbers);
        return;
    }

    // Create and initialize thread data
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    thread_data *thread_args = malloc(num_threads * sizeof(thread_data));
    uint128 total_sum = 0;

    if (!threads || !thread_args) {
        perror("Failed to allocate memory for threads or thread arguments");
        free(numbers);
        free(threads);
        free(thread_args);
        return;
    }

    size_t chunk_size = size / num_threads;
    size_t remainder = size % num_threads;

    for (size_t i = 0; i < num_threads; ++i) {
        thread_args[i].numbers = numbers;
        thread_args[i].start = i * chunk_size;
        thread_args[i].end = thread_args[i].start + chunk_size;

        if (i == num_threads - 1) {
            thread_args[i].end += remainder;
        }

        thread_args[i].partial_sum = 0;

        if (pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
    }

    // Wait for threads and accumulate partial sums
    for (size_t i = 0; i < num_threads; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
        printf("Partial sum for thread %zu, pid: %d\n", i, thread_args[i].pid);
        total_sum += thread_args[i].partial_sum;
    }

    // Print the total sum
    printf("Total sum: ");
    print_uint128(total_sum);

    // Clean up
    free(numbers);
    free(threads);
    free(thread_args);
}

// Helper to print __uint128_t
void print_uint128(uint128 value) {
    char buffer[40];
    sprintf(buffer, "%llu%llu",
            (unsigned long long)(value >> 64),
            (unsigned long long)(value & 0xFFFFFFFFFFFFFFFF));
    printf("%s\n", buffer);
}
