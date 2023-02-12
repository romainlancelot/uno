// #include "include/server.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */
#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024

/* Fonctionnalité privée au module par le mot clé static */

/* Définistion des fonctionnalités annoncées par l'entête */

// void endConnection(int sockerClient, int socketServer) {
//     close(socketClient);
//     close(socketServer);
// }

int startServer(char *ip, int port) {
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addServer;
    addServer.sin_addr.s_addr = inet_addr(ip);
    addServer.sin_family = AF_INET;
    addServer.sin_port = htons(port);

    bind(socketServer, (struct sockaddr *)&addServer, sizeof(addServer));
    printf("Binded : %d\n", socketServer);

    listen(socketServer, MAX_CLIENTS);
    printf("Listening\n");

    return socketServer;
}

// fonction qui va attendre le nombre de clients indiquer et leur demander leur prénom
// puis les stocker dans un tableau de structure
// puis les envoyer à tous les clients
int connectClients(int socketServer, int nbClients) {
    int socketClient;
    struct sockaddr_in addClient;
    socklen_t sizeClient = sizeof(addClient);
    char buffer[BUFFER_SIZE];
    int i = 0;
    for (i = 0; i < nbClients; i++) {
        socketClient = accept(socketServer, (struct sockaddr *)&addClient, &sizeClient);
        printf("Connected : %d\n", socketClient);
        recv(socketClient, buffer, BUFFER_SIZE, 0);
        printf("Received : %s\n", buffer);
    }

    return 1;
}
