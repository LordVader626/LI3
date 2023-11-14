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
    char *begindate = strdup(getBeginDate_reservation(res));
    char *enddate = strdup(getEndDate_reservation(res));

    char *aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");
    aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");
    
    int noites = atoi(strsep(&enddate,"/n")) - atoi(strsep(&begindate,"/n"));


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
        if (strcmp(getID_passenger(p),username) == 0) total++;
    }
        free(p);

    return total;
}

int get_Idade (USER *user) {
    char * birthdate = getBirthDate(user);
    int ano = atoi(strsep(&birthdate,"/"));
    int mes = atoi(strsep(&birthdate,"/"));
    int dia = atoi(strsep(&birthdate,"\n"));

    int idade ;
    if (mes<10) idade = 2023 - ano;
    else if (mes== 10 && dia >= 1) idade = 2023-ano;
    else idade = 2023-ano-1;
    return idade;
}

double getPrecoTotalReserva(RESERVATION *res) {
    char *begindate = strdup(getBeginDate_reservation(res));
    char *enddate = strdup(getEndDate_reservation(res));
    double preco = getPricePerNight_reservation(res);
    
    char *aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");
    aux = strsep(&enddate, "/");
    aux = strsep(&begindate, "/");

    double total = (strtod(strsep(&enddate, "\n"),NULL) - strtod(strsep(&begindate, "\n"),NULL)) * preco;
   
    
    free(begindate);
    free(enddate);

    return total;
}

int get_tempo_atraso(FLIGHT *flight){
    char * tp_est = strdup(getScheduleDepartureDate(flight));
    char * tp_rl = strdup(getRealDepartureDate(flight));

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

    gint result = atoi(getID_flight(f1)) - atoi(getID_flight(f2));

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

    gint result = atoi(noBook1) - atoi(noBook2);

    free(date1);
    free(date2);

    return result;
}