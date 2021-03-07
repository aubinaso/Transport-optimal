#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    float tab_X[100];//abscisses
    float tab_Y[100];//ordonnées
} coordonne; /*definition d'une structure pouvant
accueillir les coordonnées des sites de production et de demande*/


typedef struct /*definition d'une structure pour prendre la valeur minimale de cout de transport dans une matrice d'element ainsi que les indices*/
{
    float valeur;
    int ligne;
    int colonne;
    int prod;
    int demande;
} cout_min;

void afficher_matrice(int n,cout_min matrice[][n])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(j%n==0)
                printf("\n\t%f",matrice[i][j].valeur);
            else
                printf("  %f",matrice[i][j].valeur);
        }
    }
}

/*fonction pour trouver le minimum d'un tableau de matrice et les indices ligne-colonne*/
cout_min minimum(int n,cout_min C[][n])
{
    cout_min minimum;
    minimum.valeur=1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
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

/*fonction permettant de reduire une matrice*/
void reduire_matrice(int n,int ligne,int colonne,cout_min C[][n],cout_min C_reduit[][n-1])
{
    int i=0,indice_ligne=0,indice_colonne,j;
    while(i<n)
    {
        if(i==ligne)
            i++;//ne pas copier cette ligne
        j=0;
        indice_colonne=0;
        while(j<n)
        {
            if(j==colonne)
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

int main()
{
    /*definition des elements permettant de
    générer des valeurs aléatoire entre 0 et 1*/
    long int u;
    int a=0,b=1;//les valeurs minimale et maximale
    time(&u);
    srand(u);

    printf("entrer le nombre de site de production\n");
    int N;//variale pour contenir le nombre de site de production
    scanf("%d",&N);
    coordonne site_production;//coordonnées des sites de production
    coordonne site_demande;//cordonnées des sites de demande

    for(int i=0; i<N; i++)
    {
        site_production.tab_X[i]=a+(b-a)*((float)rand())/RAND_MAX;//l'abscisse du site de production numero i
        site_demande.tab_X[i]=a+(b-a)*((float)rand())/RAND_MAX;//l'abscisse du site de demande numero i
        site_demande.tab_Y[i]=a+(b-a)*((float)rand())/RAND_MAX;//l'ordonnée du site de demande numero i
        site_production.tab_Y[i]=a+(b-a)*((float)rand())/RAND_MAX;//l'ordonnée du site de production numero i
    }
    /*creation d'une matrice*/
    cout_min cout_transport[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout_transport[i][j].valeur=pow(site_production.tab_X[i]-site_demande.tab_X[j],2);
            cout_transport[i][j].valeur+=pow(site_production.tab_Y[i]-site_demande.tab_Y[j],2);
            cout_transport[i][j].ligne=i+1;
            cout_transport[i][j].colonne=j+1;
        }
    }
    cout_min minim=minimum(N,cout_transport);
    cout_min **matrice_reduit;
    matrice_reduit=cout_transport;

    int transport[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            transport[i][j]=0;
        }
    }

    float cout_total=0;
    afficher_matrice(N,cout_transport);
    /*printf("\napres une reduction\n");
    reduire_matrice(N,minim.ligne,minim.colonne,cout_transport,matrice_reduit1);
    afficher_matrice(N-1,matrice_reduit1);*/
    for(int i=0; i<N; i++)
    {
        minim=minimum(N-i,matrice_reduit);
        printf("\n\nle site de production numero %d livre au site de demande numero %d avec pour cout de transport de %f\n",minim.prod,minim.demande,minim.valeur);
        transport[minim.prod-1][minim.demande-1]=1;
        cout_total+=minim.valeur;
        reduire_matrice(N-i,minim.ligne,minim.colonne,cout_transport,matrice_reduit);
        /*afficher_matrice(N-i-1,matrice_reduit);*/
        printf("\n");
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(j%N==0)
                printf("\n\t%d",transport[i][j]);
            else
                printf("  %d",transport[i][j]);
        }
    }
    printf("\n\nle cout total du transport est %f\n",cout_total);

    return 0;
}

