#ifndef DEF_HEADER_PLAYERS
#define DEF_HEADER_PLAYERS

/* Protection du module */
#include "cards.h"
#include "actions.h"
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
extern void creationJoueur (joueur *j, int nbJoueurs);
extern void trierMain(joueur *j);
extern void afficherMain(joueur *j);

#endif