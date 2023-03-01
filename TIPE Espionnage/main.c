#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"
#include "ville.h"
#include "ville.c"
#include "antennes.h"
#include "antennes.c"

/* ****************** */
/* *** CONSTANTES *** */
/* ****************** */

#define MAX_TAILLE_VILLE 2000 // en unités de référence

#define L_UNIT 100 // Nombre de mètres (m) par unité 

/* *** Types d'antennes *** */
#define RECEPTEUR 0 // Convention pour une antenne émettrice
#define EMETTEUR  1 // Convention pour une antenne réceptrice

/* *** Types d'antennes *** */
#define ISOTROPE  0 
#define DIPOLAIRE 1

/* *** Type de météo *** */
#define CLAIR    0
#define PLUVIEUX 1
#define BRUMEUX  2
#define GRIS     3

/* *** Fréquences *** */
#define WIFI1      0
#define WIFI2      1
#define RADIO_FM   2
#define RADIO_AM   3
#define RADIO_PART 4
#define GSM        5
#define BLUETOOTH  6
#define TALKIE     7

const float REFLEXION[1][1] = { {0} }; // Coefficients de réflexion par fréquences ([Matériau][fréquence] : position du coefficient) 
                                       // Béton : 0
                                       // Verre : 1
                                       // Bois  : 2
                                       // Herbe : 3
                                       // Eau   : 4 
                                       // 
const float REFLEXION_ATM[1][1] = { {0} }; // Coefficients de réflexion dûe à l'atmosphère par fréquences ([Matériau][fréquence] : position du coefficient)

/* ****************** */
/* *** STRUCTURES *** */
/* ****************** */

typedef struct ville ville;
typedef struct coords coords; // Coordonnées d'une antenne émetrice (source) source ou d'une antenne réceptrice (cible)
typedef struct antenne antenne; // Source d'une

struct coords
{
    unsigned int x, y; // position en unités de référence
    float z;   // hauteur flottante
};

struct antenne
{
    coords pos;              // Coordonnées absolues de l'antenne en unités
    unsigned char role;      // Rôle de l'antenne : RECEPTEUR / EMETTEUR
    unsigned char type;      // Type de l'antenne : ISOTROPE / DIPOLAIRE
    float freq;     // Fréquence d'émission réception de l'antenne en Hz
    float gain;     // Gain de l'antenne en dB
    float impedance; // Impédance de l'antenne en Ohm
};

struct ville
{
    const unsigned char meteo;
    mat_d* hauteur;
    mat_i* coeff_reflexion; // matrices d'entiers car les éléments 
                            // sont les indices des coefficients de 
                            // réflexion correspondant dans la table 
                            // de correspondance REFLEXION
    antenne* antennes;
};

/* ****************** */
/* *** PROTOTYPES *** */
/* ****************** */



int main()
{
    city3D c;
    emitter3D e1 = newEmitter3D(433.0e6, 3.0, 327.5, 682.7, 584.2);
    emitter3D e2 = newEmitter3D(557.0, 3.0, 367.5, 982.7, 184.2);

    initCity3D(&c, 100, 100, 3000);
    randomCity3D(&c);
    addEmitter3D(&c, e1);
    addEmitter3D(&c, e2);

    saveCity3D(&c);

    destroyCity3D(&c);

    printf("Ok");

    return EXIT_SUCCESS;
}