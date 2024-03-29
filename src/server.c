#include "include/server.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */
#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024
int isServer;
serverInfos partyServer;

/* Fonctionnalité privée au module par le mot clé static */
static void closeConnection(int socketServer) {
    close(socketServer);
}

/* Définition des fonctionnalités annoncées par l'entête */
void createServer() {
    printf("Entrez l'adresse IP du serveur : ");
    scanf("%s", partyServer.ip);
    printf("Entrez le port du serveur : ");
    scanf("%d", &partyServer.port);

    char tmpnbJoueurs[2];
    do {
        printf("\nCombien y'a t'il de joueurs ? ");
        scanf("%s", tmpnbJoueurs);
        // vérifier que le caractere est bien un chiffre
        nbJoueurs = atoi(tmpnbJoueurs);
        if (nbJoueurs < 2 || nbJoueurs > 4) {
            printf("Nombre de joueurs invalide (entre 2 et 4 joueurs)\n");
        }
    } while (nbJoueurs < 2 || nbJoueurs > 4);
    partyServer.nbClients = nbJoueurs;

    partyServer.socketServer = startServer(partyServer.ip, partyServer.port);
    int status = connectClients(partyServer.socketServer, partyServer.nbClients);
    if (status == 1) {
        printf("Tous les clients sont connectés\n");
    } else {
        printf("Erreur lors de la connexion des clients\n");
    }
}

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
        strcpy(joueurs[i].nom, buffer);
        joueurs[i].score = 0;
        joueurs[i].nbCartes = 7;
        joueurs[i].isBot = 0;
        // piocher 7 cartes
        for (int j = 0; j < joueurs[i].nbCartes; j++) {
            joueurs->main[j] = pioche(0);
            supprCarteDePioche(); 
        }
        send(socketClient, &joueurs[i], sizeof(joueurs[i]), 0);
    }

    return 1;
}
