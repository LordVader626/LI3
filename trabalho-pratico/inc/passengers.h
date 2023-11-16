#ifndef passengers_h
#define passengers_h

#include <glib.h>

typedef struct passenger PASSENGER;

PASSENGER *create_Passenger(char *line);
char *getID_passenger(PASSENGER *p);
char *get_FlightID_passenger(PASSENGER *p);
void kill_Passenger(void *passenger);
void freeGArray(GArray *garray);

#endif
