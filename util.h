#include <math.h>

#ifndef UTIL_H
#define UTIL_H

struct point {
    int x;
    int y;
};

struct point rotate(struct point *pos, struct point *center, double angle);
#endif