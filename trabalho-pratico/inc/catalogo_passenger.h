#ifndef catalogo_passenger_h
#define catalogo_passenger_h

#include <glib.h>

struct passenger;
typedef struct passenger PASSENGER;

typedef struct cat_passenger CATALOGO_PASSENGER;

/**
 * @brief Função de criação de catalogo.
 * 
 * Esta função cria o catalogo relacionado aos passageiros
 * 
 * @return pointer para a estrutura de catalogo criada
 */
CATALOGO_PASSENGER *create_catalogo_Passenger();

/**
 * @brief getter de catalogo.
 * 
 * Esta função é usada para obter o catalogo de passageiros.
 * 
 * @param catp apontador para o catalogo dos passageiros.
 * 
 * @return apontador para o garray do catalogo.
 */
GArray *get_catalogo_passengers(CATALOGO_PASSENGER *catp);

/**
 * @brief getter de Passageiro.
 * 
 * Esta função é usada para obter um voo.
 * 
 * @param catp apontador para o catalogo dos passageiros.
 * 
 * @return apontador para um voo.
 */
PASSENGER * getPassenger(CATALOGO_PASSENGER *catp, char *id);

/**
 * @brief função para adicionar um passageiro.
 * 
 * Esta função é usada adicionar um passageiro ao catalogo de passageiros.
 * 
 * @param cat_passenger apontador para o catalogo dos passageiros.
 * @param p apontador para o passageiro.
 */
void addPassenger(CATALOGO_PASSENGER *cat_passenger, PASSENGER *p);

/**
 * @brief função para libertar a memoria do catalogo.
 * 
 * Esta função é usada libertar toda a memória do catalogo de passageiros.
 * 
 * @param cat_passenger apontador para o catalogo dos voos  a ser libertado.
 */
void destroy_catalogo_passengers(CATALOGO_PASSENGER *cat_passenger);

#endif