#include "game.h"

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
    b->angle = BOW_START_ANGLE;
    b->center_pos = center_pos;
    b->tense = true;
    b->pos.x = center_pos.x - BOW_POS_CENTER_OFFSET_X;
    b->pos.y = center_pos.y - BOW_POS_CENTER_OFFSET_Y;

    b->max_radius = BOW_WIDTH > BOW_HEIGHT
                        ? BOW_WIDTH - BOW_POS_CENTER_OFFSET_X
                        : BOW_HEIGHT - BOW_POS_CENTER_OFFSET_Y;

    b->draw_pos.x = g->player_bow.center_pos.x - g->player_bow.max_radius;
    b->draw_pos.y = g->player_bow.center_pos.y - g->player_bow.max_radius;
}

bool is_tense(struct bow *b) { return b->tense == true; }

bool is_release(struct bow *b) { return b->tense == false; }