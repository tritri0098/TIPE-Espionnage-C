#ifndef VILLE
#define VILLE

#ifndef MATERIAL
#include "materiaux.h"
#endif

#ifndef ANTENNES
#include "antennes.h"
#endif


/* ************** */
/* *** Villes *** */
/* ************** */


/* ##################################################### */
/* ##################################################### */
/* ####################### DEFINES ##################### */
/* ##################################################### */
/* ##################################################### */

// Noms
#define MAX_NAME_LENGTH 50 // Taille maximale pour un nom de ville ou de quartiers
// Mesures
#define MAX_CITY_WIDTH 500               // Largeur maximale d'une ville carré
#define MAX_HEIGHT     300               // Hauteur maximale en blocs d'une ville
#define MAX_DEPTH      50                // Profondeur maximale en blocs du réseau souterrain d'une ville
// Couleurs
// Primaires
#define RED   [255,0,0]
#define GREEN [0,255,0]
#define BLUE  [0,0,255]
#define WHITE [255,255,255]
#define BLACK [0,0,0]
#define GREY  [80,80,80];
// Particulières
#define COLOR_EMITTER BLUE               // Couleur d'un émetteur
#define COLOR_RECEIVER RED               // Couleur d'une source
#define MIN_COLOR_BUILDING GREY       // Couleur du bloc bâtiment à l'altitude théorique max de la map 
#define MAX_COLOR_BUILDING WHITE      // Couleur du bloc bâtiment au niveau du sol
#define MIN_COLOR_FOREST   [0,100,0]
#define MAX_COLOR_FOREST   GREEN
#define MIN_COLOR_WATER    [0,0,100]
#define MAX_COLOR_WATER    BLUE
#define MIN_COLOR_ROAD     [50, 50, 50]
#define MAX_COLOR_ROAD     BLACK
#define MIN_COLOR_SOIL     [86, 64, 54] // marron clair
#define MAX_COLOR_SOIL     [46, 24, 14] // marron foncé
// Extensions de fichier
#define CITY_FILE_EXT ".city"
// Codes d'erreur
#define NAME_ALLOC_ERROR 1 // Erreur d'allocation mémoire des blocs de la ville
#define MAP_ALLOC_ERROR  2 // Erreur d'allocation mémoire des blocs de la ville
#define ANT_ALLOC_ERROR  3 // Erreur d'allocation d'une antenne
#define FILE_OPEN_ERROR  4 // Erreur d'ouverture de fichier


/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */

typedef struct block block;
typedef struct city2D city2D;           // Modèle de ville en 2D
typedef struct subdivision subdivision; // Zone délimitant un arrondissement en 2D (hauteur infinie)
typedef struct city3D city3D;           // Modèle de ville en 3D

struct block
{
	unsigned int material; // Numéro d'identification du matériau
};

struct subdivision
{
	char* name; // Nom de l'arrondissement / quartier
	int*** marking;                      // colonnes unitaires de coordonées (x,y) délimitant la frontière d'un arrondissment
	unsigned int number_marking;         // Nombre de colonnes unitaires 
};

struct city2D
{
	char* name;                       // Nom de la ville
	unsigned int size_x, size_y;      // Dimensions de la ville
	block** map;                      // Carte de la ville
	subdivision* subdivisions;        // Arrondissements / quartiers de la ville ([i][x][y])
	emitter2D* emitters;                // Antennes d'émissions  (cibles)
	receiver2D* receivers;              // Antennes de réception (intercepteurs)
	unsigned int number_subdivisions; // Nombre d'arrondissements
	unsigned int number_emitters;     // Nombre d'émetteurs
	unsigned int number_receivers;    // Nombre de récepteurs
};

struct city3D
{
	char* name;                          // Nom de la ville
	unsigned int size_x, size_y, size_z; // Dimensions de la ville
	block***      map;                   // Carte de la ville [x][y][z]
	subdivision* subdivisions;           // Arrondissements / quartiers de la ville ([i][x][y])
	emitter3D* emitters;                   // Antennes d'émissions  (cibles)
	receiver3D* receivers;                 // Antennes de réception (intercepteurs)
	unsigned int number_subdivisions;    // Nombre d'arrondissements
	unsigned int number_emitters;        // Nombre d'émetteurs
	unsigned int number_receivers;       // Nombre de récepteurs
};

/* ##################################################### */
/* ##################################################### */
/* ###################### En-têtes ##################### */
/* ##################################################### */
/* ##################################################### */

int saveCity2D(city2D* c);               // Sauvegarde les données de la ville dans un fichier f
int loadCity2D(city2D* c, FILE* f);               // Récupère les données d'une ville issue d'un fichier f
int initCity2D(city2D* c, int size_x, int size_y);   // Crée la ville nulle
int randomCity2D(city2D* c, int size_x, int size_y); // Crée une ville aléatoire
int replace_block2D(city2D* c, int x, int y, block block);   // Modifie le bloc de coordonnées (x,y) par un nouveau
int destroyCity2D(city2D* c);                              // Désalloue la ville
int addEmitter2D(city2D* c, emitter2D e);                    // Ajoute un émetteur à la ville

int saveCity3D(city3D* c);               // Sauvegarde les données de la ville dans un fichier f
int loadCity3D(city3D* c, FILE* f);               // Récupère les données d'une ville issue d'un fichier f
int initCity3D(city3D* c, int size_x, int size_y, int size_z);   // Crée la ville nulle
int randomCity3D(city3D* c); // Crée une ville aléatoire
int replace_block3D(city3D* c, int x, int y, int z, block block);   // Modifie le bloc de coordonnées (x,y,z) par un nouveau
int destroyCity3D(city3D* c);                              // Désalloue la ville
int addEmitter3D(city3D* c, emitter3D e);                    // Ajoute un émetteur à la ville

#endif