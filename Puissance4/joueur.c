#include "joueur.h"

unsigned short getnumcol(struct joueur_s * joueur)
{
    char erreur[]="Mauvaise saisie !!";
    char ligne[3];
    char ch;
    unsigned short value=0;

    while(1)
    {
        printf("joueur %u : ",joueur->numjoueur);
        fgets(ligne,3,stdin);
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
                return ch - '0';
            }
            else
            {
                printf("%s\n",erreur);
            }
        }

    }
    return value;
}

bool jouer(char tab[7][6], struct joueur_s * joueur)
{
    bool trouve = false;
    unsigned short pos = joueur->position - 1;

    for(int i=0; i<6; ++i)
    {
        if (tab[pos][i]==' ')
        {
            tab[pos][i]=joueur->symbole;
            trouve = true;
            break;
        }
    }
    return trouve;
}

int diag(char tab[7][6],int ligne, char *test)
{
    int col=0;
    char *pt;
    char mot[8];
    pt=mot;

    while(ligne<7 && col<6)
    {
        *pt=tab[ligne][col];
        ++pt,++ligne,++col;
    }
    *pt='\0';
    if(strstr(mot,test) != NULL) return 1;

    return 0;
}

int xdiag(char tab[7][6],int col,char *test) 
{
    int ligne=0;
    char *pt;
    char mot[8];
    pt = mot;
    while(ligne<7 && col<6)
    {
        *pt=tab[ligne][col];
        ++pt,++ligne,++col;
    }
    *pt='\0';
    if(strstr(mot,test) != NULL) return 1;
    return 0;
}

int rdiag(char tab[7][6],int ligne, char *test)
{
    int col=5;
    char *pt;
    char mot[8];
    pt = mot;
    while(ligne<7 && col>=0)
    {
        *pt=tab[ligne][col];
        ++pt,++ligne,--col;
    }
    *pt='\0';
    if(strstr(mot,test) != NULL) return 1;
    return 0;
}

int rxdiag(char tab[7][6],int col, char *test)
{
    int ligne=0;
    char *pt;
    char mot[8];
    pt = mot;
    while(ligne<7 && col>=0)
    {
        *pt=tab[ligne][col];
        ++pt,++ligne,--col;
    }
    *pt='\0';
    if(strstr(mot,test) != NULL) return 1;
    return 0;
}

FINPARTIE checkjeu(char tab[7][6], struct joueur_s *joueur)
    
{
    char c = joueur->symbole;
    char phrase[10];
    char test[5];
    int ligne, col, k;

    for(k=0;k<4;++k)
    {
        test[k]=c;
    }
    test[k]='\0';

    for(ligne=0;ligne<7;++ligne)
    {
        for(col=0;col<6;++col)
        {
            phrase[col]=tab[ligne][col];
        } 
        phrase[col]='\0';

        if(strstr(phrase,test) != NULL) return VICTOIRE;

    }

    for(ligne=0;ligne<6;++ligne)
    {
        for(col=0;col<7;++col)
        {
            phrase[col]=tab[col][ligne];
        } 
        phrase[col]='\0';

        if(strstr(phrase,test) != NULL) return VICTOIRE;
    }

    for(k=0;k<4;k++)
    {
        if(diag(tab,k,test)==1) return VICTOIRE;
    }

    diag(tab,k,test);

    for(k=0;k<3;k++)
    {
        if(xdiag(tab,k,test) == 1) return VICTOIRE;
        if(rdiag(tab,k,test) == 1) return VICTOIRE;
    }

    for(k=5;k>2;k--)
    {
        if(rxdiag(tab,k,test) == 1) return VICTOIRE;
    }

    return ENCOURS;
}
