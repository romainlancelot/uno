#ifndef DEF_HEADER_PLAYERS
#define DEF_HEADER_PLAYERS

/* Protection du module */
#include "display_standars.h"
#include "cards.h"
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */
typedef struct joueur {
  char nom[20];
  int score;
  carte main[108];
  int nbCartes;
} joueur;

/* Variables publiques du module */

/* Fonctionnalités publiques du module */
extern void initTapis ();
extern void creationJoueur (joueur *j, int nbJoueurs);
extern void trierMain(joueur *j);
extern void afficherMain(joueur *j);
extern int joueurJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern void carteSpeciale (joueur *j, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern struct carte pioche(int afficher);
extern struct carte piocheCarte(joueur *j);
extern struct carte poseCarte(joueur *j, carte *tapis);

#endif