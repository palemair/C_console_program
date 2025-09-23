#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"

/*fonctions d'affichage du tableau 6 x 7 du puissance 4 */

int initialize_tab(char tab[7][8], char c)
{
    memset(tab,(int)c,sizeof(char) *7*8);
    return 0; 
}

int printtab(char tab[7][8])
{
    printf("\n  ");
    for (unsigned i = 1; i<8; ++i) printf("%d   ",i);
    printf("\n");

    for (int y=6; y>=1; --y) 
    {
        for (unsigned i=0;i<7;++i) 
        {
            printf("+---");
        }
        printf("+\n");

        for (int x=1;x<8;++x) 
        {
            printf("| %c ",tab[y][x]);
        }
        printf("|\n");
    }

    for (unsigned i=0;i<7;++i) 
    {
        printf("+---");
    }
    printf("+\n");

    printf("  ");
    for (unsigned i = 1; i<8; ++i) printf("%d   ",i);
    printf("\n\n");

    return 0;
}
