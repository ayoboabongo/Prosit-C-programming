#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>

etudiant saisir(etudiant e)
{
    printf("ID\n");
    scanf("%d",&e.ID);
    printf("Nom\n");
    scanf("%s",e.nom);
    printf("Prenom\n");
    scanf("%s",e.prenom);
    printf("Nivau\n");
    scanf("%d",&e.niv);
    printf("Moyenne\n");
    scanf("%f",&e.moy);

    return e;

}

abr initialiser(etudiant e)
{

    struct Noeud* nouv;
        nouv=(struct Noeud*)malloc(sizeof(struct Noeud));

            nouv->e=e;
            nouv->FG=NULL;
            nouv->FD=NULL;


   return nouv;
}

abr inserer (abr a,etudiant e)
{

   if(a==NULL)

      a=initialiser(e);

   else
   {
       if(e.moy<=a->e.moy)
        a->FG=inserer(a->FG,e);

       else
        a->FD=inserer(a->FD,e);
   }

   return a;
}

abr construireArbre (abr a,char nomFich[])
{
    etudiant e;

    FILE *fichier=NULL;
    fichier=fopen(nomFich,"r");
    printf("depart");

        while((fscanf(fichier,"%d %s %s %d %f",&e.ID,e.nom,e.prenom,&e.niv,&e.moy))!=EOF)
        {

            a=inserer(a,e);
        }
        fclose(fichier);


    return a;
}

void afficher(abr a)
{
    if(a!=NULL)
    {
        afficher(a->FD);
        printf("\nID : %d \nNom : %s \nPrenom : %s \n Niveau : %d \n Moyenne :%.2f\n",a->e.ID,a->e.nom,a->e.prenom,a->e.niv,a->e.moy);
        afficher(a->FG);

    }
}
int calculerNombre(abr a)
{
    if(a!=NULL)
        return (calculerNombre(a->FG)+calculerNombre(a->FD)+1);

}

LDC Inserer_tete_LDC (LDC L,etudiant e)
{
    struct Noeud* nouv;
    nouv = (struct Noeud*)malloc(sizeof(struct Noeud));
    if(!nouv)
        printf("Espace memoire insuffisant\n");
    else
        {
            nouv->e =e;
            nouv->FG = NULL;
            nouv->FD = L.tete;
            if(L.tete!=NULL&&L.queu!=NULL)
                L.tete->FG=nouv;
            else // liste initiale vide
                L.queu = nouv;
                L.tete = nouv;
        }

    return(L);
}


void construireListe(abr a,LDC *L, float BI, float BS)
{
      if(a!=NULL)
      {
         if(a->e.moy>=BI&&a->e.moy<BS)
            *L=Inserer_tete_LDC (*L,a->e);

         if(a->e.moy<BI)
             construireListe(a->FG,L,BI,BS);
         if(a->e.moy>=BI)
             construireListe(a->FD,L,BI,BS);
      }
}


void construireListe_trier(abr a,LDC *L, float BI, float BS)
{
      if(a!=NULL)
      {
         if(a->e.moy>=BI&&a->e.moy<BS)
            construireListe_trier(a->FG,L,BI,BS);

         if(a->e.moy>=BI&&a->e.moy<BS)
            *L=Inserer_tete_LDC (*L,a->e);

         if(a->e.moy>=BI)
            construireListe_trier(a->FD,L,BI,BS);
      }
}

void afficherLDC(LDC L)
{
     struct Noeud* p;
     if(L.tete==NULL&&L.queu==NULL)
        printf ("Liste vide\n");
    else
       {
           p = L.tete;
           while(p)
            {
                printf("\n ID : %d \n Nom : %s \n Prenom : %s \nNiveau : %d \n Moyenne : %.2f", p->e.ID,p->e.nom,p->e.prenom,p->e.niv,p->e.moy);
                p = p->FD;
            }

       }
}

LDC supprimer_etudiant(LDC L,int id)
{
    struct Noeud* P=L.tete;

    while(P&&P->e.ID!=id)
        P=P->FD;

    if(P)
    {
        if(P==L.tete)
        {
            if(P->FD==NULL)
            {
                L.tete=NULL;
                L.queu=NULL;
            }
            else
            {
                L.tete=L.tete->FD;
                L.tete->FD=NULL;
            }
            free(P);

        }
        else
        {
            if(P==L.queu)
            {
                if(L.queu==L.tete)
                {
                    L.tete=NULL;
                    L.queu=NULL;

                }
                else
                {
                    L.queu=L.queu->FG;
                    L.queu->FD=NULL;

                }
                free(P);

            }
            else
            {
                (P->FG)->FD=P->FD;
                (P->FD)->FG=P->FG;
                free(P);
                P=NULL;
            }

        }
    }
    else
        printf("Erreur Etudiant introuvable\n");

    return L;
}

abr list_to_tree(abr a,LDC *L)
{
    struct Noeud * P=(*L).tete;
    while(P)
    {
        a=inserer (a,P->e);
        P=P->FD;
    }

    return a;
}

LDC Inserer_milieu(LDC L,etudiant e)
{
    struct Noeud* P=L.tete,*nouv;

    while(P&&P->e.niv!=e.niv)
        P=P->FD;

    if(P)
    {
        nouv=(struct Noeud*)malloc(sizeof(struct Noeud));
        nouv->e=e;
        nouv->FG=NULL;
        nouv->FD=NULL;

        if(P==L.tete)
        {
            nouv->FD=L.tete;
            L.tete->FG=nouv;
            L.tete=nouv;

        }

        else
        {
            nouv->FD=P;
            nouv->FG=P->FG;
            (P->FG)->FD=nouv;
            P->FG=nouv;
        }


    }
    else
        printf("Erreur niveau introuvable\n");

    return L;
}

LDC Ajout_trier(LDC L,etudiant e)
{
    struct Noeud *P=L.tete,*nouv;
    nouv=(struct Noeud*)malloc(sizeof(struct Noeud));
    if(nouv!=NULL)
    {
        nouv->e=e;
        nouv->FG=NULL;
        nouv->FD=NULL;

        if((L.tete==NULL)&&(L.queu==NULL))
        {
            L.tete=nouv;
            L.queu=nouv;
        }

        else if(e.niv<=(L.tete)->e.niv)
        {
            nouv->FD=L.tete;
            L.tete->FG=nouv;
            L.tete=nouv;

        }
        else
        {
            while(P&&P->e.niv<=e.niv)
               P=P->FD;

               if(P)
               {
                   nouv->FD=P->FD;
                   (P->FD)->FG=nouv;
                   nouv->FG=P;
                   P->FD=nouv;

               }
               else
               {
                   nouv->FG=L.queu;
                   L.queu->FD=nouv;
                   L.queu=nouv;
               }

        }
    }
    else
        printf("Impossible d'allouer de la memoire\n");

   return L;

}

