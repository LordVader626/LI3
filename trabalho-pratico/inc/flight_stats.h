#ifndef flight_stats_h
#define flight_stats_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct f_stat FLIGHT_STAT;

char *get_flight_stat_id(FLIGHT_STAT *f);
int get_flight_stat_nPassageiros(FLIGHT_STAT *f);

void create_flight_stat(PASSENGER *p, GHashTable *flight_stats, GHashTable *flights);

#endif