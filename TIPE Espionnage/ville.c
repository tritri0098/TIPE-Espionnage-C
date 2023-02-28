#ifndef VILLE
#include "ville.h"
#endif

int saveCity2D(city2D* c) 
{
    FILE* f;

    f = fopen(strcat(c->name, ".txt"), "w");
    
    if (f == NULL) // Si erreur pointeur
        return 1;

    int x, y, z;

    fprintf(f, "SX=%d;SY=%d\n", c->size_x, c->size_y);

    // Ecriture de la map
    for (x = 0; x < c->size_x; x++)
        for (y = 0; y < c->size_y; y++)
            fprintf(f, "X%dY%d:M=%d\n", x, y, c->map[x][y].material);
    fprintf(f, "\n");

    // Ecriture des arrondissements
    fprintf(f, "NS=%d\n", c->number_subdivisions);
    for (z = 0; z < c->number_subdivisions; z++) {
        fprintf(f, "S%d:N=%s\n", (c->subdivisions[z]).name);
        for(x = 0; x < (c->subdivisions[z]).number_marking; z++)
            fprintf(f, "S%d;M%d:X=%d;Y=%d\n", z, x, (c->subdivisions[z]).marking[x][0], (c->subdivisions[z]).marking[x][1]);
    }

    // Ecriture des emitters
    fprintf(f, "NE=%d\n", c->number_emitters);
    for (x = 0; x < c->number_emitters; x++) {
        fprintf(f, "E%d:F=%lf;PO=%lf;L=%lf;PU=%lf;X=%lf;Y=%lf\n", x, (c->emitters[x]).frequency, c->emitters[x].power, c->emitters[x].lambda, c->emitters[x].pulsation, c->emitters[x].position[0], c->emitters[x].position[1]);
    }
    // Ecriture des receivers
    fprintf(f, "NE=%d\n", c->number_receivers);
    for (x = 0; x < c->number_receivers; x++) {
        fprintf(f, "E%d:F=%lf;PO=%lf;L=%lf;PU=%lf;X=%lf;Y=%lf\n", x, c->receivers[x].frequency, c->receivers[x].lambda, c->receivers[x].pulsation, c->receivers[x].position[0], c->receivers[x].position[1]);
    }

    fclose(f);

    return 0;
}

int saveCity3D(city3D* c)
{
    FILE* f = NULL;

    //printf("numb:%d\n", strlen(CITY_FILE_EXT));

    char* file_name = NULL;
    file_name = malloc((strlen(c->name) + strlen(CITY_FILE_EXT) - 1) * sizeof(char));

    if (file_name == NULL)
        return NAME_ALLOC_ERROR;
    else
    {
        strcpy(file_name, c->name);
        strncat(file_name, CITY_FILE_EXT, (strlen(CITY_FILE_EXT) - 2));

        f = fopen(c->name, "w");

        if (f == NULL) // Si erreur pointeur
            return 1;

        int x, y, z;

        // Ecriture du nom
        fprintf(f, "NOM=%s\n", c->name);

        // Ecriture des dimensions
        fprintf(f, "SX=%d;SY=%d;SZ=%d\n", c->size_x, c->size_y, c->size_z);

        // Ecriture de la map
        if(c->map != NULL)
            for (x = 0; x < c->size_x; x++)
                for (y = 0; y < c->size_y; y++)
                    for (z = 0; z < c->size_z; z++)
                        fprintf(f, "X%dY%dZ%d:M=%d\n", x, y, z, (c->map[x][y][z]).material);
        fprintf(f, "\n");

        // Ecriture des arrondissements
        fprintf(f, "NS=%d\n", c->number_subdivisions);
        for (z = 0; z < c->number_subdivisions; z++) 
        {
            fprintf(f, "S%d:N=%s\n", (c->subdivisions[z]).name);
            for (x = 0; x < (c->subdivisions[z]).number_marking; z++)
                fprintf(f, "S%d;M%d:X=%d;Y=%d\n", z, x, (c->subdivisions[z]).marking[x][0], (c->subdivisions[z]).marking[x][1]);
        }

        // Ecriture des emitters
        fprintf(f, "NE=%d\n", c->number_emitters);
        for (x = 0; x < c->number_emitters; x++)
            fprintf(f, "E%d:F=%lf;PO=%lf;L=%lf;PU=%lf;X=%lf;Y=%lf;Z=%lf\n", x, c->emitters[x].frequency, c->emitters[x].power, c->emitters[x].lambda, c->emitters[x].pulsation, c->emitters[x].position[0], c->emitters[x].position[1], c->emitters[x].position[2]);
        
        // Ecriture des receivers
        fprintf(f, "NE=%d\n", c->number_receivers);
        for (x = 0; x < c->number_receivers; x++)
            fprintf(f, "E%d:F=%lf;PO=%lf;L=%lf;PU=%lf;X=%lf;Y=%lf\n", x, c->receivers[x].frequency, c->receivers[x].lambda, c->receivers[x].pulsation, c->receivers[x].position[0], c->receivers[x].position[1], c->receivers[x].position[2]);

        fclose(f);
        free(file_name);

        return 0;
    }
}

void initCity3D(city3D* c, int size_x, int size_y, int size_z)
{
    c->name = NULL;
    c->size_x = size_x;
    c->size_y = size_y;
    c->size_z = size_z;
    c->emitters = NULL;
    c->receivers = NULL;
    c->map = NULL;
    c->subdivisions = NULL;
    c->number_subdivisions = 0;
    c->number_emitters = 0;
    c->number_receivers = 0;
}

int randomCity3D(city3D* c)
{
    char random_name[] = "RandomCity";
    int name_length = strlen(random_name);

    c->name = calloc(name_length, sizeof(char));

    if (c->name == NULL)
        return NAME_ALLOC_ERROR; // Erreur d'allocation du nom
    else
    {
        strncpy(c->name, random_name, name_length);

        printf("name length = %d\n", strlen(c->name));

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