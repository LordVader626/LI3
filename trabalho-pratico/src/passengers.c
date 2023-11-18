#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/passengers.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/validation.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/hotel_stats.h"
#include "../inc/airport_stats.h"

struct passenger{
    char *flight_id;
    char *user_id;
};
PASSENGER *create_Passenger(char *line){

    PASSENGER *p = malloc(sizeof(PASSENGER));

    p->flight_id = strdup(strsep(&line, ";"));
    p->user_id = strdup(strsep(&line, "\n"));

    return p;
}

char *get_FlightID_passenger(PASSENGER *p){
    return strdup(p->flight_id);
}

char *getID_passenger(PASSENGER *p){
    return strdup(p->user_id);
}

void kill_Passenger(void *passenger){
    PASSENGER *p = passenger;

    free(p->flight_id);
    free(p->user_id);
    free(p);
}

void freeGArray(GArray *garray) {
    g_assert(garray != NULL);

    for (guint i = 0; i < garray->len; i++) {
        PASSENGER* p = g_array_index(garray, PASSENGER*, i);
        free(p->flight_id);
        free(p->user_id);
        free(p);
    }

    g_array_free(garray, TRUE);
}

GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights, GHashTable *invalid_users, GHashTable *invalid_flights) {
    char *path_passengers = malloc(sizeof(char) * 70);
    strcpy(path_passengers, path);
    strcat(path_passengers, "/passengers.csv");
    char *path_passengers_erros = "Resultados/passengers_errors.csv";

    char *line = NULL;
    size_t len = 0;

    GArray *passengers = g_array_new(FALSE, TRUE, sizeof(PASSENGER *));

    FILE *file = fopen(path_passengers, "r");
    FILE *file_errors = fopen(path_passengers_erros, "w");

    fprintf(file_errors, "flight_id;user_id\n");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return NULL;
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1) {

        PASSENGER *passenger = create_Passenger(line);

        if((g_hash_table_contains(invalid_users, passenger->user_id) == FALSE) && (!g_hash_table_contains(invalid_flights, passenger->flight_id))){
            g_array_append_val(passengers, passenger);

            create_user_stat_flights(passenger, get_user_stats(stats), users, flights);
            create_airport_stat_passenger(passenger, get_airport_stats(stats), flights);
        }
        else{
            fprintf(file_errors, "%s;%s\n", passenger->flight_id, passenger->user_id);
            kill_Passenger(passenger);
        }

    }

    printf("Passenger Validation and Parsing Successfull\n");
    free(line);
    free(path_passengers);
    fclose(file_errors);
    fclose(file);

    return passengers;
}