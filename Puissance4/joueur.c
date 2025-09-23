#include "joueur.h"

bool test_cell(unsigned int x, unsigned int y, char tab[7][8], struct joueur_s *j)
{
   return (tab[y][x] == j->symbole);
}

int getnumcol(struct joueur_s * joueur)
{
    char erreur[]="Mauvaise saisie !!";
    char ligne[3];
    char ch = 'd';
    unsigned short value=0;

    while(1)
    {
        printf("joueur %u : ",joueur->numjoueur);
        fgets(ligne,2,stdin);
        while (ch != '\n' && ch != EOF) ch = getchar();

        if(sscanf(ligne,"%c",&ch) == 1)
        {
            if(ch=='q' || ch=='Q') 
            {
                value=0;
                break;
            }
            if(ch=='w' || ch=='W') 
            {
                value=9;
                break;
            }
            
            if(ch>'0' && ch <'8')
            {
                value = (ch - '0');
                break;
            }
            else
            {
                printf("%s\n",erreur);
            }
        }

    }
    return value;
}

unsigned int jouer(char tab[7][8], struct joueur_s * joueur)
{
    int i = 1;
    bool trouve = false;

    for( i=1; i<7; ++i)
    {
        if (tab[i][joueur->x_position]==' ')
        {
            tab[i][joueur->x_position]=joueur->symbole;
            trouve = true;
            break;
        }
    }
    return (trouve == true) ? i : 0;
}

bool check_victory(char tab[7][8], struct joueur_s *joueur)
{
    for (int u = 0; u<4;u++)
    {
        int x = joueur->x_position;
        int y = joueur->y_position;
        int count = 0;

        switch (u)
        {
            case 0 :
            {
                while(y>0 && (tab[y--][x] == joueur->symbole) && count++ < 4);
                break;
            }
            case 1 :
            {
                int i = 0;
                while(test_cell(x + i,y,tab,joueur) && count<4)
                {
                    if((x + i++)<8) count ++;
                }
                i = -1;
                while(test_cell(x + i,y,tab,joueur) && count<4)
                {
                    if((x + i--)>0) count ++;
                }

                break;
            }
            case 2 :
            {
                int i = 0;
                while(test_cell(x + i,y + i,tab,joueur) && count<4)
                {
                    if((y + i <7) && ((x + i++)<8)) count ++;
                }

                i = -1;
                while(test_cell(x + i,y + i,tab,joueur) && count<4)
                {
                    if(((y + i) > 0) && ((x + i--)>0)) count ++;
                }

                break;
            }
            case 3 :
            {
                int i = 0;
                while(test_cell(x + i,y - i,tab,joueur) && count<4)
                {
                    if(((y - i) <7) && ((x + i++)<8)) count ++;
                }
                i = -1;
                while(test_cell(x + i,y,tab,joueur) && count<4)
                {
                    if(((y - i) > 0) && ((x + i--)>0)) count ++;
                }

                break;
            }
        }

        if(count == 4) return true;
    }
    return false;
}
