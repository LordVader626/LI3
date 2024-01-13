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
    GHashTable *stats_needed;
};

//GETTERS

GHashTable *get_user_stats(STATS *s)
{
    return s->user_stats;
}

USER_STAT *get_stat_user(STATS *s, char *user_id){
    return (USER_STAT*) g_hash_table_lookup(s->user_stats, user_id);
}

void addUserStat (STATS *s, USER_STAT *ustat, char *username){
    g_hash_table_insert(s->user_stats, username, ustat);
}

HOTEL_STAT *get_stat_hotel(STATS *s, char *hotel_id){
    return (HOTEL_STAT*) g_hash_table_lookup(s->hotel_stats, hotel_id);
}

void addHotelStat (STATS *s, HOTEL_STAT *hstat, char *hotel){
    g_hash_table_insert(s->hotel_stats, hotel, hstat);
}

GHashTable *get_hotel_stats(STATS *s)
{
    return s->hotel_stats;
}

AIRPORT_STAT *get_stat_airport(STATS *s, char *airport_id){
    return (AIRPORT_STAT*) g_hash_table_lookup(s->airport_stats, airport_id);
}

void addAirportStat (STATS *s, AIRPORT_STAT *astat, char *aiport){
    g_hash_table_insert(s->airport_stats, aiport, astat);
}

GList *get_airport_stats_values(STATS *s){
    return g_hash_table_get_values(s->airport_stats);
}

GHashTable *get_airport_stats(STATS *s)
{
    return s->airport_stats;
}

void addStatNeeded(STATS *s, char *key){
    if (!contains_stat(s, key)){
        g_hash_table_insert(s->stats_needed, key, key);
        //printf("Inserted %s\n", key);
    }
    else{
        free(key);
    }
}

GHashTable *get_stats_needed(STATS *s)
{
    return s->stats_needed;
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
    // como ambas sao o mesmo dup so precisa de dar free a uma
    GHashTable *stats_needed = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, free);
    
    s->user_stats = user_stats;
    s->hotel_stats = hotel_stats;
    s->airport_stats = airport_stats;
    s->stats_needed = stats_needed;

    return s;
}

int contains_stat(STATS *stats, char *key){
    return g_hash_table_contains(stats->stats_needed, key);
}

void destroy_stats_needed(STATS *stats){
    g_hash_table_destroy(stats->stats_needed);
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
