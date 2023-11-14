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
#include "../inc/flight_stats.h"
#include "../inc/hotel_stats.h"

GHashTable *parse_files_flights(char *path, STATS *stats){

    // ou usar func em utils
    char *path_flights = malloc(sizeof(char) * 70);
    strcpy(path_flights, path);
    strcat(path_flights, "/flights.csv");


    char *line = NULL;
    size_t len = 0;

    GHashTable *flights = g_hash_table_new(g_str_hash, g_str_equal);

    FILE *file = fopen(path_flights, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
    }

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        FLIGHT *flight = new_Flight(line);

        g_hash_table_insert(flights, getID_flight(flight), flight);
        create_airport_stat_flight(flight, get_airport_stats(stats));
    }
    printf("Flight Validation and Parsing SuccessFull\n");

    fclose(file);
    free(line);
    free(path_flights);

    return flights;
}

GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights) {
    char *path_passengers = malloc(sizeof(char) * 70);
    strcpy(path_passengers, path);
    strcat(path_passengers, "/passengers.csv");

    char *line = NULL;
    size_t len = 0;

    GArray *passengers = g_array_new(FALSE, TRUE, sizeof(PASSENGER *));

    FILE *file = fopen(path_passengers, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return NULL;  // Return NULL to indicate an error
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1) {

        PASSENGER *passenger = create_Passenger(line);
    

            g_array_append_val(passengers, passenger);

            create_user_stat_flights(passenger, get_user_stats(stats), users, flights);
            create_airport_stat_passenger(passenger, get_airport_stats(stats), flights);
    }

    printf("Passenger Validation and Parsing Successfull\n");
    free(line);
    free(path_passengers);
    fclose(file);

    return passengers;
}

GHashTable* parse_files_reservations(char *path, STATS*stats, GHashTable *users) {

    char *line = NULL;
    size_t len = 0;

    GHashTable *reservations = g_hash_table_new(g_str_hash, g_str_equal);
    
    char *path_reservations = malloc(sizeof(char) * 70);
    strcpy(path_reservations, path);
    strcat(path_reservations, "/reservations.csv");

    FILE *file = fopen(path_reservations, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        RESERVATION *reservation = create_Reservation(line);

        g_hash_table_insert(reservations, getID_reservation(reservation), reservation);
        create_user_stat_reservations(reservation, get_user_stats(stats), users);
        create_hotel_stats(reservation, get_hotel_stats(stats));
    }

    
    printf("Reservation validition and Parsing Sucessfull\n");
    free(line);
    free(path_reservations);
    fclose(file);
    return reservations;
}


GHashTable *parse_files_users(char *path){

    char *path_users = malloc(sizeof(char) * 70);
    strcpy(path_users, path);
    strcat(path_users, "/users.csv");

    char *line = NULL;
    size_t len = 0;

    //GHashTable *users = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_user);

    GHashTable *users = g_hash_table_new(g_str_hash, g_str_equal);

    FILE *file = fopen(path_users, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
         // Exit
    }

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
            
        USER *user = create_User(line);

        g_hash_table_insert(users, getID(user), user);

    }
    printf("User Validation and Parsing Sucessfull\n");

    fclose(file);
    free(line);
    free(path_users);
    return users;
}

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