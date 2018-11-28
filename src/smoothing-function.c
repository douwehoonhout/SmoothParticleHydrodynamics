#include <math.h>
#include <stdio.h>
#include "particle.h"

//double smoothing_funtion(particle particle1, particle particle2, int h) {
//    double r = fabs(particle2.x - particle1.x) / (double) h;
//
//    if (r >= 2) {
//        return 0;
//    }
//
//    if (r >= 1) {
//        return 1. / 6. * pow(2-r, 3);
//    }
//
//    return 2. / 3. - r * r + 0.5 * pow(r, 3);
//
//}

double smoothing_funtion(particle particle1, particle particle2, int h) {
    double r = fabs(particle2.x - particle1.x) / (double) h;

    if (r >= 2) {
        return 0;
    }

    if (r >= 1) {
        return -0.5 * (2-r) * (2-r) * 1/h;
    }

    return -2 * r + 1.5 * r * r * 1/h;

}
