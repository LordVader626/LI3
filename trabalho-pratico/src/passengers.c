#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/passengers.h"

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

void kill_Passenger(PASSENGER *p){
    free(p->flight_id);
    free(p->user_id);
    free(p);
}