#ifndef utils_h
#define utils_h

#include "../inc/stats.h"

int get_Nights (RESERVATION *res);
double get_Total_Price(RESERVATION *res);
int getNumVoos(char*username,GArray *passengers);
int get_Idade (USER *user) ;
//double getPrecoTotalReserva(RESERVATION *r);
void print_stats(STATS *s);
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

#endif