#ifndef passengers_h
#define passengers_h
#include"../inc/stats.h"
#include <glib.h>

#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_user.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"

typedef struct passenger PASSENGER;

PASSENGER *create_Passenger(char *line);
char *getID_passenger(PASSENGER *p);
char *get_FlightID_passenger(PASSENGER *p);
void kill_Passenger(void *passenger);
void freeGArray(GArray *garray);
GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights, GHashTable *invalid_users, GHashTable *invalid_flights);

//int start_passenger_process(char *line,CATALOGO_PASSENGER *cat_passenger, CATALOGO_INVALID *cat_invalids, STATS *stats, CATALOGO_FLIGHTS *cat_flights, CATALOGO_USER *cat_users);
int start_passenger_process(char *line,CATALOGO_PASSENGER *cat_passenger, CATALOGO_INVALID *cat_invalids, STATS *stats, CATALOGO_FLIGHTS *cat_flights, CATALOGO_USER *cat_users, GHashTable *stats_needed);

#endif
