#include "include/game.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

/* Autres inclusions */

/* Définition des variables globales relatives au module */

/* Fonctionnalité privée au module par le mot clé static */
static void printWelcome() {
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
}

static int game() {
	int skipTurn = 0; //permet de vérifier si un joueur doit skip son tour
	int inversion = 0; //permet de vérifier le sens du tour
	int draw = 0; //permet de vérifier si un joueur doit piocher une carte
	do {
		for (int i=0; i < nbJoueurs;) {
			if (skipTurn == 1) {
				skipTurn = 0;
				if (inversion % 2 == 0) {
					i++;
					i = i%nbJoueurs;
				} else {
					i--;
					i = i%nbJoueurs;
					if (i < 0) {
						i = nbJoueurs + i;
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
				i = i%nbJoueurs;
			} else {
				i--;
				i = i%nbJoueurs;
				if(i < 0){
					i = nbJoueurs + i;
				}
			}
		}
	} while (joueurs[0].nbCartes != 0 || joueurs[1].nbCartes != 0 || joueurs[2].nbCartes != 0 || joueurs[3].nbCartes != 0);
}

static void setPlayers() {
	CLEAR_SCREEN;
	char tmpnbJoueurs[2];
    if (isServer != 1) {
        do {
            printf("\nCombien y'a t'il de joueurs ? ");
            scanf("%s", tmpnbJoueurs);
            // vérifier que le caractere est bien un chiffre
            nbJoueurs = atoi(tmpnbJoueurs);
            if (nbJoueurs < 2 || nbJoueurs > 4) {
                printf("Nombre de joueurs invalide (entre 2 et 4 joueurs)\n");
            }
        } while (nbJoueurs < 2 || nbJoueurs > 4);
    }
	for (int i=0; i < nbJoueurs; i++) {
		CLEAR_SCREEN;
		creationJoueur(&joueurs[i], i);
	}
	CLEAR_SCREEN;
	for (int i=0; i < nbJoueurs; i++) {
		printf("Joueur %d : %s !\n", i+1, joueurs[i].nom);
		printf("Votre score est de %d\n", joueurs[i].score);
		afficherMain(&joueurs[i]);
		if(i != nbJoueurs-1) {
		SEPARATEUR;
		} else {
			printf("\n\n");
		}
	}
	CLEAR_SCREEN;
    game();
}


/* Définition des fonctionnalités annoncées par l'entête */
void printMenu() {
    int choice;
    printWelcome();
    printf("\n==================================\n|| Bienvenue dans le jeu de UNO ||\n==================================\n\n");
    printf("Que voulez-vous faire ?\n");
    printf("\t1) Lancer une nouvelle partie\n");
    printf("\t2) Voir les règles du jeu\n");
    printf("\t3) Quitter\n"),
    printf("Votre choix : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1 :
        	creer_jeu();
            initTapis();
            printf("\n=== Début d'une nouvelle partie ===\n");
			printf("Voulez-vous jouer sur le même ordinateur ou en réseau ?\n");
			printf("\t1) Même ordinateur\n");
			printf("\t2) En réseau\n");
			printf("Votre choix : ");
			scanf("%d", &choice);
			switch(choice) {
				case 1 :
                    isServer = 0;
					printf("\n=== Même ordinateur ===\n");
                    setPlayers();
					break;
				case 2 :
                    isServer = 1;
					printf("\n=== En réseau ===\n");
					printf("Voulez-vous être le serveur ou le client ?\n");
					printf("\t1) Serveur\n");
					printf("\t2) Client\n");
					printf("Votre choix : ");
					scanf("%d", &choice);
					switch(choice) {
						case 1 :
							printf("\n=== Serveur ===\n");
							createServer();
							break;
						case 2 :
							printf("\n=== Client ===\n");
							clientInfos cli;
							createClient(&cli);
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
}

void startParty(joueur joueurs[]) {
	printMenu();

    printf("Le serveur est lancé sur l'adresse %s:%d\n", partyServer.ip, partyServer.port);
    printf("Il y a %d joueurs dans la partie\n", nbJoueurs);
    do {
		printf("Appuyez sur entrée pour commencer la partie\n");
		getchar();
	} while (getchar() != '\n');
}
