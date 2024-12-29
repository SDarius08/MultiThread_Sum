//
// Created by pafnu on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_FILE_HANDLING_H
#define MULTITHREAD_SUM_FILE_HANDLING_H

#define _MAX_BUFFER 4026

int open_file(const char*);
void file_access(const char*);
void close_file(int*); // Giving a pointer, we can hide the number of files that are open

void read_file(int);


#endif //MULTITHREAD_SUM_FILE_HANDLING_H
