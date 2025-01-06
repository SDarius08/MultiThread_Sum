//
// Created by pafnu on 12/24/2024.
//
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "../headers/functions.h"
#include "../headers/error_handling.h"

void* calculate_partial_sum(void *arg) {
    thread_data *data = (thread_data *)arg;
    size_t i = 0;

    data->thread_id = pthread_self();
    uint128 local_sum = 0;

    // Calculate sum for the assigned chunk
    for (i = data->start; i < data->end; ++i) {
        local_sum += (uint128)data->numbers[i];
    }

    // Store the partial sum
    data->partial_sum = local_sum;

    return NULL;
}

void calculate_chunked_sum(size_t num_threads, int fd) {
    int *numbers = malloc(_MAX_DIM_VECTOR * sizeof(int));
    if (numbers == NULL) {
        perror("Failed to allocate memory for numbers");
        return;
    }

    size_t size = 0;
    ssize_t bytes_read;

    FILE *file = fopen("../testv2.txt", "r");
    if (!file)
    {
        perror("Failed to open file");
    }

    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        // Store the number in the numbers array
        numbers[size] = num;
        ++size;
    }

/*
    // Read numbers from file
    while ((bytes_read = read(fd, (numbers+size), sizeof(int))) > 0)
    {
        ++size;
        if (size >= _MAX_DIM_VECTOR) {
            perror("File contains more numbers than the allocated buffer size\n");
            free(numbers);
            return;
        }
    }
    */

    if (bytes_read == -1) {
        perror("Error reading file");
        free(numbers);
        return;
    }

    // Create and initialize thread data
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    thread_data *thread_args = malloc(num_threads * sizeof(thread_data));
    uint128 total_sum = 0;

    if (threads == NULL || thread_args == NULL) {
        perror("Failed to allocate memory for threads or thread arguments");
        free(numbers);
        free(threads);
        free(thread_args);
        return;
    }

    size_t chunk_size = size / num_threads;
    size_t remainder = size % num_threads;
    size_t i = 0;


    for (i = 0; i < num_threads; ++i) {
        thread_args[i].numbers = numbers;
        thread_args[i].start = i * chunk_size;
        thread_args[i].end = thread_args[i].start + chunk_size;

        if (i == num_threads - 1) {
            thread_args[i].end += remainder;
        }

        thread_args[i].partial_sum = 0;

        // Debugging statement to verify chunk assignment
        printf("Thread %zu processing from index %zu to %zu\n", i, thread_args[i].start, thread_args[i].end);

        if (pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
    }

    // Wait for threads and accumulate partial sums
    for (i = 0; i < num_threads; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
        printf("Partial sum for thread %zu, thread_id: %llu is: %llu\n", i, thread_args[i].thread_id, thread_args[i].partial_sum);
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

void calculate_chunked_sumv2(size_t num_threads, FILE* file) {
    int *numbers = malloc(_MAX_DIM_VECTOR * sizeof(int));
    if (numbers == NULL) {
        perror("Failed to allocate memory for numbers");
        return;
    }

    size_t size = 0;

    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        // Store the number in the numbers array
        numbers[size] = num;
        ++size;
    }

    // Create and initialize thread data
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    thread_data *thread_args = malloc(num_threads * sizeof(thread_data));
    uint128 total_sum = 0;

    if (threads == NULL || thread_args == NULL) {
        perror("Failed to allocate memory for threads or thread arguments");
        free(numbers);
        free(threads);
        free(thread_args);
        return;
    }

    size_t chunk_size = size / num_threads;
    size_t remainder = size % num_threads;
    size_t i = 0;


    for (i = 0; i < num_threads; ++i) {
        thread_args[i].numbers = numbers;
        thread_args[i].start = i * chunk_size;
        thread_args[i].end = thread_args[i].start + chunk_size;

        if (i == num_threads - 1) {
            thread_args[i].end += remainder;
        }

        thread_args[i].partial_sum = 0;

        // Debugging statement to verify chunk assignment
        printf("Thread %zu processing from index %zu to %zu\n", i, thread_args[i].start, thread_args[i].end);

        if (pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
    }

    // Wait for threads and accumulate partial sums
    for (i = 0; i < num_threads; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            free(numbers);
            free(threads);
            free(thread_args);
            return;
        }
        printf("Partial sum for thread %zu, thread_id: %llu\n", i, thread_args[i].thread_id);
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

// Helper to print uint128
void print_uint128(uint128 value) {
    char buffer[40] = {0};  // Enough space for a 128-bit number in decimal
    char *ptr = buffer + sizeof(buffer) - 1;  // Start at the end of the buffer
    *ptr = '\0';

    do {
        *(--ptr) = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    printf("%s\n", ptr);
}