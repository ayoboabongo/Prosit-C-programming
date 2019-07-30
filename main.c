#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>


int main()
{
    int choix;
    abr a=NULL;

    LDC L;
    L.queu=NULL;
    L.tete=NULL;
    int nb,id;
    float BI,BS;
    etudiant e;
    do
    {
         printf("Menu!\n");
         printf("1-initailiser\n");
         printf("2-Inserer etudiant\n");
         printf("3-Construire arbre a partir du fichier\n");
         printf("4-Afficher arbre\n");
         printf("5-Calculer nombre total\n");
         printf("6-Construire liste\n");
         printf("7-Construire liste trier\n");
         printf("8-Afficher LDC\n");
         printf("9-Supprimer Etudiant\n");
         printf("10-Transfert Liste->Abr\n");
         printf("11-Inserer etudiant LDC\n");
         printf("12-Ajout trier LDC\n");
         printf("0-Quitter\n");
         printf("Entrez votre choix\n");
         scanf("%d",&choix);
         switch(choix)
         {
         case 1 :
           a=initialiser(e);
           break;

         case 2 :
           e=saisir(e);
           a=inserer (a,e);
            break;
         case 3 :
            a=construireArbre (a,"moyennes.txt");printf("ok");
            break;
         case 4 :
            afficher(a);
            printf("\n");
            break;
         case 5 :
            nb=calculerNombre(a);
            printf("Arbre de %d etudiant(s)\n",nb);
            printf("Arbre de %d etudiant(s)\n",nb);
            break;
         case 6 :
             printf("Intervalle de recherche\n");
             printf("Entrez la borne inferiure de la note\n");
             scanf("%f",&BI);
             printf("Entrez la borne superieure de la note\n");
             scanf("%f",&BS);
             construireListe(a,&L,BI,BS);
            break;
         case 7 :
             printf("Intervalle de recherche\n");
             printf("Entrez la borne inferiure de la note\n");
             scanf("%f",&BI);
             printf("Entrez la borne superieure de la note\n");
             scanf("%f",&BS);
             construireListe_trier(a,&L,BI,BS);
            break;
         case 8 :
            afficherLDC(L);
            break;
         case 9 :
            printf("Veuillez entrer l'ID de l'etudiant\n");
            scanf("%d",&id);
            if(L.queu!=NULL&&L.tete!=NULL)
            {
                L=supprimer_etudiant(L,id);
            }
            else
                printf("Liste vide\n");

            break;

         case 10 :
            a=list_to_tree(a,&L);
            break;
         case 11 :
            e=saisir(e);
            if(L.tete!=NULL&&L.queu!=NULL)
                 L=Inserer_milieu(L,e);
            else
                printf("Liste vide\n");
            break;

         case 12 :
            e=saisir(e);
            L=Ajout_trier(L,e);
            break;


         }


    }while(choix!=0);

    return 0;
}
