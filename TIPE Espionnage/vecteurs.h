#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ************** */
/* ** Vecteurs ** */
/* ************** */

/* ##################################################### */
/* ##################################################### */
/* ####################### DEFINES ##################### */
/* ##################################################### */
/* ##################################################### */

#ifndef EMPTY
#define EMPTY 0 // Taille du vecteur vide
#endif

/* ##################################################### */
/* ##################################################### */
/* ####################### Types ####################### */
/* ##################################################### */
/* ##################################################### */

typedef double* vector_double; // Vecteur de doubles utilisé pour représenter ligne ou colonne de matrices de doubles
typedef int* vector_int;    // Vecteur d'entiers utilisé pour représenter ligne ou colonne de matrices d'entiers

/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */

struct vect_d // Vecteur de doubles avec sa taille
{
    vector_double data;      // Données de la matrice (doubles)
    unsigned int *length; // Nombre de lignes resp. de colonnes
};

struct vect_i // Vecteur d'entiers avec sa taille
{
    vector_int data;      // Données de la matrice (entiers)
    unsigned int *length; // Nombre de lignes resp. de colonnes
};

typedef struct vect_d vect_d;
typedef struct vect_i vect_i;

/* ##################################################### */
/* ##################################################### */
/* ###################### En-têtes ##################### */
/* ##################################################### */
/* ##################################################### */

// Initialisation
void init_vect_d(vect_d* v);
void init_vect_i(vect_i* v);

// Créer un vecteur nul
void vect_nul_d(vect_d* u, unsigned int n); // n -> taille du vecteur nul souhaitée
void vect_nul_i(vect_i* u, unsigned int n); // n -> taille du vecteur nul souhaitée

// Créer un vecteur à partir d'une liste
void creer_vect_d(vect_d* u, vector_double v, unsigned int len); // len est la taille de v
void creer_vect_i(vect_i* u, vector_int v, unsigned int len);    // len est la taille de v

// Désallocation
void destroy_vect_d(vect_d* u);
void destroy_vect_i(vect_i* u);