#ifndef DEF_HEADER_CLIENT
#define DEF_HEADER_CLIENT

/* Protection du module */
#include "display_standars.h"
#include "players.h"
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */
typedef struct clientInfos {
    joueur joueur;
    char ip[16];
    int port;
    int socketClient;
} clientInfos;

/* Variables publiques du module */

/* Fonctionnalités publiques du module */
extern void createClient(clientInfos *cli);
extern void startClient(char *ip, int port);

#endif