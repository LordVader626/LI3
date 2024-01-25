#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <glib.h>
#include <math.h>

#include "../inc/catalogo_flights.h"
#include "../inc/catalogo_invalids.h"
#include "../inc/catalogo_passenger.h"
#include "../inc/catalogo_reservations.h"
#include "../inc/catalogo_user.h"
#include "../inc/parser.h"
#include "../inc/stats.h"
#include "../inc/handle.h"
#include "../inc/interativo.h"

#define linesPerPage 12

void showLoading(WINDOW *menuWin) {
    werase(menuWin);
    box(menuWin, 0, 0);
    mvwprintw(menuWin, 0, 2, "Loading Dataset...");
    wrefresh(menuWin);
}

int nLines(char *path) {
    FILE *file = fopen(path, "r");
    
    if (file == NULL) {
        perror("Error");
        return -1;
    }

    int lines = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

int showQuery(WINDOW *menuWin) {
    int currentPage = 1;

    FILE *file = fopen("Resultados/command_interactive_output.txt", "r");
    if (file == NULL) {
        return 1;
    }

    char **lines = NULL;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int totalLines = nLines("Resultados/command_interactive_output.txt");
    int totalPages = ceil((double)totalLines / linesPerPage);
    
    lines = (char **)malloc(totalLines * sizeof(char *));

    int i = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        lines[i] = strdup(line);
        i++;
    }

    int startLine, endLine;

    while(1){
        werase(menuWin);
        box(menuWin, 0, 0);

        //calcula a 1 linha da pagina
        startLine = (currentPage - 1) * linesPerPage;
        //ultima linha da pagina
        endLine = startLine + linesPerPage;

        for(int x = startLine; x < endLine && x < totalLines; x++){
            mvwprintw(menuWin, x - startLine + 1, 1, "%s", lines[x]);
        }

        mvwprintw(menuWin, 0, 1, "Page %d of %d", currentPage, totalPages);
        mvwprintw(menuWin, getmaxy(menuWin) - 1, (getmaxx(menuWin) - strlen("p - previous page / n - next page")) / 2, "p - previous page / n - next page");

        wrefresh(menuWin);

        int userInput = getch();

        switch (userInput){
            case 'n':
                if(currentPage < totalPages){
                    currentPage++;
                }
                break;
            case 'p':
                if(currentPage > 1){
                    currentPage--;
                }
                break;
            default:
                werase(menuWin);
                return 1;
        }
    }

    
    for (int x = 0; x < i; x++) {
        free(lines[x]);
    }

    free(line);
    free(lines);

    fclose(file);
}

void load(WINDOW *menuWin, char *second_word, char *full_query, char *queryType, char *dataset) {
    wclear(menuWin);
    showLoading(menuWin);

    CATALOGO_USER *cat_users = create_Catalogo_User();
    CATALOGO_FLIGHTS *cat_flights = create_Catalogo_flights();
    CATALOGO_PASSENGER *cat_passengers = create_catalogo_Passenger();
    CATALOGO_RESERVATIONS *cat_reservations = create_Catalogo_Reservations();
    CATALOGO_INVALID *cat_invalids = create_Catalogo_invalids();

    STATS *stats = create_stats();
    addStatNeeded(stats, second_word);

    wrefresh(menuWin);

    parse_files_users_teste(dataset, cat_users, cat_invalids);
    mvwprintw(menuWin, 1, 1, "Parsing users complete");
    wrefresh(menuWin);

    parse_files_flights_teste(dataset, cat_flights, stats, cat_invalids);
    mvwprintw(menuWin, 2, 1, "Parsing flights complete");
    wrefresh(menuWin);

    parse_files_passengers_teste(dataset, stats, cat_passengers, cat_users, cat_flights, cat_invalids);
    mvwprintw(menuWin, 3, 1, "Parsing passengers complete");
    wrefresh(menuWin);

    parse_files_reservations_test(dataset, stats, cat_reservations, cat_users, cat_invalids);
    mvwprintw(menuWin, 4, 1, "Parsing reservations complete");
    wrefresh(menuWin);

    handleQuery(queryType, full_query, "Resultados/command_interactive_output.txt", cat_users, cat_flights, cat_passengers, cat_reservations, stats, cat_invalids, 0, 0);

    showQuery(menuWin);

    wclear(menuWin);
    mvwprintw(menuWin, 1, 1, "Data being cleared..");
    wrefresh(menuWin);
    destroy_catalogo_invalids(cat_invalids);
    destroy_catalogo_users(cat_users);
    destroy_catalogo_flights(cat_flights);
    destroy_catalogo_reservations(cat_reservations);
    destroy_catalogo_passengers(cat_passengers);
    destroy_stats(stats);
    mvwprintw(menuWin, 2, 1, "Data cleared");
    wrefresh(menuWin);

    wrefresh(menuWin);
    getch();
}


