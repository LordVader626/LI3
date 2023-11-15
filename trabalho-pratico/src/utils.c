#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <time.h>

#include "../inc/queries.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include "../inc/passengers.h"
#include "../inc/reservations.h"
#include "../inc/parser.h"
#include "../inc/handle.h"
#include "../inc/user_stat.h"
#include "../inc/stats.h"

#define TODAY "2023/10/01"

int get_Nights (RESERVATION *res) {
    char *begindate = getBeginDate_reservation(res);
    char *enddate = getEndDate_reservation(res);

    int year1,month1,day1, year2,month2,day2;

    sscanf(enddate,"%d/%d/%d", &year2, &month2, &day2);
    sscanf(begindate, "%d/%d/%d", &year1, &month1, &day1);

    /*char *aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");
    aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");*/
    
    //int noites = atoi(strsep(&enddate,"/n")) - atoi(strsep(&begindate,"/n"));

    int noites = day2 - day1;

    free(begindate);
    free(enddate);
    return noites;
}

double get_Total_Price(RESERVATION *res){
    double preco = getPricePerNight_reservation(res);
    int noites = get_Nights(res);
    double imposto = getCityTax_reservation(res);
    double total = preco*noites+((preco*noites)/100)*imposto;
    return total;
}
int getNumVoos(char*username,GArray *passengers){
    int total = 0;
    PASSENGER *p = malloc(sizeof(PASSENGER*));
    guint i;
    for (i = 0; i < passengers->len; i++) {
        p = g_array_index(passengers, PASSENGER*, i);
        char* id_Passenger = getID_passenger(p);
        if (strcmp(id_Passenger,username) == 0) total++;
        free(id_Passenger);
    }
        free(p);

    return total;
}

int get_Idade (USER *user) {
    char * birthdate = getBirthDate(user);

    int idade, ano, mes, dia;
    
    sscanf(birthdate, "%d/%d/%d", &ano, &mes, &dia);
    
    if (mes<10) idade = 2023 - ano;
    else if (mes== 10 && dia >= 1) idade = 2023-ano;
    else idade = 2023-ano-1;

    free(birthdate);

    return idade;
}
/*
int get_tempo_atraso(FLIGHT *flight){
    char *tp_est = getScheduleDepartureDate(flight);
    char *tp_rl = getRealDepartureDate(flight);

    char * aux = strsep(&tp_est, " ");
    aux = strsep(&tp_rl, " ");
    int horaEST = atoi(strsep(&tp_est,":"));
    int minutoEST = atoi(strsep(&tp_est,":"));
    int secEST = atoi(strsep(&tp_est,"\n"));

    int horaRL = atoi(strsep(&tp_rl,":"));
    int minutoRL = atoi(strsep(&tp_rl,":"));
    int secRL = atoi(strsep(&tp_rl,"\n"));

    int total = (horaRL-horaEST) * 3600 + (minutoRL-minutoEST)*60 +(secRL-secEST);

    free(tp_est);
    free(tp_rl);
    return total;
}*/

int get_tempo_atraso(FLIGHT *flight) {
    char *tp_est = getScheduleDepartureDate(flight);
    char *tp_rl = getRealDepartureDate(flight);

    int horaEST, minutoEST, secEST;
    int horaRL, minutoRL, secRL;

    sscanf(tp_est, "%*d/%*d/%*d %d:%d:%d", &horaEST, &minutoEST, &secEST);

    sscanf(tp_rl, "%*d/%*d/%*d %d:%d:%d", &horaRL, &minutoRL, &secRL);

    int total = (horaRL - horaEST) * 3600 + (minutoRL - minutoEST) * 60 + (secRL - secEST);

    free(tp_est);
    free(tp_rl);

    return total;
}

void removeHMS(char *inputString) {
    char *space = strchr(inputString, ' ');
    if (space != NULL) {
        *space = '\0';
    }
}

gint compare_flights(gconstpointer a, gconstpointer b) {
    FLIGHT *f1 = (FLIGHT*)a;
    FLIGHT *f2 = (FLIGHT*)b;

    char *date1 = getScheduleDepartureDate(f1);
    char *date2 = getScheduleDepartureDate(f2);

    removeHMS(date1);
    removeHMS(date2);

    int year1, month1, day1;
    int year2, month2, day2;

    sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
    sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);

    if (year1 != year2) {
        free(date1);
        free(date2);
        return year2 - year1;
    }
    if (month1 != month2) {
        free(date1);
        free(date2);
        return month2 - month1;
    }
    if (day1 != day2) {
        free(date1);
        free(date2);
        return day2 - day1;
    }

    char *id_flight1 = getID_flight(f1);
    char *id_flight2 = getID_flight(f2);


    gint result = atoi(id_flight1) - atoi(id_flight2);

    free(id_flight1);
    free(id_flight2);
    free(date1);
    free(date2);

    return result;
}

gint compare_reservations(gconstpointer a, gconstpointer b) {
    RESERVATION *res1 = (RESERVATION*)a;
    RESERVATION *res2 = (RESERVATION*)b;

    char *date1 = getBeginDate_reservation(res1);
    char *date2 = getBeginDate_reservation(res2);

    char *id1 = getID_reservation(res1);
    char *id2 = getID_reservation(res2);
    char *noBook1 = id1 + 4;
    char *noBook2 = id2 + 4;

    int year1, month1, day1;
    int year2, month2, day2;

    sscanf(date1, "%d/%d/%d", &year1, &month1, &day1);
    sscanf(date2, "%d/%d/%d", &year2, &month2, &day2);

    if (year1 != year2) {
        free(id1);
        free(id2);
        free(date1);
        free(date2);
        return year2 - year1;
    }
    if (month1 != month2) {
        free(id1);
        free(id2);
        free(date1);
        free(date2);
        return month2 - month1;
    }
    if (day1 != day2) {
        free(id1);
        free(id2);
        free(date1);
        free(date2);
        return day2 - day1;
    }

    gint result = atoi(noBook1) - atoi(noBook2);

    free(id1);
    free(id2);
    free(date1);
    free(date2);

    return result;
}

int get_Ano_Voo(FLIGHT *f){
    char *data_est = getScheduleDepartureDate(f);
    int ano;

    sscanf(data_est, "%d/%*d/%*d %*d:%*d:%*d", &ano);

    free(data_est);
    return ano;
}

void addAtraso(int *arr, int at, int n)
{
    int i; 
    for (i = n - 1; (i >= 0 && arr[i] > at); i--) 
        arr[i + 1] = arr[i]; 
  
    arr[i + 1] = at; 
}
int passageirosPorVoo(char *idflight , GArray *passengers){
    int n = 0;
    for(guint i = 0; i < passengers->len ;i++) {
        PASSENGER *p = g_array_index(passengers,PASSENGER*,i);
        char *id_flight = get_FlightID_passenger(p);
        if (strcmp(id_flight,idflight)==0) n++;
        free(id_flight);
    }
    return n;
}