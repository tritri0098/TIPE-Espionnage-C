#ifndef ANTENNES 
#define ANTENNES

/* *************** */
/* *** Sources *** */
/* *************** */

/* ##################################################### */
/* ##################################################### */
/* ####################### DEFINES ##################### */
/* ##################################################### */
/* ##################################################### */

// Constantes utiles

#define PI      3.14159265
#define DEUXPI     6.28318531
#define	EPS0    8.85418782e-12
#define U0      1.25663706e-6
#define LIGHT_C 299792458 // (en m/s)

// Flags

#define EMETTEUR  0 
#define RECEPTEUR 1 

/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */

typedef struct emitter2D emitter2D;
typedef struct emitter3D emitter3D;
typedef struct receiver2D receiver2D;
typedef struct receiver3D receiver3D;

struct emitter2D
{
	float frequency;
	float power;
	float lambda;
	float pulsation;
	float position[2]; // la position est exprimée en cordonnées flottantes cartésiennes [0] = x, [1] = y
};

struct emitter3D
{
	float frequency;
	float power;
	float lambda;
	float pulsation;
	float position[3]; // la position est exprimée en cordonnées flottantes cartésiennes [0] = x, [1] = y, [2] = z
};

struct receiver2D
{
	float frequency;
	float lambda;
	float pulsation;
	float position[2]; // la position est exprimée en cordonnées flottantes cartésiennes [0] = x, [1] = y
};

struct receiver3D
{
	float frequency;
	float lambda;
	float pulsation;
	float position[3]; // la position est exprimée en cordonnées flottantes cartésiennes [0] = x, [1] = y, [2] = z
};

/* ##################################################### */
/* ##################################################### */
/* ###################### En-têtes ##################### */
/* ##################################################### */
/* ##################################################### */

emitter2D  newEmitter2D  (float f, float pow, float x, float y);
receiver2D newReceiver2D (float f, float x, float y, float z);

emitter3D  newEmitter3D  (float f, float pow, float x, float y, float z);
receiver3D newReceiver3D (float f, float x, float y, float z);

#endif