#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "../inc/airport_stats.h"
#include "../inc/flights.h"


/*
    Struct que contem os dados necessários para os aerpoportos
*/

struct a_stat{
    char *airportid;
    int nPassageirosAno[3];
    int *atrasosVoos;
    int nVoos;
    GList *listaVoos;
    //mediana = atrasosVoos[(n+1)/2];
};


/*
    Função Responsavel por libertar os airportStats
*/
void kill_airportStat(void *airportStat){
    AIRPORT_STAT *as = airportStat;

    free(as->airportid);
    if(as->atrasosVoos!=NULL) free(as->atrasosVoos);

    g_list_free(as->listaVoos);

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
int *get_airport_stat_atrasosVoos(AIRPORT_STAT *a)
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
void create_airport_stat_flight(FLIGHT *f, GHashTable *airport_stats) {
    int atraso = get_tempo_atraso(f);
    
    char *airportID = getFlightOrigin(f); 
    
    AIRPORT_STAT *astat = g_hash_table_lookup(airport_stats, airportID);
    
    
    if (astat == NULL) {
        AIRPORT_STAT *airport_stat = malloc(sizeof(AIRPORT_STAT));
        
        airport_stat->airportid = airportID;
        for(int i = 0; i<3;i++) airport_stat->nPassageirosAno[i] = 0;
        airport_stat->atrasosVoos = (int *)malloc(200 * sizeof(int));
        airport_stat->atrasosVoos[0] = atraso;
        airport_stat->nVoos = 1;
        airport_stat->listaVoos= NULL;
        airport_stat->listaVoos = g_list_append(airport_stat->listaVoos, f);

        g_hash_table_insert(airport_stats, airportID, airport_stat);
    } else {
        astat->listaVoos = g_list_append(astat->listaVoos,f);
        insertion_Sort(astat->atrasosVoos,astat->nVoos,atraso);
        astat->nVoos += 1;
        free(airportID);
    }
    
}



void create_airport_stat_passenger(PASSENGER *p, GHashTable *airport_stats,GHashTable *flights) {
    char *flightID = get_FlightID_passenger(p);
    FLIGHT *f = g_hash_table_lookup(flights,flightID); 
    char *airportIDorigin = getFlightOrigin(f);
    
    int ano = get_Ano_Voo(f);
    AIRPORT_STAT *astato = g_hash_table_lookup(airport_stats, airportIDorigin);
    
    size_t n = 2023 - ano;
    astato->nPassageirosAno[n] += 1;
    
    free(airportIDorigin);
    free(flightID);

    char * aIDdest = getFlightDestination(f);

    AIRPORT_STAT *astatd = g_hash_table_lookup(airport_stats, aIDdest);

    if(astatd == NULL) {
        AIRPORT_STAT *airport_statd = malloc(sizeof(AIRPORT_STAT));

        airport_statd->airportid = aIDdest;
        for(int i = 0; i<3;i++) airport_statd->nPassageirosAno[i] = 0;
        airport_statd->nPassageirosAno[n] = 1;
        airport_statd->atrasosVoos = (int *)malloc(200 * sizeof(int));
        airport_statd->atrasosVoos[0] = -1;
        airport_statd->nVoos = 0;
        airport_statd->listaVoos = NULL;
        g_hash_table_insert(airport_stats, aIDdest, airport_statd);
    } else {
        astatd->nPassageirosAno[n] +=1;
        
        free(aIDdest);
    }

}
