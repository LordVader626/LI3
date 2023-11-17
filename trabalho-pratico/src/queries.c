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
#include "../inc/hotel_stats.h"
#include "../inc/airport_stats.h"
#include "../inc/validation.h"



void query1(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats){;
    char *aux = strdup(linha);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }
    
    if(strncmp(aux, "Book", 4) == 0) {
        //  ./main-program /home/rui/Desktop/dataset/data_clean /home/rui/Desktop/dataset/inputTest.txt
        RESERVATION* res = g_hash_table_lookup(reservations,aux);

        if (res == NULL) {
            printf("Reservation not found in hash table\n");
            fclose(file);
            return;
        }

        char *idHotel = getHotelID_reservation(res);
        char *hotelName = getHotelName_reservation(res);
        double hotelStars = getHotelStars_reservation(res);
        char *beginDate = getBeginDate_reservation(res);
        char *endDate = getEndDate_reservation(res);
        char *incBreakfast = getIncludesBreakfast_reservation(res);
        int nights = get_Nights(res);
        double totalPrice = get_Total_Price(res);

        if(f == 1){
            fprintf(file,"--- 1 ---\n");
            fprintf(file,"hotel_id: %s\n",idHotel);
            fprintf(file,"hotel_name: %s\n",hotelName);
            fprintf(file,"hotel_stars: %d\n",(int) hotelStars);
            fprintf(file,"begin_date: %s\n",beginDate);
            fprintf(file,"end_date: %s\n",endDate);
            if(strcasecmp(incBreakfast,"true") == 0|| strcasecmp(incBreakfast,"t") == 0|| strcmp(incBreakfast,"1") == 0) fprintf(file,"includes_breakfast: True\n");
            else fprintf(file,"includes_breakfast: False\n");
        
            fprintf(file,"nights: %d\n",nights);
            fprintf(file,"total_price: %.3f\n",totalPrice);
            
            printf("Reservation id %s from query 1 printed\n", idHotel);
        }
        else {
            if(strcasecmp(incBreakfast,"true") == 0|| strcasecmp(incBreakfast,"t") == 0|| strcmp(incBreakfast,"1") == 0) 
            fprintf(file,"%s;%s;%d;%s;%s;True;%d;%.3f\n",idHotel,hotelName, (int) hotelStars, beginDate, endDate, nights, totalPrice);
            else fprintf(file,"%s;%s;%d;%s;%s;False;%d;%.3f\n",idHotel,hotelName, (int) hotelStars, beginDate, endDate, nights, totalPrice);
            printf("Reservation id %s from query 1 printed\n", idHotel);
        }
        free(idHotel);
        free(hotelName);
        free(beginDate);
        free(endDate);
        free(incBreakfast);
    }
    else if (isalpha(aux[0])!=0) {
        USER* user = g_hash_table_lookup(users,aux);
        
        if (user == NULL) {
            printf("User not found in hash table\n");
            fclose(file);
            return;
        }

        char *account_status = getAccountStatus(user);
        
        if(strcmp(account_status,"active") == 0){
            int numVoos;
            int numReservas;
            double totalGasto;;

            char *idUser = getID(user);

            USER_STAT *us = g_hash_table_lookup(user_stats,idUser);

            if(us == NULL){
                numVoos = 0;
                numReservas = 0;
                totalGasto = 0;
            } else{
                numVoos= get_user_stat_numVoos(us);
                numReservas = get_user_stat_numReservas(us);
                totalGasto = get_user_stat_totalGasto(us);
            }

            printf("%d\n", numVoos);
            
            char *name = getName(user);
            char *sex = getSex(user);
            char *passport = getPassport(user);
            char *country_code = getCountryCode(user);
            int idade = get_Idade(user);

            if(f == 1){
                fprintf(file,"--- 1 ---\n");
                fprintf(file,"name: %s\n",name);
                fprintf(file,"sex: %s\n",sex);
                fprintf(file,"age: %d\n",idade);
                fprintf(file,"country_code: %s\n",country_code);
                fprintf(file,"passport: %s\n",passport);
                fprintf(file,"number_of_flights: %d\n",numVoos);
                fprintf(file,"number_of_reservations: %d\n",numReservas);
                fprintf(file,"total_spent: %.3f\n",totalGasto);
            } else fprintf(file,"%s;%s;%d;%s;%s;%d;%d;%.3f\n",name,sex,idade,country_code,passport,numVoos,numReservas,totalGasto);

            free(idUser);
            free(name);
            free(sex);
            free(passport);
            free(country_code); 
        }
        free(account_status);
    } 
    else {
        FLIGHT* flight = g_hash_table_lookup(flights,aux);

        if (flight == NULL) {
            printf("Flight not found in hash table\n");
            fclose(file);
            return;
        }

        char *companhia = getAirline(flight);
        char *aviao = getPlaneModel(flight);
        char *origem = getFlightOrigin(flight);
        char *destino = getFlightDestination(flight);
        char *partida_est = getScheduleDepartureDate(flight);
        char *chegada_est = getScheduleArrivalDate(flight);
        int numero_passageiros = passageirosPorVoo(aux ,passengers);
        int tempo_atraso = get_tempo_atraso(flight);

        if(f == 1){
            fprintf(file,"--- 1 ---\n");
            fprintf(file,"airline: %s\n",companhia);
            fprintf(file,"plane_model: %s\n",aviao);
            fprintf(file,"origin: %s\n",origem);
            fprintf(file,"destination: %s\n",destino);
            fprintf(file,"schedule_departure_date: %s\n",partida_est);
            fprintf(file,"schedule_arrival_date: %s\n",chegada_est);
            fprintf(file,"passengers: %d\n",numero_passageiros);
            fprintf(file,"delay: %d\n",tempo_atraso);
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
    free(aux);
}

void query2(GHashTable *reservations, GHashTable *users,GHashTable *flights, GArray *passengers ,char* linha, int f,char *path, GHashTable *user_stats, GHashTable *invalid_users){
    char *aux = strdup(linha);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }
    char *id = malloc(20);
    char *type = malloc(15);

    if (sscanf(aux, "%20s %14s", id, type) == 2) {
        if (strcmp(type, "flights") == 0 && g_hash_table_lookup(invalid_users, id) == NULL && g_hash_table_lookup(users, id) != NULL) {
            USER *u = g_hash_table_lookup(users, id);

            char *accountStatus = getAccountStatus(u);

            if(strcasecmp(accountStatus, "active") == 0){
                USER_STAT *userStat = g_hash_table_lookup(user_stats, id);

                if(userStat != NULL){

                    GList *listaVoos = get_user_stat_listaVoos(userStat);

                    listaVoos = g_list_sort(listaVoos, compare_flights);
                    GList *current = listaVoos;
                    if (f == 0) {
                        while (current != NULL) {
                            FLIGHT *flight = (FLIGHT*)current->data;
                            char *data = getScheduleDepartureDate(flight);
                            char *id_flight = getID_flight(flight);
                            removeHMS(data);
                            fprintf(file, "%s;%s\n", id_flight, data);
                            free(data);
                            free(id_flight);
                            current = g_list_next(current);
                        }
                        printf("Flight dates printed\n");
                    }
                    else {
                        guint i = 1;
                        while (current != NULL) { if (i!=1) fprintf(file,"\n");
                            FLIGHT *flight = (FLIGHT*)current->data;
                            char *id_flight = getID_flight(flight);
                            fprintf(file, "--- %d ---\n", i);
                            fprintf(file, "id: %s\n", id);
                            char *data = getScheduleDepartureDate(flight);
                            removeHMS(data);
                            fprintf(file, "date: %s\n", data);
                            free(data);
                            free(id_flight);
                            current = g_list_next(current);
                            i++;
                        }
                        printf("Flight dates printed\n");
                    }
                }
            free(accountStatus);
            }
        }
        
        else if (strcmp(type, "reservations") == 0 && g_hash_table_lookup(invalid_users, id) == NULL && g_hash_table_lookup(users, id) != NULL){
            USER *u = g_hash_table_lookup(users, id);
            char *accountStatus = getAccountStatus(u);

            if(strcasecmp(accountStatus, "active") == 0){
                USER_STAT *userStat = g_hash_table_lookup(user_stats, id);

                if(userStat != NULL){
                    GList *listaReservas = get_user_stat_listaReservas(userStat);

                    GList *current = listaReservas;
                    listaReservas = g_list_sort(listaReservas, compare_reservations);
                    if (f == 0) {
                        while (current != NULL){
                            RESERVATION *reserva = (RESERVATION*)current->data;
                            char *idReserva = getID_reservation(reserva);
                            char *beginDate = getBeginDate_reservation(reserva);
                            fprintf(file, "%s;%s\n", idReserva, beginDate);

                            free(idReserva);
                            free(beginDate);
                            current = g_list_next(current);
                        }
                        printf("Reservation dates printed\n");
                    } else {
                        guint i = 1;
                        while (current != NULL) {
                            if(i!=1) fprintf(file,"\n");
                            RESERVATION *reserva = (RESERVATION*)current->data;
                            char *idReserva = getID_reservation(reserva);
                            char *beginDate = getBeginDate_reservation(reserva);
                            fprintf(file, "--- %d ---\n", i);
                            fprintf(file, "id: %s\n", idReserva);
                            fprintf(file, "date: %s\n", beginDate);

                            free(idReserva);
                            free(beginDate);
                            current = g_list_next(current);
                            i++;
                        }
                        printf("Reservation dates from user printed\n");
                    }
                }
            }
            free(accountStatus);
        }
    } 
    else if (sscanf(aux, "%20s", id) == 1) {
        printf("IN PROGRESS\n");
    }
    free(aux);
    free(id);
    free(type);
    fclose(file);
}