void runQuery(WINDOW *menuWin, char *dataset) {
    werase(menuWin);
    box(menuWin, 0, 0);
    mvwprintw(menuWin, 0, 2, "Write your Query");
    wrefresh(menuWin);
    echo();
    char query[100];
    mvwgetstr(menuWin, 1, 1, query);
    noecho();

    char *token = strtok(query, " ");

    if (token != NULL) {
        char *second_word = strtok(NULL, " ");
        if (second_word != NULL) {
            char *resto = strtok(NULL, "\0");
                    
            if (resto != NULL) {
                char *full_query = malloc(strlen(second_word) + strlen(resto) + 1);

                strcpy(full_query, second_word);
                strcat(full_query, " ");
                strcat(full_query, resto);
                wclear(menuWin);
                wrefresh(menuWin);

                load(menuWin, second_word, full_query, token, dataset);
            }

            else{
                load(menuWin, second_word, second_word, token, dataset);
            }
        }
    } else {
        werase(menuWin);
        wprintw(menuWin, "Invalid format");
        wrefresh(menuWin);
        wgetch(menuWin);
    }
}
int showHelp(WINDOW *menuWin) {
    noecho();
    int page = 1;
    int totalPages = 10;

    while (1) {
        werase(menuWin);
        box(menuWin, 0, 0);
        mvwprintw(menuWin, 0, 2, " Query %d ", page);

        switch (page) {
            case 1:
                mvwprintw(menuWin, 1, 1, "Query 1 - List the summary of a user, flight, or reservation.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 1 <ID>");
                mvwprintw(menuWin, 4, 1, "If the ID is from a user the output will be:");
                mvwprintw(menuWin, 5, 1, "name;sex;age;country_code;number_of_fights;number_of_reservations;total_spent");
                mvwprintw(menuWin, 7, 1, "If the ID is from a flight the output will be:");
                mvwprintw(menuWin, 8, 1, "airline;plane_model;origin;destination;schedule_departure_date;schedule_arrival_date;passengers;delay");
                mvwprintw(menuWin, 10, 1, "If the ID is from a reservation the output will be:");
                mvwprintw(menuWin, 11, 1, "hotel_id;hotel_name;hotel_stars;begin_date;end_date;includes_breakfast;nights;total_price");
                break;

            case 2:
                mvwprintw(menuWin, 1, 1, "Query 2 - List the flights or reservations of a user, if the second argument is flights or reservations, respectively, sorted by date,");
                mvwprintw(menuWin, 2, 1, "if no argument is used, it will print both");
                mvwprintw(menuWin, 3, 1, "To use, select Run Query and write 2 <ID> [fights|reservations]");
                mvwprintw(menuWin, 5, 1, "The result will be:");
                mvwprintw(menuWin, 6, 1, "id;date[;type]");
                mvwprintw(menuWin, 7, 1, "id;date[;type]");
                mvwprintw(menuWin, 8, 1, "...");
                break;

            case 3:
                mvwprintw(menuWin, 1, 1, "Query 3 - Present the average rating of a hotel");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 3 <ID>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "rating");
                break;

            case 4:
                mvwprintw(menuWin, 1, 1, "Query 4 - List the reservations of a hotel, sorted by start date");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 4 <ID>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "id;begin_date;end_date;user_id;rating;total_price");
                mvwprintw(menuWin, 6, 1, "id;begin_date;end_date;user_id;rating;total_price");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            case 5:
                mvwprintw(menuWin, 1, 1, "Query 5 - List flights with origin at a given airport, between two dates, sorted by estimated departure date");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 5 <Name> <Begin_date> <End_date>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "id;schedule_departure_date;destination;airline;plane_model");
                mvwprintw(menuWin, 6, 1, "id;schedule_departure_date;destination;airline;plane_model");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            case 6:
                mvwprintw(menuWin, 1, 1, "Query 6 - List the top N airports with the most passengers for a given year.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 6 <Year> <N>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "name;passengers");
                mvwprintw(menuWin, 6, 1, "name;passengers");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            case 7:
                mvwprintw(menuWin, 1, 1, "Query 7 - List the top N airports with the highest median delays.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 7 <N>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "name;median");
                mvwprintw(menuWin, 6, 1, "name;median");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            case 8:
                mvwprintw(menuWin, 1, 1, "Query 8 - Present the total revenue of a hotel between two dates.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 8 <Id> <Begin_date> <End_date>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "revenue");
                break;
            case 9:
                mvwprintw(menuWin, 1, 1, "Query 9 -  List all users whose name starts with the prefix passed as an argument, sorted by name.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 9 <Prefx>");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "id;name");
                mvwprintw(menuWin, 6, 1, "id;name");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            case 10:
                mvwprintw(menuWin, 1, 1, "Query 10 - Present various general metrics of the application.");
                mvwprintw(menuWin, 2, 1, "To use, select Run Query and write 10 [year [month]]");
                mvwprintw(menuWin, 4, 1, "The result will be:");
                mvwprintw(menuWin, 5, 1, "year|month|day);users;fights;passengers;unique_passengers;reservations");
                mvwprintw(menuWin, 6, 1, "year|month|day);users;fights;passengers;unique_passengers;reservations");
                mvwprintw(menuWin, 7, 1, "...");
                break;
            default:
                break;
        }

        mvwprintw(menuWin, getmaxy(menuWin) - 1, (getmaxx(menuWin) - strlen("p - previous page / n - next page")) / 2, "p - previous page / n - next page");

        wrefresh(menuWin);

        int userInput = getch();

        switch (userInput) {
            case 'n':
                if (page < totalPages) {
                    page++;
                }
                break;
            case 'p':
                if (page > 1) {
                    page--;
                }
                break;
            default:
                werase(menuWin);
                return 1; // menu atras
        }
    }
}

