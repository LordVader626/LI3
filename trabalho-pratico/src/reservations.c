#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/reservations.h"

struct reservation{
    char *id;
    char *user_id;
    char *hotel_id;
    char *hotel_name;
    int hotel_stars;
    int city_tax;
    char *adress;
    char *begin_date;
    char *end_date;
    int price_per_night;
    char *includes_breakfast; //usar bool lib ou 1 = TRUE && 0 = FALSE
    char *room_details;
    int rating;
    char *comment;
};

RESERVATION*create_Reservation(char *line){

    RESERVATION *r = malloc(sizeof(RESERVATION));

    r->id = strdup(strsep(&line, ";"));
    r->user_id = strdup(strsep(&line, ";"));
    r->hotel_id = strdup(strsep(&line, ";"));
    r->hotel_name = strdup(strsep(&line, ";"));
    r->hotel_stars = atoi(strsep(&line, ";"));
    r->city_tax = atoi(strsep(&line, ";"));
    r->adress = strdup(strsep(&line, ";"));
    r->begin_date = strdup(strsep(&line, ";"));
    r->end_date = strdup(strsep(&line, ";"));
    r->price_per_night = atoi(strsep(&line, ";"));
    r->includes_breakfast = strdup(strsep(&line, ";"));
    r->room_details = strdup(strsep(&line, ";"));
    r->rating = atoi(strsep(&line, ";"));
    r->comment = strdup(strsep(&line, "\n"));
    return r;
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

int getHotelStars_reservation(RESERVATION *r) {
    return r->hotel_stars;
}

int getCityTax_reservation(RESERVATION *r) {
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

int getPricePerNight_reservation(RESERVATION *r) {
    return r->price_per_night;
}

char *getIncludesBreakfast_reservation(RESERVATION *r) {
    return strdup(r->includes_breakfast);
}

char *getRoomDetails_reservation(RESERVATION *r) {
    return strdup(r->room_details);
}

int getRating_reservation(RESERVATION *r) {
    return r->rating;
}

char *getComment_reservation(RESERVATION *r) {
    return strdup(r->comment);
}