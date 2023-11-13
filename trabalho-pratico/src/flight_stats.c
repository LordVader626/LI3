#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/flight_stats.h"


struct f_stat{
    char *flightid;
    int nPassageiros;
};

// FUNÇÕES GET

char *get_flight_stat_id(FLIGHT_STAT *f)
{
	return strdup(f->flightid);
}

int get_flight_stat_nPassageiros(FLIGHT_STAT *f)
{
	return f->nPassageiros;
}

void create_flight_stat(PASSENGER *p, GHashTable *flight_stats, GHashTable *flights)
{
	char *flightID = get_FlightID_passenger(p);	
	
	FLIGHT_STAT *fstat = g_hash_table_lookup(flight_stats, flightID);

		if (fstat == NULL)
		{
			FLIGHT_STAT *flight_stat = malloc(sizeof(FLIGHT_STAT));

			flight_stat->flightid = flightID;
			flight_stat->nPassageiros = 1;
			g_hash_table_insert(flight_stats, flightID, flight_stat);
		}
		else{
			fstat->nPassageiros += 1;
			free(flightID);
        }
		
}

