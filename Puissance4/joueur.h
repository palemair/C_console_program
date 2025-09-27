#ifndef JOUEUR
#define JOUEUR

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

extern char tab[7][8];
struct joueur_s;

struct joueur_s {
    unsigned short numjoueur;
    unsigned short nbjetons;
    int x_position;
    int y_position;
    unsigned char symbole;
    struct joueur_s * suivant;
};

/* test validit d'une cellule */
bool test_cell(unsigned int x, unsigned int y, char );

unsigned int get_ligne_dispo(unsigned int x);

/* fonction de jouer */
unsigned int jouer(struct joueur_s * joueur);

/* récuperer le numéro souhaité */
int getnumcol(struct joueur_s * joueur);

int get_max_jetons( int x_org,int y_org,char sym);

int get_max_from_2_col(int *t1, int *t2);

int choose_col(int *t1,int *t2);

int check_col(int *cols,  char sym);

/* Controler l'état du jeu */
bool check_victory( struct joueur_s* joueur);

#endif
