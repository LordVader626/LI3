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
#include "../inc/airport_stats.h"
#include "../inc/stats.h"

#define TODAY "2023/10/01"


/*
    Função que retorna o numero de noites de uma reserva
*/
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


/*
    Função que retorna o total price de uma reserva
*/
double get_Total_Price(RESERVATION *res){
    double preco = getPricePerNight_reservation(res);
    int noites = get_Nights(res);
    double imposto = getCityTax_reservation(res);
    double total = preco*noites+((preco*noites)/100)*imposto;
    return total;
}

/*
    Função que retorna o numero de voos de um user
*/
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

/*
    Função que calcula a idade de um utilizador
*/
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
    Função que calcula o tempo de atraso de um flight
*/
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

/*
    Função que remove horas minutos e segundos de uma data
*/
void removeHMS(char *inputString) {
    char *space = strchr(inputString, ' ');
    if (space != NULL) {
        *space = '\0';
    }
}

/*
    Função responsavel por comparar flights por data
    Usada para dar sort nas listas
*/
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

/*
    Função responsavel por comparar reservas por data
    Usada para dar sort nas listas
*/
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


/*
    Função que retorna o ano de uma data
*/
int get_Ano_Voo(FLIGHT *f){
    char *data_est = getScheduleDepartureDate(f);
    int ano;

    sscanf(data_est, "%d/%*d/%*d %*d:%*d:%*d", &ano);

    free(data_est);
    return ano;
}

/*
    Função que adiciona um atrado ao seu array
*/
void addAtraso(int *arr, int at, int n)
{
    int i; 
    for (i = n - 1; (i >= 0 && arr[i] > at); i--) 
        arr[i + 1] = arr[i]; 
  
    arr[i + 1] = at; 
}

/*
    Função que returna o numero de passsageiros num voo
*/
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


/*
    Função insertion_sort
*/
void insertion_Sort(int arr[], int n, int value) {
    int i, j;

    for (i = 0; i < n; i++) {
        if (arr[i] >= value) {

            for (j = n; j > i; j--) {
                arr[j] = arr[j - 1];
            }

            arr[i] = value;

            return;
        }
    }
    arr[n] = value;
}

void insertionSort_garray(GArray *garray, int value) {
    int n = garray->len;

    for (guint i = 0; i < n; i++) {
        if (g_array_index(garray, int, i) >= value) {
            g_array_insert_val(garray, i, value);
            return;
        }
    }
    g_array_append_val(garray, value);
}

int compare_dates(char * data1 , char * data2) {
    int ano1,ano2,mes1,mes2,dia1,dia2,hora1,hora2,minuto1,minuto2,sec1,sec2;

    sscanf(data1, "%d/%d/%d %d:%d:%d", &ano1, &mes1, &dia1, &hora1, &minuto1 ,&sec1);
    sscanf(data2, "%d/%d/%d %d:%d:%d", &ano2, &mes2, &dia2, &hora2, &minuto2 ,&sec2);
    
    if ((ano1 > ano2) || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2) || 
    (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 > hora2) || (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 > minuto2)
    || (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 == minuto2 && sec1 > sec2))
        return -1;

    if (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 == minuto2 && sec1 == sec2)
        return 0;

    return 1;
}

/*gint compareNPassageirosAno(gconstpointer a, gconstpointer b, gpointer userdata) {
    AIRPORT_STAT *astat1 = (AIRPORT_STAT*)a;
    AIRPORT_STAT *astat2 = (AIRPORT_STAT*)b;
    char *ano = (char*) userdata;

    int npassageiros1 = get_airport_stat_nPassageirosAno(astat1)[2023-atoi(ano)];
    int npassageiros2 = get_airport_stat_nPassageirosAno(astat2)[2023-atoi(ano)];

    if (npassageiros1 != npassageiros2) {
        return npassageiros2 - npassageiros1;
    }

    char * id1 = get_airport_stat_id(astat1);
    char * id2 = get_airport_stat_id(astat2);
    if(id1[0]!= id2[0]) return id2[0]-id1[0];
    if(id1[1]!= id2[1]) return id2[1]-id1[1];
    if(id1[2]!= id2[2]) return id2[2]-id1[2];

    return 0;
}*/

