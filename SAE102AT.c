#include<stdio.h>
#include<wchar.h>
#define LMAX 30
#define CMAX 30

struct T_case
{
    int ligne;
    int colonne;
};
int hasard(int min, int max);
int lire_entier(int min, int max);
void parametres(int *L, int *C, int *lvl, int * firstPlayer);
void afficheGrille(int tab[][CMAX], int L, int C);

void main()
{
    srand((unsigned int)time(NULL));
    int grille[LMAX][CMAX] = {{0, 1, 1, 1, 1},{1, 1, 1, 1, 1},{1, 1, 1, 1, 1},{1, 1, 1, 1, 1},{1, 1, 1, 1, 1}};
    afficheGrille(grille, 5, 5);
}


void afficheGrille(int tab[][CMAX], int L, int C)
{
    for (int compteLigne = -1; compteLigne < L; compteLigne++)
    {
        if (compteLigne == -1)
        {
            for (int i = 0; i <= C; i++)
            {
                printf("\e[0;32m %3d\e[0m", i);
            }
            printf("\n");
        }
        else
        {
            for (int compteColonne = 0; compteColonne < C; compteColonne++)
            {
                if (compteColonne == 0)
                {
                    printf("\e[0;32m %3d\e[0m||", compteLigne + 1);
                }
                if (compteLigne == L - 1 && compteColonne == C - 1) printf("\e[7;34m%3c\e[0m|", '-');
                else if (tab[compteLigne][compteColonne] > 0)
                {
                    printf("\e[1;29m%3c\e[0m|", '-');
                }
                if (tab[compteLigne][compteColonne] == 0)
                {
                    printf("\e[1;31m%3d\e[0m|", tab[compteLigne][compteColonne]);
                }
            }
            printf("\n");
        }
    }
}
void parametres(int *L, int *C, int *lvl, int * firstPlayer)
{
    printf("Saisir le nombre de lignes : ");
    *L = lire_entier(5, LMAX);
    printf("\nSaisir le nombre de colonnes : ");
    *C = lire_entier(5, CMAX);
    printf("\nDe quel niveau est l'IA ? (de 1 à 4) : ");
    *lvl = lire_entier(1, 4);
    printf("\nQui commence ? Ordinateur (1), joueur (2) : ");
    *firstPlayer = lire_entier(1,2);
}
int lire_entier(int min, int max)
{
    int n;
    do
    {
        scanf("%d", &n);
        while(getchar()!='\n');
    } while (n < min || n > max);
    return n;
}
int hasard(int min, int max)
{
    int res;
    do
    {
        res = rand()%max;
    } while (res < min);
    return res;
}