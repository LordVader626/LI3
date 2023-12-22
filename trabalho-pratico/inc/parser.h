#ifndef parser_h
#define parser_h

#include "../inc/catalogo_user.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_invalids.h"
#include "../inc/reservations.h"

#include "../inc/stats.h"

void parse_files_users_teste(char *path, CATALOGO_USER *catusers, CATALOGO_INVALID *cat_invalids);
void parse_files_flights_teste(char *path, CATALOGO_FLIGHTS *cat_flights,STATS *stats, CATALOGO_INVALID *cat_invalids);
void parse_files_passengers_teste(char *path, STATS*stats, CATALOGO_PASSENGER *cat_passenger, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_INVALID *cat_invalids);
void parse_files_reservations_test(char *path, STATS *stats, CATALOGO_RESERVATIONS *cat_reservations, CATALOGO_USER *cat_users, CATALOGO_INVALID *cat_invalids);


#endif