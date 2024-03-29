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
  int isBot;
} joueur;

/* Variables publiques du module */
extern int nbJoueurs;
extern joueur joueurs[];

/* Fonctionnalités publiques du module */
extern void initTapis ();
extern void creationJoueur (joueur *j, int nbJoueurs);
extern void creationBot (joueur *j);
extern void afficherMain(joueur *j);
extern int joueurJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern int botJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern struct carte pioche(int afficher);
extern struct carte piocheCarte(joueur *j);

#endif
