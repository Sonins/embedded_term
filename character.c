#include "game.h"

struct point get_neck_pos(struct character *ch) {
    struct point result;
    const int neck_offset_x = CHARACTER_WIDTH / 2;
    const int neck_offset_y = 15;
    result.x = ch->pos.x + neck_offset_x;
    result.y = ch->pos.y + neck_offset_y;

    return result;
}

void init_character(struct character *_character, int posx, int posy) {
    
    _character->pos.x = posx;
    _character->pos.y = posy;

    struct point neck_pos = get_neck_pos(_character);

    _character->body_box.lower_x = _character->pos.x - 6;
    _character->body_box.lower_y = (int) neck_pos.y;
    _character->body_box.upper_x = _character->pos.x + 6;
    _character->body_box.upper_y = MAP_HEIGHT;


    _character->head_box.lower_x = _character->pos.x - 8;
    _character->head_box.lower_y = MAP_HEIGHT - CHARACTER_HEIGHT - 5;
    _character->head_box.upper_x = _character->pos.x + 8;
    _character->head_box.upper_y = (int) neck_pos.y - 2;
}