#ifndef validation_h
#define validation_h

#include <glib.h>

#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/users.h"

int user_validation(USER *u);
int flight_validation_1phase(FLIGHT *f);
int reservation_validation(RESERVATION *r);
int compareDates(char *data1, char *data2);

#endif