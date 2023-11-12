#ifndef parser_h
#define parser_h

GArray *parse_files_passengers(char *path);
GHashTable *parse_files_users(char *path);

void printUserByID(GHashTable *users, char *id);
void printPassanger(GArray *passenger);

#endif