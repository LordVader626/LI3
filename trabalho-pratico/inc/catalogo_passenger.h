#ifndef catalogo_passenger_h
#define catalogo_passenger_h

#include <glib.h>

struct passenger;
typedef struct passenger PASSENGER;

typedef struct cat_passenger CATALOGO_PASSENGER;
CATALOGO_PASSENGER *create_catalogo_Passenger();
GArray *get_catalogo_passengers(CATALOGO_PASSENGER *catp);
PASSENGER * getPassenger(CATALOGO_PASSENGER *catp, char *id);
void addPassenger(CATALOGO_PASSENGER *cat_passenger, PASSENGER *p);
void destroy_catalogo_passengers(CATALOGO_PASSENGER *cat_passenger);

#endif