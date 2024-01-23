#ifndef flights_h
#define flights_h

#include "../inc/stats.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"

typedef struct flight FLIGHT;

/**
 * @brief função para criar um flight.
 * 
 * @param line contem todos os detalhes de um flight
 * 
 * @return pointer para o flight criado
 */
FLIGHT *new_Flight(char *line);

/**
 * @brief função para libertar o espaço de um flight.
 * 
 * @param flight apontador para um voo 
 */
void kill_flight(void *flight);

/**
 * @brief getters.
 * 
 * @param f apontador para o voo
 * 
 * @return dado da estrutura pretendido
 */
char *getID_flight(FLIGHT *f);
char *getAirline(FLIGHT *f);
char *getPlaneModel(FLIGHT *f);
int getTotalSeats(FLIGHT *f);
char *getFlightOrigin(FLIGHT *f);
char *getFlightDestination(FLIGHT *f);
char *getScheduleDepartureDate(FLIGHT *f);
char *getScheduleArrivalDate(FLIGHT *f);
char *getRealDepartureDate(FLIGHT *f);
char *getRealArrivalDate(FLIGHT *f);
char *getPilot(FLIGHT *f);
char *getCopilot(FLIGHT *f);
char *getNotes(FLIGHT *f);


/**
 * @brief função que inicia o processo de um flight.
 *
 * Função que trata do processo de um flight para criação, inserção, criação de estatisticas
 *  
 * @param line contem todos os detalhes de um flight
 * @param cat_flights catalogo de voos
 * @param cat_invalids catalogo de dados invalidos
 * @param stats catalogo das estatisticas
 * 
 * @return se o processo foi um sucesso
 */
int start_flight_process(char *line, CATALOGO_FLIGHTS *cat_flights, CATALOGO_INVALID *cat_invalids, STATS *stats);

#endif