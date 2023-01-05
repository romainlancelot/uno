#include <stdlib.h>
#include <stdio.h>
// #include <game.h>




int main() {
    int choice;
    printf("==================================\n|| Bienvenue dans le jeu de UNO ||\n==================================\n\n");
    printf("Que voulez-vous faire ?\n");
    printf("\t1) Lancer une nouvelle partie\n");
    printf("\t2) Reprendre une partie existante à partir d'un fihcier de sauvegarde\n");
    printf("\t3) Voir les règles du jeu\n");
    printf("\t4) Quitter\n"),
    printf("Votre choix : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1 :
            printf("\n=== Début d'une nouvelle partie ===\n");
            int cartesTotal = 108;
            int cartesJoueur = 7;
            int cartesoOrdi = 7;
            int cartespioche = cartestotal - cartesjoueur - cartesordi;
            int cartesJoueesJoueur = 0;
            int cartesJoueesOrdi = 0;

            int cartesJoueur[cartesJoueur];
            int cartesOrdi[cartesOrdi];


            // Initialisation du jeu
            int jeu[cartesTotal];
            for (int i = 0; i < cartesTotal; i++) {
                jeu[i] = i;
            }

            // Mélange du jeu
            for (int i = 0; i < cartesTotal; i++) {
                int j = rand() % cartesTotal;
                int temp = jeu[i];
                jeu[i] = jeu[j];
                jeu[j] = temp;
            }

            // Distribution des cartes
            for (int i = 0; i < cartesJoueur; i++) {
                cartesJoueur[i] = jeu[i];
            }
            for (int i = 0; i < cartesOrdi; i++) {
                cartesOrdi[i] = jeu[i + cartesJoueur];
            }

            // Affichage des cartes du joueur
            printf("Voici vos cartes :\n");
            for (int i = 0; i < cartesJoueur; i++) {
                printf("\t%d\n", cartesJoueur[i]);
            }

            // Affichage des cartes de l'ordinateur
            printf("Voici les cartes de l'ordinateur :\n");
            for (int i = 0; i < cartesOrdi; i++) {
                printf("\t%d\n", cartesOrdi[i]);
            }

            // Affichage des cartes restantes
            printf("Il reste %d cartes dans la pioche\n", cartespioche);

            // Affichage des cartes jouées
            printf("Il y a %d cartes jouées par le joueur\n", cartesJoueesJoueur);
            printf("Il y a %d cartes jouées par l'ordinateur\n", cartesJoueesOrdi);

            // Affichage du jeu
            printf("Voici le jeu :\n");
            for (int i = 0; i < cartesTotal; i++) {
                printf("\t%d\n", jeu[i]);
            }

            break;
        case 2 :
            printf("\n=== Reprise d'une partie à partir d'un fichier de sauvegarde ===\n");
            printf("Cette fonctionnalité est en cours de développement, à bientôt !\n");
            exit(EXIT_SUCCESS);
        case 3 :
            printf("\n=== Règles du jeu ===\n");
            FILE * fichier = NULL;
            if((fichier = fopen("rules.txt", "r")) == NULL) {
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
        case 4 :
            printf("\nA bientôt !\n");
            exit(EXIT_SUCCESS);
        default :
            printf("Choix invalide.\n");
            exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}