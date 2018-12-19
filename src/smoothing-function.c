#include <math.h>
#include <stdio.h>
#include "particle.h"

double smoothing_funtion(particle particle1, particle particle2, int h) {
    double r = (particle2.x - particle1.x) / (double) h;

    if (r >= 2 || r <= -2) {
        return 0;
    }

    if (r < -1) {
        return 0.5 * (2+r) * (2+r) * 1/h;
    }

    if (r < 0) {
        return (-2 * r - 1.5 * r * r) * 1/h;
    }

    if (r < 1) {
        return (-2 * r + 1.5 * r * r) * 1/h;
    }
    return -0.5 * (2-r) * (2-r) * 1/h;
}

//double smoothing_funtion(particle particle1, particle particle2, int h) {
//    double r = sqrt((particle2.x - particle1.x)*(particle2.x - particle1.x) + (particle2.y - particle1.y)*(particle2.y - particle1.y)) / (double) h;
//
//    if (r >= 2) {
//        return 0;
//    }
//
//    if (r >= 1) {
//        return -0.5 * (2-r) * (2-r) * 15/(7*M_PI*h*h);
//    }
//
//    return -2 * r + 1.5 * r * r * 15/(7*M_PI*h*h);
//}

//double smoothing_funtion(particle particle1, particle particle2, int h) {
//    double alpha = 4.0 / 3.0 * h;
//    double r = (particle2.x - particle1.x) / (double) h;
//
//    if (r >= 2 || r <= -1) {
//        return 0;
//    }
//
//    if (r < -0.5) {
//        return pow(2 + 2 * r, 2) * -alpha;
//    }
//
//    if (r < 0) {
//        return (-8 * r - 12 * r * r) * -alpha;
//    }
//
//    if (r < 1) {
//        return (-2 * r + 3.0 / 2.0 * r * r * r) * alpha;
//    }
//
//    if (r < 2) {
//        return (-0.5 * pow(2 - r, 2)) * alpha;
//    }
//
//
//}
