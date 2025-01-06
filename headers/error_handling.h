//
// Created by pafnu on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_ERROR_HANDLING_H
#define MULTITHREAD_SUM_ERROR_HANDLING_H
#include <pthread.h>
#include "functions.h"

typedef unsigned int uint;


void file_error_handling();
void free_int(int*, uint);
void free_thread_data(thread_data*, uint);
void free_pthread_t(pthread_t*, uint);


#endif //MULTITHREAD_SUM_ERROR_HANDLING_H
