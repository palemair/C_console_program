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
    int x_position;
    int y_position;
    unsigned char symbole;
    struct joueur_s * suivant;
};

/* test validit d'une cellule */
bool test_cell(unsigned int x, unsigned int y, char tab[7][8], struct joueur_s *j);

/* fonction de jouer */
unsigned int jouer(char tab[7][8], struct joueur_s * joueur);

/* récuperer le numéro souhaité */
int getnumcol(struct joueur_s * joueur);

/* Controler l'état du jeu */
bool check_victory(char tab[7][8], struct joueur_s* joueur);

#endif
