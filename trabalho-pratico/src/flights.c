#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include "../inc/flights.h"
#include "../inc/users.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/validation.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/hotel_stats.h"
#include "../inc/airport_stats.h"

struct flight {
    char *id;
    char *airline;
    char *plane_model;
    int total_seats;
    char *origin; //aeroporto de origem
    char *destination; // aeroporto de destino
    char *schedule_departure_date; //se possivel usar lib com datas
    char *schedule_arrival_date;
    char *real_departure_date;
    char *real_arrival_date;
    char *pilot; //nome do piloto
    char *copilot; //nome do copiloto
    char *notes; //observações sobre o voo
};

FLIGHT *new_Flight(char *line){

    FLIGHT *f = malloc(sizeof(FLIGHT));
    
    f->id = strdup(strsep(&line, ";"));
    f->airline = strdup(strsep(&line, ";"));
    f->plane_model = strdup(strsep(&line, ";"));
    f->total_seats = atoi(strsep(&line, ";"));
    f->origin = strdup(strsep(&line, ";"));
    f->destination = strdup(strsep(&line, ";"));
    f->schedule_departure_date = strdup(strsep(&line, ";"));
    f->schedule_arrival_date = strdup(strsep(&line, ";"));
    f->real_departure_date = strdup(strsep(&line, ";"));
    f->real_arrival_date = strdup(strsep(&line, ";"));
    f->pilot = strdup(strsep(&line, ";"));
    f->copilot = strdup(strsep(&line, ";"));
    f->notes = strdup(strsep(&line, "\n"));

    return f;
}

void kill_flight(void *flight){
    FLIGHT *f = flight;

    free(f->id);
    free(f->airline);
    free(f->plane_model);
    free(f->origin);
    free(f->destination);
    free(f->schedule_departure_date);
    free(f->schedule_arrival_date);
    free(f->real_departure_date);
    free(f->real_arrival_date);
    free(f->pilot);
    free(f->copilot);
    free(f->notes);
    free(f);
}


char *getID_flight(FLIGHT *f){
    /*char *str_id = malloc(11);
    sprintf(str_id, "%012d", f->id);
    return str_id;*/
    return strdup(f->id);
}

char *getAirline(FLIGHT *f) {
    return strdup(f->airline);
}

char *getPlaneModel(FLIGHT *f){
    return strdup(f->plane_model);
}

int getTotalSeats(FLIGHT *f){
    return (f->total_seats);
}

char *getFlightOrigin(FLIGHT *f){
    return strdup(f->origin);
}

char *getFlightDestination(FLIGHT *f){
    return strdup(f->destination);
}

char *getScheduleDepartureDate(FLIGHT *f) {
    return strdup(f->schedule_departure_date);
}

char *getScheduleArrivalDate(FLIGHT *f) {
    return strdup(f->schedule_arrival_date);
}

char *getRealDepartureDate(FLIGHT *f) {
    return strdup(f->real_departure_date);
}

char *getRealArrivalDate(FLIGHT *f) {
    return strdup(f->real_arrival_date);
}

char *getPilot(FLIGHT *f) {
    return strdup(f->pilot);
}

char *getCopilot(FLIGHT *f) {
    return strdup(f->copilot);
}

char *getNotes(FLIGHT *f) {
    return strdup(f->notes);
}
GHashTable *parse_files_flights(char *path, STATS *stats, GHashTable *invalid_flights){

    // ou usar func em utils
    char *path_flights = malloc(sizeof(char) * 70);
    char *path_flights_errors = malloc(sizeof(char) * 70);
    strcpy(path_flights, path);
    strcat(path_flights, "/flights.csv");
    strcpy(path_flights_errors, path);
    strcat(path_flights_errors, "/flights_errors.csv");

    char *line = NULL;
    size_t len = 0;

    GHashTable *flights = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_flight);

    FILE *file = fopen(path_flights, "r");
    //FILE *file_errors = fopen(path_flights_errors, "w");

    if (file == NULL /*|| file_errors == NULL*/) {
        printf("Unable to open the file.\n");
    }

    //escreve o cabeçalho no ficheiro dos erros
    //fprintf(file_errors, "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes\n");

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        FLIGHT *flight = new_Flight(line);

        if (flight_validation_1phase(flight) == 0){

            
        
            int i;
            for (i = 0; i < 3 && flight->origin[i] != '\0'; i ++){
                flight->origin[i] = toupper(flight->origin[i]);
            }
            
            for (i = 0; i < 3 && flight->destination[i] != '\0'; i ++){
                flight->destination[i] = toupper(flight->destination[i]);
            }

            g_hash_table_insert(flights, flight->id, flight);
            create_airport_stat_flight(flight, get_airport_stats(stats));          
        }
        else {

            g_hash_table_insert(invalid_flights, getID_flight(flight), "INVALIDO");

            char *airline = getAirline(flight);
            char *planeModel = getPlaneModel(flight);
            char *flightOrigin = getFlightOrigin(flight);
            char *flightDestination = getFlightDestination(flight);
            char *notrealDeparture = getScheduleDepartureDate(flight);
            char *notrealArrival = getScheduleArrivalDate(flight);
            char *realDeparture = getRealDepartureDate(flight);
            char *realArrival = getRealArrivalDate(flight);
            char *pilot = getPilot(flight);
            char *copilot = getCopilot(flight);
            char *notes = getNotes(flight);

            //fprintf(file_errors,"%10s;%s;%s;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",flightID, airline, planeModel, getTotalSeats(flight), flightOrigin,
            //        flightDestination, notrealDeparture, notrealArrival, realDeparture, realArrival, pilot, copilot, notes);

            kill_flight(flight);

            free(airline);
            free(planeModel);
            free(flightOrigin);
            free(flightDestination);
            free(notrealDeparture);
            free(notrealArrival);
            free(realArrival);
            free(realDeparture);
            free(pilot);
            free(copilot);
            free(notes);
        }
    }
    printf("Flight Validation and Parsing SuccessFull\n");

    fclose(file);
    //fclose(file_errors);
    free(line);
    free(path_flights);
    free(path_flights_errors);

    return flights;
}