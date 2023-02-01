#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CLEAR_SCREEN printf("\e[1;1H\e[2J");
#define SEPARATEUR printf(" -------------------------------------------- \n\n");

typedef struct carte {
  char valeur[10];
  char couleur[10];
  int piocheVide;
} carte;

char *valeurs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};

int rang; //rang du tableau contenant les cartes
int rangDefausse = 0; //rang du tableau contenant les cartes défausse

int taillePioche = 108; //nb total de carte dans la pioche en début de partie
carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().
carte defausse[108];
carte tapis[1];


void creer_jeu () {
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

// print la carte
int afficher_carte(carte *c) {
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

int transfertDefausseToPioche () {
  // si la défausse est vide, on ne fait rien (on ne peut pas transférer)
  if (rangDefausse == 0) {
    return 0;
  }
  // copie colle le tableau des cartes de la défausse dans celui de la pioche
  for (int i = 0; i < 108; i++) {
    jeu[i] = defausse[i];
    *defausse[i].valeur = '\0';
    *defausse[i].couleur = '\0';
  }
  return 1;
}

// fonction pour une carte aléatoire
int aleatoire(int *taillePioche) {
  if (*taillePioche == 0) {
    if (transfertDefausseToPioche() == 0) {
      return -1;
    }
    *taillePioche = rangDefausse;
    rangDefausse = 0;
  }
  // Initialisation du générateur de nombres aléatoires
  srand(time(NULL));
  // Génération d'un nombre aléatoire compris entre 0 et la taille de la pioche (inclus)
  int indice_aleatoire = rand() % (*taillePioche);
  // On décrémente la taille de la pioche
  *taillePioche = *taillePioche - 1;
  return indice_aleatoire;
}

int supprCarteDePioche() {
  // copie colle le tableau des cartes dans la pioche en enlevant l'élément pioché
  int j = 0;
  for (int i = 0; i < (taillePioche+1); i++) {
    if (i == rang) continue; // ignore l'élément rang
    jeu[j] = jeu[i];
    j++;
  }
  *jeu[taillePioche].valeur = '\0';
  *jeu[taillePioche].couleur = '\0';
}

//mets la carte du tapis dans la défausse
void tapisToDefausse() {
  defausse[rangDefausse] = tapis[1];
  //printf la carte défaussée
  supprCarteDePioche();
  rangDefausse++;
}

//mets la carte piochée dans le tapis
void carteToTapis() {
  tapis[1] = jeu[rang];
}

struct carte pioche(int afficher) {
  // récupère un nb aléatoire
  rang = aleatoire(&taillePioche);
  if (rang == -1) {
    return (carte) { .valeur = "", .couleur = "", .piocheVide = 1 };
  }
  carte cartePioche = jeu[rang];
  // Affichage de la carte à l'indice généré aléatoirement
  if (afficher == 1) {
    afficher_carte(&cartePioche);
    printf("\n");
  }
  return cartePioche;
}

// déclaration des joueurs
typedef struct joueur {
  char nom[20];
  int score;
  carte main[108];
  int nbCartes;
} joueur;

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

// joueur pose une carte
struct carte poseCarte(joueur *j, carte *tapis) {
  char tmpChoix[10];
  int choix, choixCouleur;
  do {
    // printf("\nQuelle carte voulez vous jouer ? ('p' : annuler et piocher une carte)\n => ");
    printf("\nQuelle carte voulez vous jouer ?\n => ");
    scanf("%s", tmpChoix);
    choix = atoi(tmpChoix);
    // TODO
    // if (strcmp(tmpChoix, "p") == 0) {

    // }
    if (choix < 0 || choix > j->nbCartes) {
      printf("Veuillez choisir une carte valide !\n");
    }
    if (strcmp(j->main[choix].couleur, "joker") == 0 || strcmp(j->main[choix].valeur , "changer") == 0) {
      printf("Vous avez joué une carte changement de coueleur  !\nQuelle couleur voulez vous choisir ?\n");
      do {
        printf("Possibilités : { 1 : \033[0;31mrouge\033[0m | 2 : \033[0;33mjaune\033[0m | 3 : \033[0;32mvert\033[0m | 4 : \033[0;34mbleu\033[0m }\n => ");
        scanf("%d", &choixCouleur);
        if (choixCouleur < 1 || choixCouleur > 4) {
          printf("Veuillez choisir une couleur valide !\n");
        }
      } while (choixCouleur < 1 || choixCouleur > 4);
      switch (choixCouleur) {
        case 1:
          strcpy(j->main[choix].couleur, "rouge");
          break;
        case 2:
          strcpy(j->main[choix].couleur, "jaune");
          break;
        case 3:
          strcpy(j->main[choix].couleur, "vert");
          break;
        case 4:
          strcpy(j->main[choix].couleur, "bleu");
          break;
      }
      break;
    } else if (strcmp(j->main[choix].couleur, tapis[1].couleur) != 0 && strcmp(j->main[choix].valeur, tapis[1].valeur) != 0) {
      printf("Vous ne pouvez pas poser cette carte...\n");
    }
  } while (choix < 0 || choix > j->nbCartes || strcmp(j->main[choix].couleur, tapis[1].couleur) != 0 && strcmp(j->main[choix].valeur, tapis[1].valeur) != 0);
  carte cartePosee = j->main[choix];

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

  afficherMain(j);
  return cartePosee;
}

// joueur pioche une carte
struct carte piocheCarte(joueur *j) {
  carte cartePiochee = pioche(0);
  if (cartePiochee.piocheVide == 1) {
    return cartePiochee;
  }
  j->main[j->nbCartes] = cartePiochee;
  j->nbCartes++;
  supprCarteDePioche();
  return j->main[j->nbCartes-1];
}

void initTapis () {
  do {
    pioche(1);
    //mets la carte piochée dans le tableau du tapis
    carteToTapis();
    //mets la carte du tapis dans la défausse
    tapisToDefausse();
  } while (strcmp(tapis[1].valeur, "draw+2") == 0 || strcmp(tapis[1].valeur, "draw+4") == 0 || strcmp(tapis[1].valeur, "skip") == 0 || strcmp(tapis[1].valeur, "inversion") == 0 || strcmp(tapis[1].valeur, "change") == 0 || strcmp(tapis[1].valeur, "skip") == 0 ||  strcmp(tapis[1].couleur, "joker") == 0);
}

void carteSpeciale (joueur *j, carte *tapis, int *skipTurn, int *inversion, int *draw) {
  if (strcmp(tapis[1].valeur, "draw+2") == 0) { *draw = 2; }
  if (strcmp(tapis[1].valeur, "draw+4") == 0) { *draw = 4; }
  if (strcmp(tapis[1].valeur, "skip") == 0) { *skipTurn = 1; }
  if (strcmp(tapis[1].valeur, "inversion") == 0) { *inversion = *inversion + 1;	}
}

int joueurJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw) {
  int choix;
  do {
    printf("Que voulez vous faire ?\n\t1. Poser une carte\n\t2. Piocher une carte\n\n => ");
    scanf("%d", &choix);
  } while (choix != 1 && choix != 2);
  switch (choix) {
    case 1:
      carte cartePose = poseCarte(j, tapis);
      CLEAR_SCREEN;
      SEPARATEUR;
      printf("Joueur %d (%s) a joué la carte : ", nbJoueurs, j->nom);
      afficher_carte(&cartePose);
      carteSpeciale(j, tapis, skipTurn, inversion, draw);
      printf("\n\n");
      SEPARATEUR;
      break;
    case 2:
      carte cartePioche = piocheCarte(j);
      if (cartePioche.piocheVide == 1) {
        printf("\n /!\\ La pioche est vide, vous ne pouvez pas piocher de carte /!\\ \n");
        return 0;
      }
      CLEAR_SCREEN;
      SEPARATEUR;
      printf("Joueur %d (%s) a pioché la carte : ", nbJoueurs, j->nom);
      afficher_carte(&cartePioche);
      printf("\n\n");
      SEPARATEUR;
      break;
    default:
      printf("Choix invalide\n");
      break;
  }
  if (j->nbCartes == 0) {
    printf("Vous avez gagné %s !\n", j->nom);
  }
  return 1;
}

int main() {
  int i;
  creer_jeu();

  // for (i = 0; i < 110; i++) { 
  //   initTapis();
  //   printf("\n");
  // }
    
  CLEAR_SCREEN;
  FILE * fichier = NULL;
  if ((fichier = fopen("welcome.txt", "r")) == NULL) {
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