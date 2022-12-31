#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct carte {
  char valeur[10];
  char couleur[10];
};

char *valeurs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};

int rang; //rang du tableau contenant les cartes
int taillePioche = 108; //nb total de carte dans la pioche en début de partie
struct carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().


void creer_jeu() {
  int quatuor, paire, i, j;
  int ind = 0;
  
  //creation des cartes uniques par coueleur pour les 0 (c'est les règles officielles cherchez pas a comprendre j'ai suffisemment galerer a cause de cette connerie)
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      strcpy(jeu[ind].valeur, valeurs[i]);
      strcpy(jeu[ind].couleur, couleurs[j]);
      ind++;
    }
  }
  //creation des paires par couleurs pour ls cartes allant de 1 a 9, pour les +2, les inversion et les skip
  for (paire = 0; paire < 2; paire++) {
    for (i = 1; i < 13; i++) {
      for (j = 0; j < 4; j++) {
        strcpy(jeu[ind].valeur, valeurs[i]);
        strcpy(jeu[ind].couleur, couleurs[j]);
        ind++;
      }
    }
  }
  //création des quators pour les +4 et les changement de couleur
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

// fonction pour une carte aléatoire
int aleatoire(int *taillePioche) {
  // Initialisation du générateur de nombres aléatoires
  srand(time(NULL));
  // Génération d'un nombre aléatoire compris entre 0 et la taille de la pioche ( inclus)
  int indice_aleatoire = rand() % (*taillePioche);
  (*taillePioche) = (*taillePioche) -1;
  //taillePioche == taillePioche -1;
  return indice_aleatoire;
}

// print la carte
int afficher_carte(struct carte c) {
  printf("%s %s\n", c.valeur, c.couleur);
}

int supprCarteDePioche() {
  // copie colle le tableau des cartes dans la pioche en enlevant l'élément pioché
  int j = 0;
  for (int i = 0; i < (taillePioche+1); i++) {
    if (i == rang) continue; // ignore l'élément rang
    jeu[j] = jeu[i];
    j++;
  }
}

int pioche() {
  // récupère un nb aléatoire
  rang = aleatoire(&taillePioche);
  // Affichage de la carte à l'indice généré aléatoirement
  afficher_carte(jeu[rang]);
  // supprime la carte pioché de la pioche
  supprCarteDePioche();
  // print la taille de la pioche restante
  //printf("\n%d\n", taillePioche);
  return rang;
}

int main() {
  creer_jeu();
  pioche();
  //printf("%d\n", rang);

  // Affichez chaque élément du nouveau tableau (vérifier que l'ancienne carte est plus dedans)
  //for (int i = 0; i < (taillePioche); i++) {
  //printf("jeu[%d] = %s %s\n", i, jeu[i].valeur, jeu[i].couleur);
  //}

  return 0;
}
