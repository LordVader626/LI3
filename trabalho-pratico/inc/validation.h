#ifndef validation_h
#define validation_h

#include <glib.h>

#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/users.h"

int user_validation(USER *u);
void validade_files(GHashTable *users);//, GHashTable *flights, GHashTable *reservations, GHashTable *flight_stats);

#endif