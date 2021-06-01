#include "util.h"

struct point rotate(struct point *pos, struct point *center, double angle) {
    double rotate_transform[2][2] = {{cos(angle), -1 * sin(angle)},
                                     {sin(angle), cos(angle)}};

    struct point vec = {pos->x - center->x, pos->y - center->y};

    struct point result;
    result.x =
        (int)(rotate_transform[0][0] * vec.x + rotate_transform[0][1] * vec.y) +
        center->x;
    result.y =
        (int)(rotate_transform[1][0] * vec.x + rotate_transform[1][1] * vec.y) +
        center->y;

    return result;
}