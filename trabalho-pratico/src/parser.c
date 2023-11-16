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

GHashTable *parse_files_flights(char *path, STATS *stats, GHashTable *invalid_flights){

    // ou usar func em utils
    char *path_flights = malloc(sizeof(char) * 70);
    char *path_flights_errors = malloc(sizeof(char) * 70);
    strcpy(path_flights, path);
    strcat(path_flights, "/flights.csv");
    strcpy(path_flights_errors, path);
    strcat(path_flights_errors, "/flights_errors.csv");

    char *line = NULL;
    size_t len = 0;

    GHashTable *flights = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_flight);

    FILE *file = fopen(path_flights, "r");
    //FILE *file_errors = fopen(path_flights_errors, "w");

    if (file == NULL /*|| file_errors == NULL*/) {
        printf("Unable to open the file.\n");
    }

    //escreve o cabeçalho no ficheiro dos erros
    //fprintf(file_errors, "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes\n");

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        FLIGHT *flight = new_Flight(line);

        if (flight_validation_1phase(flight) == 0){

            g_hash_table_insert(flights, getID_flight(flight), flight);
            create_airport_stat_flight(flight, get_airport_stats(stats));          
        }
        else {
            char *flightID = getID_flight(flight);

            g_hash_table_insert(invalid_flights, flightID, "INVALIDO");

            char *airline = getAirline(flight);
            char *planeModel = getPlaneModel(flight);
            char *flightOrigin = getFlightOrigin(flight);
            char *flightDestination = getFlightDestination(flight);
            char *notrealDeparture = getScheduleDepartureDate(flight);
            char *notrealArrival = getScheduleArrivalDate(flight);
            char *realDeparture = getRealDepartureDate(flight);
            char *realArrival = getRealArrivalDate(flight);
            char *pilot = getPilot(flight);
            char *copilot = getCopilot(flight);
            char *notes = getNotes(flight);

            //fprintf(file_errors,"%10s;%s;%s;%d;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",flightID, airline, planeModel, getTotalSeats(flight), flightOrigin,
            //        flightDestination, notrealDeparture, notrealArrival, realDeparture, realArrival, pilot, copilot, notes);

            kill_flight(flight);

            free(flightID);
            free(airline);
            free(planeModel);
            free(flightOrigin);
            free(flightDestination);
            free(notrealDeparture);
            free(notrealArrival);
            free(realArrival);
            free(realDeparture);
            free(pilot);
            free(copilot);
            free(notes);
        }
    }
    printf("Flight Validation and Parsing SuccessFull\n");

    fclose(file);
    //fclose(file_errors);
    free(line);
    free(path_flights);
    free(path_flights_errors);

    return flights;
}

GArray *parse_files_passengers(char *path, STATS*stats, GHashTable *users, GHashTable *flights, GHashTable *invalid_users, GHashTable *invalid_flights) {
    char *path_passengers = malloc(sizeof(char) * 70);
    strcpy(path_passengers, path);
    strcat(path_passengers, "/passengers.csv");
    char *path_passengers_errors = malloc(sizeof(char) * 70);
    strcpy(path_passengers_errors,path);
    strcat(path_passengers_errors, "/passengers_errors.csv");

    char *line = NULL;
    size_t len = 0;

    GArray *passengers = g_array_new(FALSE, TRUE, sizeof(PASSENGER *));

    FILE *file = fopen(path_passengers, "r");
    ///FILE *file_errors = fopen(path_passengers_errors, "w");

    //fprintf(file_errors, "flight_id;user_id\n");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return NULL;  // Return NULL to indicate an error
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1) {

        PASSENGER *passenger = create_Passenger(line);
        char *user_id = getID_passenger(passenger);

        char *flight_id = get_FlightID_passenger(passenger);
        if(!(g_hash_table_contains(invalid_users, user_id)) && (!g_hash_table_contains(invalid_flights, flight_id))){
            g_array_append_val(passengers, passenger);

            create_user_stat_flights(passenger, get_user_stats(stats), users, flights);
            //create_airport_stat_passenger(passenger, get_airport_stats(stats), flights);
        }
        else{
            //fprintf(file_errors, "%s;%s\n", get_FlightID_passenger(passenger), getID_passenger(passenger));
            kill_Passenger(passenger);
        }
        free(user_id);
        free(flight_id);
    }
    printf("Passenger Validation and Parsing Successfull\n");
    free(line);
    free(path_passengers);
    free(path_passengers_errors);
    //fclose(file_errors);
    fclose(file);

    return passengers;
}

