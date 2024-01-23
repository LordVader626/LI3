#ifndef reservations_h
#define reservations_h

#include "../inc/stats.h"
#include "../inc/catalogo_user.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_invalids.h"

typedef struct reservation RESERVATION;

/**
 * @brief função para criação de uma reservation
 * 
 * @param line detalhes de um passageiro
 * 
 * @return apontador para uma reserva
 */
RESERVATION *create_Reservation(char *line);
/**
 * @brief função para libertação de memmoria de uma reserva
 * 
 * @param reservation reserva 
 */
void kill_reservation(void *reservation);

/**
 * @brief getters
 * 
 * @param reservation apontador para uma reserva
 * 
 * @return detalhe sobre reserva pretendido 
 */
char *getID_reservation(RESERVATION *r);
char *getUserID_reservartion(RESERVATION *r);
char *getHotelID_reservation(RESERVATION *r);
char *getHotelName_reservation(RESERVATION *r);
double getHotelStars_reservation(RESERVATION *r);
double getCityTax_reservation(RESERVATION *r);
char *getAddress_reservation(RESERVATION *r);
char *getBeginDate_reservation(RESERVATION *r);
char *getEndDate_reservation(RESERVATION *r);
double getPricePerNight_reservation(RESERVATION *r);
char *getIncludesBreakfast_reservation(RESERVATION *r);
char *getRoomDetails_reservation(RESERVATION *r);
double getRating_reservation(RESERVATION *r);
char *getComment_reservation(RESERVATION *r);

/**
 * @brief função que inicia o processo de uma reservation.
 *
 * Função que trata do processo de uma reservation para criação, inserção, criação de estatisticas
 *  
 * @param line contem todos os detalhes de uma reservation
 * @param cat_reservations catalogo de reservations
 * @param cat_invalids catalogo de dados invalidos
 * @param cat_users catalogo de users
 * @param stats catalogo das estatisticas
 * 
 * @return se o processo foi um sucesaso
 */
int start_reservation_process(char *line, CATALOGO_USER *cat_users, CATALOGO_RESERVATIONS *cat_reservas, STATS *stats, CATALOGO_INVALID *cat_invalids);

#endif