#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct carte {
  char valeur[10];
  char couleur[10];
} carte;

char *valeurs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};

int rang; //rang du tableau contenant les cartes
int taillePioche = 108; //nb total de carte dans la pioche en début de partie
carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().
carte defausse[108];
carte tapis[1];

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
int afficher_carte(carte c) {
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

struct carte pioche(int afficher) {
  // récupère un nb aléatoire
  rang = aleatoire(&taillePioche);
  carte cartePioche = jeu[rang];
  // Affichage de la carte à l'indice généré aléatoirement
  if (afficher == 1) {
    afficher_carte(cartePioche);
  }
  // supprime la carte pioché de la pioche
  supprCarteDePioche();
  //printf("\n%d\n", taillePioche);
  return cartePioche;
}

// déclaration des joueurs
typedef struct joueur {
  char nom[20];
  int score;
  carte main[108];
  int nbCartes;
} joueur;

void creationJoueur(joueur *j) {
  printf("Quel est votre nom ? ");
  scanf("%s", j->nom);
  printf("Bienvenue %s !\n", j->nom);
  j->score = 0;
  printf("Votre score est de %d\n", j->score);
  j->nbCartes = 7;
  // piocher 7 cartes
  for (int i = 0; i < j->nbCartes; i++) {
    j->main[i] = pioche(0);
  }
  // afficher sa main
  printf("Cartes de %s :\n { ", j->nom);
  for (int i = 0; i < j->nbCartes; i++) {
    if (i == j->nbCartes-1) {
      printf("%s %s }\n", j->main[i].valeur, j->main[i].couleur);
      break;
    }
    printf("%s %s | ", j->main[i].valeur, j->main[i].couleur);
  }
}

// joueur pose une carte
void poseCarte(joueur *j) {
  int choix;
  printf("Quelle carte voulez vous jouer ? ");
  scanf("%d", &choix);
  printf("Vous avez joué la carte %s %s\n", j->main[choix].valeur, j->main[choix].couleur);
  // supprime la carte joué de la main du joueur
  for (int i = choix; i < j->nbCartes; i++) {
    j->main[i] = j->main[i+1];
  }
  j->nbCartes--;
  // afficher sa main
  printf("Cartes de %s :\n { ", j->nom);
  for (int i = 0; i < j->nbCartes; i++) {
    if (i == j->nbCartes-1) {
      printf("%s %s }\n", j->main[i].valeur, j->main[i].couleur);
      break;
    }
    printf("%s %s | ", j->main[i].valeur, j->main[i].couleur);
  }
}

// joueur pioche une carte
void piocheCarte(joueur *j) {
  j->main[j->nbCartes] = pioche(0);
  j->nbCartes++;
  printf("Vous avez pioché la carte : %s %s\n", j->main[j->nbCartes-1].valeur, j->main[j->nbCartes-1].couleur);
  // afficher sa main
  printf("Cartes de %s :\n { ", j->nom);
  for (int i = 0; i < j->nbCartes; i++) {
    if (i == j->nbCartes-1) {
      printf("%s %s }\n", j->main[i].valeur, j->main[i].couleur);
      break;
    }
    printf("%s %s | ", j->main[i].valeur, j->main[i].couleur);
  }
}

int main() {
  creer_jeu();

  // Déclarez un joueur
  // int nbJoueur;
  // printf("Combien de joueurs ? ");
  // scanf("%d", &nbJoueur);
  printf("--------------------\n");
  joueur j1;
  creationJoueur(&j1);
  printf("--------------------\n");
  joueur j2;
  creationJoueur(&j2);
  printf("--------------------\n");

  poseCarte(&j1);
  printf("--------------------\n");
  piocheCarte(&j1);
  printf("--------------------\n");

  do {
    // tour du joueur 1
    poseCarte(&j1);
    printf("--------------------\n");
    printf("--------------------\n");
    // tour du joueur 2
    poseCarte(&j2);
    printf("--------------------\n");
  } while (j1.nbCartes != 0 || j2.nbCartes != 0);


  // Affichez chaque élément du nouveau tableau (vérifier que l'ancienne carte est plus dedans)
  //   for (int i = 0; i < (taillePioche); i++) {
  //  printf("jeu[%d] = %s %s\n", i, jeu[i].valeur, jeu[i].couleur);
  // }

  return 0;
}
