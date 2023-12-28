#ifndef catalogo_flights_h
#define catalogo_flights_h

#include <glib.h>
#include "../inc/catalogo_flights.h"

struct flight;
typedef struct flight FLIGHT;

typedef struct cat_flights CATALOGO_FLIGHTS;

/**
 * @brief Função de criação de catalogo.
 * 
 * Esta função cria o catalogo relacionado aos voos
 * 
 * @return Estrutura de catalogo criada
 */
CATALOGO_FLIGHTS *create_Catalogo_flights();

/**
 * @brief getter de Flight.
 * 
 * Esta função é usada para obter um voo.
 * 
 * @param catf apontador para o catalogo dos voos.
 * @param id identificar do voo.
 * 
 * @return apontador para um voo.
 */
FLIGHT *getFlight(CATALOGO_FLIGHTS *catf, char *id);

/**
 * @brief função para adicionar um flight.
 * 
 * Esta função é usada adicionar um flight ao catalogo de voos.
 * 
 * @param catf apontador para o catalogo dos voos.
 * @param f apontador para o voo.
 */
void addFlight (CATALOGO_FLIGHTS *catf, char *id, FLIGHT *f);

/**
 * @brief função para libertar a memoria do catalogo.
 * 
 * Esta função é usada libertar toda a memória do catalogo de voos.
 * 
 * @param catf apontador para o catalogo dos voos  a ser libertado.
 */
void destroy_catalogo_flights(CATALOGO_FLIGHTS *cat_flights);


#endif