#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/stats.h"



struct stats
{
    GHashTable *flight_stats;

};

GHashTable *get_flight_stats(STATS *s)
{
    return s->flight_stats;
}

STATS *create_stats()
{
    STATS *s = malloc(sizeof(STATS));
    
    GHashTable *flight_stats = g_hash_table_new(g_str_hash, g_str_equal);
    
    s->flight_stats = flight_stats;
    

    return s;
}

void destroy_stats(STATS *s)
{
    if (s != NULL) {
        g_hash_table_destroy(s->flight_stats);
        free(s);
    }
}
