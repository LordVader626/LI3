#ifndef hotel_stats_h
#define hotel_stats_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct h_stat HOTEL_STAT;

char *get_hotel_stat_id(HOTEL_STAT *h);
double get_hotel_stat_nReservas(HOTEL_STAT *h);
double get_hotel_stat_somaRatings(HOTEL_STAT *h);
GList *get_hotel_stat_reservasHotel(HOTEL_STAT *h);
double get_hotel_stat_avgscore(HOTEL_STAT *h);


void create_hotel_stats(RESERVATION *r, GHashTable *hotel_stats);

#endif