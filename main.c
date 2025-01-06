#include <stdio.h>
#include "headers/functions.h"
#include "headers/file_handling.h"

int main()
{
    size_t n = 0;
    FILE *file = 0;
    file = open_file_v2("../test_files/test.txt");
    printf("Introduce the number of threads: ");
    scanf("%d",&n);
    while(n <= 0)
    {
        printf("Incorrect number, it must be positive: ");
        scanf("%d",&n);
    }


    calculate_chunked_sumv2(n,file);
    return 0;
}