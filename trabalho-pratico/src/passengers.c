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
#include "../inc/catalogo_flights.h"

/*
    Struct responsavel por guardar os dados dos passageiros
*/
struct passenger{
    char *flight_id;
    char *user_id;
};

int start_passenger_process(char *line,CATALOGO_PASSENGER *cat_passenger, CATALOGO_INVALID *cat_invalids, STATS *stats, CATALOGO_FLIGHTS *cat_flights, CATALOGO_USER *cat_users){

    PASSENGER *p = create_Passenger(line);
    
    char *flightID = get_FlightID_passenger(p);
    char *userID = getID_passenger(p);
    if(!cointains_invalid_user(cat_invalids, userID) && !cointains_invalid_flight(cat_invalids, flightID) && strcmp("",p->flight_id) != 0){
        addPassenger(cat_passenger, p);
        
        if(contains_stat(stats, p->user_id))
            create_user_stat_flights(p, stats, cat_users, cat_flights);
        create_airport_stat_passenger(p, stats, cat_flights);

        free(flightID);
        free(userID);

        return 0;
    }

    free(flightID);
    free(userID);
    kill_Passenger(p);

    return 1;
}
/*
    Função responsavel pela criação de uma struct PASSENGER e atribuição dos seus dados
*/
PASSENGER *create_Passenger(char *line){

    PASSENGER *p = malloc(sizeof(PASSENGER));

    p->flight_id = strdup(strsep(&line, ";"));
    p->user_id = strdup(strsep(&line, "\n"));

    return p;
}


// GETTERS
char *get_FlightID_passenger(PASSENGER *p){
    return strdup(p->flight_id);
}

char *getID_passenger(PASSENGER *p){
    return strdup(p->user_id);
}

/*
    Função que liberta o espaço alocado na funcao create_passenger
*/
void kill_Passenger(void *passenger){
    PASSENGER *p = passenger;

    free(p->flight_id);
    free(p->user_id);
    free(p);
}


/*
    Função responsavel por dar free ao array completo
*/
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