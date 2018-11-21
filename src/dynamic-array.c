#include <stdlib.h>
#include "dynamic-array.h"

int* alloc_array(int i) {
    return calloc(i, sizeof(int));
}
