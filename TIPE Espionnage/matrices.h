#pragma once
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif  // _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "vecteurs.h"

/* ************** */
/* ** Matrices ** */
/* ************** */

/* ##################################################### */
/* ##################################################### */
/* ####################### DEFINES ##################### */
/* ##################################################### */
/* ##################################################### */

#define BIG_SQUARE_MATRIX_SIZE 100 // Taille minimale d'une matrice carrée considérée comme "grande" // /!\ 3 -> problèmes

#ifndef EMPTY
#define EMPTY 0                   // Taille d'un élément vide
#endif

/* ##################################################### */
/* ##################################################### */
/* ####################### Macros ###################### */
/* ##################################################### */
/* ##################################################### */

/* ##################################################### */
/* ##################################################### */
/* ####################### Types ####################### */
/* ##################################################### */
/* ##################################################### */

typedef double** matrix_double; // Matrice de doubles de format quelconque
typedef int**    matrix_int;    // Matrice d'entiers de format quelconque

/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */

struct mat_d // Matrice de doubles avec sa taille
{
    matrix_double data;      // Données de la matrice (doubles)
    unsigned int *rows, *cols; // Nombre de lignes resp. de colonnes
};

struct mat_i // Matrice d'entiers avec sa taille
{
    matrix_int data;         // Données de la matrice (entiers)
    unsigned int *rows, *cols; // Nombre de lignes resp. de colonnes
};

typedef struct mat_d mat_d;
typedef struct mat_i mat_i;

/* ##################################################### */
/* ##################################################### */
/* ###################### En-têtes ##################### */
/* ##################################################### */
/* ##################################################### */

/* ***************************************************** */
/* **************** Fonctions standards **************** */
/* ***************************************************** */

// Initialisation (Permet d'initialiser la matrice en affectant NULL à leur pointeur et EMPTY à leurs tailles)
void init_mat_d(mat_d* a); // Matrice de doubles
void init_mat_i(mat_i* a); // Matrice d'entiers

// Destruction (mémoire) d'une matrice
void destroy_mat_d(mat_d* a);
void destroy_mat_i(mat_i* a);

// Matrices nulles
void creer_nulle_d(mat_d* a, unsigned int n, unsigned m); // Crée la matrice nulle de doubles de taille n x m
void creer_nulle_i(mat_i* a, unsigned int n, unsigned m); // Crée la matrice nulle d'entiers de taille n x m

// Matrices identité
void creer_identite_d(mat_d* a, unsigned int n); // Crée la matrice identité de doubles de taille n
void creer_identite_i(mat_i* a, unsigned int n); // Crée la matrice identité d'entiers de taille n

// Matrices diagonales
void diag_d(mat_d* a, vect_d v); // Crée une matrice diagonale de la taille du vecteur de v et rempli des valeurs de v prises dans l'ordre
void diag_i(mat_i* a, vect_i v); // Crée une matrice diagonale de la taille du vecteur de v et rempli des valeurs de v prises dans l'ordre

// Remplir matrice
void fill_d(mat_d* a, double v); // Rempli a de v (double)
void fill_i(mat_i* a, int v);    // Rempli a de v (entier)

// Augmenter une matrice
void add_rows_d(mat_d* a, unsigned int n, double val); // Ajoute n lignes en bas d'une matrice de doubles
void add_rows_i(mat_i* a, unsigned int n, int val);    // Ajoute n lignes en bas d'une matrice d'entiers
void add_cols_d(mat_d* a, unsigned int n, double val); // Ajoute n colonnes à droite d'une matrice de doubles
void add_cols_i(mat_i* a, unsigned int n, int val);    // Ajoute n colonnes à droite d'une matrice d'entiers

// Supprimer dans une matrice
void del_rows_d(mat_d* a, unsigned int n); // Supprimer n lignes à partir de la dernière lignes (bas) d'une matrice de doubles
void del_rows_i(mat_i* a, unsigned int n); // Supprimer n lignes à partir de la dernière lignes (bas) d'une matrice de d'entiers
void del_cols_d(mat_d* a, unsigned int n); // Supprimer n colonnes à partir de la dernière colonne (droite) d'une matrice de doubles
void del_cols_i(mat_i* a, unsigned int n); // Supprimer n colonnes à partir de la dernière colonne (droite) d'une matrice de d'entiers

// Récupérer une colonne
void recup_col_d(vect_d* rec, const mat_d A, unsigned int i); // Récupère dans rec la colonne 0 <= i <= M-1 si A (double) est de taille N x M
void recup_col_i(vect_i* rec, const mat_i A, unsigned int i); // Récupère dans rec la colonne 0 <= i <= M-1 si A (entiers) est de taille N x M

// Récupérer une ligne
void recup_row_d(vect_d* rec, const mat_d A, unsigned int i); // Récupère dans rec la ligne 0 <= i <= N-1 si A (double) est de taille N x M
void recup_row_i(vect_i* rec, const mat_i A, unsigned int i); // Récupère dans rec la ligne 0 <= i <= N-1 si A (entiers) est de taille N x M

