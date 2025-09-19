#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include <term.h>

struct prix
{
  float nicotine;
  float base;
  float arome;
};

struct quantite
{
  int eliquide;
  int nicotine;
  int base;
  float arome;
};

struct prix tarif = { 0.075, 0.0099, 0.39 };
struct quantite demande = { 0 };
struct quantite *dem = &demande;

struct quantite* calc_eliquid (struct quantite* q, struct quantite* retour)     // calculateur  
{
  retour->eliquide = q->eliquide;
  retour->arome = q->eliquide * 0.15;
  retour->nicotine = (q->eliquide * q->nicotine) / 20;
  retour->base = q->eliquide - (retour->nicotine + retour->arome);

  return retour;
}

float calc_prix (struct quantite *q, struct prix *p)      // calculateur  
{
  float total = 0;

  total = (p->nicotine * q->nicotine) + (p->base * q->base) + (p->arome * q->arome);
  return total;
}

static const char* texte[] = {
    "CALCULATEUR DE E-LIQUIDE",
    "Entrez la dose de nicotine souhaitée en mg/ml : ",
    "Entrez la quantité de totale de eliquide souhaitée en ml : ",
    "Rappel des prix des éléments",
    "Tarif de la base",
    "Tarif de la nicotine",
    "Tarif de l'arome",
    "Quantités calculées :",
    "E-liquide",
    "Base",
    "Nicotine",
    "Arome"
};

int main (int argc, char **argv)
{
  /* gestion des arguments de la ligne de commande !! */
    static char help[] = "Calcul du dosage de eliquide\n\n"
                         "\toption -n pour la quantite de nicotine en mg/L\n"
                         "\toption -t pour la quantite totale\n\n";

    static int Nbnico = 0;
    static int etotal = 0;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "hn:t:")) != -1)
        switch (c)
        {
        case 'n':
            Nbnico = strtol (optarg, NULL, 10);
            break;
        case 't':
            etotal = strtol (optarg, NULL, 10);
            break;
        case 'h':
            fprintf (stderr, "%s", help);
            return EXIT_FAILURE;
            break;
        case '?':
            if (optopt == 'n')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (optopt == 't')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
        }

  #define MAX 20

  char string[MAX]= "\0";
  
  if(Nbnico == 0 && etotal == 0) 
  {
      printf ("\t%s", texte[1]);
      fgets(string,MAX-1,stdin);
      sscanf(string,"%d",&Nbnico);
      
      memset(string,0,sizeof(string));

      printf ("\t%s", texte[2]);
      fgets(string,MAX-1,stdin);
      etotal = strtol (string, NULL, 10);
  }

  dem->nicotine = Nbnico;
  dem->eliquide = etotal;

  /* Calcul des quantites !! */
  struct quantite reponse = { 0, 0, 0, 0 };
  calc_eliquid (&demande,&reponse);

  float total = calc_prix (&reponse, &tarif);

  /* Affichage du resultat !! */

  printf ("\n\t\033[1;37m%s\033[0m\n", texte[0]);

  printf ("\n\t\033[1;37m%s\033[0m\n\n", texte[3]);
  printf ("\t%-22s: \033[1;37m%5.2f €/L\033[0m\n", texte[4],tarif.base);
  printf ("\t%-22s: \033[1;37m%5.2f €/L\033[0m\n", texte[5],tarif.nicotine);
  printf ("\t%-22s: \033[1;37m%5.2f €/L\033[0m\n\n", texte[6],tarif.arome);

  printf ("\n\t\033[1;37m%s\033[0m\n\n", texte[7]);

  printf ("\t%-22s: \033[1;37m%5u ml\033[0m\n", texte[8],reponse.eliquide);
  printf ("\t%-22s: \033[1;37m%5u ml\033[0m\n", texte[9],reponse.base);
  printf ("\t%-22s: \033[1;37m%5u ml\033[0m\n", texte[10],reponse.nicotine);
  printf ("\t%-22s: \033[1;37m%5u ml\033[0m\n\n", texte[11],(unsigned char)reponse.arome);

  printf ("\t\033[1;37m%3u\033[0m ml de base + ",reponse.base);
  printf ("\033[1;37m%3u\033[0m boosters de nicotine + ",reponse.nicotine/10);
  printf ("\033[1;37m%3.1f\033[0m flacons d'arome\n\n",reponse.arome/10);

  printf ("\t\033[1;37m%s\033[0m\n\n", "Tarif global :");

  printf ("\t%-15s \033[1;41m %.2f € \033[0m | ", "Prix total :", total);
  printf ("\t%-20s \033[1;41m %.2f €/ml \033[0m\n", " Prix de revient : ", total / (float) reponse.eliquide);
  printf ("\n");

  return (0);
}
