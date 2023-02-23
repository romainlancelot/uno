#include "include/client.h"
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

/* Fonctionnalité privée au module par le mot clé static */
static void closeConnection(int socketClient) {
    close(socketClient);
}

static void recupProfil(int socketClient) {
    joueur *joueur = malloc(sizeof(joueur));
    memset(joueur, 0, sizeof(joueur)); // Initialise tous les membres de la structure à zéro

    ssize_t bytesReceived = recv(socketClient, joueur, sizeof(*joueur), 0);
    if (bytesReceived == -1) {
        perror("Erreur de réception");
        exit(EXIT_FAILURE);
    } else if (bytesReceived != sizeof(*joueur)) {
        fprintf(stderr, "Erreur : taille de données reçues inattendue\n");
        exit(EXIT_FAILURE);
    }

    CLEAR_SCREEN;

    printf("Joueur : %s !\n", joueur->nom);
    printf("Votre score est de %d\n", joueur->score);
    afficherMain(joueur);
    
    free(joueur);
}

static void startClient(clientInfos *cli) {
    cli->socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addServer;
    addServer.sin_addr.s_addr = inet_addr(cli->ip);
    addServer.sin_family = AF_INET;
    addServer.sin_port = htons(cli->port);

    connect(cli->socketClient, (struct sockaddr *)&addServer, sizeof(addServer));
    printf("Connected\n");

    CLEAR_SCREEN;

    char nom[20];
    printf("Quel est votre nom ? ");
    scanf("%s", nom);

    send(cli->socketClient, nom, sizeof(nom), 0);

    recupProfil(cli->socketClient);
}

/* Définistion des fonctionnalités annoncées par l'entête */

void createClient(clientInfos *cli) {
    printf("Entrez l'adresse IP du serveur : ");
    scanf("%s", cli->ip);
    printf("Entrez le port du serveur : ");
    scanf("%d", &cli->port);

    startClient(cli);
    closeConnection(cli->socketClient);
}
