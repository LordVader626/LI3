#ifndef catalogo_reservations_h
#define catalogo_reservations_h

#include <glib.h>

struct reservation;
typedef struct reservation RESERVATION;

typedef struct cat_reservations CATALOGO_RESERVATIONS;
CATALOGO_RESERVATIONS *create_Catalogo_Reservations();
RESERVATION * getReservation(CATALOGO_RESERVATIONS *catr, char *id);
GHashTable *get_Catalogo_reservations(CATALOGO_RESERVATIONS * catr);
void addReservations(CATALOGO_RESERVATIONS *catr, char *id, RESERVATION *f);
void destroy_catalogo_reservations(CATALOGO_RESERVATIONS *cat_reservations);

#endif