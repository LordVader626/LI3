#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
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