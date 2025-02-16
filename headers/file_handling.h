//
// Created by pafnu on 12/24/2024.
//

#ifndef MULTITHREAD_SUM_FILE_HANDLING_H
#define MULTITHREAD_SUM_FILE_HANDLING_H

#define _MAX_BUFFER 4026
FILE* open_file_v2(const char* file_name);
int open_file(const char*);
void file_access(const char*);
void close_file(int*); // Giving a pointer, we can hide the number of files that are open


#endif //MULTITHREAD_SUM_FILE_HANDLING_H
