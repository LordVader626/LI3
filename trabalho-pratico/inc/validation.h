#ifndef validation_h
#define validation_h

#include <glib.h>

#include "../inc/flights.h"
#include "../inc/reservations.h"
#include "../inc/users.h"


/**
 * @brief função que realiza a validação de um utilizador
 * 
 * @param u utilizador a ser verificado
 * 
 * @return valido ou invalido
*/
int user_validation(USER *u);

/**
 * @brief função que realiza a validação de um flight
 * 
 * @param f flight a ser verificado
 * 
 * @return valido ou invalido
*/
int flight_validation_1phase(FLIGHT *f);

/**
 * @brief função que realiza a validação de uma reserva
 * 
 * @param r reserva a ser verificado
 * 
 * @return valido ou invalido
*/
int reservation_validation(RESERVATION *r);
//int compareDates(char *data1, char *data2);

#endif