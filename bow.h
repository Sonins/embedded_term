#include "util.h"

#define ANGLE_VELOCITY 0.5
#define MAX_ANGLE 90
#define INIT_ANGLE 30
#define MIN_ANGLE 0

struct bow {
    double angle;
    struct point center_pos;
};

void rotate_bow_up(bow *b) {
    if (b->angle < MAX_ANGLE) {
        b->angle += ANGLE_VELOCITY;
    }
}

void rotate_bow_down(bow *b) {
    if (b->angle > MIN_ANGLE) {
        b->angle -= ANGLE_VELOCITY;
    }
}