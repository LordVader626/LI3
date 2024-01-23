#ifndef handle_h
#define handle_h
#include "../inc/stats.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_user.h"


/**
 * @brief função para handle de um input
 * 
 * Esta função lê o ficheiro de input e cria os ficheiros de outputs
 * 
 * @param data_input path para o input
 * @param cat_users catalogo de utilizadores
 * @param cat_flights catalogo de voos
 * @param cat_passangers catalogo de passageiros
 * @param cat_reservations catalogo de reservations
 * @param stats catalogo das stats
 * @param cat_invalids catalogo de dados invalidos
 * @param mode modo de execução teste/normal
 * 
 */
void handle(char *data_input, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers, CATALOGO_RESERVATIONS *cat_reservations, STATS *stats, CATALOGO_INVALID *cat_invalids, int mode);

/**
 * @brief função para handle de um input
 * 
 * Esta função lê o ficheiro de input e cria os ficheiros de outputs
 * 
 * @param query numero da query
 * @param line dados da queru
 * @param data_input path para o input
 * @param cat_users catalogo de utilizadores
 * @param cat_flights catalogo de voos
 * @param cat_passangers catalogo de passageiros
 * @param cat_reservations catalogo de reservations
 * @param stats catalogo das stats
 * @param cat_invalids catalogo de dados invalidos
 * @param mode modo de execução teste/normal
 * @param nQuery numero do output
 * 
 */
void handleQuery(char *query, char *line, char *path, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers, CATALOGO_RESERVATIONS *cat_reservations, STATS *stats, CATALOGO_INVALID *cat_invalids, int mode, int nQuery);

#endif