#include "../include/players.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */

/* Fonctionnalité privée au module par le mot clé static */

/* Définistion des fonctionnalités annoncées par l'entête */

// déclaration des joueurs
void creationJoueur (joueur *j, int nbJoueurs) {
  printf("Quel est le nom du joueur %d ? ", nbJoueurs+1);
  scanf("%s", j->nom);
  j->score = 0;
  j->nbCartes = 7;
  // piocher 7 cartes
  for (int i = 0; i < j->nbCartes; i++) {
    j->main[i] = pioche(0);
    supprCarteDePioche();
  }
}

// trier la main du joueur
void trierMain(joueur *j) {
  int i, x;
  carte temp;
  for (i = 0; i < j->nbCartes; i++) {
    for (x = i+1; x < j->nbCartes; x++) {
      if (strcmp(j->main[i].couleur, j->main[x].couleur) > 0) {
        temp = j->main[i];
        j->main[i] = j->main[x];
        j->main[x] = temp;
      }
      if (strcmp(j->main[i].couleur, j->main[x].couleur) == 0) {
        if (strcmp(j->main[i].valeur, j->main[x].valeur) > 0) {
          temp = j->main[i];
          j->main[i] = j->main[x];
          j->main[x] = temp;
        }
      }
    }
  }
}

void afficherMain(joueur *j) {
  trierMain(j);
  printf("\nCartes de %s :\n\n { ", j->nom);
  for (int i = 0; i < j->nbCartes; i++) {
    if (i == j->nbCartes-1) {
      printf("%d : ", i);
      afficher_carte(&j->main[i]);
      printf(" }\n");
      break;
    }
    printf("%d : ", i);
    afficher_carte(&j->main[i]);
    printf(" | ");
  }
  printf("\n");
}
