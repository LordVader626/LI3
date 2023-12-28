#ifndef catalogo_reservations_h
#define catalogo_reservations_h

#include <glib.h>

struct reservation;
typedef struct reservation RESERVATION;

typedef struct cat_reservations CATALOGO_RESERVATIONS;

/**
 * @brief Função de criação de catalogo.
 * 
 * Esta função cria o catalogo relacionado as reservas
 * 
 * @return pointer para a estrutura de catalogo criada
 */
CATALOGO_RESERVATIONS *create_Catalogo_Reservations();

/**
 * @brief getter de Reserva.
 * 
 * Esta função é usada para obter uma reserva.
 * 
 * @param catr apontador para o catalogo das reservas.
 * @param id identificar da reserva.
 * 
 * @return apontador para uma reserva.
 */
RESERVATION * getReservation(CATALOGO_RESERVATIONS *catr, char *id);

/**
 * @brief getter de catalogo.
 * 
 * Esta função é usada para obter o catalogo de reservas.
 * 
 * @param catr apontador para o catalogo das reservas.
 * 
 * @return apontador para a hashtable do catalogo.
 */
GHashTable *get_Catalogo_reservations(CATALOGO_RESERVATIONS * catr);

/**
 * @brief função para adicionar uma reserva.
 * 
 * Esta função é usada adicionar uma reserva ao seu catalogo.
 * 
 * @param catr apontador para o catalogo de reservas.
 * @param id id da reserva.
 * @param f apontador para a reserva.
 */
void addReservations(CATALOGO_RESERVATIONS *catr, char *id, RESERVATION *f);

/**
 * @brief função para libertar a memoria do catalogo.
 * 
 * Esta função é usada libertar toda a memória do catalogo de revervas.
 * 
 * @param cat_passenger apontador para o catalogo das reservas a ser libertado.
 */
void destroy_catalogo_reservations(CATALOGO_RESERVATIONS *cat_reservations);

#endif