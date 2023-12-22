#include <stdio.h>
#include <stdlib.h>

#include "../inc/catalogo_invalids.h"
#include "../inc/utils.h"

struct cat_invalids {
    GHashTable *catalogo_invalid_users;
    GHashTable *catalogo_invalid_flights;
};

CATALOGO_INVALID *create_Catalogo_invalids(){

    CATALOGO_INVALID *cat_inv = malloc(sizeof(struct cat_invalids));
    GHashTable *catalogo_inv_users = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable *catalogo_inv_flights = g_hash_table_new(g_str_hash, g_str_equal);

    cat_inv->catalogo_invalid_users = catalogo_inv_users;
    cat_inv->catalogo_invalid_flights = catalogo_inv_flights;

    return cat_inv;
}

GHashTable *get_catalogo_invalid_users(CATALOGO_INVALID *cat_inv)
{ 
	return cat_inv->catalogo_invalid_users;
}

GHashTable *get_catalogo_invalid_flights(CATALOGO_INVALID *cat_inv)
{ 
	return cat_inv->catalogo_invalid_flights;
}

void addInvalidUser(CATALOGO_INVALID *cat_inv, char *id, char *s){
    g_hash_table_insert(cat_inv->catalogo_invalid_users,id,s);
}

void addInvalidFlight(CATALOGO_INVALID *cat_inv, char *id, char *s){
    g_hash_table_replace(cat_inv->catalogo_invalid_flights, id, s);
}

int cointains_invalid_user(CATALOGO_INVALID *cat_invalid, char *userID){
    return g_hash_table_contains(cat_invalid->catalogo_invalid_users, userID);
}

int cointains_invalid_flight(CATALOGO_INVALID *cat_invalid, char *flightID){
    return g_hash_table_contains(cat_invalid->catalogo_invalid_flights, flightID);

}

void destroy_catalogo_invalids(CATALOGO_INVALID *cat_invalids){
   
    g_hash_table_foreach_remove(cat_invalids->catalogo_invalid_users, remove_keys, NULL);
    g_hash_table_destroy(cat_invalids->catalogo_invalid_users);
        
    g_hash_table_foreach_remove(cat_invalids->catalogo_invalid_flights, remove_keys, NULL);
    g_hash_table_destroy(cat_invalids->catalogo_invalid_flights);

    free(cat_invalids);
}