#include "matrices.h"

/* ##################################################### */
/* ##################################################### */
/* #################### Définitions #################### */
/* ##################################################### */
/* ##################################################### */

// Initialisation
void init_mat_d(mat_d* a)
{
    a->data = NULL;
    a->rows = NULL;
    a->cols = NULL;
}

void init_mat_i(mat_i* a)
{
    a->data = NULL;
    a->rows = NULL;
    a->cols = NULL;
}

// Destruction (mémoire) d'une matrice
void destroy_mat_d(mat_d* a)
{
    unsigned int i;
    for(i = 0; i < *(a->rows); i++)
        free(a->data[i]); 
    free(a->data);
    free(a->rows);
    free(a->cols);
}

void destroy_mat_i(mat_i* a)
{
    unsigned int i;
    for (i = 0; i < *(a->rows); i++)
        free((a->data)[i]);
    free(a->data);
    free(a->rows);
    free(a->cols);
}

// Matrices nulles
void creer_nulle_d(mat_d* a, unsigned int n, unsigned int m) // modification en place
{
    init_mat_d(a);

    unsigned int i, j;

    a->rows = malloc(sizeof(double));
    a->cols = malloc(sizeof(double));

    *(a->rows) = n;
    *(a->cols) = m;

    // (Ré)allocation propre
    a->data = (vector_double*) realloc(a->data, n * sizeof(vector_double));
    memset(a->data, NULL, n * sizeof(vector_double));
    for (i = 0; i < n; i++)
        a->data[i] = (vector_double) realloc(a->data[i], m * sizeof(double));

    if (a->data != NULL)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                a->data[i][j] = 0.;
    }
}

void creer_nulle_i(mat_i* a, unsigned int n, unsigned int m)
{
    init_mat_i(a);

    unsigned int i, j;

    a->rows = malloc(sizeof(int));
    a->cols = malloc(sizeof(int));

    *(a->rows) = n;
    *(a->cols) = m;

    // (Ré)allocation propre
    a->data = (vector_int*)realloc(a->data, n * sizeof(vector_int));
    memset(a->data, NULL, n * sizeof(vector_int));
    for (i = 0; i < n; i++)
        a->data[i] = (vector_int)malloc(m * sizeof(int));

    if (a->data != NULL)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                a->data[i][j] = 0;
    }
}


// Matrices identité
void creer_identite_d(mat_d *a, unsigned int n)
{
    creer_nulle_d(a, n, n);

    if (a->data != NULL)
    {
        unsigned int i;
        for (i = 0; i < n; i++)
            a->data[i][i] = 1.;
    }
}

void creer_identite_i(mat_i* a, unsigned int n)
{
    creer_nulle_i(a, n, n);

    if (a->data != NULL)
    {
        unsigned int i;
        for (i = 0; i < n; i++)
            a->data[i][i] = 1;
    }
}

// Matrices diagonales
void diag_d(mat_d* a, vect_d v)
{
    creer_nulle_d(a, *(v.length), *(v.length));

    if (a->data != NULL)
    {
        unsigned int i;

        for (i = 0; i < *(v.length); i++)
            a->data[i][i] = v.data[i];
    }
}

void diag_i(mat_i* a, vect_i v)
{
    creer_nulle_i(a, *(v.length), *(v.length));

    if (a->data != NULL)
    {
        unsigned int i;

        for (i = 0; i < *(v.length); i++)
            a->data[i][i] = v.data[i];
    }
}

// Remplir matrice (modification en place)
void fill_d(mat_d* a, double v)
{
    const unsigned int R = *(a->rows), C = *(a->cols);

    if (a->data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = v;
    }
}

void fill_i(mat_i* a, int v)
{
    const unsigned int R = *(a->rows), C = *(a->cols);

    if (a->data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = v;
    }
}

// Augmenter une matrice
void add_rows_d(mat_d* a, unsigned int n, double val)
{
    unsigned int i, j;

    *(a->rows) += n;

    const unsigned int R = *(a->rows), C = *(a->cols);

    a->data = (vector_double*)realloc(a->data, R * sizeof(vector_double));
    for (i = 0; i < n; i++)
        a->data[C - 1 - i] = (vector_double)malloc(C * sizeof(double)); // On alloue les nouvelles lignes

    if (a->data != NULL)
        for (i = 0; i < n; i++)
            for (j = 0; j < C; j++)
                a->data[R - 1 - i][j] = val;


}

void add_rows_i(mat_i* a, unsigned int n, int val)
{
    unsigned int i, j;

    *(a->rows) += n;

    const unsigned int R = *(a->rows), C = *(a->cols);

    a->data = (vector_int*)realloc(a->data, R * sizeof(vector_int));
    for (i = 0; i < n; i++)
        a->data[R - 1 - i] = (vector_int)malloc(C * sizeof(int)); // On alloue les nouvelles lignes

    if (a->data != NULL)
        for (i = 0; i < n; i++)
            for (j = 0; j < C; j++)
                a->data[R - 1 - i][j] = val;
}

void add_cols_d(mat_d* a, unsigned int n, double val)
{
    unsigned int i, j;

    *(a->cols) = (a->data == NULL) ? n : *(a->cols) + n; // Si data = NULL => matrice erronée (ou vide): on impose n colonnes. Sinon: + n

    const unsigned int R = *(a->rows), C = *(a->cols);

    for (i = 0; i < R; i++)
        a->data[i] = (vector_double) realloc(a->data[i], C * sizeof(double));
    
    if (a->data != NULL)
        for (i = 0; i < R; i++)
            for (j = 0; j < n; j++)
                a->data[i][C - 1 - j] = val;
}

void add_cols_i(mat_i* a, unsigned int n, int val)
{
    unsigned int i, j;

    *(a->cols) = (a->data == NULL) ? n : *(a->cols) + n; // Si data = NULL => matrice erronée (ou vide): on impose n colonnes. Sinon: + n

    const unsigned int R = *(a->rows), C = *(a->cols);

    for (i = 0; i < R; i++)
        a->data[i] = (vector_int) realloc(a->data[i], C * sizeof(int));

    if (a->data != NULL)
        for (i = 0; i < R; i++)
            for (j = 0; j < n; j++)
                a->data[i][C - 1 - j] = val;
}

// Supprimer dans une matrice
void del_rows_d(mat_d* a, unsigned int n)
{
    if (a->data != NULL && *(a->rows) >= n + 1)
    {
        *(a->rows) -= n;

        const unsigned int R = *(a->rows);
        a->data = (vector_double*)realloc(a->data, R * sizeof(vector_double));
    }
    else
        printf("\nErreur : Matrice erronee (donnees vides) ou de format incorrect pour enlever %d lignes !\n", n);
}

void del_rows_i(mat_i* a, unsigned int n)
{
    if (a->data != NULL && *(a->rows) >= n + 1)
    {
        *(a->rows) -= n;

        const unsigned int R = *(a->rows);
        a->data = (vector_int*)realloc(a->data, R * sizeof(vector_int));
    }
    else
        printf("\nErreur : Matrice erronee (donnees vides) ou de format incorrect pour enlever %d lignes !\n", n);
}

