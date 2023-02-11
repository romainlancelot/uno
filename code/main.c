#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/display_standars.h"
#include "src/actions.h"
#include "src/cards.h"
#include "src/players.h"


int main() {
  int i;
  creer_jeu();
    
  CLEAR_SCREEN;
  FILE * fichier = NULL;
  if ((fichier = fopen("./text/welcome.txt", "r")) == NULL) {
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