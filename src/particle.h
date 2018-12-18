#ifndef SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_H
#define SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_H

typedef struct particle {
    double x;
    double y;
    double density;
    double ve;
    double velocity;
    double rho;
} particle;

particle* alloc_particle();
void free_particle(particle* s);

#endif //SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_H
