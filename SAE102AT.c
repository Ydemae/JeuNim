#include<stdio.h>

struct T_case
{
    int ligne;
    int colonne;
};
int hasard(int min, int max);

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


int hasard(int min, int max)
{
    int res;
    do
    {
        res = rand()%max;
    } while (res < min);
    return res;
}