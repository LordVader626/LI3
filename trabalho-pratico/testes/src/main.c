#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../inc/tests.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Insufficient arguments, use <input_folder_path> <commands_file_path> <results_path>\n");
        return 1;
    }

    char *files_path = argv[1];
    char *data_input = argv[2];
    char *test_path = argv[3];

    run_test(files_path, data_input);

    execute_tests(data_input, test_path);

    return 0;
}