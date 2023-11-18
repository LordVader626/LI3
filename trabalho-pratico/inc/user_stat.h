#ifndef user_stat_h
#define user_stat_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct stat USER_STAT;

char *get_user_stat_username(USER_STAT *s);
int get_user_stat_numReservas(USER_STAT *s);
int get_user_stat_numVoos(USER_STAT *s);
GList* get_user_stat_listaVoos(USER_STAT *s);
GList* get_user_stat_listaReservas(USER_STAT *s);
double get_user_stat_totalGasto(USER_STAT *s);

void create_user_stat_flights(PASSENGER *p, GHashTable *user_stats, GHashTable *users, GHashTable *flights);
void create_user_stat_reservations(RESERVATION *r, GHashTable *user_stats, GHashTable *users);

void kill_userStat(void *userStat);

void print_user_stat(USER_STAT *user_stat);


#endif