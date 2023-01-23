#include "ville.h"

int saveCity(city* c, FILE* f) {
    if (f == NULL) {
        return 1;
    }

    fprintf(f, "%d %d %d\n", c->height, c->length, c->width);

    // Write map
    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->length; j++) {
            fprintf(f, "%d ", c->map[i][j]);
        }
        fprintf(f, "\n");
    }

    // Write emitters
    fprintf(f, "%d\n", c->emitter->length);
    for (int i = 0; i < c->emitter->length; i++) {
        fprintf(f, "%lf %lf %lf %lf\n", c->emitter[i].frequency, c->emitter[i].power, c->emitter[i].lambda, c->emitter[i].pulsation);
    }
    // Write receivers
    fprintf(f, "%d\n", c->receiver->length);
    for (int i = 0; i < c->receiver->length; i++) {
        fprintf(f, "%lf %lf %lf\n", c->receiver[i].frequency, c->receiver[i].lambda, c->receiver[i].pulsation);
    }

    return 0;
}
