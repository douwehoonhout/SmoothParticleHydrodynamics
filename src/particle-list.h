//
// Created by douwe on 20-11-18.
//
#include "particle.h"

#ifndef SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
#define SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
    typedef struct particle_list {
        int size;                /* Number of particles    */
        particle* particles;
    } particle_list;

    particle_list alloc_particles(int size);
    particle_list read_from_file();
    void write_to_file(particle_list particle_list1, double time);
    void initial_write(particle_list particles_list1);
    void initialize_particles(particle_list particle_list1, int size);
#endif //SMOOTHPARTICLEHYDRODYNAMICS_PARTICLE_LIST_H
