#ifndef queries_h
#define queries_h

#include "../inc/reservations.h"
#include "../inc/stats.h"

void query1(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats,GHashTable *flight_stats);
void query2(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats);

#endif