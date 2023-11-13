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
    else if (isalpha(linha[0])!=0) {
        USER* user = g_hash_table_lookup(users,linha);
        
        if (user == NULL) {
            printf("User not found in hash table\n");
            return;
        }

        char *account_status = getAccountStatus(user);
        
        if(strcmp(account_status,"active") == 0){
           
            char *idUser = getID(user);
            
            USER_STAT *us = g_hash_table_lookup(user_stats,idUser);
            
            char *name = getName(user);
            char *sex = getSex(user);
            char *passport = getPassport(user);
            char *country_code = getCountryCode(user);
            int idade = get_Idade(user);
            int numVoos = get_user_stat_numVoos(us);
            int numReservas = get_user_stat_numReservas(us);
            double totalGasto = get_user_stat_totalGasto(us);

            if(f == 1){
                fprintf(file,"--- 1 ---\n");
                fprintf(file,"nome: %s\n",name);
                fprintf(file,"sexo: %s\n",sex);
                fprintf(file,"idade: %d\n",idade);
                fprintf(file,"codigo_do_país: %s\n",country_code);
                fprintf(file,"passaporte: %s\n",passport);
                fprintf(file,"número_voos: %d\n",numVoos);
                fprintf(file,"número_reservas: %d\n",numReservas);
                fprintf(file,"total_gasto: %.3f\n",totalGasto);
            } else fprintf(file,"%s;%s;%d;%s;%s;%d;%d;%.3f\n",name,sex,idade,country_code,passport,numVoos,numReservas,totalGasto);

            free(account_status);
            free(idUser);
            free(name);
            free(sex);
            free(passport);
            free(country_code); 
        }
    } 
      else {
        FLIGHT* flight = g_hash_table_lookup(flights,linha);

        if (flight == NULL) {
            printf("Flight not found in hash table\n");
            return;
        }
        
        FLIGHT_STAT *fs = g_hash_table_lookup(flight_stats,linha);

        char *companhia = getAirline(flight);
        char *aviao = getPlaneModel(flight);
        char *origem = getFlightOrigin(flight);
        char *destino = getFlightDestination(flight);
        char *partida_est = getScheduleDepartureDate(flight);
        char *chegada_est = getScheduleArrivalDate(flight);
        int numero_passageiros = get_flight_stat_nPassageiros(fs);
        int tempo_atraso = get_tempo_atraso(flight);

        if(f == 1){
            fprintf(file,"--- 1 ---\n");
            fprintf(file,"companhia: %s\n",companhia);
            fprintf(file,"avião: %s\n",aviao);
            fprintf(file,"origem: %s\n",origem);
            fprintf(file,"destino: %s\n",destino);
            fprintf(file,"partida_est: %s\n",partida_est);
            fprintf(file,"chegada_est: %s\n",chegada_est);
            fprintf(file,"número_passageiros: %d\n",numero_passageiros);
            fprintf(file,"tempo_atraso: %d\n",tempo_atraso);
            
            printf("Flight from query 1 printed\n");
        }
        else {
            fprintf(file,"%s;%s;%s;%s;%s;%s;%d;%d\n",companhia,aviao, origem, destino, partida_est, chegada_est, numero_passageiros, tempo_atraso);
            printf("Flight from query 1 printed\n");
        }
        free(companhia);
        free(aviao);
        free(origem);
        free(destino);
        free(partida_est);
        free(chegada_est);

    }
    fclose(file);
}

void query2(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats){
}