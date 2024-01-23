#ifndef users_h
#define users_h

#include "../inc/catalogo_user.h"
#include "../inc/catalogo_invalids.h"

typedef struct user USER;

/**
 * @brief função para criação de um utilizador
 * 
 * @param line string que contem os dados do utilizador
 * 
 * @return utilizador criado
 */
USER *create_User(char *line);


/**
 * @brief função para libertar a memoria alocada de um utilizador
 * 
 * @param user Utilizador
 */
void kill_user(void*user);


/**
 * @brief getters
 * 
 * @param u utilizador
 * 
 * @return dado requisitado
 */
char *getID(USER *u);
char *getName(USER *u);
char *getEmail(USER *u);
char *getPhoneNumber(USER *u);
char *getBirthDate(USER *u);
char *getSex(USER *u);
char *getPassport(USER *u);
char *getCountryCode(USER *u);
char *getAddress(USER *u);
char *getAccountCreation(USER *u);
char *getPayMethod(USER *u);
char *getAccountStatus(USER *u);


/**
 * @brief função que inicia o processo de um user.
 *
 * Função que trata do processo de um user para criação, inserção, criação de estatisticas
 *  
 * @param line contem todos os detalhes de um user
 * @param cat_user catalogo de user
 * @param cat_invalids catalogo de dados invalidos
 * 
 * @return se o processo foi um sucesaso
 */
int start_user_process(char *line, CATALOGO_USER *cat_user, CATALOGO_INVALID *cat_invalids);

#endif