#include "print.h"
#include "joueur.h"

int main (void) 
{
    static char tab[7][8];
    
    initialize_tab(tab,' ');
    unsigned short col, ligne;

    struct joueur_s joueur1 = { 1, 21, 0, 0, 'X', NULL};
    struct joueur_s joueur2 = { 2, 21, 0, 0, 'O', &joueur1};
    joueur1.suivant = &joueur2;
   	
    struct joueur_s * courant = &joueur1;
    
    FINPARTIE jeu = ENCOURS; 
    bool gagne = false;

    while(jeu == ENCOURS)

    {
        printtab(tab);
        col = getnumcol(courant);
        
        if(col == 0) 
        {
            jeu = QUITTER;
            printf("Jeu arrété !!\n\n");
            break;
        }
        else
        {
            courant->x_position = col;
        } 
        
        ligne = jouer(tab,courant);

        if(ligne == 0) 
        {
            fprintf(stderr,"Mauvaise saisie, colonne pleine !!\n");
            continue;
        }
        else
        {
            courant->y_position = ligne;
        }

        gagne = check_victory(tab, courant);
        
        if (gagne) 
        {
            jeu = VICTOIRE;
            printtab(tab);
            printf("joueur %u vainqueur !! \n\n", courant->numjoueur);
            break;
        }
        
        courant->nbjetons -=1;
        courant = courant->suivant;
    }

    return 0;
}        
