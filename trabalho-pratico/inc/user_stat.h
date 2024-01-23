#ifndef user_stat_h
#define user_stat_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct user_stat USER_STAT;

/**
 * @brief getters.
 *
 * getters para as estatisticas relativas aos users
 *   
 * @param stats catalogo de estatisticas
 * @param data_input path para os dados de input
 * 
 */
char *get_user_stat_username(USER_STAT *s);
int get_user_stat_numReservas(USER_STAT *s);
int get_user_stat_numVoos(USER_STAT *s);
GList* get_user_stat_listaVoos(USER_STAT *s);
GList* get_user_stat_listaReservas(USER_STAT *s);
double get_user_stat_totalGasto(USER_STAT *s);


/**
 * @brief função de criação de stat relativa a um flight.
 *  
 * @param p passageiro 
 * @param cat_users catalogo de users
 * @param cat_flights catalogo de flights
 * 
 */
void create_user_stat_flights(PASSENGER *p, STATS *s, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights);

/**
 * @brief função de criação de stat relativa a um flight.
 *  
 * @param r reserva 
 * @param stats catalogo de stats
 * @param cat_users catalogo de users
 * 
 */
void create_user_stat_reservations(RESERVATION *r, STATS *stats, CATALOGO_USER *cat_users);

/**
 * @brief função de liberação de memoria de um userStat.
 *  
 * @param userStat stat de utilizador
 * 
 */
void kill_userStat(void *userStat);

void print_user_stat(USER_STAT *user_stat);


#endif