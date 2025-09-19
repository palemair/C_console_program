#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"

/*fonctions d'affichage du tableau 7 x 6 du puissance 4 */

int viderTableau(char tab[7][6], char c)
{
    memset(tab,(int)c,sizeof(char) *6*7);
    return 0; 
}

int bordh(unsigned n)
{
    for (unsigned i=0;i<n;++i) 
    {
        printf("+---");
    }
    printf("+\n");

    return 0;
}
	
int lign(char tab[7][6],unsigned n)
{
    for (int i=0;i<7;++i) 
    {
        printf("| %c ",tab[i][5-n]);
    }
    printf("|\n");
    return 0;
}
	
int afftab(char tab[7][6])
{
    printf("\n  ");
    for (unsigned i = 1; i<8; ++i) printf("%d   ",i);
    printf("\n");

    for (int i=0; i<6; ++i) 
    {
        bordh(7);
        lign(tab,i);
    }
    bordh(7);

    printf("  ");
    for (unsigned i = 1; i<8; ++i) printf("%d   ",i);
    printf("\n\n");

    return 0;
}
