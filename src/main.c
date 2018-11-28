#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "particle.h"
#include "particle-list.h"
#include "smooting-function.h"

int main() {

    omp_set_num_threads(4);
    particle_list particle_list1 = read_from_file();
    particle* particles = particle_list1.particles;
    double time_step = 0.1, max_speed = 33.33;

    // Calculate dRho / dt
    for (int i = 0; i < particle_list1.n; i++) {
        double rho = 0;
        for(int j = 0; j < particle_list1.n; j++) {
            if (i == j) {
                continue;
            }
            rho += (particles[i].velocity - particles[j].velocity) * smoothing_funtion(particles[i], particles[j], 201);
        }
        printf("Rho result %lf \n", rho);
        particles[i].rho = rho;
    }

    for (int i = 0; i < particle_list1.n; i++) {
        particles[i].x = particles[i].velocity * time_step + 1 / particles[i].rho;
        //printf("x: %lf density: %lf velocity: %lf rho: %lf \n", particles[i].x, particles[i].density, particles[i].velocity, particles[i].rho);
    }

    for (int i = particle_list1.n - 2; i >= 0; i--) {
        double left_hand_side = (1.0 / (3.0 * max_speed)) / (max_speed / ((1.0 / 7.0) - (1.0 / (3.0 * max_speed))));
        double right_hand_side = (particles[i].x - particles[i + 1].x) / 7 - 1;
        particles[i].velocity = left_hand_side * right_hand_side;
        if (particles[i].velocity < 0) {
            particles[i].velocity = 0;
        }
        if (particles[i].velocity > max_speed) {
            particles[i].velocity = max_speed;
        }
    }

    for (int i = 0; i < particle_list1.n; i++) {
        printf("x: %lf density: %lf velocity: %lf rho: %lf \n", particles[i].x, particles[i].density, particles[i].velocity, particles[i].rho);
    }
    printf("Zou git nu eindelijk werke   n?");

    return 0;
}