#include "line-change.h"
#include "particle-list.h"
#include <math.h>


void make_line_change_decision(particle_list particle_list, double time_step) {
    particle* particles = particle_list.particles;
    for (int i = 0; i < particle_list.size; i++) {
        if (particles[i].overtake == -1) {
            particles[i].y = particles[i].y - time_step;
            if (particles[i].y < 0) {
                particles[i].overtake = 0;
            }
            continue;
        }

        if (particles[i].overtake == 1) {
            particles[i].y = particles[i].y + time_step;
            if (particles[i].y > 3.7) {
                particles[i].overtake = 0;
            }
            continue;
        }


        for (int j = 0; j < particle_list.size; j++) {
            if (i == j || fabs(particles[i].y - particles[j].y) > 3.7) {
                continue;
            }
            if (particles[j].ve < particles[i].ve && particles[j].x - particles[i].x < 200) {
                particles[i].y = particles[i].y + time_step;
            }
        }
    }
}