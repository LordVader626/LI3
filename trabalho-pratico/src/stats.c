#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/stats.h"
#include "../inc/user_stat.h"



struct stats
{
    GHashTable *user_stats;
    GHashTable *flight_stats;

};

GHashTable *get_user_stats(STATS *s)
{
    return s->user_stats;
}
GHashTable *get_flight_stats(STATS *s)
{
    return s->flight_stats;
}

STATS *create_stats()
{
    STATS *s = malloc(sizeof(STATS));
    
    GHashTable *user_stats = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable *flight_stats = g_hash_table_new(g_str_hash, g_str_equal);
    
    s->user_stats = user_stats;
    s->flight_stats = flight_stats;
    

    return s;
}

void destroy_stats(STATS *s)
{
    if (s != NULL) {
        g_hash_table_destroy(s->user_stats);
        free(s);
    }
}
