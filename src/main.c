#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "particle.h"
#include <math.h>
#include "particle-list.h"
#include "smooting-function.h"

#define DECELERATE 5.0
#define H 201.0
#define MAX_SPEED 33.33
#define NR_ITERATIONS 2000
#define TAU 5.0
#define TIME_STEP  0.03
#define RHO_C 0.025
#define RHO_J 0.125

int main() {

    double time = 0;

    omp_set_num_threads(4);
    particle_list particle_list1 = read_from_file();
    particle* particles = particle_list1.particles;
    initial_write(particle_list1);

    for (int loop = 0; loop < NR_ITERATIONS; loop++) {
        // Calculate dRho / dt
        for (int i = 0; i < particle_list1.n; i++) {
            double rho = 0;
            for(int j = 0; j < particle_list1.n; j++) {
                if (i == j) {
                    continue;
                }
                rho += -(particles[i].velocity - particles[j].velocity) * smoothing_funtion(particles[i], particles[j], H);

            }
            printf("%f \n", rho);
            particles[i].density = particles[i].density + rho*TIME_STEP;

        }

        // Calculate new x
        for (int i = 0; i < particle_list1.n; i++) {
            particles[i].x = particles[i].x + particles[i].velocity * TIME_STEP;
        }

        // Calculate wanted velocities
        particles[9].ve = MAX_SPEED;
        if ((int)time % 40 > 20) {
            particles[9].ve = MAX_SPEED - 30;
        }
        for (int i = particle_list1.n - 2; i >= 0; i--) {
            double left_hand_side = (RHO_C*MAX_SPEED) / (RHO_J - RHO_C);
            double right_hand_side = RHO_J/particles[i].density - 1.0;
            particles[i].ve = left_hand_side * right_hand_side;
            if (particles[i].density < RHO_C) {
                particles[i].ve = MAX_SPEED;
            }

        }

        // Calculate new velocities
        for (int i = 0; i < particle_list1.n; i++) {
            const double deltaV = (particles[i].ve - particles[i].velocity);
            if (deltaV < 0) {
                particles[i].velocity = particles[i].velocity + deltaV / DECELERATE * TIME_STEP;
            } else {
                particles[i].velocity = particles[i].velocity + deltaV / TAU * TIME_STEP;
            }
            if (particles[i].velocity < 0) {
                particles[i].velocity = 0;
            }
        }

        time += TIME_STEP;
        write_to_file(particle_list1, time);

    }

    return 0;
}