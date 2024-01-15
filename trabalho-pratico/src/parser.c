#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/parser.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/passengers.h"
#include "../inc/stats.h"

void parse_files_users_teste(char *path, CATALOGO_USER *catusers, CATALOGO_INVALID *cat_invalids){

    char *path_users = malloc(sizeof(char) * 70);
    strcpy(path_users, path);
    strcat(path_users, "/users.csv");
    char *path_user_erros = "Resultados/users_errors.csv";

    char *line = NULL;
    size_t len = 0;

    FILE *file = fopen(path_users, "r");
    FILE *file_error = fopen(path_user_erros, "w");

    if (file == NULL || file_error == NULL) {
        printf("Unable to open the file.\n");
        fclose(file);
        fclose(file_error);
    }

    // cabeçalho ficheiro de erros
    fprintf(file_error, "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status\n");

    //skip ao cabeçalho do ficheiro input
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){

        char *temp = strdup(line);    
        int status = start_user_process(line, catusers, cat_invalids);

        if (status != 0){

            fprintf(file_error, "%s", temp);

        }
        free(temp);
    }
    fclose(file);
    fclose(file_error); 
    free(line);
    free(path_users);
}

void parse_files_flights_teste(char *path, CATALOGO_FLIGHTS *cat_flights,STATS *stats, CATALOGO_INVALID *cat_invalids){

    // ou usar func em utils
    char *path_flights = malloc(sizeof(char) * 70);
    strcpy(path_flights, path);
    strcat(path_flights, "/flights.csv");
    char *path_flights_errors = "Resultados/flights_errors.csv";

    char *line = NULL;
    size_t len = 0;

    FILE *file = fopen(path_flights, "r");
    FILE *file_errors = fopen(path_flights_errors, "w");

    if (file == NULL || file_errors == NULL) {
        printf("Unable to open the file.\n");
        fclose(file);
        fclose(file_errors);
    }

    //escreve o cabeçalho no ficheiro dos erros
    fprintf(file_errors, "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes\n");

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        
        char *temp = strdup(line);

        int status = start_flight_process(line, cat_flights, cat_invalids, stats);

        if (status != 0){

            fprintf(file_errors, "%s",temp);

        }
        free(temp);
    }
    //printf("Flight Validation and Parsing SuccessFull\n");

    fclose(file);
    fclose(file_errors);
    free(line);
    free(path_flights);
}

//void parse_files_passengers_teste(char *path, STATS*stats, CATALOGO_PASSENGER *cat_passenger, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_INVALID *cat_invalids, GHashTable *stats_needed) {
void parse_files_passengers_teste(char *path, STATS *stats, CATALOGO_PASSENGER *cat_passenger, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_INVALID *cat_invalids) {
  
    char *path_passengers = malloc(sizeof(char) * 70);
    strcpy(path_passengers, path);
    strcat(path_passengers, "/passengers.csv");
    char *path_passengers_erros = "Resultados/passengers_errors.csv";

    char *line = NULL;
    size_t len = 0;

    FILE *file = fopen(path_passengers, "r");
    FILE *file_errors = fopen(path_passengers_erros, "w");

    //cabeçalho ficheiro de erros
    fprintf(file_errors, "flight_id;user_id\n");

    if (file == NULL) {
        printf("Unable to open the file.\n");
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1) {

        char *temp = strdup(line);
        //printf("%s\n", line);
        int status = start_passenger_process(line, cat_passenger, cat_invalids, stats, cat_flights, cat_users);

        if (status != 0){
            fprintf(file_errors, "%s", temp);
        }
        free(temp);
    }

    //printf("Passenger Validation and Parsing Successfull\n");
    free(line);
    free(path_passengers);
    fclose(file_errors);
    fclose(file);
}

void parse_files_reservations_test(char *path, STATS *stats, CATALOGO_RESERVATIONS *cat_reservations, CATALOGO_USER *cat_users, CATALOGO_INVALID *cat_invalids) {
//void parse_files_reservations_test(char *path, STATS *stats, CATALOGO_RESERVATIONS *cat_reservations, CATALOGO_USER *cat_users, CATALOGO_INVALID *cat_invalids, GHashTable *stats_needed) {

    char *line = NULL;
    size_t len = 0;
    
    char *path_reservations = malloc(sizeof(char) * 70);
    strcpy(path_reservations, path);
    strcat(path_reservations, "/reservations.csv");
    char *path_reservations_erros = "Resultados/reservations_errors.csv";

    FILE *file = fopen(path_reservations, "r");
    FILE *file_errors = fopen(path_reservations_erros, "w");

    if (file == NULL || file_errors == NULL) {
        printf("Unable to open the file.\n");
    }

    //cabeçalho ficheiro de erros
    fprintf(file_errors, "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment\n");

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){

        char *temp = strdup(line);

        int status = start_reservation_process(line, cat_users, cat_reservations, stats, cat_invalids);

        if (status != 0){

            fprintf(file_errors, "%s", temp);

        }
         free(temp);
        
    }
    //printf("Reservation validition and Parsing Sucessfull\n");
    free(line);
    free(path_reservations);
    fclose(file);
    fclose(file_errors);
}