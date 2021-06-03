#include "arrow-game.h"

void rotate_bow_up(struct bow *b) {
    if (b->angle < BOW_MAX_ANGLE) {
        b->angle += BOW_ANGLE_CHANGE_RATE;
    }
}

void rotate_bow_down(struct bow *b) {
    if (b->angle > BOW_MIN_ANGLE) {
        b->angle -= BOW_ANGLE_CHANGE_RATE;
    }
}

void init_bow(struct bow *b, struct point center_pos) {
    b->angle = BOW_MIN_ANGLE;
    b->center_pos = center_pos;
    b->tense = false;
    b->pos.x = center_pos.x - BOW_POS_CENTER_OFFSET_X;
    b->pos.y = center_pos.y - BOW_POS_CENTER_OFFSET_Y;
}