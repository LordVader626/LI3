#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "../inc/reservations.h"
#include "../inc/catalogo_reservations.h"


struct cat_reservations {
    GHashTable *catalogo_reservations;
};

CATALOGO_RESERVATIONS *create_Catalogo_Reservations(){

    CATALOGO_RESERVATIONS *catr = malloc(sizeof(CATALOGO_RESERVATIONS*));
    GHashTable *cat_reservations = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_reservation);
    catr->catalogo_reservations = cat_reservations;

    return catr;
}

GHashTable *get_Catalogo_reservations(CATALOGO_RESERVATIONS * catr)
{ 
	return catr->catalogo_reservations;
}

RESERVATION * getReservation(CATALOGO_RESERVATIONS *catr, char *id){

    return (RESERVATION*) g_hash_table_lookup(catr->catalogo_reservations,id);
}

void addReservations (CATALOGO_RESERVATIONS *catr, char *id, RESERVATION *r){
    g_hash_table_insert(catr->catalogo_reservations,id,r);
}

void destroy_catalogo_reservations(CATALOGO_RESERVATIONS *cat_reservations){
    g_hash_table_destroy(cat_reservations->catalogo_reservations);
    free(cat_reservations);
}