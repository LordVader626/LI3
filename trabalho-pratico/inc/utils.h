#ifndef utils_h
#define utils_h

#include "../inc/stats.h"
#include "../inc/reservations.h"
#include "../inc/users.h"
#include "../inc/flights.h"
#include <stdbool.h>
/**
 * @brief função para obter o numero de noites de uma reserva
 * 
 * @param res reserva
 * 
 * @return numero de noits
*/
int get_Nights (RESERVATION *res);

/**
 * @brief obtem o valor total de uma reserva
 * 
 * @param res reserva
 * 
 * @return valor total da reserva
*/
double get_Total_Price(RESERVATION *res);

/**
 * @brief obtem o numero de voos de um passagiero
 * 
 * @param username key do user a contar os voos
 * @param passengers array dos passageiros
 * 
 * @return numero de voos 
*/
int getNumVoos(char*username,GArray *passengers);

/**
 * @brief obtem a idade de um utilizador
 * 
 * @param user utilizador
 * 
 * @return idade
*/
int get_Idade (USER *user) ;

/**
 * @brief utilizada para remover as horas minutos e segundos
 * 
 * @param data data   
*/
void removeHMS(char *data);

//nao utilizadas
gint compare_flights(gconstpointer a, gconstpointer b);
gint compare_reservations(gconstpointer a, gconstpointer b);

/**
 * @brief obtem o tempo de atraso de um flight
 * 
 * @param flight voo
*/
int get_tempo_atraso(FLIGHT *flight);

/**
 * @brief obtem o ano do voo
 * 
 * @param f flight
 * 
 * @return ano do voo
*/
int get_Ano_Voo(FLIGHT *f);

//n usada
void addAtraso(int *arr, int at, int n);

/**
 * @brief obtem o numero de passageiros por voo
 * 
 * @param idFlight identificador do voo
 * @param passengers array dos passageiros
 * 
 * @return numero de passageiros do voo 
*/
int passageirosPorVoo(char * idflight , GArray *passengers);

//n usada
void insertion_Sort(int arr[], int n, int value);

/**
 * @brief funcao utilizada para verifcar se uma data é "antes ou depois" de outra
 * 
 * @param data1
 * @param date2
 * 
 * @return -1 se date1 mais recente que date2 / 1 se contrario
 *  
*/
int compare_dates(char * data1 , char * data2);

/**
 * @brief funcao utilizada para comprar o numero de passageiros por ano de aeroportos
 * 
 * @return -1 se date1 mais recente que date2 / 1 se contrario
 *  
*/
gint compareNPassageirosAno(gconstpointer a, gconstpointer b, gpointer userdata);

/**
 * @brief funcao utilizada para comparar a mediana 
 * 
 * @return resultado da comparação
 *  
*/
gint compareMediana(gconstpointer a, gconstpointer b);

/**
 * @brief funcao utilizada para comparar as datas dos flights, includindo horas 
 * 
 * @return resultado da comparação
 *  
*/
gint compare_flightswithHours(gconstpointer a, gconstpointer b);

/**
 * @brief funcao utilizada para libertar a chave de uma estrutra
*/
gboolean remove_keys(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief para realizar insertion sort no array de atrasos das airport_stats
 *
 * @param garray array dos atrasos
 * @param value valor a inserir
 *  
*/
void insertionSort_garray(GArray *garray, int value);

/**
 * @brief compara as datas de reservas e flights
 *
*/
int compare_flights_and_reservations(gconstpointer a, gconstpointer b);

/**
 * @brief verifica quantos dias dão "overlap" com uma certa data
 *  
 * @param start1 data inicial para comparação
 * @param end1 data final para comparação
 * @param start2 data inicial do voo
 * @param end2 data final do voo
 * 
 * @return dias overlaped
*/
int diasDentro(char* start1, char* end1, char* start2, char* end2);


/**
 * @brief funcao utilizada para verifcar se uma data é "antes ou depois" de outra, nao utilizando as horas
 * 
 * @param data1
 * @param date2
 * 
 * @return -1 se date1 mais recente que date2 / 1 se contrario
 *  
*/
int compareDatas (char * data1 , char * data2);

/**
 * @brief função para remover as aspas
 * 
 * @param stat string em que se vai remover as aspas
*/
void remove_quotes(char *stat);

/**
 * @brief verifica se uma string é prefixo
 * 
 * @param prefix prefixo
 * @param word string que vai ser verificada
*/
bool isPrefix(char *prefix, char *word);

/**
 * @brief função de comparação de usernames/nomes
 * 
 * @param a identificador de utilizador
 * @param b identificador de utilizador
 * @param user_data utilizadores
 * 
*/
int compareUsers(gconstpointer a, gconstpointer b, gpointer user_data);
#endif