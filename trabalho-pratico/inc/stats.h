#ifndef stats_h
#define stats_h

#include <glib.h>

typedef struct stats STATS;
/*

*/
struct user_stat;
typedef struct user_stat USER_STAT;
//GHashTable *get_user_stats(STATS *s);

/**
 * @brief função para obter a stat de um user
 * 
 * @param s catalogo de stats
 * @param user_id id do utilizador
 * 
 * @return estatistica do utilizador
 */
USER_STAT *get_stat_user(STATS *s, char *user_id);

/**
 * @brief função para adicionar a stat de um user
 * 
 * @param s catalogo de stats
 * @param ustat stat do utilizador
 * @param username id do utilizador
 */
void addUserStat (STATS *s, USER_STAT *ustat, char *username);

struct hotel_stat;
typedef struct hotel_stat HOTEL_STAT;

/**
 * @brief função para obter a stat de um hotel
 * 
 * @param s catalogo de stats
 * @param hotel_id id do hotel
 * 
 * @return estatistica do hotel
 */
HOTEL_STAT *get_stat_hotel(STATS *s, char *hotel_id);

/**
 * @brief função para adicionar a stat de um hotel
 * 
 * @param s catalogo de stats
 * @param hstat stat do hotel
 * @param hotel id do hotel
 */
void addHotelStat (STATS *s, HOTEL_STAT *hstat, char *hotel);
GHashTable *get_hotel_stats(STATS *s);

struct airport_stat;
typedef struct airport_stat AIRPORT_STAT;

/**
 * @brief função para obter a stat de um aeroporto
 * 
 * @param s catalogo de stats
 * @param airport_id id do aeroporto
 * 
 * @return estatistica do aeroporto
 */
AIRPORT_STAT *get_stat_airport(STATS *s, char *airport_id);

/**
 * @brief função para adicionar a stat de um aeroporto
 * 
 * @param s catalogo de stats
 * @param astat stat do aeroporto
 * @param airport id do aeroporto
 */
void addAirportStat (STATS *s, AIRPORT_STAT *astat, char *aiport);

/**
 * @brief função para retornar os valores da aeroport stats em Glist
 * 
 * @param s catalogo de stats
 * 
 * @return glist com os valores das airport_stats
 */
GList *get_airport_stats_values(STATS *s);
GHashTable *get_airport_stats(STATS *s);

/**
 * @brief função para adicionar uma string a hashtable de stats_needed
 * 
 * @param s catalogo de stats
 * @param key chave a ser inserida
 */
void addStatNeeded(STATS *s, char *key);
GHashTable *get_stats_needed(STATS *s);

/**
 * @brief função para criação do catalogo das stats
 * 
 * @return catalogo de stats
 */
STATS *create_stats();


/**
 * @brief verifica se existe estatistica para um certo identificador
 * 
 * @param stats catalogo de stats
 * @param keys identificador a ser procurado
 * 
 * @return se contem o stat
 */
int contains_stat(STATS *stats, char *key);
void destroy_stats_needed(STATS *stats);


/**
 * @brief função que liberta as estruturas de dados do catalogo de stats
 *  
 * @param stats catalogo de estatisticas
 * 
 */
void destroy_stats(void *stats);

#endif