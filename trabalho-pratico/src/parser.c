#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/parser.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"


GArray *parse_files_passengers(char *path) {
    char *path_passengers = malloc(sizeof(char) * 70);
    strcpy(path_passengers, path);
    strcat(path_passengers, "/passengers.csv");

    char *line = NULL;
    size_t len = 0;

    GArray *passengers = g_array_new(FALSE, TRUE, sizeof(PASSENGER *));

    FILE *file = fopen(path_passengers, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return NULL; 
    }

    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1) {

        PASSENGER *passenger = create_Passenger(line);

        g_array_append_val(passengers, passenger);
    }

    free(line);
    free(path_passengers);
    fclose(file);

    return passengers;
}

GHashTable *parse_files_users(char *path){

    char *path_users = malloc(sizeof(char) * 70);
    strcpy(path_users, path);
    strcat(path_users, "/users.csv");

    char *line = NULL;
    size_t len = 0;

    GHashTable *users = g_hash_table_new(g_str_hash, g_str_equal);

    FILE *file = fopen(path_users, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
         // Exit with an error code
    }

    //skip ao cabeçalho
    getline(&line, &len, file);

    while ((getline(&line, &len, file)) != -1){
            
        USER *user = create_User(line);
        g_hash_table_insert(users, getID(user), user);
    }

    fclose(file); 
    free(line);
    free(path_users);

    return users;
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
        printf("   Flight ID: %d\n", get_FlightID_passenger(p));
        printf("   User ID: %s\n", getID_passenger(p));
    }
}