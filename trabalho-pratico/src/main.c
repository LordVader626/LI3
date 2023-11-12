#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"


int main(int argc, char **argv){
    /*Modo batch em que primeiro Input = o caminho para a pasta onde estão os cheiros de entrada 
    segundo input = caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados*/

    if (argc < 3){
        printf("Insufficient arguments, use <input_folder_path> <commands_file_path>\n");
    }

    if (argc == 3){
        char *files_path = strdup(argv[1]);
        char *data_input = strdup(argv[2]);

        //files parsing

    }
    return 0;
}