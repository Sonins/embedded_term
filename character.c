#include "arrow-game.h"

struct point get_neck_pos(struct character *ch) {
    struct point result;
    int neck_offset = 18;
    result.x = ch->pos.x;
    result.y = ch->pos.y + neck_offset;

    return result;
}

void init_character(struct character *_character, int posx, int posy) {
    
    _character->pos.x = posx;
    _character->pos.y = posy;

    struct point neck_pos = get_neck_pos(&_character);

    _character->body_box.lower_x = _character->pos.x - CHARACTER_WIDTH / 2;
    _character->body_box.lower_y = 0;
    _character->body_box.upper_x = _character->pos.x + CHARACTER_WIDTH / 2;
    _character->body_box.upper_y = neck_pos.y;


    _character->head_box.lower_x = _character->pos.x - CHARACTER_WIDTH / 2;
    _character->head_box.lower_y = neck_pos.y;
    _character->head_box.upper_x = _character->pos.x + CHARACTER_WIDTH / 2;
    _character->head_box.upper_y = CHARACTER_HEIGHT;
}