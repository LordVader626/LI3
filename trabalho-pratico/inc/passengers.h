#ifndef passengers_h
#define passengers_h
#include"../inc/stats.h"
#include <glib.h>

#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_user.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"

typedef struct passenger PASSENGER;

/**
 * @brief função para criação de um passageiro
 * 
 * @param line string com dados para criação de passageiro
 * 
 * @return apontador para um passenger
 */
PASSENGER *create_Passenger(char *line);

/**
 * @brief getters
 * 
 * @param p passenger
 * 
 * @return detalhe pretendido sobre passageiro
 */
char *getID_passenger(PASSENGER *p);
char *get_FlightID_passenger(PASSENGER *p);


/**
 * @brief função para libertação de memmoria de um passageiro
 * 
 * @param passenger passageiro 
 */
void kill_Passenger(void *passenger);

/**
 * @brief função que para libertar a estrutura de passageiros
 */
void freeGArray(GArray *garray);

/**
 * @brief função que inicia o processo de um passenger.
 *
 * Função que trata do processo de um passageiro para criação, inserção, criação de estatisticas
 *  
 * @param line contem todos os detalhes de um passageiro
 * @param cat_passengers catalogo de passengers
 * @param cat_invalids catalogo de dados invalidos
 * @param cat_flights catalogo de flights
 * @param cat_users catalogo de users
 * @param stats catalogo das estatisticas
 * 
 * @return se o processo foi um sucesaso
 */
int start_passenger_process(char *line,CATALOGO_PASSENGER *cat_passenger, CATALOGO_INVALID *cat_invalids, STATS *stats, CATALOGO_FLIGHTS *cat_flights, CATALOGO_USER *cat_users);

#endif
