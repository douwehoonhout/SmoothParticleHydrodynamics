#include <math.h>
#include <stdio.h>
#include "particle.h"

double calculateDistance(double position1, double position2, double roadLength) {
    double distance1, distance2;
    distance1 = fabs(position1 - position2);

    if (position1 < position2) {
        distance2 = position1 + roadLength - position2;
    }
    else {
        distance2 = position2 + roadLength - position1;
    }

    if (distance1 < distance2) {
        return distance1;
    }

    return distance2;
}


// Provide roadlength for cars that drive in a circle
double smoothing_function(particle particle1, particle particle2, int h, double roadLength) {
    double distance = calculateDistance(particle1.x, particle2.x, roadLength);
    double r = distance / (double) h;

    if (r >= 2) {
        return 0;
    }

    if (r >= 1) {
        return -0.5 * (2-r) * (2-r) * 1/h;
    }

    return -2 * r + 1.5 * r * r * 1/h;

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
