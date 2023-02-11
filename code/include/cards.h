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
char *valeurs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};
int rang; //rang du tableau contenant les cartes
int rangDefausse = 0; //rang du tableau contenant les cartes défausse
int taillePioche = 108; //nb total de carte dans la pioche en début de partie
carte jeu[108]; // Déclarer le tableau de cartes global afin qu'il soit accessible depuis main().
carte defausse[108];
carte tapis[1];

/* Fonctionnalités publiques du module */
extern void creer_jeu ();
extern void initTapis ();
extern int afficher_carte(carte *c);
extern int transfertDefausseToPioche ();
extern int supprCarteDePioche();
extern void tapisToDefausse();
extern void carteToTapis();

#endif