#ifndef users_h
#define users_h

#include "../inc/catalogo_user.h"
#include "../inc/catalogo_invalids.h"

typedef struct user USER;

USER *create_User(char *line);
void kill_user(void*user);

char *getID(USER *u);
char *getName(USER *u);
char *getEmail(USER *u);
char *getPhoneNumber(USER *u);
char *getBirthDate(USER *u);
char *getSex(USER *u);
char *getPassport(USER *u);
char *getCountryCode(USER *u);
char *getAddress(USER *u);
char *getAccountCreation(USER *u);
char *getPayMethod(USER *u);
char *getAccountStatus(USER *u);
GHashTable *parse_files_users(char *path, GHashTable *invalid_users);

int start_user_process(char *line, CATALOGO_USER *cat_user, CATALOGO_INVALID *cat_invalids);

#endif