#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "particle.h"
#include <math.h>
#include "particle-list.h"
#include "line-change.h"
#include "smoothing-function.h"

#define DECELERATE 2.0
#define H 60
#define MAX_SPEED 33.33
#define NR_ITERATIONS 2000
#define TAU 5.0
#define TIME_STEP  0.05
#define RHO_C 0.025
#define RHO_J 0.125

void calc_density(particle* particles, int size) {
    for (int i = 0; i < size; i++) {
        double rho = 0;
        for (int j = 0; j < size; j++) {
            if (i == j) {
                continue;
            }
            if (particles[i].y == particles[i].y) {
                rho += -(particles[i].velocity - particles[j].velocity) *
                       smoothing_funtion(particles[i], particles[j], H);
            }
        }
        particles[i].density = particles[i].density + rho * TIME_STEP;

    }
}

void calc_density2(particle* particles, int size) {
    for (int i = 0; i < size; i++){
        double rho = 0;
        for (int j = 0; j < size; j++) {
            if (particles[i].y == particles[j].y) {
                rho += smoothing_funtion2(particles[i], particles[j], H);
            }
        }
        particles[i].density = rho;
    }
}

void calc_x(particle* particles, int size){
    for (int i = 0; i < size; i++) {
        particles[i].x = particles[i].x + particles[i].velocity * TIME_STEP;
    }
}

void calc_v(particle* particles, int size, int time){

// For adjusting the speed of the front car

        int temp = 0;
        for (int i =0; i <size; i++){
            for (int j =0; j <size; j++){
                if (particles[i].y == particles[i].y && particles[i].x >= particles[j].x){
                    continue;
                }
                else{
                    temp = 1;
                }
            }
            if (temp != 1){

            }
        }



    for (int i = size-1; i >= 0; i--) {
        double left_hand_side = (RHO_C*MAX_SPEED) / (RHO_J - RHO_C);
        double right_hand_side = RHO_J/particles[i].density - 1.0;
        particles[i].ve = left_hand_side * right_hand_side;
        if (particles[i].density < RHO_C) {
            particles[i].ve = MAX_SPEED;
        }

    }

    particles[size - 1].ve = MAX_SPEED;
    if (time % 40 > 20) {
        particles[size - 1].ve = MAX_SPEED - 5;
    }

    // Calculate new velocities
    for (int i = 0; i < size; i++) {
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
}


int main() {

    double time = 0;
    clock_t begin, end, begin1, end1;

    begin1 = clock();

    omp_set_num_threads(4);
    particle_list particle_list1 = read_from_file();
    particle* particles = particle_list1.particles;
    initial_write(particle_list1);

    for (int loop = 0; loop < NR_ITERATIONS; loop++) {

        calc_density2(particles, particle_list1.size);
        calc_x(particles, particle_list1.size);
        calc_v(particles, particle_list1.size, (int) time);

        time += TIME_STEP;
        write_to_file(particle_list1, time);

    }
    end1 = clock();
    printf("How fast am I? %lf \n", (double)(end1 - begin1) / CLOCKS_PER_SEC);

    return 0;
}