#pragma once

#ifndef CITY
#define CITY 
#endif

#ifndef MATERIAL
#include "materiaux.h"
#endif


/* ************** */
/* *** Villes *** */
/* ************** */


/* ##################################################### */
/* ##################################################### */
/* ####################### DEFINES ##################### */
/* ##################################################### */
/* ##################################################### */

#define MAX_CITY_WIDTH 500               // Largeur maximale d'une ville carr�
#define MAX_HEIGHT     300               // Hauteur maximale en blocs d'une ville
#define MIN_DEPTH      50                // Profndeur maximale en blocs du r�seau souterrain d'une ville
// Couleurs
// Primaires
#define RED   [255,0,0]
#define GREEN [0,255,0]
#define BLUE  [0,0,255]
#define WHITE [255,255,255]
#define BLACK [0,0,0]
// Particuli�res
#define COLOR_EMITTER BLUE               // Couleur d'un �metteur
#define COLOR_RECEIVER RED               // Couleur d'une source
#define MIN_COLOR_BUILDING BLACK       // Couleur du plus haut bloc b�timent
#define MAX_COLOR_BUILDING WHITE // Couleur du plus bas bloc b�timent
#define MIN_COLOR_FOREST   [0,100,0]
#define MAX_COLOR_FOREST   GREEN
#define MIN_COLOR_WATER    [0,0,100]
#define MAX_COLOR_WATER    BLUE
// Codes d'erreur
#define CITY_ALLOC_ERROR 2 // Erreur d'allocation m�moire des blocs de la ville

/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */


typedef struct unit unit;
typedef struct city city; 

struct unit
{
	unsigned int material; // Num�ro d'identification du mat�riau
};

struct city
{
	const unsigned int height, length, width;
	unit** map;                               // Carte de la ville
	emitter* emitters;                          // Antennes
	receiver* receivers;
};

int saveCity(city* c, FILE* f);               // Sauvegarde les donn�es de la ville dans un fichier f
int loadCity(city* c, FILE* f);               // R�cup�re les donn�es d'une ville issue d'un fichier f
int initCity(city* c, int h, int l, int w);   // Cr�e la ville nulle
int randomCity(city* c, int h, int l, int w); // Cr�e une ville al�atoire
int replace_block 