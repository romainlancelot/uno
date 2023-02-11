#ifndef DEF_HEADER_ACTIONS
#define DEF_HEADER_ACTIONS

/* Protection du module */
#include "display_standars.h"
#include "players.h"
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */

/* Variables publiques du module */

/* Fonctionnalités publiques du module */
extern int joueurJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern void carteSpeciale (joueur *j, carte *tapis, int *skipTurn, int *inversion, int *draw);
extern struct carte pioche(int afficher);
extern struct carte piocheCarte(joueur *j);
extern struct carte poseCarte(joueur *j, carte *tapis);

#endif