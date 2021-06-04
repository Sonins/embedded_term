#include "game.h"

void arrow_precede(struct arrow *__arrow) {

}

void arrow_init(struct arrow *_arrow, struct bow *_bow) {
    struct point arrow_tip_pos = {
        .x = _bow->center_pos.x + cos(to_radian(_bow->angle)),
        .y = _bow->center_pos.y - sin(to_radian(_bow->angle))
    };

    _arrow->pos = arrow_tip_pos;
    

}