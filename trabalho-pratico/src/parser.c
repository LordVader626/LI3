#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/parser.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/validation.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/hotel_stats.h"
#include "../inc/airport_stats.h"














/*
void printReservationByID(GHashTable *reservations, char *id) {
    RESERVATION *res = g_hash_table_lookup(reservations, id);//Book0000020828

    if (res != NULL) {
        printf("Reservation ID: %s\n", getID_reservation(res));
        printf("Name: %s\n", getHotelName_reservation(res));
        printf("Stars: %d\n", getHotelStars_reservation(res));
        // Adicione mais campos conforme necessário
    } else {
        printf("Reservation with ID %s not found.\n", id);
    }
}

void printUserByID(GHashTable *users, char *id) {
    USER *user = g_hash_table_lookup(users, "DGarcia429");

    if (user != NULL) {
        printf("User ID: %s\n", getID(user));
        printf("Name: %s\n", getName(user));
        printf("Email: %s\n", getEmail(user));
        printf("Phone Number: %s\n", getPhoneNumber(user));
        // Adicione mais campos conforme necessário
    } else {
        printf("User with ID %s not found.\n", id);
    }
}

void printPassanger(GArray *passengers) {
    
    guint i;
    for (i = 0; i < passengers->len; i++) {
        PASSENGER *p = g_array_index(passengers, PASSENGER*, i);
        printf("Element %d:\n", i);
        printf("   Flight ID: %s\n", get_FlightID_passenger(p));
        printf("   User ID: %s\n", getID_passenger(p));
    }
}

void printFlightrByID(GHashTable *flights, char *id) {
    FLIGHT *flight = g_hash_table_lookup(flights, "100");

    if (flight != NULL) {
        printf("Flight ID: %s\n", getID_flight(flight));
        printf("Origin: %s\n", getFlightOrigin(flight));
        printf("Destination: %s\n", getFlightDestination(flight));
        // Adicione mais campos conforme necessário
    } else {
        printf("Flight with ID %s not found. \n", id);
    }
}*/