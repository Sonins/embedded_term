#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef UTIL_H
#define UTIL_H

#define MALLOC(p, s)                                       \
    if ((p = malloc(s)) == NULL) {                         \
        fprintf(stderr, "malloc: insufficient memory!\n"); \
        exit(1);                                           \
    }

struct point {
    double x;
    double y;
};

struct point rotate(struct point *pos, struct point *center, double angle);

double to_radian(double angle);

#endif