void del_cols_d(mat_d* a, unsigned int n)
{
    if (a->data != NULL && *(a->cols) >= n + 1)
    {
        unsigned int i;

        *(a->cols) -= n;
        const unsigned int C = *(a->cols);

        for(i = 0; i < *(a->rows); i++)
            a->data[i] = (vector_double)realloc(a->data[i], C * sizeof(double));
    }
    else
        printf("\nErreur : Matrice erronee (donnees vides) ou de format incorrect pour enlever %d lignes !\n", n);
}

void del_cols_i(mat_i* a, unsigned int n)
{
    if (a->data != NULL && *(a->cols) >= n + 1)
    {
        unsigned int i;

        *(a->cols) -= n;
        const unsigned int C = *(a->cols);

        for (i = 0; i < *(a->rows); i++)
            a->data[i] = (vector_int)realloc(a->data[i], C * sizeof(int));
    }
    else
        printf("\nErreur : Matrice erronee (donnees vides) ou de format incorrect pour enlever %d lignes !\n", n);
}


// Récupérer une colonne
void recup_col_d(vect_d* rec, const mat_d A, unsigned int i)
{
    rec->data = NULL;
    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? *(A.rows) : EMPTY;

    if (A.data != NULL)
    {
        rec->data = (vector_double)malloc(*(rec->length) * sizeof(double));
        if (rec->data != NULL)
        {
            unsigned int k;
            for (k = 0; k < *(rec->length); k++)
                rec->data[k] = A.data[k][i];
        }
    }
}

void recup_col_i(vect_i* rec, const mat_i A, unsigned int i)
{
    rec->data = NULL;
    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? *(A.rows) : EMPTY;

    if (A.data != NULL)
    {
        rec->data = (vector_int) malloc(*(rec->length) * sizeof(int));
        if (rec->data != NULL)
        {
            unsigned int k;
            for (k = 0; k < *(rec->length); k++)
                rec->data[k] = A.data[k][i];
        }
    }
}

// Récupérer une ligne
void recup_row_d(vect_d* rec, const mat_d A, unsigned int i)
{
    rec->data = NULL;
    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? *(A.cols) : EMPTY;

    if (A.data != NULL)
    {
        rec->data = (vector_double)malloc(*(rec->length) * sizeof(double));
        if (rec->data != NULL)
        {
            unsigned int k;
            for (k = 0; k < *(rec->length); k++)
                rec->data[k] = A.data[i][k];
        }
    }
}

void recup_row_i(vect_i* rec, const mat_i A, unsigned int i)
{
    rec->data = NULL;
    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? *(A.cols) : EMPTY;

    if (A.data != NULL)
    {
        rec->data = (vector_int) malloc(*(rec->length) * sizeof(int));
        if (rec->data != NULL)
        {
            unsigned int k;
            for (k = 0; k < *(rec->length); k++)
                rec->data[k] = A.data[i][k];
        }
    }
}

