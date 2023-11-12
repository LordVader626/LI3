#ifndef passengers_h
#define passengers_h

typedef struct passenger PASSENGER;

PASSENGER *create_Passenger(char *line);
char *getID_passenger(PASSENGER *p);
int get_FlightID_passenger(PASSENGER *p);

#endif
