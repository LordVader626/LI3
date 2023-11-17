#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "../inc/handle.h"
#include "../inc/queries.h"
#include "../inc/stats.h"

void handle(char *data_input, GHashTable *users, GHashTable *flights, GArray *passengers, GHashTable *reservations, STATS *stats, GHashTable *invalid_users) {
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
          switch( query[0]-'0'){ 
               case 1:
                    if(strcmp(query, "10") == 0|| strcmp(query, "10F") == 0) break;
                    if (strcmp(query, "1F") == 0) query1(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats));                        
                    else query1 (reservations, users, flights, passengers, line, 0, path, get_user_stats(stats));
                    break;
               case 2:
                    if (strcmp(query, "2F") == 0) query2(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats), invalid_users);                        
                    else query2 (reservations, users, flights,passengers,line, 0, path, get_user_stats(stats), invalid_users);   
                    break;
               case 3:
                    if (strcmp(query, "3F") == 0) query3(reservations,line, 1, path, get_hotel_stats(stats));                        
                    else query3(reservations,line, 0, path, get_hotel_stats(stats));
                    break;
               case 4:
                    if (strcmp(query, "4F") == 0) query4(line, 1, path, get_hotel_stats(stats));                        
                    else query4(line, 0, path, get_hotel_stats(stats));
                    break;
               case 5:
                    if (strcmp(query, "5F") == 0) query5(line, 1, path, get_airport_stats(stats));                     
                    else query5(line, 0, path, get_airport_stats(stats));
                    break;
               case 6:
                    if (strcmp(query, "6F") == 0) query6(line, 1, path, get_airport_stats(stats));                     
                    else query6(line, 0, path, get_airport_stats(stats));
                    break;
               case 7:
                    if (strcmp(query, "7F") == 0) query7(line, 1,path, get_airport_stats(stats));                      
                    else query7(line, 0,path, get_airport_stats(stats));    
                    break;
               case 8:
                    /*if (strcmp(query, "8F")) query8(catalogo,line, 1);                        
                    else query8(catalogo, 0);
                    break;*/
                case 9:
                    /*if (strcmp(query, "7F")) query9(catalogo,line, 1);                        
                    else query9(catalogo, 0);*/
                    break;
               case 10:
                    /*if (strcmp(query, "8F")) query10(catalogo,line, 1);                        
                    else query10(catalogo, 0);*/
                    break;
          
          }
          printf("Query number: %d\n", x);
          free(query);
          free(path);
     }
     free(copy);
     fclose(file);
}

/*void handle(char *data_input, GHashTable *users, GHashTable *flights, GArray *passengers, GHashTable *reservations, STATS *stats, GHashTable *invalid_users) {
     char *line = NULL;
     size_t len;
     ssize_t read;
     int i;
     FILE * file ;
     file = fopen(data_input , "r");

     if(!file){
          perror("Erro ao abrir input");
     }
     int x = 0;
     for (i = 1; (read = getline(&line, &len, file))!=-1; i++){
          line[read-1] = '\0';
          printf("%s\n", line);
          char *query = strdup(strsep(&line, " "));
          if(line != NULL) printf("%s\n", line);
          char *path = malloc(100);

          sprintf(path, "Resultados/command%d_output.txt\n", i);          
          x++;
          switch( query[0]-'0'){ 
               case 1:
                    if(strcmp(query, "10") == 0|| strcmp(query, "10F") == 0) break;
                    if (strcmp(query, "1F") == 0) query1(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats));                        
                    else query1 (reservations, users, flights, passengers, line, 0, path, get_user_stats(stats));
                    break;
               case 2:
                    if (strcmp(query, "2F") == 0) query2(reservations, users, flights,passengers,line, 1, path, get_user_stats(stats), invalid_users);                        
                    else query2 (reservations, users, flights,passengers,line, 0, path, get_user_stats(stats), invalid_users);   
                    break;
               case 3:
                    if (strcmp(query, "3F") == 0) query3(reservations,line, 1, path, get_hotel_stats(stats));                        
                    else query3(reservations,line, 0, path, get_hotel_stats(stats));
                    break;
               case 4:
                    if (strcmp(query, "4F") == 0) query4(line, 1, path, get_hotel_stats(stats));                        
                    else query4(line, 0, path, get_hotel_stats(stats));
                    break;
               case 5:
                    if (strcmp(query, "5F")) printf("not done\n");//query5(catalogo,line, 1);                        
                    else printf("not done\n");//query5 (catalogo, 0);
                    break;
               case 6:
                    /*if (strcmp(query, "6F")) query6(catalogo,line, 1);                        
                    else query6 (catalogo, 0);
                    break;
               case 7:
                    /*if (strcmp(query, "7F")) query7(catalogo,line, 1);                        
                    else query7(catalogo, 0);
                    break;
               case 8:
                    /*if (strcmp(query, "8F")) query8(catalogo,line, 1);                        
                    else query8(catalogo, 0);
                    break;
                case 9:
                    /*if (strcmp(query, "7F")) query9(catalogo,line, 1);                        
                    else query9(catalogo, 0);
                    break;
               case 10:
                    /*if (strcmp(query, "8F")) query10(catalogo,line, 1);                        
                    else query10(catalogo, 0);
                    break;
          
          }
          free(path); //confirm
          free(query);
          printf("Query number: %d\n", x);
          printf("MACACO\n");
     }
     //free(line);
     //line = NULL;
     fclose(file);
}*/