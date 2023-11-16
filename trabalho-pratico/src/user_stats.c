#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../inc/user_stat.h"
#include "../inc/users.h"


struct stat{
	char *username;
	char *nome;
	char *gender;
	int idade;
	int numReservas;
	int numVoos;
    GList *listaVoos;
	GList *listaReservas;
	double total_gasto;
};

void kill_userStat(void *userStat){
	USER_STAT *us = userStat;
	free(us->username);
	free(us->nome);
	free(us->gender);

	g_list_free(us->listaVoos);
	g_list_free(us->listaReservas);

	free(us);
}

// FUNÇÕES GET

char *get_user_stat_username(USER_STAT *s)
{
	return strdup(s->username);
}

char *get_user_stat_nome(USER_STAT *s)
{
	return strdup(s->nome);
}

char *get_user_stat_gender(USER_STAT *s)
{
	return strdup(s->gender);
}

int get_user_stat_idade(USER_STAT *s)
{
	return s->idade;
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
	return s->listaVoos;
}
GList* get_user_stat_listaReservas(USER_STAT *s)
{
	return s->listaReservas;
}

double get_user_stat_totalGasto(USER_STAT *s)
{
	return s->total_gasto;
}

void create_user_stat_flights(PASSENGER *p, GHashTable *user_stats, GHashTable *users, GHashTable *flights)
{
	char *username = getID_passenger(p);
	USER *u = g_hash_table_lookup(users, username);

	USER_STAT *ustat = g_hash_table_lookup(user_stats, username);
	
	char *account_status = getAccountStatus(u);

	if (!strcmp(account_status, "active"))
	{   
		char *flightID = get_FlightID_passenger(p);
        FLIGHT *f = g_hash_table_lookup(flights,flightID);

		if (ustat == NULL)
		{
			USER_STAT *user_stat = malloc(sizeof(USER_STAT));

			user_stat->username = username;
			user_stat->nome = getName(u);
			user_stat->gender = getSex(u);
			user_stat->idade = get_Idade(u);
            user_stat->numReservas = 0;
			user_stat->numVoos = 1;
			user_stat->listaReservas = NULL;
			user_stat->listaVoos = g_list_append(NULL, f);
			user_stat->total_gasto = 0;
			g_hash_table_insert(user_stats, username, user_stat);
		}
		else{
			ustat->numVoos = get_user_stat_numVoos(ustat) + 1;
            ustat->listaVoos = g_list_append(ustat->listaVoos,f);
			free(username);
        }
		free(flightID);
    }
	free(account_status);
}


void create_user_stat_reservations(RESERVATION *r, GHashTable *user_stats, GHashTable *users)
{
    char *username = getUserID_reservartion(r);
    USER *u = g_hash_table_lookup(users, username);

    USER_STAT *ustat = g_hash_table_lookup(user_stats, username);

    char *account_status = getAccountStatus(u);

    if (!strcmp(account_status, "active"))
    {
        if (ustat == NULL)
        {
            USER_STAT *user_stat = malloc(sizeof(USER_STAT));
            user_stat->username = username;
            user_stat->nome = getName(u);
            user_stat->gender = getSex(u);
            user_stat->idade = get_Idade(u);
            user_stat->numReservas = 1;
            user_stat->numVoos = 0;
            user_stat->listaVoos = NULL;
            user_stat->listaReservas = g_list_append(NULL, r);
            user_stat->total_gasto = get_Total_Price(r);
            g_hash_table_insert(user_stats, user_stat->username, user_stat);
        }
        else
        {
            ustat->numReservas += 1;
            ustat->listaReservas = g_list_append(ustat->listaReservas, r);
            ustat->total_gasto += get_Total_Price(r);
            free(username);
        }
    }
    free(account_status);
}
