#ifndef stats_needed_h
#define stats_needed_h

#include <glib.h>
#include "../inc/stats.h"


/**
 * @brief função que inicia o verifica que identificadores irão necessitar de estatisticas.
 *
 * Esta função "itera" o ficheiro de input e guarda os identificares que encontra num hashtable, para facilitar a criação de estatisticas
 *  
 * @param stats catalogo de estatisticas
 * @param data_input path para os dados de input
 * 
 */
void start_stats_needed(STATS *stats, char *data_input);

#endif