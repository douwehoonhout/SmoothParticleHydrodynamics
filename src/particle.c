#include <stdio.h>
#include <stdlib.h>
#include "particle.h"

particle* alloc_particle() {
    return calloc(1, sizeof(particle));
}

void free_particle(particle* particle1) {
    free(particle1);
}

