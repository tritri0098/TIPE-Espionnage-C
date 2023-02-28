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

#define PI   3.14159265
#define	EPS0 8.85418782e-12
#define U0   1.25663706e-6

// Flags

#define EMETTEUR  0 
#define RECEPTEUR 1 

/* ##################################################### */
/* ##################################################### */
/* #################### Structures ##################### */
/* ##################################################### */
/* ##################################################### */

typedef struct emitter emitter;
typedef struct receiver receiver;

struct emitter
{
	double frequency;
	double power;
	double lambda;
	double pulsation;
	double position[3]; // la position est exprim�e en cordonn�es flottantes cart�siennes [0] = x, [1] = y, [2] = z
};

struct receiver
{
	double frequency;
	double lambda;
	double pulsation;
	double position[3]; // la position est exprim�e en cordonn�es flottantes cart�siennes [0] = x, [1] = y, [2] = z
};

#endif