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

#define MAX_TAILLE_VILLE 2000 // en unit�s de r�f�rence

#define L_UNIT 100 // Nombre de m�tres (m) par unit� 

/* *** Types d'antennes *** */
#define RECEPTEUR 0 // Convention pour une antenne �mettrice
#define EMETTEUR  1 // Convention pour une antenne r�ceptrice

/* *** Types d'antennes *** */
#define ISOTROPE  0 
#define DIPOLAIRE 1

/* *** Type de m�t�o *** */
#define CLAIR    0
#define PLUVIEUX 1
#define BRUMEUX  2
#define GRIS     3

/* *** Fr�quences *** */
#define WIFI1      0
#define WIFI2      1
#define RADIO_FM   2
#define RADIO_AM   3
#define RADIO_PART 4
#define GSM        5
#define BLUETOOTH  6
#define TALKIE     7

const float REFLEXION[1][1] = { {0} }; // Coefficients de r�flexion par fr�quences ([Mat�riau][fr�quence] : position du coefficient) 
                                       // B�ton : 0
                                       // Verre : 1
                                       // Bois  : 2
                                       // Herbe : 3
                                       // Eau   : 4 
                                       // 
const float REFLEXION_ATM[1][1] = { {0} }; // Coefficients de r�flexion d�e � l'atmosph�re par fr�quences ([Mat�riau][fr�quence] : position du coefficient)

/* ****************** */
/* *** STRUCTURES *** */
/* ****************** */

typedef struct ville ville;
typedef struct coords coords; // Coordonn�es d'une antenne �metrice (source) source ou d'une antenne r�ceptrice (cible)
typedef struct antenne antenne; // Source d'une

struct coords
{
    unsigned int x, y; // position en unit�s de r�f�rence
    float z;   // hauteur flottante
};

struct antenne
{
    coords pos;              // Coordonn�es absolues de l'antenne en unit�s
    unsigned char role;      // R�le de l'antenne : RECEPTEUR / EMETTEUR
    unsigned char type;      // Type de l'antenne : ISOTROPE / DIPOLAIRE
    float freq;     // Fr�quence d'�mission r�ception de l'antenne en Hz
    float gain;     // Gain de l'antenne en dB
    float impedance; // Imp�dance de l'antenne en Ohm
};

struct ville
{
    const unsigned char meteo;
    mat_d* hauteur;
    mat_i* coeff_reflexion; // matrices d'entiers car les �l�ments 
                            // sont les indices des coefficients de 
                            // r�flexion correspondant dans la table 
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