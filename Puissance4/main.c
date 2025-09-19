#include "affichage.h"
#include "joueur.h"

int main (void) 

{
    static char tab[7][6];
    
    viderTableau(tab,' ');
    unsigned short col = 0;

    struct joueur_s joueur1 = { 1,21,0,'X',NULL};
    struct joueur_s joueur2 = { 2,21,1,'O',&joueur1};
    joueur1.suivant = &joueur2;
   	
    struct joueur_s * courant = NULL;
    courant = &joueur1;
    
    FINPARTIE jeu = ENCOURS; 

    while(1)

    {
        afftab(tab);
        col = getnumcol(courant);
        
        if(col == 0) 
        {
            jeu = QUITTER;
            printf("Jeu arrété !!\n\n");
            break;
        }
        courant->position = col;
        
        if(!jouer(tab,courant))
        {
            fprintf(stderr,"Mauvaise saisie, colonne pleine !!\n");
            continue;
        }

        jeu=checkjeu(tab, courant);
        
        if (jeu == VICTOIRE) 
        {
            afftab(tab);
            printf("joueur %u vainqueur !! \n\n", courant->numjoueur);
            break;
        }
        
        courant->nbjetons -=1;
        courant = courant->suivant;
    }

    return 0;
}        
