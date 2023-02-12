#ifndef DEF_HEADER_SERVER
#define DEF_HEADER_SERVER

/* Protection du module */
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */
// typedef struct {
//     struct sockaddr_in address;
//     int sockfd;
//     int uid;
//     char name[32];
// } client_t;

/* Variables publiques du module */

/* Fonctionnalités publiques du module */
extern int startServer(char *ip, int port);
extern int connectClients(int socketServer, int nbClients);

#endif