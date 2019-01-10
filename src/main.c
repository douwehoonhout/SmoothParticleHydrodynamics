#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "particle.h"
#include <math.h>
#include "particle-list.h"
#include "line-change.h"
#include "smoothing-function.h"

#define DECELERATE 8.0
#define H 150.0
#define MAX_SPEED 33.33
#define NR_ITERATIONS 2000
#define TAU 5.0
#define TIME_STEP  0.5
#define RHO_C 0.025
#define RHO_J 0.125
#define ROADLENGTH 2000
#define LANEWIDTH 3.7
#define LANECHANGETIME 5

void lane_change(particle* particles, int size, int i) {
    int safeToOvertake = 1;
    for(int j  = 0; j < size; j++) {
        if (i == j) {
            continue;
        }

        // Only check if it is safe with cars on the left lane
        if (particles[j].y == 0) {
            continue;
        }

        // Check whether there is enough distance to make the lane change
        if (fabs(particles[i].x - particles[j].x) < 100) {
            safeToOvertake = 0;
            break;
        }

    }
    if (safeToOvertake == 1) {
        particles[i].overtake = 1;
    }
}

void calc_density(particle* particles, int size) {
    for (int i = 0; i < size; i++) {
        double rho = 0, rho2 = 0;
        particle temp = particles[i];
        if (temp.y == 0){
            temp.y = 3.7;
        }
        else if(temp.y == 3.7){
            temp.y = 0;
        }


        for(int j  = 0; j < size; j++) {
            if (i == j) {
                continue;
            }
            rho += -(particles[i].velocity - particles[j].velocity) * smoothing_function(particles[i], particles[j], H);
            if (particles[i].y < 3.7 && particles[i].overtake != 0) {
                rho2 += -(temp.velocity - particles[j].velocity) * smoothing_function(temp, particles[j], H);
            }
        }

        // If density on the adjacent lane is lower than the current lane, then switch lanes.
        if (rho2 < 0 && rho2 < rho) {
            lane_change(particles, size, i);
        }
        particles[i].density = particles[i].density + rho * TIME_STEP;

    }
}


void calc_x(particle* particles, int size){
    for (int i = 0; i < size; i++) {
        particles[i].x = particles[i].x + particles[i].velocity * TIME_STEP;

        //Creates the roundabout structure
        /*
        if (particles[i].x > ROADLENGTH) {
            particles[i].x -= ROADLENGTH;
        }
        */

    }
}

void calc_y(particle* particles, int size) {
    for (int i = 0; i < size; i++) {

        if (particles[i].overtake == 0) {
            continue;
        }

        if (particles[i].overtake == 1) {
            particles[i].y += particles[i].vy * TIME_STEP;
        }

        if (particles[i].y >= 3.7) {
            particles[i].y = 3.7;
            particles[i].overtake = 0;
        }
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
        } if (particles[i].ve > MAX_SPEED) {
            particles[i].ve = MAX_SPEED;
        } if (particles[i].density < RHO_C) {
            particles[i].ve = MAX_SPEED;
        }
    }

    particles[size - 1].ve = MAX_SPEED;
    if (time % 200 > 100) {
        particles[size - 1].ve = 15;
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

void calc_vy(particle* particles, int size){
    double acceleration = 4 * LANEWIDTH / pow(LANECHANGETIME, 2);
    for (int i = 0; i < size; i++){
        if (particles[i].overtake == 1){
            if (particles[i].y < LANEWIDTH / 2){
                particles[i].vy += acceleration * TIME_STEP;
            }
            else {
                particles[i].vy -= acceleration * TIME_STEP;
            }
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
        calc_y(particles, particle_list1.size);
        calc_v(particles, particle_list1.size, (int) time);
        calc_vy(particles, particle_list1.size);

        time += TIME_STEP;
        write_to_file(particle_list1, time);

    }

    return 0;
}