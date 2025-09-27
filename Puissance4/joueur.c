#include "joueur.h"

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

bool test_cell(unsigned int x, unsigned int y, char sym)
{
    if(x>0 && x<8 && y>0 && y<7) return (tab[y][x] == sym);
    else return false;
}

unsigned int get_ligne_dispo(unsigned int x)
{
    int i = 1;
    bool trouve = false;

    for( i=1; i<7; ++i)
    {
        if (tab[i][x]==' ')
        {
            trouve = true;
            break;
        }
    }
    return (trouve == true) ? i : 0;
}

unsigned int jouer(struct joueur_s *j)
{
    unsigned int y = get_ligne_dispo(j->x_position);
    
    if((y >0) && (y<7))
        tab[y][j->x_position] = j->symbole;
    
    return y;
}

int get_max_jetons( int x_org,int y_org,char sym)
{
    int maxtb[4];

    for (int u = 0; u<4;u++)
    {
        int x = x_org;
        int y = y_org;
        int count = 1;

        switch (u)
        {
            case 0 :
            {
                int i = 1;
                while((test_cell(x, y - i++,sym)) && count++ < 4);
                break;
            }
            case 1 :
            {
                int i = 1;
                while(test_cell(x + i,y,sym) && count++<4) i++;

                i = 1;
                while(test_cell(x - i,y,sym) && count++<4) i++;
                break;
            }
            case 2 :
            {
                int i = 1;
                while(test_cell(x + i,y + i,sym) && count++<4) i++;

                i = 1;
                while(test_cell(x - i,y - i,sym) && count++<4) i++;
                break;
            }
            case 3 :
            {
                int i = 1;
                while(test_cell(x + i,y - i,sym) && count++<4) i++;

                i = 1;
                while(test_cell(x - i,y + i,sym) && count++<4) i++;
                break;
            }
        }
        maxtb[u] = count;
    }

    int max = -1;
    for(int z=0;z<4;z++)
    {
        max = (maxtb[z] > max) ? maxtb[z] : max ;
    }

    return max;
}

int check_col(int *cols,  char sym)
{
    memset(cols,-1,sizeof(int) * 8);
    for (int u = 1; u<8;u++)
    {
        unsigned int ligne = get_ligne_dispo(u);
        cols[u] = get_max_jetons(u,ligne,sym);
    }
    /* for (int u = 1; u<8;u++) */
    /* { */
    /*     printf(" %d |",cols[u]); */
    /* } */
    /*     printf("\n"); */
    return EXIT_SUCCESS;
}

int get_max_from_2_col(int *t1, int *t2)
{
    for(int z=1;z<8;z++)
    {
        t1[z] = (t1[z] > t2[z]) ? t1[z] : t2[z] ;
    }
    /* for (int u = 1; u<8;u++) */
    /* { */
    /*     printf(" %d |",t1[u]); */
    /* } */
    /*     printf("\n"); */
    return 1;
}

int choose_col(int *t1, int *t2)
{
    memset(t2,0,sizeof(int) * 8);
    
    int max1 = t1[1];
    for(int z=1;z<8;z++)
    {
        max1 = (max1 > t1[z]) ? max1 : t1[z] ;
        t2[0] = max1;
        if (max1 == 4) return z;
    }
   
    int i = 1;
    t2[0] = 0;
    for(int z=1;z<8;z++)
    {
        if(t1[z] == max1) 
        {
            t2[i++] = z ;
            t2[0]++;
        }
    }

    int nc = rand() %(t2[0]);

    return t2[nc + 1];
}

bool check_victory( struct joueur_s *joueur)
{
    int jetons = get_max_jetons(joueur->x_position, joueur->y_position, joueur->symbole);

    if(jetons == 4) return true;
    
    return false;
}
