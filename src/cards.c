#include "include/cards.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */
char *valeurs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "draw+2", "inversion", "skip", "change", "draw+4"};
char *couleurs[] = {"rouge", "jaune", "vert", "bleu", "joker"};
int rang;
int rangDefausse = 0;
int taillePioche = 108;
carte jeu[108];
carte defausse[108];
carte tapis[1];

/* Fonctionnalité privée au module par le mot clé static */

/* Définistion des fonctionnalités annoncées par l'entête */

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