// Découper en blocs de 4
void split4_d(const mat_d M, mat_d* a, mat_d* b, mat_d* c, mat_d* d, unsigned int i, unsigned int j)
{
    init_mat_d(a); // Initialisation du bloc haut gauche
    init_mat_d(b); // Initialisation du bloc haut droit
    init_mat_d(c); // Initialisation du bloc bas  gauche
    init_mat_d(d); // Initialisation du bloc bas  droit

    const unsigned int MR = *(M.rows), MC = *(M.cols);

    if (i >= 1 && j >= 1 && i <= MR && j <= MC) // Si le format est valide
    {
        // On donne les bons formats aux différentes matrices
        creer_nulle_d(a, i, j);
        creer_nulle_d(b, i, MC - j);
        creer_nulle_d(c, MR - i, j);
        creer_nulle_d(d, MR - i, MC - j);

        const unsigned int A = *(a->cols), B = *(b->cols), C = *(c->cols), D = *(d->cols);

        unsigned int k, l;
        int id[][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} }; // Donne la position actuelle du prochain coefficient à remplir dans chaque res[i]

        for (k = 0; k < MR; k++)
        {
            for (l = 0; l < MC; l++)
            {
                if (k < i)
                    if (l < j) // Matrice haut gauche
                    {
                        a->data[id[0][0]][id[0][1]] = M.data[k][l];
                        id[0][1] = (id[0][1] == A - 1) ? 0 : id[0][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                    else       // Matrice haut droite
                    {
                        b->data[id[1][0]][id[1][1]] = M.data[k][l];
                        id[1][1] = (id[1][1] == B - 1) ? 0 : id[1][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                else
                    if (l < j)  // Matrice bas gauche
                    {
                        c->data[id[2][0]][id[2][1]] = M.data[k][l];
                        id[2][1] = (id[2][1] == C - 1) ? 0 : id[2][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                    else       // Matrice bas droite
                    {
                        d->data[id[3][0]][id[3][1]] = M.data[k][l];
                        id[3][1] = (id[3][1] == D - 1) ? 0 : id[3][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }

            }

            // A chaque saut de ligne on incrémente les lignes d'écritures des matrices du secteur concerné 
            if (k < i) // Si on est dans le secteur haut
            {
                id[0][0]++; // Matrice haut gauche
                id[1][0]++; // Matrice haut droite
            }
            else       // Si on est dans le secteur bas
            {
                id[2][0]++; // Matrice bas gauche
                id[3][0]++; // Matrice bas droite
            }
        }
    }
}

void split4_i(const mat_i M, mat_i* a, mat_i* b, mat_i* c, mat_i* d, unsigned int i, unsigned int j)
{

    init_mat_i(a); // Initialisation du bloc haut gauche
    init_mat_i(b); // Initialisation du bloc haut droit
    init_mat_i(c); // Initialisation du bloc bas  gauche
    init_mat_i(d); // Initialisation du bloc bas  droit

    const unsigned int MR = *(M.rows), MC = *(M.cols);

    if (i >= 1 && j >= 1 && i <= MR && j <= MC) // Si le format est valide
    {
        // On donne les bons formats aux différentes matrices
        creer_nulle_i(a, i, j);
        creer_nulle_i(b, i, MC - j);
        creer_nulle_i(c, MR - i, j);
        creer_nulle_i(d, MR - i, MC - j);

        const unsigned int A = *(a->cols), B = *(b->cols), C = *(c->cols), D = *(d->cols);

        unsigned int k, l;
        int id[][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} }; // Donne la position actuelle du prochain coefficient à remplir dans chaque res[i]

        for (k = 0; k < MR; k++)
        {
            for (l = 0; l < MC; l++)
            {
                if (k < i)
                    if (l < j) // Matrice haut gauche
                    {
                        a->data[id[0][0]][id[0][1]] = M.data[k][l];
                        id[0][1] = (id[0][1] == A - 1) ? 0 : id[0][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                    else       // Matrice haut droite
                    {
                        b->data[id[1][0]][id[1][1]] = M.data[k][l];
                        id[1][1] = (id[1][1] == B - 1) ? 0 : id[1][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                else
                    if (l < j)  // Matrice bas gauche
                    {
                        c->data[id[2][0]][id[2][1]] = M.data[k][l];
                        id[2][1] = (id[2][1] == C - 1) ? 0 : id[2][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }
                    else       // Matrice bas droite
                    {
                        d->data[id[3][0]][id[3][1]] = M.data[k][l];
                        id[3][1] = (id[3][1] == D - 1) ? 0 : id[3][1] + 1; // On incrémente sauf si on est en fin de ligne pour cette matrice
                    }

            }

            // A chaque saut de ligne on incrémente les lignes d'écritures des matrices du secteur concerné 
            if (k < i) // Si on est dans le secteur haut
            {
                id[0][0]++; // Matrice haut gauche
                id[1][0]++; // Matrice haut droite
            }
            else       // Si on est dans le secteur bas
            {
                id[2][0]++; // Matrice bas gauche
                id[3][0]++; // Matrice bas droite
            }
        }
    }
}

void split4_equal_d(const mat_d M, mat_d* a, mat_d* b, mat_d* c, mat_d* d)
{
    const unsigned int R = *(M.rows), C = *(M.cols);

    unsigned int row = (R % 2 == 0) ? R : R + 1,
                 col = (C % 2 == 0) ? C : C + 1; // Si le nombre de lignes (resp. de colonnes) est impair on l'incrémente

    split4_d(M, a, b, c, d, row / 2, col / 2); // On effectue un split presque ajusté (presque des blocs égaux en taille)

    // Rajout de lignes ou de colonnes nulles pour former des blocs égaux en taille

    if (row != R) // Si le nombre de lignes de M est impair
    {
        add_rows_d(c, 1, 0.);
        add_rows_d(d, 1, 0.);
    }

    if (col != C) // Si le nombre de colonnes de M est impair
    {
        add_cols_d(b, 1, 0.);
        add_cols_d(d, 1, 0.);
    }
}

void split4_equal_i(const mat_i M, mat_i* a, mat_i* b, mat_i* c, mat_i* d)
{
    const unsigned int R = *(M.rows), C = *(M.cols);

    unsigned int row = (R % 2 == 0) ? R : R + 1, 
                 col = (C % 2 == 0) ? C : C + 1; // Si le nombre de lignes (resp. de colonnes) est impair on l'incrémente
        
    split4_i(M, a, b, c, d, row / 2, col / 2); // On effectue un split presque ajusté (presque des blocs égaux en taille)

    // Rajout de lignes ou de colonnes nulles pour former des blocs égaux en taille

    if (row != R) // Si le nombre de lignes de M est impair
    {
        add_rows_i(c, 1, 0);
        add_rows_i(d, 1, 0);
    }

    if (col != C) // Si le nombre de colonnes de M est impair
    {
        add_cols_i(b, 1, 0);
        add_cols_i(d, 1, 0);
    }

    
}

// Reconstruire une matrice à partir de 4 blocs
void fus4_d(mat_d* rec, const mat_d* A, const mat_d* B, const mat_d* C, const mat_d* D)
{
    init_mat_d(rec);

    if (A->data != NULL && B->data != NULL && C->data != NULL && D->data != NULL) // Si aucune matrice est juste initialisée (donc vide)
    {
        const unsigned int AR = *(A->rows), BR = *(B->rows), CR = *(C->rows), DR = *(D->rows),
                           AC = *(A->cols), BC = *(B->cols), CC = *(C->cols), DC = *(D->cols);

        // Vérification de la compatibilité des blocs
        if (AR == BR && AC == CC && CR == DR && BC == DC)
        {
            const unsigned int ROW = AR + CR,
                      COL = AC + BC;

            creer_nulle_d(rec, ROW, COL);

            unsigned int k, l;
            int id[][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} }; // Donne la position actuelle du prochain coefficient à lire dans chaque bloc

            for (k = 0; k < ROW; k++)
            {
                for (l = 0; l < COL; l++)
                {
                    if (k < AR)
                        if (l < AC) // Bloc haut gauche
                        {
                            rec->data[k][l] = A->data[id[0][0]][id[0][1]];
                            id[0][1] = (id[0][1] == AC - 1) ? 0 : id[0][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                        else       // Bloc haut droit
                        {
                            rec->data[k][l] = B->data[id[1][0]][id[1][1]];
                            id[1][1] = (id[1][1] == BC - 1) ? 0 : id[1][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                    else
                        if (l < AC)  // Bloc bas gauche
                        {
                            rec->data[k][l] = C->data[id[2][0]][id[2][1]];
                            id[2][1] = (id[2][1] == CC - 1) ? 0 : id[2][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                        else       // Bloc bas droit
                        {
                            rec->data[k][l] = D->data[id[3][0]][id[3][1]];
                            id[3][1] = (id[3][1] == DC - 1) ? 0 : id[3][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }

                }

                // A chaque saut de ligne on incrémente les lignes d'écritures des matrices du secteur concerné 
                if (k < AR) // Si on est dans le secteur haut
                {
                    id[0][0]++; // Matrice haut gauche
                    id[1][0]++; // Matrice haut droite
                }
                else       // Si on est dans le secteur bas
                {
                    id[2][0]++; // Matrice bas gauche
                    id[3][0]++; // Matrice bas droite
                }
            }
        }
        else
            printf("\nErreur : Bloc(s) de matrice(s) de formats incompatibles !!!\n");
    }
    else
        printf("\nErreur : Bloc(s) de matrice(s) vides !!!\n");
}

void fus4_i(mat_i* rec, const mat_i* A, const mat_i* B, const mat_i* C, const mat_i* D)
{
    init_mat_i(rec);

    if (A->data != NULL && B->data != NULL && C->data != NULL && D->data != NULL) // Si aucune matrice est juste initialisée (donc vide)
    {
        const unsigned int AR = *(A->rows), BR = *(B->rows), CR = *(C->rows), DR = *(D->rows),
                           AC = *(A->cols), BC = *(B->cols), CC = *(C->cols), DC = *(D->cols);

        // Vérification de la compatibilité des blocs
        if (AR == BR && AC == CC && CR == DR && BC == DC)
        {
            const unsigned int ROW = AR + CR,
                      COL = AC + BC;

            creer_nulle_i(rec, ROW, COL);

            unsigned int k, l;
            int id[][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} }; // Donne la position actuelle du prochain coefficient à lire dans chaque bloc

            for (k = 0; k < ROW; k++)
            {
                for (l = 0; l < COL; l++)
                {
                    if (k < AR)
                        if (l < AC) // Bloc haut gauche
                        {
                            rec->data[k][l] = A->data[id[0][0]][id[0][1]];
                            id[0][1] = (id[0][1] == AC - 1) ? 0 : id[0][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                        else       // Bloc haut droit
                        {
                            rec->data[k][l] = B->data[id[1][0]][id[1][1]];
                            id[1][1] = (id[1][1] == BC - 1) ? 0 : id[1][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                    else
                        if (l < AC)  // Bloc bas gauche
                        {
                            rec->data[k][l] = C->data[id[2][0]][id[2][1]];
                            id[2][1] = (id[2][1] == CC - 1) ? 0 : id[2][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }
                        else       // Bloc bas droit
                        {
                            rec->data[k][l] = D->data[id[3][0]][id[3][1]];
                            id[3][1] = (id[3][1] == DC - 1) ? 0 : id[3][1] + 1; // On incrémente sauf si on est en fin de ligne pour ce bloc
                        }

                }

                // A chaque saut de ligne on incrémente les lignes d'écritures des matrices du secteur concerné 
                if (k < AR) // Si on est dans le secteur haut
                {
                    id[0][0]++; // Matrice haut gauche
                    id[1][0]++; // Matrice haut droite
                }
                else       // Si on est dans le secteur bas
                {
                    id[2][0]++; // Matrice bas gauche
                    id[3][0]++; // Matrice bas droite
                }
            }
        }
        else
            printf("\nErreur : Bloc(s) de matrice(s) de formats incompatibles !!!\n");
    }
    else
        printf("\nErreur : Bloc(s) de matrice(s) vides !!!\n");
}

// Trace
double tr_d(const mat_d A)
{
    const unsigned int R = *(A.rows);

    if (A.data != NULL && R == *(A.cols))
    {
        unsigned int i;
        double t = A.data[0][0];
        for (i = 1; i < R; i++)
            t += A.data[i][i];
        return t;
    }
    else return 0.;
}

int tr_i(const mat_i A)
{
    const unsigned int R = *(A.rows);

    if (A.data != NULL && R == *(A.cols))
    {
        unsigned int i;
        int t = A.data[0][0];
        for (i = 1; i < R; i++)
            t += A.data[i][i];
        return t;
    }
    else return 0;
}

// Conversion de matrices
void cast_to_md(const mat_i A, mat_d* rec)
{
    const unsigned int R = *(A.rows), C = *(A.cols);

    init_mat_d(rec);
    creer_nulle_d(rec, R, C);

    if (rec->data != NULL && A.data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                rec->data[i][j] = (double)A.data[i][j];
    }
}

void cast_to_mi(const mat_d A, mat_i* rec)
{
    const unsigned int R = *(A.rows), C = *(A.cols);

    init_mat_i(rec);
    creer_nulle_i(rec, R, C);

    if (rec->data != NULL && A.data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                rec->data[i][j] = (int)A.data[i][j];
    }
}

// Actions flottantes sur les matrices flottantes
void round_mat(mat_d* a)
{
    const unsigned int R = *(a->rows), C = *(a->cols);

    if (a->data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = round(a->data[i][j]);
    }
}

void ceil_mat(mat_d* a)
{
    const unsigned int R = *(a->rows), C = *(a->cols);

    if (a->data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = ceil(a->data[i][j]);
    }
}

void floor_mat(mat_d* a)
{
    const unsigned int R = *(a->rows), C = *(a->cols);

    if (a->data != NULL)
    {
        unsigned int i, j;
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = floor(a->data[i][j]);
    }
}

// Conversions
void vect_to_mat_d(const vect_d U, mat_d* rec)
{
    init_mat_d(rec);

    creer_nulle_d(rec, U.length, 1);

    if (rec->data != NULL)
    {
        unsigned int i;
        for (i = 0; i < U.length; i++)
            rec->data[i][0] = U.data[i];
    }
}

void vect_to_mat_i(const vect_i U, mat_i* rec)
{
    init_mat_i(rec);

    creer_nulle_i(rec, *(U.length), 1);

    if (rec->data != NULL)
    {
        unsigned int i;
        for (i = 0; i < *(U.length); i++)
            rec->data[i][0] = U.data[i];
    }
}

void mat_to_vect_d(const mat_d A, vect_d* rec)
{
    const unsigned int R = *(A.rows);

    rec->data = NULL;
    rec->data = (double *) malloc(R * sizeof(double));

    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? R : EMPTY;

    if (rec->data != NULL && *(A.cols) == 1)
    {
        unsigned int i;
        for (i = 0; i < R; i++)
            rec->data[i] = A.data[i][0];
    }
}

void mat_to_vect_i(const mat_i A, vect_i* rec)
{
    const unsigned int R = *(A.rows);

    rec->data = NULL;
    rec->data = (int*) malloc(R * sizeof(int));

    rec->length = malloc(sizeof(unsigned int));
    *(rec->length) = (rec->length != NULL) ? R : EMPTY;

    if (rec->data != NULL && *(A.cols) == 1)
    {
        unsigned int i;
        for (i = 0; i < R; i++)
            rec->data[i] = A.data[i][0];
    }
}

// Copie de matrices
void copy_d(mat_d* rec, const mat_d* A)
{
    unsigned int i, j;

    init_mat_d(rec); // Initialisation 
    creer_nulle_d(rec, *(A->rows), *(A->cols)); // format de la matrice

    const unsigned int C = *(rec->cols);

    if (rec->data != NULL)
        for (i = 0; i < *(rec->rows); i++)
            for (j = 0; j < C; j++)
                rec->data[i][j] = A->data[i][j];
}

void copy_i(mat_i* rec, const mat_i* A)
{
    unsigned int i, j;

    init_mat_i(rec); // Initialisation 
    creer_nulle_i(rec, *(A->rows), *(A->cols)); // format de la matrice

    const unsigned int C = *(rec->cols);

    if (rec->data != NULL)
        for (i = 0; i < *(rec->rows); i++)
            for (j = 0; j < C; j++)
                rec->data[i][j] = A->data[i][j];
}

// Transposition de matrices
void transpose_d(mat_d* a)
{
    unsigned int i, j;

    mat_d cpy;
    copy_d(&cpy, a); // cpy est initialisée via copy_d

    *(a->rows) = *(cpy.cols);
    *(a->cols) = *(cpy.rows);

    const unsigned int R = *(a->rows), C = *(a->cols);

    a->data = (vector_double*)realloc(a->data, R * sizeof(vector_double));
    for (i = 0; i < R; i++)
        a->data[R - 1 - i] = (vector_double)malloc(C * sizeof(double)); // On alloue les nouvelles lignes

    if (a->data != NULL)
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = cpy.data[j][i];
}

void transpose_i(mat_i* a)
{
    unsigned int i, j;

    mat_i cpy;
    copy_i(&cpy, a); // cpy est initialisée via copy_i

    *(a->rows) = *(cpy.cols);
    *(a->cols) = *(cpy.rows);

    const unsigned int R = *(a->rows), C = *(a->cols);

    a->data = (vector_int*)realloc(a->data, R * sizeof(vector_int));
    for (i = 0; i < R; i++)
        a->data[R - 1 - i] = (vector_int)malloc(C * sizeof(int)); // On alloue les nouvelles lignes

    if (a->data != NULL)
        for (i = 0; i < R; i++)
            for (j = 0; j < C; j++)
                a->data[i][j] = cpy.data[j][i];
}

// Multiplication scalaire
void scal_mul_d(mat_d* a, double lambda)
{
    if (a->data != NULL)
    {
        const unsigned int C = *(a->cols);

        unsigned int i, j;
        for (i = 0; i < *(a->rows); i++)
            for (j = 0; j < C; j++)
                a->data[i][j] *= lambda;
    }
}

void scal_mul_i(mat_i* a, int lambda)
{
    if (a->data != NULL)
    {
        const unsigned int C = *(a->cols);

        unsigned int i, j;
        for (i = 0; i < *(a->rows); i++)
            for (j = 0; j < *(a->cols); j++)
                a->data[i][j] *= lambda;
    }
}

// Addition de matrices
void sum_d(mat_d* rec, const mat_d A, const mat_d B)
{
    const unsigned int AR = *(A.rows), AC = *(A.cols),
                       BR = *(B.rows), BC = *(B.cols);

    creer_nulle_d(rec, AR, AC);

    if (rec->data != NULL && AR == BR && AC == BC) // si formats compatibles
    {
        unsigned int i, j;
        for (i = 0; i < AR; i++)
            for (j = 0; j < BC; j++)
                rec->data[i][j] = A.data[i][j] + B.data[i][j];
    }
}

void sum_i(mat_i* rec, const mat_i A, const mat_i B)
{
    const unsigned int AR = *(A.rows), AC = *(A.cols),
                       BR = *(B.rows), BC = *(B.cols);

    if (rec->data == NULL)
        creer_nulle_i(rec, AR, AC);
    if (AR == BR && AC == BC) // si formats compatibles
    {
        unsigned int i, j;
        for (i = 0; i < AR; i++)
            for (j = 0; j < BC; j++)
                rec->data[i][j] = A.data[i][j] + B.data[i][j];
    }
}

// Soustraction de matrices
void sub_d(mat_d* rec, const mat_d A, const mat_d B)
{
    const unsigned int AR = *(A.rows), AC = *(A.cols),
                       BR = *(B.rows), BC = *(B.cols);

    creer_nulle_d(rec, AR, AC);

    if (rec->data != NULL && AR == BR && AC == BC) // si formats compatibles
    {
        unsigned int i, j;
        for (i = 0; i < AR; i++)
            for (j = 0; j < BC; j++)
                rec->data[i][j] = A.data[i][j] - B.data[i][j];
    }
}

void sub_i(mat_i* rec, const mat_i A, const mat_i B)
{
    const unsigned int AR = *(A.rows), AC = *(A.cols),
                       BR = *(B.rows), BC = *(B.cols);

    if (rec->data == NULL)
        creer_nulle_i(rec, AR, AC);
    if (rec->data != NULL && AR == BR && AC == BC) // si formats compatibles
    {
        unsigned int i, j;
        for (i = 0; i < AR; i++)
            for (j = 0; j < BC; j++)
                rec->data[i][j] = A.data[i][j] - B.data[i][j];
    }
}

// Produits matriciels
void mul_strassen_d(mat_d* rec, mat_d* A, mat_d* B)
{
    init_mat_d(rec);

    if (*(A->cols) == *(B->rows) && A->data != NULL && B->data != NULL) // Si les formats sont compatibles et les matrices non vides
    {
        const unsigned int R = *(A->rows), C = *(B->cols);

        // Détermination la taille des matrices A et B qui soit une puissance entière de 2 ou au moins divisible par 2
        int n = max(R, C);

        // On suppose la taille des matrices comme des puissances de 2 !!!
        mat_d* a11 = NULL, * a12 = NULL, * a21 = NULL, * a22 = NULL; // Matrices blocs de A
        mat_d* b11 = NULL, * b12 = NULL, * b21 = NULL, * b22 = NULL; // Matrices blocs de B
        mat_d* c11 = NULL, * c12 = NULL, * c21 = NULL, * c22 = NULL; // Matrices blocs résultat

        mat_d* m1 = NULL, * m2 = NULL, * m3 = NULL, * m4 = NULL, * m5 = NULL, * m6 = NULL, * m7 = NULL; // Matrices intermédiaires de calcul
        mat_d                             // Matrices intermédiaires de calcul des mi (1 <= i <= 7)
            * m1_1 = NULL, * m1_2 = NULL,
            * m2_1 = NULL,
            * m3_1 = NULL,
            * m4_1 = NULL,
            * m5_1 = NULL,
            * m6_1 = NULL, * m6_2 = NULL,
            * m7_1 = NULL, * m7_2 = NULL;

        // Allocations
        a11 = malloc(sizeof(mat_d));
        a12 = malloc(sizeof(mat_d));
        a21 = malloc(sizeof(mat_d));
        a22 = malloc(sizeof(mat_d));
        b11 = malloc(sizeof(mat_d));
        b12 = malloc(sizeof(mat_d));
        b21 = malloc(sizeof(mat_d));
        b22 = malloc(sizeof(mat_d));
        c11 = malloc(sizeof(mat_d));
        c12 = malloc(sizeof(mat_d));
        c21 = malloc(sizeof(mat_d));
        c22 = malloc(sizeof(mat_d));
        m1 = malloc(sizeof(mat_d));
        m2 = malloc(sizeof(mat_d));
        m3 = malloc(sizeof(mat_d));
        m4 = malloc(sizeof(mat_d));
        m5 = malloc(sizeof(mat_d));
        m6 = malloc(sizeof(mat_d));
        m7 = malloc(sizeof(mat_d));
        m1_1 = malloc(sizeof(mat_d));
        m1_2 = malloc(sizeof(mat_d));
        m2_1 = malloc(sizeof(mat_d));
        m3_1 = malloc(sizeof(mat_d));
        m4_1 = malloc(sizeof(mat_d));
        m5_1 = malloc(sizeof(mat_d));
        m6_1 = malloc(sizeof(mat_d));
        m6_2 = malloc(sizeof(mat_d));
        m7_1 = malloc(sizeof(mat_d));
        m7_2 = malloc(sizeof(mat_d));

        // Initialisations

        init_mat_d(a11);
        init_mat_d(a12);
        init_mat_d(a21);
        init_mat_d(a22);
        init_mat_d(b11);
        init_mat_d(b12);
        init_mat_d(b21);
        init_mat_d(b22);
        init_mat_d(c11);
        init_mat_d(c12);
        init_mat_d(c21);
        init_mat_d(c22);
        init_mat_d(m1);
        init_mat_d(m2);
        init_mat_d(m3);
        init_mat_d(m4);
        init_mat_d(m5);
        init_mat_d(m6);
        init_mat_d(m7);
        init_mat_d(m1_1);
        init_mat_d(m1_2);
        init_mat_d(m2_1);
        init_mat_d(m3_1);
        init_mat_d(m4_1);
        init_mat_d(m5_1);
        init_mat_d(m6_1);
        init_mat_d(m6_2);
        init_mat_d(m7_1);
        init_mat_d(m7_2);


        if (n % 2 == 1) // Si n n'est pas divisible par 2
        {
            n |= (n >> 16);
            n |= (n >> 8);
            n |= (n >> 4);
            n |= (n >> 2);
            n |= (n >> 1);
            ++n;
        }

        // Nombre de lignes / colonnes à rajouter à A et B (puis à supprimer)
        unsigned int delta_r_a = n - R, delta_c_a = (A != B) ? n - *(A->cols) : 0; // Si A = B et même adresse, on va trop rajouter de lignes / colonnes
        unsigned int delta_r_b = (A != B) ? n - *(B->rows) : 0, delta_c_b = n - C; // Si A = B et même adresse, on va trop rajouter de lignes / colonnes

        // Augmentation temporaire de A
        if (delta_r_a > 0)
            add_rows_d(A, delta_r_a, 0);
        if (delta_c_a > 0)
            add_cols_d(A, delta_c_a, 0);

        // Augmentation temporaire de B
        if (delta_r_b > 0)
            add_rows_d(B, delta_r_b, 0);
        if (delta_c_b > 0)
            add_cols_d(B, delta_c_b, 0);

        unsigned int sn = n / 2;

        // Découpe égale (n est pair)
        split4_equal_d(*A, a11, a12, a21, a22); // on découpe A en a11, a12, a21, a22 (l'initialisation se fait par cette fonction)
        split4_equal_d(*B, b11, b12, b21, b22); // on découpe B en b11, b12, b21, b22 (l'initialisation se fait par cette fonction)

        // Création spatiale des ci

        // Suppression des lignes / colonnes rajoutées à A
        if (delta_r_a > 0)
            del_rows_d(A, delta_r_a);
        if (delta_c_a > 0)
            del_cols_d(A, delta_c_a);

        // Suppression des lignes / colonnes rajoutées à B
        if (delta_r_b > 0)
            del_rows_d(B, delta_r_b);
        if (delta_c_b > 0)
            del_cols_d(B, delta_c_b);

        // Calculs intermédiaires

        // M1
        sum_d(m1_1, *a11, *a22);
        sum_d(m1_2, *b11, *b22);
        // M2
        sum_d(m2_1, *a21, *a22);
        // M3
        sub_d(m3_1, *b12, *b22);
        // M4
        sub_d(m4_1, *b21, *b11);
        // M5
        sum_d(m5_1, *a11, *a12);
        // M6
        sub_d(m6_1, *a21, *a11);
        sum_d(m6_2, *b11, *b12);
        // M7
        sub_d(m7_1, *a12, *a22);
        sum_d(m7_2, *b21, *b22);

        // /!\ Dans la suite on désalloue le plus vite possible ce qu'on peut désallouer

        // Désallocation des matrices intermédiaires (celles qu'on peut car plus jamais utilisées ultérieurement)
        destroy_mat_d(a12);
        destroy_mat_d(a21);
        destroy_mat_d(b12);
        destroy_mat_d(b21);
        free(a12);
        free(a21);
        free(b12);
        free(b21);

        // Récursivité (et désallocation immédiate (optimisation))
        // /!\ On cherche à désallouer le plus vite possible les ai et les bi donc l'ordre des mi calculées n'est pas croissant

        if (sn > BIG_SQUARE_MATRIX_SIZE) // Si la matrice reste trop grande, on itère récursivement Strassen
        {
            // M3
            mul_strassen_d(m3, a11, m3_1);
            destroy_mat_d(a11);
            destroy_mat_d(m3_1);
            free(a11);
            free(m3_1);
            // M4
            mul_strassen_d(m4, a22, m4_1);
            destroy_mat_d(a22);
            destroy_mat_d(m4_1);
            free(a22);
            free(m4_1);
            // M2
            mul_strassen_d(m2, m2_1, b11);
            destroy_mat_d(b11);
            destroy_mat_d(m2_1);
            free(b11);
            free(m2_1);
            // M5
            mul_strassen_d(m5, m5_1, b22);
            destroy_mat_d(b22);
            destroy_mat_d(m5_1);
            free(b22);
            free(m5_1);
            // M1
            mul_strassen_d(m1, m1_1, m1_2);
            destroy_mat_d(m1_1);
            destroy_mat_d(m1_2);
            free(m1_1);
            free(m1_2);
            // M6
            mul_strassen_d(m6, m6_1, m6_2);
            destroy_mat_d(m6_1);
            destroy_mat_d(m6_2);
            free(m6_1);
            free(m6_2);
            // M7
            mul_strassen_d(m7, m7_1, m7_2);
            destroy_mat_d(m7_1);
            destroy_mat_d(m7_2);
            free(m7_1);
            free(m7_2);
        }
        else // Sinon on itère la multiplication naturelle (méthode naive)
        {
            // M3
            mul_natural_d(m3, a11, m3_1);
            destroy_mat_d(a11);
            destroy_mat_d(m3_1);
            free(a11);
            free(m3_1);
            // M4
            mul_natural_d(m4, a22, m4_1);
            destroy_mat_d(a22);
            destroy_mat_d(m4_1);
            free(a22);
            free(m4_1);
            // M2
            mul_natural_d(m2, m2_1, b11);
            destroy_mat_d(b11);
            destroy_mat_d(m2_1);
            free(b11);
            free(m2_1);
            // M5
            mul_natural_d(m5, m5_1, b22);
            destroy_mat_d(b22);
            destroy_mat_d(m5_1);
            free(b22);
            free(m5_1);
            // M1
            mul_natural_d(m1, m1_1, m1_2);
            destroy_mat_d(m1_1);
            destroy_mat_d(m1_2);
            free(m1_1);
            free(m1_2);
            // M6
            mul_natural_d(m6, m6_1, m6_2);
            destroy_mat_d(m6_1);
            destroy_mat_d(m6_2);
            free(m6_1);
            free(m6_2);
            // M7
            mul_natural_d(m7, m7_1, m7_2);
            destroy_mat_d(m7_1);
            destroy_mat_d(m7_2);
            free(m7_1);
            free(m7_2);
        }

        // C11
        sum_d(c11, *m1, *m4);
        sub_d(c11, *c11, *m5);
        sum_d(c11, *c11, *m7);
        destroy_mat_d(m7);
        free(m7);

        // C12
        sum_d(c12, *m3, *m5);
        destroy_mat_d(m5);
        free(m5);

        // C21
        sum_d(c21, *m2, *m4);
        destroy_mat_d(m4);
        free(m4);

        // C22
        sub_d(c22, *m1, *m2);
        sum_d(c22, *c22, *m3);
        sum_d(c22, *c22, *m6);
        destroy_mat_d(m1);
        destroy_mat_d(m2);
        destroy_mat_d(m3);
        destroy_mat_d(m6);
        free(m1);
        free(m2);
        free(m3);
        free(m6);

        // Fusion des 4 blocs formant C
        fus4_d(rec, c11, c12, c21, c22);

        // Désallocation finale (optimisation)
        destroy_mat_d(c11);
        destroy_mat_d(c12);
        destroy_mat_d(c21);
        destroy_mat_d(c22);
        free(c11);
        free(c12);
        free(c21);
        free(c22);

        if (delta_r_a > 0) // Suppression à C des lignes rajoutées à A
            del_rows_d(rec, delta_r_a);
        if (delta_c_b > 0) // Suppression à C des colonnes rajoutées à B
            del_cols_d(rec, delta_c_b);
    }
    else
        printf("\nErreur : matrices de mauvais formats ou vides7 !!! \n");
}

void mul_strassen_i(mat_i* rec, mat_i* A, mat_i* B)
{
    init_mat_i(rec);

    if (*(A->cols) == *(B->rows) && A->data != NULL && B->data != NULL) // Si les formats sont compatibles et les matrices non vides
    {
        const unsigned int R = *(A->rows), C = *(B->cols);

        // Détermination la taille des matrices A et B qui soit une puissance entière de 2 ou au moins divisible par 2
        int n = max(R, C);

        // On suppose la taille des matrices comme des puissances de 2 !!!
        mat_i *a11 = NULL, *a12 = NULL, *a21 = NULL, *a22 = NULL; // Matrices blocs de A
        mat_i *b11 = NULL, *b12 = NULL, *b21 = NULL, *b22 = NULL; // Matrices blocs de B
        mat_i *c11 = NULL, *c12 = NULL, *c21 = NULL, *c22 = NULL; // Matrices blocs résultat

        mat_i *m1 = NULL, *m2 = NULL, *m3 = NULL, *m4 = NULL, *m5 = NULL, *m6 = NULL, *m7 = NULL; // Matrices intermédiaires de calcul
        mat_i                             // Matrices intermédiaires de calcul des mi (1 <= i <= 7)
            *m1_1 = NULL, *m1_2 = NULL,
            *m2_1 = NULL,
            *m3_1 = NULL,
            *m4_1 = NULL,
            *m5_1 = NULL,
            *m6_1 = NULL, *m6_2 = NULL,
            *m7_1 = NULL, *m7_2 = NULL;

        // Allocations
        a11 = malloc(sizeof(mat_i));
        a12 = malloc(sizeof(mat_i));
        a21 = malloc(sizeof(mat_i));
        a22 = malloc(sizeof(mat_i));
        b11 = malloc(sizeof(mat_i));
        b12 = malloc(sizeof(mat_i));
        b21 = malloc(sizeof(mat_i));
        b22 = malloc(sizeof(mat_i));
        c11 = malloc(sizeof(mat_i));
        c12 = malloc(sizeof(mat_i));
        c21 = malloc(sizeof(mat_i));
        c22 = malloc(sizeof(mat_i));
        m1 = malloc(sizeof(mat_i));
        m2 = malloc(sizeof(mat_i));
        m3 = malloc(sizeof(mat_i));
        m4 = malloc(sizeof(mat_i));
        m5 = malloc(sizeof(mat_i));
        m6 = malloc(sizeof(mat_i));
        m7 = malloc(sizeof(mat_i));
        m1_1 = malloc(sizeof(mat_i));
        m1_2 = malloc(sizeof(mat_i));
        m2_1 = malloc(sizeof(mat_i));
        m3_1 = malloc(sizeof(mat_i));
        m4_1 = malloc(sizeof(mat_i));
        m5_1 = malloc(sizeof(mat_i));
        m6_1 = malloc(sizeof(mat_i));
        m6_2 = malloc(sizeof(mat_i));
        m7_1 = malloc(sizeof(mat_i));
        m7_2 = malloc(sizeof(mat_i));

        // Initialisations

        init_mat_i(a11);
        init_mat_i(a12);
        init_mat_i(a21);
        init_mat_i(a22);
        init_mat_i(b11);
        init_mat_i(b12);
        init_mat_i(b21);
        init_mat_i(b22);
        init_mat_i(c11);
        init_mat_i(c12);
        init_mat_i(c21);
        init_mat_i(c22);
        init_mat_i(m1);
        init_mat_i(m2);
        init_mat_i(m3);
        init_mat_i(m4);
        init_mat_i(m5);
        init_mat_i(m6);
        init_mat_i(m7);
        init_mat_i(m1_1);
        init_mat_i(m1_2);
        init_mat_i(m2_1);
        init_mat_i(m3_1);
        init_mat_i(m4_1);
        init_mat_i(m5_1);
        init_mat_i(m6_1);
        init_mat_i(m6_2);
        init_mat_i(m7_1);
        init_mat_i(m7_2);


        if (n % 2 == 1) // Si n n'est pas divisible par 2
        {
            n |= (n >> 16);
            n |= (n >> 8);
            n |= (n >> 4);
            n |= (n >> 2);
            n |= (n >> 1);
            ++n;
        }

        // Nombre de lignes / colonnes à rajouter à A et B (puis à supprimer)
        unsigned int delta_r_a = n - R, delta_c_a = (A != B) ? n - *(A->cols) : 0; // Si A = B et même adresse, on va trop rajouter de lignes / colonnes
        unsigned int delta_r_b = (A != B) ? n - *(B->rows) : 0, delta_c_b = n - C; // Si A = B et même adresse, on va trop rajouter de lignes / colonnes

        // Augmentation temporaire de A
        if (delta_r_a > 0)
            add_rows_i(A, delta_r_a, 0);
        if (delta_c_a > 0)
            add_cols_i(A, delta_c_a, 0);

        // Augmentation temporaire de B
        if (delta_r_b > 0)
            add_rows_i(B, delta_r_b, 0);
        if (delta_c_b > 0)
            add_cols_i(B, delta_c_b, 0);

        unsigned int sn = n / 2;

        // Découpe égale (n est pair)
        split4_equal_i(*A, a11, a12, a21, a22); // on découpe A en a11, a12, a21, a22 (l'initialisation se fait par cette fonction)
        split4_equal_i(*B, b11, b12, b21, b22); // on découpe B en b11, b12, b21, b22 (l'initialisation se fait par cette fonction)

        // Création spatiale des ci

        // Suppression des lignes / colonnes rajoutées à A
        if (delta_r_a > 0)
            del_rows_i(A, delta_r_a);
        if (delta_c_a > 0)
            del_cols_i(A, delta_c_a);

        // Suppression des lignes / colonnes rajoutées à B
        if (delta_r_b > 0)
            del_rows_i(B, delta_r_b);
        if (delta_c_b > 0)
            del_cols_i(B, delta_c_b);

        // Calculs intermédiaires

        // M1
        sum_i(m1_1, *a11, *a22);
        sum_i(m1_2, *b11, *b22);
        // M2
        sum_i(m2_1, *a21, *a22);
        // M3
        sub_i(m3_1, *b12, *b22);
        // M4
        sub_i(m4_1, *b21, *b11);
        // M5
        sum_i(m5_1, *a11, *a12);
        // M6
        sub_i(m6_1, *a21, *a11);
        sum_i(m6_2, *b11, *b12);
        // M7
        sub_i(m7_1, *a12, *a22);
        sum_i(m7_2, *b21, *b22);

        // /!\ Dans la suite on désalloue le plus vite possible ce qu'on peut désallouer

        // Désallocation des matrices intermédiaires (celles qu'on peut car plus jamais utilisées ultérieurement)
        destroy_mat_i(a12);
        destroy_mat_i(a21);
        destroy_mat_i(b12);
        destroy_mat_i(b21);
        free(a12);
        free(a21);
        free(b12);
        free(b21);

        // Récursivité (et désallocation immédiate (optimisation))
        // /!\ On cherche à désallouer le plus vite possible les ai et les bi donc l'ordre des mi calculées n'est pas croissant
        
        if (sn > BIG_SQUARE_MATRIX_SIZE) // Si la matrice reste trop grande, on itère récursivement Strassen
        {
            // M3
            mul_strassen_i(m3, a11, m3_1);
            destroy_mat_i(a11);
            destroy_mat_i(m3_1);
            free(a11);
            free(m3_1);
            // M4
            mul_strassen_i(m4, a22, m4_1);
            destroy_mat_i(a22);
            destroy_mat_i(m4_1);
            free(a22);
            free(m4_1);
            // M2
            mul_strassen_i(m2, m2_1, b11);
            destroy_mat_i(b11);
            destroy_mat_i(m2_1);
            free(b11);
            free(m2_1);
            // M5
            mul_strassen_i(m5, m5_1, b22);
            destroy_mat_i(b22);
            destroy_mat_i(m5_1);
            free(b22);
            free(m5_1);
            // M1
            mul_strassen_i(m1, m1_1, m1_2);
            destroy_mat_i(m1_1);
            destroy_mat_i(m1_2);
            free(m1_1);
            free(m1_2);
            // M6
            mul_strassen_i(m6, m6_1, m6_2);
            destroy_mat_i(m6_1);
            destroy_mat_i(m6_2);
            free(m6_1);
            free(m6_2);
            // M7
            mul_strassen_i(m7, m7_1, m7_2);
            destroy_mat_i(m7_1);
            destroy_mat_i(m7_2);
            free(m7_1);
            free(m7_2);
        }
        else // Sinon on itère la multiplication naturelle (méthode naive)
        {
            // M3
            mul_natural_i(m3, a11, m3_1);
            destroy_mat_i(a11);
            destroy_mat_i(m3_1);
            free(a11);
            free(m3_1);
            // M4
            mul_natural_i(m4, a22, m4_1);
            destroy_mat_i(a22);
            destroy_mat_i(m4_1);
            free(a22);
            free(m4_1);
            // M2
            mul_natural_i(m2, m2_1, b11);
            destroy_mat_i(b11);
            destroy_mat_i(m2_1);
            free(b11);
            free(m2_1);
            // M5
            mul_natural_i(m5, m5_1, b22);
            destroy_mat_i(b22);
            destroy_mat_i(m5_1);
            free(b22);
            free(m5_1);
            // M1
            mul_natural_i(m1, m1_1, m1_2);
            destroy_mat_i(m1_1);
            destroy_mat_i(m1_2);
            free(m1_1);
            free(m1_2);
            // M6
            mul_natural_i(m6, m6_1, m6_2);
            destroy_mat_i(m6_1);
            destroy_mat_i(m6_2);
            free(m6_1);
            free(m6_2);
            // M7
            mul_natural_i(m7, m7_1, m7_2);
            destroy_mat_i(m7_1);
            destroy_mat_i(m7_2);
            free(m7_1);
            free(m7_2);
        }

        // C11
        sum_i(c11, *m1, *m4);
        sub_i(c11, *c11, *m5);
        sum_i(c11, *c11, *m7);
        destroy_mat_i(m7);
        free(m7);

        // C12
        sum_i(c12, *m3, *m5);
        destroy_mat_i(m5);
        free(m5);

        // C21
        sum_i(c21, *m2, *m4);
        destroy_mat_i(m4);
        free(m4);

        // C22
        sub_i(c22, *m1, *m2);
        sum_i(c22, *c22, *m3);
        sum_i(c22, *c22, *m6);
        destroy_mat_i(m1);
        destroy_mat_i(m2);
        destroy_mat_i(m3);
        destroy_mat_i(m6);
        free(m1);
        free(m2);
        free(m3);
        free(m6);

        // Fusion des 4 blocs formant C
        fus4_i(rec, c11, c12, c21, c22);

        // Désallocation finale (optimisation)
        destroy_mat_i(c11);
        destroy_mat_i(c12);
        destroy_mat_i(c21);
        destroy_mat_i(c22);
        free(c11);
        free(c12);
        free(c21);
        free(c22);

        if (delta_r_a > 0) // Suppression à C des lignes rajoutées à A
            del_rows_i(rec, delta_r_a);
        if (delta_c_b > 0) // Suppression à C des colonnes rajoutées à B
            del_cols_i(rec, delta_c_b);
    }
    else
        printf("\nErreur : matrices de mauvais formats ou vides7 !!! \n");
}

void mul_natural_d(mat_d* rec, mat_d* A, mat_d* B)
{
    init_mat_d(rec);

    const unsigned int AR = *(A->rows), AC = *(A->cols),
                       BR = *(B->rows), BC = *(B->cols);

    if (AC == BR && A->data != NULL && B->data != NULL) // Si les formats sont compatibles et les matrices non vides
    {
        unsigned int i, j, k;

        creer_nulle_d(rec, AR, BC);

        if (rec->data != NULL)
        {
            for (i = 0; i < AR; i++)
                for (j = 0; j < BC; j++)
                    for (k = 0; k < AC; k++)
                        rec->data[i][j] += A->data[i][k] * B->data[k][j];
        }
    }
    else
        printf("\nErreur : matrices de mauvais formats ou vides !!! \n");
}

void mul_natural_i(mat_i* rec, mat_i* A, mat_i* B)
{
    init_mat_i(rec);

    const unsigned int AR = *(A->rows), AC = *(A->cols),
                       BR = *(B->rows), BC = *(B->cols);

    if (AC == BR && A->data != NULL && B->data != NULL) // Si les formats sont compatibles et les matrices non vides
    {
        unsigned int i, j, k;

        creer_nulle_i(rec, AR, BC);

        if (rec->data != NULL)
        {
            for (i = 0; i < AR; i++)
                for (j = 0; j < BC; j++)
                    for (k = 0; k < AC; k++)
                        rec->data[i][j] += A->data[i][k] * B->data[k][j];
        }
    }
    else
        printf("\nErreur : matrices de mauvais formats ou vides !!! \n");
}

// Graphiques /Debug (console)
void affiche_d(const mat_d A)
{
    printf("\n");
    if (A.data != NULL)
    {
        const unsigned int R = *(A.rows), C = *(A.cols);

        unsigned int i, j;

        for (i = 0; i < R; i++)
        {
            if (i == 0)
                printf("/ ");
            else if (i == R - 1)
                printf("\\ ");
            else
                printf("| ");

            for (j = 0; j < C; j++)
                printf("%lf ", A.data[i][j]);

            if (i == 0)
                printf("\\ \n");
            else if (i == R - 1)
                printf("/ \n");
            else
                printf("| \n");
        }
    }
    else
        printf("ERREUR : Matrice non definie (donnees vides)\n");
}

void affiche_i(const mat_i A)
{
    printf("\n");
    if (A.data != NULL)
    {
        const unsigned int R = *(A.rows), C = *(A.cols);

        unsigned int i, j;

        for (i = 0; i < R; i++)
        {
            if (i == 0)
                printf("/ ");
            else if (i == R - 1)
                printf("\\ ");
            else
                printf("| ");

            for (j = 0; j < C; j++)
                printf("%d ", A.data[i][j]);

            if (i == 0)
                printf("\\ \n");
            else if (i == R - 1)
                printf("/ \n");
            else
                printf("| \n");
        }
    }
    else
        printf("ERREUR : Matrice non definie (donnees vides)\n");
}