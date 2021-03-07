#ifndef SIMPLEX_H_INCLUDED
#define SIMPLEX_H_INCLUDED



#endif // SIMPLEX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct /*definition d'une structure pour prendre la valeur minimale de cout de transport dans une matrice d'element ainsi que les indices*/
{
    float valeur;//la valeur
    int ligne;//ligne dans la matrice iniiale par rapport à la matrice reduit
    int colonne;//colonne dans la matrice iniiale par rapport à la matrice reduit
    int prod;//colonne initiale dans la matrice iniiale
    int demande;//colonne initiale dans la matrice iniiale
} cout_min;

typedef struct
{
    float X;//abscisses
    float Y;//ordonnées
    float quantite;//la quantité que veux le site ou que le site peut disposer
} site; /*definition d'une structure pouvant
accueillir les coordonnées des sites de production et de demande*/

void afficher_matrice(int ligne,int colonne,cout_min matrice[][colonne])
{
    for(int i=0; i<ligne; i++)
    {
        for(int j=0; j<colonne; j++)
        {
            if(j%colonne==0)
                printf("\n\t%.2f",matrice[i][j].valeur);
            else
                printf("  %.2f",matrice[i][j].valeur);
        }
    }
}

cout_min minimum(int ligne,int colonne,cout_min C[][colonne])
{
    cout_min minimum;
    minimum.valeur=1;
    for(int i=0; i<ligne; i++)
    {
        for(int j=0; j<colonne; j++)
        {
            if(minimum.valeur>=C[i][j].valeur)
            {
                minimum.valeur=C[i][j].valeur;
                minimum.ligne=i;
                minimum.colonne=j;
                minimum.demande=C[i][j].colonne;
                minimum.prod=C[i][j].ligne;
            }
        }
    }
    return minimum;
}
//fonction permettant de reduire une ligne et une colonne
void reduire_matrice(int ligne,int colonne,int ligne_ini,int colonne_ini,cout_min C[][colonne],cout_min C_reduit[][colonne-1])
{
    int i=0,indice_ligne=0,indice_colonne,j;
    while(i<ligne)
    {
        if(i==ligne_ini)
            i++;//ne pas copier cette ligne
        j=0;
        indice_colonne=0;
        while(j<colonne)
        {
            if(j==colonne_ini)
                j++;//ne pas copier cette colonne
            C_reduit[indice_ligne][indice_colonne].valeur=C[i][j].valeur;
            C_reduit[indice_ligne][indice_colonne].ligne=C[i][j].ligne;
            C_reduit[indice_ligne][indice_colonne].colonne=C[i][j].colonne;
            j++;
            indice_colonne++;
        }
        i++;
        indice_ligne++;
    }
}

void copier(int ligne,int colonne,cout_min C[][colonne],cout_min C_copie[][colonne])
{
    for (int i=0;i<ligne;i++)
    {
        for (int j=0;j<colonne;j++)
        {
            C_copie[i][j].colonne=C[i][j].colonne;
            C_copie[i][j].demande=C[i][j].demande;
            C_copie[i][j].ligne=C[i][j].ligne;
            C_copie[i][j].prod=C[i][j].prod;
            C_copie[i][j].valeur=C[i][j].valeur;
        }
    }
}
//fonction permettant de reduire une ligne
void reduire_ligne_matrice(int ligne,int colonne,int ligne_ini,cout_min C[][colonne],cout_min C_reduit[][colonne])
{
    int i=0,indice_ligne=0,indice_colonne,j;
    while(i<ligne)
    {
        if(i==ligne_ini)
            i++;//ne pas copier cette ligne
        j=0;
        indice_colonne=0;
        while(j<colonne)
        {
            C_reduit[indice_ligne][indice_colonne].valeur=C[i][j].valeur;
            C_reduit[indice_ligne][indice_colonne].ligne=C[i][j].ligne;
            C_reduit[indice_ligne][indice_colonne].colonne=C[i][j].colonne;
            j++;
            indice_colonne++;
        }
        i++;
        indice_ligne++;
    }
}
//fonction permettant de reduire une colonne
void reduire_colonne_matrice(int ligne,int colonne,int colonne_ini,cout_min C[][colonne],cout_min C_reduit[][colonne-1])
{
    int i=0,indice_ligne=0,indice_colonne,j;
    while(i<ligne)
    {
        j=0;
        indice_colonne=0;
        while(j<colonne)
        {
            if(j==colonne_ini)
                j++;//ne pas copier cette colonne
            C_reduit[indice_ligne][indice_colonne].valeur=C[i][j].valeur;
            C_reduit[indice_ligne][indice_colonne].ligne=C[i][j].ligne;
            C_reduit[indice_ligne][indice_colonne].colonne=C[i][j].colonne;
            j++;
            indice_colonne++;
        }
        i++;
        indice_ligne++;
    }
}
