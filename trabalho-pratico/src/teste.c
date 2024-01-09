#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../inc/stats.h"

void start_stats_needed(STATS *stats, char *data_input) {
    FILE *input;
    input = fopen(data_input, "r");

    if (input == NULL) {
        printf("Error opening file\n");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, input)) != -1) {
        line[read - 1] = '\0';

        char *first_word = strtok(line, " ");

        if (first_word != NULL) {
            char *second_word = strtok(NULL, " ");
            if (second_word != NULL) {
                //printf("%s\n", second_word);
                //g_hash_table_insert(stats_needed, strdup(second_word), strdup(second_word));
                addStatNeeded(stats, strdup(second_word));
            }
        }
    }

    free(line);
    fclose(input);
}


/*void remove_quotes(char *stat) {
    size_t length = strlen(stat);

    if (length >= 2 && stat[0] == '"' && stat[length - 1] == '"') {
        for (size_t i = 0; i < length - 1; i++) {
            stat[i] = stat[i + 1];
        }
        stat[length - 2] = '\0';
    }
}

void start_stats_needed(STATS *stats, char *data_input) {
    FILE *input;
    input = fopen(data_input, "r");

    if (input == NULL) {
        printf("Error opening file\n");
        return;
    }

    GHashTable *stats_needed = get_stats_needed(stats);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, input)) != -1) {
        line[read - 1] = '\0';

        char *first_word = strtok(line, " ");
        char *second_word = strtok(NULL, "\"");

        //third_word por causa da query de predicados / 3 query
        if (first_word != NULL && second_word != NULL) {
            if (first_word[0] == '9') {
                remove_quotes(second_word);
                //printf("%s\n", second_word);
                g_hash_table_insert(stats_needed, strdup(second_word), strdup(second_word));
            } else {
                char *third_word = strtok(NULL, "\"");
                if (third_word != NULL && third_word[0] == '"' && second_word[0] == '"') {
                    remove_quotes(second_word);
                    //printf("%s\n", strcat(second_word, " "));
                    //printf("%s\n", third_word);
                    g_hash_table_insert(stats_needed, strdup(strcat(second_word, third_word)), strdup(strcat(second_word, third_word)));
                } else {
                    remove_quotes(second_word);
                    //printf("%s\n", second_word);
                    g_hash_table_insert(stats_needed, strdup(second_word), strdup(second_word));
                }
            }
        }
    }

    free(line);
    fclose(input);
}*/

        //QUERY 1 SO SACAR O 1 INPUT
        //QUERY 2 UTILIZADOR NECESSARIO SO INTERESSA 1 CAMPO
        //QUERY 3 IMPORTA HOTEL ID (DAS RESERVAS)
        //QUERY 4 IMPORTA HOTEL ID (DAS RESERVAS)

        // PARA OS VOOS TEM DE SER TODOS
        //QUERY 5 IMPORTA CAMPO ORIGIN (DOS VOOS)
        //QUERY 6 IMPORTA CAMPO ORIGEM E DESTINO DOS VOOS

        //QUERY 8 IMPORTA HOTEL ID