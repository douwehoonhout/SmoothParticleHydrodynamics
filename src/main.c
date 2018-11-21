#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "dynamic-array.h"
#include "particle.h"
#include "particle-list.h"

int main() {
    int i, size = 500000000;
    int* array = alloc_array(size);
    int chunk = size / 100;

    omp_set_num_threads(4);

    particle_list particles = alloc_particles(10);

    for (int j = 0; j < particles.n; j++) {
        particles.particles[j].x = j;
    }

    for (int j = 0; j < particles.n; j++) {
        printf("Particle x: %f \n", particles.particles[j].x);
    }
    double begin = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk) private(i)
    for (i = 0; i < size; i++) {
        array[i] = i;
    }

    double end = omp_get_wtime();
    double time_spent = (end - begin);

    printf("Hello, World! %f\n", time_spent);
    return 0;
}