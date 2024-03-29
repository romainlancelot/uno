#include "include/players.h"
/* Inclusion des déclarations du module */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Autres inclusions */

/* Définition des variables globales relatives au module */
int nbJoueurs;
joueur joueurs[3];

/* Fonctionnalité privée au module par le mot clé static */
// trier la main du joueur
static void trierMain(joueur *j) {
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

static void carteSpeciale (joueur *j, carte *tapis, int *skipTurn, int *inversion, int *draw) {
	if (strcmp(tapis[1].valeur, "draw+2") == 0) { *draw = 2; }
	if (strcmp(tapis[1].valeur, "draw+4") == 0) { *draw = 4; }
	if (strcmp(tapis[1].valeur, "skip") == 0) { *skipTurn = 1; }
	if (strcmp(tapis[1].valeur, "inversion") == 0) { *inversion = *inversion + 1;	}
}

// joueur pose une carte
static struct carte poseCarte(joueur *j, carte *tapis) {
	char tmpChoix[10];
	int choix, choixCouleur;
	do {
		printf("\nQuelle carte voulez vous jouer ? ('q' : annuler)\n => ");
		scanf("%s", tmpChoix);
		choix = atoi(tmpChoix);
		if (strcmp(tmpChoix, "q") == 0) {
			return (carte) { .valeur = "", .couleur = "", .piocheVide = 0, .annuler = 1 };
		}
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

// fonction pour une carte aléatoire
static int aleatoire(int *taillePioche) {
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

static void checkWin(joueur *j) {
	if (j->nbCartes == 0) {
		CLEAR_SCREEN;
		printf("\n\n%s a gagné la partie  !\n\n", j->nom);
		FILE * fichier = NULL;
		if ((fichier = fopen("text/end.txt", "r")) == NULL) {
			printf("Impossible d'ouvrir le fichier end.txt\n");
			exit(EXIT_FAILURE);
		} else {
			char c;
			while ((c = fgetc(fichier)) != EOF) {
				printf("%c", c);
			}
			fclose(fichier);
			fichier = NULL;
		}
		exit(EXIT_SUCCESS);
	}
}


/* Définistion des fonctionnalités annoncées par l'entête */
void initTapis () {
	do {
		pioche(0);
		//mets la carte piochée dans le tableau du tapis
		carteToTapis();
		//mets la carte du tapis dans la défausse
		tapisToDefausse();
	} while (strcmp(tapis[1].valeur, "draw+2") == 0 || strcmp(tapis[1].valeur, "draw+4") == 0 || strcmp(tapis[1].valeur, "skip") == 0 || strcmp(tapis[1].valeur, "inversion") == 0 || strcmp(tapis[1].valeur, "change") == 0 || strcmp(tapis[1].valeur, "skip") == 0 ||  strcmp(tapis[1].couleur, "joker") == 0);
}

void creationJoueur(joueur *j, int nbJoueurs) {
	printf("Quel est le nom du joueur %d ? ", nbJoueurs+1);
	scanf("%s", j->nom);
	j->score = 0;
	j->nbCartes = 7;
	j->isBot = 0;
	// piocher 7 cartes
	for (int i = 0; i < j->nbCartes; i++) {
		j->main[i] = pioche(0);
		supprCarteDePioche();
	}
}

//création du joueur ordinateur pour les partis solo
void creationBot(joueur *j) {
	strcpy(j->nom, "Ordinateur");
	j->score = 0;
	j->nbCartes = 7;
	j->isBot = 1;
	// piocher 7 cartes
	for (int i = 0; i < j->nbCartes; i++) {
		j->main[i] = pioche(0);
		supprCarteDePioche();
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

int botJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw) {
	for (int i=0; i < j->nbCartes; i++) {
		// si le bot a une carte qui correspond à la carte du tapis il la joue
		if (strcmp(j->main[i].valeur, tapis[1].valeur) == 0 || strcmp(j->main[i].couleur, tapis[1].couleur) == 0) {
			//mets la carte en question dans le tapis
			strcpy(tapis[1].valeur, j->main[i].valeur);
			strcpy(tapis[1].couleur, j->main[i].couleur);

			//mets la carte du tapis dans la défausse
			tapisToDefausse();

			// supprime la carte joué de la main du joueur
			for (int x = i; x < j->nbCartes; x++) {
				j->main[x] = j->main[x+1];
			}
			j->nbCartes--;
			CLEAR_SCREEN;
			SEPARATEUR;
			printf("Joueur %d (%s) a joué la carte : ", nbJoueurs, j->nom);
			afficher_carte(&tapis[1]);
			carteSpeciale(j, tapis, skipTurn, inversion, draw);
			printf("\n\n");
			SEPARATEUR;
			checkWin(j);
			return 1;
		}
		if (strcmp(j->main[i].couleur, "change") == 0 || strcmp(j->main[i].couleur, "draw+4") == 0) {
			// compter de quel couleur il y a le plus de carte dans la main du joueur
			int nbRouge = 0;
			int nbBleu = 0;
			int nbVert = 0;
			int nbJaune = 0;
			for (int x = 0; x < j->nbCartes; x++) {
				if (strcmp(j->main[x].couleur, "rouge") == 0) {
					nbRouge++;
				}
				if (strcmp(j->main[x].couleur, "bleu") == 0) {
					nbBleu++;
				}
				if (strcmp(j->main[x].couleur, "vert") == 0) {
					nbVert++;
				}
				if (strcmp(j->main[x].couleur, "jaune") == 0) {
					nbJaune++;
				}
			}
			// comparaison du plus grand nomobre de carte
			if (nbRouge > nbBleu && nbRouge > nbVert && nbRouge > nbJaune) {
				strcpy(j->main[i].couleur, "rouge");
			}
			if (nbBleu > nbRouge && nbBleu > nbVert && nbBleu > nbJaune) {
				strcpy(j->main[i].couleur, "bleu");
			}
			if (nbVert > nbRouge && nbVert > nbBleu && nbVert > nbJaune) {
				strcpy(j->main[i].couleur, "vert");
			}
			if (nbJaune > nbRouge && nbJaune > nbBleu && nbJaune > nbVert) {
				strcpy(j->main[i].couleur, "jaune");
			}

			//mets la carte en question dans le tapis
			strcpy(tapis[1].valeur, j->main[i].valeur);
			strcpy(tapis[1].couleur, j->main[i].couleur);

			//mets la carte du tapis dans la défausse
			tapisToDefausse();

			// supprime la carte joué de la main du joueur
			for (int x = i; x < j->nbCartes; x++) {
				j->main[x] = j->main[x+1];
			}
			j->nbCartes--;
			CLEAR_SCREEN;
			SEPARATEUR;
			printf("Joueur %d (%s) a joué la carte : ", nbJoueurs, j->nom);
			afficher_carte(&tapis[1]);
			carteSpeciale(j, tapis, skipTurn, inversion, draw);
			printf("\n\n");
			SEPARATEUR;
			checkWin(j);
			return 1;
		}
	}

	// si le bot n'a pas de carte qui correspond à la carte du tapis il pioche
	carte cartePioche = piocheCarte(j);
	if (cartePioche.piocheVide == 1) {
		printf("\n /!\\ La pioche est vide, vous ne pouvez pas piocher de carte (si vous arrivez à cette erreur vous tombez dans une boucle infini et c'est pas normal j'espère que vous ne verez jamais cette ligne) /!\\ \n");
		return 0;
	}
	CLEAR_SCREEN;
	SEPARATEUR;
	printf("Joueur %d (%s) a pioché la carte : ", nbJoueurs, j->nom);
	afficher_carte(&cartePioche);
	printf("\n\n");
	SEPARATEUR;
	checkWin(j);
	return 1;
}

int joueurJoue (joueur *j, int nbJoueurs, carte *tapis, int *skipTurn, int *inversion, int *draw) {
	int choix;
	char charchoix[10];
	do {
		printf("Que voulez vous faire ?\n\t1. Poser une carte\n\t2. Piocher une carte\n\n => ");
		scanf("%s", charchoix);
		choix = atoi(charchoix);
	} while (choix != 1 && choix != 2);
	switch (choix) {
		case 1:
			carte cartePose = poseCarte(j, tapis);
			if (cartePose.annuler == 1) {
				return 0;
			}
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
	checkWin(j);
	return 1;
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
