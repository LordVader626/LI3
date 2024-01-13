#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ncurses.h>

#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/parser.h"
#include "../inc/handle.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/validation.h"
#include "../inc/batch.h"
#include "../inc/interativo.h"


int main(int argc, char **argv){
    /*Modo batch em que primeiro Input = o caminho para a pasta onde estão os cheiros de entrada 
    segundo input = caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados*/

    if (argc == 1){
        interativo();
    }

    else if (argc < 3){
        printf("Insufficient arguments, use <input_folder_path> <commands_file_path>\n");
    }

    if (argc == 3){

        clock_t start_time, end_time;
        double cpu_time_used;

        start_time = clock();

        char *files_path = strdup(argv[1]);
        char *data_input = strdup(argv[2]);

        batch(files_path, data_input);

        end_time = clock();

        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

        printf("CPU time used: %f seconds\n", cpu_time_used);

        free(files_path);
        free(data_input);

    }
    return 0;
}