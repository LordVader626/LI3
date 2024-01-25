#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "../inc/airport_stats.h"
#include "../inc/flights.h"
#include "../inc/catalogo_flights.h"

/*
    Struct que contem os dados necessários para os aerpoportos
*/

struct airport_stat{
    char *airportid;
    int nPassageirosAno[3];
    GArray *atrasosVoos;
    int nVoos;
    GList *listaVoos;
    //mediana = atrasosVoos[(n+1)/2];
};


/*
    Função Responsavel por libertar os airportStats
*/
void kill_airportStat(void *airportStat){
    AIRPORT_STAT *as = airportStat;

    if(as != NULL){
        free(as->airportid);
        if(as->atrasosVoos!=NULL) g_array_free(as->atrasosVoos, TRUE);

        g_list_free(as->listaVoos);

    }
    free(as);
}

// GETTERS 

char *get_airport_stat_id(AIRPORT_STAT *a)
{
	return strdup(a->airportid);
}

int *get_airport_stat_nPassageirosAno(AIRPORT_STAT *a)
{
	return a->nPassageirosAno;
}
GArray *get_airport_stat_atrasosVoos(AIRPORT_STAT *a)
{
	return a->atrasosVoos;
}
int get_airport_stat_nVoos(AIRPORT_STAT *a)
{
	return a->nVoos;
}
GList *get_airport_stat_listaVoos(AIRPORT_STAT *a)
{
	return g_list_copy(a->listaVoos);
}



/*
    Funções de criação de estatistica dos aeroportos
    Procura a estatistica, se nao encontrar cria uma nova, caso contrario da update aos campos
*/
void create_airport_stat_flight(FLIGHT *f, STATS *s) {
    int atraso = get_tempo_atraso(f);
    
    char *airportID = getFlightOrigin(f); 
    
    AIRPORT_STAT *astat = get_stat_airport(s, airportID);

    if (astat == NULL) {
        AIRPORT_STAT *airport_stat = malloc(sizeof(AIRPORT_STAT));
        
        airport_stat->airportid = airportID;
        for(int i = 0; i<3;i++) airport_stat->nPassageirosAno[i] = 0;
        airport_stat->atrasosVoos = g_array_new(FALSE, FALSE, sizeof(int));
        g_array_append_val(airport_stat->atrasosVoos, atraso);
        airport_stat->nVoos = 1;
        airport_stat->listaVoos= NULL;
        airport_stat->listaVoos = g_list_append(airport_stat->listaVoos, f);

        addAirportStat(s, airport_stat, airportID);

    } else {
        astat->listaVoos = g_list_append(astat->listaVoos,f);
        insertionSort_garray(astat->atrasosVoos, atraso);
        astat->nVoos += 1;
        free(airportID);
    }
    
}


void create_airport_stat_passenger(PASSENGER *p, STATS *stats, CATALOGO_FLIGHTS *cat_flights) {
    char *flightID = get_FlightID_passenger(p);
    FLIGHT *f = getFlight(cat_flights, flightID);
    char *airportIDorigin = getFlightOrigin(f);
    
    int ano = get_Ano_Voo(f);
    AIRPORT_STAT *astato = get_stat_airport(stats, airportIDorigin);

    size_t n = 2023 - ano;
    astato->nPassageirosAno[n] += 1;
    
    free(airportIDorigin);
    free(flightID);

    char * aIDdest = getFlightDestination(f);

    AIRPORT_STAT *astatd = get_stat_airport(stats, aIDdest);

    if(astatd == NULL) {
        AIRPORT_STAT *airport_statd = malloc(sizeof(AIRPORT_STAT));

        airport_statd->airportid = aIDdest;
        for(int i = 0; i<3;i++) airport_statd->nPassageirosAno[i] = 0;
        airport_statd->nPassageirosAno[n] = 1;
        airport_statd->atrasosVoos = g_array_new(FALSE, FALSE, sizeof(int));
        int insert = -1;
        g_array_append_val(airport_statd->atrasosVoos, insert);
        airport_statd->nVoos = 0;
        airport_statd->listaVoos = NULL;
        addAirportStat(stats, airport_statd, aIDdest);
    } else {
        astatd->nPassageirosAno[n] +=1;
        
        free(aIDdest);
    }

}

