#ifndef VILLE
#include "ville.h"
#endif

#include <string.h>     // strcpy_s, strcat_s
#include <stdlib.h>     // _countof
#include <errno.h>      // return values
#include <time.h>
#include <math.h>


int saveCity2D(city2D* c)
{
    FILE* f = NULL;

    char* file_name = NULL;
    file_name = malloc((strlen(c->name) + _countof(CITY_FILE_EXT)) * sizeof(char));

    if (file_name == NULL)
        return NAME_ALLOC_ERROR;
    else
    {
        strcpy(file_name, c->name);
        strncat(file_name, CITY_FILE_EXT, strlen(CITY_FILE_EXT));

        f = fopen(file_name, "w");

        if (f == NULL) // Si erreur pointeur
            return FILE_OPEN_ERROR;

        int x, y, z;

        // Ecriture du nom
        fprintf(f, "NOM=%s\n\n", c->name);

        // Ecriture des dimensions
        fprintf(f, "G=2D\n");
        fprintf(f, "SX%d;SY%d\n\n", c->size_x, c->size_y);

        // Ecriture de la map
        if (c->map != NULL)
            for (x = 0; x < c->size_x; x++)
                for (y = 0; y < c->size_y; y++)
                {
                    if ((c->map)[x][y].material != 0) // On n'écrit pas les blocs vide (gain de complexité spatiale et temporelle)
                        fprintf(f, "X%dY%d:M%d\n", x, y, (c->map[x][y]).material);
                }
        fprintf(f, "\n");

        // Ecriture des arrondissements
        fprintf(f, "NS%d\n", c->number_subdivisions);
        for (z = 0; z < c->number_subdivisions; z++)
        {
            fprintf(f, "S%d:N%s\n", (c->subdivisions[z]).name);
            for (x = 0; x < (c->subdivisions[z]).number_marking; z++)
                fprintf(f, "S%d;M%d:X%d;Y%d\n", z, x, (c->subdivisions[z]).marking[x][0], (c->subdivisions[z]).marking[x][1]);
        }
        fprintf(f, "\n");

        // Ecriture des emitters
        fprintf(f, "NE%d\n", c->number_emitters);
        for (x = 0; x < c->number_emitters; x++)
            fprintf(f, "E%d:F%.2lf;PO%.2lf;L%.2lf;PU%.2lf;X%.2lf;Y%.2lf\n", x, c->emitters[x].frequency, c->emitters[x].power, c->emitters[x].lambda, c->emitters[x].pulsation, c->emitters[x].position[0], c->emitters[x].position[1]);
        fprintf(f, "\n");

        // Ecriture des receivers
        fprintf(f, "NR%d\n", c->number_receivers);
        for (x = 0; x < c->number_receivers; x++)
            fprintf(f, "R%d:F%.2lf;PO%.2lf;L%.2lf;PU%.2lf;X%.2lf;Y%.2lf\n", x, c->receivers[x].frequency, c->receivers[x].lambda, c->receivers[x].pulsation, c->receivers[x].position[0], c->receivers[x].position[1]);
        fprintf(f, "\n");

        fclose(f);
        free(file_name);

        return 0;
    }
}

int randomCity2D(city2D* c)
{
    const char random_name[] = "Random City";
    int name_length = _countof(random_name); // _countof prend aussi le caractère null en compte contrairement à strlen

    c->name = calloc(name_length, sizeof(char));

    if (c->name == NULL)
        return NAME_ALLOC_ERROR; // Erreur d'allocation du nom
    else
    {
        strcpy_s(c->name, name_length, random_name); // Ecriture du nom

        c->map = calloc(c->size_x, sizeof(block*));

        // Allocation de la map
        if (c->map == NULL)
            return MAP_ALLOC_ERROR;
        else
        {
            int x, y;

            for (x = 0; x < c->size_x; x++)
            {
                (c->map)[x] = NULL;
                (c->map)[x] = calloc(c->size_y, sizeof(block));

                if ((c->map)[x] == NULL)
                    return MAP_ALLOC_ERROR;
            }

            srand(time(NULL));

            for (x = 0; x < c->size_x; x++)
                for (y = 0; y < c->size_y; y++)
                    (c->map)[x][y].material = rand() % 6; // % 6 pour avoir des nombres aléatoires de 0 à 5 inclus


        }

        return 0;
    }
}

