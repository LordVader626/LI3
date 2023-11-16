#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/airport_stats.h"


struct a_stat{
    char *airportid;
    int nPassageirosAno[3];
    GArray *atrasosVoos;
    int nVoos;
    GList *listaVoos;
    //mediana = atrasosVoos[(n+1)/2];
};

void kill_airportStat(void *airportStat){
    AIRPORT_STAT *as = airportStat;

    free(as->airportid);
    
    g_array_free(as->atrasosVoos, TRUE);

    g_list_free(as->listaVoos);

    free(as);
}

// FUNÇÕES GET

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
	return a->listaVoos;
}

void create_airport_stat_flight(FLIGHT *f, GHashTable *airport_stats) {
    char *flightID = getID_flight(f);
    char *airportID = getFlightOrigin(f);
    int ano = get_Ano_Voo(f);
    int atraso = get_tempo_atraso(f);
    
    AIRPORT_STAT *astat = g_hash_table_lookup(airport_stats, airportID);
    
    if (astat == NULL) {
        AIRPORT_STAT *airport_stat = malloc(sizeof(AIRPORT_STAT));
        
        airport_stat->airportid = airportID;//strdup(airportID);
        airport_stat->nPassageirosAno[2023 - ano] = 0;
        airport_stat->atrasosVoos = g_array_new(FALSE,TRUE, sizeof(int));
        airport_stat->atrasosVoos = g_array_append_val(airport_stat->atrasosVoos,atraso);
        airport_stat->nVoos = 1;
        airport_stat->listaVoos = g_list_append(NULL, f);

        g_hash_table_insert(airport_stats, strdup(airportID), airport_stat);
    } else {
        
        astat->atrasosVoos = g_array_append_val(astat->atrasosVoos,atraso);
        astat->nVoos += 1;
        astat->listaVoos = g_list_append(astat->listaVoos, f);
        free(airportID);
    }
    free(flightID);
}

void create_airport_stat_passenger(PASSENGER *p, GHashTable *airport_stats,GHashTable *flights) {
    char *flightID = get_FlightID_passenger(p);
    FLIGHT *f = g_hash_table_lookup(flights,flightID);
    char *airportID = getFlightOrigin(f);
    int ano = get_Ano_Voo(f);

    AIRPORT_STAT *astat = g_hash_table_lookup(airport_stats, airportID);
        
    astat->nPassageirosAno[2023 - ano] += 1;
    
    free(airportID);
    free(flightID);
}