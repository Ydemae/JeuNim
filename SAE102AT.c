#include<stdio.h>
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

void main()
{
    srand((unsigned int)time(NULL));
    struct T_case case1, case2;
    case1.ligne = 10;
    case2.colonne = 11;
    printf("%d et %d", case1.ligne, case2.colonne);
    int jsp = hasard(10, 20);
    printf("\n le nombre entre 10 et 20 est %d", jsp);
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