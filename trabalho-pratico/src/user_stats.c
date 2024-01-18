#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/user_stat.h"
#include "../inc/users.h"
#include "../inc/catalogo_user.h"
#include "../inc/catalogo_flights.h"

/*
	Struct que vai guardar os dados para as stats dos utilizadores
*/
struct user_stat{
	char *username;
	int numReservas;
	int numVoos;
    GList *listaVoos;
	GList *listaReservas;
	double total_gasto;
};

/*
	Função que liberta o espaço das user_stats
*/
void kill_userStat(void *userStat){
	USER_STAT *us = userStat;
	free(us->username);
	g_list_free(us->listaVoos);
	g_list_free(us->listaReservas);

	free(us);
}

// GETTERS

char *get_user_stat_username(USER_STAT *s)
{
	return strdup(s->username);
}

int get_user_stat_numReservas(USER_STAT *s)
{
	return s->numReservas;
}

int get_user_stat_numVoos(USER_STAT *s)
{
	return s->numVoos;
}

GList* get_user_stat_listaVoos(USER_STAT *s)
{
	return g_list_copy(s->listaVoos);
}
GList* get_user_stat_listaReservas(USER_STAT *s)
{
	return g_list_copy(s->listaReservas);
}

double get_user_stat_totalGasto(USER_STAT *s)
{
	return s->total_gasto;
}


/*
	Funções que criam as stats para os utilizadores
	Caso não exista ja criada inicia os dados
	Caso contrario apenas os atualiza
*/
void create_user_stat_flights(PASSENGER *p, STATS *s, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights)
{
	char *username = getID_passenger(p);
	USER *u = getUser(cat_users, username);

	USER_STAT *ustat = get_stat_user(s, username);

	char *account_status = getAccountStatus(u);

	if (!strcasecmp(account_status, "active"))
	{   
		char *flightID = get_FlightID_passenger(p);
        FLIGHT *f = getFlight(cat_flights, flightID);

		if (ustat == NULL)
		{
			USER_STAT *user_stat = malloc(sizeof(USER_STAT));

			user_stat->username = username;
            user_stat->numReservas = 0;
			user_stat->numVoos = 1;
			user_stat->listaReservas = NULL;
			user_stat->listaVoos = g_list_prepend(NULL, f);
			user_stat->total_gasto = 0;
			addUserStat(s, user_stat, username);
		}
		else{
			ustat->numVoos = get_user_stat_numVoos(ustat) + 1;
            ustat->listaVoos = g_list_prepend(ustat->listaVoos,f);
			free(username);
        }
		free(flightID);
    }
	else free(username);

	free(account_status);
}

void create_user_stat_reservations(RESERVATION *r, STATS *stats, CATALOGO_USER *cat_users)
{
    char *username = getUserID_reservartion(r);

	USER *u = getUser(cat_users, username);

	USER_STAT *ustat = get_stat_user(stats, username);

    char *account_status = getAccountStatus(u);

    if (!strcasecmp(account_status, "active"))
    {
        if (ustat == NULL)
        {
			
            USER_STAT *user_stat = malloc(sizeof(USER_STAT));
            user_stat->username = username;
            user_stat->numReservas = 1;
            user_stat->numVoos = 0;
            user_stat->listaVoos = NULL;
            user_stat->listaReservas = g_list_prepend(NULL, r);
            user_stat->total_gasto = get_Total_Price(r);
            //g_hash_table_insert(user_stats, user_stat->username, user_stat);
			addUserStat(stats, user_stat, username);
        }
        else
        {			
            ustat->numReservas += 1;
            ustat->listaReservas = g_list_prepend(ustat->listaReservas, r);
				//		if(strcmp(username, "FrancDomingues523") == 0){
				//traverseGList(ustat->listaReservas);
			//}
            ustat->total_gasto += get_Total_Price(r);
            free(username);
        }
    } else free(username);
    free(account_status);
}