#include "game.h"

void arrow_fly(struct arrow *__arrow) {
    __arrow->pos.x += __arrow->power_x;
    __arrow->pos.y -= __arrow->power_y;
    __arrow->power_y -= ARROW_FALL_SPEED;
}

void init_arrow(struct arrow *_arrow, struct bow *_bow) {
    struct point arrow_tip_pos = {
        .x = _bow->center_pos.x + cos(to_radian(_bow->angle)),
        .y = _bow->center_pos.y - sin(to_radian(_bow->angle))
    };

    _arrow->pos = arrow_tip_pos;
    _arrow->power_x = ARROW_POWER * cos(to_radian(_bow->angle));
    _arrow->power_y = ARROW_POWER * sin(to_radian(_bow->angle));
}

bool arrow_expired(struct arrow *_arrow) {
    if (_arrow->pos.x > MAP_WIDTH)
        return true;
    
    if (_arrow->pos.y >= MAP_HEIGHT)
        return true;
    
    return false;
}

int arrow_enemy_colide(struct arrow *_arrow, struct character *enemy) {
    if (box_colide(&_arrow->pos, &enemy->body_box))
        return 1;
    
    if (box_colide(&_arrow->pos, &enemy->head_box))
        return 3;
    
    return 0;
}