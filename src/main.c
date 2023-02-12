#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/display_standars.h"
#include "include/cards.h"
#include "include/players.h"
#include "include/server.h"
#include "include/client.h"

int main() {
	int i;
	creer_jeu();
		
	CLEAR_SCREEN;
	FILE * fichier = NULL;
	if ((fichier = fopen("text/welcome.txt", "r")) == NULL) {
		printf("Impossible d'ouvrir le fichier welcome.txt\n");
		exit(EXIT_FAILURE);
	} else {
		char c;
		while((c = fgetc(fichier)) != EOF) {
			printf("%c", c);
		}
		fclose(fichier);
		fichier = NULL;
	}

	int choice;
    printf("==================================\n|| Bienvenue dans le jeu de UNO ||\n==================================\n\n");
    printf("Que voulez-vous faire ?\n");
    printf("\t1) Lancer une nouvelle partie\n");
    printf("\t2) Voir les règles du jeu\n");
    printf("\t3) Quitter\n"),
    printf("Votre choix : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1 :
            printf("\n=== Début d'une nouvelle partie ===\n");
			printf("Voulez-vous jouer sur le même ordinateur ou sur en réseau ?\n");
			printf("\t1) Même ordinateur\n");
			printf("\t2) En réseau\n");
			printf("Votre choix : ");
			scanf("%d", &choice);
			switch(choice) {
				case 1 :
					printf("\n=== Même ordinateur ===\n");
					break;
				case 2 :
					printf("\n=== En réseau ===\n");
					printf("Voulez-vous être le serveur ou le client ?\n");
					printf("\t1) Serveur\n");
					printf("\t2) Client\n");
					printf("Votre choix : ");
					scanf("%d", &choice);
					char ip[16];
					int port;
					switch(choice) {
						case 1 :
							printf("\n=== Serveur ===\n");
							printf("Entrez l'adresse IP du serveur : ");
							scanf("%s", ip);
							printf("Entrez le port du serveur : ");
							scanf("%d", &port);
							int socketServer = startServer(ip, port);
							connectClients(socketServer, 1);
							break;
						case 2 :
							printf("\n=== Client ===\n");
							printf("Entrez l'adresse IP du serveur : ");
							scanf("%s", ip);
							printf("Entrez le port du serveur : ");
							scanf("%d", &port);
							startClient(ip, port);
							break;
						default :
							printf("Choix invalide.\n");
							exit(EXIT_FAILURE);
					}
				default :
					printf("Choix invalide.\n");
					exit(EXIT_FAILURE);
			}
			break;
        case 2 :
            printf("\n=== Règles du jeu ===\n");
            FILE * fichier = NULL;
            if((fichier = fopen("text/rules.txt", "r")) == NULL) {
                printf("Impossible d'ouvrir le fichier rules.txt\n");
                exit(EXIT_FAILURE);
            } else {
                char c;
                while((c = fgetc(fichier)) != EOF) {
                    printf("%c", c);
                }
                fclose(fichier);
                fichier = NULL;
            }
            break;
        case 3 :
            printf("\nA bientôt !\n");
            exit(EXIT_SUCCESS);
        default :
            printf("Choix invalide.\n");
            exit(EXIT_FAILURE);
    }

	//Déclarez un joueur
	char tmpNbJoueur[2];
	int nbJoueur=0;
	do {
		printf("\nBienvenue !\n\nCombien y'a t'il de joueurs ? ");
		scanf("%s", tmpNbJoueur);
		// vérifier que le caractere est bien un chiffre
		nbJoueur = atoi(tmpNbJoueur);
		if (nbJoueur < 2 || nbJoueur > 4) {
			printf("Nombre de joueurs invalide (entre 2 et 4 joueurs)\n");
		}
	} while (nbJoueur < 2 || nbJoueur > 4);

	joueur joueurs[nbJoueur];
	for (i=0; i < nbJoueur; i++) {
		CLEAR_SCREEN;
		creationJoueur(&joueurs[i], i);
	}
	CLEAR_SCREEN;
	for (i=0; i < nbJoueur; i++) {
		printf("Joueur %d : %s !\n", i+1, joueurs[i].nom);
		printf("Votre score est de %d\n", joueurs[i].score);
		afficherMain(&joueurs[i]);
		if(i != nbJoueur-1) {
		SEPARATEUR;
		} else {
			printf("\n\n");
		}
	}

	do {
		printf("Appuyez sur entrée pour commencer la partie\n");
		getchar();
	} while (getchar() != '\n');

	CLEAR_SCREEN;

	initTapis();

	CLEAR_SCREEN;

	int skipTurn = 0; //permet de vérifier si un joueur doit skip son tour
	int inversion = 0; //permet de vérifier le sens du tour
	int draw = 0; //permet de vérifier si un joueur doit piocher une carte

	do {
		for (i=0; i < nbJoueur;) {
			if (skipTurn == 1) {
				skipTurn = 0;
				if (inversion % 2 == 0) {
					i++;
					i = i%nbJoueur;
				} else {
					i--;
					i = i%nbJoueur;
					if (i < 0) {
						i = nbJoueur + i;
					}
				}
				continue;
			}

			if (draw != 0) {
				printf("Voici vos %d cartes :\n", draw);
				printf(" { ");
				for (int j = 0; j < draw; j++) {
					carte c = piocheCarte(&joueurs[i]);
					if (j == draw-1) {
						printf("%d : ", j);
						afficher_carte(&c);
						printf(" }\n");
						break;
					}
					printf("%d : ", j);
					afficher_carte(&c);
					printf(" | ");
				}
				printf("\n");
				draw = 0;
			}

			printf("Tour de joueur %d : %s !\n", i+1, joueurs[i].nom);
			afficherMain(&joueurs[i]);

			printf("\nCarte du tapis : ");
			afficher_carte(&tapis[1]);

			// //la meme avec la défausse
			// for (int x = 0; x < 108; x++) {
			//   printf("defausse[%d] = %s %s\n", x, defausse[x].valeur, defausse[x].couleur);
			// }

			// // supprime la carte pioché de la pioche
			// for (int x = 0; x < 108; x++) {
			//   printf("jeu[%d] = %s %s\n", x, jeu[x].valeur, jeu[x].couleur);
			// }

			printf("\n\n");
			int playSuccess = 0;
			do {
				playSuccess = joueurJoue(&joueurs[i], i+1, tapis, &skipTurn, &inversion, &draw);
			} while (playSuccess != 1);

			if (inversion % 2 == 0) {
				i++;
				i = i%nbJoueur;
			} else {
				i--;
				i = i%nbJoueur;
				if(i < 0){
					i = nbJoueur + i;
				}
			}
		}
	} while (joueurs[0].nbCartes != 0 || joueurs[1].nbCartes != 0 || joueurs[2].nbCartes != 0 || joueurs[3].nbCartes != 0);
	
	exit(EXIT_SUCCESS);
}