gint compareNPassageirosAno(gconstpointer a, gconstpointer b, gpointer userdata) {
    AIRPORT_STAT *astat1 = (AIRPORT_STAT*)a;
    AIRPORT_STAT *astat2 = (AIRPORT_STAT*)b;
    char *ano = (char*)userdata;

    int npassageiros1 = get_airport_stat_nPassageirosAno(astat1)[2023 - atoi(ano)];
    int npassageiros2 = get_airport_stat_nPassageirosAno(astat2)[2023 - atoi(ano)];

    if (npassageiros1 != npassageiros2) {
        return npassageiros2 - npassageiros1;
    }

    char *id1 = get_airport_stat_id(astat1);
    char *id2 = get_airport_stat_id(astat2);

    if (id1[0] != id2[0]) {
        gint bool = id1[0] - id2[0];
        free(id1);
        free(id2);
        return bool;
    }
    if (id1[1] != id2[1]) {
        gint bool = id1[1] - id2[1];
        free(id1);
        free(id2);
        return bool;
    }
    if (id1[2] != id2[2]) {
        gint bool = id1[2] - id2[2];
        free(id1);
        free(id2);
        return bool;
    }

    free(id1);
    free(id2);
    return 0;
}

/*gint compareMediana(gconstpointer a, gconstpointer b){
    AIRPORT_STAT *astat1 = (AIRPORT_STAT*)a;
    AIRPORT_STAT *astat2 = (AIRPORT_STAT*)b;

    int *aux1 = get_airport_stat_atrasosVoos(astat1);
    int *aux2 = get_airport_stat_atrasosVoos(astat2);

    int len1 = get_airport_stat_nVoos(astat1);
    int len2 = get_airport_stat_nVoos(astat2);
    int mediana1,mediana2;
    int index1 = len1/2;
    int index2 = len2/2;

    if(aux1[0] == -1) return 1;
    if(aux2[0] == -1) return -1;

    if(len1 % 2 == 0) mediana1 = (aux1[index1] + aux1[index1-1])/2;
    else mediana1 = aux1[index1];
    if(len2 % 2 == 0) mediana2 = (aux2[index2] + aux2[index2-1])/2;
    else mediana2 = aux2[index2];

    if (mediana1 != mediana2) {
        return mediana2 - mediana1;
    }

    char *id1 = get_airport_stat_id(astat1);
    char *id2 = get_airport_stat_id(astat2);

    int idComparison = strcmp(id1, id2);

    free(id1);
    free(id2);

    return idComparison;
}*/

gint compareMediana(gconstpointer a, gconstpointer b) {
    AIRPORT_STAT *astat1 = (AIRPORT_STAT *)a;
    AIRPORT_STAT *astat2 = (AIRPORT_STAT *)b;

    GArray *aux1 = get_airport_stat_atrasosVoos(astat1);
    GArray *aux2 = get_airport_stat_atrasosVoos(astat2);

    int len1 = aux1->len;
    int len2 = aux2->len;
    int mediana1, mediana2;
    int index1 = len1 / 2;
    int index2 = len2 / 2;

    if (g_array_index(aux1, int, 0) == -1) return 1;
    if (g_array_index(aux2, int, 0) == -1) return -1;

    if (len1 % 2 == 0) mediana1 = (g_array_index(aux1, int, index1) + g_array_index(aux1, int, index1 - 1)) / 2;
    else mediana1 = g_array_index(aux1, int, index1);

    if (len2 % 2 == 0) mediana2 = (g_array_index(aux2, int, index2) + g_array_index(aux2, int, index2 - 1)) / 2;
    else mediana2 = g_array_index(aux2, int, index2);

    if (mediana1 != mediana2) {
        return mediana2 - mediana1;
    }

    char *id1 = get_airport_stat_id(astat1);
    char *id2 = get_airport_stat_id(astat2);

    int idComparison = strcmp(id1, id2);

    free(id1);
    free(id2);

    return idComparison;
}

gint compare_flightswithHours(gconstpointer a, gconstpointer b) {
    FLIGHT *f1 = (FLIGHT*)a;
    FLIGHT *f2 = (FLIGHT*)b;

    char *data1 = getScheduleDepartureDate(f1);
    char *data2 = getScheduleDepartureDate(f2);
    int ano1,ano2,mes1,mes2,dia1,dia2,hora1,hora2,minuto1,minuto2,sec1,sec2;

    sscanf(data1, "%d/%d/%d %d:%d:%d", &ano1, &mes1, &dia1, &hora1, &minuto1 ,&sec1);
    sscanf(data2, "%d/%d/%d %d:%d:%d", &ano2, &mes2, &dia2, &hora2, &minuto2 ,&sec2);
    free(data1);
    free(data2);
    if ((ano1 > ano2) || (ano1 == ano2 && mes1 > mes2) || (ano1 == ano2 && mes1 == mes2 && dia1 > dia2) || 
    (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 > hora2) || (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 > minuto2)
    || (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 == minuto2 && sec1 > sec2))
        return -1;

    if (ano1 == ano2 && mes1 == mes2 && dia1 == dia2 && hora1 == hora2 && minuto1 == minuto2 && sec1 == sec2)
        return 0;

    return 1;
}

gboolean remove_keys(gpointer key, gpointer value, gpointer user_data) {
    free(key);

    return FALSE;
}
