#include <math.h>
#include "particle.h"

double smoothing_funtion(particle* particle1, particle* particle2, double h) {
    double r = fabs(particle2->x - particle1->x) / h;

    if (r >= 2) {
        return 0;
    }

    if (r >= 1) {
        return 1. / 6. * pow(2-r, 3);
    }

    return 2. / 3. - r * r + 0.5 * pow(r, 3);
}