void query3(GHashTable *reservations,char* linha, int f,char *path, GHashTable *hotel_stats){
    char *aux = strdup(linha);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    HOTEL_STAT *hstat = g_hash_table_lookup(hotel_stats,aux);

    if(hstat != NULL){

        double avgscore = get_hotel_stat_avgscore(hstat);

        if(f == 1){
            fprintf(file,"--- 1 ---\n");
            fprintf(file,"rating: %.3f\n",avgscore);
        }
        else {
            fprintf(file,"%.3f\n",avgscore);
            printf("Rating from Hotel  from query 3 printed\n");
        }
    }
    fclose(file);
    free(aux);
}

void query4(char *linha, int f, char *path, GHashTable *hotel_stats){
    char *aux = strdup(linha);
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    HOTEL_STAT *hstat = g_hash_table_lookup(hotel_stats,aux);

        if(hstat != NULL){

        GList *sortedList = g_list_sort(get_hotel_stat_reservasHotel(hstat), compare_reservations);
        if (f == 0) {
            while (sortedList != NULL){
                RESERVATION *reserva = (RESERVATION*)sortedList->data;
                char *idReserva = getID_reservation(reserva);
                char *beginDate = getBeginDate_reservation(reserva);
                char *endDate = getEndDate_reservation(reserva);
                char *user_id = getUserID_reservartion(reserva);
                double rating = getRating_reservation(reserva);
                double total_price = get_Total_Price(reserva);

                fprintf(file, "%s;%s;%s;%s;%d;%.3f\n", idReserva, beginDate, endDate, user_id, (int)rating, total_price);
                sortedList = g_list_next(sortedList);

                free(idReserva);
                free(beginDate);
                free(endDate);
                free(user_id);
                }
            printf("Reservation dates from Hotel\n");
        } else {
            guint i = 1;
            while (sortedList != NULL) {
                RESERVATION *reserva = (RESERVATION*)sortedList->data;
                char *idReserva = getID_reservation(reserva);
                char *beginDate = getBeginDate_reservation(reserva);
                char *endDate = getEndDate_reservation(reserva);
                char *user_id = getUserID_reservartion(reserva);
                double rating = getRating_reservation(reserva);
                double total_price = get_Total_Price(reserva);
                if(i!=1) fprintf(file,"\n");
                fprintf(file, "--- %d ---\n", i);
                fprintf(file, "id: %s\n", idReserva);
                fprintf(file, "begin_date: %s\n", beginDate);
                fprintf(file, "end_date: %s\n", endDate);
                fprintf(file, "user_id: %s\n", user_id);
                fprintf(file, "rating: %d\n", (int)rating);
                fprintf(file, "total_price: %.3f\n", total_price);
                sortedList = g_list_next(sortedList);
                i++;

                free(idReserva);
                free(beginDate);
                free(endDate);
                free(user_id);
            }
            printf("Reservation dates from hotel\n");
        }
    }
    fclose(file);
    free(aux);
}

