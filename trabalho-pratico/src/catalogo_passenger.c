#include <stdio.h>
#include <stdlib.h>

#include "../inc/passengers.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/utils.h"


struct cat_passenger {
    GArray *catalogo_passengers;
};

CATALOGO_PASSENGER *create_catalogo_Passenger(){

    CATALOGO_PASSENGER *catp = malloc(sizeof(struct cat_passenger));
    GArray *cat_passenger = g_array_new(FALSE, TRUE, sizeof(PASSENGER *));
    catp->catalogo_passengers = cat_passenger;

    return catp;
}

GArray *get_catalogo_passengers(CATALOGO_PASSENGER *catp)
{ 
	return catp->catalogo_passengers;
}

void addPassenger (CATALOGO_PASSENGER *catp, PASSENGER *p){
    g_array_append_val(catp->catalogo_passengers, p);
}

void destroy_catalogo_passengers(CATALOGO_PASSENGER *cat_passenger){
    freeGArray(cat_passenger->catalogo_passengers);
    free(cat_passenger);
}