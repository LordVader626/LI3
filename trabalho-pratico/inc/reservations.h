#ifndef reservations_h
#define reservations_h
#include"../inc/stats.h"
typedef struct reservation RESERVATION;

RESERVATION *create_Reservation(char *line);
void kill_reservation(void *reservation);

char *getID_reservation(RESERVATION *r);
char *getUserID_reservartion(RESERVATION *r);
char *getHotelID_reservation(RESERVATION *r);
char *getHotelName_reservation(RESERVATION *r);
double getHotelStars_reservation(RESERVATION *r);
double getCityTax_reservation(RESERVATION *r);
char *getAddress_reservation(RESERVATION *r);
char *getBeginDate_reservation(RESERVATION *r);
char *getEndDate_reservation(RESERVATION *r);
double getPricePerNight_reservation(RESERVATION *r);
char *getIncludesBreakfast_reservation(RESERVATION *r);
char *getRoomDetails_reservation(RESERVATION *r);
double getRating_reservation(RESERVATION *r);
char *getComment_reservation(RESERVATION *r);
GHashTable* parse_files_reservations(char *path, STATS*stats, GHashTable *users, GHashTable *invalid_users) ;

#endif