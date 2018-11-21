//
// Created by douwe on 20-11-18.
//
#include "particle.h"

#ifndef SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
#define SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
    typedef struct particle_list {
        int n;                /* Number of particles    */
        particle* particles;
    } particle_list;

    particle_list alloc_particles(int size);
    void initialize_particles(particle_list particle_list1, int size);
#endif //SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