// Découper en blocs de 4
void split4_d(const mat_d M, mat_d* a, mat_d* b, mat_d* c, mat_d* d, unsigned int i, unsigned int j); // Découpe la matrice M de doubles en 4 blocs dans a,b,c,d où la découpe se fait à la ligne i et la colonne j
void split4_i(const mat_i M, mat_i* a, mat_i* b, mat_i* c, mat_i* d, unsigned int i, unsigned int j); // Découpe la matrice M d'entiers en 4 blocs dans a,b,c,d où la découpe se fait à la ligne i et la colonne j
void split4_equal_d(const mat_d M, mat_d* a, mat_d* b, mat_d* c, mat_d* d); // Découpe la matrice M de doubles en 4 blocs dans a,b,c,d de mêmes formats si la matrice est de format compatible
void split4_equal_i(const mat_i M, mat_i* a, mat_i* b, mat_i* c, mat_i* d); // Découpe la matrice M d'entiers en 4 blocs dans a,b,c,d de mêmes formats si la matrice est de format compatible

// Reconstruire une matrice rec à partir de 4 blocs
void fus4_d(mat_d* rec, const mat_d* A, const mat_d* B, const mat_d* C, const mat_d* D); // Version matrices de doubles
void fus4_i(mat_i* rec, const mat_i* A, const mat_i* B, const mat_i* C, const mat_i* D); // Version matrices d'entiers

// Trace
double tr_d(const mat_d A); // Trace de la matrice de doubles A
int    tr_i(const mat_i A); // Trace de la matrice d'entiers  A

// Conversion de matrices
void cast_to_md(const mat_i A, mat_d* rec); // Convertit une matrice d'entiers en matrice de flottants
void cast_to_mi(const mat_d A, mat_i* rec); // Convertit une matrice de flottants en matrice d'entiers

// Actions flottantes sur les matrices flottantes
void round_mat(mat_d* a); // Arrondit les coefficients de la matrice
void ceil_mat(mat_d* a);  // Arrondit par excès les coefficients de la matrice
void floor_mat(mat_d* a); // Arrondit par défaut les coefficients de la matrice

// Conversions
void vect_to_mat_d(const vect_d U, mat_d* rec); // Convertit le vecteur de doubles en matrice à 1 colonne dans rec
void vect_to_mat_i(const vect_i U, mat_i* rec); // Convertit le vecteur d'entiers en matrice à 1 colonne dans rec

void mat_to_vect_d(const mat_d A, vect_d* rec); // Convertit la matrice de doubles (si possible) en vecteur dans rec
void mat_to_vect_i(const mat_i A, vect_i* rec); // Convertit la matrice d'entiers (si possible) en vecteur dans rec

// Copie de matrices
void copy_d(mat_d* rec, const mat_d* A); // Copie A dans rec (version double)
void copy_i(mat_i* rec, const mat_i* A); // Copie A dans rec (version entier)

// Transposition de matrices
void transpose_d(mat_d* a);
void transpose_i(mat_i* a);

/* ***************************************************** */
/* *************** Opérations d'anneaux **************** */
/* ***************************************************** */

// Multiplication scalaire
void scal_mul_d(mat_d* a, double lambda); // Multiplie la matrice par le scalaire lambda
void scal_mul_i(mat_i* a, int lambda);    // Multiplie la matrice par le scalaire lambda

// Addition de matrices
void sum_d(mat_d* rec, const mat_d A, const mat_d B); // Ajoute deux matrices de doubles, rec = A + B
void sum_i(mat_i* rec, const mat_i A, const mat_i B); // Ajoute deux matrices d'entiers, rec = A + B

// Soustraction de matrices
void sub_d(mat_d* rec, const mat_d A, const mat_d B); // Ajoute deux matrices de doubles, rec = A - B
void sub_i(mat_i* rec, const mat_i A, const mat_i B); // Ajoute deux matrices d'entiers, rec = A - B

// Produits matriciels

/* **************** Méthode de Strassen **************** */
/* On implémente le produit matriciel de deux matrices   */
/* de tailles n par l'algorithme de Strassen car         */
/* l'algorithme de Coppersmith-Winograd est inutilisable */
/* dans les cas pratiques (cf Wikipedia).                */
/* Complexité   : O(n^2.807)                             */
/* Cas d'usage  : matrices grandes tailles + non creuses */
/* Cas prohibés : matrices petites tailles ou creuses    */
/* ***************************************************** */

void mul_strassen_d(mat_d* rec, mat_d* A, mat_d* B); // rec = A x B
void mul_strassen_i(mat_i* rec, mat_i* A, mat_i* B); // rec = A x B

/* ******************* Méthode naive ******************* */
/* On implémente le produit matriciel de deux matrices   */
/* de tailles n par l'algorithme naif lorsque strassen   */
/* est inutilisable.                                     */
/* Complexité   : O(n^3)                                 */
/* Cas d'usage  : matrices petites tailles ou creuses    */
/* Cas prohibés : matrices grandes tailles / non creuses */
/* ***************************************************** */

void mul_natural_d(mat_d* rec, mat_d* A, mat_d* B); // rec = A x B
void mul_natural_i(mat_i* rec, mat_i* A, mat_i* B); // rec = A x B

// Graphiques /Debug (console)
void affiche_d(const mat_d A);
void affiche_i(const mat_i A);