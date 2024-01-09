#ifndef stats_h
#define stats_h

#include <glib.h>

typedef struct stats STATS;
/*

*/
struct user_stat;
typedef struct user_stat USER_STAT;
GHashTable *get_user_stats(STATS *s);
USER_STAT *get_stat_user(STATS *s, char *user_id);
void addUserStat (STATS *s, USER_STAT *ustat, char *username);

struct hotel_stat;
typedef struct hotel_stat HOTEL_STAT;
HOTEL_STAT *get_stat_hotel(STATS *s, char *hotel_id);
void addHotelStat (STATS *s, HOTEL_STAT *hstat, char *hotel);
GHashTable *get_hotel_stats(STATS *s);

struct airport_stat;
typedef struct airport_stat AIRPORT_STAT;
AIRPORT_STAT *get_stat_airport(STATS *s, char *airport_id);
void addAirportStat (STATS *s, AIRPORT_STAT *astat, char *aiport);
GList *get_airport_stats_values(STATS *s);
GHashTable *get_airport_stats(STATS *s);

void addStatNeeded(STATS *s, char *value);
GHashTable *get_stats_needed(STATS *s);

STATS *create_stats();

int contains_stat(STATS *stats, char *key);

void destroy_stats(void *stats);
//void print_stats(STATS *s);

#endif