#ifndef catalogo_flights_h
#define catalogo_flights_h

#include <glib.h>
#include "../inc/catalogo_flights.h"

struct flight;
typedef struct flight FLIGHT;

typedef struct cat_flights CATALOGO_FLIGHTS;
CATALOGO_FLIGHTS *create_Catalogo_flights();
FLIGHT *getFlight(CATALOGO_FLIGHTS *catf, char *id);
void addFlight (CATALOGO_FLIGHTS *catf, char *id, FLIGHT *f);
void destroy_catalogo_flights(CATALOGO_FLIGHTS *cat_flights);


#endif