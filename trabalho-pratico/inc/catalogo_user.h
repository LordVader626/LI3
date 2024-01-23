#ifndef catalogo_user_h
#define catalogo_user_h

#include <glib.h>

struct user;
typedef struct user USER;

typedef struct cat_user CATALOGO_USER;

/**
 * @brief Função de criação de catalogo.
 * 
 * Esta função cria o catalogo relacionado aos utilizadores
 * 
 * @return pointer para a estrutura de catalogo criada
 */

CATALOGO_USER *create_Catalogo_User();

/**
 * @brief função para obter o catalogo dos utilizadores.
 * 
 * @param catu apontador para o catalogo de utilizadores
 */
GHashTable *get_Catalogo_User(CATALOGO_USER * catu);

/**
 * @brief função para obter um utilizador.
 * 
 * Esta função é usada obter um utilizador do seu catalogo.
 * 
 * @param catr apontador para o catalogo de utilizadores.
 * @param id id do user.
 */
USER * getUser(CATALOGO_USER *catu, char *id);

/**
 * @brief função para adicionar um utilizador.
 * 
 * Esta função é usada adicionar um utilizador ao seu catalogo.
 * 
 * @param catu apontador para o catalogo de utilizadores.
 * @param id id do utilizador.
 * @param f apontador para o user.
 */
void addUser(CATALOGO_USER *catu, char *id, USER *u);

/**
 * @brief função para libertar a memoria do catalogo de utilizadores.
 * 
 * @param cat_users apontador para o catalogo de utilizadores.
 */
void destroy_catalogo_users(CATALOGO_USER *cat_users);

/**
 * @brief função para adicionar verificar se um utilizador se encontra no catalogo.
 * 
 * @param cat_users apontador para o cat de utilizadores
 * @param userID id do utilizador
 * 
 * @return if the user exists
 */
int cointains_user(CATALOGO_USER *cat_users, char *userID);

#endif