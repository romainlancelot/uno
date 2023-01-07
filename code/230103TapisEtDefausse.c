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
int rangDefausse = 1; //rang du tableau contenant les cartes défausse

int taillePioche = 108; //nb total de carte dans la pioche en début de partie
carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().
carte defausse[109];
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
int afficher_carte(carte *c) {
// char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};
  if (strcmp(c->couleur, "rouge") == 0) {
    printf("\033[0;31m%s %s\033[0m", c->valeur, c->couleur);
  } else if (strcmp(c->couleur, "jaune") == 0) {
    printf("\033[0;33m%s %s\033[0m", c->valeur, c->couleur);
  } else if (strcmp(c->couleur, "vert") == 0) {
    printf("\033[0;32m%s %s\033[0m", c->valeur, c->couleur);
    return 0; 
  } else if (strcmp(c->couleur, "bleu") == 0) {
    printf("\033[0;34m%s %s\033[0m", c->valeur, c->couleur);
    return 0;
  } else {
    printf("%s %s", c->valeur, c->couleur);
  }
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

//mets la carte du tapis dans la défausse
void tapisToDefausse() {
  defausse[rangDefausse] = tapis[1];
  //printf la carte défaussée
  //printf("\ndefausse %d : %s %s\n", rangDefausse, defausse[rangDefausse].valeur, defausse[rangDefausse].couleur);
  rangDefausse++;
}

//mets la carte piochée dans le tapis
void carteToTapis(){
    tapis[1] = jeu[rang];
    //printf la carte du tapis
    //printf("\n\ntapis : %s %s\n", tapis[1].valeur, tapis[1].couleur);
}

struct carte pioche(int afficher) {
  // récupère un nb aléatoire
  rang = aleatoire(&taillePioche);
  carte cartePioche = jeu[rang];
  // Affichage de la carte à l'indice généré aléatoirement
  if (afficher == 1) {
    printf("%s %s\n", cartePioche.valeur, cartePioche.couleur);
  }
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

void afficherMain(joueur *j) {
  printf("Cartes de %s :\n { ", j->nom);
  for (int i = 0; i < j->nbCartes; i++) {
    if (i == j->nbCartes-1) {
      afficher_carte(&j->main[i]);
      printf(" }\n");
      break;
    }
    afficher_carte(&j->main[i]);
    printf(" | ");
  }
}

void creationJoueur(joueur *j, int nbJoueurs) {
  printf("Quel est le nom du joueur %d ? ", nbJoueurs+1);
  scanf("%s", j->nom);
  // printf("Bienvenue %s !\n", j->nom);
  j->score = 0;
  // printf("Votre score est de %d\n", j->score);
  j->nbCartes = 7;
  // piocher 7 cartes
  for (int i = 0; i < j->nbCartes; i++) {
    j->main[i] = pioche(0);
  }
  // afficher sa main
  // afficherMain(j);
}

// joueur pose une carte
void poseCarte(joueur *j) {
  int choix;
  printf("Quelle carte voulez vous jouer ? ");
  scanf("%d", &choix);
  printf("Vous avez joué la carte ");
  afficher_carte(&j->main[choix]);
  printf("\n");
  //mets la carte en question dans le tapis
  strcpy(tapis[1].valeur, j->main[choix].valeur);
  strcpy(tapis[1].couleur, j->main[choix].couleur);
  //mets la carte du tapis dans la défausse
  tapisToDefausse();
  // supprime la carte joué de la main du joueur
  for (int i = choix; i < j->nbCartes; i++) {
    j->main[i] = j->main[i+1];
  }
  j->nbCartes--;
  // afficher sa main
  afficherMain(j);
}

// joueur pioche une carte
void piocheCarte(joueur *j) {
  j->main[j->nbCartes] = pioche(0);
  j->nbCartes++;
  printf("Vous avez pioché la carte : ");
  afficher_carte(&j->main[j->nbCartes-1]);
  printf("\n");
  // afficher sa main
  afficherMain(j);
}

void initapis(){
    pioche(1);
  //mets la carte piochée dans le tableau du tapis
  //printf("%d", rang);
  carteToTapis();
  //mets la carte du tapis dans la défausse
  tapisToDefausse();
}

void joueurJoue (joueur *j) {
  int choix;
  do {
    printf("Que voulez vous faire ?\n\t1. Poser une carte\n\t2. Piocher une carte\n");
    scanf("%d", &choix);
  } while (choix != 1 && choix != 2);
  switch (choix) {
    case 1:
      poseCarte(j);
      break;
    case 2:
      piocheCarte(j);
      break;
    default:
      printf("Choix invalide\n");
      break;
  }
  if (j->nbCartes == 0) {
    printf("Vous avez gagné %s !\n", j->nom);
  }
}

int main() {
  int i;
  creer_jeu();
    
  printf("\e[1;1H\e[2J");
  FILE * fichier = NULL;
  if((fichier = fopen("welcome.txt", "r")) == NULL) {
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
  int nbJoueur=0;
  do {
    printf("\n\nCombien y'a t'il de joueurs ? ");
    scanf("%d", &nbJoueur);
    if(nbJoueur < 2 || nbJoueur > 4) {
      printf("Nombre de joueurs invalide (entre 2 et 4 joueurs)\n");
    }
  } while (nbJoueur < 2 || nbJoueur > 4);

  joueur joueurs[nbJoueur];
  for (i=0; i < nbJoueur; i++) {
    printf("\e[1;1H\e[2J");
    creationJoueur(&joueurs[i], i);
  }
  printf("\e[1;1H\e[2J");
  for (i=0; i < nbJoueur; i++) {
    printf("Joueur %d : %s !\n", i+1, joueurs[i].nom);
    printf("Votre score est de %d\n", joueurs[i].score);
    printf("Votre main est composée de : ");
    afficherMain(&joueurs[i]);
    if(i != nbJoueur-1) {
      printf("\n\n -------------------------------------------- \n\n");
    } else {
      printf("\n\n");
    }
  }

  do {
    printf("Appuyez sur entrée pour commencer la partie\n");
    getchar();
  } while (getchar() != '\n');

  printf("\e[1;1H\e[2J");
  initapis();
  // supprime la carte pioché de la pioche
  supprCarteDePioche();

  // joueur j1;
  // creationJoueur(&j1);
  // printf("j1 : %s\n", j1.nom);
  // joueur j2;
  // creationJoueur(&j2);
  // printf("j2 : %s\n", j2.nom);

  // poseCarte(&j1);
  // piocheCarte(&j1);
  
  
  //la meme avec la défausse
     //for (int i = 1; i < 108; i++) {
    //printf("defausse[%d] = %s %s\n", i, defausse[i].valeur, defausse[i].couleur);
   //}
      //printf("%s %s\n\n", tapis[1].valeur, tapis[1].couleur);
  // supprime la carte pioché de la pioche

////////////////////

    //printf("\n%d\n\n", rang);
    
  //Affichez chaque élément du nouveau tableau (vérifier que l'ancienne carte est plus dedans)
     //for (int i = 0; i < (taillePioche); i++) {
    //printf("jeu[%d] = %s %s\n", i, jeu[i].valeur, jeu[i].couleur);
   //}
   
   //printf("%s %s\n\n", tapis[0].valeur, tapis[0].couleur);


  return 0;
}