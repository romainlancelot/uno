#ifndef DEF_HEADER_CARDS
#define DEF_HEADER_CARDS

/* Protection du module */
/**
	Documentation du module et auteurs
*/

/* Macros publiques */

/* Types publiques du module */
typedef struct carte {
	char valeur[10];
	char couleur[10];
	int piocheVide;
	int annuler;
} carte;

/* Variables publiques du module */
extern char *valeurs[];
extern char *couleurs[];
extern int rang; // rang du tableau contenant les cartes
extern int rangDefausse; // rang du tableau contenant les cartes défausse
extern int taillePioche; // nb total de carte dans la pioche en début de partie
extern carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().
extern carte defausse[108];
extern carte tapis[1];

/* Fonctionnalités publiques du module */
extern void creer_jeu ();
extern int afficher_carte(carte *c);
extern int transfertDefausseToPioche ();
extern int supprCarteDePioche();
extern void tapisToDefausse();
extern void carteToTapis();

#endif