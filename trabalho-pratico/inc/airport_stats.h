#ifndef airport_stats_h
#define airport_stats_h

#include <glib.h>
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/utils.h"

typedef struct airport_stat AIRPORT_STAT;

/**
 * @brief getters.
 * 
 * Estas funções sao utilizadas para obter os dados relactionados
 * as estatísticas de aeroportos.
 * 
 * @param a pointer para as estatisticas do aeroporto.
 */
char *get_airport_stat_id(AIRPORT_STAT *a);
int *get_airport_stat_nPassageirosAno(AIRPORT_STAT *a);
GArray *get_airport_stat_atrasosVoos(AIRPORT_STAT *a);
int get_airport_stat_nVoos(AIRPORT_STAT *a);
GList *get_airport_stat_listaVoos(AIRPORT_STAT *a);


/**
 * @brief Função para criação de estatística.
 * 
 * Esta função é responsavel pela criação de estatística relativa
 * a um voo, com dados como os voos por ano e atrasos nos voos.
 * 
 * @param f pointer para o voo sobre o qual vai ser criada a estatística.
 * @param airport_stats estrutura de dados onde são guardadas as estatísticas
 */
    
void create_airport_stat_flight(FLIGHT *f, STATS *s);
/**
 * @brief Função para criação de estatística.
 * 
 * Esta função é responsavel pela criação de estatística relativa
 * a um passageiro, com dados como os passageiros por ano.
 * 
 * @param p pointer para o passageiro sobre o qual vai ser criada a estatística.
 * @param s catalogo de dados onde são guardadas as estatísticas
 */
void create_airport_stat_passenger(PASSENGER *p, STATS *stats, CATALOGO_FLIGHTS *cat_flights);


/**
 * @brief Função para libertação de memória.
 * 
 * Função responsável por libertar a memoria das estatisticas
 * de aeroportos.
 * 
 * @param airportStat pointer para a estrutura de dados a ser libertada.
 */
void kill_airportStat(void *airportStat);


#endif