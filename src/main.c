#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "particle.h"
#include <math.h>
#include "particle-list.h"
#include "line-change.h"
#include "smoothing-function.h"

#define DECELERATE 8.0
#define H 50.0
#define MAX_SPEED 33.33
#define NR_ITERATIONS 2000
#define TAU 6.0
#define TIME_STEP  0.1
#define RHO_C 0.025
#define RHO_J 0.125
#define ROADLENGTH 1000.0

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

// WORKS FOR 1D
void calc_density(particle* particles, int size) {
    for (int i = 0; i < size; i++) {
        double rho = 0;
        for(int j = 0; j < size; j++) {
            if (i == j) {
                continue;
            }
            rho += -(particles[i].velocity - particles[j].velocity) * smoothing_function(particles[i], particles[j], H, ROADLENGTH);
        }
//        if (particles[i].density < 0) {
//            printf("Rho: %lf Density: %lf \n", rho, particles[i].density);
//        }
        particles[i].density = particles[i].density + rho*TIME_STEP;

    }
}


void calc_x(particle* particles, int size) {
    for (int i = 0; i < size; i++) {
        particles[i].x = particles[i].x + particles[i].velocity * TIME_STEP;


        if (particles[i].x > ROADLENGTH) {
            particles[i].x -= ROADLENGTH;
        }


        //Checking if the car in front is not to close to cause a collision
//        if (fabs(particles[i].x - particles[i + 1].x) <= 0.5) {
//            printf("ERROR: CRASH OCCURRED\n");
//            exit(0);
//        }
    }
}

void calc_v(particle* particles, int size, int time){

// For adjusting the speed of the front car
/*
        int temp;
        for (int i =0; i <size; i++){
            for (int j =0; j <size; j++){
                if (particles[i].y == particles[i].y && particles[i].x >= particles[j].x){
                    continue;
                }
                else{
                    temp = 0;
                }
            }
            if (temp != 1){

            }
        }
*/

    for (int i = size-1; i >= 0; i--) {
        double left_hand_side = (RHO_C*MAX_SPEED) / (RHO_J - RHO_C);
        double right_hand_side = RHO_J/particles[i].density - 1.0;
        particles[i].ve = left_hand_side * right_hand_side;
        if (particles[i].ve < 0) {
            particles[i].ve = 0;
        }
        if (particles[i].ve > MAX_SPEED) {
            particles[i].ve = MAX_SPEED;
        }
        if (particles[i].density < RHO_C) {
            particles[i].ve = MAX_SPEED;
        }
    }

    if (time % 80 > 40) {
        particles[size - 1].ve = 0;
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

    omp_set_num_threads(4);
    particle_list particle_list1 = read_from_file();
    particle* particles = particle_list1.particles;
    initial_write(particle_list1);

    for (int loop = 0; loop < NR_ITERATIONS; loop++) {

        calc_density(particles, particle_list1.size);
        calc_x(particles, particle_list1.size);
        calc_v(particles, particle_list1.size, (int) time);

        time += TIME_STEP;
        write_to_file(particle_list1, time);

    }

    return 0;
}