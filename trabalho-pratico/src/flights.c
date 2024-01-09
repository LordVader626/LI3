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


/*
    Struct responsavel por guardar os dados dos voos
*/
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
};

int start_flight_process(char *line, CATALOGO_FLIGHTS *cat_flights, CATALOGO_INVALID *cat_invalids, STATS *stats){
    FLIGHT *f = new_Flight(line);
    if(flight_validation_1phase(f) == 0){

        int i;
        for (i = 0; i < 3 && f->origin[i] != '\0'; i ++){
            f->origin[i] = toupper(f->origin[i]);
        }
        
        for (i = 0; i < 3 && f->destination[i] != '\0'; i ++){
            f->destination[i] = toupper(f->destination[i]);
        }

        addFlight(cat_flights, f->id, f);
        create_airport_stat_flight(f, stats);  
        return 0;
    }
    else{
       if(strcmp("",f->id) != 0) 

            addInvalidFlight(cat_invalids, getID_flight(f), "INVALIDO");
            //g_hash_table_replace(invalid_flights, getID_flight(f), "INVALIDO");
        
        kill_flight(f);
        return 1;
    }
    return 1;
}

/*
    Função responsavel por iniciar uma struct FLIGHT com as suas informações
*/
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
    strsep(&line, "\n");

    return f;
}


/*
    Função que apaga a memoria alocada na função new_flight
*/
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
    free(f);
}


// getters

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