void query5(char *linha, int f, char *path, GHashTable *airport_stats){

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *aux = strdup(linha); //need to fix memleak
    char *airportID = strdup(strsep(&aux,"\""));
    char *begindate = strdup(strsep(&aux,"\""));
    char *enddate = strdup(strsep(&aux,"\n"));
    airportID[3] = '\0';
    for(int i = 2; i<strlen(enddate);i++) enddate[i-2] = enddate[i];
    enddate[19] = '\0';   

    AIRPORT_STAT *astat = g_hash_table_lookup(airport_stats,airportID);


    GList * listaAuxiliar = g_list_sort(get_airport_stat_listaVoos(astat), compare_flights);
    


    GList * listaVoosOrd = NULL;
    
    while (listaAuxiliar != NULL && listaAuxiliar->data != NULL) {

        FLIGHT *fl = malloc(sizeof(FLIGHT*));
        fl = (FLIGHT*) listaAuxiliar->data;
        char *dataF = getScheduleDepartureDate(fl);
        if (compare_dates(dataF,begindate) != 1 && compare_dates(dataF,enddate) != -1) { 
            listaVoosOrd = g_list_append(listaVoosOrd,fl);
            }
            listaAuxiliar = g_list_next(listaAuxiliar);
        free(dataF);
        }
        

    if (f == 0) {
        while (listaVoosOrd != NULL) {
            FLIGHT *flight = (FLIGHT*)listaVoosOrd->data;
            char *id = getID_flight(flight);
            char *depdate = getScheduleDepartureDate(flight);
            char *destino = getFlightDestination(flight);
            char *airline = getAirline(flight);
            char *planemodel = getPlaneModel(flight);
            
            fprintf(file, "%s;%s;%s;%s;%s\n", id, depdate, destino, airline, planemodel);
            listaVoosOrd = g_list_next(listaVoosOrd);
            free(id);
            free(depdate);
            free(destino);
            free(airline);
            free(planemodel);
        }
    }
    else {
        guint i = 1;
        while (listaVoosOrd != NULL) {
            FLIGHT *flight = (FLIGHT*)listaVoosOrd->data;
            char *id = getID_flight(flight);
            char *depdate = getScheduleDepartureDate(flight);
            char *destino = getFlightDestination(flight);
            char *airline = getAirline(flight);
            char *planemodel = getPlaneModel(flight);
            if(i!=1) fprintf(file,"\n");
            fprintf(file, "--- %d ---\n", i);
            fprintf(file, "id: %s\n", id);
            fprintf(file, "schedule_departure_date: %s\n", depdate);
            fprintf(file, "destination: %s\n", destino);
            fprintf(file, "airline: %s\n", airline);
            fprintf(file, "plane_model: %s\n", planemodel);
            
            listaVoosOrd = g_list_next(listaVoosOrd);
            i++;
            free(id);
            free(depdate);
            free(destino);
            free(airline);
            free(planemodel);
            }
    }
    /*GList *current = listaAuxiliar;
    while (current != NULL) {
        free(current->data); // Free the individual elements
        current = g_list_next(current);
    }*/
    g_list_free(listaAuxiliar);
    g_list_free(listaVoosOrd);
    free(airportID);
    free(begindate);
    free(enddate);
    fclose(file);
}

