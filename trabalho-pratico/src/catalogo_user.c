#include <stdio.h>
#include <stdlib.h>


#include "../inc/catalogo_user.h"
#include "../inc/users.h"


struct cat_user {
    GHashTable *catalogo_user;
};

CATALOGO_USER *create_Catalogo_User(){

    CATALOGO_USER *catu = malloc(sizeof(struct cat_user));
    GHashTable *catalogo = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, kill_user);
    catu->catalogo_user = catalogo;

    return catu;
}

GHashTable *get_Catalogo_User(CATALOGO_USER *catu)
{ 
	return catu->catalogo_user;
}

USER *getUser(CATALOGO_USER *catu, char *id){

    return (USER*) g_hash_table_lookup(catu->catalogo_user,id);
}

void addUser(CATALOGO_USER *catu, char *id, USER *u){
    g_hash_table_insert(catu->catalogo_user,id,u);
}

void destroy_catalogo_users(CATALOGO_USER *cat_users){
    g_hash_table_destroy(cat_users->catalogo_user);
    free(cat_users);
}

int cointains_user(CATALOGO_USER *cat_users, char *userID){
    return g_hash_table_contains(cat_users->catalogo_user, userID);
}