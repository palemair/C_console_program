#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"

/*fonctions d'affichage du tableau 6 x 7 du puissance 4 */
static char bord[] = "+---";

int initialize_tab(char c)
{
    memset(tab,(int)c,sizeof(char) *7*8);
    return 0; 
}

int printtab()
{
    printf("\n  ");
    for (unsigned i = 1; i<8; ++i) printf("\033[37m%-4d\033[0m",i);
    printf("\n");

    for (int y=6; y>=1; --y) 
    {
        for (unsigned i=0;i<7;++i) 
        {
            printf("\033[37m%s\033[0m",bord);
        }
        printf("\033[37m%c\033[0m\n",'+');

        for (int x=1;x<8;++x) 
        {
            printf("\033[37m%c\033[0m",'|');
            char ch = tab[y][x];
            switch(ch)
            {
                case ('X'): 
                    printf("\033[1;33m%2c\033[0m ",tab[y][x]);
                    break;
                case ('O'): 
                    printf("\033[1;31m%2c\033[0m ",tab[y][x]);
                    break;
                default :
                    printf("%2c ",tab[y][x]);
                    break;
            }

        }
        printf("\033[37m%c\033[0m\n",'|');
    }

    for (unsigned i=0;i<7;++i) 
    {
        printf("\033[37m%s\033[0m",bord);
    }
    printf("\033[37m%c\033[0m",'+');

    printf("\n  ");
    for (unsigned i = 1; i<8; ++i) printf("\033[37m%-4d\033[0m",i);
    printf("\n\n");

    return 0;
}
