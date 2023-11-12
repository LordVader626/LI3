#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/passengers.h"

struct passenger{
    int flight_id;
    char *user_id;
};
PASSENGER *create_Passenger(char *line){

    PASSENGER *p = malloc(sizeof(PASSENGER));

    p->flight_id = atoi(strsep(&line, ";"));
    p->user_id = strdup(strsep(&line, "\n"));

    return p;
}

int get_FlightID_passenger(PASSENGER *p){
    return p->flight_id;
}

char *getID_passenger(PASSENGER *p){
    return strdup(p->user_id);
}