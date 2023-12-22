#include <stdio.h>
#include <stdlib.h>

#include "../inc/flights.h"
#include "../inc/catalogo_flights.h"


struct cat_flights {
    GHashTable *catalogo_flights;
};

CATALOGO_FLIGHTS *create_Catalogo_flights(){

    CATALOGO_FLIGHTS *catf = malloc(sizeof(struct cat_flights));
    GHashTable *cat_flights = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_flight);
    catf->catalogo_flights = cat_flights;

    return catf;
}

GHashTable *get_Catalogo_flights(CATALOGO_FLIGHTS * catf)
{ 
	return catf->catalogo_flights;
}

FLIGHT * getFlight(CATALOGO_FLIGHTS *catf, char *id){

    return (FLIGHT*) g_hash_table_lookup(catf->catalogo_flights,id);
}

void addFlight (CATALOGO_FLIGHTS *catf, char *id, FLIGHT *f){
    g_hash_table_insert(catf->catalogo_flights, id ,f);
}

void destroy_catalogo_flights(CATALOGO_FLIGHTS *cat_flights){
    g_hash_table_destroy(cat_flights->catalogo_flights);
    free(cat_flights);
}