#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

 struct etudiant
{
    int ID;
    char nom[25];
    char prenom[25];
    int niv;
    float moy;
};typedef struct etudiant etudiant;

typedef struct Noeud
{
    etudiant e;
    struct Noeud* FG;
    struct Noeud* FD;
}Noeud;
typedef struct Noeud *abr;

typedef struct listeLDC
{
    Noeud* tete;
    Noeud* queu;
}LDC;

etudiant saisir(etudiant e);
abr initialiser(etudiant e);
abr inserer (abr a,etudiant e);
abr construireArbre (abr a,char nomFich[]);
void afficher(abr a);
int calculerNombre(abr a);
LDC Inserer_tete_LDC (LDC L,etudiant e);
void construireListe(abr a,LDC *L, float BI, float BS);
void construireListe_trier(abr a,LDC *L, float BI, float BS);
void afficherLDC(LDC L);
LDC supprimer_etudiant(LDC L,int id) ;
abr list_to_tree(abr a,LDC *L) ;
LDC Inserer_milieu(LDC L,etudiant e);
LDC Ajout_trier(LDC L,etudiant e) ;

#endif // HEADER_H_INCLUDED
