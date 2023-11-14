#ifndef parser_h
#define parser_h
#include "../inc/stats.h"

GHashTable *parse_files_flights(char *path, STATS *stats, GHashTable *invalid_flights);
GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights, GHashTable *invalid_users, GHashTable *invalid_flights);
GHashTable* parse_files_reservations(char *path, STATS*stats, GHashTable *users, GHashTable *invalid_users);
GHashTable *parse_files_users(char *path, GHashTable *invalid_users);

void printUserByID(GHashTable *users, char *id);
void printFlightrByID(GHashTable *flight, char *id);
void printPassanger(GArray *passenger);
void printReservationByID(GHashTable *reservations, char *id);

#endif