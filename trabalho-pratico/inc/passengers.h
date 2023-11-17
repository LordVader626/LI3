#ifndef passengers_h
#define passengers_h
#include"../inc/stats.h"
#include <glib.h>

typedef struct passenger PASSENGER;

PASSENGER *create_Passenger(char *line);
char *getID_passenger(PASSENGER *p);
char *get_FlightID_passenger(PASSENGER *p);
void kill_Passenger(void *passenger);
void freeGArray(GArray *garray);
GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights, GHashTable *invalid_users, GHashTable *invalid_flights);
#endif
