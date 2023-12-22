#ifndef catalogo_user_h
#define catalogo_user_h

#include <glib.h>

struct user;
typedef struct user USER;

typedef struct cat_user CATALOGO_USER;
CATALOGO_USER *create_Catalogo_User();
GHashTable *get_Catalogo_User(CATALOGO_USER * catu);
USER * getUser(CATALOGO_USER *catu, char *id);
void addUser(CATALOGO_USER *catu, char *id, USER *u);
void destroy_catalogo_users(CATALOGO_USER *cat_users);
int cointains_user(CATALOGO_USER *cat_users, char *userID);

#endif