GHashTable* parse_files_reservations(char *path, STATS*stats, GHashTable *users, GHashTable *invalid_users) {

    char *line = NULL;
    size_t len = 0;

    GHashTable *reservations = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_reservation);
    
    char *path_reservations = malloc(sizeof(char) * 70);
    strcpy(path_reservations, path);
    strcat(path_reservations, "/reservations.csv");
    char *path_reservations_erros = malloc(sizeof(char) * 70);
    strcpy(path_reservations_erros, path);
    strcat(path_reservations_erros, "/reservations_errors.csv");

    FILE *file = fopen(path_reservations, "r");
    //FILE *file_errors = fopen(path_reservations_erros, "w");

    if (file == NULL /*|| file_errors == NULL*/) {
        printf("Unable to open the file.\n");
    }

    //fprintf(file_errors, "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment\n");

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
        RESERVATION *reservation = create_Reservation(line);
        char *userID = getUserID_reservartion(reservation);

        if (!(g_hash_table_contains(invalid_users, userID)) && reservation_validation(reservation) == 0){
            g_hash_table_insert(reservations, getID_reservation(reservation), reservation);
            create_user_stat_reservations(reservation, get_user_stats(stats), users);
            create_hotel_stats(reservation, get_hotel_stats(stats));
        }
        else {
            char *reservationID = getID_reservation(reservation);
            char *userID = getUserID_reservartion(reservation);
            char *hotelID = getHotelID_reservation(reservation);
            char *hotelName = getHotelName_reservation(reservation);
            char *address = getAddress_reservation(reservation);
            char *beginDate = getBeginDate_reservation(reservation);
            char *endDate = getEndDate_reservation(reservation);
            char *incBreakfast = getIncludesBreakfast_reservation(reservation);
            char *roomDetails = getRoomDetails_reservation(reservation);
            char *comment = getComment_reservation(reservation);
        
            //fprintf(file_errors, "%s;%s;%s;%s;%f;%f;%s;%s;%s;%f;%s;%s;%f;%s\n", reservationID, userID, hotelID, hotelName, getHotelStars_reservation(reservation), getCityTax_reservation(reservation), 
            //address, beginDate, endDate, getPricePerNight_reservation(reservation), incBreakfast, roomDetails, getRating_reservation(reservation), comment);

            free(reservationID);
            free(userID);
            free(hotelID);
            free(hotelName);
            free(address);
            free(beginDate);
            free(endDate);
            free(incBreakfast);
            free(roomDetails);
            free(comment);

            kill_reservation(reservation);
        }
        free(userID);
    }
    printf("Reservation validition and Parsing Sucessfull\n");
    free(line);
    free(path_reservations);
    free(path_reservations_erros);
    fclose(file);
    //fclose(file_errors);
    return reservations;
}


GHashTable *parse_files_users(char *path, GHashTable *invalid_users){

    char *path_users = malloc(sizeof(char) * 70);
    strcpy(path_users, path);
    strcat(path_users, "/users.csv");
    char *path_user_erros = malloc(sizeof(char) * 70);
    strcpy(path_user_erros, path);
    strcat(path_user_erros, "/users_errors.csv");

    char *line = NULL;
    size_t len = 0;

    GHashTable *users = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_user);

    FILE *file = fopen(path_users, "r");
    //FILE *file_error = fopen(path_user_erros, "w");

    if (file == NULL /*|| file_error == NULL*/) {
        printf("Unable to open the file.\n");
         // Exit
    }


    //fprintf(file_error, "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status\n");

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
            
        USER *user = create_User(line);

        if (user_validation(user) == 0){
            g_hash_table_insert(users, getID(user), user);
        }
        else {
            char *idUser = getID(user);
            char *Name = getName(user);
            char *email = getEmail(user);
            char *phoneNumber = getPhoneNumber(user);
            char *birthDate = getBirthDate(user);
            char *sex = getSex(user);
            char *passport = getPassport(user);
            char *countryCode = getCountryCode(user);
            char *address = getAddress(user);
            char *accountCreation = getAccountCreation(user);
            char *paymethod = getPayMethod(user);
            char *accountStatus = getAccountStatus(user); 

            //g_hash_table_insert(invalid_users, getID(user), "invalid");
            //fprintf(file_error,"%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", idUser, Name, email, phoneNumber, birthDate, sex, passport, countryCode, address, accountCreation, paymethod, accountStatus);

            kill_user(user);

            free(idUser);
            free(Name);
            free(email);
            free(phoneNumber);
            free(birthDate);
            free(sex);
            free(passport);
            free(countryCode);
            free(address);
            free(accountCreation);
            free(paymethod);
            free(accountStatus);
        }
    }
    printf("User Validation and Parsing Sucessfull\n");

    fclose(file);
    //fclose(file_error); 
    free(line);
    free(path_users);
    free(path_user_erros);
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