#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct carte {
  char valeur[10];
  char couleur[10];
};

char *valeurs[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};

struct carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().

void creer_jeu() {
  int quatuor, paire, i, j;
  int ind = 0;

  for (paire = 0; paire < 2; paire++) {
    for (i = 0; i < 13; i++) {
      for (j = 0; j < 4; j++) {
        strcpy(jeu[ind].valeur, valeurs[i]);
        strcpy(jeu[ind].couleur, couleurs[j]);
        ind++;
      }
    }
  }
  for (quatuor = 1; quatuor < 5; quatuor++) {
    for (i = 13; i < 15; i++) {
      for (j = 4; j < 5; j++) {
        strcpy(jeu[ind].valeur, valeurs[i]);
        strcpy(jeu[ind].couleur, couleurs[j]);
        ind++;
      }
    }
  }
}

void afficher_carte(struct carte c) {
  printf("%s %s", c.valeur, c.couleur);
}

int main() {
  creer_jeu();
  int i;
  for (i = 0; i < 120; i++) {
    afficher_carte(jeu[i]);
    printf("\n");
  }
  return 0;
}
