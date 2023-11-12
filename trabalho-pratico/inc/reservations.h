#ifndef reservations_h
#define reservations_h

typedef struct reservation RESERVATION;

RESERVATION *create_Reservation(char *line);
char *getID_reservation(RESERVATION *r);
char *getUserID_reservartion(RESERVATION *r);
char *getHotelID_reservation(RESERVATION *r);
char *getHotelName_reservation(RESERVATION *r);
int getHotelStars_reservation(RESERVATION *r);
int getCityTax_reservation(RESERVATION *r);
char *getAddress_reservation(RESERVATION *r);
char *getBeginDate_reservation(RESERVATION *r);
char *getEndDate_reservation(RESERVATION *r);
int getPricePerNight_reservation(RESERVATION *r);
char *getIncludesBreakfast_reservation(RESERVATION *r);
char *getRoomDetails_reservation(RESERVATION *r);
int getRating_reservation(RESERVATION *r);
char *getComment_reservation(RESERVATION *r);

#endif