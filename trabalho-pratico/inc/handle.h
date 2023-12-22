#ifndef handle_h
#define handle_h
#include "../inc/stats.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_user.h"

void handle(char *data_input, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers, CATALOGO_RESERVATIONS *cat_reservations, STATS *stats, CATALOGO_INVALID *cat_invalids);

#endif