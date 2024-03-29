#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define LMAX 30
#define CMAX 30


typedef struct
{
    int ligne;
    int colonne;
} T_case;

int lire_entier(int min, int max); //lit un entier entre une valeur minimum et maximum
void creerTabNimber(int nlig, int ncol, int tabnim[][CMAX]); //Creer le tableau contenant tous les nimber du plateau selon le nombre de ligne et de colonne
void echange(int *a, int *b);//echange deux variables de type int
void voisines(int L, int C, T_case tabvois[], T_case Acase, int *n);//définie les voisines d'une case donnée en paramètre et les range dans une table
int verifieCase(int L, int C, T_case Acase);//définie si une case est dans les limites du plateau ou non en fonction du nombre de lignes et de colonnes
void coupJoueur(int tab[][CMAX], int L, int C, T_case Acase);//Gère le coup du joueur
void initGrille(int tab[][CMAX], int L, int C);//Initialise la grille en plaçant le pion à l'indice 0 0 de la grille et des 1 dans toutes les autres cases
void afficheGrille(int tab[][CMAX], int L, int C, T_case *Acase);//Affiche la grille en fonction du nombre de lignes et de colonnes. La fonction renvoit aussi la case actuelle sur laquelle se trouve le pion.
void parametres(int *nlig, int *ncol, int *niveau, int *next);//fait saisir à l'utilisateur le nombre de lignes et de colonnes de l', de la grille, le niveaux de l'IA et le joueur qui a l'initiative.
int hasard(int min, int max);//Renvoi un nombre au hasard entre les valeurs min et max
int nimber(T_case Acase, int tabnim[][CMAX]);//définis le nimber d'une case
T_case coupOrdiHasard(int nlig, int ncol, T_case Acase);//définis le coup au hasard de l'ordi
T_case coupOrdiGagnant(int nlig, int ncol, T_case Acase, int tabnim[][CMAX]);//définis le meilleur coup de l'ordi en utilisant le tableau des nimber
void coupOrdi(int nlig, int ncol, T_case Acase, int tabnim[][CMAX], int tab[][CMAX], int niveau);//Gère le coup de l'ordi à l'aide de coupOrdiGagnant et CoupOrdiHasard
void afficheRegles();//Affiche les règles du jeu


