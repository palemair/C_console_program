#include "joueur.h"
#include "print.h"
#include <unistd.h>

char tab[7][8];

int main (void) 
{
    srand (time (NULL));
    typedef enum {VICTOIRE, PLUSDEJETON, QUITTER, ENCOURS} FINPARTIE;
    
    initialize_tab(' ');
    unsigned short col, ligne;

    struct joueur_s joueur1 = { 1, 21, 0, 0, 'X', NULL};
    struct joueur_s joueur2 = { 2, 21, 0, 0, 'O', &joueur1};
    joueur1.suivant = &joueur2;
   	
    struct joueur_s * courant = &joueur1;
    
    FINPARTIE jeu = ENCOURS; 
    bool gagne = false;
    int tj1[8], tj2[8];

    while((jeu == ENCOURS) && (courant->nbjetons>0))
    {
        printtab(courant);
        if(courant->numjoueur == 2)
        {
            check_col(tj1, joueur1.symbole);
            check_col(tj2, joueur2.symbole);
            get_max_from_2_col(tj1, tj2);
            int choice = choose_col(tj1, tj2);
            sleep(1);
            printf("Ordinateur joue : %d\n", choice);
            
            col = choice;
        }
        else
        {
            col = getnumcol(courant);
        }
        
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
        
        ligne = jouer(courant);

        if(ligne == 0) 
        {
            fprintf(stderr,"Mauvaise saisie, colonne pleine !!\n");
            continue;
        }
        else
        {
            courant->y_position = ligne;
        }

        gagne = check_victory( courant);
        
        if (gagne) 
        {
            jeu = VICTOIRE;
            printtab(courant);
            printf("joueur %u vainqueur !! \n\n", courant->numjoueur);
            break;
        }
        
        courant->nbjetons -=1;
        courant = courant->suivant;
    }

    return 0;
}        
