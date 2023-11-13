#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "../inc/queries.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/parser.h"
#include "../inc/handle.h"
#include "../inc/utils.h"
#include "../inc/stats.h"
#include "../inc/user_stat.h"
#include "../inc/flight_stats.h"



void query1(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats,GHashTable *flight_stats){
    char *aux = strdup(linha);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    
    if(strncmp(aux, "Book", 4) == 0) {
        //  ./main-program /home/rui/Desktop/dataset/data_clean /home/rui/Desktop/dataset/inputTest.txt
        RESERVATION* res = g_hash_table_lookup(reservations,linha);

        if (res == NULL) {
            printf("Reservation not found in hash table\n");
            return;
        }

        char *idHotel = getHotelID_reservation(res);
        char *hotelName = getHotelName_reservation(res);
        int hotelStars = getHotelStars_reservation(res);
        char *beginDate = getBeginDate_reservation(res);
        char *endDate = getEndDate_reservation(res);
        char *incBreakfast = getIncludesBreakfast_reservation(res);
        int nights = get_Nights(res);
        double totalPrice = get_Total_Price(res);

        if(f == 1){
            fprintf(file,"--- 1 ---\n");
            fprintf(file,"hotel_id: %s\n",idHotel);
            fprintf(file,"hotel_name: %s\n",hotelName);
            fprintf(file,"hotel_stars: %d\n",hotelStars);
            fprintf(file,"begin_date: %s\n",beginDate);
            fprintf(file,"end_date: %s\n",endDate);
            fprintf(file,"includes_breakfast: %s\n",incBreakfast);
            fprintf(file,"nights: %d\n",nights);
            fprintf(file,"total_price: %.3f\n",totalPrice);
            
            printf("Reservation id %s from query 1 printed\n", idHotel);
        }
        else {
            fprintf(file,"%s;%s;%d;%s;%s;%s;%d;%.3f\n",idHotel,hotelName, hotelStars, beginDate, endDate, incBreakfast, nights, totalPrice);
            printf("Reservation id %s from query 1 printed\n", idHotel);
        }
        free(idHotel);
        free(hotelName);
        free(beginDate);
        free(endDate);
        free(incBreakfast);
    }
}

void query2(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats){
}