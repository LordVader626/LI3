#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/airport_stats.h"
#include "../inc/hotel_stats.h"


/*
    Struct que vai guardar as varias ststs
*/
struct stats
{
    GHashTable *user_stats;
    GHashTable *hotel_stats;
    GHashTable *airport_stats;

};

//GETTERS

GHashTable *get_user_stats(STATS *s)
{
    return s->user_stats;
}

GHashTable *get_hotel_stats(STATS *s)
{
    return s->hotel_stats;
}
GHashTable *get_airport_stats(STATS *s)
{
    return s->airport_stats;
}

/*
    Função que cria as estruturas de dados para as stats
*/
STATS *create_stats()
{
    STATS *s = malloc(sizeof(STATS));
    
    GHashTable *user_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_userStat);
    GHashTable *hotel_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_hotelStat);
    GHashTable *airport_stats = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_airportStat);
    
    s->user_stats = user_stats;
    s->hotel_stats = hotel_stats;
    s->airport_stats = airport_stats;

    return s;
}


/*
    Função que liberta o espaço das stats
*/
void destroy_stats(void *stats){
    STATS *s = stats;

    g_hash_table_destroy(s->user_stats);
    g_hash_table_destroy(s->hotel_stats);
    g_hash_table_destroy(s->airport_stats);
    free(s);

}
