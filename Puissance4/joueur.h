#ifndef JOUEUR
#define JOUEUR

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct joueur_s;

struct joueur_s {
    unsigned short numjoueur;
    unsigned short nbjetons;
    unsigned short position;
    unsigned char symbole;
    struct joueur_s * suivant;
};

typedef enum {VICTOIRE, PLUSDEJETON, QUITTER, ENCOURS} FINPARTIE;

/* fonction de jouer */
bool jouer(char tab[7][6], struct joueur_s * joueur);

/* récuperer le numéro souhaité */
unsigned short getnumcol(struct joueur_s * joueur);

/* Controler l'état du jeu */


int diag(char tab[7][6],int ligne,char * test);
int xdiag(char tab[7][6],int col, char *test);
int rdiag(char tab[7][6],int ligne,char *test);
int xdiag(char tab[7][6],int col,char *test);

FINPARTIE checkjeu(char tab[7][6], struct joueur_s* joueur);

#endif
