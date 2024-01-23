#ifndef interativo_h
#define interativo_h

typedef struct pages PAGES;

#include <ncurses.h>

/**
 * @brief pequeno ecra a informar que o dataset está loading
 */
void showLoading(WINDOW *menuWin);

/**
 * @brief Função para determinar o numero de linhas de um ficheiro.
 * 
 * @param path caminho para o ficheiro que contem os dados
 * 
 * @return numero de linhas
 */
int nLines(char *path);

/**
 * @brief menu a mostrar a query
 */
int showQuery(WINDOW *menuWin);

/**
 * @brief funcao que faz o loading dos dados
 * 
 * @param second_word identificados que irá ser necessário para a criação das stats
 * @param full_query query
 * @param query_type numero da query
 * @param dataset path para o dataset
 */
void load(WINDOW *menuWin, char *second_word, char *full_query, char *queryType, char *dataset);

/**
 * @brief pequeno ecra a informar que o dataset está loading
 */
void runQuery(WINDOW *menuWin, char *dataset);

/**
 * @brief menu informção
 */
int showHelp(WINDOW *menuWin);

/**
 * @brief menu principal
 */
void mainMenu(WINDOW *menuWin, char *dataset);
void interativo();

#endif