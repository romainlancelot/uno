#include <stdlib.h>
#include <stdio.h>


int main() {
    int choice;
    printf("==================================\n|| Bienvenue dans le jeu de UNO ||\n==================================\n\n");
    printf("Que voulez-vous faire ?\n");
    printf("\t1) Lancer une nouvelle partie\n");
    printf("\t2) Reprendre une partie existante à partir d'un fihcier de sauvegarde\n");
    printf("\t3) Quitter\n"),
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
            printf("\nA bientôt !\n");
            exit(EXIT_SUCCESS);
        default :
            printf("Choix invalide.\n");
            exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}