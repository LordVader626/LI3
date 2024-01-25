#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#include "../inc/tests.h"


void print_memory_usage() {
    struct rusage usage;

    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        long megabytes = usage.ru_maxrss / 1024;
        printf("Memoria Usada: %ld megabytes\n", megabytes);
    } 
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Insufficient arguments, use <input_folder_path> <commands_file_path> <results_path>\n");
        return 1;
    }
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    char *files_path = argv[1];
    char *data_input = argv[2];
    char *test_path = argv[3];

    run_test(files_path, data_input);
    execute_tests(data_input, test_path);

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    print_memory_usage();

    return 0;
}