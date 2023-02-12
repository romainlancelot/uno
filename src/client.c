// #include "include/client.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
// #include <unistd.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */

/* Fonctionnalité privée au module par le mot clé static */

/* Définistion des fonctionnalités annoncées par l'entête */

void startClient(char *ip, int port) {
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addServer;
    addServer.sin_addr.s_addr = inet_addr(ip);
    addServer.sin_family = AF_INET;
    addServer.sin_port = htons(port);

    connect(socketClient, (struct sockaddr *)&addServer, sizeof(addServer));
    printf("Connected\n");

    send(socketClient, "Hello", 5, 0);
}