int main()
{
    T_case actualCase;
    int nlig, ncol, niveau, next;
    srand((unsigned int)time(NULL));
    int grille[LMAX][CMAX], tabnim[LMAX][CMAX];
    afficheRegles();
    parametres(&nlig, &ncol, &niveau, &next);
    creerTabNimber(nlig, ncol, tabnim);
    initGrille(grille, nlig, ncol);
    afficheGrille(grille, nlig, ncol, &actualCase);
    while (actualCase.ligne != nlig - 1 || actualCase.colonne != ncol - 1)
    {
        for (int i = 0; i < 2; i++)
        {
            sleep(1);
            if (next == 1)
            {
                coupOrdi(nlig, ncol, actualCase, tabnim, grille, niveau);
                next = 2;
            }
            else
            {
                coupJoueur(grille, nlig, ncol, actualCase);
                next = 1;
            }
            afficheGrille(grille, nlig, ncol, &actualCase);
            if (actualCase.ligne == nlig - 1 && actualCase.colonne == ncol - 1) break;
        }
    }
    if (next == 1) printf("\n\e[7;35mFelicitations ! Vous avez gagne !\e[0m");
    else printf("\n\e[7;34mL'ordinateur a gagne ! You lose !\e[0m");
    return 0;
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
            printf("\n\e[7;31mErreur !\e[0m\n");
    } while (n < min || n > max);
    return n;
}
void creerTabNimber(int nlig, int ncol, int tabnim[][CMAX])
{
    int i,j, k, n, test0;
    T_case tabvois[4];
    tabnim[nlig-1][ncol-1] = 0;
    for (j = ncol - 1; j >= 0; j --)
        for (i = nlig - 1; i >= 0; i--)
        {
            test0 = 0;
            T_case actualCase = {i, j};
            voisines(nlig, ncol, tabvois, actualCase, &n);
            for (k = 0; k < n; k++ ) if (tabnim[tabvois[k].ligne][tabvois[k].colonne] == 0) test0 += 1;
            if (test0 != 0) tabnim[i][j] = 1;
            else tabnim[i][j] = 0;
        }
}
void echange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void voisines(int L, int C, T_case tabvois[], T_case Acase, int *n)
{
    *n = 4;
    int i = 0;
    T_case sud1 = {Acase.ligne + 1, Acase.colonne};
    T_case sud2 = {Acase.ligne + 2, Acase.colonne};
    T_case est1 = {Acase.ligne, Acase.colonne + 1};
    T_case est2 = {Acase.ligne, Acase.colonne + 2};
    if (verifieCase(L, C, sud1) == 1)
    {
        tabvois[i] = sud1;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase( L, C, sud2) == 1)
    {
        tabvois[i] = sud2;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase(L, C, est1) == 1)
    {
        tabvois[i] = est1;
        i += 1;
    }
    else
        *n -= 1;
    if (verifieCase( L, C, est2) == 1)
    {
        tabvois[i] = est2;
        i += 1;
    }
    else
        *n -= 1;
}
int verifieCase(int L, int C, T_case Acase)
{
    if (Acase.colonne < 0 || Acase.colonne >= C || Acase.ligne < 0 || Acase.ligne >= L)
        return -1;
    else
        return 1;
}
void coupJoueur(int tab[][CMAX], int L, int C, T_case Acase)
{
    T_case Tabvoisines[CMAX];
    int n, i;
    voisines(L, C, Tabvoisines, Acase, &n);
    printf("\e[0;35mC'est ton tour !\nVers quelle case veux-tu deplacer le pion? \e[0m");
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
                if (compteLigne == L - 1 && compteColonne == C - 1 && tab[compteLigne][compteColonne] != 0)
                    printf("\e[7;34m%3c|\e[0m", '-');
                else if (tab[compteLigne][compteColonne] > 0)
                {
                    printf("\e[1;29m%3c\e[0m|", '-');
                }
                if (tab[compteLigne][compteColonne] == 0)
                {
                    if (compteLigne == L - 1 && compteColonne == C - 1) printf("\e[7;35m%3d|\e[0m", 0);
                    else printf("\e[1;35m%3d\e[0m|", 0);
                    T_case temp = {compteLigne, compteColonne};
                    *Acase = temp;
                }
            }
            printf("\n");
        }
    }
}
void parametres(int *nlig, int *ncol, int *niveau, int *next)
{
    printf("Saisir le nombre de lignes : ");
    *nlig = lire_entier(5, LMAX);
    printf("Saisir le nombre de colonnes : ");
    *ncol = lire_entier(5, CMAX);
    printf("De quel niveau est l'IA ? (de 1 a 4) : ");
    *niveau = lire_entier(1, 4);
    printf("Qui commence ? Ordinateur (1), joueur (2) : ");
    *next = lire_entier(1, 2);
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
int nimber( T_case Acase, int tabnim[][CMAX])
{
    return tabnim[Acase.ligne][Acase.colonne];
}
T_case coupOrdiHasard(int nlig, int ncol, T_case Acase)
{
    int n;
    T_case tabvois[4];
    voisines(nlig, ncol, tabvois, Acase, &n);
    int coup = hasard(1, n);
    return tabvois[coup - 1];
}
T_case coupOrdiGagnant(int nlig, int ncol, T_case Acase, int tabnim[][CMAX])
{
    int n, i;
    T_case tabvois[4];
    voisines(nlig, ncol, tabvois, Acase, &n);
    for (i = 0; i < n; i++)
        if (nimber(tabvois[i], tabnim) == 0)
        {
            T_case rep = {tabvois[i].ligne, tabvois[i].colonne};
            return rep;
        }
    return coupOrdiHasard(nlig, ncol, Acase);
}
void coupOrdi(int nlig, int ncol, T_case Acase, int tabnim[][CMAX], int tab[][CMAX], int niveau)
{
    int randomNbe = hasard(1, 3);
    T_case caseVisee;
    if (niveau == 1)
    {
        caseVisee = coupOrdiHasard(nlig, ncol, Acase);
    }
    else if (niveau == 2)
    {
        if (randomNbe == 1) caseVisee = coupOrdiGagnant(nlig, ncol, Acase, tabnim);
        else caseVisee = coupOrdiHasard(nlig, ncol, Acase);
    }
    else if (niveau == 3)
    {
        if (randomNbe == 3) caseVisee = coupOrdiHasard(nlig, ncol, Acase);
        else caseVisee = coupOrdiGagnant(nlig, ncol, Acase, tabnim);
    }
    else caseVisee = coupOrdiGagnant(nlig, ncol, Acase, tabnim);
    printf("\n\e[0;34mTour de l'ordinateur :\nL'ordinateur deplace le pion en case (%d, %d) !\e[0m\n", caseVisee.ligne + 1, caseVisee.colonne + 1);
    echange(&tab[caseVisee.ligne][caseVisee.colonne], &tab[Acase.ligne][Acase.colonne]);

}
void afficheRegles()
{   
    int veutAfficheRegles;
    printf("Bienvenue,\nvous etes en train de jouer au Jeu Nim edition AT mais peut etre que c'est votre premiere fois, souhaitez vous voir les regles du jeu? (repondre 1 pour oui, 2 pour non)");
    veutAfficheRegles = lire_entier(1,2);
    if(veutAfficheRegles == 1) printf("\nCe jeu se joue seul et se deroule sur un plateau defini par un nombre de ligne et de colonne \e[0;33md'au moins 5 par 5 \e[0m comme celui ci :\n\e[0;32m0 %3d  %3d  %3d  %3d  %3d\e[0m\n\e[0;32m1\e[0m||\e[1;35m  0\e[0m|   -|   -|   -|   -|\n\e[0;32m2\e[0m||  -|   -|   -|   -|   -|\n\e[0;32m3\e[0m||  -|   -|   -|   -|   -|\n\e[0;32m4\e[0m||  -|   -|   -|   -|   -|\n\e[0;32m5\e[0m||  -|   -|   -|   -|\e[7;34m   -|\e[0m\nLe 0 represente le pion que vous pourrez deplacer dans deux directions, vers le sud et vers le nord de 1 ou 2 cases, votre but est de faire tomber le pion dans le puit bleu en bas a droite du plateau. Nous esperons que cette breve explication vous aura ete utile mais rien n'est mieux qu'une partie pour comprendre le fonctionnement du jeu, nous vous souhaitons donc bon jeu, \e[1;33mHave Fun !\e[0m\n\n", 1, 2, 3, 4, 5);
}