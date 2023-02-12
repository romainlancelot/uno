#ifndef DEF_HEADER_SERVER
#define DEF_HEADER_SERVER

/* Protection du module */
#include "display_standars.h"
#include "players.h"
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */
typedef struct serverInfos {
    joueur joueur;
    char ip[16];
    int port;
    int nbClients;
    int socketServer;
    int socketClients[];
} serverInfos;

/* Variables publiques du module */
extern struct serverInfos partyServer;
extern int isServer;

/* Fonctionnalités publiques du module */
extern void createServer();
extern int startServer(char *ip, int port);
extern int connectClients(int socketServer, int nbClients);

#endif