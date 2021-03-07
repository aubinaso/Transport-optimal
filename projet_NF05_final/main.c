#include "simplex.h"

int main()
{
    int choix;
    printf("voulez vous entrerles valeurs ou alors l'ordinateur s'en occupe, 1 pour OUI et 0 pour non\n");
    scanf("%d",&choix);
    /*definition des elements permettant de
    générer des valeurs aléatoire entre 0 et 1*/
    long int u;
    time(&u);
    srand(u);

    printf("entrer le nombre de site de production\n");
    int N_p,N_d;//variale pour contenir le nombre de site de production
    scanf("%d",&N_p);
    printf("entrer le nombre de site de demande\n");
    scanf("%d",&N_d);
    site *site_production;//coordonnées des sites de production
    site *site_demande;//cordonnées des sites de demande

    site_demande=(site*)malloc(N_d*sizeof(site));
    site_production=(site*)malloc(N_p*sizeof(site));

    for(int i=0; i<N_p; i++)
    {
        site_production[i].X=1*((float)rand())/RAND_MAX;//l'abscisse du site de production numero i
        site_production[i].Y=1*((float)rand())/RAND_MAX;//l'ordonnée du site de production numero i
    }
    for(int i=0; i<N_d; i++)
    {
        site_demande[i].X=1*((float)rand())/RAND_MAX;//l'abscisse du site de demande numero i
        site_demande[i].Y=1*((float)rand())/RAND_MAX;//l'ordonnée du site de demande numero i
    }

    int indice=0;
    float volume=0;
    if(choix==1)
    {
        if(N_p<N_d)
        {
            printf("la quantite de site de production ne doit pas depasser %d\n",N_p);
            do
            {
                for(int i=0; i<N_d; i++)
                {

                    do
                    {
                        printf("entrer la quantite du site de demande numero %d (il doit etre inferieur ou egale a 1)\n",indice+1);
                        scanf("%f",&site_demande[indice].quantite);//la quantité du site de demande numero i
                    }
                    while(site_demande[indice].quantite>1);//la quantité du site de demande numero i
                    volume+=site_demande[i].quantite;
                }
            }
            while(volume>N_p);

            //generation des quatite des sites de productions
            float b=volume;
            indice=0;
            while(indice<N_d-1)
            {
                do
                {
                    printf("entrer la quantite du site de production numero %d (il doit etre inferieur a %d et a 1)\n",indice+1,b);
                    scanf("%f",&site_production[indice].quantite);
                }
                while(site_production[indice].quantite>1);
                b-=site_production[indice].quantite;
                indice++;
            }
            site_production[N_d-1].quantite=b-0.01;
        }
        else
        {

            for(int i=0; i<N_d; i++)
            {

                do
                {
                    printf("entrer la quantite du site de demande numero %d (il doit etre inferieur a 1)\n",indice+1);
                    scanf("%f",&site_demande[indice].quantite);//la quantité du site de demande numero i
                }
                while(site_demande[indice].quantite>1);//la quantité du site de demande numero i
                volume+=site_demande[i].quantite;
            }

            //generation des quatite des sites de productions
            float b=volume;
            indice=0;
            while(indice<N_p-1)
            {
                do
                {
                    printf("entrer la quantite du site de production numero %d (il doit etre inferieur a %d et a 1)\n",indice+1,b);
                    scanf("%f",&site_production[indice].quantite);
                }
                while(site_production[indice].quantite>1);
                b-=site_production[indice].quantite;
                indice++;
            }
            site_production[N_d-1].quantite=b+0.01;
        }
    }
    else
    {
        if(N_p>=N_d)
        {
            for(int i=0; i<N_d; i++)
            {
                site_demande[i].quantite=1*((float)rand())/RAND_MAX;//la quantité du site de demande numero i
                volume+=site_demande[i].quantite;
            }

            //generation des quatite des sites de productions
            float b=volume;
            int indice=0;
            while(indice<N_p-1)
            {
                do
                {
                    site_production[indice].quantite=b*((float)rand())/RAND_MAX;//la quantité du site de demande numero i
                }
                while(site_production[indice].quantite>1);
                b-=site_production[indice].quantite;
                indice++;
            }
            site_production[N_p-1].quantite=b+0.01;
        }
        else
        {
            do
            {
                for(int i=0; i<N_p; i++)
                {
                    site_production[i].quantite=1*((float)rand())/RAND_MAX;//la quantité du site de demande numero i
                    volume+=site_production[i].quantite;
                }
            }
            while(volume>N_d);
            //generation des quatite des sites de productions
            float b=volume;
            int indice=0;
            while(indice<N_d-1)
            {
                do
                {
                    site_demande[indice].quantite=b*((float)rand())/RAND_MAX;//la quantité du site de demande numero i
                }
                while(site_demande[indice].quantite>1);
                b-=site_demande[indice].quantite;
                indice++;
            }
            site_demande[N_d-1].quantite=b-0.01;
        }
    }

    printf("\n\nle site de demande est : \n");
    for(int i=0; i<N_d; i++)
    {
        printf("\t %f",site_demande[i].quantite);
    }
    printf("\n\nle site de production est : \n");
    for(int i=0; i<N_p; i++)
    {
        printf("\t %f",site_production[i].quantite);
    }
    printf("\n\n");

    //OK OK OK!!!


//constitution de la matrice transport


    float **transport;
    transport=(float**)malloc(N_p*sizeof(float*));
    for(int j=0; j<N_p; j++)
    {
        transport[j]=(float*)malloc(N_d*sizeof(float));
    }
    cout_min cout_transport[N_p][N_d];
    /*cout_min **cout_transport;
    cout_transport=(cout_min**)malloc(N_p*sizeof(cout_min*));
    for(int j=0; j<N_p; j++)
    {
        cout_transport[j]=(cout_min*)malloc(N_d*sizeof(cout_min));
    }*/





    for(int i=0; i<N_p; i++)
    {
        //calcul des couts de transport et enregistrement dans la matrice
        for(int j=0; j<N_d; j++)
        {
            cout_transport[i][j].valeur=pow(site_production[i].X-site_demande[j].X,2);
            cout_transport[i][j].valeur+=pow(site_production[i].Y-site_demande[j].Y,2);
            cout_transport[i][j].ligne=i+1;
            cout_transport[i][j].colonne=j+1;
        }
    }

    cout_min minim;
    cout_min matrice_reduit[N_p][N_d];//a allouer dynamique
    afficher_matrice(N_p,N_d,cout_transport);
    printf("\nc'est bon la matrice transport\n");
    copier(N_p,N_d,cout_transport,matrice_reduit);
    printf("\nla matrice reduit est : \n");
    afficher_matrice(N_p,N_d,matrice_reduit);
    printf("\n\n");


    for(int i=0; i<N_p; i++)
    {
        for(int j=0; j<N_d; j++)
        {
            transport[i][j]=0;
        }
    }

    int i=0,j=0;
    float vol;
    int vrai;
    for(int col=0; col<N_d; col++)
    {
        i=0,j=0;
        copier(N_p,N_d,cout_transport,matrice_reduit);
        afficher_matrice(N_p-i,N_d-j,matrice_reduit);
        while(site_demande[col].quantite!=0)
        {
            printf("\n%f\n",site_demande[col].quantite);
            minim=minimum(N_p-i,N_d-j,matrice_reduit);
            printf("\n la colonne du minimale est %d et sa ligne %d \n et on est a la colonne %d\n",minim.demande-1,minim.prod-1,col);
            if(site_demande[minim.demande-1].quantite==site_production[minim.prod-1].quantite)
            {
                vol=site_demande[minim.demande-1].quantite;
                printf("\nla demande est %f et la production %f\n",site_demande[minim.demande-1].quantite, site_production[minim.prod-1].quantite);
                printf("\nj'ai trouve %f\n",vol);
                vrai=0;
                reduire_matrice(N_p-i,N_d-j,minim.ligne,minim.colonne,matrice_reduit,matrice_reduit);
                afficher_matrice(N_p-i,N_d-j,matrice_reduit);
                i++;
                j++;
            }
            else if(site_demande[minim.demande-1].quantite>site_production[minim.prod-1].quantite)
            {
                vol=site_production[minim.prod-1].quantite;
                printf("\nla demande est %f et la production %f\n",site_demande[minim.demande-1].quantite, site_production[minim.prod-1].quantite);
                printf("\nj'ai trouve %f\n",vol);
                vrai=1;
                reduire_ligne_matrice(N_p-i,N_d-j,minim.ligne,matrice_reduit,matrice_reduit);
                afficher_matrice(N_p-i,N_d-j,matrice_reduit);
                i++;
            }
            else
            {
                vol=site_demande[minim.demande-1].quantite;
                printf("\nla demande est %f et la production %f\n",site_demande[minim.demande-1].quantite, site_production[minim.prod-1].quantite);
                printf("\nj'ai trouve %f\n",vol);
                vrai=2;
                reduire_colonne_matrice(N_p-i,N_d-j,minim.colonne,matrice_reduit,matrice_reduit);
                afficher_matrice(N_p-i,N_d-j,matrice_reduit);
                j++;
            }
            if(minim.demande-1==col)
            {
                if(vrai==0)
                {
                    site_demande[col].quantite=0;
                    site_production[minim.prod-1].quantite=0;
                }
                else if(vrai==1)
                {
                    site_demande[col].quantite-=vol;
                    site_production[minim.prod-1].quantite=0;
                }
                else
                {
                    site_demande[col].quantite=0;
                    site_production[minim.prod-1].quantite-=vol;
                }
                printf("\nj'ai affecter\n");
                transport[minim.prod-1][col]=vol;
                printf("\nla valeur a affecter est %f\n",vol);
            }
        }
    }

    float cout_total=0;
    for(int i=0; i<N_p; i++)
    {
        for(int j=0; j<N_d; j++)
        {
            if(j%N_d==0)
                printf("\n\t%f",transport[i][j]);
            else
                printf("  %f",transport[i][j]);

            if(transport[i][j]!=0)
            {
                cout_total+=(transport[i][j]*cout_transport[i][j].valeur);
            }
        }
    }

    printf("\n\nle prix total de transport est %f\n",cout_total);

    printf("\nc'est bon\n");
    for(int j=0; j<N_p; j++)
    {
        free(transport[j]);
    }
    free(transport);
    /*for(int j=0; j<N_p; j++)
    {
        free(cout_transport[j]);
    }
    free(cout_transport);*/
    free(site_demande);//on libère la memoire
    free(site_production);//on libère la memoire
    return 0;
}