void mainMenu(WINDOW *menuWin, char *dataset) {
    keypad(menuWin, true);
    char *choices[] = {"Run Query", "Help", "Exit"};
    int choice;
    int highlight = 0;

    while (1) {
        wclear(menuWin);

        for (int i = 0; i < 3; i++) {
            if (i == highlight)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, i + 1, 1, "%s", choices[i]);
            wattroff(menuWin, A_REVERSE);
        }
        wrefresh(menuWin);

        choice = wgetch(menuWin);

        switch (choice) {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            case 10:
                switch (highlight) {
                    case 0:
                        runQuery(menuWin, dataset);
                        break;
                    case 1:
                        if (showHelp(menuWin))
                            break;
                        break;
                    case 2:
                        endwin(); 
                        exit(0);
                }
                werase(menuWin);
                wrefresh(menuWin);
                break;
            default:
                break;
        }
        highlight = (highlight + 3) % 3;
    }
}

void interativo() {
    initscr();
    cbreak();

    int y, x;
    getmaxyx(stdscr, y, x);

    WINDOW *menu = newwin(15, x - 12, y - 30, 5);
    box(menu, 0, 0);

    mvwprintw(menu, 1, 2, "Input the dataset path: ");
    refresh();
    wrefresh(menu);

    // colocar o "cursor" a frente da mensagem
    wmove(menu, 1, strlen("Input the dataset path: ") + 2);

    char user_input[100];
    wgetstr(menu, user_input);

    werase(menu);
    wrefresh(menu);

    mainMenu(menu, user_input);

    endwin();
}