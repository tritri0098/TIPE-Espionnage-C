#include "vecteurs.h"

/* ##################################################### */
/* ##################################################### */
/* #################### Définitions #################### */
/* ##################################################### */
/* ##################################################### */

// Initialisation
void init_vect_d(vect_d* v)
{
	v->data = NULL;
	v->length = NULL;
}

void init_vect_i(vect_i* v)
{
	v->data = NULL;
	v->length = NULL;
}

// Créer un vecteur nul
void vect_nul_d(vect_d* u, unsigned int n)
{
	u->length = malloc(sizeof(unsigned int));
	*(u->length) = (u->length != NULL) ? n : EMPTY;

	if (u->data != NULL)
		realloc(u->data, n * sizeof(double));
	else
		u->data = malloc(n * sizeof(double));

	if (u->data != NULL)
	{
		int i;

		for (i = 0; i < n; i++)
			u->data[i] = 0.;
	}
}

void vect_nul_i(vect_i* u, unsigned int n)
{
	u->length = malloc(sizeof(unsigned int));
	*(u->length) = (u->length != NULL) ? n : EMPTY;

	if (u->data != NULL)
		realloc(u->data, n * sizeof(int));
	else
		u->data = malloc(n * sizeof(int));

	if (u->data != NULL)
	{
		int i;

		for (i = 0; i < n; i++)
			u->data[i] = 0;
	}
}

// Créer un vecteur à partir d'une liste
void creer_vect_d(vect_d* u, vector_double v, unsigned int len)
{
	if (u->data != NULL)
		u->data = (vector_double) realloc(u->data, len * sizeof(double));
	else
		u->data = (vector_double) malloc(len * sizeof(double));

	if (u->data != NULL)
	{
		u->length = malloc(sizeof(unsigned int));
		*(u->length) = (u->length != NULL) ? len : EMPTY;

		int i;
		for (i = 0; i < len; i++)
			u->data[i] = v[i];
	}
}

void creer_vect_i(vect_i* u, vector_int v, unsigned int len)
{
	if (u->data != NULL)
		u->data = (vector_int) realloc(u->data, len * sizeof(int));
	else
		u->data = (vector_int) malloc(len * sizeof(int));

	if (u->data != NULL)
	{
		u->length = malloc(sizeof(unsigned int));
		*(u->length) = (u->length != NULL) ? len : EMPTY;

		int i;
		for (i = 0; i < len; i++)
			u->data[i] = v[i];
	}
}

// Désallocation
void destroy_vect_d(vect_d* u)
{
	free(u->data);
	free(u->length);
}

void destroy_vect_i(vect_i* u)
{
	free(u->data);
	free(u->length);
}