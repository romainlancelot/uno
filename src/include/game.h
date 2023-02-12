#ifndef DEF_HEADER_GAME
#define DEF_HEADER_GAME

/* Protection du module */
#include "display_standars.h"
#include "players.h"
#include "server.h"
#include "client.h"
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */

/* Variables publiques du module */
extern int skipTurn;
extern int inversion;
extern int draw;

/* Fonctionnalités publiques du module */
extern void printMenu();
extern void startParty(joueur joueurs[]);

#endif