int destroyCity2D(city2D* c)
{
    if (c->name != NULL)
        free(c->name);
    if (c->map != NULL)
        free(c->map);
    if (c->subdivisions != NULL)
        free(c->subdivisions);
    if (c->emitters != NULL)
        free(c->emitters);
    if (c->receivers != NULL)
        free(c->receivers);

    return 0;
}

int addEmitter2D(city2D* c, emitter2D e)
{
    c->number_emitters++;

    c->emitters = (emitter2D*)realloc(c->emitters, c->number_emitters * sizeof(emitter2D)); // Augmente la taille du tableau d'émetteurs sans le modifier

    if (c->emitters == NULL) // Si erreur d'allocation
    {
        c->number_emitters--; // On retire l'indication de l'ajout d'un émetteur
        return ANT_ALLOC_ERROR;
    }
    else
    {
        int id = c->number_emitters - 1;

        c->emitters[id].frequency = e.frequency;
        c->emitters[id].power = e.power;
        c->emitters[id].lambda = e.lambda;
        c->emitters[id].pulsation = e.pulsation;
        c->emitters[id].position[0] = e.position[0];
        c->emitters[id].position[1] = e.position[1];
    }

    return 0;
}

int initCity2D(city2D* c, int size_x, int size_y)
{
    c->name = NULL;
    c->size_x = size_x;
    c->size_y = size_y;
    c->emitters = NULL;
    c->receivers = NULL;
    c->emitters = (emitter2D*)malloc(0 * sizeof(emitter2D));
    c->receivers = (receiver2D*)malloc(0 * sizeof(receiver2D));
    c->map = NULL;
    c->subdivisions = NULL;
    c->number_subdivisions = 0;
    c->number_emitters = 0;
    c->number_receivers = 0;

    if (c->emitters == NULL || c->receivers == NULL)
        return ANT_ALLOC_ERROR;

    return 0;
}

int saveCity3D(city3D* c)
{
    FILE* f = NULL;

    char* file_name = NULL;
    file_name = malloc((strlen(c->name) + _countof(CITY_FILE_EXT)) * sizeof(char));

    if (file_name == NULL)
        return NAME_ALLOC_ERROR;
    else
    {
        strcpy(file_name, c->name);
        strncat(file_name, CITY_FILE_EXT, strlen(CITY_FILE_EXT));

        f = fopen(file_name, "w");

        if (f == NULL) // Si erreur pointeur
            return FILE_OPEN_ERROR;

        int x, y, z;

        // Ecriture du nom
        fprintf(f, "NOM=%s\n\n", c->name);

        // Ecriture des dimensions
        fprintf(f, "G=3D\n");
        fprintf(f, "SX%d;SY%d;SZ%d\n\n", c->size_x, c->size_y, c->size_z);

        // Ecriture de la map
        if(c->map != NULL)
            for (x = 0; x < c->size_x; x++)
                for (y = 0; y < c->size_y; y++)
                    for (z = 0; z < c->size_z; z++)
                    {
                        if((c->map)[x][y][z].material != 0) // On n'écrit pas les blocs vide (gain de complexité spatiale et temporelle)
                            fprintf(f, "X%dY%dZ%d:M%d\n", x, y, z, (c->map[x][y][z]).material);
                    }
        fprintf(f, "\n");

        // Ecriture des arrondissements
        fprintf(f, "NS%d\n", c->number_subdivisions);
        for (z = 0; z < c->number_subdivisions; z++) 
        {
            fprintf(f, "S%d:N%s\n", (c->subdivisions[z]).name);
            for (x = 0; x < (c->subdivisions[z]).number_marking; z++)
                fprintf(f, "S%d;M%d:X%d;Y%d\n", z, x, (c->subdivisions[z]).marking[x][0], (c->subdivisions[z]).marking[x][1]);
        }
        fprintf(f, "\n");

        // Ecriture des emitters
        fprintf(f, "NE%d\n", c->number_emitters);
        for (x = 0; x < c->number_emitters; x++)
            fprintf(f, "E%d:F%.2lf;PO%.2lf;L%.2lf;PU%.2lf;X%.2lf;Y%.2lf;Z%.2lf\n", x, c->emitters[x].frequency, c->emitters[x].power, c->emitters[x].lambda, c->emitters[x].pulsation, c->emitters[x].position[0], c->emitters[x].position[1], c->emitters[x].position[2]);
        fprintf(f, "\n");

        // Ecriture des receivers
        fprintf(f, "NR%d\n", c->number_receivers);
        for (x = 0; x < c->number_receivers; x++)
            fprintf(f, "R%d:F%.2lf;PO%.2lf;L%.2lf;PU%.2lf;X%.2lf;Y%.2lf\n", x, c->receivers[x].frequency, c->receivers[x].lambda, c->receivers[x].pulsation, c->receivers[x].position[0], c->receivers[x].position[1], c->receivers[x].position[2]);
        fprintf(f, "\n");

        fclose(f);
        free(file_name);

        return 0;
    }
}

