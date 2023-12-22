#ifndef catalogo_invalids_h
#define catalogo_invalids_h

#include <glib.h>

typedef struct cat_invalids CATALOGO_INVALID;
CATALOGO_INVALID *create_Catalogo_invalids();
GHashTable *get_catalogo_invalid_users(CATALOGO_INVALID *cat_inv);
GHashTable *get_catalogo_invalid_flights(CATALOGO_INVALID *cat_inv);
void addInvalidUser(CATALOGO_INVALID *cat_inv, char *id, char *s);
void addInvalidFlight(CATALOGO_INVALID *cat_inv, char *id, char *s);
void destroy_catalogo_invalids(CATALOGO_INVALID *cat_invalids);
int cointains_invalid_user(CATALOGO_INVALID *cat_invalid, char *userID);
int cointains_invalid_flight(CATALOGO_INVALID *cat_invalid, char *flightID);

#endif