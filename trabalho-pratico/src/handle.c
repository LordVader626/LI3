#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>

#include "../inc/handle.h"
#include "../inc/queries.h"
#include "../inc/stats.h"

void handle(char *data_input, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers, CATALOGO_RESERVATIONS *cat_reservations, STATS *stats, CATALOGO_INVALID *cat_invalids, int mode){
     char *copy = NULL;
     size_t len;
     ssize_t read;
     int i;
     FILE * file ;
     file = fopen(data_input , "r");

     if(!file){
          perror("Erro ao abrir input");
          fclose(file);
          return;
     }
     int x = 0;
     for (i = 1; (read = getline(&copy, &len, file))!=-1; i++){
          char *line = copy;
          line[read-1] = '\0';
          char *query = strdup(strsep(&line, " "));
          char *path = malloc(100);

          sprintf(path, "Resultados/command%d_output.txt", i);        
          x++;

          handleQuery(query, line, path, cat_users, cat_flights, cat_passengers, cat_reservations, stats, cat_invalids, mode, x);

          free(query);
          free(path);
     }
     fclose(file);
     free(copy);
}

/*
     Função que executa as queries perante o seu input
     0 - normal
     1 - testes
*/
void handleQuery(char *query, char *line, char *path, CATALOGO_USER *cat_users, CATALOGO_FLIGHTS *cat_flights, CATALOGO_PASSENGER *cat_passengers, CATALOGO_RESERVATIONS *cat_reservations, STATS *stats, CATALOGO_INVALID *cat_invalids, int mode, int nQuery) {

     clock_t start, end;

     start = clock();

     switch(query[0]-'0'){ 
          case 1:
               if(strcmp(query, "10") == 0|| strcmp(query, "10F") == 0) break;
               if (strcmp(query, "1F") == 0) query1(cat_reservations, cat_users, cat_flights, cat_passengers,line, 1, path, stats);                        
               else query1 (cat_reservations, cat_users, cat_flights, cat_passengers, line, 0, path, stats);
               break;
          case 2:
               if (strcmp(query, "2F") == 0) query2(cat_reservations, cat_users, cat_flights, cat_passengers,line, 1, path, stats, cat_invalids);                       
               else query2(cat_reservations, cat_users, cat_flights, cat_passengers,line, 0, path, stats, cat_invalids);
               break;
          case 3:
               if (strcmp(query, "3F") == 0) query3(cat_reservations,line, 1, path, stats);                        
               else query3(cat_reservations,line, 0, path, stats);
               break;
          case 4:
               if (strcmp(query, "4F") == 0) query4(line, 1, path, stats);                        
               else query4(line, 0, path, stats);
               break;
          case 5:
               if (strcmp(query, "5F") == 0) query5(line, 1, path, stats);                     
               else query5(line, 0, path, stats);
               break;
          case 6:
               if (strcmp(query, "6F") == 0) query6(line, 1, path, stats);                     
               else query6(line, 0, path, stats);
               break;
          case 7:
               if (strcmp(query, "7F") == 0) query7(line, 1,path, stats);                      
               else query7(line, 0,path, stats);    
               break;
          case 8:
               if (strcmp(query, "8F") == 0) query8(line, 1,path, stats, cat_reservations);                        
               else query8(line, 0,path, stats, cat_reservations);
               break;
          //case 9:
               //   if (strcmp(query, "9F"))  query9(line, 1, path, cat_users);                        
               // else query9(line, 1, path, cat_users);
               //break;
          //case 10:
               //    if (strcmp(query, "8F")) query10(catalogo,line, 1);                        
               //  else query10(catalogo, 0);
               //break;
     
     }

     end = clock();

     double tempo_query = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;

     //printf("Query number: %d\n", x);
     if (mode == 1)
          printf("Query %d time: %f milliseconds\n", nQuery, tempo_query);
     //free(path);
}