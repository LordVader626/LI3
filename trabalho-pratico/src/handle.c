#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/handle.h"
#include "../inc/queries.h"
#include "../inc/stats.h"


void handle(char *data_input, GHashTable *users, GHashTable *flights, GArray *passengers, GHashTable *reservations, STATS *stats) {
     char *line = NULL;
     size_t len;
     ssize_t read;
     int i;
     FILE * file ;
     file = fopen(data_input , "r");

     if(!file){
          perror("Erro ao abrir input");
     }

     for (i = 1; (read = getline(&line, &len, file))!=-1; i++){
          line[read-1] = '\0';
          char *query = strdup(strsep(&line, " "));;
          char *path = malloc(50);

          sprintf(path, "Resultados/command%d_output.txt\n", i);          

          switch( query[0]-'0'){ 
               case 1:
                    if (strcmp(query, "1F") == 0) query1(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats), get_flight_stats(stats));                        
                    else query1 (reservations, users, flights, passengers, line, 0, path, get_user_stats(stats), get_flight_stats(stats));
                    break;
               case 2:
                    if (strcmp(query, "2F") == 0) query2(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats));                        
                    else query2 (reservations, users, flights,passengers,line, 0, path, get_user_stats(stats));   
                    break;
             /*  case 3:
                    if (strcmp(query, "3F")) query3(catalogo,line, 1);                        
                    else query3(catalogo, 0);
                    break;
               case 4:
                    if (strcmp(query, "4F")) query4(catalogo,line, 1);                        
                    else query4 (catalogo, 0);
                    break;
               case 5:
                    if (strcmp(query, "5F")) query5(catalogo,line, 1);                        
                    else query5 (catalogo, 0);
                    break;
                case 6:
                    if (strcmp(query, "6F")) query6(catalogo,line, 1);                        
                    else query6 (catalogo, 0);
                    break;
               case 7:
                    if (strcmp(query, "7F")) query7(catalogo,line, 1);                        
                    else query7(catalogo, 0);
                    break;
               case 8:
                    if (strcmp(query, "8F")) query8(catalogo,line, 1);                        
                    else query8(catalogo, 0);
                    break;
                case 9:
                    if (strcmp(query, "7F")) query9(catalogo,line, 1);                        
                    else query9(catalogo, 0);
                    break;
               case 10:
                    if (strcmp(query, "8F")) query10(catalogo,line, 1);                        
                    else query10(catalogo, 0);
                    break;
                    */
               }
          free(path);
     }   
    int fclose(FILE* file);
}