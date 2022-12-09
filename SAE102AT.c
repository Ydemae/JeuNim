#include <stdio.h>
#include <stdlib.h>
#define LMAX 30
#define CMAX 30

typedef struct
{
    int ligne;
    int colonne;
} T_case;

void echange(int *a, int *b);
void voisines(int tab[][CMAX], int L, int C, T_case tabvois[], T_case Acase, int *n);
int verifieCase(int tab[][CMAX], int L, int C, T_case Acase);
int hasard(int min, int max);
int lire_entier(int min, int max);
void parametres(int *L, int *C, int *lvl, int *firstPlayer);
void afficheGrille(int tab[][CMAX], int L, int C, T_case *Acase);
void initGrille(int tab[][CMAX], int L, int C);
void coupJoueur(int tab[][CMAX], int L, int C, T_case Acase);

void main()
{
    T_case TheCase, TabVois[4];
    int n = 0;
    srand((unsigned int)time(NULL));
    int grille[LMAX][CMAX];
    int TabVoisines[LMAX];
    initGrille(grille, 5, 5);
    afficheGrille(grille, 5, 5, &TheCase);
    coupJoueur(grille, 5, 5, TheCase);
    afficheGrille(grille, 5, 5, &TheCase);
    printf("\n %d %d ", TheCase.ligne, TheCase.colonne);
}

void echange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void voisines(int tab[][CMAX], int L, int C, T_case tabvois[], T_case Acase, int *n)
{
    *n = 4;
    int i = 0;
    T_case sud1 = {Acase.ligne + 1, Acase.colonne};
    T_case sud2 = {Acase.ligne + 2, Acase.colonne};
    T_case est1 = {Acase.ligne, Acase.colonne + 1};
    T_case est2 = {Acase.ligne, Acase.colonne + 2};
    if (verifieCase(tab, L, C, sud1) == 1)
    {
        tabvois[i] = sud1;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase(tab, L, C, sud2) == 1)
    {
        tabvois[i] = sud2;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase(tab, L, C, est1) == 1)
    {
        tabvois[i] = est1;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase(tab, L, C, est2) == 1)
    {
        tabvois[i] = est2;
        i += 1;
    }
    else
        *n -= 1;
}
int verifieCase(int tab[][CMAX], int L, int C, T_case Acase)
{
    if (Acase.colonne < 0 || Acase.colonne >= L || Acase.ligne < 0 || Acase.ligne >= C || tab[Acase.ligne][Acase.colonne] != 1)
        return -1;
    else
        return 1;
}
void coupJoueur(int tab[][CMAX], int L, int C, T_case Acase)
{
    T_case Tabvoisines[CMAX];
    int n, i;
    voisines(tab, L, C, Tabvoisines, Acase, &n);
    printf("C'est ton tour !\nGet your shit together ! ");
    for (i = 1; i <= n; i++)
        printf(" %d : (%d, %d)", i, Tabvoisines[i - 1].ligne + 1, Tabvoisines[i - 1].colonne + 1);
    printf("\n");
    int coord = lire_entier(1, n);
    echange(&tab[Acase.ligne][Acase.colonne], &tab[Tabvoisines[coord - 1].ligne][Tabvoisines[coord - 1].colonne]);
}
void initGrille(int tab[][CMAX], int L, int C)
{
    int i, j;
    tab[0][0] = 0;
    for (i = 0; i < L; i++)
        for (j = 0; j < C; j++)
        {
            if (i == 0 && j == 0)
                continue;
            else
                tab[i][j] = 1;
        }
}
void afficheGrille(int tab[][CMAX], int L, int C, T_case *Acase)
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
                if (compteLigne == L - 1 && compteColonne == C - 1)
                    printf("\e[7;34m%3c|\e[0m", '-');
                else if (tab[compteLigne][compteColonne] > 0)
                {
                    printf("\e[1;29m%3c\e[0m|", '-');
                }
                if (tab[compteLigne][compteColonne] == 0)
                {
                    printf("\e[1;35m%3d\e[0m|", 0);
                    T_case temp = {compteLigne, compteColonne};
                    *Acase = temp;
                }
            }
            printf("\n");
        }
    }
}
void parametres(int *L, int *C, int *lvl, int *firstPlayer)
{
    printf("Saisir le nombre de lignes : ");
    *L = lire_entier(5, LMAX);
    printf("\nSaisir le nombre de colonnes : ");
    *C = lire_entier(5, CMAX);
    printf("\nDe quel niveau est l'IA ? (de 1 à 4) : ");
    *lvl = lire_entier(1, 4);
    printf("\nQui commence ? Ordinateur (1), joueur (2) : ");
    *firstPlayer = lire_entier(1, 2);
}
int lire_entier(int min, int max)
{
    int n;
    do
    {
        scanf("%d", &n);
        while (getchar() != '\n')
            ;
        if (n < min || n > max)
            printf("\nErreur !\n");
    } while (n < min || n > max);
    return n;
}
int hasard(int min, int max)
{
    int res;
    do
    {
        res = rand() % max;
    } while (res < min);
    return res;
}