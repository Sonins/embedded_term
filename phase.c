#include "game.h"

void aim_phase(struct game *g) {
    struct box update_box = {
        .lower_x = g->player_bow.center_pos.x - g->player_bow.max_radius,
        .upper_x = g->player_bow.center_pos.x + g->player_bow.max_radius,
        .upper_y = g->player_bow.center_pos.y - g->player_bow.max_radius,
        .lower_y = 0};

    int width = update_box.upper_x - update_box.lower_x;
    int height = update_box.upper_y = update_box.lower_y;

    struct point update_pos = {.x = update_box.lower_x,
                               .y = update_box.upper_y};

    struct point display_pos = {.x = 0, .y = MAP_HEIGHT - S_HEIGHT};

    do {
        uint32_t param_value[3];
        get_gpio_input(gpio_fd, param_value);

        if (param_value[GPIO_UP_INDEX]) {
            rotate_bow_up(g->player_bow);
        }

        if (param_value[GPIO_DOWN_INDEX]) {
            rotate_bow_down(g->player_bow);
        }

        draw_player(g);
        update_range_map(i2c_fd, (uint8_t *) g->entire_map, update_box, MAP_WIDTH, &display_pos)        
    } while (!param_value[GPIO_FIRE_INDEX]);

    g->player_bow.tense = false;
}