void query6(char *linha, int f, char *path, GHashTable *airport_stats){

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    char *ano = strdup(strsep(&linha," "));
    int n = atoi(strsep(&linha,"\n"));
    GList *air_stats = g_hash_table_get_values(airport_stats);
    air_stats = g_list_sort_with_data(air_stats,compareNPassageirosAno, ano);
    int i = 1;
    
    if (f == 1) {
        while (i<=n)
        {
            AIRPORT_STAT *airport_stat = (AIRPORT_STAT*) g_list_nth_data(air_stats,i-1);
            char *airport_stat_id = get_airport_stat_id(airport_stat);
            if(i!=1) fprintf(file,"\n");
            fprintf(file, "--- %d ---\n", i);
            fprintf(file, "name: %s\n", airport_stat_id);
            fprintf(file, "passengers: %d\n", get_airport_stat_nPassageirosAno(airport_stat)[2023-atoi(ano)]);
            i++;
            free(airport_stat_id);
        }
    }
    else {
        while (i<=n)
        {
            AIRPORT_STAT *airport_stat = (AIRPORT_STAT*) g_list_nth_data(air_stats,i-1);
            char *airport_stat_id = get_airport_stat_id(airport_stat);

            fprintf(file, "%s;%d\n", airport_stat_id,get_airport_stat_nPassageirosAno(airport_stat)[2023-atoi(ano)]);
            i++;
            free(airport_stat_id);
            
        }
    }
    g_list_free(air_stats);
    free(ano);
    fclose(file);
}

