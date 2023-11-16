#ifndef airport_stats_h
#define airport_stats_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct a_stat AIRPORT_STAT;

char *get_airport_stat_id(AIRPORT_STAT *a);
int *get_airport_stat_nPassageirosAno(AIRPORT_STAT *a);
GArray *get_airport_stat_atrasosVoos(AIRPORT_STAT *a);
int get_airport_stat_nVoos(AIRPORT_STAT *a);
GList *get_airport_stat_listaVoos(AIRPORT_STAT *a);


void create_airport_stat_flight(FLIGHT *f, GHashTable *airport_stats) ;
void create_airport_stat_passenger(PASSENGER *p, GHashTable *airport_stats,GHashTable *flights);

void kill_airportStat(void *airportStat);


#endif