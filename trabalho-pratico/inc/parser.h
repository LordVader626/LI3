#ifndef parser_h
#define parser_h


GHashTable *parse_files_flights(char *path);
GArray *parse_files_passengers(char *path);
GHashTable* parse_files_reservations(char *path);
GHashTable *parse_files_users(char *path);

void printUserByID(GHashTable *users, char *id);
void printFlightrByID(GHashTable *flight, char *id);
void printPassanger(GArray *passenger);
void printReservationByID(GHashTable *reservations, char *id);

#endif