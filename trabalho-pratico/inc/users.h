#ifndef users_h
#define users_h

typedef struct user USER;

USER *create_User(char *line);
void kill_user();

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


#endif