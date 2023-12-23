#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void start_stats_needed(GHashTable *stats_needed, char *data_input) {
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
        line[read - 1] = '\0'; // Remove the newline character

        char *first_word = strtok(line, " "); // Tokenize by space

        if (first_word != NULL) {
            char *second_word = strtok(NULL, " "); // Get the second token
            if (second_word != NULL) {
                printf("%s\n", second_word);
                g_hash_table_insert(stats_needed, strdup(second_word), strdup(second_word));
            }
        }
    }

    free(line);
    fclose(input);
}


        //QUERY 1 SO SACAR O 1 INPUT
        //QUERY 2 UTILIZADOR NECESSARIO SO INTERESSA 1 CAMPO
        //QUERY 3 IMPORTA HOTEL ID (DAS RESERVAS)
        //QUERY 4 IMPORTA HOTEL ID (DAS RESERVAS)

        // PARA OS VOOS TEM DE SER TODOS
        //QUERY 5 IMPORTA CAMPO ORIGIN (DOS VOOS)
        //QUERY 6 IMPORTA CAMPO ORIGEM E DESTINO DOS VOOS

        //QUERY 8 IMPORTA HOTEL ID