#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/parser.h"
#include "../inc/handle.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/validation.h"

int main(int argc, char **argv){
    /*Modo batch em que primeiro Input = o caminho para a pasta onde estão os cheiros de entrada 
    segundo input = caminho para um ficheiro de texto que contém uma lista de comandos (queries) a serem executados*/

    if (argc < 3){
        printf("Insufficient arguments, use <input_folder_path> <commands_file_path>\n");
    }

    if (argc == 3){
        char *files_path = strdup(argv[1]);
        char *data_input = strdup(argv[2]);

        GHashTable *invalid_users = g_hash_table_new(g_str_hash, g_str_equal);
        GHashTable *invalid_flights = g_hash_table_new(g_str_hash, g_str_equal);

        STATS *stats = create_stats();

        GHashTable *users = parse_files_users(files_path, invalid_users);
        GHashTable *flights = parse_files_flights(files_path, stats, invalid_flights);
        GArray *passengers = parse_files_passengers(files_path,stats,users,flights,invalid_users,invalid_flights);
        GHashTable *reservations = parse_files_reservations(files_path, stats, users, invalid_users);

        //printUserByID(users, "DGarcia429");
        //printFlightrByID(flights, "100");
        //printPassanger(passengers);
        //printReservationByID(reservations, "Book0000020828");//Book0000024352

        //validade_files(users);//, flights, reservations, get_flight_stats(stats));

        handle(data_input, users, flights, passengers, reservations, stats, invalid_users);

        g_hash_table_destroy(invalid_flights);
        g_hash_table_destroy(invalid_users);


        free(files_path);
        free(data_input);

        g_hash_table_destroy(users);
        g_hash_table_destroy(flights);
        g_hash_table_destroy(reservations);
        freeGArray(passengers);
        destroy_stats(stats);

    }
    printf("EXECUTION FINISHED\n");
    return 0;
}