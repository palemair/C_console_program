#include <stdio.h>
#include <stdlib.h>

extern char tab[7][8];

#ifndef AFFICHAGE
#define AFFICHAGE
#include <curses.h>

/* affichage.c */
int initialize_tab( char c);
int printtab();

#endif
