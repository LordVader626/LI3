#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/reservations.h"

struct reservation{
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    double hotel_stars;
    double city_tax;
    char *adress;
    char *begin_date;
    char *end_date;
    double price_per_night;
    char *includes_breakfast; //usar bool lib ou 1 = TRUE && 0 = FALSE
    char *room_details;
    double rating;
    char *comment;
};

RESERVATION*create_Reservation(char *line){

    RESERVATION *r = malloc(sizeof(RESERVATION));

    r->id = strdup(strsep(&line, ";"));
    r->user_id = strdup(strsep(&line, ";"));
    r->hotel_id = strdup(strsep(&line, ";"));
    r->hotel_name = strdup(strsep(&line, ";"));
    r->hotel_stars = strtod(strsep(&line, ";"), NULL);
    r->city_tax = strtod(strsep(&line, ";"), NULL);
    r->adress = strdup(strsep(&line, ";"));
    r->begin_date = strdup(strsep(&line, ";"));
    r->end_date = strdup(strsep(&line, ";"));
    r->price_per_night = strtod(strsep(&line, ";"), NULL);
    r->includes_breakfast = strdup(strsep(&line, ";"));
    r->room_details = strdup(strsep(&line, ";"));
    r->rating = strtod(strsep(&line, ";"), NULL);
    r->comment = strdup(strsep(&line, "\n"));
    return r;
}

void kill_reservation(RESERVATION *r){
    free(r->id);
    free(r->user_id);
    free(r->hotel_id);
    free(r->hotel_name);
    free(r->adress);
    free(r->begin_date);
    free(r->end_date);
    free(r->includes_breakfast);
    free(r->room_details);
    free(r->comment);
    free(r);
}

char *getID_reservation(RESERVATION *r){
    return strdup(r->id);
}

char *getUserID_reservartion(RESERVATION *r){
    return strdup(r->user_id);
}

char *getHotelID_reservation(RESERVATION *r) {
    return strdup(r->hotel_id);
}

char *getHotelName_reservation(RESERVATION *r) {
    return strdup(r->hotel_name);
}

double getHotelStars_reservation(RESERVATION *r) {
    return r->hotel_stars;
}

double getCityTax_reservation(RESERVATION *r) {
    return r->city_tax;
}

char *getAddress_reservation(RESERVATION *r) {
    return strdup(r->adress);
}

char *getBeginDate_reservation(RESERVATION *r) {
    return strdup(r->begin_date);
}

char *getEndDate_reservation(RESERVATION *r) {
    return strdup(r->end_date);
}

double getPricePerNight_reservation(RESERVATION *r) {
    return r->price_per_night;
}

char *getIncludesBreakfast_reservation(RESERVATION *r) {
    return strdup(r->includes_breakfast);
}

char *getRoomDetails_reservation(RESERVATION *r) {
    return strdup(r->room_details);
}

double getRating_reservation(RESERVATION *r) {
    return r->rating;
}

char *getComment_reservation(RESERVATION *r) {
    return strdup(r->comment);
}