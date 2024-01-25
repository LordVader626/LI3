#ifndef queries_h
#define queries_h

#include "../inc/stats.h"
#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_user.h"

void query1(CATALOGO_RESERVATIONS *cat_reservations, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers ,char* linha, int f,char *path, STATS *stats);
void query2(CATALOGO_RESERVATIONS *cat_reservations, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers ,char* linha, int f,char *path, STATS *stats, CATALOGO_INVALID *cat_invalids);
void query3(CATALOGO_RESERVATIONS *cat_reservations,char* linha, int f,char *path, STATS *stats);
void query4(char *lina, int f, char *path, STATS *stats);
void query5(char *linha, int f, char *path, STATS *stats);
void query6(char *linha, int f, char *path, STATS *stats);
void query7(char *linha, int f, char *path, STATS *stats);
void query8(char *linha, int f, char *path, STATS *stats, CATALOGO_RESERVATIONS *cat_reservations);
void query9(CATALOGO_USER *cat_users,char* linha, int f,char *path);



#endif