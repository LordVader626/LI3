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