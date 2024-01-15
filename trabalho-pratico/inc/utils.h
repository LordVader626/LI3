#ifndef utils_h
#define utils_h

#include "../inc/stats.h"
#include "../inc/reservations.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include <stdbool.h>

int get_Nights (RESERVATION *res);
double get_Total_Price(RESERVATION *res);
int getNumVoos(char*username,GArray *passengers);
int get_Idade (USER *user) ;
void removeHMS(char *inputString);
gint compare_flights(gconstpointer a, gconstpointer b);
gint compare_reservations(gconstpointer a, gconstpointer b);
int get_tempo_atraso(FLIGHT *flight);
int get_Ano_Voo(FLIGHT *f);
void addAtraso(int *arr, int at, int n);
int passageirosPorVoo(char * idflight , GArray *passengers);
void insertion_Sort(int arr[], int n, int value);
int compare_dates(char * data1 , char * data2);
gint compareNPassageirosAno(gconstpointer a, gconstpointer b, gpointer userdata);
gint compareMediana(gconstpointer a, gconstpointer b);
gint compare_flightswithHours(gconstpointer a, gconstpointer b);
gboolean remove_keys(gpointer key, gpointer value, gpointer user_data);

void insertionSort_garray(GArray *garray, int value);
int compare_flights_and_reservations(gconstpointer a, gconstpointer b);
bool is_flight(gpointer data);
bool is_reservation(gpointer data);

#endif