int initCity3D(city3D* c, int size_x, int size_y, int size_z)
{
    c->name = NULL;
    c->size_x = size_x;
    c->size_y = size_y;
    c->size_z = size_z;
    c->emitters = NULL;
    c->receivers = NULL;
    c->emitters = (emitter3D*)malloc(0 * sizeof(emitter3D));
    c->receivers = (receiver3D*)malloc(0 * sizeof(receiver3D));
    c->map = NULL;
    c->subdivisions = NULL;
    c->number_subdivisions = 0;
    c->number_emitters = 0;
    c->number_receivers = 0;

    if (c->emitters == NULL || c->receivers == NULL)
        return ANT_ALLOC_ERROR;

    return 0;
}

int randomCity3D(city3D* c)
{
    const char random_name[] = "Random City";
    int name_length = _countof(random_name); // _countof prend aussi le caractère null en compte contrairement à strlen

    c->name = calloc(name_length, sizeof(char));

    if (c->name == NULL)
        return NAME_ALLOC_ERROR; // Erreur d'allocation du nom
    else
    {
        strcpy_s(c->name, name_length, random_name); // Ecriture du nom
        
        c->map = calloc(c->size_x, sizeof(block**));

        // Allocation de la map
        if (c->map == NULL)
            return MAP_ALLOC_ERROR;
        else
        {
            int x, y, z;

            for (x = 0; x < c->size_x; x++)
            {
                (c->map)[x] = NULL;
                (c->map)[x] = calloc(c->size_y, sizeof(block*));

                if((c->map)[x] == NULL)
                    return MAP_ALLOC_ERROR;
                else
                {
                    for (y = 0; y < c->size_y; y++)
                    {
                        (c->map)[x][y] = NULL;
                        (c->map)[x][y] = calloc(c->size_z, sizeof(block));

                        if ((c->map)[x][y] == NULL)
                            return MAP_ALLOC_ERROR;
                    }
                }        
            }

            srand(time(NULL));

            for (x = 0; x < c->size_x; x++)
                for (y = 0; y < c->size_y; y++)
                    for (z = 0; z < c->size_z; z++)
                        (c->map)[x][y][z].material = rand() % 6; // % 6 pour avoir des nombres aléatoires de 0 à 5 inclus


        }

        return 0;
    }
}

int destroyCity3D(city3D* c)
{
    if(c->name != NULL)
        free(c->name);
    if (c->map != NULL)
        free(c->map);
    if (c->subdivisions != NULL)
        free(c->subdivisions);
    if (c->emitters != NULL)
        free(c->emitters);
    if (c->receivers != NULL)
        free(c->receivers);
    
    return 0;
}

int addEmitter3D(city3D* c, emitter3D e)
{
    c->number_emitters++;

    c->emitters = (emitter3D*) realloc(c->emitters, c->number_emitters * sizeof(emitter3D)); // Augmente la taille du tableau d'émetteurs sans le modifier

    if (c->emitters == NULL) // Si erreur d'allocation
    {
        c->number_emitters--; // On retire l'indication de l'ajout d'un émetteur
        return ANT_ALLOC_ERROR;
    }
    else
    {
        int id = c->number_emitters - 1;

        c->emitters[id].frequency = e.frequency;
        c->emitters[id].power     = e.power;
        c->emitters[id].lambda    = e.lambda;
        c->emitters[id].pulsation = e.pulsation;
        c->emitters[id].position[0]  = e.position[0];
        c->emitters[id].position[1] = e.position[1];
        c->emitters[id].position[2] = e.position[2];
    }

    return 0;
}