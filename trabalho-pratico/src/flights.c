#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/flights.h"

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

gpointer copy_FLIGHT(gconstpointer f, gpointer user_data) {
    FLIGHT *flightToCopy = (FLIGHT *)f;
    FLIGHT *flight = g_slice_new(FLIGHT);

    flight->id = strdup(flightToCopy->id);
    flight->airline = strdup(flightToCopy->airline);
    flight->plane_model = strdup(flightToCopy->plane_model);
    flight->total_seats = flightToCopy->total_seats;
    flight->origin = strdup(flightToCopy->origin);
    flight->destination = strdup(flightToCopy->destination);
    flight->schedule_departure_date = strdup(flightToCopy->schedule_departure_date);
    flight->schedule_arrival_date = strdup(flightToCopy->schedule_arrival_date);
    flight->real_departure_date = strdup(flightToCopy->real_departure_date);
    flight->real_arrival_date = strdup(flightToCopy->real_arrival_date);
    flight->pilot = strdup(flightToCopy->pilot);
    flight->copilot = strdup(flightToCopy->copilot);
    flight->notes = strdup(flightToCopy->notes);

    return flight;
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
