#include <math.h>
#include <stdio.h>
#include "particle.h"

double smoothing_function(particle particle1, particle particle2, int h) {
    if (fabs(particle1.y - particle2.y) > 0.5) {
        return 0;
    }
    double r = fabs(particle2.x - particle1.x) / (double) h;

    if (r >= 2) {
        return 0;
    }

    if (r >= 1) {
        return -0.5 * (2-r) * (2-r) * 1. / h;
    }

    return -2 * r + 1.5 * r * r * 1. / h;

}

double smoothing_function2(particle particle1, particle particle2, int h){
    if (fabs(particle1.y - particle2.y) > 0.5){
        return 0;
    }

    double r = fabs(particle2.x - particle1.x) / (double) h;

    if (r >= 2){
        return 0;
    }
    if (r >= 1) {
        return (2. / 3. - r * r + 0.5 * pow(r, 3)) * 1./(double)h;
    }

    return 1. / 6. * pow(2 - r, 3) * 1./(double)h;
}
