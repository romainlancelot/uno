#include <stdlib.h>
#include <stdio.h>


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