void query7(char *linha, int f, char *path, GHashTable *airport_stats){

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error opening file");
        fclose(file);
        return;
    }

    int n = atoi(strsep(&linha,"\n"));
    GList *air_stats = g_hash_table_get_values(airport_stats);
    air_stats = g_list_sort(air_stats,compareMediana);

    int i = 1;
    int median;
    
    if (f == 1) {
        while (i<=n && i<20)
        {
            AIRPORT_STAT *airport_stat = (AIRPORT_STAT*) g_list_nth_data(air_stats,i-1);

            char *statID = get_airport_stat_id(airport_stat);
            if(i!=1) fprintf(file,"\n");
            fprintf(file, "--- %d ---\n", i);
            fprintf(file, "name: %s\n", statID);
            int *aux = get_airport_stat_atrasosVoos(airport_stat);
            int len = get_airport_stat_nVoos(airport_stat);
            int index = len/2;
            if(len % 2 == 0) median = (aux[index] + aux[index-1])/2;
            else median = aux[index];
            fprintf(file, "median: %d\n", median);
            i++;
            free(statID);
        }
    }
    else {
        while (i<=n && i<20)
        {
            AIRPORT_STAT *airport_stat = (AIRPORT_STAT*) g_list_nth_data(air_stats,i-1);
            
            char *statID = get_airport_stat_id(airport_stat);
            int *aux = get_airport_stat_atrasosVoos(airport_stat);
            int len = get_airport_stat_nVoos(airport_stat);
            int index = len/2;
            if(len % 2 == 0) median = (aux[index] + aux[index-1])/2;
            else median = aux[index];
            fprintf(file, "%s;%d\n", statID,median);
            i++;
            
            free(statID);
        }
    }
    g_list_free(air_stats);
    fclose(file);
}