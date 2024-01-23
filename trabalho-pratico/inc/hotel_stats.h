#ifndef hotel_stats_h
#define hotel_stats_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct hotel_stat HOTEL_STAT;

/**
 * @brief getters de hotel stats
 * 
 * @param h estatisticas de um hotel
 * 
 * @return detalhe das estatisticas pretendido
 */
char *get_hotel_stat_id(HOTEL_STAT *h);
double get_hotel_stat_nReservas(HOTEL_STAT *h);
double get_hotel_stat_somaRatings(HOTEL_STAT *h);
double get_hotel_stat_avgscore(HOTEL_STAT *h);


/**
 * @brief getter da lista de reservas de um hotel
 * 
 * @param h estatisticas de um hotel
 * 
 * @return copia da glist
 */
GList *get_hotel_stat_reservasHotel(HOTEL_STAT *h);

/**
 * @brief funçao de criaçao de uma estatistica de hotel
 * 
 * @param r apontador para uma reserva
 * @param stats catalogo de stats
 */
void create_hotel_stats(RESERVATION *r, STATS *stats);

/**
 * @brief funcao para libertar a memoria de um hotel_stat
 * 
 * @param hotelStat estatistica de um hotel
 */
void kill_hotelStat(void *hotelStat);

#endif