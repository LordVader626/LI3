#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/flights.h"

struct flight {
    int id;
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
    
    f->id = atoi(strsep(&line, ";"));
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


char *getID_flight(FLIGHT *f){
    char *str = malloc(10); //cada id é uma string de 10 caracteres
    sprintf(str, "%d", f->id);
    return strdup(str);
}

char *getAirline(FLIGHT *f) {
    return strdup(f->airline);
}

char *getPlaneModel(FLIGHT *f){
    return strdup(f->plane_model);
}

char *getTotalSeats(FLIGHT *f){
    char *str = malloc(3);
    sprintf(str, "%d", f->total_seats);
    return strdup(str);
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
