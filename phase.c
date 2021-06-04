#include "game.h"

void aim_phase(struct game *g) {
    
    struct display_range range = {
        .col[0] = g->player_bow.center_pos.x - g->player_bow.max_radius,
        .col[1] = g->player_bow.center_pos.x + g->player_bow.max_radius,
        .row[0] = 0,
        .row[1] = g->player_bow.center_pos.y - g->player_bow.max_radius
    };

    int width = range.col[1] - range.col[0];

    struct point display_pos = {.x = 0, .y = MAP_HEIGHT - S_HEIGHT};
    uint32_t param_value[3];
    do {
        get_gpio_input(gpio_fd, param_value);
        if (param_value[GPIO_UP_INDEX]) {
            rotate_bow_up(&g->player_bow);
        }

        if (param_value[GPIO_DOWN_INDEX]) {
            rotate_bow_down(&g->player_bow);
        }

        draw_player(g);
        display_map(g);
    } while (!param_value[GPIO_FIRE_INDEX]);

    g->player_bow.tense = false;
    draw_player(g);
    display_map(g);
}

void fire_phase(struct game *g) {
    
}