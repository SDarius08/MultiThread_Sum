#include <stdio.h>
#include "headers/functions.h"
#include "headers/file_handling.h"

int main()
{
    int fd;
    size_t n = 10;

    // -------------------------------------------------------
    fd = open_file("D:\\\\Personal\\\\MultiThread_Sum\\\\test.txt");
    //printf("S-a deschis file-ul: %d\n",fd);

    calculate_chunked_sum(n,fd);

    close_file(&fd);
    //printf("S-a inchis file-ul: %d\n", fd);
    return 0;
}