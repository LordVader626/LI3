#ifndef catalogo_invalids_h
#define catalogo_invalids_h

#include <glib.h>

typedef struct cat_invalids CATALOGO_INVALID;

/**
 * @brief Função de criação de catalogo.
 * 
 * Esta função cria o catalogo relacionado aos dados invalidos
 * 
 * @return pointer para a estrutura de catalogo criada
 */
CATALOGO_INVALID *create_Catalogo_invalids();

/**
 * @brief Funções para obter os dados invalidos.
 * 
 * Estas funções são utilizadas para obter os dados
 * invalidos de utilizadores e voos
 * 
 * @param cat_inv catalogo de dados inválidos
 * 
 * @return apontador para a estrutura de que contem os dados
 */
GHashTable *get_catalogo_invalid_users(CATALOGO_INVALID *cat_inv);
GHashTable *get_catalogo_invalid_flights(CATALOGO_INVALID *cat_inv);


/**
 * @brief Funções para adicionar dados inválidos.
 * 
 * Estas funções são utilizadas para adicionar os dados
 * invalidos de utilizadores e voos ao catalogo
 * 
 * @param cat_inv catalogo de dados inválidos
 * @param id id do voo/flight invalido
 * @param s string a informar que user é inválido
 */
void addInvalidUser(CATALOGO_INVALID *cat_inv, char *id, char *s);
void addInvalidFlight(CATALOGO_INVALID *cat_inv, char *id, char *s);

/**
 * @brief Função para libertação de memória.
 * 
 * Esta função é utilizada para libertar a memória relacionada
 * ao catalogo de dados inválido
 * 
 * @param cat_inv catalogo de dados inválidos
 */

void destroy_catalogo_invalids(CATALOGO_INVALID *cat_invalids);

/**
 * @brief Funções para verificar se um "dado" está na lista.
 * 
 * Estas funções são utilizadas para verificar se um user/flight
 * está na estrutura de dados inválido
 * 
 * @param cat_inv catalogo de dados inválidos
 * @param id id do voo/flight invalido
 */
int cointains_invalid_user(CATALOGO_INVALID *cat_invalid, char *userID);
int cointains_invalid_flight(CATALOGO_INVALID *cat_invalid, char *flightID);

#endif