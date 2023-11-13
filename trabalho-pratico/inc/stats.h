#ifndef stats_h
#define stats_h

#include <glib.h>

typedef struct stats STATS;

GHashTable *get_flight_stats(STATS *s);

STATS *create_stats();

void destroy_stats(STATS *s);
//void print_stats(STATS *s);

#endif