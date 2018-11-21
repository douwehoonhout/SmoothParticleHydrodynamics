#include <stdlib.h>
#include "particle-list.h"

particle_list alloc_particles(int size) {
    particle_list particles;
    particles.n = size;
    particles.particles = malloc(size * sizeof(particle));
    return particles;
}

