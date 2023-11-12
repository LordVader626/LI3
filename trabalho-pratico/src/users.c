#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "../inc/users.h"

/*
* Struct user
* Guarda os dados dos utilizadores
*/
struct user{
    char *id;
    char *name;
    char *email;
    char *phone_number;
    char *birth_date; // aaaaa/MM/dd com horas hh:mm:ss
    char *sex;
    char *passport;
    char *country_code;
    char *address;
    char *account_creation;
    char *pay_method;
    char *account_status;
};

USER *create_User(char *line){

    USER *u = malloc(sizeof(USER));

    u->id = strdup(strsep(&line, ";"));
    u->name = strdup(strsep(&line, ";"));
    u->email = strdup(strsep(&line, ";"));
    u->phone_number = strdup(strsep(&line, ";"));
    u->birth_date = strdup(strsep(&line, ";"));
    u->sex = strdup(strsep(&line, ";"));
    u->passport = strdup(strsep(&line, ";"));
    u->country_code = strdup(strsep(&line, ";"));
    u->address = strdup(strsep(&line, ";"));
    u->account_creation = strdup(strsep(&line, ";"));
    u->pay_method = strdup(strsep(&line, ";"));
    u->account_status = strdup(strsep(&line, "\n"));
    
    return u;
}

// vai apagar utilizador se tiver campo invalido
/*void kill_user(){
    USER *u;

    free(u->id);
    free(u->name);
    free(u->email);
    free(u->phone_number);
    free(u->birth_date);
    free(u->sex);
    free(u->passport);
    free(u->country_code);
    free(u->address);
    free(u->account_creation);
    free(u->pay_method);
    free(u->account_status);
    free(u);
}*/

char *getID(USER *u){
    return strdup(u->id);
}

char *getName(USER *u){
    return strdup(u->name);
}

char *getEmail(USER *u){
    return strdup(u->email);
}

char *getPhoneNumber(USER *u){
    return strdup(u->phone_number);
}

char *getBirthDate(USER *u){
    return strdup(u->birth_date);
}

char *getSex(USER *u){
    return strdup(u->sex);
}

char *getPassport(USER *u){
    return strdup(u->passport);
}

char *getCountryCode(USER *u){
    return strdup(u->country_code);
}

char *getAddress(USER *u){
    return strdup(u->address);
}

char *getAccountCreation(USER *u){
    return strdup(u->account_creation);
}

char *getPayMethod(USER *u){
    return strdup(u->pay_method);
}

char *getAccountStatus(USER *u){
    return strdup(u->account_status);
}